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
            config_entry(config_entry &&move_) noexcept;
            config_entry & operator=(const config_entry &copy_);
            config_entry & operator=(config_entry &&move_) noexcept;
            config_entry operator>>(sqf_string_const_ref entry_);

            operator config &();
        protected:
            types::config _config_entry;
            bool _initialized;
        };

        std::vector<config> config_hierarchy(const config &config_entry_);
        sqf_return_string config_name(const config &config_entry_);
        std::vector<config> config_properties(const config &config_entry, sqf_string_const_ref condition_ = "true", bool inherit = true);
        sqf_return_string config_source_mod(const config &config_entry_);
        sqf_return_string_list config_source_mod_list(const config &config_entry_);
        float count(const config &config_entry_);
        //std::vector<game_value> get_array(const config &config_entry_);
        config get_mission_config(sqf_string_const_ref value_);
        float get_number(const config &config_entry_);
        sqf_return_string get_text(const config &config_entry_);
        config inherits_from(const config &config_entry_);
        bool is_array(const config &config_entry_);
        bool is_class(const config &config_entry_);
        bool is_null(const config &config_entry_);
        bool is_number(const config &config_entry_);
        bool is_text(const config &config_entry_);
        std::vector<config> config_classes(sqf_string_const_ref condition_, const config &config_);
        config select(const config &a_config_, float a_number_);
        config campaign_config_file();
        config config_file();
        config config_null();
        config mission_config_file();
        game_value get_array(const config config_);

        game_value get_mission_config_value(sqf_string_const_ref attribute_);
        game_value get_mission_config_value(sqf_string_const_ref attribute_, game_value default_value_);

        //config
        bool is_kind_of(const object &obj_, sqf_string_const_ref type_);
        bool is_kind_of(sqf_string_const_ref type1_, sqf_string_const_ref type2_);
        bool is_kind_of(sqf_string_const_ref type1_, sqf_string_const_ref type2_, const config &target_config_);

        sqf_return_string_list config_source_addon_list(const config &config_);
        game_value mod_params(sqf_string_const_ref mod_class_, sqf_string_list_const_ref options_);
        sqf_return_string type_of(const object &value_);
    }
}
