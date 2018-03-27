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
            config_entry &operator=(const config_entry &copy_) = default;
            config_entry &operator=(config_entry &&move_) noexcept;
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
        int count(const config &config_entry_);
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
        config select(const config &a_config_, int a_number_);
        config campaign_config_file();
        config config_file();
        config config_null();
        config mission_config_file();
        game_value get_array(config config_);

        game_value get_mission_config_value(sqf_string_const_ref attribute_);
        game_value get_mission_config_value(sqf_string_const_ref attribute_, game_value default_value_);

        //config
        bool is_kind_of(const object &obj_, sqf_string_const_ref type_);
        bool is_kind_of(sqf_string_const_ref type1_, sqf_string_const_ref type2_);
        bool is_kind_of(sqf_string_const_ref type1_, sqf_string_const_ref type2_, const config &target_config_);

        sqf_return_string_list config_source_addon_list(const config &config_);
        enum class mod_params_options : uint32_t {
            name = 1,          //String - name to be shown(Arma 3 instead of A3, etc.)
            picture = 2,       //String - picture shown in Mod Launcher
            logo = 4,          //String - logo to be shown in Main Menu
            logoOver = 8,      //String - logo to be shown in Main Menu when mouse is over
            logoSmall = 0x10,     //String - small version of logo, prepared for drawing small icons
            tooltip = 0x20,       //String - tooltip to be shown on mouse over
            tooltipOwned = 0x40,  //String - tooltip to be shown on mouse over the icon when DLC is owned by player
            action = 0x80,        //String - url to be triggered when mod button is clicked
            actionName = 0x100,    //String - what to put on Action Button
            overview = 0x200,      //String - overview text visible in expansion menu
            hidePicture = 0x400,   //Boolean - do not show mod picture icon in the main menu mod list
            hideName = 0x800,      //Boolean - do not show mod name in the main menu mod list
            defaultMod = 0x1000,    //Boolean - default mods cannot be moved or disabled by Mod Launcher
            serverOnly = 0x2000,    //Boolean - mod doesn't have to be installed on client in order to play on server with this mod running
            active = 0x4000        //Boolean - active mod(activated through command line or stored in profile by mod launcher)
        };

        inline constexpr mod_params_options operator|(mod_params_options _Left, mod_params_options _Right) {
            return (static_cast<mod_params_options>(static_cast<unsigned int>(_Left)
                                                    | static_cast<unsigned int>(_Right)));
        }
        inline constexpr bool operator&(mod_params_options _Left, mod_params_options _Right) {
            return (static_cast<unsigned int>(_Left)
                    & static_cast<unsigned int>(_Right));
        }
        std::vector<game_value> mod_params(sqf_string_const_ref mod_class_, mod_params_options options_);
        sqf_return_string type_of(const object &value_);
    }  // namespace sqf
}  // namespace intercept
