#pragma once

#include "shared.hpp"

namespace intercept::search {
    class plugin_searcher {
    public:
        plugin_searcher();
        //This is here because it's easier to crossplatform n stuff
        static std::string getCommandLine();
    private:
    #if !__linux__
        static std::vector<std::string> generate_pbo_list();
    #endif
        std::vector<std::string> active_mod_folder_list;
    };
}