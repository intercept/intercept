#include "uncategorized.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"


using namespace intercept::types;

namespace intercept {
	namespace sqf {
		std::vector<std::string> action_keys(const std::string &user_action_)
		{
			game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeys__string__ret__array, user_action_);
			std::vector<std::string> r_arr = __helpers::__convert_to_strings_vector(act_keys);

			host::functions.free_value(&act_keys);
			return r_arr;
		}

		text action_keys_images(const std::string &user_action_)
		{
			return text(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysimages__string_array__ret__text, user_action_));
		}

		std::string action_keys_names(const std::string &user_action_)
		{
			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnames__string_array__ret__string, user_action_));
		}

		std::string action_keys_names(const std::string &user_action_, int max_keys_)
		{
			std::vector<game_value> params{ user_action_, game_value((float)max_keys_) };
			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnames__string_array__ret__string, params));
		}
		std::string action_keys_names(const std::string &user_action_, int max_keys_, const std::string &input_device_priority_)
		{
			game_value params({
				user_action_,
				(float)max_keys_,
				input_device_priority_
			});

			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnames__string_array__ret__string, params));
		}
			
		std::vector<std::string> action_keys_names_array(const std::string &user_action_)
		{
			game_value act_keys = host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnamesarray__string_array__ret__array, user_action_);
			std::vector<std::string> r_arr = __helpers::__convert_to_strings_vector(act_keys);

			host::functions.free_value(&act_keys);
			return r_arr;
		}

		std::vector<std::string> action_keys_names_array(const std::string &user_action_, int max_keys_)
		{
			std::vector<game_value> params{ user_action_, game_value((float)max_keys_) };

			return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnamesarray__string_array__ret__array, params));
		}
		std::vector<std::string> action_keys_names_array(const std::string &user_action_, int max_keys_, const std::string &input_device_priority_)
		{
			game_value params({
				user_action_,
				(float)max_keys_,
				input_device_priority_
			});

			return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__actionkeysnamesarray__string_array__ret__array, params));
		}

		void activate_addons(std::vector<std::string> &addons_)
		{
            std::vector<game_value> addons;
            for (auto it : addons_)
                addons.push_back(it);

			host::functions.invoke_raw_unary(client::__sqf::unary__activateaddons__array__ret__nothing, addons);
		}

		/* potential namespace: camera */
		void add_cam_shake(float power_, float duration_, float frequency_)
		{
			std::vector<game_value> params{ power_, duration_, frequency_ };

			host::functions.invoke_raw_unary(client::__sqf::unary__addcamshake__array__ret__nothing, params);
		}

		/* potential namespace: items, inventory, campaign */
		void add_item_pool(const std::string &item_name_, int item_count_)
		{
			std::vector<game_value> params{ item_name_, game_value((float)item_count_) };

			host::functions.invoke_raw_unary(client::__sqf::unary__additempool__array__ret__nothing, params);
		}

		void add_magazine_pool(const std::string &mag_name_, int mag_count_)
		{
			std::vector<game_value> params{ mag_name_, game_value((float)mag_count_) };
			host::functions.invoke_raw_unary(client::__sqf::unary__addmagazinepool__array__ret__nothing, params);
		}

		void add_to_remains_collector(std::vector<object> objects_)
		{
            std::vector<game_value> objects;
            for (auto &it : objects_)
                objects.push_back(it);
            host::functions.invoke_raw_unary(client::__sqf::unary__addtoremainscollector__array__ret__nothing, objects);
		}

		void ais_finish_heal(const object &wounded_, const object &medic_, bool medic_can_heal_)
		{
			game_value params(std::vector<game_value>{
				wounded_,
                medic_,
				medic_can_heal_
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__aisfinishheal__array__ret__nothing, params);
		}

		std::vector<object> all_mission_objects(const std::string &type_)
		{
			return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__allmissionobjects__string__ret__array, type_));
		}

		std::vector<object> assigned_cargo(const object &veh_)
		{
			return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__assignedcargo__object__ret__array, veh_));
		}

		std::vector<std::string> assigned_items(const object &unit_)
		{
			return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__assigneditems__object__ret__array, unit_));
		}

		object attached_object(const location &loc_)
		{
			return object(host::functions.invoke_raw_unary(client::__sqf::unary__attachedobject__location__ret__object, loc_));
		}

		std::vector<object> attached_objects(const object &obj_)
		{
			return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(client::__sqf::unary__attachedobjects__object__ret__array, obj_));
		}

		object attached_to(const object &obj_)
		{
			return object(host::functions.invoke_raw_unary(client::__sqf::unary__attachedto__object__ret__array, obj_));
		}

		bool attack_enabled(const object &unit_)
		{
			return __helpers::__bool_unary_object(client::__sqf::unary__attackenabled__object_group__ret__bool, unit_);
		}

		bool attack_enabled(const group &group_)
		{
			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__attackenabled__object_group__ret__bool, group_));
		}

		std::vector<std::string> backpack_cargo(const object &box_)
		{
			return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackcargo__object__ret__array, box_));
		}

		std::vector<std::string> backpack_items(const object &unit_)
		{
			return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackitems__object__ret__array, unit_));
		}

		std::vector<std::string> backpack_magazines(const object &unit_)
		{
			return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__backpackmagazines__object__ret__array, unit_));
		}

		sqf::rv_bounding_box bounding_box(const object &model_)
		{
			//game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__boundingbox__object__ret__array, model_);
			//game_data_array* array_value = ((game_data_array *)input.data);

			//sqf::rv_bounding_box bb;

			//float x_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[0].data)->number;
			//float y_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[1].data)->number;
			//float z_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[2].data)->number;
			//bb.min = vector3(x_min, y_min, z_min);

			//float x_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[0].data)->number;
			//float y_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[1].data)->number;
			//float z_max  = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[2].data)->number;
			//bb.min = vector3(x_max, y_max, z_max);

			//host::functions.free_value(&input);
			//return bb;
			throw 713; // TODO
		}

		sqf::rv_bounding_box bounding_box_real(const object &model_)
		{
			//game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__boundingboxreal__object__ret__array, model_);
			//game_data_array* array_value = ((game_data_array *)input.data);

			//sqf::rv_bounding_box bb;

			//float x_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[0].data)->number;
			//float y_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[1].data)->number;
			//float z_min = ((game_data_number *)((game_data_array *)array_value->data[0].data)->data[2].data)->number;
			//bb.min = vector3(x_min, y_min, z_min);

			//float x_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[0].data)->number;
			//float y_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[1].data)->number;
			//float z_max = ((game_data_number *)((game_data_array *)array_value->data[1].data)->data[2].data)->number;
			//bb.min = vector3(x_max, y_max, z_max);

			//host::functions.free_value(&input);
			//return bb;
			throw 713; // TODO
		}

		vector3 bounding_center(const object &obj_)
		{
			return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(client::__sqf::unary__boundingcenter__object__ret__array, obj_));
		}

		void button_set_action(int control_id_, const std::string &code_)
		{
			game_value params({
				(float)control_id_,
				code_
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__buttonsetaction__array__ret__nothing, params);
		}

		void button_set_action(const control &control_, const std::string &code_)
		{
			game_value params({
				control_,
				code_
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__buttonsetaction__array__ret__nothing, params);
		}

		// What a confusing command name.
		std::string class_name(const location &loc_)
		{
			return game_value( host::functions.invoke_raw_unary(client::__sqf::unary__classname__location__ret__string, loc_) );
		}

		std::string combat_mode(const group &grp_)
		{
			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__combatmode__object_group__ret__string, grp_));
		}

		std::string combat_mode(const object &unit_)
		{
			return __helpers::__string_unary_object(client::__sqf::unary__combatmode__object_group__ret__string, unit_);
		}

		void command_get_out(const object &unit_)
		{
			return __helpers::__empty_unary_object(client::__sqf::unary__commandgetout__object_array__ret__nothing, unit_);
		}

		void command_get_out(std::vector<object> units_)
		{
			//std::vector<game_value> units;
			//for (auto it : units)
			//	units.push_back(it);

			//__helpers::__empty_unary_object(client::__sqf::unary__commandgetout__object_array__ret__nothing, units);
			//TODO Implement command_get_out
			throw 713;
		}

		void command_stop(const object &unit_)
		{
			return __helpers::__empty_unary_object(client::__sqf::unary__commandstop__object_array__ret__nothing, unit_);
		}
		void command_stop(std::vector<object> units_)
		{
			throw 713; // TODO Implement command_stop
			//return __helpers::__empty_unary_object(client::__sqf::unary__commandstop__object_array__ret__nothing, unit_);
		}

		object create_agent(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_ /* = {}*/, float placement_ /*= 0.0f*/, const std::string &special_ /*= "NONE"*/)
		{
			std::vector<game_value> markers;
			for (auto &it : markers_)
				markers.push_back(it);

			game_value args({
				type_,
				pos_,
				markers,
				placement_,
				special_
			});

			return object(host::functions.invoke_raw_unary(__sqf::unary__createagent__array__ret__object, args));

		}

		void create_gear_dialog(const object &unit_, const std::string &resource_)
		{
			game_value params({
				unit_,
				resource_
			});

			host::functions.invoke_raw_unary(__sqf::unary__creategeardialog__array__ret__nothing, params);
		}

		void create_guarded_point(const side &side_, const vector3 &pos_, float idstatic_, const object &veh_)
		{
			game_value params({
				side_,
				pos_,
				idstatic_,
				veh_
			});

			host::functions.invoke_raw_unary(__sqf::unary__createguardedpoint__array__ret__nothing, params);
		}

		location create_location(const std::string &classname_, const vector3 &pos_, float size_x_, float size_y_)
		{
			game_value params({
				classname_,
				pos_,
				size_x_,
				size_y_
			});

			return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
		}

		location create_location(const std::string &classname_, vector2 pos_, float size_x_, float size_y_)
		{
			game_value params({
				classname_,
				pos_,
				size_x_,
				size_y_
			});

			return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
		}
		location create_location(const std::string &classname_, const object &obj_, float size_x_, float size_y_)
		{
			game_value params({
				classname_,
                obj_,
				size_x_,
				size_y_
			});

			return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
		}

		object create_mine(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_/* = {}*/, float placement_/* = 0.0f*/)
		{
			std::vector<game_value> markers;
			for (auto &it : markers_)
				markers.push_back(it);

			game_value args({
				type_,
				pos_,
				markers,
				placement_,
			});

			return object(host::functions.invoke_raw_unary(__sqf::unary__createmine__array__ret__object, args));
		}

		object create_sound_source(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_/* = {}*/, float placement_/* = 0.0f*/)
		{
			std::vector<game_value> markers;
			for (auto it : markers_)
				markers.push_back(it);

			game_value args({
				type_,
				pos_,
				markers,
				placement_,
			});

			return object(host::functions.invoke_raw_unary(__sqf::unary__createsoundsource__array__ret__object, args));
		}

		team_member create_team(const std::string &type_, const std::string &name_)
		{
			game_value args({
				(type_),
				(name_),
			});

			return team_member(host::functions.invoke_raw_unary(__sqf::unary__createteam__array__ret__team_member, args));
		}

		object create_trigger(const std::string &type_, const vector3 &pos_, bool make_global_/* = true*/)
		{
			game_value args({
				(type_),
				(pos_),
				(make_global_)
			});

			return object(host::functions.invoke_raw_unary(__sqf::unary__createtrigger__array__ret__object, args));
		}

		object create_trigger(const std::string &type_, const object &pos_, bool make_global_ /*= true*/)
		{
			game_value args({
				(type_),
				pos_,
				(make_global_)
			});

			return object(host::functions.invoke_raw_unary(__sqf::unary__createtrigger__array__ret__object, args));
		}

		std::vector<object> crew(object _veh)
		{
			return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__crew__object__ret__array, _veh));
		}

		std::string current_magazine_detail(const object &veh_)
		{
			return __helpers::__string_unary_object(client::__sqf::unary__currentmagazinedetail__object__ret__array, veh_);
		}
			
		std::vector<task> current_tasks(const team_member &team_member_)
		{
			game_value input = host::functions.invoke_raw_unary(client::__sqf::unary__currenttasks__team_member__ret__array, team_member_);

			std::vector<task> output;
			for (uint32_t i = 0; i < input.length(); ++i) {
				output.push_back(task(input[i].rv_data));
			}

			return output;
		}

		void cut_obj(const std::string &name_, const std::string &type_, float speed_)
		{
			game_value args({
				(name_),
				(type_),
				(speed_)
			});

			host::functions.invoke_raw_unary(__sqf::unary__cutobj__array__ret__nothing, args);
		}

		void cut_rsc(const std::string &name_, const std::string &type_, float speed_, bool show_on_map_)
		{
			game_value args({
				(name_),
				(type_),
				(speed_),
				(show_on_map_)
			});

			host::functions.invoke_raw_unary(__sqf::unary__cutrsc__array__ret__nothing, args);
		}

		void cut_text(const std::string &name_, const std::string &type_, float speed_, bool show_on_map_)
		{
			game_value args({
				(name_),
				(type_),
				(speed_),
				(show_on_map_)
			});

			host::functions.invoke_raw_unary(__sqf::unary__cuttext__array__ret__nothing, args);
		}

		void enable_debriefing_stats(float left_, float top_, float width_, float height_)
		{
			//game_value args({
			//	(left_),
			//	(top_),
			//	(width_),
			//	(height_)
			//});

			//host::functions.invoke_raw_unary(__sqf::unary__enabledebriefingstats__array__ret__nothing, args);
		}

		void enable_saving(bool enable_)
		{
			enable_saving(enable_, !enable_);
		}

		void enable_saving(bool enable_, bool autosave_)
		{
			//game_value args({
			//	(enable_),
			//	(autosave_)
			//});

			//host::functions.invoke_raw_unary(__sqf::unary__enablesaving__bool_array__ret__nothing, args);
		}

		std::string formation(const object &leader_)
		{
			return game_value(host::functions.invoke_raw_unary(__sqf::unary__formation__object_group__ret__string, leader_));
		}

		std::string formation(const group &group_)
		{
			return game_value(host::functions.invoke_raw_unary(__sqf::unary__formation__object_group__ret__string, group_));
		}

		std::vector<object> formation_members(const object &unit_)
		{
			return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__formationmembers__object__ret__array, unit_));
		}

		vector3 formation_position(const object &unit_)
		{
			return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(__sqf::unary__formationposition__object__ret__array, unit_));
		}

		std::vector<rv_crew_member> full_crew(const object &veh_, const std::string & filter_)
		{
			//game_value crew_list;

			//if (filter_ == "")
			//{
			//	crew_list = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__object__ret__array, veh_);
			//}
			//else
			//{
			//	game_value args({
			//		veh_,
			//		(filter_)
			//	});

			//	crew_list = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__array__ret__array, args);
			//}

			//game_data_array* gd_array = ((game_data_array *)crew_list.data);
			//std::vector<rv_crew_member> output;
			//for (uint32_t i = 0; i < gd_array->length; ++i) {

			//	rv_crew_member crew_m;

			//	crew_m.unit = object(((game_data_array *)gd_array->data[i].data)->data[0]);
			//	crew_m.role = ((game_data_string *)((game_data_array *)gd_array->data[i].data)->data[1].data)->get_string();
			//	crew_m.cargo_index = ((game_data_number *)((game_data_array *)gd_array->data[i].data)->data[2].data)->number;
			//	// Turret path
			//	crew_m.person_turret = ((game_data_bool *)((game_data_array *)gd_array->data[i].data)->data[4].data)->value;
			//	output.push_back(crew_m);
			//}

			//host::functions.free_value(&crew_list);
			//return output;

			throw 713; // TODO re-implement full_crew
		}

		std::vector<std::string> get_artillery_ammo(const std::vector<object>& units_)
		{
			std::vector<game_value> units;
			for (auto &it : units_)
				units.push_back(it);

			return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(client::__sqf::unary__getartilleryammo__array__ret__array, units));
		}

		vector3 get_center_of_mass(const object &obj_)
		{
			return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(client::__sqf::unary__getcenterofmass__object__ret__array, obj_));
		}

		std::vector<float> get_dlcs(float filter_)
		{
			return __helpers::__convert_to_numbers_vector(host::functions.invoke_raw_unary(client::__sqf::unary__getdlcs__scalar__ret__array, filter_));
		}

