#pragma once

#include "shared.hpp"
#include <optional>

namespace intercept::search {
    class plugin_searcher {
    public:
        plugin_searcher();
        //This is here because it's easier to crossplatform n stuff
        static std::string get_command_line();
        std::optional<std::string> find_extension(const std::string& name);
    private:
        static std::vector<std::string> generate_pbo_list();
        std::vector<std::string> active_mod_folder_list;
    };
}
