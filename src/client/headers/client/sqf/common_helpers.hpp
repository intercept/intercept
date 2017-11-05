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


            template <class T>
            typename std::enable_if<std::is_convertible<game_value, T>::value, std::vector<T>>::type
            __convert_to_vector(game_value input_) {
                if (input_.size() == 0) return {};
                auto& arr = input_.to_array();
                return std::vector<T>(arr.begin(), arr.end());
            }


            template <class T>
            typename std::enable_if<!std::is_convertible<game_value, T>::value, std::vector<T>>::type
            __convert_to_vector(game_value input_) {
                std::vector<T> output;
                if (input_.size() == 0) return {};
                output.reserve(input_.size());
                for (auto &gv : input_.to_array()) {
                    output.emplace_back(T(gv));
                }
                return output;
            }

        }  // namespace __helpers
    }      // namespace sqf
}  // namespace intercept
