#include "loader.hpp"
#include "controller.hpp"
#include <thread>
#include <future>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <optional>
#include <regex>
#ifdef __linux__
#include <dlfcn.h>
#include <link.h>
#else
#include <Psapi.h>
#pragma comment (lib, "Psapi.lib")//GetModuleInformation
#pragma comment (lib, "version.lib") //GetFileVersionInfoSize
#endif
//template class intercept::types::rv_allocator<intercept::__internal::gsFunction>;
//template class intercept::types::rv_allocator<intercept::__internal::gsOperator>;
//template class intercept::types::rv_allocator<intercept::__internal::gsNular>;
//template class intercept::types::rv_allocator<intercept::__internal::game_functions>;
//template class intercept::types::rv_allocator<intercept::__internal::game_operators>;

#ifdef LOADER_DEBUG
#define DEBUG_PTR(n) std::cerr << "intercept::loader: " << #n << ": 0x" << std::hex << n << std::endl
#else
#define DEBUG_PTR(n)
#endif

namespace intercept {
    loader::loader() : _attached(false), _patched(false) {}

    loader::~loader() {
    }

    class MemorySection {
    public:
#if _WIN32 || _WIN64
        explicit MemorySection(const MODULEINFO& modInfo) noexcept :
            start(reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll)),
            end(static_cast<uintptr_t>(modInfo.SizeOfImage) + reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll)) {}
