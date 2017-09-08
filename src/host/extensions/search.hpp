#pragma once

#include "shared.hpp"
#include <optional>

namespace intercept::search {
    class plugin_searcher {
    public:
        plugin_searcher();
        //This is here because it's easier to crossplatform n stuff
        static std::string get_command_line();
    #ifdef __linux__
        std::optional<std::string> find_extension(const std::string& name);
    #else 
        std::optional<std::wstring> find_extension(const std::wstring& name);
    #endif
        
        
    private:
    #ifdef __linux__
        static std::vector<std::string> generate_pbo_list();
        std::vector<std::string> active_mod_folder_list;
    #else 
        static std::vector<std::wstring> generate_pbo_list();
        std::vector<std::wstring> active_mod_folder_list;
    #endif
    };
}
