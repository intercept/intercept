#pragma once

#include "shared.hpp"

#include <vector>
#include <string>

namespace intercept {
    class argument_accessor {
    public:
        argument_accessor(const uint32_t index, const std::vector<std::string> & ar) noexcept : _index(index), _args(ar) { }

        const std::string & as_string() const { return _args[_index]; }
        operator const std::string &() const { return as_string(); }

        static float to_float(const std::string & val) { float res = 0.0f; std::istringstream iss(val); iss >> res; return res; }
        float as_float() const { return to_float(_args[_index]); }
        operator float() const { return as_float(); }

        int as_int() const { return atoi(_args[_index].c_str()); }
        operator int() const { return as_int(); }

        int as_uint32() const { return static_cast<uint32_t>(atoi(_args[_index].c_str())); }
        operator uint32_t() const { return as_uint32(); }

    protected:
        const uint32_t                      _index;
        const std::vector<std::string> &    _args;
    };

    class arguments {
    public:
        arguments(const std::string & str) : _original(str), _internal_index(0) {
            _args = intercept::split(str, ',');
            for (uint32_t i = 0; i < _args.size(); i++) {
                _args[i] = trim(_args[i]);
            }
        }
        //#TODO string_view implementation
        //arguments(std::string_view str) : _original(std::string(str)), _internal_index(0) {
        //    _args = intercept::split(str, ',');
        //    for (uint32_t i = 0; i < _args.size(); i++) {
        //        _args[i] = trim(_args[i]);
        //    }
        //}

        size_t size() const noexcept { return _args.size(); }

        const argument_accessor operator[] (int index) const noexcept { return argument_accessor(index, _args); }
        //argument_accessor operator[] (int index) const { return argument_accessor(index, _args); }


        static float to_float(const std::string & val) { float res = 0.0f; std::istringstream iss(val); iss >> res; return res; }

        const std::string & as_string() { return _args[_internal_index++]; }
        float as_float() { return to_float(_args[_internal_index++]); }
        int as_int() { return atoi(_args[_internal_index++].c_str()); }
        int as_uint32() { return static_cast<uint32_t>(atoi(_args[_internal_index++].c_str())); }

        const std::string & as_string(uint32_t _index) const { return _args[_index]; }
        float as_float(uint32_t _index) const { return to_float(_args[_index]); }
        int as_int(uint32_t _index) const { return atoi(_args[_index].c_str()); }
        int as_uint32(uint32_t _index) const { return static_cast<uint32_t>(atoi(_args[_index].c_str())); }


        const std::string & get() const noexcept {
            return _original;
        }

        std::string create(const std::string & command) const {
            std::stringstream ss;
            ss << command << ":";

            for (auto & v : _args) {
                ss << v << ",";
            }

            // Remove the trailing ,
            std::string result = ss.str();
            result.erase(result.length());

            return result;
        }
        static std::string create(const std::string & command, const arguments & args) {
            return args.create(command);
        }
        

    protected:
        std::vector<std::string> _args;
        const std::string        _original;
        uint32_t                 _internal_index;
    };
}