#endif // _WIN32 || _WIN64
        MemorySection(uintptr_t _start, uintptr_t _end) noexcept : start(_start), end(_end) {}
        uintptr_t start;
        uintptr_t end;
        inline size_t size() const {
            return end - start;
        }
        std::optional<uintptr_t> findInMemory(const char* pattern, size_t patternLength) const {
            const uintptr_t base = start;
            const auto sz = size();
            for (uintptr_t i = 0; i < sz - patternLength; i++) {
                bool found = true;
                for (uintptr_t j = 0; j < patternLength; j++) {
                    found &= pattern[j] == *reinterpret_cast<char*>(base + i + j);
                    if (!found) {
                        break;
                    }
                }
                if (found) {
                    return base + i;
                }
            }
            return std::nullopt;
        }
        std::optional<uintptr_t> findInMemoryPattern(const char* pattern, const char* mask, uintptr_t offset = 0) const {
            const uintptr_t base = start;
            const auto sz = size();
            const auto patternLength = strlen(mask);
            for (uintptr_t i = 0; i < sz - patternLength; i++) {
                bool found = true;
                for (uintptr_t j = 0; j < patternLength; j++) {
                    found &= mask[j] == '?' || pattern[j] == *reinterpret_cast<char*>(base + i + j);
                    if (!found) {
                        break;
                    }
                }
                if (found) {
                    return base + i + offset;
                }
            }
            return std::nullopt;
        }
    };

    class MemorySections {
    protected:
        std::vector<MemorySection> sections;
    public:
#if _WIN32 || _WIN64
        MemorySections() {
            MODULEINFO modInfo = { nullptr };
            HMODULE hModule = GetModuleHandleA(nullptr);
            GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
            const uintptr_t baseAddress = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
            const uintptr_t moduleSize = static_cast<uintptr_t>(modInfo.SizeOfImage);
            sections.push_back(MemorySection(modInfo));
        }
#endif // _WIN32 || _WIN64
#ifdef __linux__
        MemorySections(const char* path = "/proc/self/maps") {
            std::ifstream maps(path);
            std::string line;
            // example: 00400000-0040e000 r--p 00000000 00:27 1709145                            /opt/faststeam/steamapps/common/Arma 3 Server/arma3server_x64
            const std::regex mapsPattern("^([0-9a-f]+)-([0-9a-f]+)\\s+(.{4})\\s+([0-9a-f]+)\\s+[0-9]+:[0-9]+\\s+[0-9]+\\s+(.*)$");
            std::smatch match;
            std::optional<std::string> firstModule = std::nullopt;
            while (std::getline(maps, line)) {
                if (!std::regex_match(line, match, mapsPattern)) {
                    continue;
                }
                // If we don't get a module name, then skip it
                if (match.size() < 6) {
                    continue;
                }
                // If this is the first module encountered, set the module name.
                if (!firstModule.has_value()) {
                    firstModule = match[5].str();
                }
                // Only read sections while we're still in the first module, and before we get to it's heap
                auto moduleName = match[5].str();
                if (moduleName == "[heap]" || moduleName != firstModule.value()) {
                    break;
                }
                // Parse out begin/end memory locations
                auto startParsed = std::strtoul(match[1].str().c_str(), nullptr, 16);
                auto endParsed = std::strtoul(match[2].str().c_str(), nullptr, 16);
                #ifdef LOADER_DEBUG
                    std::cerr << "intercept::loader: map line: " << line << std::endl;
                    std::cerr << '\t' << std::hex << startParsed << "-" << std::hex << endParsed << std::endl;
                #endif

                // Add section to array
                sections.push_back(MemorySection(static_cast<uintptr_t>(startParsed), static_cast<uintptr_t>(endParsed)));
            }
        }
#endif // defined(__linux__)
        explicit MemorySections(uintptr_t _start, uintptr_t _size): sections({MemorySection(_start, _start + _size)}) {}
        uintptr_t findInMemory(const char* pattern, size_t patternLength) const {
            for (const auto& section : sections) {
                auto found = section.findInMemory(pattern, patternLength);
                if (found.has_value()) {
                    return found.value();
                }
            }
            return 0;
        }
        uintptr_t findInMemory(const std::string_view& pattern) const {
            return findInMemory(pattern.data(), pattern.length());
        }
        uintptr_t findInMemoryPattern(const char* pattern, const char* mask, uintptr_t offset = 0) const {
            for (const auto& section : sections) {
                auto found = section.findInMemoryPattern(pattern, mask, offset);
                if (found.has_value()) {
                    return found.value();
                }
            }
            return 0;
        }
    };

    bool loader::get_function(std::string_view function_name_, unary_function & function_, std::string_view arg_signature_) {
        auto it = _unary_operators.find(function_name_);
        if (it != _unary_operators.end()) {
            for (auto op : it->second) {
                if (op.op->arg_type.type().count(arg_signature_)) {
                    function_ = reinterpret_cast<unary_function>(op.op->procedure_addr);
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    bool loader::get_function(std::string_view function_name_, unary_function & function_) {
        auto it = _unary_operators.find(function_name_);
        if (it != _unary_operators.end()) {
            function_ = reinterpret_cast<unary_function>(it->second[0].op->procedure_addr);
            return true;
        }
        return false;
    }

    bool loader::get_function(std::string_view function_name_, binary_function & function_) {
        auto it = _binary_operators.find(function_name_);
        if (it != _binary_operators.end()) {
            function_ = reinterpret_cast<binary_function>(it->second[0].op->procedure_addr);
            return true;
        }
        return false;
    }

    bool loader::get_function(std::string_view function_name_, binary_function & function_, std::string_view arg1_signature_, std::string_view arg2_signature_) {
        auto it = _binary_operators.find(function_name_);
        if (it != _binary_operators.end()) {
            for (auto op : it->second) {
                if (op.op->arg1_type.type().count(arg1_signature_) && op.op->arg2_type.type().count(arg2_signature_)) {
                    function_ = reinterpret_cast<binary_function>(op.op->procedure_addr);
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    bool loader::get_function(std::string_view function_name_, nular_function & function_) {
        auto it = _nular_operators.find(function_name_);
        if (it != _nular_operators.end()) {
            function_ = reinterpret_cast<nular_function>(it->second[0].op->procedure_addr);
            return true;
        }
        return false;
    }

    void loader::do_function_walk(uintptr_t state_addr_) {
        game_state_ptr = reinterpret_cast<game_state*>(state_addr_);
        DEBUG_PTR(game_state_ptr);

        // default constructor chosen by platform
        MemorySections memorySections;
        auto findInMemory = [memorySections](const char* pattern, size_t patternLength) -> uintptr_t {
            return memorySections.findInMemory(pattern, patternLength);
        };
        auto findInMemoryPattern = [memorySections](const char* pattern, const char* mask, uintptr_t offset = 0) {
            return memorySections.findInMemoryPattern(pattern, mask, offset);
        };

        auto getRTTIName = [](uintptr_t vtable) -> const char* {
            class v1 {
                virtual void doStuff() {}
            };
            class v2 : public v1 {
                virtual void doStuff() {}
            };
            v2* v = (v2*) vtable;
            try {

                auto& typex = typeid(*v);
#ifdef __GNUC__
                auto test = typex.name();
#else
                auto test = typex.raw_name();
#endif
                return test;
            } catch (std::bad_typeid) {
                return "";
            }
        };

        //This can be used to detect game version in case we already fix something for next release
        /*
        //Shamelessly copied from Dedmen's Hack :3
        CHAR fileName[_MAX_PATH];
        DWORD size = GetModuleFileName(nullptr, fileName, _MAX_PATH);
        fileName[size] = NULL;
        DWORD handle = 0;
        size = GetFileVersionInfoSize(fileName, &handle);
        BYTE* versionInfo = new BYTE[size];
        if (!GetFileVersionInfo(fileName, handle, size, versionInfo)) {
            delete[] versionInfo;
        }
        UINT                len = 0;
        VS_FIXEDFILEINFO*   vsfi = nullptr;
        VerQueryValue(versionInfo, "\\", reinterpret_cast<void**>(&vsfi), &len);
        short version = HIWORD(vsfi->dwFileVersionLS);//131
        short version1 = LOWORD(vsfi->dwFileVersionLS);//646
        short version2 = HIWORD(vsfi->dwFileVersionMS);// 1
        short version3 = LOWORD(vsfi->dwFileVersionMS);// 48
        delete[] versionInfo;
        */



        //Start them async before doing the other stuff so they are done when we are done parsing the script functions
    #ifdef __linux__
        auto future_stringOffset = std::async([&]() {
            auto offs = findInMemory("12MemFunction", 13);
            #ifdef LOADER_DEBUG
                auto prefix = "intercept::loader";
                fprintf(stderr, "%s: stringSearch: %s\n%s: stringOffset: %p\n", prefix, "12MemFunction", prefix, offs);
            #endif
            return offs;
        });
    #else
        auto future_stringOffset = std::async([&]() {return findInMemory("tbb4malloc_bi", 13); });
    #endif

        //Second part of finding the allocator. Done here so the second memorySearch is done when we are done parsing the Nulars

        auto future_allocatorVtablePtr = std::async(std::launch::deferred, [&]() -> uintptr_t {
            uintptr_t stringOffset = future_stringOffset.get();
        #ifndef __linux__
            return (findInMemory(reinterpret_cast<char*>(&stringOffset), sizeof(uintptr_t)) - sizeof(uintptr_t));
        #elif _LINUX64
            bool oldCompiler = *reinterpret_cast<uintptr_t*>(stringOffset - 8) == stringOffset;

            if (oldCompiler) {
                uintptr_t vtableStart = stringOffset + 0x20;
                return vtableStart;
            }

            auto ref = findInMemory(reinterpret_cast<char*>(&stringOffset), sizeof(uintptr_t));
            if (!ref) return 0;
            // find who points to the address after, there should only be one
            ref += 8;
            ref = findInMemory(reinterpret_cast<char*>(&ref), sizeof(uintptr_t));
            if (!ref) return 0;
            return ref - 0x108;
        #else
            static_assert(false, "32bit linux Not supported anymore intentional compile fail")
            return 0;
            //uintptr_t vtableStart = stringOffset - (0x09D20C70 - 0x09D20BE8);
            //return vtableStart;
            //return (findInMemory(reinterpret_cast<char*>(&vtableStart), 4));
        #endif
        });




        //auto future_unary_construct =std::async([&]() {return findInMemoryPattern("\x51\x8b\x44\x24\x00\x53\x55\x56\x33\xf6\x89\x74\x24\x00\x57\x8b\xf9\x8d\x5e\x00\x85\xc0\x74\x00\x50\xe8\x00\x00\x00\x00\x8b\xf0\x83\xc4\x00\x85\xf6\x74\x00\x8b\xc3\xf0\x0f\xc1\x06\x89\x74\x24\x00\x85\xf6\x74\x00\x8b\xc3\xf0\x0f\xc1\x06", "xxxx?xxxxxxxx?xxxxx?xxx?xx????xxxx?xxx?xxxxxxxxx?xxx?xxxxxx"); });

        //auto future_operator_construct = std::async([&]() {return findInMemoryPattern("\x51\x8b\x44\x24\x00\x53\x55\x56\x33\xf6\x89\x74\x24\x00\x57\x8b\xf9\x8d\x5e\x00\x85\xc0\x74\x00\x50\xe8\x00\x00\x00\x00\x8b\xf0\x83\xc4\x00\x85\xf6\x74\x00\x8b\xc3\xf0\x0f\xc1\x06\x89\x74\x24\x00\x85\xf6\x74\x00\x8b\xc3\xf0\x0f\xc1\x06\x6a\x00\x8d\x4f\x00\x89\x37\xe8\x00\x00\x00\x00\x83\xcd\x00\x85\xf6\x74\x00\x8b\xc5\xf0\x0f\xc1\x06\x48\x75\x00\x8b\x0d\x00\x00\x00\x00\x56\x8b\x01\xff\x50\x00\xc7\x44\x24\x00\x00\x00\x00\x00\x8b\x0f\x8b\x44\x24\x00\x89\x47\x00\x85\xc9\x74\x00\x8b\xc3\xf0\x0f\xc1\x01\x8b\x44\x24\x00\x89\x4f\x00\x89\x47\x00\x8b\x44\x24\x00\xc7\x47\x00\x00\x00\x00\x00\xc7\x47\x00\x00\x00\x00\x00\x85\xc0\x74\x00\x50\xe8\x00\x00\x00\x00\x8b\x57\x00\x83\xc4\x00\x85\xc0\x74\x00\x8b\xcb\xf0\x0f\xc1\x08", "xxxx?xxxxxxxx?xxxxx?xxx?xx????xxxx?xxx?xxxxxxxxx?xxx?xxxxxxx?xx?xxx????xx?xxx?xxxxxxxx?xx????xxxxx?xxx?????xxxxx?xx?xxx?xxxxxxxxx?xx?xx?xxx?xx?????xx?????xxx?xx????xx?xx?xxx?xxxxxx"); });

        //make sure insert patterns are long enough. they have to include the offset after the target of the first jmp instruction
        //auto future_operator_insert = std::async([&]() {return findInMemoryPattern("\x81\xec\x00\x00\x00\x00\x53\x56\x8b\xb4\x24\x00\x00\x00\x00\x8b\xd9\x57\x56\x8d\x4c\x24\x00\xe8\x00\x00\x00\x00\x8b\x46\x00\x85\xc0\x74\x00\x83\xc0\x00\xeb\x00\xb8\x00\x00\x00\x00\x83\xc3\x18", "xx????xxxxx????xxxxxxx?x????xx?xxx?xx?x?x????xxx"); });
        //auto future_unary_insert = std::async([&]() {return findInMemoryPattern("\x81\xec\x00\x00\x00\x00\x53\x56\x8b\xb4\x24\x00\x00\x00\x00\x8b\xd9\x57\x56\x8d\x4c\x24\x00\xe8\x00\x00\x00\x00\x8b\x46\x00\x85\xc0\x74\x00\x83\xc0\x00\xeb\x00\xb8\x00\x00\x00\x00\x83\xc3\x0C", "xx????xxxxx????xxxxxxx?x????xx?xxx?xx?x?x????xxx"); });

        //#TODO these patternfinds can be replaced by taking the alloc function out of any Types createFunction. and the dealloc function is right next to it asm wise


    #if _WIN64 || __X86_64__
        auto future_poolFuncAlloc = std::async([&]() {
            auto result = findInMemoryPattern("\x40\x53\x48\x83\xEC\x20\xFF\x41\x60\x48\x8B\x41\x08\x48\x8B\xD9\x48\x3B\xC1\x74\x0B\x48\x85\xC0\x74\x06\x48\x83\xC0\xE0\x75\x2B\x48\x8D\x41\x18\x48\x8B\x49\x20\x48\x3B\xC8\x74\x0E\x48\x85\xC9\x74\x09\x48\x8D\x41\xE0\x48\x85\xC0\x75\x10\x48\x8B\xCB\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x4C\x8B\x43\x08\x32\xC9\x45\x33\xD2\x4C\x3B\xC3\x74\x0B\x4D\x85\xC0\x74\x06\x49\x83\xC0\xE0\x75\x2A\x4C\x8B\x43\x20\x48\x8D\x43\x18\x4C\x3B\xC0", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
            if (!result) //vc143
                result = findInMemoryPattern("\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x20\xFF\x41\x60\x33\xF6\x48\x8B\x41\x08\x48\x8B\xD9\x48\x3B\xC1\x74\x0F\x48\x85\xC0\x74\x0A\x48\x83\xC0\xE0\x0F\x85\x00\x00\x00\x00\x48\x8B\x41\x20\x48\x8D\x79\x18\x48\x3B\xC7\x74\x0F\x48\x85\xC0\x74\x0A\x48\x83\xC0\xE0\x0F\x85\x00\x00\x00\x00\x48\x63\x51\x58\x48\x8B\x0D\x00\x00\x00\x00\x4C\x8B\xC2\x48\x8B\x01\xFF\x50\x38\x48\x89\x70\x28\x48\x8B\xD0\x48\x89\x70\x20\x48\x8D\x48\x20\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x89\x30\x89\x70\x10\x48\x89\x58\x08\x48\x8B\x47\x08\x48\x89\x08\x48\x8B\x47\x08\x48\x89\x39\x48\x89\x42\x28\xFF\x47\x10\x48\x89\x4F\x08\x44\x8B\x4B\x5C", "xxxx?xxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

            return result;
        });
        auto future_poolFuncDealloc = std::async([&]() {
            auto result = findInMemoryPattern("\x48\x85\xD2\x0F\x84\x00\x00\x00\x00\x53\x48\x83\xEC\x20\x48\x63\x41\x58\x48\x89\x7C\x24\x00\x48\x8B\xFA\x48\xFF\xC8\x48\x8B\xD9\x48\x23\xC2\x48\x2B\xF8\x83\x3F\x00\x74\x28\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x44\x8B\x07\x48\x8D\x0D\x00\x00\x00\x00\x48\x8B\xD7\x48\x8B\x7C\x24\x00\x48\x83\xC4\x20\x5B\xE9\x00\x00\x00\x00\x48\x8B\x47\x18\x48\x89\x02\x48\x83\x7F\x00\x00\x48\x89\x57\x18\x0F\x94\xC0\x48\x89\x7A\x08\xFF\x4F\x10\x41\x0F\x94\xC0\x84\xC0\x74\x46\x48\x8B\x4F\x28\x48\x8B\x47\x20\x48\x8D\x57\x20\x48\x89\x01\x48\x8B\x42\x08\x48\x8B\x0A", "xxxxx????xxxxxxxxxxxxx?xxxxxxxxxxxxxxxxxxxxxxx????x????xxxxxx????xxxxxxx?xxxxxx????xxxxxxxxxx??xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
            if (!result) //vc143
                result = findInMemoryPattern("\x48\x85\xD2\x0F\x84\x00\x00\x00\x00\x53\x48\x83\xEC\x20\x48\x63\x41\x58\x48\x8B\xD9\x48\xFF\xC8\x48\x89\x7C\x24\x00\x48\x23\xC2\x48\x8B\xFA\x48\x2B\xF8\x83\x3F\x00\x74\x28\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x44\x8B\x07\x48\x8D\x0D\x00\x00\x00\x00\x48\x8B\xD7\x48\x8B\x7C\x24\x00\x48\x83\xC4\x20\x5B\xE9\x00\x00\x00\x00\x48\x8B\x47\x18\x48\x89\x02\x48\x8B\x4F\x18\x48\x89\x57\x18\x48\x89\x7A\x08\x8B\x57\x10\xFF\xCA\x48\x89\x6C\x24\x00\x33\xED\x89\x57\x10\x48\x85\xC9\x75\x78\x48\x8B\x4F\x28\x48\x8B\x47\x20\x48\x89\x01\x48\x8B\x4F\x20\x48\x8B\x47\x28\x48\x89\x41\x08\x48\x89\x6F\x28\x48\x89\x6F\x20\xFF\x4B\x40\x85\xD2\x75\x2B\x48\x8B\x43\x20\x48\x8D\x57\x20\x48\x85\xFF", "xxxxx????xxxxxxxxxxxxxxxxxxx?xxxxxxxxxxxxxxxxx????x????xxxxxx????xxxxxxx?xxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");


            return result;
        });
        //auto future_fileBanks = std::async([&]() {
        //    auto patternFindLoc = findInMemoryPattern("\x48\x83\xEC\x28\x48\x8B\x0D\x00\x00\x00\x00\xBA\x00\x00\x00\x00\x48\x8B\x01\xFF\x50\x08\x33\xC9\x48\x85\xC0\x74\x18\x48\x89\x08\x89\x48\x10\x89\x48\x08\x48\x89\x48\x28\x89\x48\x38\x89\x48\x30\x88\x48\x21\xEB\x03\x48\x8B\xC1\x48\x8D\x0D\x00\x00\x00\x00\x48\x89\x05\x00\x00\x00\x00\x48\x83\xC4\x28\xE9", "xxxxxxx????x????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx????xxxxx");
        //    auto offs = *reinterpret_cast<uint32_t*>(patternFindLoc + 0x42);
        //    return patternFindLoc + 0x46 + offs;
        //});
    #else

    #ifdef __linux__
        //auto future_poolFuncAlloc = std::async([&]() {return findInMemoryPattern("", ""); });
        //auto future_poolFuncDealloc = std::async([&]() {return findInMemoryPattern("\x56\x53\x83\xec\x00\x8b\x44\x24\x00\x8b\x74\x24\x00\x85\xc0\x0f\x84\x00\x00\x00\x00\x8b\x18\x8b\x0b\x85\xc9\x0f\x85\x00\x00\x00\x00\x8b\x53\x00\x89\x10\x89\x43\x00\x89\x58\x00\x83\x6b\x00\x00\x0f\x94\xc0\x85\xd2\x0f\x84\x00\x00\x00\x00\x84\xc0\x74\x00\x8b\x43\x00\x8b\x53\x00\x89\x10\x8b\x53\x00\x89\x42\x00\xc7\x43\x00\x00\x00\x00\x00\x83\x6e\x00\x00\x8b\x56\x00\x8d\x43\x00\x89\x02\x89\x53\x00\x8d\x56\x00\x89\x53\x00\x83\x46\x00\x00\x89\x46", "xxxx?xxx?xxx?xxxx????xxxxxxxx????xx?xxxx?xx?xx??xxxxxxx????xxx?xx?xx?xxxx?xx?xx?????xx??xx?xx?xxxx?xx?xx?xx??xx"); });
    #else
        auto future_poolFuncAlloc = std::async([&]() {return findInMemoryPattern("\x56\x8B\xF1\xFF\x46\x38\x8B\x46\x04\x3B\xC6\x74\x09\x85\xC0\x74\x05\x83\xC0\xF0\x75\x26\x8B\x4E\x10\x8D\x46\x0C\x3B\xC8\x74\x0B\x85\xC9\x74\x07\x8D\x41\xF0\x85\xC0\x75\x11", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); });
        auto future_poolFuncDealloc = std::async([&]() {return findInMemoryPattern("\x8B\x44\x24\x04\x85\xC0\x74\x09\x89\x44\x24\x04\xE9", "xxxxxxxxxxxxx"); });
        //auto future_fileBanks = std::async([&]() {
        //    auto patternFindLoc = findInMemoryPattern("\x8b\x0d\x00\x00\x00\x00\x6a\x00\x8b\x01\xff\x50\x00\x85\xc0\x74\x00\xc7\x00\x00\x00\x00\x00\xc7\x40\x00\x00\x00\x00\x00\xc7\x40\x00\x00\x00\x00\x00\xc7\x40\x00\x00\x00\x00\x00\xc7\x40\x00\x00\x00\x00\x00\xc7\x40\x00\x00\x00\x00\x00\xc6\x40\x00\x00\x68\x00\x00\x00\x00\xa3\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x59\xc3\x33\xc0\x68\x00\x00\x00\x00\xa3\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x59\xc3", "xx????x?xxxx?xxx?xx????xx?????xx?????xx?????xx?????xx?????xx??x????x????x????xxxxx????x????x????xx");
        //    return *reinterpret_cast<uintptr_t*>(patternFindLoc) + 0x44;
        //    //prntscr gli4fh dedmen sharex/eko4AXiY.png
        //});
    #endif

    #endif

    #if _WIN32 && !_WIN64
        //via profile context "scrpt"
        auto future_evaluateScript = std::async([&]() {
            //profiling branch
            auto patternFindLoc = findInMemoryPattern(
                "\xA1\x00\x00\x00\x00\x81\xEC\x00\x00\x00\x00\x53\x55\x56\x57\x8B\xF9\xA8\x01\x75\x1C\x83\xC8\x01\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xA3\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x80\x3D\x00\x00\x00\x00\x00\x75\x49\xE8\x00\x00\x00\x00\x50\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\xB9\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xA3\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xA3\x00\x00\x00\x00\xC6\x05\x00\x00\x00\x00\x00\xB9\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x0F\xB6\xC0\x8D\x4C\x24\x1C\x50\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\xB4\x24\x00\x00\x00\x00\x83\xCB\xFF\x80\x3D\x00\x00\x00\x00\x00\xBD\x00\x00\x00\x00\x74\x68\x51\x8B\x0E\x8B\xD4\x85\xC9\x74\x06\x8B\xC5\xF0\x0F\xC1\x01\x8D\x44\x24\x18\x89\x0A\x50",
                "x????xx????xxxxxxxxxxxxxxx????????x????xx????????xx?????xxx????xx????x????x????xx????????xx????????xx????????x????x????x????xx?????x????x????xxxxxxxxx????x????xxx????xxxxx?????x????xxxxxxxxxxxxxxxxxxxxxxxx");

            if (!patternFindLoc) //non-prof
                patternFindLoc = findInMemoryPattern(
                    "\x8b\x44\x24\x00\x81\xec\x00\x00\x00\x00\x8b\x00\x53\x55\x56\x57\x8b\xf9\x85\xc0\x74\x00\x80\x78\x00\x00\x75\x00\x8b\x8c\x24\x00\x00\x00\x00\x8b\x09\x85\xc9\x0f\x84\x00\x00\x00\x00\x83\x79\x00\x00\x0f\x84\x00\x00\x00\x00\x83\xbc\x24\x00\x00\x00\x00\x00\x75\x00\x80\xbf\x00\x00\x00\x00\x00\x74\x00\xc7\x84\x24\x00\x00\x00\x00\x00\x00\x00\x00\xeb\x00\x85\xc0\x74\x00\x83\xc0\x00\xeb\x00\xb8\x00\x00\x00\x00\x50\x68\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x83\xc4\x00\x8b\x87\x00\x00\x00\x00\x83\xcd\x00\xc7\x40\x00\x00\x00\x00\x00\x8d\x44\x24\x00\x8b\xb7\x00\x00\x00\x00\x83\xc6\x00\x3b\xf0\x74\x00\x8b\x16\x85\xd2\x74\x00\x8b\xc5\xf0\x0f\xc1\x02\x48\x75\x00\x8b\x0d\x00\x00\x00\x00\x52\x8b\x01\xff\x50\x00\xc7\x06\x00\x00\x00\x00\x6a\x00\x8d\x4c\x24\x00\xe8\x00\x00\x00\x00\x8b\xb7\x00\x00\x00\x00\x8b\xce\xe8\x00\x00\x00\x00\x8b\xce\x8a\xd8\xe8\x00\x00\x00\x00\x8b\x94\x24\x00\x00\x00\x00\x89\x84\x24\x00\x00\x00\x00\x35\x00\x00\x00\x00\x8b\xc8\x88\x9c\x24\x00\x00\x00\x00\xd1\xf9\xbb\x00\x00\x00\x00\x2b\xc1\x89\x8c\x24",
                    "xxx?xx????xxxxxxxxxxx?xx??x?xxx????xxxxxx????xx??xx????xxx?????x?xx?????x?xxx????????x?xxx?xx?x?x????xx????x????xx?xx????xx?xx?????xxx?xx????xx?xxx?xxxxx?xxxxxxxx?xx????xxxxx?xx????x?xxx?x????xx????xxx????xxxxx????xxx????xxx????x????xxxxx????xxx????xxxxx");

            return patternFindLoc;
        });
        //Checked on prof/non-prof
        auto future_varSetLocal = std::async([&]() {
            auto patternFindLoc = findInMemoryPattern(
                "\x51\x56\x57\x8B\x7C\x24\x10\x8B\xF1\x85\xFF\x0F\x84\x00\x00\x00\x00\x80\x3F\x00\x0F\x84\x00\x00\x00\x00\x57\xC7\x44\x24\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\x54\x24\x14\x83\xC4\x04\x85\xC0\x74\x09\xB9\x00\x00\x00\x00\xF0\x0F\xC1\x08\x53\x83\xCB\xFF\x89\x44\x24\x14\x85\xD2\x74\x15\x8B\xC3\xF0\x0F\xC1\x02\x48\x75\x0C\x8B\x0D\x00\x00\x00\x00\x52\x8B\x01\xFF\x50\x0C\x8D\x4C\x24\x14\xE8\x00\x00\x00\x00\x80\x7C\x24\x00\x00\x75\x12\x80\x3F\x5F\x74\x0D\x6A\x05\x56\xE8\x00\x00\x00\x00\x83\xC4\x08\xEB\x56",
                "xxxxxxxxxxxxx????xxxxx????xxxx?????x????xxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxx????xxx??xxxxxxxxxxx????xxxxx");

            return patternFindLoc;
        });
    #elif _WIN32 && _WIN64
        //via profile context "scrpt"
        auto future_evaluateScript = std::async([&]() {
            //profiling branch missing for x64
            auto patternFindLoc = findInMemoryPattern(
                "\x48\x89\x5C\x24\x00\x4C\x89\x4C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x8B\x05\x00\x00\x00\x00\x83\xCE\xFF\x49\x8B\xD9\x4D\x8B\xE8\x4C\x8B\xF2\x4C\x8B\xF9\xA8\x01\x75\x1A\x83\xC8\x01\x48\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x89\x35\x00\x00\x00\x00\x89\x05\x00\x00\x00\x00\x80\x3D\x00\x00\x00\x00\x00\x4C\x8D\x25\x00\x00\x00\x00\x75\x46\xE8\x00\x00\x00\x00\x48\x8D\x15\x00\x00\x00\x00\x4C\x8D\x05\x00\x00\x00\x00\x49\x8B\xCC\x44\x8B\xC8\x4C\x89\x25\x00\x00\x00\x00\x48\x89\x15\x00\x00\x00\x00\x4C\x89\x05\x00\x00\x00\x00\x89\x05\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xC6\x05\x00\x00\x00\x00\x00\x89\x05\x00\x00\x00\x00\x48\x8D\x3D\x00\x00\x00\x00\x48\x8B\xCF\xE8\x00\x00\x00\x00\x48\x89\x7C\x24\x00\x33\xFF\x83\x3D\x00\x00\x00\x00\x00\x48\x89\x7C\x24\x00\x88\x44\x24\x40\x74\x45\x40\x38\x3D\x00\x00\x00\x00\x75\x12\x84\xC0\x74\x38\xFF\x15\x00\x00\x00\x00\x39\x05\x00\x00\x00\x00\x75\x2A",
                "xxxx?xxxx?xxxxxxxxxxxxxxx????xxx????xx????xxxxxxxxxxxxxxxxxxxxxxxxx????????xx????xx????xx?????xxx????xxx????xxx????xxx????xxxxxxxxx????xxx????xxx????xx????x????xx?????xx????xxx????xxxx????xxxx?xxxx?????xxxx?xxxxxxxxx????xxxxxxxx????xx????xx");

            if (!patternFindLoc) //non-prof
                patternFindLoc = findInMemoryPattern(
                    "\x4C\x89\x4C\x24\x00\x4C\x89\x44\x24\x00\x55\x56\x41\x56\x41\x57\x48\x8D\xAC\x24\x00\x00\x00\x00\x48\x81\xEC\x00\x00\x00\x00\x49\x8B\x00\x48\x8B\xF2\x4C\x8B\xF1\x48\x85\xC0\x74\x06\x80\x78\x10\x00\x75\x16\x49\x8B\x09\x48\x85\xC9\x0F\x84\x00\x00\x00\x00\x83\x79\x08\x00\x0F\x84\x00\x00\x00\x00\x48\x89\x9C\x24\x00\x00\x00\x00\x48\x89\xBC\x24\x00\x00\x00\x00\x4C\x89\xA4\x24\x00\x00\x00\x00\x4C\x89\xAC\x24\x00\x00\x00\x00\x4C\x8B\xAD\x00\x00\x00\x00\x4D\x85\xED\x75\x2E\x45\x38\xAE\x00\x00\x00\x00\x74\x09\x4C\x8D\x2D\x00\x00\x00\x00\xEB\x1C\x48\x8D\x50\x10\x48\x85\xC0\x75\x07\x48\x8D\x15\x00\x00\x00\x00",
                    "xxxx?xxxx?xxxxxxxxxx????xxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxx????xxxx????xxxx????xxxx????xxxx????xxx????xxxxxxxx????xxxxx????xxxxxxxxxxxxxx????");

            return patternFindLoc;
        });
        //Checked on prof/non-prof
        auto future_varSetLocal = std::async([&]() {
            auto patternFindLoc = findInMemoryPattern(
                "\x48\x89\x6C\x24\x00\x56\x57\x41\x56\x48\x83\xEC\x30\x41\x0F\xB6\xE9\x4D\x8B\xF0\x48\x8B\xF2\x48\x8B\xF9\x48\x85\xD2\x0F\x84\x00\x00\x00\x00\x80\x3A\x00\x0F\x84\x00\x00\x00\x00\x48\x8B\xCA\x48\x89\x5C\x24\x00\x48\xC7\x44\x24\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8B\x54\x24\x00\x48\x85\xC0\x74\x03\xF0\xFF\x00\x48\x89\x44\x24\x00\x48\x85\xD2\x74\x17\xF0\xFF\x0A\x75\x0D\x48\x8B\x0D\x00\x00\x00\x00\x48\x8B\x01\xFF\x50\x18\x48\x8B\x44\x24\x00\x48\x85\xC0\x74\x6E\x48\x8D\x48\x10\xE8\x00\x00\x00\x00\x84\xC0\x48\x8B\x44\x24\x00\x75\x5C\x48\x85\xC0\x74\x57\x8B\x08\x83\xF9\x01\x7E\x37\x48\x8B\x4C\x24\x00\x48\x83\xC1\x10\xE8\x00\x00\x00\x00\x48\x8B\x54\x24\x00\x48\x85\xC0\x74\x03\xF0\xFF\x00\x48\x89\x44\x24\x00\x48\x85\xD2\x74\x17\xF0\xFF\x0A\x75\x0D\x48\x8B\x0D\x00\x00\x00\x00\x48\x8B\x01\xFF\x50\x18\x48\x8B\x44\x24\x00\x48\x85\xC0\x74\x0F\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00\x48\x8B\x44\x24\x00\x80\x7C\x24\x00\x00\x75\x14\x80\x3E\x5F\x74\x0F\xBA\x00\x00\x00\x00\x48\x8B\xCF\xE8\x00\x00\x00\x00\xEB\x58",
                "xxxx?xxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxx????xxxxxxx?xxxx?????x????xxxx?xxxxxxxxxxxx?xxxxxxxxxxxxx????xxxxxxxxxx?xxxxxxxxxx????xxxxxx?xxxxxxxxxxxxxxxxxx?xxxxx????xxxx?xxxxxxxxxxxx?xxxxxxxxxxxxx????xxxxxxxxxx?xxxxxxxxx?x????xxxx?xxx??xxxxxxxx????xxxx????xx");

            return patternFindLoc;
        });
    #endif

        //We need the allocator before we run the command scanning because the logging calls need r_string allocations

        uintptr_t allocatorVtablePtr = future_allocatorVtablePtr.get();
        DEBUG_PTR(allocatorVtablePtr);
#ifdef __linux__
        const char* test = getRTTIName((uintptr_t)(&allocatorVtablePtr));
        assert(strcmp(test, "12MemFunctions") == 0);
#else
        const char* test = getRTTIName(allocatorVtablePtr);
        bool vc143Allocator = false;
        if (strlen(test) == 0) {
            allocatorVtablePtr -= 0xA8; // vc143 build
            test = getRTTIName(allocatorVtablePtr);
            vc143Allocator = true;
        }

        assert(strcmp(test, ".?AVMemTableFunctions@@") == 0);
#endif
        _allocator.genericAllocBase = allocatorVtablePtr;



        /*
        Unary Hashmap

        This is a hashmap using a key->bucket system, so an array of arrays keyed by a hash.
        We don't give a fuck about that though, we just want to iterate through all of the
        buckets and in turn each item in the bucket, because they are our operator entries.
        */
        for (auto& it : game_state_ptr->_scriptFunctions) {
            for (auto& entry : it) {
                unary_entry new_entry;
                new_entry.op = entry._operator;
                new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
                new_entry.name = entry._name.data();
                LOG(INFO, "Found unary operator: {} {} ({}) @{:x}",
                    new_entry.op->return_type.type_str(), new_entry.name,
                    new_entry.op->arg_type.type_str(), reinterpret_cast<uintptr_t>(new_entry.op->procedure_addr));
                _unary_operators[entry._name2].push_back(new_entry);
            }
        }

        /*
        Binary Hashmap
        */
        for (auto& it : game_state_ptr->_scriptOperators) {
            for (auto& entry : it) {
                binary_entry new_entry;
                new_entry.op = entry._operator;
                new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
                new_entry.name = entry._name.data();
                LOG(INFO, "Found binary operator: {} ({}) {} ({}) @{:x}",
                    new_entry.op->return_type.type_str(), new_entry.op->arg1_type.type_str(), new_entry.name,
                    new_entry.op->arg2_type.type_str(), reinterpret_cast<uintptr_t>(new_entry.op->procedure_addr));
                _binary_operators[entry._name2].push_back(new_entry);
            }
        }

        /*
        Nular Hashmap
        */
        for (auto& entry : game_state_ptr->_scriptNulars) {
            nular_entry new_entry;
            new_entry.op = entry._operator;
            new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
            new_entry.name = entry._name.data();
            LOG(INFO, "Found nular operator: {} {} @{:x}", new_entry.op->return_type.type_str(), new_entry.name, reinterpret_cast<uintptr_t>(new_entry.op->procedure_addr));
            _nular_operators[entry._name2].push_back(new_entry);
        }

        //GameData pool allocators
        for (auto& entry : game_state_ptr->_scriptTypes) {
            if (!entry->_createFunction) continue; //Some types don't have create functions. Example: VECTOR.
        #if _WIN64 || __X86_64__
            auto baseOffset = 0x7;
            if (entry->_name == "CODE"sv) baseOffset += 2;

            if (vc143Allocator)
                baseOffset = 0xC;

            auto instructionPointer = reinterpret_cast<uintptr_t>(entry->_createFunction) + baseOffset + 0x4;
            auto offset = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(entry->_createFunction) + baseOffset);
            uintptr_t poolAlloc = /*reinterpret_cast<uintptr_t>*/(instructionPointer + offset);
        #else
        #ifdef __linux__
            uintptr_t poolAlloc = 1;
        #else
            auto p1 = reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(entry->_createFunction) + 0x3);
            uintptr_t poolAlloc = *reinterpret_cast<uintptr_t*>(p1);
        #endif
        #endif
            LOG(INFO, "{} {} {}", entry->_localizedName, entry->_javaFunc, entry->_readableName);
            LOG(INFO, "Found Type operator: {} create@{:x} pool@{:x}", entry->_name, reinterpret_cast<uintptr_t>(entry->_createFunction), poolAlloc);
            //OutputDebugStringA(entry->_name.data());
            //OutputDebugStringA("\n");

            const auto type = types::__internal::game_datatype_from_string(entry->_name);
            if (poolAlloc && type != types::game_data_type::end) {
                _allocator._poolAllocs[static_cast<size_t>(type)] = reinterpret_cast<rv_pool_allocator*>(poolAlloc);
                _sqf_register_funcs._types[static_cast<size_t>(type)] = entry;
            }
        }


        //File Banks
    #ifndef __linux__
            //_sqf_register_funcs._file_banks = future_fileBanks.get(); //fixed in 1.76. broken again in prof v1
    #endif

        _sqf_register_funcs._type_vtable = _binary_operators["arrayintersect"sv].front().op->arg1_type.get_vtable();
        _sqf_register_funcs._compoundtype_vtable = _unary_operators["isnil"sv].front().op->arg_type.compound_type->get_vtable();

        _sqf_register_funcs._gameState = state_addr_;

    #ifndef __linux__
        _allocator.poolFuncAlloc = future_poolFuncAlloc.get();
        _allocator.poolFuncDealloc = future_poolFuncDealloc.get();
    #endif
        _allocator.gameState = game_state_ptr;

    #if _WIN32
        //via profile context "scrpt"
        evaluate_script_function = future_evaluateScript.get();
        varset_function = future_varSetLocal.get();

        if (evaluate_script_function) {
            _allocator.evaluate_func = [](const game_data_code& code, void* ns, const r_string& name) -> game_value {
                typedef game_value*(__thiscall *evaluate_func) (game_state* gs, game_value& ret, const r_string& code, void* instruction_list, void* context, void* ns, const r_string& name);
                
                evaluate_func func = reinterpret_cast<evaluate_func>(loader::get().evaluate_script_function);
                

                struct contextType {
                    bool _local;
                    bool _nilerror;
                } c{ false, true };
                game_value ret;
                func(loader::get().game_state_ptr, ret, code.code_string, (void*) &code.instructions, &c, ns, name);
                return ret;
            };
        }

    #endif





    }

    const unary_map & loader::unary() const {
        return _unary_operators;
    }

    const binary_map & loader::binary() const {
        return _binary_operators;
    }

    const nular_map & loader::nular() const {
        return _nular_operators;
    }

    const types::__internal::allocatorInfo* loader::get_allocator() const {
        return &_allocator;
    }

    const intercept::sqf_register_functions& loader::get_register_sqf_info() const {
        return _sqf_register_funcs;
    }

#ifdef __linux__
#include <unistd.h>     // getpid...
    bool IsBadReadPtr(void *ptr, size_t size) {
        int result = access((const char *) ptr, F_OK);
        if (result == -1 && errno == EFAULT)
            return true;
        return false;
    }

#endif

    uintptr_t loader::find_game_state(uintptr_t stack_base) {
        auto checkValid = [](uintptr_t base) -> bool {
            if (IsBadReadPtr(reinterpret_cast<void*>(base), 32)) return false;
            struct size_check {
                uintptr_t p1;//typearray
                uintptr_t typeCount;
                uintptr_t typeCapacity;
                uintptr_t p2;//functions
                int f_tableCount{ 0 };
                int f_count{ 0 };
                uintptr_t p3;//operators
                int o_tableCount{ 0 };
                int o_count{ 0 };
                uintptr_t p4;//nulars
                int n_tableCount{ 0 };
                int n_count{ 0 };
            };
            auto size_check_type = reinterpret_cast<size_check*>(base);
            if (size_check_type->typeCount != size_check_type->typeCapacity) return false; //auto_array size vs capacity. Should be compacted here.
                                                                          //Check if all the function tables are valid
            if (IsBadReadPtr(reinterpret_cast<void*>(size_check_type->p1), 32)) return false;
            if (IsBadReadPtr(reinterpret_cast<void*>(size_check_type->p2), 32)) return false;
            if (IsBadReadPtr(reinterpret_cast<void*>(size_check_type->p3), 32)) return false;
            if (IsBadReadPtr(reinterpret_cast<void*>(size_check_type->p4), 32)) return false;
            return true;
        };

        //#ifdef __linux__
        //    uintptr_t game_state_addr = *reinterpret_cast<uintptr_t *>(stack_base + 0x264);
        //#else
        //    #if _WIN64 || __X86_64__
        //        uintptr_t game_state_addr = *reinterpret_cast<uintptr_t *>(stack_base + 0x160);
        //        if (checkValid(game_state_addr)) return game_state_addr;
        //        game_state_addr = *reinterpret_cast<uintptr_t *>(stack_base + 0x190); //Found in 1.76 profv7
        //    #else
        //        uintptr_t game_state_addr = *reinterpret_cast<uintptr_t *>(stack_base + 8);
        //    #endif
        //#endif
        //
        //    if (checkValid(game_state_addr)) return game_state_addr;

        for (uintptr_t i = 0; i < 0x300; i += sizeof(uintptr_t)) {
            const bool is_valid = checkValid(*reinterpret_cast<uintptr_t *>(stack_base + i));
            if (is_valid) return *reinterpret_cast<uintptr_t *>(stack_base + i);
        }

        return 0x0;
    }
}
