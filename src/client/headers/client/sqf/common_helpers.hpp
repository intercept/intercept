/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Common helper functions for SQF wrappers.

These are helpers that are used to do repetitive tasks in similar SQF wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "client/client.hpp"
#include "shared/client_types.hpp"
#include "shared/vector.hpp"

using namespace intercept::types;
namespace intercept {
    namespace sqf {
        namespace __helpers {

            /* Nular function helpers */
            void __empty_nular(nular_function fnc_);
            sqf_return_string __retrieve_nular_string(nular_function fnc_);
            float __retrieve_nular_number(nular_function fnc_);
            vector3 __retrieve_nular_vector3(nular_function fnc_);
            bool __retrieve_nular_bool(nular_function fnc_);
            object __retrieve_nular_object(nular_function fnc_);
            rv_text __retrieve_nular_text(nular_function fnc_);
            rv_namespace __retrieve_nular_namespace(nular_function fnc_);
            location __retrieve_nular_location(nular_function fnc_);
            side __retrieve_nular_side(nular_function fnc_);
            control __retrieve_nular_control(nular_function fnc_);
            group __retrieve_nular_group(nular_function fnc_);
            config __retrieve_nular_config(nular_function fnc_);
            display __retrieve_nular_display(nular_function fnc_);

            /* Unary function helpers */
            /** Void return, standard input helpers **/
            void __empty_unary_object(unary_function fnc_, const object &obj_);
            void __empty_unary_vector(unary_function fnc_, const vector3 &vec_);
            void __empty_unary_string(unary_function fnc_, sqf_string_const_ref str_);
            void __empty_unary_number(unary_function fnc_, float val_);
            void __empty_unary_bool(unary_function fnc_, bool val_);
            void __empty_unary_control(unary_function fnc_, const control &ctl_);

            /** Common return/input helpers **/
            bool __bool_unary_object(unary_function fnc_, const object &obj_);
            bool __bool_unary_string(unary_function fnc_, sqf_string_const_ref str_);
            bool __bool_unary_number(unary_function fnc_, float val_);
            bool __bool_unary_control(unary_function fnc_, const control &ctl_);

            float __number_unary_number(unary_function fnc_, float val_);
            float __number_unary_control(unary_function fnc_, const control &ctl_);
            float __number_unary_string(unary_function fnc_, sqf_string_const_ref str_);
            float __number_unary_location(unary_function fnc_, const location &str_);
            float __number_unary_object(unary_function fnc_, const object &obj_);

            sqf_return_string __string_unary_control(unary_function fnc_, const control &ctl_);
            sqf_return_string __string_unary_object(unary_function fnc_, const object &obj_);
            sqf_return_string __string_unary_string(unary_function fnc_, sqf_string_const_ref str_);

            object __object_unary_object(unary_function fnc_, const object &obj_);

            std::vector<game_value> __convert_to_game_value_vector(game_value input_);
            std::vector<vector3> __convert_to_vector3_vector(game_value input_);
            std::vector<vector2> __convert_to_vector2_vector(game_value input_);
            std::vector<object> __convert_to_objects_vector(game_value input_);
            sqf_return_string_list __convert_to_strings_vector(game_value input_);
            std::vector<float> __convert_to_numbers_vector(game_value input_);
            std::vector<int> __convert_to_integers_vector(game_value input_);
            std::vector<bool> __convert_to_booleans_vector(game_value input_);
            std::vector<script> __convert_to_scripts_vector(game_value input_);
            std::vector<team_member> __convert_to_team_members_vector(game_value input_);
            std::vector<group> __convert_to_groups_vector(game_value input__);
            std::vector<control> __convert_to_controls_vector(game_value input_);
            std::vector<display> __convert_to_displays_vector(game_value input_);
            std::vector<marker> __convert_to_markers_vector(game_value input_);
            std::vector<config> __convert_to_configs_vector(game_value input_);
            std::vector<location> __convert_to_locations_vector(game_value input_);
            std::vector<task> __convert_to_tasks_vector(game_value input_);
            vector3 __convert_to_vector3(game_value input_);
        }  // namespace __helpers
    }      // namespace sqf
}  // namespace intercept
