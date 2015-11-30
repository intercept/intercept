#pragma once
#include "shared.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"

namespace intercept {

    class module {
    public:
        module() : handle(nullptr), name("") {}
        module(const std::string & name_, HMODULE handle_, const std::string & file_) : handle(handle_), name(name_), temp_filename(file_) {}

        std::string name;
        std::string temp_filename;
        HMODULE     handle;
    };

    class extensions : public singleton<extensions> {
    public:

        extensions();
        ~extensions();

        void attach_controller();
        bool load(const arguments & args_, std::string & result);
        bool unload(const arguments & args_, std::string & result);
        bool call(const arguments & args_, std::string & result);
        bool list(const arguments & args_, std::string & result);
        
        
    protected:
        std::unordered_map<std::string, module> _modules;
    };
};
