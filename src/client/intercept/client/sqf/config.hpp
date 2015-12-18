#pragma once
/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Chat function wrappers.

These are wrappers for the `sideChat`, `globalChat`, `commandChat`, etc SQF commands.

https://github.com/NouberNou/intercept
*/
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        namespace configs {
            std::vector<config> config_hierarchy(const config &config_entry_);
            std::string config_name(const config &config_entry_);
            std::vector<config> config_properties(const config &config_entry,const std::string& condition_, bool inherit);
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
            std::vector<std::string> config_classes(const std::string& value_, config a_config_);
            void load_overlay(const control &a_control_, config a_config_);
            void new_overlay(const control &a_control_, config a_config_);
            config select(const config &a_config_, float a_number_);
            config campaign_config_file();
            config config_file();
            config config_null();
            config mission_config_file();
        }
    }
}
