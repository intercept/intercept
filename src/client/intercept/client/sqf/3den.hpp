#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
		namespace eden {
			std::string current3denoperation();
			object get3dencamera();
			bool get3deniconsvisible();
			bool get3denlinesvisible();
			// TODO array[] get_3den_mouse_over(); //      Array in format: [type,Eden Entity], where type can be: "Object", "Group", "Trigger", "Logic", "Waypoint" or "Marker"
			bool is3den();
			bool is3denmultiplayer();
			float get_3den_action_state(std::string value_);
			void edit_3den_mission_attributes(std::string value_);
			float add_3den_layer(float value0_, const std::string& value1_);
			bool remove_3den_layer(float value_);
			void remove_all_3den_eventhandlers(std::string value_);
		}
    }
}
