#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        std::vector<object>& all_3den_entities();
        std::vector<object>& all_curators();
        std::vector<object>& all_dead();
        std::vector<object>& all_deadmen();
        std::vector<display>& all_displays();
        std::vector<group>& all_groups();
        std::vector<marker>& all_map_markers();
        std::vector<object>& all_mines();
        std::vector<object>& all_players();
        // std::vector<site>& all_sites(); // This command is depecrated and no longer supported https://community.bistudio.com/wiki/allSites
        std::vector<object>& all_units();
        std::vector<object>& all_units_uav();
        
        object player();
        object create_vehicle(std::string type_, vector3 pos_);
        object create_vehicle(std::string type_, vector3 pos_, std::vector<marker> markers_, float placement_, std::string special_);
        void delete_vehicle(object obj_);
    }
}
