#pragma once
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;
namespace intercept {
	namespace sqf {
		namespace __helpers {
            void __empty_nular(nular_function fnc_);
            std::string __retrieve_nular_string(nular_function fnc_);
			float __retrieve_nular_number(nular_function fnc_);
			vector3 __retrieve_nular_vector3(nular_function fnc_);
			bool __retrieve_nular_bool(nular_function fnc_);
            object __retrieve_nular_object(nular_function fnc_);

            std::vector<team_member>& _nular_team_members(nular_function fnc_);
            std::vector<std::string>& _nular_strings(nular_function fnc_);
            std::vector<object>& all_objects(nular_function fnc_);
            std::vector<group>& all_groups(nular_function fnc_);
            std::vector<display>& all_displays(nular_function fnc_);
            std::vector<marker>& all_map_markers(nular_function fnc_);            
		}
	}
}