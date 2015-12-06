#include "chat.hpp"
#include "client\pointers.hpp"
#include "core.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
		namespace core {
			object player() {
				game_value player_obj = host::functions.invoke_raw_nular(client::__sqf::nular__player__ret__object);
				return std::make_shared<object_ptr>(player_obj);
			}

			object create_vehicle(std::string type_, vector3 pos_)
			{
				game_value type = host::functions.new_string(type_.c_str());
				game_value obj = host::functions.invoke_raw_binary(__sqf::binary__createvehicle__string__array__ret__object, &type, game_value_vector3(pos_));
				host::functions.free_value(&type);
				return std::make_shared<object_ptr>(obj);
			}

			object create_vehicle(std::string type_, vector3 pos_, std::vector<marker> markers_ = {}, float placement_ = 0.0f, std::string special_ = "NONE")
			{
				game_value_array<5> args({
					game_value_string(type_),
					game_value_vector3(pos_),
					game_value_array_dynamic<marker, game_value_string>(markers_),
					game_value_number(placement_),
					game_value_string(special_)
				});

				return std::make_shared<object_ptr>(host::functions.invoke_raw_unary(__sqf::unary__createvehicle__array__ret__object, args));
			}

			void delete_vehicle(object obj_)
			{
				host::functions.invoke_raw_unary(__sqf::unary__deletevehicle__object__ret__nothing, *obj_);
			}

			std::vector<object> all_3den_entities() {
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__all3denentities__ret__array));
			}

			std::vector<object> all_curators() {
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allcurators__ret__array));
			}

			std::vector<object> all_dead() {
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__alldead__ret__array));
			}

			std::vector<object> all_deadmen() {
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__alldeadmen__ret__array));
			}

			std::vector<display> all_displays() {
				return __helpers::__convert_to_displays_vector(host::functions.invoke_raw_nular(client::__sqf::nular__alldisplays__ret__array));
			}

			std::vector<group> all_groups() {
				return __helpers::__convert_to_groups_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allgroups__ret__array));
			}

			std::vector<marker> all_map_markers() {
				return __helpers::__convert_to_markers_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allmapmarkers__ret__array));
			}

			std::vector<object> all_mines() {
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allmines__ret__array));
			}

			std::vector<object> all_players() {
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allplayers__ret__array));
			}

			std::vector<object> all_units() {
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allunits__ret__array));
			}

			std::vector<object> all_units_uav() {
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allunitsuav__ret__array));
			}

			float server_time() {
				game_value ret_value = host::functions.invoke_raw_nular(client::__sqf::nular__servertime__ret__scalar);
				float rv = ((game_data_number *)ret_value.data)->number;
				host::functions.free_value(&ret_value);
				return rv;
			}

			std::string server_name() {
				game_value ret_value = host::functions.invoke_raw_nular(client::__sqf::nular__servername__ret__string);
				std::string ret_number = ((game_data_string *)ret_value.data)->get_string();
				host::functions.free_value(&ret_value);
				return ret_number;
			}

			bool is_null(object value_) {
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__isnull__object__ret__bool, *value_);
				bool rv = ((game_data_bool *)ret_value.data)->value;
				host::functions.free_value(&ret_value);
				return rv;
			}

			bool is_null(group value_) {
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__isnull__group__ret__bool, *value_);
				bool rv = ((game_data_bool *)ret_value.data)->value;
				host::functions.free_value(&ret_value);
				return rv;
			}

			bool is_null(control value_) {
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__isnull__control__ret__bool, *value_);
				bool rv = ((game_data_bool *)ret_value.data)->value;
				host::functions.free_value(&ret_value);
				return rv;
			}

			bool is_null(display value_) {
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__isnull__display__ret__bool, *value_);
				bool rv = ((game_data_bool *)ret_value.data)->value;
				host::functions.free_value(&ret_value);
				return rv;
			}

			bool is_null(script value_) {
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__isnull__script__ret__bool, *value_);
				bool rv = ((game_data_bool *)ret_value.data)->value;
				host::functions.free_value(&ret_value);
				return rv;
			}

			bool is_null(task value_) {
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__isnull__task__ret__bool, *value_);
				bool rv = ((game_data_bool *)ret_value.data)->value;
				host::functions.free_value(&ret_value);
				return rv;
			}

			script script_null() {
				game_value ret_value = host::functions.invoke_raw_nular(client::__sqf::nular__scriptnull__ret__script);
				return std::make_shared<script_ptr>(ret_value);
			}

			task task_null() {
				game_value ret_value = host::functions.invoke_raw_nular(client::__sqf::nular__tasknull__ret__task);
				return std::make_shared<task_ptr>(ret_value);
			}

			rv_namespace ui_namespace() {
				game_value ret_value = host::functions.invoke_raw_nular(client::__sqf::nular__uinamespace__ret__namespace);
				return std::make_shared<rv_namespace_ptr>(ret_value);
			}

			std::vector<script> diag_active_mission_fsms() {
				game_value input__ = host::functions.invoke_raw_nular(client::__sqf::nular__diag_activemissionfsms__ret__array);
				game_data_array* array_value = ((game_data_array *)input__.data);
				std::vector<script> output;
				for (uint32_t i = 0; i < array_value->length; ++i) {
					output.push_back(std::make_shared<script_ptr>(array_value->data[i]));
				}
				host::functions.free_value(&input__);
				return output;
			}

			std::vector<script> diag_active_sqf_scripts() {
				game_value input__ = host::functions.invoke_raw_nular(client::__sqf::nular__diag_activesqfscripts__ret__array);
				game_data_array* array_value = ((game_data_array *)input__.data);
				std::vector<script> output;
				for (uint32_t i = 0; i < array_value->length; ++i) {
					output.push_back(std::make_shared<script_ptr>(array_value->data[i]));
				}
				host::functions.free_value(&input__);
				return output;
			}

			std::vector<script> diag_active_sqs_scripts() {
				game_value input__ = host::functions.invoke_raw_nular(client::__sqf::nular__diag_activesqsscripts__ret__array);
				game_data_array* array_value = ((game_data_array *)input__.data);
				std::vector<script> output;
				for (uint32_t i = 0; i < array_value->length; ++i) {
					output.push_back(std::make_shared<script_ptr>(array_value->data[i]));
				}
				host::functions.free_value(&input__);
				return output;
			}
		}
    }
}
