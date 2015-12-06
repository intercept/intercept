#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
	namespace sqf {
		namespace __helpers {

			void __empty_nular(nular_function fnc_) {
				host::functions.invoke_raw_nular(fnc_);
			}

			std::string __retrieve_nular_string(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				std::string ret_number = ((game_data_string *)function_return_number.data)->get_string();
				host::functions.free_value(&function_return_number);

				return ret_number;
			}

			float __retrieve_nular_number(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				float ret_number = ((game_data_number *)function_return_number.data)->number;
				host::functions.free_value(&function_return_number);

				return ret_number;
			}

			object __retrieve_nular_object(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				return std::make_shared<object_ptr>(function_return_number);
			}

			text __retrieve_nular_text(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				return std::make_shared<text_ptr>(function_return_number);
			}

			rv_namespace __retrieve_nular_namespace(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				return std::make_shared<rv_namespace_ptr>(function_return_number);
			}

			location __retrieve_nular_location(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				return std::make_shared<location_ptr>(function_return_number);
			}

			side __retrieve_nular_side(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				return std::make_shared<side_ptr>(function_return_number);
			}

			control __retrieve_nular_control(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				return std::make_shared<control_ptr>(function_return_number);
			}

			group __retrieve_nular_group(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				return std::make_shared<group_ptr>(function_return_number);
			}

			config __retrieve_nular_config(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				return std::make_shared<config_ptr>(function_return_number);
			}

			display __retrieve_nular_display(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				return std::make_shared<display_ptr>(function_return_number);
			}

			vector3 __retrieve_nular_vector3(nular_function fnc_) {
				game_value function_return_array = host::functions.invoke_raw_nular(fnc_);
				float x = ((game_data_number *)((game_data_array *)function_return_array.data)->data[0].data)->number;
				float y = ((game_data_number *)((game_data_array *)function_return_array.data)->data[1].data)->number;
				float z = ((game_data_number *)((game_data_array *)function_return_array.data)->data[2].data)->number;
				host::functions.free_value(&function_return_array);
				return vector3(x, y, z);
			}

			bool __retrieve_nular_bool(nular_function fnc_) {
				game_value function_return_bool = host::functions.invoke_raw_nular(fnc_);
				bool ret_bool = ((game_data_bool *)function_return_bool.data)->value;
				host::functions.free_value(&function_return_bool);
				return ret_bool;
			}

			std::vector<object> all_objects(nular_function fnc_) {	
                return __convert_to_objects_vector(host::functions.invoke_raw_nular(fnc_));
			}
			std::vector<std::string> _nular_strings(nular_function fnc_) {
                return __convert_to_strings_vector(host::functions.invoke_raw_nular(fnc_));
			}
			std::vector<team_member> _nular_team_members(nular_function fnc_) {
                return __convert_to_team_members_vector(host::functions.invoke_raw_nular(fnc_));
			}
			std::vector<group> all_groups(nular_function fnc_) {
                return __convert_to_groups_vector(host::functions.invoke_raw_nular(fnc_));
			}
			std::vector<display> all_displays(nular_function fnc_) {
                return __convert_to_displays_vector(host::functions.invoke_raw_nular(fnc_));
			}
			std::vector<marker> all_map_markers(nular_function fnc_) {
                return __convert_to_markers_vector(host::functions.invoke_raw_nular(fnc_));
			}

			void __empty_unary_object(unary_function fnc_, object obj_)
			{
				host::functions.invoke_raw_unary(fnc_, *obj_);
			}

			void __empty_unary_vector(unary_function fnc_, vector3 vec_)
			{
				host::functions.invoke_raw_unary(fnc_, game_value_vector3(vec_));
			}

			void __empty_unary_string(unary_function fnc_, std::string str_)
			{
				host::functions.invoke_raw_unary(fnc_, game_value_string(str_));
			}

			void __empty_unary_number(unary_function fnc_, float val_)
			{
				host::functions.invoke_raw_unary(fnc_, game_value_number(val_));
			}

			void __empty_unary_bool(unary_function fnc_, bool val_)
			{
				host::functions.invoke_raw_unary(fnc_, game_value_bool(val_));
			}

			void __empty_unary_control(unary_function fnc_, control ctrl_)
			{
				host::functions.invoke_raw_unary(fnc_, *ctrl_);
			}

			bool __bool_unary_object(unary_function fnc_, object obj_)
			{
				game_value bool_ret = host::functions.invoke_raw_unary(fnc_, *obj_);
				bool rv = ((game_data_bool *)bool_ret.data)->value;
				host::functions.free_value(&bool_ret);
				return rv;
			}

			bool __bool_unary_string(unary_function fnc_, std::string str_)
			{
				game_value bool_ret = host::functions.invoke_raw_unary(fnc_, game_value_string(str_));
				bool rv = ((game_data_bool *)bool_ret.data)->value;
				host::functions.free_value(&bool_ret);
				return rv;
			}

			bool __bool_unary_number(unary_function fnc_, float val_)
			{
				game_value bool_ret = host::functions.invoke_raw_unary(fnc_, game_value_number(val_));
				bool rv = ((game_data_bool *)bool_ret.data)->value;
				host::functions.free_value(&bool_ret);
				return rv;
			}

			bool __bool_unary_control(unary_function fnc_, control ctl_)
			{
				game_value bool_ret = host::functions.invoke_raw_unary(fnc_, *ctl_);
				bool rv = ((game_data_bool *)bool_ret.data)->value;
				host::functions.free_value(&bool_ret);
				return rv;
			}

			float __number_unary_number(unary_function fnc_, float val_)
			{
				game_value num_ret = host::functions.invoke_raw_unary(fnc_, game_value_number(val_));
				float rv = ((game_data_number *)num_ret.data)->number;
				host::functions.free_value(&num_ret);
				return rv;
			}

			float __number_unary_control(unary_function fnc_, control ctl_)
			{
				game_value num_ret = host::functions.invoke_raw_unary(fnc_, *ctl_);
				float rv = ((game_data_number *)num_ret.data)->number;
				host::functions.free_value(&num_ret);
				return rv;
			}

			float __number_unary_string(unary_function fnc_, std::string str_)
			{
				game_value num_ret = host::functions.invoke_raw_unary(fnc_, game_value_string(str_));
				float rv = ((game_data_number *)num_ret.data)->number;
				host::functions.free_value(&num_ret);
				return rv;
			}

			float __number_unary_object(unary_function fnc_, object obj_)
			{
				game_value num_ret = host::functions.invoke_raw_unary(fnc_, *obj_);
				float rv = ((game_data_number *)num_ret.data)->number;
				host::functions.free_value(&num_ret);
				return rv;
			}

			std::string __string_unary_control(unary_function fnc_, control ctl_)
			{
				game_value str_ret = host::functions.invoke_raw_unary(fnc_, *ctl_);
				std::string rv = ((game_data_string *)str_ret.data)->get_string();
				host::functions.free_value(&str_ret);
				return rv;
			}

			std::string __string_unary_object(unary_function fnc_, object obj_)
			{
				game_value str_ret = host::functions.invoke_raw_unary(fnc_, *obj_);
				std::string rv = ((game_data_string *)str_ret.data)->get_string();
				host::functions.free_value(&str_ret);
				return rv;
			}

			std::string __string_unary_string(unary_function fnc_, std::string str_)
			{
				game_value str_ret = host::functions.invoke_raw_unary(fnc_, game_value_string(str_));
				std::string rv = ((game_data_string *)str_ret.data)->get_string();
				host::functions.free_value(&str_ret);
				return rv;
			}

			object __object_unary_object(unary_function fnc_, object obj_)
			{
				game_value obj_ret = host::functions.invoke_raw_unary(fnc_, *obj_);
				return std::make_shared<object_ptr>(obj_ret);
			}


            std::vector<object> __convert_to_objects_vector(game_value input__) {
                game_data_array* array_value = ((game_data_array *)input__.data);

                std::vector<object> output;
                for (int i = 0; i < array_value->length; ++i) {
                    output.push_back(std::make_shared<object_ptr>(array_value->data[i]));
                }
                host::functions.free_value(&input__);
                return output;
            }

            std::vector<std::string> __convert_to_strings_vector(game_value input__) {
                game_data_array* array_value = ((game_data_array *)input__.data);

                std::vector<std::string> output;
                for (int i = 0; i < array_value->length; ++i) {
                    std::string value = ((game_data_string *)array_value->data[i].data)->get_string();
                    output.push_back(value);
                }
                host::functions.free_value(&input__); // TODO do we also have to free all the strings in the array?
                return output;
            }

            std::vector<team_member> __convert_to_team_members_vector(game_value input__) {
                game_data_array* array_value = ((game_data_array *)input__.data);

                std::vector<team_member> output;
                for (int i = 0; i < array_value->length; ++i) {
                    output.push_back(std::make_shared<team_member_ptr>(array_value->data[i]));
                }
                host::functions.free_value(&input__);
                return output;
            }

            std::vector<group> __convert_to_groups_vector(game_value input__) {
                game_data_array* array_value = ((game_data_array *)input__.data);

                std::vector<group> output;
                for (int i = 0; i < array_value->length; ++i) {
                    output.push_back(std::make_shared<group_ptr>(array_value->data[i]));
                }
                host::functions.free_value(&input__);
                return output;
            }

            std::vector<display> __convert_to_displays_vector(game_value input__) {
                game_data_array* array_value = ((game_data_array *)input__.data);

                std::vector<display> output;
                for (int i = 0; i < array_value->length; ++i) {
                    output.push_back(std::make_shared<display_ptr>(array_value->data[i]));
                }
                host::functions.free_value(&input__);
                return output;
            }
            std::vector<marker> __convert_to_markers_vector(game_value input__) {
                game_data_array* array_value = ((game_data_array *)input__.data);

                std::vector<marker> output;
                for (int i = 0; i < array_value->length; ++i) { // TODO figure out converting markers in an array to an std vector marker 
                    std::string value = ((game_data_string *)array_value->data[i].data)->get_string();
                    output.push_back(value);
                }
                host::functions.free_value(&input__);
                return output;
            }
		}
	}
}