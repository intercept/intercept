#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
	namespace sqf {
		struct bounding_box
		{
			vector3 min;
			vector3 max;
		};

		struct rv_container
		{
			std::string type;
			object container;
		};

		struct rv_destination
		{
			vector3 pos;
			std::string planning_mode;
			bool force_replan;
		};

		struct rv_crew_member
		{
			object unit;
			std::string role;
			float cargo_index;
			// turret path; // TODO
			bool person_turret;
		};

		struct rv_color
		{
			float red;
			float blue;
			float green;
			float alpha;

			std::vector<game_value> __to_gv_vector() const
			{
				return std::vector<game_value> ({
					game_value(red),
					game_value(blue),
					game_value(green),
					game_value(alpha)
				});
			}
		};

		namespace __uncategorized {
			/* potential namespace: */
			std::vector<std::string> action_keys(std::string user_action_);

			text action_keys_images(std::string user_action_);

			std::string action_keys_names(std::string user_action_);
			std::string action_keys_names(std::string user_action_, int max_keys_);
			std::string action_keys_names(std::string user_action_, int max_keys_, std::string input_device_priority_);

			std::vector<std::string> action_keys_names_array(std::string user_action_);
			std::vector<std::string> action_keys_names_array(std::string user_action_, int max_keys_);
			std::vector<std::string> action_keys_names_array(std::string user_action_, int max_keys_, std::string input_device_priority_);

			/* potential namespace: misc, missions */
			void activate_addons(std::vector<std::string> &addons_);

			/* potential namespace: camera */
			void add_cam_shake(float power_, float duration_, float frequency_);

			/* potential namespace: items, inventory, campaign */
			void add_item_pool(std::string item_name_, int item_count_);
			void add_magazine_pool(std::string mag_name_, int mag_count_);

			/* potential namespace: core, misc, world */
			void add_to_remains_collector(std::vector<object> objects_);

			/* potential namespace: medical, misc, unit */
			void ais_finish_heal(object &wounded_, const object &medic_, bool medic_can_heal_);

			/* potential namespace: core, display, all */
			std::vector<control> all_controls(display display_); // TODO implement all_controls

			/* potential namespace: core, all */
			std::vector<object> all_mission_objects(std::string type_);

			/* potential namespace: vehicle, core, cargo */
			std::vector<object> assigned_cargo(object veh_);
			std::vector<std::string> assigned_items(object unit_);

			/* potential namespace: misc, attach */
			object attached_object(location loc_);
			std::vector<object> attached_objects(object obj_);
			object attached_to(object obj_);

			/* potential namespace: ai */
			bool attack_enabled(object unit_);
			bool attack_enabled(group group_);

			/* potential namespace: cargo */
			std::vector<std::string> backpack_cargo(object box_);
			std::vector<std::string> backpack_items(object unit_);
			std::vector<std::string> backpack_magazines(object unit_);

			/* potential namespace: misc, model, position? */
			sqf::bounding_box bounding_box(object model_);
			sqf::bounding_box bounding_box_real(object model_);
			vector3 bounding_center(object obj_);

			/* potential namespace: controls, ui, gui, misc */
			void button_set_action(int control_id_, std::string code_);
			void button_set_action(control control_, std::string code_);
			void ctrl_enable(int control_id_, bool enable_);
			void ctrl_enable(control control_, bool enable_);
			void ctrl_set_text(int control_id_, std::string code_);
			void ctrl_set_text(control control_, std::string code_);
			void ctrl_show(int control_id_, bool show_);
			void ctrl_show(control control_, bool show_);

			/* potential namespace: locations */
			std::string class_name(location loc_);
			location create_location(std::string classname_, vector3 pos_, float size_x_, float size_y_);
			location create_location(std::string classname_, vector2 pos_, float size_x_, float size_y_);
			location create_location(std::string classname_, const object &obj_, float size_x_, float size_y_);

			/* potential namespace: ai, group, unit */
			std::string combat_mode(group loc_);
			std::string combat_mode(object loc_);

			/* potential namespace: ai */
			void command_get_out(object unit_);
			void command_get_out(std::vector<object> units_);
			void command_stop(object unit_);
			void command_stop(std::vector<object> units_);

			/* potential namespace: core, create */
			object create_agent(std::string type_, vector3 pos_, std::vector<marker> markers_ = {}, float placement_ = 0.0f, std::string special_ = "NONE");
			object create_mine(std::string type_, vector3 pos_, std::vector<marker> markers_ = {}, float placement_ = 0.0f);
			object create_sound_source(std::string type_, vector3 pos_, std::vector<marker> markers_ = {}, float placement_ = 0.0f);
			object create_trigger(std::string type_, vector3 pos_, bool make_global_ = true);
			object create_trigger(std::string type_, const object &pos_, bool make_global_ = true);

			/* potential namespace: core, create, teams */
			team_member create_team(std::string type_, std::string name_);

			/* potential namespace: gui, ui */
			void create_gear_dialog(object unit_, std::string resource_);

			/* potential namespace: misc */
			void create_guarded_point(side side_, vector3 pos_, float idstatic_, const object &veh_);

			/* potential namespace: vehicle */
			std::vector<object> crew(object _veh);

			/* potential namespace: magazine, items, inventory */
			std::string current_magazine_detail(object veh_);

			/* potential namespace: teams */
			std::vector<task> current_tasks(team_member team_member_);

			/* potential namespace: gui, ui */
			void cut_obj(std::string name_, std::string type_, float speed_ = 1.0f);
			void cut_rsc(std::string name_, std::string type_, float speed_ = 1.0f, bool show_on_map_ = false);
			void cut_text(std::string name_, std::string type_, float speed_ = 1.0f, bool show_on_map_ = false);
			void enable_debriefing_stats(float left_, float top_, float width_, float height_);

			/* potential namespace: misc */
			void enable_saving(bool enable_);
			void enable_saving(bool enable_, bool autosave_);
			
			/* potential namespace: rtd, vehicles, afm */
			std::vector<bool> engines_is_on_rtd(object helicopter_);
			std::vector<float> engines_torque_rtd(object helicopter_);
			std::vector<float> engines_rpm_rtd(object helicopter_);

			/* potential namespace: core */
			std::vector<object> entities(std::string type_);

			/* potential namespace: backpack, containers, inventory */
			std::vector<object> every_backpack(object box_);

			/* potential namespace: containers, inventory */
			std::vector<rv_container> every_container(object box_);

			/* potential namespace: ai */
			rv_destination expected_destination(object unit_);

			/* potential namespace: position */
			vector3 eye_direction(object unit_);
			vector3 eye_pos(object unit_);

			/* potential namespace: groups, ai */
			std::string formation(object leader_);
			std::string formation(group group_);

			std::vector<object> formation_members(object unit_);
			vector3 formation_position(object unit_);
			
			/* Potential namespace: core */
			std::vector<rv_crew_member> full_crew(object veh_, const std::string &filter_ = "");

			/* potential namespace: misc */
			std::vector<std::string> get_artillery_ammo(const std::vector<object> &units_);

			/* potential namespace: physics, physx, core */
			vector3 get_center_of_mass(object obj_);

			/* potential namespace: misc */
			std::vector<float> get_dlcs(float filter_);

			/* potential namespace: dialogs, ui, listbox */
			float lb_add(int control_id_, std::string text_);
			float lb_add(control control_, std::string text_);
			float lb_color(int control_id_, int index_);
			float lb_color(control control_, int index_);
			float lb_color_right(int control_id_, int index_);
			float lb_color_right(control control_, int index_);
			std::string lb_data(int control_id_, int index_);
			std::string lb_data(control control_, int index_);
			void lb_delete(int control_id_, int index_);
			void lb_delete(control control_, int index_);
			std::string lb_picture(int control_id_, int index_);
			std::string lb_picture(control control_, int index_);
			std::string lb_picture_right(int control_id_, int index_);
			std::string lb_picture_right(control control_, int index_);
			std::vector<float> lb_selection(control control_); // USE lb_cur_sel IN A3 https://community.bistudio.com/wiki/lbSelection
			void lb_set_color(int control_id_, int index_, rv_color color_);
			void lb_set_color(control control_, int index_, rv_color color_);
			void lb_set_color_right(int control_id_, int index_, rv_color color_);
			void lb_set_color_right(control control_, int index_, rv_color color_);
			void lb_set_cur_sel(int control_id_, int index_);
			void lb_set_cur_sel(control control_, int index_);
			void lb_set_data(int control_id_, int index_, std::string data_);
			void lb_set_data(control control_, int index_, std::string data_);
			void lb_set_picture(int control_id_, int index_, std::string name_);
			void lb_set_picture(control control_, int index_, std::string name_);
			void lb_set_picture_right(int control_id_, int index_, std::string name_);
			void lb_set_picture_right(control control_, int index_, std::string name_);
			void lb_set_picture_color(int control_id_, int index_, rv_color color_);
			void lb_set_picture_color(control control_, int index_, rv_color color_);
			void lb_set_picture_color_disabled(int control_id_, int index_, rv_color color_);
			void lb_set_picture_color_disabled(control control_, int index_, rv_color color_);
			void lb_set_picture_color_selected(int control_id_, int index_, rv_color color_);
			void lb_set_picture_color_selected(control control_, int index_, rv_color color_);
			void lb_set_tooltip(int control_id_, int index_, std::string tooltip_);
			void lb_set_tooltip(control control_, int index_, std::string tooltip_);
			void lb_set_value(int control_id_, int index_, float val_);
			void lb_set_value(control control_, int index_, float val_);
			void lb_sort(control control_);
			void lb_sort(control control_, std::string sort_order_);
			std::string lb_text(int control_id_, int index_);
			std::string lb_text(control control_, int index_);
			std::string lb_text_right(int control_id_, int index_);
			std::string lb_text_right(control control_, int index_);
			float lb_value(int control_id_, int index_);
			float lb_value(control control_, int index_);


		}
	}
}
