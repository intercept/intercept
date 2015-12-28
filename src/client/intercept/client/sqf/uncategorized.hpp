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

        vector3 vector_dir(object obj_);
        vector3 vector_dir_visual(object obj_);
        vector3 selection_positon(object obj_, std::string selection_name_);

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
		
		
		/* 3den */
		std::string current3denoperation();
		object get3dencamera();
		bool get3deniconsvisible();
		bool get3denlinesvisible();
		// TODO array[] get_3den_mouse_over(); //      Array in format: [type,Eden Entity], where type can be: "Object", "Group", "Trigger", "Logic", "Waypoint" or "Marker"
		bool is3den();
		bool is3denmultiplayer();
		float get_3den_action_state(const std::string &value_);
		void edit_3den_mission_attributes(const std::string &value_);
		float add_3den_layer(float value0_, const std::string& value1_);
		bool remove_3den_layer(float value_);
		void remove_all_3den_eventhandlers(const std::string &value_);
		
		/* Chat */
		namespace __helpers {
			void chat_message(binary_function fnc_, const object &obj_, const std::string &message_);
		}
		void side_chat(const object & obj_, const std::string &message_);
		void global_chat(const object & obj_, const std::string & message_);
		void group_chat(const object & obj_, const std::string & message_);
		void vehicle_chat(const object & obj_, const std::string & message_);
		void command_chat(const object & obj_, const std::string & message_);
		void system_chat(const std::string &message_);
		void custom_chat(const object & obj_, uint32_t channel_id_, const std::string &message_);
		
		/* Config */
		std::vector<config> config_hierarchy(const config &config_entry_);
        std::string config_name(const config &config_entry_);
        std::vector<config> config_properties(const config &config_entry,const std::string& condition_, bool inherit);
        std::string config_source_mod(const config &config_entry_);
        std::vector<std::string> config_source_mod_list(const config &config_entry_);
        float count(const config &config_entry_);
        //std::vector<game_value> get_array(const config &config_entry_);
        config get_mission_config(const std::string& value_);
        float get_number(const config &config_entry_);
        std::string get_text(const config &config_entry_);
        config inherits_from(const config &config_entry_);
        bool is_array(const config &config_entry_);
        bool is_class(const config &config_entry_);
        bool is_null(const config &config_entry_);
        bool is_number(const config &config_entry_);
        bool is_text(const config &config_entry_);
        std::vector<std::string> config_classes(const std::string& value_, config a_config_);
        void load_overlay(const control &a_control_, config a_config_);
        void new_overlay(const control &a_control_, config a_config_);
        config select(const config &a_config_, float a_number_);
        config campaign_config_file();
        config config_file();
        config config_null();
        config mission_config_file();
		
		/* Core */
				std::vector<object> all_3den_entities();
		std::vector<object> all_curators();
		std::vector<object> all_dead();
		std::vector<object> all_deadmen();
		std::vector<display> all_displays();
		std::vector<group> all_groups();
		std::vector<marker> all_map_markers();
		std::vector<object> all_mines();
		std::vector<object> all_players();
		// std::vector<site> all_sites(); // This command is depecrated and no longer supported https://community.bistudio.com/wiki/allSites
		std::vector<object> all_units();
		std::vector<object> all_units_uav();

		object player();
		object create_vehicle(const std::string &type_, const vector3 &pos_);
		object create_vehicle(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_, float placement_, const std::string &special_);
		void delete_vehicle(const object &obj_);

		float server_time();
		std::string server_name();

		bool is_null(const object &value_);
		bool is_null(const group &value_);
		bool is_null(const control &value_);
		bool is_null(const display &value_);
		bool is_null(const script &value_);
		bool is_null(const task &value_);

		script script_null();
		task task_null();
		rv_namespace ui_namespace();

		std::vector<script> diag_active_mission_fsms();
		std::vector<script> diag_active_sqf_scripts();
		std::vector<script> diag_active_sqs_scripts();

		bool __sqfassert(bool test_);

        std::vector<control> all_controls(const display &display_);

        std::vector<std::string> all_turrets(const object &vehicle_, bool person_turrets_);

        std::vector<std::string> all_turrets(const object &vehicle_);

        std::vector<std::string> all_variables(const object &value_);
        std::vector<std::string> all_variables(const control &value_);
        std::vector<std::string> all_variables(const team_member &value_);
        std::vector<std::string> all_variables(rv_namespace value_);
        std::vector<std::string> all_variables(const group &value_);
        std::vector<std::string> all_variables(const task &value_);
        std::vector<std::string> all_variables(const location &value_);
		
		/* Ctrl */
				void ctrl_activate(const control &value_);
		float ctrl_auto_scroll_delay(const control &value_);
		bool ctrl_auto_scroll_rewind(const control &value_);
		float ctrl_auto_scroll_speed(const control &value_);
		bool ctrl_checked(const control &value_);
		std::string ctrl_class_name(const control &value_);
		bool ctrl_committed(const control &value_);
		bool ctrl_delete(const control &value_);
		bool ctrl_enabled(const control &value_);
		bool ctrl_enabled(float value_);
		float ctrl_fade(const control &value_);
		bool ctrl_htmlloaded(const control &value_);
		float ctrl_idc(const control &value_);
		float ctrl_idd(const display &value_);
		void ctrl_map_anim_clear(const control &value_);
		void ctrl_map_anim_commit(const control &value_);
		bool ctrl_map_anim_done(const control &value_);
		float ctrl_map_scale(const control &value_);
		std::string ctrl_model(const control &value_);
		float ctrl_model_scale(const control &value_);
		display ctrl_parent(const control &value_);
		control ctrl_parent_controls_group(const control &value_);
		float ctrl_scale(const control &value_);
		void ctrl_set_focus(const control &value_);
		bool ctrl_shown(const control &value_);
		std::string ctrl_text(const control &value_);
		std::string ctrl_text(float value_);
		float ctrl_text_height(const control &value_);
		std::string ctrl_text_secondary(const control &value_);
		float ctrl_type(const control &value_);
		bool ctrl_visible(float value_);

		void ctrl_commit(const control &value0_, float value1_);
        void ctrl_enable(int control_id_, bool enable_);
        void ctrl_enable(const control &control_, bool enable_);
		void ctrl_remove_all_event_handlers(const control &value0_, const std::string& value1_);
		void ctrl_set_auto_scroll_delay(const control &value0_, float value1_);
		void ctrl_set_auto_scroll_rewind(const control &value0_, bool value1_);
		void ctrl_set_auto_scroll_speed(const control &value0_, float value1_);
		void ctrl_set_checked(const control &value0_, bool value1_);
		void ctrl_set_fade(const control &value0_, float value1_);
		void ctrl_set_font(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h1(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h1b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h2(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h2b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h3(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h3b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h4(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h4b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h5(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h5b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h6(const control &value0_, const std::string& value1_);
		void ctrl_set_font_h6b(const control &value0_, const std::string& value1_);
		void ctrl_set_font_height(const control &value0_, float value1_);
		void ctrl_set_font_height_h1(const control &value0_, float value1_);
		void ctrl_set_font_height_h2(const control &value0_, float value1_);
		void ctrl_set_font_height_h3(const control &value0_, float value1_);
		void ctrl_set_font_height_h4(const control &value0_, float value1_);
		void ctrl_set_font_height_h5(const control &value0_, float value1_);
		void ctrl_set_font_height_h6(const control &value0_, float value1_);
		void ctrl_set_font_height_secondary(const control &value0_, float value1_);
		void ctrl_set_font_p(const control &value0_, const std::string& value1_);
		void ctrl_set_font_p(const control &value0_, float value1_);
		void ctrl_set_font_pb(const control &value0_, const std::string& value1_);
		void ctrl_set_font_secondary(const control &value0_, const std::string& value1_);
		void ctrl_set_model(const control &value0_, const std::string& value1_);
		void ctrl_set_model_scale(const control &value0_, float value1_);
		void ctrl_set_scale(const control &value0_, float value1_);
		void ctrl_set_structured_text(const control &value0_, const std::string& value1_);
		void ctrl_set_text(const control &value0_, const std::string& value1_);
        void ctrl_set_text(int control_id_, const std::string &text_);
		void ctrl_set_text_secondary(const control &value0_, const std::string& value1_);
		void ctrl_set_tooltip(const control &value0_, const std::string& value1_);
		void ctrl_show(const control &value0_, bool value1_);
        void ctrl_show(int control_id_, bool show_);
		
		/* Curator */
		object curatorcamera();
		object curatormouseover();
		std::vector<object> curatorselected();
		void opencuratorinterface();
		bool shown_curatorcompass();
		float curator_camera_area_ceiling(const object &value_);
		bool curator_editing_area_type(const object &value_);
		float curator_points(const object &value_);
		float curator_waypoint_cost(const object &value_);
		object get_assigned_curator_logic(const object &value_);
		object get_assigned_curator_unit(const object &value_);
		void remove_all_curator_addons(const object &value_);
		void remove_all_curator_camera_areas(const object &value_);
		void remove_all_curator_editing_areas(const object &value_);
		void show_curator_compass(bool value_);
		void unassign_curator(const object &value_);
		void add_curator_points(const object &value0_, float value1_);
		void allow_curator_logic_ignore_areas(const object &value0_, bool value1_);
		float curator_coef(const object &value0_, std::string value1_);
		void remove_curator_camera_area(const object &value0_, float value1_);
		void remove_curator_editing_area(const object &value0_, float value1_);
		void set_curator_camera_area_ceiling(const object &value0_, float value1_);
		void set_curator_editing_area_type(const object &value0_, bool value1_);
		void set_curator_waypoint_cost(const object &value0_, float value1_);

		std::vector<std::string> curator_addons(const object &curator_module_);
		std::vector<object> curator_editable_objects(const object &curator_module_);
		
		/* Group */
		bool group_icon_selectable();
		std::array<bool, 2> group_icons_visible();
		group grp_null();
		void clear_group_icons(const group &value_);
		group create_group(const side &value_);
		void delete_group(const group &value_);

		group group_from_net_id(const std::string &value_);
		std::string group_id(const group &value_);
		float group_owner(const group &value_);
		bool set_group_owner(const group &value0_, float value1_);

		object leader(const group &value_);
		void group_radio(const object &value0_, const std::string& value1_);
		void remove_group_icon(const group &value0_, float value1_);
		void select_leader(const object &value0_, const group &value1_);
		float current_waypoint(const group &value_);
		void set_group_icons_selectable(bool value_);
		
		/* Marker */
		void delete_marker(const std::string& value_);
		void delete_marker_local(const std::string& value_);
		float marker_alpha(const std::string& value_);
		float marker_dir(const std::string& value_);

		std::string marker_brush(const std::string& value_);
		std::string marker_color(const std::string& value_);
		std::string marker_shape(const std::string& value_);
		std::string marker_text(const std::string& value_);
		std::string marker_type(const std::string& value_);

		void set_marker_alpha(float value0_, const std::string& value1_);
		void set_marker_alpha_local(float value0_, const std::string& value1_);
		void set_marker_dir(float value0_, const std::string& value1_);
		void set_marker_dir_local(float value0_, const std::string& value1_);

		std::string get_marker_color(const std::string& value_);
		std::string get_marker_type(const std::string& value_);
		vector3 get_marker_pos(const std::string& value_);
		vector2 get_marker_size(const std::string& value_);

        std::string create_marker(const std::string &name_, const vector3 &pos_);
        std::string create_marker(const std::string &name_, const vector2 &pos_);
        std::string create_marker(const std::string &name_, const object &pos_);
        std::string create_marker_local(const std::string &name_, const vector3 &pos_);
        std::string create_marker_local(const std::string &name_, const vector2 &pos_);
        std::string create_marker_local(const std::string &name_, const object &pos_);
		
		/* Multiplayer */
		bool local(const object &value_);
		bool local(const group &value_);
		bool is_server();
		bool is_multiplayer();
		bool is_dedicated();
		bool did_jip();
		
		/* Position */
		namespace __helpers {
			vector3 get_pos_obj(unary_function fnc_, const object & obj_);
		}

		vector3 get_pos(const object &obj_);
		vector3 get_pos(const location *loc_);
		vector3 get_pos_asl(const object & obj_);
		vector3 get_pos_atl(const object & obj_);
		vector3 get_pos_aslw(const object & obj_);
		vector3 visible_position(const object & obj_);
		vector3 visible_position_asl(const object & obj_);
		vector3 position(const object & obj_);
		vector3 get_pos_visual(const object & obj_);
		vector3 get_pos_asl_visual(const object & obj_);
		vector3 get_pos_atl_visual(const object & obj_);
		vector3 aim_pos(const object & obj_);

		void set_pos(const object & obj_, const vector3 &pos_);
		void set_pos_asl(const object & obj_, const vector3 & pos_);
		void set_pos_asl2(const object & obj_, const vector3 & pos_);
		void set_pos_aslw(const object & obj_, const vector3 & pos_);
		void set_pos_atl(const object & obj_, const vector3 & pos_);

		/////////////////////////////////////* Coordinate converters */
		vector3 agl_to_asl(const vector3 & agl_);
		vector3 asl_to_agl(const vector3 & asl_);
		vector3 atl_to_asl(const vector3 & atl_);
		vector3 asl_to_atl(const vector3 & asl_);
		
		/* Waypoint */
		       struct waypoint
        {
            group wgroup;
            float windex;

            waypoint(const group& rv_game_value, uint32_t windex)
                : wgroup(rv_game_value),
                windex((float)windex)
            {
            }

            waypoint(const game_value& rv_game_value)
                : wgroup(group(rv_game_value[0].rv_data)),
                windex(rv_game_value[1])
            {
            }

            std::vector<game_value> __to_gv_vec()
            {
                return std::vector<game_value>{wgroup, game_value(windex)};
            }

            game_value __to_gv()
            {
                return game_value(std::vector<game_value>{ wgroup, windex });
            }

            static const std::string __speed_lookup[4];
            enum class speed
            {
                UNCHANGED = 0,
                LIMITED = 1,
                NORMAL = 2,
                FULL = 3
            };
            static const std::string __show_lookup[4];
            enum class show
            {
                NEVER,
                EASY,
                ALWAYS,
                WAYPOINT_ERROR
            };
            static const std::string __type_lookup[22];
            enum class type
            {
                MOVE,
                DESTROY,
                GETIN,
                SAD,
                JOIN,
                LEADER,
                GETOUT,
                CYCLE,
                LOAD,
                UNLOAD,
                TR_UNLOAD,
                HOLD,
                SENTRY,
                GUARD,
                TALK,
                SCRIPTED,
                SUPPORT,
                GETIN_NEAREST,
                DISMISS,
                LOITER,
                AND,
                OR
            };
            static const std::string __behaviour_lookup[6];
            enum class behaviour
            {
                UNCHANGED,
                CARELESS,
                SAFE,
                AWARE,
                COMBAT,
                STEALTH
            };
            static const std::string __combat_mode_lookup[6];
            enum class combat_mode
            {
                NO_CHANGE,
                BLUE,
                GREEN,
                WHITE,
                YELLOW,
                RED

            };
            static const std::string __formation_lookup[10];
            enum class formation
            {
                NO_CHANGE,
                COLUMN,
                STAG_COLUMN,
                WEDGE,
                ECH_LEFT,
                ECH_RIGHT,
                VEE,
                LINE,
                FILE,
                DIAMOND
            };
            static const std::string __loiter_lookup[2];
            enum class loiter_type
            {
                CIRCLE,
                CIRCLE_L
            };


            static speed __parse_speed(const std::string& subject_)
            {
                for (size_t i = 0; i < __speed_lookup->length(); i++)
                {
                    if (subject_ == __speed_lookup[i])
                    {
                        return static_cast<speed>(i);
                    }
                }
                throw 712;
            }
            static show __parse_show(const std::string& subject_)
            {
                for (size_t i = 0; i < __show_lookup->length(); i++)
                {
                    if (subject_ == __show_lookup[i])
                    {
                        return static_cast<show>(i);
                    }
                }
                throw 712;
            }
            static type __parse_type(const std::string& subject_)
            {
                for (size_t i = 0; i < __type_lookup->length(); i++)
                {
                    if (subject_ == __type_lookup[i])
                    {
                        return static_cast<type>(i);
                    }
                }
                throw 712;
            }
            static behaviour __parse_behaviour(const std::string& subject_)
            {
                for (size_t i = 0; i < __behaviour_lookup->length(); i++)
                {
                    if (subject_ == __behaviour_lookup[i])
                    {
                        return static_cast<behaviour>(i);
                    }
                }
                throw 712;
            }
            static combat_mode __parse_combat_mode(const std::string& subject_)
            {
                for (size_t i = 0; i < __combat_mode_lookup->length(); i++)
                {
                    if (subject_ == __combat_mode_lookup[i])
                    {
                        return static_cast<combat_mode>(i);
                    }
                }
                throw 712;
            }
            static formation __parse_formation(const std::string& subject_)
            {
                for (size_t i = 0; i < __formation_lookup->length(); i++)
                {
                    if (subject_ == __formation_lookup[i])
                    {
                        return static_cast<formation>(i);
                    }
                }
                throw 712;
            }
            static loiter_type __parse_loiter_type(const std::string& subject_)
            {
                for (size_t i = 0; i < __loiter_lookup->length(); i++)
                {
                    if (subject_ == __loiter_lookup[i])
                    {
                        return static_cast<loiter_type>(i);
                    }
                }
                throw 712;
            }

            static std::string __get_enum_as_str(speed subject_)
            {
                return __speed_lookup[(int)subject_];
            }
            static std::string __get_enum_as_str(show subject_)
            {
                return __show_lookup[(int)subject_];
            }
            static std::string __get_enum_as_str(type subject_)
            {
                return __type_lookup[(int)subject_];
            }
            static std::string __get_enum_as_str(behaviour subject_)
            {
                return __behaviour_lookup[(int)subject_];
            }
            static std::string __get_enum_as_str(combat_mode subject_)
            {
                return __combat_mode_lookup[(int)subject_];
            }
            static std::string __get_enum_as_str(formation subject_)
            {
                return __formation_lookup[(int)subject_];
            }
            static std::string __get_enum_as_str(loiter_type subject_)
            {
                return __loiter_lookup[(int)subject_];
            }

        };
        // It's ficking replaced at compile time anyway, why is this nessecary.................
        const std::string waypoint::__speed_lookup[4] = { "UNCHANGED", "LIMITED", "NORMAL", "FULL" };
        const std::string waypoint::__show_lookup[4] = { "NEVER", "EASY", "ALWAYS", "ERROR" };
        const std::string waypoint::__type_lookup[22] = { "MOVE","DESTROY","GETIN","SAD","JOIN","LEADER","GETOUT","CYCLE","LOAD","UNLOAD","TR UNLOAD","HOLD","SENTRY","GUARD","TALK","SCRIPTED","SUPPORT","GETIN NEAREST","DISMISS","LOITER","AND","OR" };
        const std::string waypoint::__behaviour_lookup[6] = { "UNCHANGED", "CARELESS", "SAFE", "AWARE", "COMBAT", "STEALTH" };
        const std::string waypoint::__combat_mode_lookup[6] = { "NO CHANGE", "BLUE", "GREEN", "WHITE", "YELLOW", "RED" };
        const std::string waypoint::__formation_lookup[10] = { "NO_CHANGE","COLUMN","STAG_COLUMN","WEDGE","ECH_LEFT","ECH_RIGHT","VEE","LINE","FILE","DIAMOND" };
        const std::string waypoint::__loiter_lookup[2] = { "CIRCLE", "CIRCLE_L" };

        /*!
        @brief Adds (or inserts when index is given) a new waypoint to a group.

        The waypoint is placed randomly within a circle with the given center and radius. The function returns the placed waypoint.

        @param gp_ The group to add the waypoint to.
        @param center_ The poition of the center of the waypoint placement radius.
        @param radius_ The radius of the waypoint placement area.
        @param index_ [OPTIONAL] The index of the waypoint to insert this waypoint after.
        @param name_ [OPTIONAL] The waypoint name

        @return Returns the placed waypoint.

        @sa https://community.bistudio.com/wiki/addWaypoint
        */
        waypoint add_waypoint(group & gp_, const vector3 & center_, float radius_, int index_ = -1, const std::string & name_ = "");

        /*!
        @brief Adds (or inserts when index is given) a new waypoint to a group.

        The waypoint is placed randomly within a circle with the given center and radius. The function returns the placed waypoint.

        @param gp_ The group to add the waypoint to.
        @param center_ An object to be the center of the waypoint placement radius.
        @param radius_ The radius of the waypoint placement area.
        @param index_ [OPTIONAL] The index of the waypoint to insert this waypoint after.
        @param name_ [OPTIONAL] The waypoint name

        @return Returns the placed waypoint.

        @sa 		https://community.bistudio.com/wiki/addWaypoint
        */
        waypoint add_waypoint(group & gp_, const object & center_, float radius_, int index_ = -1, const std::string & name_ = "");

        /*!
        @brief  Removes the specified waypoint.

        @param  wp_ Waypoint to delete

        @sa https://community.bistudio.com/wiki/deleteWaypoint
        */
        void delete_waypoint(waypoint & wp_);


        void copy_waypoints(group & to_, group & from_);

        /************************************************  GETTERS   ************************************************/

        /*!
        @brief Gets the object attached to the waypoint.

        @param wp_ Waypoint to use

        @return Object attached to the waypoint, if any.
        */
        object waypoint_attached_object(waypoint& wp_);

        /*!
        @brief Gets the vehicle attached to the waypoint.

        @param wp_ Waypoint to use

        @return Vehicle attached to the waypoint, if any.

        @sa https://community.bistudio.com/wiki/waypointAttachedVehicle
        */
        object waypoint_attached_vehicle(waypoint & wp_);

        /*!
        @brief Gets the waypoint behavior.

        @param wp_ Waypoint to use

        @return Returns the behaviour of the waypoint.

        @sa waypoint::behaviour
        */
        waypoint::behaviour waypoint_behaviour(waypoint & wp_);

        /*!
        @brief Gets the waypoint combat mode.

        @param wp_ Waypoint to use

        @return Returns the combat mode of the waypoint.

        @sa waypoint::combat_mode
        @sa https://community.bistudio.com/wiki/2D_Editor:_Waypoints#Combat_Mode
        */
        waypoint::combat_mode waypoint_combat_mode(waypoint & wp_);

        /*!
        @brief Gets the radius around the waypoint where the waypoint is completed.

        @param wp_ Waypoint to use

        @return Returns the completeion radius of the waypoint.

        @sa https://community.bistudio.com/wiki/waypointCompletionRadius
        */
        float waypoint_completeion_radius(waypoint & wp_);

        /*!
        @brief Gets the waypoint description.

        @param wp_ Waypoint to use

        @return Returns the waypoint description

        @sa https://community.bistudio.com/wiki/waypointDescription
        */
        std::string waypoint_description(waypoint & wp_);

        /*!
        @brief Gets the waypoint description.

        @param wp_ Waypoint to use

        @return Returns the waypoint formation, enumeratred.

        @sa https://community.bistudio.com/wiki/waypointFormation
        */
        waypoint::formation waypoint_formation(waypoint & wp_);

        /*!
        @brief Gets the house position assigned to the waypoint.

        @param wp_ Waypoint to use

        @return Returns the house position.

        @sa https://community.bistudio.com/wiki/waypointHousePosition
        */
        float waypoint_house_position(waypoint & wp_);

        /*!
        @brief Gets the waypoint loiter radius.

        @param wp_ Waypoint to use

        @return Returns the loiter radius.

        @sa https://community.bistudio.com/wiki/waypointLoiterRadius
        */
        float waypoint_loiter_radius(waypoint & wp_);

        /*!
        @brief Gets the waypoint loiter type.

        @param wp_ Waypoint to use

        @return Returns the loiter type, enumerated.

        @sa https://community.bistudio.com/wiki/waypointLoiterType
        */
        waypoint::loiter_type waypoint_loiter_type(waypoint & wp_);

        /*!
        @brief Gets the waypoint name.

        @param wp_ Waypoint to use

        @return The name assigned to the waypoint.

        @sa https://community.bistudio.com/wiki/waypointName
        */
        std::string waypoint_name(waypoint & wp_);

        /*!
        @brief Get Waypoint's Position.

        @param wp_ Waypoint to use

        @return The position of the waypoint.

        @sa https://community.bistudio.com/wiki/waypointPosition
        */
        vector3 waypoint_position(waypoint & wp_);

        /*!
        @brief  	Returns an array of waypoints for the specified unit/group

        @param  	gp_ Group to retrieve waypoints of.

        @return The position of the waypoint.

        @sa https://community.bistudio.com/wiki/waypoints
        */
        std::vector<waypoint> waypoints(group & gp_);

        /*!
        @brief Gets the waypoint script.

        @param wp_ Waypoint to use

        @return The position of the waypoint.

        @sa https://community.bistudio.com/wiki/waypointScript
        */
        std::string waypoint_script(waypoint & wp_);

        /*!
        @brief Gets the waypoint show/hide status.

        @param wp_ Waypoint to use

        @return Gets the showhide status, enumerated.

        @sa https://community.bistudio.com/wiki/waypointShow
        */
        waypoint::show waypoint_show(waypoint & wp_);

        /*!
        @brief Gets the waypoint movement speed.

        @param wp_ Waypoint to use

        @return Gets the waypoint speed, enumerated.

        @sa https://community.bistudio.com/wiki/waypointSpeed
        */
        waypoint::speed waypoint_speed(waypoint & wp_);
        // TODO waypoint_statements needs struct for return value
        // TODO waypoint_timeout needs struct for return value

        /*!
        @brief Gets the waypoint type.

        @param wp_ Waypoint to use

        @return The waypoint type, enumerated.

        @sa https://community.bistudio.com/wiki/waypointType
        */
        waypoint::type waypoint_type(waypoint & wp_);

        /*!
        @brief Returns the visibility of the waypoint.

        @param wp_ Waypoint to use

        @return The waypoint visibility.

        @sa https://community.bistudio.com/wiki/waypointVisible
        */
        bool waypoint_visible(waypoint & wp_);
        bool waypoint_exists(waypoint & wp_); // NOTE Not SQF command.

        std::vector<waypoint> synchronized_waypoints(waypoint & wp_);
        std::vector<waypoint> synchronized_waypoints(object & obj_);

        void set_current_waypoint(group & gp_, waypoint & wp_);
        void set_waypoint_behaviour(waypoint & wp_, waypoint::behaviour mode_);
        void set_waypoint_combat_mode(waypoint & wp_, waypoint::combat_mode mode_);
        void set_waypoint_completion_radius(waypoint & wp_, float radius_);
        void set_waypoint_description(waypoint & wp_, std::string text_);
        void set_waypoint_formation(waypoint & wp_, waypoint::formation formation_);
        void set_waypoint_house_position(waypoint & wp_, float house_pos_);
        void set_waypoint_loiter_radius(waypoint & wp_, float radius_);
        void set_waypoint_loiter_type(waypoint & wp_, waypoint::loiter_type type_);
        void set_waypoint_name(waypoint & wp_, std::string name_);
        void set_waypoint_position(waypoint & wp_, vector3 & pos_, float radius_);
        void set_waypoint_script(waypoint & wp_, std::string command_);
        void set_waypoint_speed(waypoint& wp_, waypoint::speed mode_);
        void set_waypoint_statements(waypoint& wp_, std::string condition_, std::string statement_);
        void set_waypoint_timeout(waypoint& wp_, float min_, float mid_, float max_);
        void set_waypoint_type(waypoint& wp_, waypoint::type type_);
        void set_waypoint_visible(waypoint& wp_, bool visibility_);

        void show_waypoint(waypoint& wp_, std::string show_);

        void synchronize_waypoint(waypoint& wp_, std::vector<waypoint> others_);
        void synchronize_waypoint(object& trigger_, std::vector<waypoint> others_);

        void waypoint_attach_object(waypoint& wp_, int obj_id_);
        void waypoint_attach_object(waypoint& wp_, object obj_);

        float current_waypoint(group gp_);
        bool waypoints_enabled_uav(object value_);
        void enable_uavwaypoints(bool value0_, object value1_);
        float waypoint_timeout_current(group value_);
		
		/* World */
		
        struct game_date
        {
            float year;
            float month;
            float day;
            float hour;
            float minute;

            game_date(float year_, float month_, float day_, float hour_, float minute_)
            {
                year = year_;
                month = month_;
                day = day_;
                hour = hour_;
                minute = minute_;
            }

            static game_date from_vector(const std::vector<float> &date_vector_)
            {
                return game_date(date_vector_[0], date_vector_[1], date_vector_[2], date_vector_[3], date_vector_[4]);
            }

            std::vector<float> to_vector() const
            {
                std::vector<float> ret_val{ year, month, day, hour, minute };
                return ret_val;
            }
        };

        float world_size();
        std::string world_name();
        float wind_str();
        float wind_dir();

        vector3 wind();
        float waves();
        void set_waves(float lerp_time_, float val_); // TODO

        float time();
		game_date date();

        float time_multiplier();

        float date_to_number(game_date date_);
	}
}
