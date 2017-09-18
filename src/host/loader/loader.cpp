#include "loader.hpp"
#include "controller.hpp"
#include <thread>
#include <future>
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

namespace intercept {
    loader::loader() : _attached(false), _patched(false) {}

    loader::~loader() {

    }

    bool loader::get_function(std::string_view function_name_, unary_function & function_, std::string arg_signature_) {
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

    bool loader::get_function(std::string_view function_name_, binary_function & function_, std::string arg1_signature_, std::string arg2_signature_) {
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

    bool loader::hook_function(std::string_view function_name_, void * hook_, unary_function & trampoline_) {
        LOG(WARNING) << "Attempting to hook unary function "sv << function_name_;
        auto op = _unary_operators.find(function_name_);
        if (op != _unary_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            trampoline_ = *reinterpret_cast<unary_function *>(op_ptr);
            memcpy(reinterpret_cast<void *>(op_ptr), &hook_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    bool loader::hook_function(std::string_view function_name_, void * hook_, binary_function & trampoline_) {
        LOG(WARNING) << "Attempting to hook binary function "sv << function_name_;
        auto op = _binary_operators.find(function_name_);
        if (op != _binary_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            trampoline_ = *reinterpret_cast<binary_function *>(op_ptr);
            memcpy(reinterpret_cast<void *>(op_ptr), &hook_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    bool loader::hook_function(std::string_view function_name_, void * hook_, nular_function & trampoline_) {
        LOG(WARNING) << "Attempting to hook nular function "sv << function_name_;
        auto op = _nular_operators.find(function_name_);
        if (op != _nular_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            trampoline_ = *reinterpret_cast<nular_function *>(op_ptr);
            memcpy(reinterpret_cast<void *>(op_ptr), &hook_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    bool loader::unhook_function(std::string function_name_, void * hook_, unary_function & trampoline_) {
        LOG(WARNING) << "Attempting to unhook unary function "sv << function_name_;
        if (&trampoline_ == nullptr)
            return false;
        auto op = _unary_operators.find(function_name_);
        if (op != _unary_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            memcpy(reinterpret_cast<void *>(op_ptr), &trampoline_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    bool loader::unhook_function(std::string function_name_, void * hook_, binary_function & trampoline_) {
        //LOG(DEBUG) << "Attempting to unhook binary function "sv << function_name_;
        if (&trampoline_ == nullptr)
            return false;
        auto op = _binary_operators.find(function_name_);
        if (op != _binary_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            memcpy(reinterpret_cast<void *>(op_ptr), &trampoline_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    bool loader::unhook_function(std::string function_name_, void * hook_, nular_function & trampoline_) {
        //LOG(DEBUG) << "Attempting to unhook nular function "sv << function_name_;
        if (&trampoline_ == nullptr)
            return false;
        auto op = _nular_operators.find(function_name_);
        if (op != _nular_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            memcpy(reinterpret_cast<void *>(op_ptr), &trampoline_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    void loader::do_function_walk(uintptr_t state_addr_) {
        uintptr_t types_array = state_addr_;
        auto game_state = reinterpret_cast<__internal::game_state*>(state_addr_);

    #ifdef __linux__
        std::ifstream maps("/proc/self/maps");
        uintptr_t start;
        uintptr_t end;
        char placeholder;
        maps >> std::hex >> start >> placeholder >> end;
        //link_map *lm = (link_map*) dlopen(0, RTLD_NOW);
        //uintptr_t baseAddress = reinterpret_cast<uintptr_t>(lm->l_addr);
        //uintptr_t moduleSize = 35000000; //35MB hardcoded till I find out how to detect it properly
        uintptr_t baseAddress = start;
        uintptr_t moduleSize = end - start;
    #else
        MODULEINFO modInfo = { nullptr };
        HMODULE hModule = GetModuleHandleA(nullptr);
        GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
        uintptr_t baseAddress = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
        uintptr_t moduleSize = static_cast<uintptr_t>(modInfo.SizeOfImage);
    #endif
        //std::cout << "base - size" << std::hex << baseAddress << moduleSize << "\n";
        auto findInMemory = [baseAddress, moduleSize](const char* pattern, size_t patternLength) ->uintptr_t {
            uintptr_t base = baseAddress;
            uintptr_t size = moduleSize;
            for (uintptr_t i = 0; i < size - patternLength; i++) {
                bool found = true;
                for (uintptr_t j = 0; j < patternLength; j++) {
                    found &= pattern[j] == *reinterpret_cast<char*>(base + i + j);
                    if (!found)
                        break;
                }
                if (found)
                    return base + i;
            }
            return 0;
        };

        auto findInMemoryPattern = [baseAddress, moduleSize](const char* pattern, const char* mask, uintptr_t offset = 0) {
            uintptr_t base = baseAddress;
            uintptr_t size = moduleSize;

            uintptr_t patternLength = static_cast<uintptr_t>(strlen(mask));

            for (uintptr_t i = 0; i < size - patternLength; i++) {
                bool found = true;
                for (uintptr_t j = 0; j < patternLength; j++) {
                    found &= mask[j] == '?' || pattern[j] == *reinterpret_cast<char*>(base + i + j);
                    if (!found)
                        break;
                }
                if (found)
                    return base + i + offset;
            }
            return static_cast<uintptr_t>(0x0u);
        };

        auto getRTTIName = [](uintptr_t vtable) -> const char* {
            class v1 {
                virtual void doStuff() {}
            };
            class v2 : public v1 {
                virtual void doStuff() {}
            };
            v2* v = (v2*) vtable;
            auto& typex = typeid(*v);
        #ifdef __GNUC__
            auto test = typex.name();
        #else
            auto test = typex.raw_name();
        #endif
            return test;
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
        UINT    			len = 0;
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
            //std::cout << "future_stringOffset" << std::hex << offs << "\n";
            return offs;
        });
    #else
        auto future_stringOffset = std::async([&]() {return findInMemory("tbb4malloc_bi", 13); });
    #endif

        //Second part of finding the allocator. Done here so the second memorySearch is done when we are done parsing the Nulars

        auto future_allocatorVtablePtr = std::async(std::launch::deferred, [&]() {
            uintptr_t stringOffset = future_stringOffset.get();
        #ifndef __linux__
            return (findInMemory(reinterpret_cast<char*>(&stringOffset), 4) - sizeof(uintptr_t));
        #else
            uintptr_t vtableStart = stringOffset - (0x09D20C70 - 0x09D20BE8);
            return vtableStart;
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
        auto future_poolFuncAlloc = std::async([&]() {return findInMemoryPattern("\x40\x53\x48\x83\xEC\x20\xFF\x41\x60\x48\x8B\x41\x08\x48\x8B\xD9\x48\x3B\xC1\x74\x0B\x48\x85\xC0\x74\x06\x48\x83\xC0\xE0\x75\x2B\x48\x8D\x41\x18\x48\x8B\x49\x20\x48\x3B\xC8\x74\x0E\x48\x85\xC9\x74\x09\x48\x8D\x41\xE0\x48\x85\xC0\x75\x10\x48\x8B\xCB\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x4C\x8B\x43\x08\x32\xC9\x45\x33\xD2\x4C\x3B\xC3\x74\x0B\x4D\x85\xC0\x74\x06\x49\x83\xC0\xE0\x75\x2A\x4C\x8B\x43\x20\x48\x8D\x43\x18\x4C\x3B\xC0", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); });
        auto future_poolFuncDealloc = std::async([&]() {return findInMemoryPattern("\x48\x85\xD2\x0F\x84\x00\x00\x00\x00\x53\x48\x83\xEC\x20\x48\x63\x41\x58\x48\x89\x7C\x24\x00\x48\x8B\xFA\x48\xFF\xC8\x48\x8B\xD9\x48\x23\xC2\x48\x2B\xF8\x83\x3F\x00\x74\x28\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x44\x8B\x07\x48\x8D\x0D\x00\x00\x00\x00\x48\x8B\xD7\x48\x8B\x7C\x24\x00\x48\x83\xC4\x20\x5B\xE9\x00\x00\x00\x00\x48\x8B\x47\x18\x48\x89\x02\x48\x83\x7F\x00\x00\x48\x89\x57\x18\x0F\x94\xC0\x48\x89\x7A\x08\xFF\x4F\x10\x41\x0F\x94\xC0\x84\xC0\x74\x46\x48\x8B\x4F\x28\x48\x8B\x47\x20\x48\x8D\x57\x20\x48\x89\x01\x48\x8B\x42\x08\x48\x8B\x0A", "xxxxx????xxxxxxxxxxxxx?xxxxxxxxxxxxxxxxxxxxxxx????x????xxxxxx????xxxxxxx?xxxxxx????xxxxxxxxxx??xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); });
        auto future_fileBanks = std::async([&]() {
            auto patternFindLoc = findInMemoryPattern("\x41\x55\x41\x56\x41\x57\x48\x83\xEC\x50\x48\x8B\xCA\x4C\x8B\xF2\xE8\x00\x00\x00\x00\x49\x8B\x16\x48\x85\xD2\x74\x1C\x48\x8B\x0D\x00\x00\x00\x00\x48\x8B\x01\xFF\x50\x18\x49\xC7\x06\x00\x00\x00\x00\x41\xC7\x46\x00\x00\x00\x00\x00\x4C\x8B\x2D\x00\x00\x00\x00\x45\x33\xFF\x4C\x89\x6C\x24\x00\x45\x39\x7D\x08\x0F\x8E\x00\x00\x00\x00\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x48\x89\x7C\x24\x00\x4C\x89\x64\x24\x00\x45\x33\xE4\x66\x90", "xxxxxxxxxxxxxxxxx????xxxxxxxxxxx????xxxxxxxxx????xxx?????xxx????xxxxxxx?xxxxxx????xxxx?xxxx?xxxx?xxxx?xxxx?xxxxx");
            auto offs =  *reinterpret_cast<uint32_t*>(patternFindLoc + 0x3C);
            return patternFindLoc + 0x40 + offs;
        });
    #else

    #ifdef __linux__
        //auto future_poolFuncAlloc = std::async([&]() {return findInMemoryPattern("", ""); });
        //auto future_poolFuncDealloc = std::async([&]() {return findInMemoryPattern("\x56\x53\x83\xec\x00\x8b\x44\x24\x00\x8b\x74\x24\x00\x85\xc0\x0f\x84\x00\x00\x00\x00\x8b\x18\x8b\x0b\x85\xc9\x0f\x85\x00\x00\x00\x00\x8b\x53\x00\x89\x10\x89\x43\x00\x89\x58\x00\x83\x6b\x00\x00\x0f\x94\xc0\x85\xd2\x0f\x84\x00\x00\x00\x00\x84\xc0\x74\x00\x8b\x43\x00\x8b\x53\x00\x89\x10\x8b\x53\x00\x89\x42\x00\xc7\x43\x00\x00\x00\x00\x00\x83\x6e\x00\x00\x8b\x56\x00\x8d\x43\x00\x89\x02\x89\x53\x00\x8d\x56\x00\x89\x53\x00\x83\x46\x00\x00\x89\x46", "xxxx?xxx?xxx?xxxx????xxxxxxxx????xx?xxxx?xx?xx??xxxxxxx????xxx?xx?xx?xxxx?xx?xx?????xx??xx?xx?xxxx?xx?xx?xx??xx"); });
    #else
        auto future_poolFuncAlloc = std::async([&]() {return findInMemoryPattern("\x56\x8B\xF1\xFF\x46\x38\x8B\x46\x04\x3B\xC6\x74\x09\x85\xC0\x74\x05\x83\xC0\xF0\x75\x26\x8B\x4E\x10\x8D\x46\x0C\x3B\xC8\x74\x0B\x85\xC9\x74\x07\x8D\x41\xF0\x85\xC0\x75\x11", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); });
        auto future_poolFuncDealloc = std::async([&]() {return findInMemoryPattern("\x8B\x44\x24\x04\x85\xC0\x74\x09\x89\x44\x24\x04\xE9", "xxxxxxxxxxxxx"); });
        auto future_fileBanks = std::async([&]()
        {
            auto patternFindLoc = findInMemoryPattern("\x83\xec\x00\x55\x57\x8b\x7c\x24\x00\x8b\xcf\xe8\x00\x00\x00\x00\x8b\x17\x85\xd2\x74\x00\x8b\x0d\x00\x00\x00\x00\x52\x8b\x01\xff\x50\x00\xc7\x07\x00\x00\x00\x00\xc7\x47\x00\x00\x00\x00\x00\xa1\x00\x00\x00\x00\x33\xed\x89\x44\x24\x00\x39\x68\x00\x0f\x8e\x00\x00\x00\x00\x53\x56\x8b\x00\x68\x00\x00\x00\x00\x8b\x1c\xa8\x89\x5c\x24\x00\xe8\x00\x00\x00\x00", "xx?xxxxx?xxx????xxxxx?xx????xxxxx?xx????xx?????x????xxxxx?xx?xx????xxxxx????xxxxxx?x????");
            return *reinterpret_cast<uintptr_t*>(patternFindLoc) + 0x30;
        });
    #endif

    #endif



        /*
        Unary Hashmap

        This is a hashmap using a key->bucket system, so an array of arrays keyed by a hash.
        We don't give a fuck about that though, we just want to iterate through all of the
        buckets and in turn each item in the bucket, because they are our operator entries.
        */
        for (auto& it : game_state->_scriptFunctions) {
            for (auto& entry : it) {
                unary_entry new_entry;
                new_entry.op = entry._operator;
                new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
                new_entry.name = entry._name.data();
                LOG(INFO) << "Found unary operator: "sv <<
                    new_entry.op->return_type.type_str() << " " <<
                    new_entry.name <<
                    "(" << new_entry.op->arg_type.type_str() << ")" <<
                    " @ "sv << new_entry.op->procedure_addr << "\n";
                _unary_operators[entry._name2].push_back(new_entry);
            }
        }

        /*
        Binary Hashmap
        */
        for (auto& it : game_state->_scriptOperators) {
            for (auto& entry : it) {
                binary_entry new_entry;
                new_entry.op = entry._operator;
                new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
                new_entry.name = entry._name.data();
                LOG(INFO) << "Found binary operator: "sv <<
                    new_entry.op->return_type.type_str() << " " <<
                    "(" << new_entry.op->arg1_type.type_str() << ")" <<
                    new_entry.name <<
                    "(" << new_entry.op->arg2_type.type_str() << ")" <<
                    " @ "sv << new_entry.op->procedure_addr << "\n";
                _binary_operators[entry._name2].push_back(new_entry);
            }
        }

        /*
        Nular Hashmap
        */
        for (auto& entry : game_state->_scriptNulars) {
            nular_entry new_entry;
            new_entry.op = entry._operator;
            new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
            new_entry.name = entry._name.data();
            LOG(INFO) << "Found nular operator: "sv << new_entry.op->return_type.type_str() << " "
                << new_entry.name << " @ "sv << new_entry.op->procedure_addr << "\n";
            _nular_operators[entry._name2].push_back(new_entry);
        }

        auto typeToEnum = [](const r_string& name) {     //I know this is ugly. Feel free to make it better
            if (name == "SCALAR"sv) return types::GameDataType::SCALAR;
            if (name == "BOOL"sv) return types::GameDataType::BOOL;
            if (name == "ARRAY"sv) return types::GameDataType::ARRAY;
            if (name == "STRING"sv) return types::GameDataType::STRING;
            if (name == "NOTHING"sv) return types::GameDataType::NOTHING;
            if (name == "ANY"sv) return types::GameDataType::ANY;
            if (name == "NAMESPACE"sv) return types::GameDataType::NAMESPACE;
            if (name == "NaN"sv) return types::GameDataType::NaN;
            if (name == "CODE"sv) return types::GameDataType::CODE;
            if (name == "OBJECT"sv) return types::GameDataType::OBJECT;
            if (name == "SIDE"sv) return types::GameDataType::SIDE;
            if (name == "GROUP"sv) return types::GameDataType::GROUP;
            if (name == "TEXT"sv) return types::GameDataType::TEXT;
            if (name == "SCRIPT"sv) return types::GameDataType::SCRIPT;
            if (name == "TARGET"sv) return types::GameDataType::TARGET;
            if (name == "CONFIG"sv) return types::GameDataType::CONFIG;
            if (name == "DISPLAY"sv) return types::GameDataType::DISPLAY;
            if (name == "CONTROL"sv) return types::GameDataType::CONTROL;
            if (name == "NetObject"sv) return types::GameDataType::NetObject;
            if (name == "SUBGROUP"sv) return types::GameDataType::SUBGROUP;
            if (name == "TEAM_MEMBER"sv) return types::GameDataType::TEAM_MEMBER;
            if (name == "TASK"sv) return types::GameDataType::TASK;
            if (name == "DIARY_RECORD"sv) return types::GameDataType::DIARY_RECORD;
            if (name == "LOCATION"sv) return types::GameDataType::LOCATION;
            return types::GameDataType::end;
        };

        //Game Types
        for (auto& entry : game_state->_scriptTypes) {
            if (!entry->_createFunction) continue; //Some types don't have create functions. Example: VECTOR.
        #if _WIN64 || __X86_64__
            auto instructionPointer = reinterpret_cast<uintptr_t>(entry->_createFunction) + 0xB;
            auto offset = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(entry->_createFunction) + 0x7);
            uintptr_t poolAlloc = /*reinterpret_cast<uintptr_t>*/(instructionPointer + offset);
        #else
        #ifdef __linux__
            uintptr_t poolAlloc = 1;
        #else
            auto p1 = reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(entry->_createFunction) + 0x3);
            uintptr_t poolAlloc = *reinterpret_cast<uintptr_t*>(p1);
        #endif
        #endif
            LOG(INFO) << entry->_localizedName << entry->_javaFunc << entry->_readableName << "\n";
            LOG(INFO) << "Found Type operator: "sv << entry->_name << " create@ "sv << std::hex << entry->_createFunction << " pool@ "sv << poolAlloc << "\n";
            //OutputDebugStringA(entry->_name.data());
            //OutputDebugStringA("\n");

            auto type = typeToEnum(entry->_name);
            if (poolAlloc && type != types::GameDataType::end) {
                _allocator._poolAllocs[static_cast<size_t>(type)] = reinterpret_cast<rv_pool_allocator*>(poolAlloc);
                _sqf_register_funcs._types[static_cast<size_t>(type)] = entry;
            }
        }


        //File Banks
#ifndef __linux__
        //_sqf_register_funcs._file_banks = future_fileBanks.get(); //Broken in 1.74
#endif

        _sqf_register_funcs._type_vtable = _binary_operators["arrayintersect"].front().op->arg1_type.get_vtable();
        //_sqf_register_funcs._types[static_cast<size_t>(types::GameDataType::ARRAY)] = reinterpret_cast<uintptr_t>(&_binary_operators["arrayintersect"].front().op->arg1_type);
        //_sqf_register_funcs._types[static_cast<size_t>(types::GameDataType::OBJECT)] = reinterpret_cast<uintptr_t>(&_binary_operators["doorphase"].front().op->arg1_type);
        //_sqf_register_funcs._types[static_cast<size_t>(types::GameDataType::STRING)] = reinterpret_cast<uintptr_t>(&_binary_operators["doorphase"].front().op->arg2_type);
        //_sqf_register_funcs._types[static_cast<size_t>(types::GameDataType::SCALAR)] = reinterpret_cast<uintptr_t>(&_binary_operators["doorphase"].front().op->return_type);
        //_sqf_register_funcs._types[static_cast<size_t>(types::GameDataType::BOOL)] = reinterpret_cast<uintptr_t>(&_unary_operators["isplayer"].front().op->return_type);
        //_sqf_register_funcs._types[static_cast<size_t>(types::GameDataType::ANY)] = reinterpret_cast<uintptr_t>(&_unary_operators["diag_log"].front().op->arg_type);

        //_sqf_register_funcs._operator_construct = future_operator_construct.get();
        //_sqf_register_funcs._operator_insert = future_operator_insert.get();
        //_sqf_register_funcs._unary_construct = future_unary_construct.get();
        //_sqf_register_funcs._unary_insert = future_unary_insert.get();
        _sqf_register_funcs._gameState = state_addr_;

        uintptr_t allocatorVtablePtr = future_allocatorVtablePtr.get();
    #ifdef __linux__
        const char* test = getRTTIName((uintptr_t) (&allocatorVtablePtr));
        assert(strcmp(test, "12MemFunctions") == 0);
    #else
        const char* test = getRTTIName(/**reinterpret_cast<uintptr_t*>(*/allocatorVtablePtr/*)*/);
        assert(strcmp(test, ".?AVMemTableFunctions@@") == 0);
    #endif
        _allocator.genericAllocBase = allocatorVtablePtr;
    #ifndef __linux__
        _allocator.poolFuncAlloc = future_poolFuncAlloc.get();
        _allocator.poolFuncDealloc = future_poolFuncDealloc.get();
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

}
