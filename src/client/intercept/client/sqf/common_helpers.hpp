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
            text __retrieve_nular_text(nular_function fnc_);
            rv_namespace __retrieve_nular_namespace(nular_function fnc_);
            location __retrieve_nular_location(nular_function fnc_);
            side __retrieve_nular_side(nular_function fnc_);
            control __retrieve_nular_control(nular_function fnc_);
            group __retrieve_nular_group(nular_function fnc_);
            config __retrieve_nular_config(nular_function fnc_);
            display __retrieve_nular_display(nular_function fnc_);

			std::vector<team_member> _nular_team_members(nular_function fnc_);
			std::vector<std::string> _nular_strings(nular_function fnc_);
			std::vector<object> all_objects(nular_function fnc_);
			std::vector<group> all_groups(nular_function fnc_);
			std::vector<display> all_displays(nular_function fnc_);
			std::vector<marker> all_map_markers(nular_function fnc_);

			/* Unary function helpers */
			/** Void return, standard input helpers **/
			void __empty_unary_object(unary_function fnc_, object obj_);
			void __empty_unary_vector(unary_function fnc_, vector3 vec_);
			void __empty_unary_string(unary_function fnc_, std::string str_);
			void __empty_unary_number(unary_function fnc_, float val_);
			void __empty_unary_bool(unary_function fnc_, bool val_);
			void __empty_unary_control(unary_function fnc_, control ctl_);

			/** Common return/input helpers **/
			bool __bool_unary_object(unary_function fnc_, object obj_);
			bool __bool_unary_string(unary_function fnc_, std::string str_);
			bool __bool_unary_number(unary_function fnc_, float val_);
			bool __bool_unary_control(unary_function fnc_, control ctl_);

			float __number_unary_number(unary_function fnc_, float val_);
			float __number_unary_control(unary_function fnc_, control ctl_);
			float __number_unary_string(unary_function fnc_, std::string str_);
			float __number_unary_object(unary_function fnc_, object obj_);

			std::string __string_unary_control(unary_function fnc_, control ctl_);
			std::string __string_unary_object(unary_function fnc_, object obj_);
			std::string __string_unary_string(unary_function fnc_, std::string str_);

			object __object_unary_object(unary_function fnc_, object obj_);
		}
	}
}