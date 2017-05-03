#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        namespace __helpers {

            void __empty_nular(nular_function fnc_) {
                host::functions.invoke_raw_nular(fnc_);
            }

            std::string __retrieve_nular_string(nular_function fnc_) {
                return game_value(host::functions.invoke_raw_nular(fnc_));
            }

            float __retrieve_nular_number(nular_function fnc_) {
                return game_value(host::functions.invoke_raw_nular(fnc_));
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
                return game_value(host::functions.invoke_raw_nular(fnc_));
            }

            bool __retrieve_nular_bool(nular_function fnc_) {
                return game_value(host::functions.invoke_raw_nular(fnc_));
            }

            void __empty_unary_object(unary_function fnc_, const object &obj_) {
                host::functions.invoke_raw_unary(fnc_, obj_);
            }

            void __empty_unary_vector(unary_function fnc_, const vector3 &vec_) {
                host::functions.invoke_raw_unary(fnc_, vec_);
            }

            void __empty_unary_string(unary_function fnc_, const std::string &str_) {
                host::functions.invoke_raw_unary(fnc_, str_);
            }

            void __empty_unary_number(unary_function fnc_, float val_) {
                host::functions.invoke_raw_unary(fnc_, val_);
            }

            void __empty_unary_bool(unary_function fnc_, bool val_) {
                host::functions.invoke_raw_unary(fnc_, val_);
            }

            void __empty_unary_control(unary_function fnc_, const control &ctrl_) {
                host::functions.invoke_raw_unary(fnc_, ctrl_);
            }

            bool __bool_unary_object(unary_function fnc_, const object &obj_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, obj_));
            }

            bool __bool_unary_string(unary_function fnc_, const std::string &str_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, str_));
            }

            bool __bool_unary_number(unary_function fnc_, float val_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, val_));
            }

            bool __bool_unary_control(unary_function fnc_, const control &ctl_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, ctl_));
            }

            float __number_unary_number(unary_function fnc_, float val_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, val_));
            }

            float __number_unary_control(unary_function fnc_, const control &ctl_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, ctl_));
            }

            float __number_unary_string(unary_function fnc_, const std::string &str_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, str_));
            }

            float __number_unary_location(unary_function fnc_, const location &obj_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, obj_));
            }

            float __number_unary_object(unary_function fnc_, const object &obj_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, obj_));
            }

            std::string __string_unary_control(unary_function fnc_, const control &ctl_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, ctl_));
            }

            std::string __string_unary_object(unary_function fnc_, const object &obj_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, obj_));
            }

            std::string __string_unary_string(unary_function fnc_, const std::string &str_) {
                return game_value(host::functions.invoke_raw_unary(fnc_, str_));
            }

            object __object_unary_object(unary_function fnc_, const object &obj_) {
                return object(host::functions.invoke_raw_unary(fnc_, obj_));
            }


            std::vector<object> __convert_to_objects_vector(game_value input_) {
                std::vector<object> output;
                for (uint32_t i = 0; i < input_.length(); ++i) {
                    output.push_back(object(input_[i]));
                }
                return output;
            }

            std::vector<std::string> __convert_to_strings_vector(game_value input_) {
                std::vector<std::string> output;
                for (uint32_t i = 0; i < input_.length(); ++i) {
                    output.push_back(input_[i]);
                }
                return output;
            }

            std::vector<float> __convert_to_numbers_vector(game_value input__) {
                std::vector<float> output;
                for (uint32_t i = 0; i < input__.length(); ++i) {
                    output.push_back(input__[i]);
                }

                return output;
            }

            std::vector<int> __convert_to_integers_vector(game_value input__) {
                std::vector<int> output;
                for (uint32_t i = 0; i < input__.length(); ++i) {
                    output.push_back(input__[i]);
                }

                return output;
            }

            std::vector<bool> __convert_to_booleans_vector(game_value input__) {
                std::vector<bool> output;
                for (uint32_t i = 0; i < input__.length(); ++i) {
                    output.push_back(input__[i]);
                }

                return output;
            }

            std::vector<team_member> __convert_to_team_members_vector(game_value input__) {
                std::vector<team_member> output;
                for (uint32_t i = 0; i < input__.length(); ++i) {
                    output.push_back(team_member(input__[i]));
                }
                return output;
            }

            std::vector<group> __convert_to_groups_vector(game_value input_) {
                std::vector<group> output;
                for (uint32_t i = 0; i < input_.length(); ++i) {
                    output.push_back(group(input_[i]));
                }
                return output;
            }

            std::vector<display> __convert_to_displays_vector(game_value input_) {
                std::vector<display> output;
                for (uint32_t i = 0; i < input_.length(); ++i) {
                    output.push_back(display(input_[i]));
                }
                return output;
            }

            std::vector<marker> __convert_to_markers_vector(game_value input_) {
                std::vector<marker> output;
                for (uint32_t i = 0; i < input_.length(); ++i) {
                    output.push_back(input_[i]);
                }
                return output;
            }

            std::vector<config> __convert_to_configs_vector(game_value input_) {
                std::vector<config> output;
                for (uint32_t i = 0; i < input_.length(); ++i) {
                    output.push_back(config(input_[i]));
                }
                return output;
            }

            std::vector<location> __convert_to_locations_vector(game_value input_) {
                std::vector<location> output;
                for (uint32_t i = 0; i < input_.length(); ++i) {
                    output.push_back(location(input_[i]));
                }
                return output;
            }

            std::vector<task> __convert_to_tasks_vector(game_value input_) {
                std::vector<task> output;
                for (uint32_t i = 0; i < input_.length(); ++i) {
                    output.push_back(task(input_[i]));
                }
                return output;
            }

            vector3 __convert_to_vector3(game_value input_) {
                return vector3(input_[0], input_[1], input_[2]);
            }
        }
    }
}
