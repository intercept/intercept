#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        namespace __helpers {

            void __empty_nular(nular_function fnc_) {
                host::functions.invoke_raw_nular(fnc_);
            }

            sqf_return_string __retrieve_nular_string(nular_function fnc_) {
                return host::functions.invoke_raw_nular(fnc_);
            }

            float __retrieve_nular_number(nular_function fnc_) {
                return host::functions.invoke_raw_nular(fnc_);
            }

            object __retrieve_nular_object(nular_function fnc_) {
                return object(host::functions.invoke_raw_nular(fnc_));
            }

            rv_text __retrieve_nular_text(nular_function fnc_) {
                return rv_text(host::functions.invoke_raw_nular(fnc_));
            }

            rv_namespace __retrieve_nular_namespace(nular_function fnc_) {
                return rv_namespace(host::functions.invoke_raw_nular(fnc_));
            }

            location __retrieve_nular_location(nular_function fnc_) {
                return location(host::functions.invoke_raw_nular(fnc_));
            }

            side __retrieve_nular_side(nular_function fnc_) {
                return side(host::functions.invoke_raw_nular(fnc_));
            }

            control __retrieve_nular_control(nular_function fnc_) {
                return control(host::functions.invoke_raw_nular(fnc_));
            }

            group __retrieve_nular_group(nular_function fnc_) {
                return group(host::functions.invoke_raw_nular(fnc_));
            }

            config __retrieve_nular_config(nular_function fnc_) {
                return config(host::functions.invoke_raw_nular(fnc_));
            }

            display __retrieve_nular_display(nular_function fnc_) {
                return display(host::functions.invoke_raw_nular(fnc_));
            }

            vector3 __retrieve_nular_vector3(nular_function fnc_) {
                return host::functions.invoke_raw_nular(fnc_);
            }

            bool __retrieve_nular_bool(nular_function fnc_) {
                return host::functions.invoke_raw_nular(fnc_);
            }

            void __empty_unary_object(unary_function fnc_, const object& obj_) {
                host::functions.invoke_raw_unary(fnc_, obj_);
            }

            void __empty_unary_vector(unary_function fnc_, const vector3& vec_) {
                host::functions.invoke_raw_unary(fnc_, vec_);
            }

            void __empty_unary_string(unary_function fnc_, sqf_string_const_ref str_) {
                host::functions.invoke_raw_unary(fnc_, str_);
            }

            void __empty_unary_number(unary_function fnc_, float val_) {
                host::functions.invoke_raw_unary(fnc_, val_);
            }

            void __empty_unary_bool(unary_function fnc_, bool val_) {
                host::functions.invoke_raw_unary(fnc_, val_);
            }

            void __empty_unary_control(unary_function fnc_, const control& ctrl_) {
                host::functions.invoke_raw_unary(fnc_, ctrl_);
            }

            bool __bool_unary_object(unary_function fnc_, const object& obj_) {
                return host::functions.invoke_raw_unary(fnc_, obj_);
            }

            bool __bool_unary_string(unary_function fnc_, sqf_string_const_ref str_) {
                return host::functions.invoke_raw_unary(fnc_, str_);
            }

            bool __bool_unary_number(unary_function fnc_, float val_) {
                return host::functions.invoke_raw_unary(fnc_, val_);
            }

            bool __bool_unary_control(unary_function fnc_, const control& ctl_) {
                return host::functions.invoke_raw_unary(fnc_, ctl_);
            }

            float __number_unary_number(unary_function fnc_, float val_) {
                return host::functions.invoke_raw_unary(fnc_, val_);
            }

            float __number_unary_control(unary_function fnc_, const control& ctl_) {
                return host::functions.invoke_raw_unary(fnc_, ctl_);
            }

            float __number_unary_string(unary_function fnc_, sqf_string_const_ref str_) {
                return host::functions.invoke_raw_unary(fnc_, str_);
            }

            float __number_unary_location(unary_function fnc_, const location& obj_) {
                return host::functions.invoke_raw_unary(fnc_, obj_);
            }

            float __number_unary_object(unary_function fnc_, const object& obj_) {
                return host::functions.invoke_raw_unary(fnc_, obj_);
            }

            sqf_return_string __string_unary_control(unary_function fnc_, const control& ctl_) {
                return host::functions.invoke_raw_unary(fnc_, ctl_);
            }

            sqf_return_string __string_unary_object(unary_function fnc_, const object& obj_) {
                return host::functions.invoke_raw_unary(fnc_, obj_);
            }

            sqf_return_string __string_unary_string(unary_function fnc_, sqf_string_const_ref str_) {
                return host::functions.invoke_raw_unary(fnc_, str_);
            }

            object __object_unary_object(unary_function fnc_, const object& obj_) {
                return object(host::functions.invoke_raw_unary(fnc_, obj_));
            }
        }  // namespace __helpers
    }      // namespace sqf
}  // namespace intercept
