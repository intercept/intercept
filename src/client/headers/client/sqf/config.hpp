#pragma once
/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Functions used to access and parse RV Engine configuration files.

These are functions that are used to access the config class structure in the RV
Engine.

https://github.com/NouberNou/intercept
*/
#include "shared.hpp"
#include "client/client.hpp"
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        class config_entry {
        public:
            config_entry();
            config_entry(types::config entry_);
            config_entry(config_entry const &copy_);
            config_entry(config_entry &&move_);
            config_entry & operator=(const config_entry &copy_);
            config_entry & operator=(config_entry &&move_);
            config_entry operator>>(const std::string &entry_);

            operator config &();
        protected:
            types::config _config_entry;
            bool _initialized;
        };

        std::vector<config> config_hierarchy(const config &config_entry_);
        std::string config_name(const config &config_entry_);
        std::vector<config> config_properties(const config &config_entry, const std::string& condition_ = "true", bool inherit = true);
        std::string config_source_mod(const config &config_entry_);
        std::vector<std::string> config_source_mod_list(const config &config_entry_);
        float count(const config &config_entry_);
        //std::vector<game_value> get_array(const config &config_entry_);
        config get_mission_config(const std::string& value_);
        float get_number(const config &config_entry_);
        std::string get_text(const config &config_entry_);
        config inherits_from(const config &config_entry_);
        bool is_array(const config &config_entry_);
        bool is_class(const config &config_entry_);
        bool is_null(const config &config_entry_);
        bool is_number(const config &config_entry_);
        bool is_text(const config &config_entry_);
        std::vector<std::string> config_classes(const std::string& value_, const config & a_config_);
        config select(const config &a_config_, float a_number_);
        config campaign_config_file();
        config config_file();
        config config_null();
        config mission_config_file();




    }
}
