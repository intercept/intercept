#pragma once


    class MemorySection {
public:
#if _WIN32 || _WIN64
    explicit MemorySection(const MODULEINFO& modInfo) noexcept : start(reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll)),
                                                                 end(static_cast<uintptr_t>(modInfo.SizeOfImage) + reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll)) {}
#endif  // _WIN32 || _WIN64
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
        MODULEINFO modInfo = {nullptr};
        HMODULE hModule = GetModuleHandleA(nullptr);
        GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
        const uintptr_t baseAddress = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
        const uintptr_t moduleSize = static_cast<uintptr_t>(modInfo.SizeOfImage);
        sections.push_back(MemorySection(modInfo));
    }
#endif  // _WIN32 || _WIN64
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
#endif  // defined(__linux__)
    explicit MemorySections(uintptr_t _start, uintptr_t _size) : sections({MemorySection(_start, _start + _size)}) {}
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

    bool IsInAnySection(uintptr_t address) const {
        for (const auto& section : sections) {
            if (section.start < address && address < section.end)
                return true;
        }
        return false;
    }
};
