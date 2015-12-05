#pragma once
#include "client\client.hpp"
#include "client\client_types.hpp"
#include "../vector.hpp"

using namespace intercept::client::types;
namespace intercept {
	namespace sqf {
		namespace __helpers {

			/* Nular function helpers */
            void __empty_nular(nular_function fnc_);
            std::string __retrieve_nular_string(nular_function fnc_);
			float __retrieve_nular_number(nular_function fnc_);
			vector3 __retrieve_nular_vector3(nular_function fnc_);
			bool __retrieve_nular_bool(nular_function fnc_);
            object __retrieve_nular_object(nular_function fnc_);

			/* Unary function helpers */
			/** Void return, standard input helpers **/
			void __empty_unary_obj(unary_function fnc_, object obj_);
			void __empty_unary_vector(unary_function fnc_, vector3 obj_);
			void __empty_unary_string(unary_function fnc_, std::string str_);
			void __empty_unary_number(unary_function fnc_, float val_);
			void __empty_unary_bool(unary_function fnc_, bool val_);

            std::vector<team_member>& _nular_team_members(nular_function fnc_);
            std::vector<std::string>& _nular_strings(nular_function fnc_);
            std::vector<object>& all_objects(nular_function fnc_);
            std::vector<group>& all_groups(nular_function fnc_);
            std::vector<display>& all_displays(nular_function fnc_);
            std::vector<marker>& all_map_markers(nular_function fnc_);            
		}
	}
}