#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
	namespace sqf {
		namespace __helpers {
			float __retrieve_nular_number(nular_function fnc_) {
				game_value function_return_number = host::functions.invoke_raw_nular(fnc_);
				float ret_number = ((game_data_number *)function_return_number.data)->number;
				host::functions.free_value(&function_return_number);

				return ret_number;
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


            std::vector<object>& all_objects(nular_function fnc_) {
                game_value intersects_value = host::functions.invoke_raw_nular(fnc_);
                game_data_array* intersects = ((game_data_array *)intersects_value.data);

                std::vector<object> output;
                for (int i = 0; i < intersects->length; ++i) {
                    output.push_back(std::make_shared<object_ptr>(intersects->data[i]));
                }
                host::functions.free_value(&intersects_value);
                return output;
            }

            std::vector<group>& all_groups(nular_function fnc_) {
                game_value intersects_value = host::functions.invoke_raw_nular(fnc_);
                game_data_array* intersects = ((game_data_array *)intersects_value.data);

                std::vector<group> output;
                for (int i = 0; i < intersects->length; ++i) {
                    output.push_back(std::make_shared<group_ptr>(intersects->data[i]));
                }
                host::functions.free_value(&intersects_value);
                return output;
            }

            std::vector<display>& all_displays(nular_function fnc_) {
                game_value intersects_value = host::functions.invoke_raw_nular(fnc_);
                game_data_array* intersects = ((game_data_array *)intersects_value.data);

                std::vector<display> output;
                for (int i = 0; i < intersects->length; ++i) {
                    output.push_back(std::make_shared<display_ptr>(intersects->data[i]));
                }
                host::functions.free_value(&intersects_value);
                return output;
            }
            std::vector<marker>& all_map_markers(nular_function fnc_) {
                game_value intersects_value = host::functions.invoke_raw_nular(fnc_);
                game_data_array* intersects = ((game_data_array *)intersects_value.data);

                std::vector<marker> output;
                for (int i = 0; i < intersects->length; ++i) { // TODO figure out converting markers in an array to an std vector marker 
                                                               // output.push_back((host::functions.new_string((const char *)(intersects->data[i]))));
                }
                host::functions.free_value(&intersects_value);
                return output;
            }
		}
	}
}