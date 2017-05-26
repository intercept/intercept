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
        float diag_fps();
        float diag_fpsmin();
        float diag_frameno();
        float diag_ticktime();

        std::vector<script> diag_active_mission_fsms();
        std::vector<script> diag_active_sqf_scripts();
        std::vector<script> diag_active_sqs_scripts();



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
        void set_dynamic_simulation_distance(const std::string& category_, float distance_);
        //#TODO add BIKI entry and implement 
        //void set_dynamic_simulation_distance_coef(const std::string&, float); //binary__setdynamicsimulationdistancecoef__string__scalar__ret__nothing 
        void enable_dynamic_simulation(const object &object_, bool enable_);
        void enable_dynamic_simulation(const group &group_, bool enable_);
        void diag_dynamic_simulation_end(const std::string &type_);
        float dynamic_simulation_distance(const std::string &category_);
        float dynamic_simulation_distance_coef(const std::string &class_);
        bool dynamic_simulation_enabled(const object &object_);
        bool dynamic_simulation_enabled(const group &group_);
        void enable_dynamic_simulation_system(bool enable_);
        bool dynamic_simulation_system_enabled();
    }
}
