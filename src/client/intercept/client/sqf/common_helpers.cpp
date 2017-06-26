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

            std::vector<game_value> __convert_to_game_value_vector(game_value input_) {
                std::vector<game_value> output;
                output.reserve(input_.size());
                for (auto &gv : input_.to_array()) {
                    output.push_back(game_value(gv));
                }
                return output;
            }

            std::vector<vector3> __convert_to_vector3_vector(game_value input_) {
                std::vector<vector3> output;
                output.reserve(input_.size());
                for (auto &v3 : input_.to_array()) {
                    output.push_back(vector3(v3));
                }
                return output;
            }

            std::vector<vector2> __convert_to_vector2_vector(game_value input_) {
                std::vector<vector2> output;
                output.reserve(input_.size());
                for (auto &v2 : input_.to_array()) {
                    output.push_back(vector2(v2));
                }
                return output;
            }

            std::vector<object> __convert_to_objects_vector(game_value input_) {
                std::vector<object> output;
                output.reserve(input_.size());
                for (auto &ob : input_.to_array()) {
                    output.push_back(object(ob));
                }
                return output;
            }

            sqf_return_string_list __convert_to_strings_vector(game_value input_) {
                sqf_return_string_list output;
                if (input_.type() != game_data_array::type_def) return output;
                const auto& arr = input_.to_array();
#ifdef __GNUC__  //fails to find conversion to std::string
                output.reserve(input_.size());
                for (auto& it : arr)
                    output.push_back(it);
#else
                output.insert(output.end(), arr.begin(), arr.end());
#endif

                return output;
            }

            std::vector<float> __convert_to_numbers_vector(game_value input_) {
                std::vector<float> output;
                if (input_.type() != game_data_array::type_def) return output;
                const auto& arr = input_.to_array();
                output.insert(output.end(), arr.begin(), arr.end());
                return output;
            }

            std::vector<int> __convert_to_integers_vector(game_value input_) {
                std::vector<int> output;
                if (input_.type() != game_data_array::type_def) return output;
                const auto& arr = input_.to_array();
                output.insert(output.end(), arr.begin(), arr.end());
                return output;
            }

            std::vector<bool> __convert_to_booleans_vector(game_value input_) {
                std::vector<bool> output;
                if (input_.type() != game_data_array::type_def) return output;
                const auto& arr = input_.to_array();
                output.insert(output.end(), arr.begin(), arr.end());
                return output;
            }

            std::vector<script> __convert_to_scripts_vector(game_value input_) {
                std::vector<script> output;
                if (input_.type() != game_data_array::type_def) return output;
                const auto& arr = input_.to_array();
                output.insert(output.end(), arr.begin(), arr.end());
                return output;
            }

            std::vector<team_member> __convert_to_team_members_vector(game_value input_) {
                std::vector<team_member> output;
                if (input_.type() != game_data_array::type_def) return output;
                const auto& arr = input_.to_array();
                output.insert(output.end(), arr.begin(), arr.end());
                return output;
            }

            std::vector<group> __convert_to_groups_vector(game_value input_) {
                std::vector<group> output;
                if (input_.type() != game_data_array::type_def) return output;
                const auto& arr = input_.to_array();
                output.insert(output.end(), arr.begin(), arr.end());
                return output;
            }

            std::vector<control> __convert_to_controls_vector(game_value input_) {
                std::vector<control> output;
                output.reserve(input_.size());
                for (uint32_t i = 0; i < input_.size(); ++i) {
                    output.push_back(control(input_[i]));
                }
                return output;
            }

            std::vector<display> __convert_to_displays_vector(game_value input_) {
                std::vector<display> output;
                if (input_.type() != game_data_array::type_def) return output;
                const auto& arr = input_.to_array();
                output.insert(output.end(), arr.begin(), arr.end());
                return output;
            }

            std::vector<marker> __convert_to_markers_vector(game_value input_) {
                return __convert_to_strings_vector(input_);
                //std::vector<marker> output;
                //if (input_.type() != game_data_array::type_def) return output;
                //const auto& arr = input_.to_array();
                //output.insert(output.end(), arr.begin(), arr.end());
                //return output;
            }

            std::vector<config> __convert_to_configs_vector(game_value input_) {
                std::vector<config> output;
                if (input_.type() != game_data_array::type_def) return output;
                const auto& arr = input_.to_array();
                output.insert(output.end(), arr.begin(), arr.end());
                return output;
            }

            std::vector<location> __convert_to_locations_vector(game_value input_) {
                std::vector<location> output;
                if (input_.type() != game_data_array::type_def) return output;
                const auto& arr = input_.to_array();
                output.insert(output.end(), arr.begin(), arr.end());
                return output;
            }

            std::vector<task> __convert_to_tasks_vector(game_value input_) {
                std::vector<task> output;
                if (input_.type() != game_data_array::type_def) return output;
                const auto& arr = input_.to_array();
                output.insert(output.end(), arr.begin(), arr.end());
                return output;
            }

            vector3 __convert_to_vector3(game_value input_) {
                return vector3(input_[0], input_[1], input_[2]);
            }
        }  // namespace __helpers
    }      // namespace sqf
}  // namespace intercept
