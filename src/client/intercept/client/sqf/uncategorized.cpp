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

			text action_keys_images(std::string user_action_)
			{
				game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysimages__string_array__ret__text, game_value_string(user_action_));
				return text(act_keys);
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

			void ais_finish_heal(object wounded_, object medic_, bool medic_can_heal_)
			{
				game_value_array<3> params({
					wounded_,
					medic_,
					game_value_bool(medic_can_heal_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__aisfinishheal__array__ret__nothing, params);
			}

			std::vector<object> all_mission_objects(std::string type_)
			{
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__allmissionobjects__string__ret__array, game_value_string(type_)));
			}

			std::vector<object> assigned_cargo(object veh_)
			{
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__assignedcargo__object__ret__array, veh_));
			}

			std::vector<std::string> assigned_items(object unit_)
			{
				return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__assigneditems__object__ret__array, unit_));
			}

			object attached_object(location loc_)
			{
				game_value ath_obj = host::functions.invoke_raw_unary(client::__sqf::unary__attachedobject__location__ret__object, loc_);
				return object(ath_obj);
			}

			std::vector<object> attached_objects(object obj_)
			{
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__attachedobjects__object__ret__array, obj_));
			}

			object attached_to(object obj_)
			{
				game_value ath_obj = host::functions.invoke_raw_unary(client::__sqf::unary__attachedto__object__ret__array, obj_);
				return object(ath_obj);
			}

			bool attack_enabled(object unit_)
			{
				return __helpers::__bool_unary_object(client::__sqf::unary__attackenabled__object_group__ret__bool, unit_);
			}

			bool attack_enabled(group group_)
			{
				game_value bool_ret = host::functions.invoke_raw_unary(client::__sqf::unary__attackenabled__object_group__ret__bool, group_);
				bool rv = ((game_data_bool *)bool_ret.data)->value;
				host::functions.free_value(&bool_ret);
				return rv;
			}

			std::vector<std::string> backpack_cargo(object box_)
			{
				return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackcargo__object__ret__array, box_));
			}

			std::vector<std::string> backpack_items(object unit_)
			{
				return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackitems__object__ret__array, unit_));
			}

			std::vector<std::string> backpack_magazines(object unit_)
			{
				return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackmagazines__object__ret__array, unit_));
			}

			sqf::bounding_box bounding_box(object model_)
			{
				game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__boundingbox__object__ret__array, model_);
				game_data_array* array_value = ((game_data_array *)input.data);

				sqf::bounding_box bb;

				float x_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[0].data)->number;
				float y_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[1].data)->number;
				float z_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[2].data)->number;
				bb.min = vector3(x_min, y_min, z_min);

				float x_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[0].data)->number;
				float y_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[1].data)->number;
				float z_max  = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[2].data)->number;
				bb.min = vector3(x_max, y_max, z_max);

				host::functions.free_value(&input);
				return bb;
			}

			sqf::bounding_box bounding_box_real(object model_)
			{
				game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__boundingboxreal__object__ret__array, model_);
				game_data_array* array_value = ((game_data_array *)input.data);

				sqf::bounding_box bb;

				float x_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[0].data)->number;
				float y_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[1].data)->number;
				float z_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[2].data)->number;
				bb.min = vector3(x_min, y_min, z_min);

				float x_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[0].data)->number;
				float y_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[1].data)->number;
				float z_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[2].data)->number;
				bb.min = vector3(x_max, y_max, z_max);

				host::functions.free_value(&input);
				return bb;
			}

			vector3 bounding_center(object obj_)
			{
				game_value function_return_array = host::functions.invoke_raw_unary(client::__sqf::unary__boundingcenter__object__ret__array, obj_);
				float x = ((game_data_number *)((game_data_array *)function_return_array.data)->data[0].data)->number;
				float y = ((game_data_number *)((game_data_array *)function_return_array.data)->data[1].data)->number;
				float z = ((game_data_number *)((game_data_array *)function_return_array.data)->data[2].data)->number;
				host::functions.free_value(&function_return_array);
				return vector3(x, y, z);
			}

			void button_set_action(float control_id_, std::string code_)
			{
				game_value_array<2> params({
					game_value_number(control_id_),
					game_value_string(code_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__buttonsetaction__array__ret__nothing, params);
			}

			void button_set_action(control control_, std::string code_)
			{
				game_value_array<2> params({
					control_,
					game_value_string(code_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__buttonsetaction__array__ret__nothing, params);
			}

			void ctrl_enable(float control_id_, bool enable_)
			{
				game_value_array<2> params({
					game_value_number(control_id_),
					game_value_bool(enable_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__ctrlenable__array__ret__nothing, params);
			}

			void ctrl_enable(control control_, bool enable_)
			{
				{
					game_value_array<2> params({
						control_,
						game_value_bool(enable_)
					});

					host::functions.invoke_raw_unary(client::__sqf::unary__ctrlenable__array__ret__nothing, params);
				}
			}

			void ctrl_set_text(float control_id_, std::string text_)
			{
				game_value_array<2> params({
					game_value_number(control_id_),
					game_value_string(text_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__ctrlsettext__array__ret__nothing, params);
			}

			void ctrl_set_text(control control_, std::string text_)
			{
				game_value_array<2> params({
					control_,
					game_value_string(text_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__ctrlsettext__array__ret__nothing, params);
			}

			void ctrl_show(float control_id_, bool show_)
			{
				game_value_array<2> params({
					game_value_number(control_id_),
					game_value_bool(show_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__ctrlshow__array__ret__nothing, params);
			}

			void ctrl_show(control control_, bool show_)
			{
				{
					game_value_array<2> params({
						control_,
						game_value_bool(show_)
					});

					host::functions.invoke_raw_unary(client::__sqf::unary__ctrlshow__array__ret__nothing, params);
				}
			}


			// What a confusing command name.
			std::string class_name(location loc_)
			{
				game_value str_ret = host::functions.invoke_raw_unary(client::__sqf::unary__classname__location__ret__string, loc_);
				std::string rv = ((game_data_string *)str_ret.data)->get_string();
				host::functions.free_value(&str_ret);
				return rv;
			}

			std::string combat_mode(group grp_)
			{
				game_value str_ret = host::functions.invoke_raw_unary(client::__sqf::unary__combatmode__object_group__ret__string, grp_);
				std::string rv = ((game_data_string *)str_ret.data)->get_string();
				host::functions.free_value(&str_ret);
				return rv;
			}

			std::string combat_mode(object unit_)
			{
				return __helpers::__string_unary_object(client::__sqf::unary__combatmode__object_group__ret__string, unit_);
			}

			void command_get_out(object unit_)
			{
				return __helpers::__empty_unary_object(client::__sqf::unary__commandgetout__object_array__ret__nothing, unit_);
			}

			void command_get_out(std::vector<object> units_)
			{
				// @todo
				throw 713; // Not Implmemented.
				//return __helpers::__empty_unary_object(client::__sqf::unary__commandgetout__object_array__ret__nothing, unit_);
			}

			void command_stop(object unit_)
			{
				return __helpers::__empty_unary_object(client::__sqf::unary__commandstop__object_array__ret__nothing, unit_);
			}
			void command_stop(std::vector<object> units_)
			{
				// @todo
				throw 713; // Not Implmemented.
				//return __helpers::__empty_unary_object(client::__sqf::unary__commandstop__object_array__ret__nothing, unit_);
			}

			object create_agent(std::string type_, vector3 pos_, std::vector<marker> markers_ /* = {}*/, float placement_ /*= 0.0f*/, std::string special_ /*= "NONE"*/)
			{
				game_value_array<5> args({
					game_value_string(type_),
					game_value_vector3(pos_),
					game_value_array_dynamic<marker, game_value_string>(markers_),
					game_value_number(placement_),
					game_value_string(special_)
				});

				return object(host::functions.invoke_raw_unary(__sqf::unary__createagent__array__ret__object, args));
			}

			void create_gear_dialog(object unit_, std::string resource_)
			{
				game_value_array<2> params({
					unit_,
					game_value_string(resource_)
				});

				host::functions.invoke_raw_unary(__sqf::unary__creategeardialog__array__ret__nothing, params);
			}

			void create_guarded_point(side side_, vector3 pos_, float idstatic_, object veh_)
			{
				game_value_array<4> params({
					side_,
					game_value_vector3(pos_),
					game_value_number(idstatic_),
					veh_
				});

				host::functions.invoke_raw_unary(__sqf::unary__createguardedpoint__array__ret__nothing, params);
			}

			location create_location(std::string classname_, vector3 pos_, float size_x_, float size_y_)
			{
				game_value_array<4> params({
					game_value_string(classname_),
					game_value_vector3(pos_),
					game_value_number(size_x_),
					game_value_number(size_y_)
				});

				return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
			}

			location create_location(std::string classname_, vector2 pos_, float size_x_, float size_y_)
			{
				game_value_array<4> params({
					game_value_string(classname_),
					game_value_vector2(pos_),
					game_value_number(size_x_),
					game_value_number(size_y_)
				});

				return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
			}
			location create_location(std::string classname_, object obj_, float size_x_, float size_y_)
			{
				game_value_array<4> params({
					game_value_string(classname_),
					obj_,
					game_value_number(size_x_),
					game_value_number(size_y_)
				});

				return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
			}

			object create_mine(std::string type_, vector3 pos_, std::vector<marker> markers_/* = {}*/, float placement_/* = 0.0f*/)
			{
				game_value_array<4> args({
					game_value_string(type_),
					game_value_vector3(pos_),
					game_value_array_dynamic<marker, game_value_string>(markers_),
					game_value_number(placement_),
				});

				return object(host::functions.invoke_raw_unary(__sqf::unary__createmine__array__ret__object, args));
			}

			object create_sound_source(std::string type_, vector3 pos_, std::vector<marker> markers_/* = {}*/, float placement_/* = 0.0f*/)
			{
				game_value_array<4> args({
					game_value_string(type_),
					game_value_vector3(pos_),
					game_value_array_dynamic<marker, game_value_string>(markers_),
					game_value_number(placement_),
				});

				return object(host::functions.invoke_raw_unary(__sqf::unary__createsoundsource__array__ret__object, args));
			}

			team_member create_team(std::string type_, std::string name_)
			{
				game_value_array<2> args({
					game_value_string(type_),
					game_value_string(name_),
				});

				return team_member(host::functions.invoke_raw_unary(__sqf::unary__createteam__array__ret__team_member, args));
			}

			object create_trigger(std::string type_, vector3 pos_, bool make_global_/* = true*/)
			{
				game_value_array<3> args({
					game_value_string(type_),
					game_value_vector3(pos_),
					game_value_bool(make_global_)
				});

				return object(host::functions.invoke_raw_unary(__sqf::unary__createtrigger__array__ret__object, args));
			}

			object create_trigger(std::string type_, object pos_, bool make_global_ /*= true*/)
			{
				game_value_array<3> args({
					game_value_string(type_),
					pos_,
					game_value_bool(make_global_)
				});

				return object(host::functions.invoke_raw_unary(__sqf::unary__createtrigger__array__ret__object, args));
			}

			std::vector<object> crew(object _veh)
			{
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__crew__object__ret__array, _veh));
			}

			std::string current_magazine_detail(object veh_)
			{
				return __helpers::__string_unary_object(client::__sqf::unary__currentmagazinedetail__object__ret__array, veh_);
			}
			
			std::vector<task> current_tasks(team_member team_member_)
			{
				game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__currenttasks__team_member__ret__array, team_member_);

				game_data_array* array_value = ((game_data_array *)input.data);

				std::vector<task> output;
				for (uint32_t i = 0; i < array_value->length; ++i) {
					output.push_back(task(array_value->data[i]));
				}
				host::functions.free_value(&input);
				return output;
			}

			void cut_obj(std::string name_, std::string type_, float speed_)
			{
				game_value_array<3> args({
					game_value_string(name_),
					game_value_string(type_),
					game_value_number(speed_)
				});

				host::functions.invoke_raw_unary(__sqf::unary__cutobj__array__ret__nothing, args);
			}

			void cut_rsc(std::string name_, std::string type_, float speed_, bool show_on_map_)
			{
				game_value_array<4> args({
					game_value_string(name_),
					game_value_string(type_),
					game_value_number(speed_),
					game_value_bool(show_on_map_)
				});

				host::functions.invoke_raw_unary(__sqf::unary__cutrsc__array__ret__nothing, args);
			}

			void cut_text(std::string name_, std::string type_, float speed_, bool show_on_map_)
			{
				game_value_array<4> args({
					game_value_string(name_),
					game_value_string(type_),
					game_value_number(speed_),
					game_value_bool(show_on_map_)
				});

				host::functions.invoke_raw_unary(__sqf::unary__cuttext__array__ret__nothing, args);
			}

			void enable_debriefing_stats(float left_, float top_, float width_, float height_)
			{
				game_value_array<4> args({
					game_value_number(left_),
					game_value_number(top_),
					game_value_number(width_),
					game_value_number(height_)
				});

				host::functions.invoke_raw_unary(__sqf::unary__enabledebriefingstats__array__ret__nothing, args);
			}

			void enable_saving(bool enable_)
			{
				enable_saving(enable_, !enable_);
			}

			void enable_saving(bool enable_, bool autosave_)
			{
				game_value_array<2> args({
					game_value_bool(enable_),
					game_value_bool(autosave_)
				});

				host::functions.invoke_raw_unary(__sqf::unary__enablesaving__bool_array__ret__nothing, args);
			}

			std::string formation(object leader_)
			{
				game_value str_ret = host::functions.invoke_raw_unary(__sqf::unary__formation__object_group__ret__string, leader_);
				std::string rv = ((game_data_string *)str_ret.data)->get_string();
				host::functions.free_value(&str_ret);
				return rv;
			}

			std::string formation(group group_)
			{
				game_value str_ret = host::functions.invoke_raw_unary(__sqf::unary__formation__object_group__ret__string, group_);
				std::string rv = ((game_data_string *)str_ret.data)->get_string();
				host::functions.free_value(&str_ret);
				return rv;
			}

			std::vector<object> formation_members(object unit_)
			{
				return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__formationmembers__object__ret__array, unit_));
			}

			vector3 formation_position(object unit_)
			{
				return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(__sqf::unary__formationposition__object__ret__array, unit_));
			}

			std::vector<rv_crew_member> full_crew(object veh_, const std::string & filter_)
			{
				game_value crew_list;

				if (filter_ == "")
				{
					crew_list = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__object__ret__array, veh_);
				}
				else
				{
					game_value_array<2> args({
						veh_,
						game_value_string(filter_)
					});

					crew_list = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__array__ret__array, args);
				}

				game_data_array* gd_array = ((game_data_array *)crew_list.data);
				std::vector<rv_crew_member> output;
				for (uint32_t i = 0; i < gd_array->length; ++i) {

					rv_crew_member crew_m;

					crew_m.unit = object(((game_data_array *)gd_array->data[i].data)->data[0]);
					crew_m.role = ((game_data_string *)((game_data_array *)gd_array->data[i].data)->data[1].data)->get_string();
					crew_m.cargo_index = ((game_data_number *)((game_data_array *)gd_array->data[i].data)->data[2].data)->number;
					// Turret path
					crew_m.person_turret = ((game_data_bool *)((game_data_array *)gd_array->data[i].data)->data[4].data)->value;
					output.push_back(crew_m);
				}

				host::functions.free_value(&crew_list);
				return output;
			}

			std::vector<std::string> get_artillery_ammo(const std::vector<object>& units_)
			{
				game_value_array_dynamic<object, object> addons_arr(units_);

				return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__getartilleryammo__array__ret__array, addons_arr));
			}

			vector3 get_center_of_mass(object obj_)
			{
				game_value function_return_array = host::functions.invoke_raw_unary(client::__sqf::unary__getcenterofmass__object__ret__array, obj_);
				float x = ((game_data_number *)((game_data_array *)function_return_array.data)->data[0].data)->number;
				float y = ((game_data_number *)((game_data_array *)function_return_array.data)->data[1].data)->number;
				float z = ((game_data_number *)((game_data_array *)function_return_array.data)->data[2].data)->number;
				host::functions.free_value(&function_return_array);
				return vector3(x, y, z);
			}

			std::vector<float> get_dlcs(float filter_)
			{
				return __helpers::__convert_to_numbers_vector(host::functions.invoke_raw_unary(client::__sqf::unary__getdlcs__scalar__ret__array, game_value_number(filter_)));
			}

			/****************************************************************************** LISTBOX ***************************************************************************/
			float lb_add(float control_id_, std::string text_)
			{
				game_value args({
					(control_id_),
					(text_)
				});

				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbadd__array__ret__scalar, args));
			}

			float lb_add(control control_, std::string text_)
			{
				return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbadd__control__string__ret__scalar, control_, text_));
			}

			float lb_color(float control_id_, float index_)
			{
				game_value args({
					(control_id_),
					(index_)
				});

				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbcolor__array__ret__array, args));
			}

			float lb_color(control control_, float index_)
			{
				return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbcolor__control__scalar__ret__array, control_, index_));
			}

			float lb_color_right(float control_id_, float index_)
			{
				game_value args({
					(control_id_),
					(index_)
				});

				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbcolorright__array__ret__array, args));
			}

			float lb_color_right(control control_, float index_)
			{
				return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbcolorright__control__scalar__ret__array, control_, index_));
			}

			std::string lb_data(float control_id_, float index_)
			{
				game_value args({
					(control_id_),
					(index_)
				});

				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbdata__array__ret__string, args));
			}

			std::string lb_data(control control_, float index_)
			{
				return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbdata__control__scalar__ret__string, control_, index_));
			}

			void lb_delete(float control_id_, float index_)
			{
				game_value args({
					(control_id_),
					(index_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbdelete__array__ret__nothing, args);
			}

			void lb_delete(control control_, float index_)
			{
				host::functions.invoke_raw_binary(client::__sqf::binary__lbdelete__control__scalar__ret__nothing, control_, index_);
			}

			std::string lb_picture(float control_id_, float index_)
			{
				game_value args({
					(control_id_),
					(index_)
				});

				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbpicture__array__ret__string, args));
			}

			std::string lb_picture(control control_, float index_)
			{
				return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbpicture__control__scalar__ret__string, control_, index_));
			}

			std::string lb_picture_right(float control_id_, float index_)
			{
				game_value args({
					(control_id_),
					(index_)
				});

				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbpictureright__array__ret__string, args));
			}

			std::string lb_picture_right(control control_, float index_)
			{
				return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbpictureright__control__scalar__ret__string, control_, index_));
			}

			std::vector<float> lb_selection(control control_); // USE lb_cur_sel IN A3 https://community.bistudio.com/wiki/lbSelection

			void lb_set_color(float control_id_, float index_, rv_color color_)
			{
				game_value args({
					(control_id_),
					(index_),
					color_.__to_gv_vector()
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsetcolor__array__ret__nothing, args);
			}

			void lb_set_color(control control_, float index_, rv_color color_)
			{
				game_value args({
					(index_),
					color_.__to_gv_vector()
				});

				host::functions.invoke_raw_binary(client::__sqf::binary__lbsetcolor__control__array__ret__nothing, control_, args);
			}

			void lb_set_color_right(float control_id_, float index_, rv_color color_)
			{
				game_value args({
					(control_id_),
					(index_),
					color_.__to_gv_vector()
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsetcolorright__array__ret__nothing, args);
			}

			void lb_set_color_right(control control_, float index_, rv_color color_)
			{
				game_value args({
					(index_),
					color_.__to_gv_vector()
				});

				host::functions.invoke_raw_binary(client::__sqf::binary__lbsetcolorright__control__array__ret__nothing, control_, args);
			}

			void lb_set_cur_sel(float control_id_, float index_)
			{
				game_value args({
					(control_id_),
					(index_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsetcursel__array__ret__nothing, args);
			}

			void lb_set_cur_sel(control control_, float index_)
			{
				host::functions.invoke_raw_binary(client::__sqf::binary__lbsetcursel__control__scalar__ret__nothing, control_, index_);
			}

			void lb_set_data(float control_id_, float index_, std::string data_)
			{
				game_value args({
					(control_id_),
					(index_),
					data_
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsetdata__array__ret__nothing, args);
			}


			void lb_set_data(control control_, float index_, std::string data_)
			{
				game_value args({
					(index_),
					(data_)
				});

				host::functions.invoke_raw_binary(client::__sqf::binary__lbsetdata__control__array__ret__nothing, control_, args);
			}

			void lb_set_picture(float control_id_, float index_, std::string name_)
			{
				game_value args({
					(control_id_),
					(index_),
					name_
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicture__array__ret__nothing, args);
			}

			void lb_set_picture(control control_, float index_, std::string name_)
			{
				game_value args({
					(index_),
					(name_)
				});

				host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicture__control__array__ret__nothing, control_, args);
			}

			void lb_set_picture_right(float control_id_, float index_, std::string name_)
			{
				game_value args({
					(control_id_),
					(index_),
					name_
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpictureright__array__ret__nothing, args);
			}

			void lb_set_picture_right(control control_, float index_, std::string name_)
			{
				game_value args({
					(index_),
					(name_)
				});

				host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpictureright__control__array__ret__nothing, control_, args);
			}

			void lb_set_picture_color(float control_id_, float index_, rv_color color_) 
			{
				game_value args({
					(control_id_),
					(index_),
					color_.__to_gv_vector()
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicturecolor__array__ret__nothing, args);
			}


			void lb_set_picture_color(control control_, float index_, rv_color color_)
			{
				game_value args({
					(index_),
					color_.__to_gv_vector()
				});

				host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturecolor__control__array__ret__nothing, control_, args);
			}

			void lb_set_picture_color_disabled(float control_id_, float index_, rv_color color_)
			{
				game_value args({
					(control_id_),
					(index_),
					color_.__to_gv_vector()
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicturecolordisabled__array__ret__nothing, args);
			}

			void lb_set_picture_color_disabled(control control_, float index_, rv_color color_)
			{
				game_value args({
					(index_),
					color_.__to_gv_vector()
				});

				host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturecolordisabled__control__array__ret__nothing, control_, args);
			}

			void lb_set_picture_color_selected(float control_id_, float index_, rv_color color_)
			{
				game_value args({
					(control_id_),
					(index_),
					color_.__to_gv_vector()
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicturecolorselected__array__ret__nothing, args);
			}

			void lb_set_picture_color_selected(control control_, float index_, rv_color color_)
			{
				game_value args({
					(index_),
					color_.__to_gv_vector()
				});

				host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturecolorselected__control__array__ret__nothing, control_, args);
			}

			void lb_set_tooltip(float control_id_, float index_, std::string tooltip_) 
			{
				game_value args({
					(control_id_),
					(index_),
					tooltip_
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsettooltip__array__ret__nothing, args);
			}

			void lb_set_tooltip(control control_, float index_, std::string tooltip_)
			{
				game_value args({
					(index_),
					(tooltip_)
				});

				host::functions.invoke_raw_binary(client::__sqf::binary__lbsettooltip__control__array__ret__nothing, control_, args);
			}

			void lb_set_value(float control_id_, float index_, float val_)
			{
				game_value args({
					(control_id_),
					(index_),
					val_
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsettooltip__array__ret__nothing, args);
			}

			void lb_set_value(control control_, float index_, float val_)
			{
				game_value args({
					(index_),
					(val_)
				});

				host::functions.invoke_raw_binary(client::__sqf::binary__lbsetvalue__control__array__ret__nothing, control_, args);
			}

			void lb_sort(control control_) 
			{
				host::functions.invoke_raw_unary(client::__sqf::unary__lbsort__control__ret__scalar, control_);
			}

			void lb_sort(control control_, std::string sort_order_)
			{
				game_value args({
					(control_),
					(sort_order_)
				});

				host::functions.invoke_raw_unary(client::__sqf::unary__lbsort__array__ret__scalar, args);
			}

			std::string lb_text(float control_id_, float index_)
			{
				game_value args({
					(control_id_),
					(index_)
				});

				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbtext__array__ret__string, args));
			}

			std::string lb_text(control control_, float index_)
			{
				return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbtext__control__scalar__ret__string, control_, index_));
			}

			std::string lb_text_right(float control_id_, float index_)
			{
				game_value args({
					(control_id_),
					(index_)
				});

				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbtextright__array__ret__string, args));
			}

			std::string lb_text_right(control control_, float index_)
			{
				return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbtextright__control__scalar__ret__string, control_, index_));
			}

			float lb_value(float control_id_, float index_)
			{
				game_value args({
					(control_id_),
					(index_)
				});

				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbtextright__array__ret__string, args));
			}

			float lb_value(control control_, float index_)
			{
				return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbvalue__control__scalar__ret__scalar, control_, index_));
			}

			/*************************************************************** LISTBOX END *****************************************************************************/
		}
	}
}