#pragma region listbox
		/****************************************************************************** LISTBOX ***************************************************************************/
		float lb_add(int control_id_, const std::string &text_)
		{
			game_value args({
				(float)(control_id_),
				(text_)
			});

			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbadd__array__ret__scalar, args));
		}

		float lb_add(const control &control_, const std::string &text_)
		{
			return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbadd__control__string__ret__scalar, control_, text_));
		}

		float lb_color(int control_id_, int index_)
		{
			std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbcolor__array__ret__array, args));
		}

		float lb_color(const control &control_, int index_)
		{
			return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbcolor__control__scalar__ret__array, control_, (float)index_));
		}

		float lb_color_right(int control_id_, int index_)
		{
			std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbcolorright__array__ret__array, args));
		}

		float lb_color_right(const control &control_, int index_)
		{
			return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbcolorright__control__scalar__ret__array, control_, (float)index_));
		}

		std::string lb_data(int control_id_, int index_)
		{
			std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbdata__array__ret__string, args));
		}

		std::string lb_data(const control &control_, int index_)
		{
			return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbdata__control__scalar__ret__string, control_, (float)index_));
		}

		void lb_delete(int control_id_, int index_)
		{
			std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

			host::functions.invoke_raw_unary(client::__sqf::unary__lbdelete__array__ret__nothing, args);
		}

		void lb_delete(const control &control_, int index_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__lbdelete__control__scalar__ret__nothing, control_, (float)index_);
		}

		std::string lb_picture(int control_id_, int index_)
		{
			std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbpicture__array__ret__string, args));
		}

		std::string lb_picture(const control &control_, int index_)
		{
			return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbpicture__control__scalar__ret__string, control_, (float)index_));
		}

		std::string lb_picture_right(int control_id_, int index_)
		{
			std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };
			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbpictureright__array__ret__string, args));
		}

		std::string lb_picture_right(const control &control_, int index_)
		{
			return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbpictureright__control__scalar__ret__string, control_, (float)index_));
		}

		std::vector<float> lb_selection(const control &control_); // USE lb_cur_sel IN A3 https://community.bistudio.com/wiki/lbSelection

		void lb_set_color(int control_id_, int index_, rv_color color_)
		{
			game_value args({
				(float)(control_id_),
				(float)(index_),
				color_.__to_gv_vector()
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__lbsetcolor__array__ret__nothing, args);
		}

		void lb_set_color(const control &control_, int index_, rv_color color_)
		{
			game_value args({
				(float)(index_),
				color_.__to_gv_vector()
			});

			host::functions.invoke_raw_binary(client::__sqf::binary__lbsetcolor__control__array__ret__nothing, control_, args);
		}

		void lb_set_color_right(int control_id_, int index_, rv_color color_)
		{
			game_value args({
				(float)(control_id_),
				(float)(index_),
				color_.__to_gv_vector()
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__lbsetcolorright__array__ret__nothing, args);
		}

		void lb_set_color_right(const control &control_, int index_, rv_color color_)
		{
			game_value args({
				(float)(index_),
				color_.__to_gv_vector()
			});

			host::functions.invoke_raw_binary(client::__sqf::binary__lbsetcolorright__control__array__ret__nothing, control_, args);
		}

		void lb_set_cur_sel(int control_id_, int index_)
		{
			std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };
			host::functions.invoke_raw_unary(client::__sqf::unary__lbsetcursel__array__ret__nothing, args);
		}

		void lb_set_cur_sel(const control &control_, int index_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__lbsetcursel__control__scalar__ret__nothing, control_, (float)index_);
		}

		void lb_set_data(int control_id_, int index_, const std::string &data_)
		{
			game_value args({
				(float)(control_id_),
				(float)(index_),
				data_
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__lbsetdata__array__ret__nothing, args);
		}


		void lb_set_data(const control &control_, int index_, const std::string &data_)
		{
			game_value args({
				(float)(index_),
				(data_)
			});

			host::functions.invoke_raw_binary(client::__sqf::binary__lbsetdata__control__array__ret__nothing, control_, args);
		}

		void lb_set_picture(int control_id_, int index_, const std::string &name_)
		{
			game_value args({
				(float)(control_id_),
				(float)(index_),
				name_
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicture__array__ret__nothing, args);
		}

		void lb_set_picture(const control &control_, int index_, const std::string &name_)
		{
			game_value args({
				(float)(index_),
				(name_)
			});

			host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicture__control__array__ret__nothing, control_, args);
		}

		void lb_set_picture_right(int control_id_, int index_, const std::string &name_)
		{
			game_value args({
				(float)(control_id_),
				(float)(index_),
				name_
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpictureright__array__ret__nothing, args);
		}

		void lb_set_picture_right(const control &control_, int index_, const std::string &name_)
		{
			game_value args({
				(float)(index_),
				(name_)
			});

			host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpictureright__control__array__ret__nothing, control_, args);
		}

		void lb_set_picture_color(int control_id_, int index_, rv_color color_)
		{
			game_value args({
				(float)(control_id_),
				(float)(index_),
				color_.__to_gv_vector()
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicturecolor__array__ret__nothing, args);
		}


		void lb_set_picture_color(const control &control_, int index_, rv_color color_)
		{
			game_value args({
				(float)(index_),
				color_.__to_gv_vector()
			});

			host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturecolor__control__array__ret__nothing, control_, args);
		}

		void lb_set_picture_color_disabled(int control_id_, int index_, rv_color color_)
		{
			game_value args({
				(float)(control_id_),
				(float)(index_),
				color_.__to_gv_vector()
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicturecolordisabled__array__ret__nothing, args);
		}

		void lb_set_picture_color_disabled(const control &control_, int index_, rv_color color_)
		{
			game_value args({
				(float)(index_),
				color_.__to_gv_vector()
			});

			host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturecolordisabled__control__array__ret__nothing, control_, args);
		}

		void lb_set_picture_color_selected(int control_id_, int index_, rv_color color_)
		{
			game_value args({
				(float)(control_id_),
				(float)(index_),
				color_.__to_gv_vector()
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__lbsetpicturecolorselected__array__ret__nothing, args);
		}

		void lb_set_picture_color_selected(const control &control_, int index_, rv_color color_)
		{
			game_value args({
				(float)(index_),
				color_.__to_gv_vector()
			});

			host::functions.invoke_raw_binary(client::__sqf::binary__lbsetpicturecolorselected__control__array__ret__nothing, control_, args);
		}

		void lb_set_tooltip(int control_id_, int index_, const std::string &tooltip_)
		{
			game_value args({
				(float)(control_id_),
				(float)(index_),
				tooltip_
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__lbsettooltip__array__ret__nothing, args);
		}

		void lb_set_tooltip(const control &control_, int index_, const std::string &tooltip_)
		{
			game_value args({
				(float)(index_),
				(tooltip_)
			});

			host::functions.invoke_raw_binary(client::__sqf::binary__lbsettooltip__control__array__ret__nothing, control_, args);
		}

		void lb_set_value(int control_id_, int index_, float val_)
		{
			std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_), val_ };

			host::functions.invoke_raw_unary(client::__sqf::unary__lbsetvalue__array__ret__nothing, args);
		}

		void lb_set_value(const control &control_, int index_, float val_)
		{
			std::vector<game_value> args{game_value((float)index_), val_ };

			host::functions.invoke_raw_binary(client::__sqf::binary__lbsetvalue__control__array__ret__nothing, control_, args);
		}

		void lb_sort(const control &control_) 
		{
			host::functions.invoke_raw_unary(client::__sqf::unary__lbsort__control__ret__scalar, control_);
		}

		void lb_sort(const control &control_, const std::string &sort_order_)
		{
			game_value args({
				control_,
				(sort_order_)
			});

			host::functions.invoke_raw_unary(client::__sqf::unary__lbsort__array__ret__scalar, args);
		}

		std::string lb_text(int control_id_, int index_)
		{
			std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbtext__array__ret__string, args));
		}

		std::string lb_text(const control &control_, int index_)
		{
			return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbtext__control__scalar__ret__string, control_, (float)index_));
		}

		std::string lb_text_right(int control_id_, int index_)
		{
			std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) };

			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbtextright__array__ret__string, args));
		}

		std::string lb_text_right(const control &control_, int index_)
		{
			return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbtextright__control__scalar__ret__string, control_, (float)index_));
		}

		float lb_value(int control_id_, int index_)
		{
			std::vector<game_value> args{ game_value((float)control_id_), game_value((float)index_) }; 

			return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lbvalue__array__ret__scalar, args));
		}

		float lb_value(const control &control_, int index_)
		{
			return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__lbvalue__control__scalar__ret__scalar, control_, (float)index_));
		}

		/*************************************************************** LISTBOX END *****************************************************************************/
#pragma endregion listbox 
	}
}
