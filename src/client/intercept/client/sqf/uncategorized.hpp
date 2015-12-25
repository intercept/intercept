/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Uncategorized

Lacking a specific category or have not been assigned to a category yet.

Similar to misc.hpp but not... Kind of... These are both a mess.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
	namespace sqf {
		struct rv_bounding_box
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
					red,
					blue,
					green,
					alpha
				});
			}

		};

        void draw_line_3d(const vector3 &pos1_, const vector3 &pos2_, const rv_color &color_);
        /*
        texture: String
        color: Color
        pos: PositionAGL
        width: Number
        height: Number
        angle: Number
        text: String - (optional)
        shadow: Number - (optional)
        textSize: Number - (optional)
        font: String - (optional)
        textAlign: String - (optional)
        drawSideArrows: Boolean - (optional)
        */
        void draw_icon_3d(
            const std::string &texture_,
            const rv_color &color_,
            const vector3 &pos_agl_,
            const float width_,
            const float height_,
            const float angle_,
            const std::string &text_ = "",
            const bool shadow_ = false,
            const float text_size_ = 1.0f,
            const std::string &font_ = "TahomaB"
            );
		/* potential namespace: */
		std::vector<std::string> action_keys(const std::string &user_action_);

		//text action_keys_images(const std::string &user_action_);

		std::string action_keys_names(const std::string &user_action_);
		std::string action_keys_names(const std::string &user_action_, int max_keys_);
		std::string action_keys_names(const std::string &user_action_, int max_keys_, const std::string &input_device_priority_);

		std::vector<std::string> action_keys_names_array(const std::string &user_action_);
		std::vector<std::string> action_keys_names_array(const std::string &user_action_, int max_keys_);
		std::vector<std::string> action_keys_names_array(const std::string &user_action_, int max_keys_, const std::string &input_device_priority_);

		/* potential namespace: misc, missions */
		void activate_addons(std::vector<std::string> &addons_);

		/* potential namespace: camera */
		void add_cam_shake(float power_, float duration_, float frequency_);

		/* potential namespace: items, inventory, campaign */
		void add_item_pool(const std::string &item_name_, int item_count_);
		void add_magazine_pool(const std::string &mag_name_, int mag_count_);

		/* potential namespace: core, misc, world */
		void add_to_remains_collector(std::vector<object> objects_);

		/* potential namespace: medical, misc, unit */
		void ais_finish_heal(const object &wounded_, const object &medic_, bool medic_can_heal_);

		/* potential namespace: core, display, all */
		std::vector<control> all_controls(const display &display_); // TODO implement all_controls

		/* potential namespace: core, all */
		std::vector<object> all_mission_objects(const std::string &type_);

		/* potential namespace: vehicle, core, cargo */
		std::vector<object> assigned_cargo(const object &veh_);
		std::vector<std::string> assigned_items(const object &unit_);

		/* potential namespace: misc, attach */
		object attached_object(const location &loc_);
		std::vector<object> attached_objects(const object &obj_);
		object attached_to(const object &obj_);

		/* potential namespace: ai */
		bool attack_enabled(const object &unit_);
		bool attack_enabled(const group &group_);

		/* potential namespace: cargo */
		std::vector<std::string> backpack_cargo(const object &box_);
		std::vector<std::string> backpack_items(const object &unit_);
		std::vector<std::string> backpack_magazines(const object &unit_);

		/* potential namespace: misc, model, position? */
		sqf::rv_bounding_box bounding_box(const object &model_);
		sqf::rv_bounding_box bounding_box_real(const object &model_);
		vector3 bounding_center(const object &obj_);

		/* potential namespace: controls, ui, gui, misc */
		void button_set_action(int control_id_, const std::string &code_);
		void button_set_action(const control &control_, const std::string &code_);
		void ctrl_enable(int control_id_, bool enable_);
		void ctrl_enable(const control &control_, bool enable_);

		/* potential namespace: locations */
		std::string class_name(const location &loc_);
		location create_location(const std::string &classname_, const vector3 &pos_, float size_x_, float size_y_);
		location create_location(const std::string &classname_, vector2 pos_, float size_x_, float size_y_);
		location create_location(const std::string &classname_, const object &obj_, float size_x_, float size_y_);

		/* potential namespace: ai, group, unit */
		std::string combat_mode(const group &loc_);
		std::string combat_mode(const object &loc_);

		/* potential namespace: ai */
		void command_get_out(const object &unit_);
		void command_get_out(std::vector<object> units_);
		void command_stop(const object &unit_);
		void command_stop(std::vector<object> units_);

		/* potential namespace: core, create */
		object create_agent(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f, const std::string &special_ = "NONE");
		object create_mine(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f);
		object create_sound_source(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f);
		object create_trigger(const std::string &type_, const vector3 &pos_, bool make_global_ = true);
		object create_trigger(const std::string &type_, const object &pos_, bool make_global_ = true);

		/* potential namespace: core, create, teams */
		team_member create_team(const std::string &type_, const std::string &name_);

		/* potential namespace: gui, ui */
		void create_gear_dialog(const object &unit_, const std::string &resource_);

		/* potential namespace: misc */
		void create_guarded_point(const side &side_, const vector3 &pos_, float idstatic_, const object &veh_);

		/* potential namespace: vehicle */
		std::vector<object> crew(object _veh);

		/* potential namespace: magazine, items, inventory */
		std::string current_magazine_detail(const object &veh_);

		/* potential namespace: teams */
		std::vector<task> current_tasks(const team_member &team_member_);

		/* potential namespace: gui, ui */
		void cut_obj(const std::string &name_, const std::string &type_, float speed_ = 1.0f);
		void cut_rsc(const std::string &name_, const std::string &type_, float speed_ = 1.0f, bool show_on_map_ = false);
		void cut_text(const std::string &name_, const std::string &type_, float speed_ = 1.0f, bool show_on_map_ = false);
		void enable_debriefing_stats(float left_, float top_, float width_, float height_);

		/* potential namespace: misc */
		void enable_saving(bool enable_);
		void enable_saving(bool enable_, bool autosave_);
			
		/* potential namespace: rtd, vehicles, afm */
		std::vector<bool> engines_is_on_rtd(const object &helicopter_);
		std::vector<float> engines_torque_rtd(const object &helicopter_);
		std::vector<float> engines_rpm_rtd(const object &helicopter_);

		/* potential namespace: core */
		std::vector<object> entities(const std::string &type_);

		/* potential namespace: backpack, containers, inventory */
		std::vector<object> every_backpack(const object &box_);

		/* potential namespace: containers, inventory */
		std::vector<rv_container> every_container(const object &box_);

		/* potential namespace: ai */
		rv_destination expected_destination(const object &unit_);

		/* potential namespace: position */
		vector3 eye_direction(const object &unit_);
		vector3 eye_pos(const object &unit_);

		/* potential namespace: groups, ai */
		std::string formation(const object &leader_);
		std::string formation(const group &group_);

		std::vector<object> formation_members(const object &unit_);
		vector3 formation_position(const object &unit_);
			
		/* Potential namespace: core */
		std::vector<rv_crew_member> full_crew(const object &veh_, const std::string &filter_ = "");

		/* potential namespace: misc */
		std::vector<std::string> get_artillery_ammo(const std::vector<object> &units_);

		/* potential namespace: physics, physx, core */
		vector3 get_center_of_mass(const object &obj_);

		/* potential namespace: misc */
		std::vector<float> get_dlcs(float filter_);

		/* potential namespace: dialogs, ui, listbox */
		float lb_add(int control_id_, const std::string &text_);
		float lb_add(const control &control_, const std::string &text_);
		float lb_color(int control_id_, int index_);
		float lb_color(const control &control_, int index_);
		float lb_color_right(int control_id_, int index_);
		float lb_color_right(const control &control_, int index_);
		std::string lb_data(int control_id_, int index_);
		std::string lb_data(const control &control_, int index_);
		void lb_delete(int control_id_, int index_);
		void lb_delete(const control &control_, int index_);
		std::string lb_picture(int control_id_, int index_);
		std::string lb_picture(const control &control_, int index_);
		std::string lb_picture_right(int control_id_, int index_);
		std::string lb_picture_right(const control &control_, int index_);
		std::vector<float> lb_selection(const control &control_); // USE lb_cur_sel IN A3 https://community.bistudio.com/wiki/lbSelection
		void lb_set_color(int control_id_, int index_, rv_color color_);
		void lb_set_color(const control &control_, int index_, rv_color color_);
		void lb_set_color_right(int control_id_, int index_, rv_color color_);
		void lb_set_color_right(const control &control_, int index_, rv_color color_);
		void lb_set_cur_sel(int control_id_, int index_);
		void lb_set_cur_sel(const control &control_, int index_);
		void lb_set_data(int control_id_, int index_, const std::string &data_);
		void lb_set_data(const control &control_, int index_, const std::string &data_);
		void lb_set_picture(int control_id_, int index_, const std::string &name_);
		void lb_set_picture(const control &control_, int index_, const std::string &name_);
		void lb_set_picture_right(int control_id_, int index_, const std::string &name_);
		void lb_set_picture_right(const control &control_, int index_, const std::string &name_);
		void lb_set_picture_color(int control_id_, int index_, rv_color color_);
		void lb_set_picture_color(const control &control_, int index_, rv_color color_);
		void lb_set_picture_color_disabled(int control_id_, int index_, rv_color color_);
		void lb_set_picture_color_disabled(const control &control_, int index_, rv_color color_);
		void lb_set_picture_color_selected(int control_id_, int index_, rv_color color_);
		void lb_set_picture_color_selected(const control &control_, int index_, rv_color color_);
		void lb_set_tooltip(int control_id_, int index_, const std::string &tooltip_);
		void lb_set_tooltip(const control &control_, int index_, const std::string &tooltip_);
		void lb_set_value(int control_id_, int index_, float val_);
		void lb_set_value(const control &control_, int index_, float val_);
		void lb_sort(const control &control_);
		void lb_sort(const control &control_, const std::string &sort_order_);
		std::string lb_text(int control_id_, int index_);
		std::string lb_text(const control &control_, int index_);
		std::string lb_text_right(int control_id_, int index_);
		std::string lb_text_right(const control &control_, int index_);
		float lb_value(int control_id_, int index_);
		float lb_value(const control &control_, int index_);

	}
}
