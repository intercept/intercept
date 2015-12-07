#include "uncategorized.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"


using namespace intercept::client::types;

namespace intercept {
	namespace sqf {
		namespace __uncategorized {
			std::vector<std::string> action_keys(std::string user_action_)
			{
				game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeys__string__ret__array, game_value_string(user_action_));
				std::vector<std::string> r_arr = __helpers::__convert_to_strings_vector(act_keys);

				host::functions.free_value(&act_keys);
				return r_arr;
			}


			std::string action_keys_names(std::string user_action_)
			{
				game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnames__string_array__ret__string, game_value_string(user_action_));
				std::string r_str = ((game_data_string *)act_keys.data)->get_string();

				host::functions.free_value(&act_keys);
				return r_str;
			}

			std::string action_keys_names(std::string user_action_, float max_keys_)
			{
				game_value_array<2> params({
					game_value_string(user_action_),
					game_value_number(max_keys_)
				});
				game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnames__string_array__ret__string, params);
				std::string r_str = ((game_data_string *)act_keys.data)->get_string();

				host::functions.free_value(&act_keys);
				return r_str;
			}
			std::string action_keys_names(std::string user_action_, float max_keys_, std::string input_device_priority_)
			{
				game_value_array<3> params({
					game_value_string(user_action_),
					game_value_number(max_keys_),
					game_value_string(input_device_priority_)
				});
				game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnames__string_array__ret__string, params);
				std::string r_str = ((game_data_string *)act_keys.data)->get_string();

				host::functions.free_value(&act_keys);
				return r_str;
			}

			std::vector<std::string> action_keys_names_array(std::string user_action_)
			{
				game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnamesarray__string_array__ret__array, game_value_string(user_action_));
				std::vector<std::string> r_arr = __helpers::__convert_to_strings_vector(act_keys);

				host::functions.free_value(&act_keys);
				return r_arr;
			}

			std::vector<std::string> action_keys_names_array(std::string user_action_, float max_keys_)
			{
				game_value_array<2> params({
					game_value_string(user_action_),
					game_value_number(max_keys_)
				});
				game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnamesarray__string_array__ret__array, params);
				std::vector<std::string> r_arr = __helpers::__convert_to_strings_vector(act_keys);

				host::functions.free_value(&act_keys);
				return r_arr;
			}
			std::vector<std::string> action_keys_names_array(std::string user_action_, float max_keys_, std::string input_device_priority_)
			{
				game_value_array<3> params({
					game_value_string(user_action_),
					game_value_number(max_keys_),
					game_value_string(input_device_priority_)
				});

				game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnamesarray__string_array__ret__array, params);
				std::vector<std::string> r_arr = __helpers::__convert_to_strings_vector(act_keys);

				host::functions.free_value(&act_keys);
				return r_arr;
			}

			void activate_addons(std::vector<std::string> &addons_)
			{
				game_value_array_dynamic<std::string, game_value_string> addons_arr(addons_);

				host::functions.invoke_raw_unary(client::__sqf::unary__activateaddons__array__ret__nothing, addons_arr);
			}

			/* potential namespace: camera */
			void add_cam_shake(float power_, float duration_, float frequency_)
			{
				game_value_array<3> params({
					game_value_number(power_),
					game_value_number(duration_),
					game_value_number(frequency_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__addcamshake__array__ret__nothing, params);
			}

			/* potential namespace: items, inventory, campaign */
			void add_item_pool(std::string item_name_, float item_count_)
			{
				game_value_array<3> params({
					game_value_string(item_name_),
					game_value_number(item_count_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__additempool__array__ret__nothing, params);
			}

			void add_magazine_pool(std::string mag_name_, float mag_count_)
			{
				game_value_array<3> params({
					game_value_string(mag_name_),
					game_value_number(mag_count_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__addmagazinepool__array__ret__nothing, params);
			}

			/// @todo
			void add_to_remains_collector(std::vector<object> objects_)
			{
				//game_value_array_dynamic<object, game_value_object> objects_arr(objects_);
			}

			void ais_finish_heal(object &wounded_, object &medic_, bool medic_can_heal_)
			{
				game_value_array<3> params({
					wounded_->value,
					medic_->value,
					game_value_bool(medic_can_heal_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__aisfinishheal__array__ret__nothing, params);
			}

			std::vector<object> all_mission_objects(std::string type_)
			{
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__allmissionobjects__string__ret__array, game_value_string(type_)));
			}
		}
	}
}