/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Wrappers for the 3den 3D editor functions.

These are wrappers for the 3den 3D editor that will be released in the next major
Arma 3 release.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\types.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
		std::string current3denoperation();
		object get3dencamera();
		bool get3deniconsvisible();
		bool get3denlinesvisible();
		// TODO array[] get_3den_mouse_over(); //      Array in format: [type,Eden Entity], where type can be: "Object", "Group", "Trigger", "Logic", "Waypoint" or "Marker"
		bool is3den();
		bool is3denmultiplayer();
		float get_3den_action_state(const std::string &value_);
		void edit_3den_mission_attributes(const std::string &value_);
		float add_3den_layer(float value0_, const std::string& value1_);
		bool remove_3den_layer(float value_);
		void remove_all_3den_eventhandlers(const std::string &value_);
    }
}
