#pragma once

#include "shared.hpp"
#include <optional>

namespace intercept::search {
    class plugin_searcher {
    public:
        plugin_searcher();
        //This is here because it's easier to crossplatform n stuff
        static std::string get_command_line();
        std::optional<std::wstring> find_extension(const std::wstring& name);
    private:
        static std::vector<std::wstring> generate_pbo_list();
        std::vector<std::wstring> active_mod_folder_list;
    };
}
