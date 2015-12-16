#pragma once
#include "shared.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"
#include "shared\functions.hpp"

namespace intercept {
    namespace module {
        typedef int(__cdecl *api_version_func)();
        typedef void(__cdecl *assign_functions_func)(const struct intercept::client_functions funcs);
        typedef void(__cdecl *pre_init_func)();
        typedef void(__cdecl *post_init_func)();
        typedef void(__cdecl *mission_end_func)();
        typedef void(__cdecl *on_frame_func)();

        struct functions {
            api_version_func api_version;
            assign_functions_func assign_functions;
            pre_init_func pre_init;
            post_init_func post_init;
            mission_end_func mission_end;
            on_frame_func on_frame;
        };

        class entry {
        public:
            entry() : handle(nullptr), name("") {}
            entry(const std::string & name_, HMODULE handle_) : handle(handle_), name(name_) {}

            std::string name;
            functions functions;
            HMODULE     handle;
        };
    }
    



    class extensions : public singleton<extensions> {
    public:

        extensions();
        ~extensions();

        void attach_controller();
        bool load(const arguments & args_, std::string & result);
        bool unload(const arguments & args_, std::string & result);
        bool call(const arguments & args_, std::string & result);
        bool list(const arguments & args_, std::string & result);
        
        const std::unordered_map<std::string, module::entry>& modules();
        client_functions functions;
    protected:
        std::unordered_map<std::string, module::entry> _modules;
        
    };
};
