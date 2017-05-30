/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Misc function wrappers.

This is basically stuff that has not been categorized yet. Compared to uncategorized.hpp,
which is functions that lack a clear category.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client/client.hpp"
#include "shared/client_types.hpp"
#include<vector>

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        struct rv_artillery_computer_settings {
            std::string name;
            std::string ammo;
            int mode; // TODO investigate what this actually is

            rv_artillery_computer_settings(const game_value &rv_game_value_)
                : name(rv_game_value_[0]),
                ammo(rv_game_value_[1]),
                mode(rv_game_value_[2]) {}
        };
        struct rv_credit {
            std::string library_name;
            std::string credits;

            rv_credit(const game_value &rv_game_value_)
                : library_name(rv_game_value_[0]),
                credits(rv_game_value_[1]) {}
        };
        struct rv_product_version {
            std::string name;
            std::string name_short;
            float version;
            float build;
            std::string branch;
            bool mods;
            std::string platform;

            rv_product_version(const game_value &rv_game_value_)
                : name(rv_game_value_[0]),
                name_short(rv_game_value_[1]),
                version(rv_game_value_[2]),
                build(rv_game_value_[3]),
                branch(rv_game_value_[4]),
                mods(rv_game_value_[5]),
                platform(rv_game_value_[6]) {}
        };
        //simulation
        //NULAR -- https://github.com/intercept/intercept/issues/13
        bool can_trigger_dynamic_simulation(const object &unit_);
        void enable_simulation(const object &value0_, bool value1_);
        void enable_simulation_global(const object &value0_, bool value1_);
        bool simulation_enabled(const object &value_);
        void trigger_dynamic_simulation(const object &object_, bool trigger_);
        /**
        * \brief
        * \param category_ - one of:

        "Group" - Infantry units. Set to a reasonable distance, player should not see disabled infantry units. Default: 500m
        "Vehicle" - Vehicles with crew. Set to a reasonable distance, player should not see disabled vehicles. Default: 350m
        "EmptyVehicle" - All vehicles without crew. Separated from Props as Empty Vehicles have often more complex damage states and selective destruction. Their activation distance should by larger that the one used for Props. Default: 250m
        "Prop" - Static objects. Anything from a small tin can to a building. Default: 50m

        * \param distance_
        */
        void set_dynamic_simulation_distance(sqf_string_const_ref category_, float distance_);
        //#TODO add BIKI entry and implement 
        //void set_dynamic_simulation_distance_coef(sqf_string_const_ref , float); //binary__setdynamicsimulationdistancecoef__string__scalar__ret__nothing 
        void enable_dynamic_simulation(const object &object_, bool enable_);
        void enable_dynamic_simulation(const group &group_, bool enable_);
        void diag_dynamic_simulation_end(sqf_string_const_ref type_);
        float dynamic_simulation_distance(sqf_string_const_ref category_);
        float dynamic_simulation_distance_coef(sqf_string_const_ref class_);
        bool dynamic_simulation_enabled(const object &object_);
        bool dynamic_simulation_enabled(const group &group_);
        void enable_dynamic_simulation_system(bool enable_);
        bool dynamic_simulation_system_enabled();








        //TOH traffic - needs to be tested, probably not working
        void set_traffic_density(float density_, float x_min_, float x_max_, float z_min_, float z_max_);
        void set_traffic_gap(float gap_, float x_min_, float x_max_, float z_min_, float z_max_);
        void set_traffic_speed(float speed_, float x_min_, float x_max_, float z_min_, float z_max_);
        void enable_traffic(bool value_);
        void set_traffic_distance(float value_);

        //A2 artillary - did this ever work?
        bool in_range_of_artillery(const vector3 &position_, const std::vector<object> &units_, sqf_string_const_ref magazine_type_);
        float get_artillery_eta(const object &unit_, const vector3 &target_position_, sqf_string_const_ref magazine_type_);
        void enable_engine_artillery(bool value_);
        rv_artillery_computer_settings get_artillery_computer_settings();

        sqf_return_string language();
        std::vector<rv_credit> library_credits();
        sqf_return_string_list library_disclaimers();
        rv_product_version product_version();
    }
}
