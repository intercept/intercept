#pragma once

#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <memory>
#include <cmath>
#include <cstdint>
#include <streambuf>
#include "logging.hpp"

#ifdef _DEBUG
#define ZERO_OUTPUT()    { memset(output, 0x00, outputSize); }
#define EXTENSION_RETURN() {output[outputSize-1] = 0x00; } return;
#else
#define ZERO_OUTPUT()
#define EXTENSION_RETURN() return;
#endif

#ifdef _WIN32
#define sleep(x) Sleep(x)
#endif

namespace intercept {

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string_view> &split(std::string_view s, char delim, std::vector<std::string_view> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
    std::vector<std::string_view> split(std::string_view s, char delim);
    // trim from start
    static std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const char _char) noexcept {return !std::isspace(_char); }));
        return s;
    }

    // trim from end
    static std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](const char _char) noexcept {return !std::isspace(_char); }).base(), s.end());
        return s;
    }

    // trim from both ends
    static std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
    }

    inline void runtime_assert(bool result);

    struct exception {
        exception(const uint32_t code_, const std::string & text_) : code(code_), text(text_) {}
        
        exception & operator= (const exception& other) { code = other.code; text = other.text;  return *this; }
        bool operator == (const exception &r) const noexcept { return code == r.code; }

        uint32_t        code;
        std::string     text;
    };
}

#ifdef _DEBUG
#define INTERCEPT_ASSERT assert()
#else
#define INTERCEPT_ASSERT intercept::runtime_assert()
#endif

#ifdef __clang__
#pragma message "clang is unsupported for usage with Arma"
#endif
