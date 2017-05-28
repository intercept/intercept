﻿/*!
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
#include "client/client.hpp"
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        

        struct rv_destination {
            vector3 pos;
            std::string planning_mode;
            bool force_replan;
        };

        struct rv_crew_member {
            object unit;
            std::string role;
            float cargo_index;
            std::vector<int> turret_path;
            bool person_turret;

            rv_crew_member(const object &unit_, sqf_string_const_ref role_, float cargo_index_, const std::vector<int> &turret_path_, bool person_turret_) {
                unit = unit_;
                role = role_;
                cargo_index = cargo_index_;
                turret_path = turret_path_;
                person_turret = person_turret_;
            }
        };
        
        
        struct rv_resolution {
            vector2 resolution;
            vector2 viewport;
            float aspect_ratio;
            float ui_scale;

            rv_resolution(const vector2 &resolution_, const vector2 &viewport_, float aspect_ratio_, float ui_scale_) {
                resolution = resolution_;
                viewport = viewport_;
                aspect_ratio = aspect_ratio_;
                ui_scale = ui_scale_;
            }

            static rv_resolution from_vector(const std::vector<float> &resolution_vector_) {
                vector2 resolution = { resolution_vector_[0], resolution_vector_[1] };
                vector2 viewport = { resolution_vector_[2], resolution_vector_[3] };
                return rv_resolution(resolution, viewport, resolution_vector_[4], resolution_vector_[5]);
            }

            std::vector<float> to_vector() const {
                std::vector<float> ret_val{ resolution.x, resolution.y, viewport.x, viewport.y, aspect_ratio, ui_scale };
                return ret_val;
            }
        };

        struct rv_particle_shape {
            std::string file;
            int ntieth = 16; //this param is a const internally
            int row;
            int column;
            int loop;

            operator game_value() {
                return game_value(std::vector<game_value>({
                    file,
                    16.0f,
                    static_cast<float>(row),
                    static_cast<float>(column),
                    static_cast<float>(loop)
                }));
            }

            operator game_value() const {
                return game_value(std::vector<game_value>({
                    file,
                    16.0f,
                    static_cast<float>(row),
                    static_cast<float>(column),
                    static_cast<float>(loop)
                }));
            }
        };
        struct rv_particle_array {
            rv_particle_shape shape;
            std::string animation_name;
            std::string type;
            float timer_period;
            float lifetime;
            vector3 position;
            vector3 move_velocity;
            float rotation_velocity;
            float weight;
            float volume;
            float rubbing;
            float size;
            std::vector<rv_color> color;
            float animation_phase;
            float rand_dir_period;
            float rand_dir_intensity;
            std::string on_timer;
            std::string before_destroy;
            object follow;
            float angle;
            bool on_surface;
            float bounce_on_surface;
            std::vector<rv_color> emissive_color;

            operator game_value() {
                std::vector<game_value> color_gv, emissive_color_gv;
                for (rv_color c : color) {
                    color_gv.push_back(c);
                }
                for (rv_color ec : emissive_color) {
                    emissive_color_gv.push_back(ec);
                }
                return game_value(std::vector<game_value>({
                    shape,
                    animation_name,
                    type,
                    timer_period,
                    lifetime,
                    position,
                    move_velocity,
                    rotation_velocity,
                    weight,
                    volume,
                    rubbing,
                    size,
                    color_gv,
                    animation_phase,
                    rand_dir_period,
                    rand_dir_intensity,
                    on_timer,
                    before_destroy,
                    follow,
                    angle,
                    on_surface,
                    bounce_on_surface,
                    emissive_color_gv
                }));
            }

            operator game_value() const {
                std::vector<game_value> color_gv, emissive_color_gv;
                for (rv_color c : color) {
                    color_gv.push_back(c);
                }
                for (rv_color ec : emissive_color) {
                    emissive_color_gv.push_back(ec);
                }
                return game_value(std::vector<game_value>({
                    shape,
                    animation_name,
                    type,
                    timer_period,
                    lifetime,
                    position,
                    move_velocity,
                    rotation_velocity,
                    weight,
                    volume,
                    rubbing,
                    size,
                    color_gv,
                    animation_phase,
                    rand_dir_period,
                    rand_dir_intensity,
                    on_timer,
                    before_destroy,
                    follow,
                    angle,
                    on_surface,
                    bounce_on_surface,
                    emissive_color_gv
                }));
            }
        };
        struct rv_particle_random {
            float lifetime;
            vector3 position;
            vector3 move_velocity;
            float rotation_velocity;
            float size;
            rv_color color;
            float random_direction_period;
            float random_direction_intensity;
            float angle;
            float bounce_on_surface;

            operator game_value() {
                return game_value(std::vector<game_value>({
                    lifetime,
                    position,
                    move_velocity,
                    rotation_velocity,
                    size,
                    color,
                    random_direction_period,
                    random_direction_intensity,
                    angle,
                    bounce_on_surface
                }));
            }

            operator game_value() const {
                return game_value(std::vector<game_value>({
                    lifetime,
                    position,
                    move_velocity,
                    rotation_velocity,
                    size,
                    color,
                    random_direction_period,
                    random_direction_intensity,
                    angle,
                    bounce_on_surface
                }));
            }
        };

        struct rv_credit {
            std::string library_name;
            std::string credits;

            rv_credit(const game_value &rv_game_value_)
                : library_name(rv_game_value_[0]),
                credits(rv_game_value_[1]) {}
        };

        struct rv_artillery_computer_settings {
            std::string name;
            std::string ammo;
            int mode; // TODO investigate what this actually is

            rv_artillery_computer_settings(const game_value &rv_game_value_)
                : name(rv_game_value_[0]),
                ammo(rv_game_value_[1]),
                mode(rv_game_value_[2]) {}
        };


        struct rv_product_version {
            std::string name;
            std::string name_short;
            float version;
            float build;
            std::string branch;
            bool mods;
            std::string platform;

            rv_product_version(const game_value &rv_game_value_)
                : name(rv_game_value_[0]),
                name_short(rv_game_value_[1]),
                version(rv_game_value_[2]),
                build(rv_game_value_[3]),
                branch(rv_game_value_[4]),
                mods(rv_game_value_[5]),
                platform(rv_game_value_[6]) {}
        };
        struct rv_vehicle_role {
            std::string role;
            std::vector<int> turret_path;
        };

        struct rv_hit_points_damage {
            sqf_return_string_list hit_points;
            sqf_return_string_list hit_selections;
            std::vector<float> damages;
        };


        struct rv_forces_rtd {
            float roll;
            float pitch;
            float collective;
        };


        struct rv_weight_rtd {
            float fuselage;
            float crew;
            float fuel;
            float custom;
            float weapons;

            rv_weight_rtd(float fuselage_, float crew_, float fuel_, float custom_, float weapons_) {
                fuselage = fuselage_;
                crew = crew_;
                fuel = fuel_;
                custom = custom_;
                weapons = weapons_;
            }

            static rv_weight_rtd from_vector(const std::vector<float> &weight_vector_) {
                return rv_weight_rtd(weight_vector_[0], weight_vector_[1], weight_vector_[2], weight_vector_[3], weight_vector_[4]);
            }
        };

        struct rv_best_place {
            vector2 pos;
            float result;
        };
        struct rv_uav_control {
            object unit;
            std::string position;

            rv_uav_control(const game_value &ret_game_value_) :
                unit(ret_game_value_[0]),
                position(ret_game_value_[1]) {}
        };

        struct rv_model_info {
            std::string name;
            std::string path;
            bool skeleton;

            rv_model_info(const game_value &ret_game_value_) :
                name(ret_game_value_[0]),
                path(ret_game_value_[1]),
                skeleton(ret_game_value_[2]) {}
        };

        struct rv_shot_parents {
            object vehicle;
            object instigator;
        };
        struct rv_action_params {
            std::string title;
            std::string script;
            game_value arguments;
            float priority;
            bool show_window;
            bool hide_on_use;
            std::string shortcut;
            std::string condition;
            float radius;
            bool unconscious;
            std::string text_window_background;
            std::string text_window_foreground;
            std::string selection;
        };
        struct rv_target {
            vector3 position;
            std::string type;
            side side;
            float subjective_cost;
            object object_;
            float position_accuracy;
        };
        //#TODO: Verify the correctness of this struct
        struct rv_target_knowledge {
            bool known_by_group;
            bool known_by_unit;
            float last_seen_by_unit;
            float last_endangered_by_unit;
            side target_side;
            bool position_error;
            vector3 target_position;
        };
        struct rv_query_target {
            float accuracy;
            object target;
            side target_side;
            std::string target_type;
            vector2 target_position;
            float target_age;
        };
        struct rv_weapon_accessories {
            std::string silencer;
            std::string flashlight_laserpointer;
            std::string optics;
            std::string bipod;
        };
        struct rv_group_icon {
            std::string icon;
            vector2 offset;
        };


        void draw_line_3d(const vector3 &pos1_, const vector3 &pos2_, const rv_color &color_);
        void draw_icon_3d(sqf_string_const_ref texture_, const rv_color &color_, const vector3 &pos_agl_, float width_, float height_, float angle_, sqf_string_const_ref text_ = "", float shadow_ = 1.0f, float text_size_ = 1.0f, sqf_string_const_ref font_ = "TahomaB");
        
        

        /* potential namespace: misc, missions */
        void activate_addons(sqf_string_list_const_ref addons_);


        
        
        /* potential namespace: core, create */
        object create_agent(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f, sqf_string_const_ref special_ = "NONE");
        object create_mine(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f);
        

        
        
        /* potential namespace: misc */
        void enable_saving(bool enable_);
        void enable_saving(bool enable_, bool autosave_);


        /* potential namespace: physics, physx, core */

        /* potential namespace: misc */
        std::vector<float> get_dlcs(float filter_);
        
        /* potential namespace: particles */
        void set_particle_params(const object &particle_source_, const rv_particle_array &particle_array_);
        void set_particle_random(const object &particle_source_, const rv_particle_random &particle_random_);
        void set_particle_circle(const object &particle_source_, float radius_, const vector3 &velocity_);
        void set_particle_fire(const object &particle_source_, float core_intensity_, float core_distance_, float damage_time_);
        void set_particle_class(const object &particle_source_, sqf_string_const_ref particle_class_);
        void drop(const rv_particle_array &particle_array_);
        void set_particle_params();
        float particles_quality();
        void set_drop_interval(const object &value0_, float value1_);



        float armory_points();
        float benchmark();
        bool cadet_mode();
        object camera_on();

        bool cheats_enabled();
        void clear_forces_rtd();

        

        
        float difficulty();
        bool difficulty_enabled_rtd();
        float distribution_region();
        void finish_mission_init();

        void force_end();
        bool free_look();
        float getelevationoffset();
        bool get_remote_sensors_disabled();
        
        float get_total_dlc_usage_time();

        
        bool is_autotest();
        bool is_filepatching_enabled();
        bool is_instructor_figure_enabled();
        bool is_pip_enabled();
        bool is_steam_mission();
        bool is_stream_friendly_ui_enabled();
        bool is_stress_damage_enabled();
        sqf_return_string language();
        std::vector<rv_credit> library_credits();
        sqf_return_string_list library_disclaimers();

        void load_game();
        void log_entities();
        bool mark_as_finished_on_steam();
        float mission_difficulty();
        
        //Seriously? Either remove this or just return PI instead of calling into Arma
        float pi();
        std::vector<object> playable_units();
        object player();
        float player_respawn_time();
        side player_side();
        
        
        
        bool reversed_mouse_y();
        void run_init_script();
        bool team_switch_enabled();
        void team_switch();

        float system_of_units();

        void select_no_player();
        bool saving_enabled();
        
        std::vector<object> switchable_units();

        void activate_key(sqf_string_const_ref keyname_);
        void add_switchable_unit(const object & unit_);
        float air_density_rtd(float altitude_);
        void airport_side(int id_);
        void airport_side(const object & target_);
        




        bool can_unload_in_combat(const object & unit_);
        



        float collective_rtd(const object & helicopter_);
        side create_center(const side & side_); //not used in A3

        void de_activate_key(sqf_string_const_ref key_);
        void delete_center(const side & side_);
        void delete_collection(const object & collection_);
        bool delete_identity(sqf_string_const_ref identity_);

        void delete_site(const object &value_);
        bool delete_status(sqf_string_const_ref value_);
        
        bool difficulty_enabled(sqf_string_const_ref value_);

        void disable_remote_sensors(bool value_);
        void disable_user_input(bool value_);
        void dissolve_team(sqf_string_const_ref value_);
        void echo(sqf_string_const_ref value_);
        // TODO void edit(sqf_string_const_ref value_); // Are we sure this is a valid sqf script command?

        void enable_diag_legend(bool value_);
        void enable_engine_artillery(bool value_);
        

        
        
        void enable_traffic(bool value_);
        void enable_sentences(bool value_);
        void enable_stress_damage(bool value_);
        void enable_team_switch(bool value_);
        void end_mission(sqf_string_const_ref value_);
        void estimated_time_left(float value_);
        



        void fail_mission(sqf_string_const_ref value_);
        
        object get_connected_uav(const object &value_);
        float get_custom_aim_coef(const object &value_);
        float get_dlcusage_time(float value_);
        
        

        float get_repair_cargo(const object &value_);
        float get_rotor_brake_rtd(const object &value_);
        float get_wings_orientation_rtd(const object &value_);
        float get_wings_position_rtd(const object &value_);


        
        
        sqf_return_string image(sqf_string_const_ref value_);
        bool is_auto_trim_on_rtd(const object &value_);
        bool is_collision_light_on(const object &value_);
        bool is_dlcavailable(float value_);
        bool is_key_active(sqf_string_const_ref value_);
        bool is_localized(sqf_string_const_ref value_);

        bool is_object_rtd(const object &value_);
        


        

        
        sqf_return_string localize(sqf_string_const_ref value_);
        
                
        float number_of_engines_rtd(const object &value_);
        
        
        float playable_slots_number(const side &value_);
        float players_number(const side &value_);

        bool required_version(sqf_string_const_ref value_);
        sqf_return_string role_description(const object &value_);
        void save_var(sqf_string_const_ref value_);
        void scope_name(sqf_string_const_ref value_);
        float score_side(const side &value_);
        void script_name(sqf_string_const_ref value_);

        
        void set_armory_points(float value_);

         
        void set_system_of_units(float value_);
        void set_traffic_distance(float value_);
        

        
        void stop_engine_rtd(const object &value_);
        sqf_return_string text(sqf_string_const_ref value_);
        

        void unassign_team(const object &value_);
        void unassign_vehicle(const object &value_);
        bool underwater(const object &value_);

        bool unlock_achievement(sqf_string_const_ref value_);





        bool verify_signature(sqf_string_const_ref value_);

        void add_live_stats(const object &value0_, float value1_);
        void add_score_side(const side &value0_, float value1_);
        void add_vehicle(const group &value0_, const object &value1_);


        void allow_sprint(const object &value0_, bool value1_);
        float animation_phase(const object &value0_, sqf_string_const_ref value1_);
        void assign_to_airport(const object &value0_, float value1_);
        void assign_to_airport(const object &value0_, const object &target_);




        void enable_auto_start_up_rtd(const object &value0_, bool value1_);
        bool enable_auto_trim_rtd(const object &value0_, bool value1_);
        void enable_copilot(const object &value0_, bool value1_);
        


        
        
        bool is_kind_of(const object &obj_, sqf_string_const_ref type_);
        bool is_kind_of(sqf_string_const_ref type1_, sqf_string_const_ref type2_);
        bool is_kind_of(sqf_string_const_ref type1_, sqf_string_const_ref type2_, const config &target_config_);





        bool load_identity(const object &value0_, sqf_string_const_ref value1_);
        bool load_status(const object &value0_, sqf_string_const_ref value1_);


        bool mine_detected_by(const object &value0_, const side &value1_);



        
        void reveal_mine(const object &value0_, const side &value1_);
        bool save_status(const object &value0_, sqf_string_const_ref value1_);
        void send_simple_command(const object &value0_, sqf_string_const_ref value1_);
        void set_actual_collective_rtd(const object &value0_, float value1_);
        void set_airport_side(float value0_, const side &value1_);
        void set_airport_side(const object & target_, const side &value1_);


        void set_collision_light(const object &value0_, bool value1_);
        void set_custom_aim_coef(const object &value0_, float value1_);
        void set_custom_weight_rtd(const object &value0_, float value1_);
        
        
        
        
        void set_light_brightness(const object &value0_, float value1_);
        void set_light_day_light(const object &value0_, bool value1_);
        void set_light_flare_max_distance(const object &value0_, float value1_);
        void set_light_flare_size(const object &value0_, float value1_);
        void set_light_intensity(const object &value0_, float value1_);
        void set_light_use_flare(const object &value0_, bool value1_);

        void set_pilot_light(const object &value0_, bool value1_);
        void set_rotor_brake_rtd(const object &value0_, float value1_);

        void save_game();
        void save_joysticks();

        

        std::vector<object> roads_connected_to(const object &obj_);

        //#categorize pos
        vector3 screen_to_world(const vector2 &pos_);


        sqf_return_string speed_mode(const object &obj_);
        sqf_return_string speed_mode(const group &grp_);

        rv_resolution get_resolution();

        std::vector<object> vehicles();

        



        rv_artillery_computer_settings get_artillery_computer_settings();
        rv_product_version product_version();

        // originally "side", but is already a type
        side get_side(const object &object_);


        sqf_return_string wf_side_text(const object &object_);
        sqf_return_string wf_side_text(const group &group_);
        sqf_return_string wf_side_text(const side &side_);

        float count_side(const side &side_, std::vector<object> &objects_);


        bool in(const object &unit_, const object &vehicle_);
        


        sqf_return_string compose_text(sqf_string_list_const_ref texts_);
        

        void host_mission(const config &config_, const display &display_);
        std::vector<object> detected_mines(const side &side_);
        
        std::vector<bool> engines_is_on_rtd(const object &heli_);
        std::vector<float> engines_rpm_rtd(const object &heli_);
        std::vector<float> engines_torque_rtd(const object &heli_);

        std::vector<rv_forces_rtd> rotors_forces_rtd(const object &heli_);
        std::vector<rv_forces_rtd> wings_forces_rtd(const object &heli_);

        std::vector<float> rotors_rpm_rtd(const object &heli_);

        rv_weight_rtd weight_rtd(const object &heli_);

        void set_brakes_rtd(const object &heli_, float amount_, int wheel_index_);
        void set_engine_rpm_rtd(const object &heli_, float rpms_, int engine_index_);
        void set_wanted_rpm_rtd(const object &heli_, float rpms_, float time_, int engine_index_);


        void on_command_mode_changed(const code &command_);
        void on_command_mode_changed(sqf_string_const_ref command_);

        void play_mission(sqf_string_const_ref campaign_, sqf_string_const_ref mission_);
        void play_mission(sqf_string_const_ref campaign_, sqf_string_const_ref mission_, bool skip_briefing_);
        void play_mission(sqf_string_const_ref campaign_, const config &mission_);
        void play_mission(sqf_string_const_ref campaign_, const config &mission_, bool skip_briefing_);

        void play_scripted_mission(sqf_string_const_ref world_, const code &command_);
        void play_scripted_mission(sqf_string_const_ref world_, const code &command_, const config &config_);
        void play_scripted_mission(sqf_string_const_ref world_, const code &command_, const config &config_, bool ignore_child_window_);


        void remove_from_remains_collector(const std::vector<object> &remains_);
        
        void set_group_icons_visible(bool map_, bool hud_);
        std::vector<bool> group_icons_visible();
        void set_local_wind_params(float strength_, float diameter_);
        void set_mouse_position(float x_, float y_);
        bool set_stat_value(sqf_string_const_ref name_, float value_);
        void set_traffic_density(float density_, float x_min_, float x_max_, float z_min_, float z_max_);
        void set_traffic_gap(float gap_, float x_min_, float x_max_, float z_min_, float z_max_);
        void set_traffic_speed(float speed_, float x_min_, float x_max_, float z_min_, float z_max_);


        rv_uav_control uav_control(const object& uav_);
        sqf_return_string format(const std::vector<game_value> &params_);
        
        
        
        float difficulty_option(sqf_string_const_ref optionname_);

        void enable_weapon_disassembly(bool enable_);
        float flag_animation_phase(const object &flag_);
        sqf_return_string_list get_mission_layer_entities(sqf_string_const_ref layername_);
        
        object road_at(const object &object_);
        object road_at(const vector3 &position_);
        //#categorize ctrl
        void show_score_table(int force_);
        
        

        

        
        
        //#categorize ctrl
        bool visible_score_table();

        //BINARY -- https://github.com/intercept/intercept/issues/13
        
        
        vector3 building_exit(const object &building_, int index_);
        vector3 building_pos(const object &building_, int index_);
        int count_enemy(const object &unit_, const std::vector<object> &units_);
        int count_friendly(const object &unit_, const std::vector<object> &units_);
        int count_type(sqf_string_const_ref type_, const std::vector<object> &objects_);
        int count_unknown(const object &unit_, const std::vector<object> &units_);
        object create_site(sqf_string_const_ref type_, const vector3 &pos_);

        
        
        
        void enable_channel(int channel_, bool chat_, bool voice_over_net_);
        float get_artillery_eta(const object &unit_, const vector3 &target_position_, sqf_string_const_ref magazine_type_);
        rv_group_icon get_group_icon(const group &group_, int &id_);


        void group_select_unit(const object &player_, const object &unit_, bool select_);
        
        bool in_range_of_artillery(const vector3 &position_, const std::vector<object> &units_, sqf_string_const_ref magazine_type_);
        
        
        
        bool is_uav_connectable(const object &unit_, const object &uav_, bool check_all_items_);
        
        
        void obj_status(sqf_string_const_ref objective_number_, sqf_string_const_ref status_);
        



        void pp_effect_adjust(std::variant<sqf_string_const_ref_wrapper, std::reference_wrapper<int>> effect_, const game_value &settings_);
        void pp_effect_commit(std::variant<std::reference_wrapper<const std::vector<int>>, std::reference_wrapper<int>> effect_, const float &duration_);
        void pp_effect_enable(const std::vector<int> &effets_, bool enable_);
        bool preload_object(float distance_, const object &object_);
        bool preload_object(float distance_, sqf_string_const_ref class_name_);

        
        void remove_owned_mine(const object &unit_, const object &mine_);
        void reveal(std::variant<object, group> &unit_, const object &target_);
        void reveal(std::variant<object, group> &unit_, const std::vector<object> &targets_);
        
        
        //doesn't work in A3 (comment from KK) - Should probably check if that's true tho
        rv_text set_attributes(const rv_text &text_, const std::vector<std::pair<std::string, std::variant<rv_text, sqf_string_const_ref_wrapper>>> &attributes_);
        
        
        void set_group_icon(const group& group_, float icon_id, sqf_string_const_ref icon_path_, const vector2 offset_);
        void set_formation(const group &group_, sqf_string_const_ref formation_);
        void set_form_dir(const group &group_, float heading_);
        void set_group_icon(const group &group_, int id_, sqf_string_const_ref icon_, const vector2 &offset_);
        void set_group_icon_params(const group &group_, const rv_color &color_, sqf_string_const_ref text_, float scale_, bool visible_);
        void set_group_id(const group &group_, sqf_string_const_ref name_format_, sqf_string_list_const_ref params_);
        void set_group_id_global(const group &group_, sqf_string_const_ref name_format_, sqf_string_list_const_ref params_);
        
        void set_light_ambient(const object &light_, float r_, float g_, float b_);
        void set_light_attenuation(const object &light_, float start_, float constant_, float linear_, float quadratic_, float hard_limit_start_, float hard_limit_end_);
        void set_light_color(const object &light_, float r_, float g_, float b_);
        
        
        //#TODO typo should be set_pip_effects
        void set_pipe_effect(sqf_string_const_ref parameter_left, const game_value &parameters_left);
        
        
        void set_rectangular(const location &location_, bool rectangular_);
        void set_size(const location &location_, float size_x_, float size_y_);
        void set_name(const location &location_, sqf_string_const_ref name_);
        void set_speech(const location &location_, sqf_string_const_ref speech_);
        void set_speed_mode(const group &group_, sqf_string_const_ref speed_mode_);
        void set_text(const location &location_, sqf_string_const_ref text_);
        void set_type(const location &location_, sqf_string_const_ref type_);
        
        

        //is this supposed to be here? - Probably need to be renamed? to correct name?
        void binary__sideradio__object_array__string__ret__nothing(const object &unit_, sqf_string_const_ref radio_name_);
        void binary__sideradio__object_array__string__ret__nothing(const side &side_, sqf_string_const_ref identity_, sqf_string_const_ref radio_name_);
        
        //vehicles - new cat
        float set_flag_animation_phase(const object& object_, float phase);
        void set_flag_owner(const object& flag_, const object& owner_);
        void set_flag_animation_phase(const object &flag_, float &animation_phase_);
        object create_vehicle_local(sqf_string_const_ref type_, const vector3 &pos_atl_);
        void add_to_remains_collector(const std::vector<object> & objects_);
        std::vector<rv_crew_member> full_crew(const object &veh_);
        std::vector<rv_crew_member> full_crew(const object &veh_, sqf_string_const_ref filter_, bool include_empty_ = false);
        std::vector<object> crew(const object & _veh);
        float aimed_at_target(const object& vehicle_, const object& target_);
        float aimed_at_target(const object& vehicle_, const object& target_, sqf_string_const_ref weapon_);
        void animate(const object& obj_, sqf_string_const_ref animation_name_, float phase_);
        void animate(const object& obj_, sqf_string_const_ref animation_name_, float phase_, bool instant_);
        void animate_door(const object& obj_, sqf_string_const_ref door_name_, float phase_, bool now_);
        vector3 get_center_of_mass(const object &obj_);
        object create_vehicle(sqf_string_const_ref type_, const vector3 &pos_);
        object create_vehicle(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_, float placement_ = 0.0f, sqf_string_const_ref special_ = "NONE");
        void delete_vehicle(const object &obj_);
        sqf_return_string_list all_turrets(const object &vehicle_, bool person_turrets_);

        sqf_return_string_list all_turrets(const object &vehicle_);
        bool alive(const object & obj_);
        object assigned_commander(const object & veh_);
        object assigned_driver(const object & veh_);
        object assigned_gunner(const object & veh_);
        object assigned_target(const object & veh_);
        object commander(const object & veh_);
        void create_vehicle_crew(const object & veh_);
        float damage(const object & object_);
        object driver(const object &value_);
        object effective_commander(const object &value_);

        void fill_weapons_from_pool(const object &value_);//#categorize inventory? to the other weapon pool stuff

        object flag(const object &value_);
        object flag_owner(const object &value_);
        side flag_side(const object &value_);
        sqf_return_string flag_texture(const object &value_);

        float fuel(const object &value_);
        float get_dammage(const object &value_);
        float get_mass(const object &value_);
        float get_object_dlc(const object &value_);
        float get_object_type(const object &value_);
        void hide_object(const object &value_);
        void hide_object_global(const object &value_);
        bool inflamed(const object &value_);
        bool is_auto_hover_on(const object &value_);
        bool is_autonomous(const object &value_);
        bool is_burning(const object &value_);
        bool is_copilot_enabled(const object &value_);
        bool is_engine_on(const object &value_);
        bool is_hidden(const object &value_);
        bool is_in_remains_collector(const object &value_);
        bool is_light_on(const object &value_);
        bool is_manual_fire(const object &value_);
        bool is_marked_for_collection(const object &value_);
        bool is_object_hidden(const object &value_);
        bool is_touching_ground(const object &value_);
        object laser_target(const object &value_);
        sqf_return_string light_is_on(const object &value_);
        float locked(const object &value_);
        bool mine_active(const object &value_);
        bool locked_driver(const object &value_);
        object object_parent(const object &value_);
        float score(const object &value_);
        float scud_state(const object &value_);
        float size_of(sqf_string_const_ref value_);
        float speed(const object &value_);
        object vehicle(const object &value_);
        sqf_return_string vehicle_var_name(const object &value_);
        void allow_crew_in_immobile(const object &value0_, bool value1_);
        void allow_damage(const object &value0_, bool value1_);
        void allow_dammage(const object &value0_, bool value1_);
        void disable_nvgequipment(const object &value0_, bool value1_);
        void disable_tiequipment(const object &value0_, bool value1_);
        float door_phase(const object &value0_, sqf_string_const_ref value1_);
        float empty_positions(const object &value0_, sqf_string_const_ref value1_);
        void engine_on(const object &value0_, bool value1_);
        float get_hit(const object &value0_, sqf_string_const_ref value1_);
        float get_hit_index(const object &value0_, float value1_);
        float get_hit_point_damage(const object &value0_, sqf_string_const_ref value1_);
        float get_speed(const object &value0_, sqf_string_const_ref value1_);
        void hide_object(const object &value0_, bool value1_);
        void hide_object_global(const object &value0_, bool value1_);
        void inflame(const object &value0_, bool value1_);
        void limit_speed(const object &value0_, float value1_);
        void lock(const object &value0_, bool value1_);
        void lock(const object &value0_, float value1_);
        void lock_cargo(const object &value0_, bool value1_);
        void lock_driver(const object &value0_, bool value1_);
        bool locked_cargo(const object &value0_, float value1_);
        void set_autonomous(const object &value0_, bool value1_);
        void set_damage(const object &value0_, float value1_, bool use_effects_ = true);
        void set_dammage(const object &value0_, float value1_);
        void set_flag_side(const object &value0_, const side &value1_);
        void set_flag_texture(const object &value0_, sqf_string_const_ref value1_);
        void set_fuel(const object &value0_, float value1_);
        void set_vehicle_armor(const object &value0_, float value1_);
        void set_vehicle_id(const object &value0_, float value1_);
        void set_vehicle_lock(const object &value0_, sqf_string_const_ref value1_);
        void set_vehicle_var_name(const object &value0_, sqf_string_const_ref value1_);
        void switch_light(const object &value0_, sqf_string_const_ref value1_);
        void set_hit(const object &object_, sqf_string_const_ref part_, float damage_);
        void set_hit_index(const object &object_, int part_index_, float damage_);
        void set_hit_point_damage(const object &object_, sqf_string_const_ref hit_point_, float damage_);
        rv_hit_points_damage get_all_hit_points_damage(const object &veh_);
        int get_cargo_index(const object &vehicle_, const object &unit_);
        sqf_return_string_list get_object_materials(const object &object_);
        sqf_return_string_list get_object_textures(const object &object_);
        std::vector<object> synchronized_objects(const object& obj_);
        rv_model_info get_model_info(const object& object_);
        std::vector<object> all_simple_objects(sqf_string_list_const_ref params_);
        object create_simple_object(sqf_string_const_ref shapename_, const vector3 &positionworld);
        float get_container_max_load(sqf_string_const_ref containerclass_);
        rv_shot_parents get_shot_parents(const object &projectile_);
        bool is_simple_object(const object &object_);
        sqf_return_string_list selection_names(const object &object_);
        void switch_camera(const object &target_);
        void animate_source(const object &object_, sqf_string_const_ref source_, float phase_, bool speed_);
        void animate_source(const object &object_, sqf_string_const_ref source_, float phase_, float speed_);
        float animation_source_phase(const object &object_, sqf_string_const_ref source_);
        void delete_vehicle_crew(const object &vehicle_, const object &unit_);
        void disable_collision_with(const object &object1_, const object &object2_);
        void enable_collision_with(const object &object1_, const object &object2_);
        void hide_selection(const object &object_, sqf_string_const_ref selection_, bool hide_);
        void lock_camera_to(const object &vehicle_, const object &target_, const std::vector<int> &turret_path_);
        void lock_cargo(const object &vehicle_, int index_, bool lock_);
        bool locked_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        void lock_turret(const object &vehicle_, const std::vector<int> &turret_path_, bool lock_);
        void respawn_vehicle(const object &vehicle_, float delay_, int count_);
        void select_weapon_turret(const object&, sqf_string_const_ref weapon_, const std::vector<int>& turretPath_);
        void set_center_of_mass(const object& object_, const vector3& offset_, float time_ = 0.f);
        enum class feature_type {
            disabled = 0,// - Feature disabled 
            visible_object_distance = 1,// - Object is always visible within object view distance 
            visible_terrain_distance = 2// - Object is always visible within terrain view distance 
        };
        bool set_feature_type(const object& object_, feature_type type_);
        bool set_feature_type(const object &object_, int type_);
        void set_mass(const object &object_, float mass_, std::optional<float> time_);
        void set_object_material(const object &object_, int index_, sqf_string_const_ref material_);
        void set_object_material_global(const object &object_, int index_, sqf_string_const_ref material_);


        void set_object_texture(const object &object_, int index_, sqf_string_const_ref texture_);
        void set_object_texture_global(const object &object_, int index_, sqf_string_const_ref texture_);
        void set_pilot_camera_direction(const object &vehicle_, const vector3 &direction_);
        void set_pilot_camera_rotation(const object &vehicle_, float yaw_, float pitch_);
        bool set_pilot_camera_target(const object &vehicle_, std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector3>> target_);
        void set_shot_parents(const object &projectile_, const object &vehicle_, const object &instigator_);
        void set_vehicle_ti_parts(const object &vehicle_, const game_value &params_right_);
        void set_weapon_reloading_time(const object &vehicle_, const object &gunner_, sqf_string_const_ref muzzle_class_, float reload_time_);
        void synchronize_objects_add(const object &unit_, const std::vector<object> &objects_);
        void synchronize_objects_remove(const object &unit_, const std::vector<object> &objects_);
        object turret_unit(const object &vehicle_, const std::vector<int> &turret_path_);
        sqf_return_string_list weapons_turret(const object &vehicle_, const std::vector<int> &turret_path_);


        //units - new cat
        void ais_finish_heal(const object &wounded_, const object &medic_, bool medic_can_heal_);

        void set_hide_behind(const object &unit_, const object &object_where_hide_, const vector3 &hide_position_);

        rv_target_knowledge target_knowledge(const object &unit_, const object &target_);
        game_value targets_aggregate(const object &speaker_, const side &side_, const object &unit_, const vector3 &place_, float time_, game_value &candidates_);
        rv_query_target targets_query(const object &unit_, const object &target_ignore_, const side &target_side, sqf_string_const_ref target_type_, const vector3 &target_position_, float target_max_age_);

        void action(const object &unit_, const std::vector<game_value> &action_array_);

        void create_unit(sqf_string_const_ref type_, const vector3 &pos_, const group &group_, sqf_string_const_ref init_ = "", float skill_ = 0.5f, sqf_string_const_ref rank_ = "PRIVATE");
        object create_unit(const group &group_, sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f, sqf_string_const_ref special_ = "NONE");
        sqf_return_string animation_state(const object & unit_);
        sqf_return_string assigned_team(const object & unit_);
        object assigned_vehicle(const object & unit_);

        bool can_fire(const object & unit_);
        bool can_move(const object & unit_);
        bool can_stand(const object & unit_);
        bool captive(const object & unit_);
        float captive_num(const object & unit_);
        sqf_return_string current_command(const object & veh_);
        int current_vision_mode(const object & unit_);
        float current_zeroing(const object & gunner_);
        sqf_return_string face(const object &value_);
        sqf_return_string faction(const object &value_);
        void force_respawn(const object &value_);
        object form_leader(const object &value_);
        float formation_direction(const object &value_);
        object formation_leader(const object &value_);
        float get_anim_aim_precision(const object &value_);
        float get_anim_speed_coef(const object &value_);
        float get_bleeding_remaining(const object &value_);
        float get_burning_value(const object &value_);
        float get_fatigue(const object &value_);
        float get_oxygen_remaining(const object &value_);
        sqf_return_string get_player_uid(const object &value_);
        float get_stamina(const object &value_);
        float get_stat_value(sqf_string_const_ref value_);
        float get_suppression(const object &value_);
        float get_weapon_sway(const object &value_);
        object gunner(const object &value_);
        float hands_hit(const object &value_);
        void hide_body(const object &value_);
        sqf_return_string incapacitated_state(const object &value_);
        bool is_able_to_breathe(const object &value_);
        bool is_aim_precision_enabled(const object &value_);
        bool is_bleeding(const object &value_);
        bool is_forced_walk(const object &value_);
        bool is_formation_leader(const object &value_);
        bool is_player(const object &value_);
        bool is_sprint_allowed(const object &value_);
        bool is_stamina_enabled(const object &value_);
        bool is_turned_out(const object &value_);
        bool is_uavconnected(const object &value_);
        bool is_walking(const object &value_);
        bool is_weapon_deployed(const object &value_);
        bool is_weapon_rested(const object &value_);
        void move(const object &unit_, const vector3 &pos_);
        void move(const group &group_, const vector3 &pos_);
        bool move_in_any(const object &unit_, const object &vehicle_);
        void move_in_cargo(const object &unit_, const object &vehicle_, int cargo_index_ = -1);
        void move_in_commander(const object &unit_, const object &vehicle_);
        void move_in_driver(const object &unit_, const object &vehicle_);
        void move_in_gunner(const object &unit_, const object &vehicle_);
        void move_in_turret(const object &unit_, const object &vehicle_, const std::vector<int> turret_path_);

        void remote_control(const object &controller_, const object &controlled_);
        rv_vehicle_role assigned_vehicle_role(const object &unit_);
        group get_group(const object &unit_); // originally "group", but is already a type
        std::vector<object> group_selected_units(const object &unit_);
        sqf_return_string_list squad_params(const object& unit_);
        bool unit_ready(const object& unit_);
        sqf_return_string_list unit_addons(sqf_string_const_ref class_);
        std::vector<object> get_all_owned_mines(const object &unit_);
        void remove_all_owned_mines(const object &unit_);
        bool unit_is_uav(const object &unit_);
        void add_owned_mine(const object &unit_, const object &mine_);
        void add_player_scores(const object &unit_, int kills_infantry_, int kills_soft_, int kills_armor_, int kills_air_, int killed_);
        void assign_as_turret(const object &unit_, const object &vehicle_, const std::vector<int> &turret_path_);
        bool connect_terminal_to_uav(const object &unit_, const object &uav_);
        void disable_uav_connectability(const object &object_, const object &uav_, bool check_all_items_);
        void enable_uav_connect_ability(const object &unit_, const object &uav_, bool check_all_items_);
        void enable_weapon_disassembly(const object &unit_, bool enable_);

        //#TODO use t_in_area typedef for position
        object find_nearest_enemy(const object &unit_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_);
        object find_nearest_enemy(const object &unit_, const object &object_);
        void fire(const object &unit_, sqf_string_const_ref muzzle_, sqf_string_const_ref mode_, sqf_string_const_ref magazine_);
        bool fire_at_target(const object &unit_, const object &target_, std::optional<std::string> muzzle_);
        vector3 get_hide_from(const object &unit_, const object &enemy_);
        std::variant<bool, float> get_unit_trait(const object &unit_, sqf_string_const_ref skill_name_);
        void set_captive(const object& object_, bool status);
        /**
        * \brief Mark a unit as captive. If unit is a vehicle, commander is marked. A captive is neutral to everyone (belong to civilian side), and will not trigger "detected by" conditions for its original side.
        * \param object_
        * \param status Using a number (instead of a boolean) for the status has no further effect on the engine's behavior, but can be used by captiveNum to keep track of the captivity status at a finer resolution (e.g. handcuffed, grouped, etc.). The numbered status syntax was introduced in Arma 2.
        */
        void set_captive(const object& object_, float status);
        void set_name(const object &unit_, sqf_string_const_ref name_, sqf_string_const_ref first_name_, sqf_string_const_ref last_name_);
        void set_unit_trait(const object &unit_, sqf_string_const_ref skill_name_, std::variant<bool, float> value_, bool is_custom_);

        void leave_vehicle(const object &unit_, const object &vehicle_);
        void look_at(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const std::vector<object>>> units_, std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector3>> target_);

        void leave_vehicle(const object &value0_, const group &value1_);
        void play_action(const object &value0_, sqf_string_const_ref value1_);
        void play_action_now(const object &value0_, sqf_string_const_ref value1_);
        void play_gesture(const object &value0_, sqf_string_const_ref value1_);
        void play_move(const object &value0_, sqf_string_const_ref value1_);
        void play_move_now(const object &value0_, sqf_string_const_ref value1_);
        bool save_identity(const object &value0_, sqf_string_const_ref value1_);
        void set_anim_speed_coef(const object &value0_, float value1_);
        void set_bleeding_remaining(const object &value0_, float value1_);
        void set_face(const object &value0_, sqf_string_const_ref value1_);
        void set_faceanimation(const object &value0_, float value1_);
        void set_fatigue(const object &value0_, float value1_);
        void set_identity(const object &value0_, sqf_string_const_ref value1_);
        void set_mimic(const object &value0_, sqf_string_const_ref value1_);
        void set_name(const object &value0_, sqf_string_const_ref value1_);
        void set_oxygen_remaining(const object &value0_, float value1_);
        void set_random_lip(const object &value0_, bool value1_);
        void set_rank(const object &value0_, sqf_string_const_ref value1_);
        void set_stamina(const object &value0_, float value1_);
        void set_suppression(const object &value0_, float value1_);
        void set_target_age(const object &value0_, sqf_string_const_ref value1_);
        void set_unconscious(const object &value0_, bool value1_);
        void set_unit_ability(const object &value0_, float value1_);
        void set_unit_pos(const object &value0_, sqf_string_const_ref value1_);
        void set_unit_pos_weak(const object &value0_, sqf_string_const_ref value1_);
        void set_unit_rank(const object &value0_, sqf_string_const_ref value1_);
        void set_unit_recoil_coefficient(const object &value0_, float value1_);
        void do_stop(const object &unit_);
        void do_stop(const std::vector<object> &units_);
        void do_get_out(const object &unit_);
        void do_get_out(const std::vector<object> &units_);
        void switch_action(const object &value0_, sqf_string_const_ref value1_);

        void switch_gesture(const object &value0_, sqf_string_const_ref value1_);
        void switch_move(const object &value0_, sqf_string_const_ref value1_);
        void use_audio_time_for_moves(const object &value0_, bool value1_);

        object leader(const object &value_);
        sqf_return_string life_state(const object &value_);
        bool lock_identity(const object &value_);
        float morale(const object &value_);
        void move_out(const object &value_);
        float move_time(const object &value_);
        sqf_return_string name(const object &value_);
        float need_reload(const object &value_);
        float precision(const object &value_);
        sqf_return_string rank(const object &value_);
        float rank_id(const object &value_);
        float rating(const object &value_);
        void reload(const object &value_);
        bool reload_enabled(const object &value_);
        void remove_switchable_unit(const object &value_);
        void reset_subgroup_direction(const object &value_);
        void select_player(const object &value_);
        void set_playable(const object &value_);
        void set_player_respawn_time(float value_);
        void set_stamina_scheme(sqf_string_const_ref value_);
        bool some_ammo(const object &value_);
        sqf_return_string speaker(const object &value_);
        sqf_return_string stance(const object &value_);
        bool stopped(const object &value_);
        sqf_return_string unit_pos(const object &value_);//#sort
        float unit_recoil_coefficient(const object &value_);
        bool weapon_lowered(const object &value_);
        void add_rating(const object &value0_, float value1_);
        void add_score(const object &value0_, float value1_);
        void assign_team(const object &value0_, sqf_string_const_ref value1_);//#TODO Enum argument
        void disable_conversation(const object &value0_, bool value1_);
        void enable_aim_precision(const object &value0_, bool value1_);
        void enable_fatigue(const object &value0_, bool value1_);
        void enable_mimics(const object &value0_, bool value1_);
        void enable_reload(const object &value0_, bool value1_);
        void enable_stamina(const object &value0_, bool value1_);
        void fire(const object &value0_, sqf_string_const_ref value1_);
        void force_speed(const object &value0_, float value1_);
        void force_walk(const object &value0_, bool value1_);
        bool is_flashlight_on(const object &value0_, sqf_string_const_ref value1_);
        bool is_irlaser_on(const object &value0_, sqf_string_const_ref value1_);



        //ai
        void do_artillery_fire(const object &unit_, const vector3 &position_, float radius_, int rounds_);
        void do_artillery_fire(const std::vector<object> &units_, const vector3 &position_, float radius_, int rounds_);
        void do_fire(const object &unit_, const object &target_);
        void do_fire(const std::vector<object> &units_, const object &target_);
        void do_follow(const object &unit_, const object &target_);
        void do_follow(const std::vector<object> &units_, const object &target_);
        void do_fsm(const object &unit_, sqf_string_const_ref fsm_name_, const vector3 &position_, const object &target_);
        void do_fsm(const std::vector<object> &units_, sqf_string_const_ref fsm_name_, const vector3 &position_, const object &target_);
        void do_move(const object &unit_, const vector3 &position_);
        void do_move(const std::vector<object> &units_, const vector3 &position_);
        void do_suppressive_fire(const object &unit_, const object &target_);
        void do_suppressive_fire(const object &unit_, const vector3 &position_);
        void do_suppressive_fire(const std::vector<object> &units_, const object &target_);
        void do_suppressive_fire(const std::vector<object> &units_, const vector3 &position_);
        void do_target(const object &unit_, const object &target_);
        void do_target(const std::vector<object> &units_, const object &target_);
        void do_watch(const object &unit_, const vector3 &position_);
        void do_watch(const std::vector<object> &units_, const vector3 &position_);
        void do_watch(const object &unit_, const object &target_);
        void do_watch(const std::vector<object> &units_, const object &target_);
        void enable_attack(const group &group_, bool enable_);
        sqf_return_string combat_mode(const object &loc_);
        sqf_return_string formation(const object &leader_);
        sqf_return_string formation(const group &group_);
        std::vector<object> formation_members(const object &unit_);
        vector3 formation_position(const object &unit_);
        sqf_return_string behaviour(const object & unit_);
        bool check_aifeature(sqf_string_const_ref feature_);
        bool fleeing(const object &value_);
        float skill(const object &value_);
        sqf_return_string land_result(const object &value_);
        bool move_to_completed(const object &value_);
        bool move_to_failed(const object &value_);
        void disable_ai(const object &value0_, sqf_string_const_ref value1_);
        void enable_ai(const object &value0_, sqf_string_const_ref value1_);
        void enable_aifeature(bool value0_, sqf_string_const_ref value1_);
        void fly_in_height(const object &value0_, float value1_);
        float knows_about(const object &source_, const object &target_);
        float knows_about(const group &source_, const object &target_);
        float knows_about(const side &side_, const object &target_);
        void land(const object &value0_, sqf_string_const_ref value1_);
        void land_at(const object &value0_, float value1_);
        void land_at(const object &value0_, const object & helipad_);
        float skill(const object &value0_, sqf_string_const_ref value1_);
        float skill_final(const object &value0_, sqf_string_const_ref value1_);
        void stop(const object &value0_, bool value1_);
        void suppress_for(const object &value0_, float value1_);
        void move_to(const object &unit_, const vector3 &pos_);
        struct rv_expected_destination {
            vector3 position;
            std::string planning_mode;
            bool force;

            rv_expected_destination(const game_value &ret_game_value_) :
                position(ret_game_value_[0]),
                planning_mode(ret_game_value_[1]),
                force(ret_game_value_[2]) {}
        };

        rv_expected_destination expected_destination(const object& unit_);

        void use_ai_oper_map_obstruction_test(bool use_);
        void use_ai_steering_component(bool use_);
        void command_suppressive_fire(const object &unit_, const object &target_);
        void command_suppressive_fire(const object &unit_, const vector3 &target_position_);


        //buldozer
        bool buldozer_is_enabled_road_diag();
        void buldozer_reload_oper_map();
        void buldozer(bool value_);
        bool buldozer(sqf_string_const_ref value_);

        //ctrl
        void slider_set_speed(const control &slider_, float line_, int page_);
        int lnb_add_row(int idc_, sqf_string_list_const_ref items_);
        std::pair<bool, bool> forced_map();
        void progress_loading_screen(float value_);
        void look_at_pos(const control &map_, const vector3 &position_);

        
        //eden
        sqf_return_string_list get_mission_layers();



        //config
        sqf_return_string_list config_source_addon_list(const config &config_);
        game_value mod_params(sqf_string_const_ref mod_class_, sqf_string_list_const_ref options_);
        sqf_return_string type_of(const object &value_);



        //core
        //onEvent
        game_value on_double_click(const control &map_, sqf_string_const_ref command_);
        void on_map_single_click(const game_value &params_, std::variant<sqf_string_const_ref_wrapper, std::reference_wrapper<const code>> command_);
        game_value on_show_new_object(const object &control_, sqf_string_const_ref command_);
        //eventhandler
        float add_event_handler(const object &object_, sqf_string_const_ref type_, const code &command_);
        float add_event_handler(const object &object_, sqf_string_const_ref type_, sqf_string_const_ref command_);
        void remove_event_handler(const object &object_, sqf_string_const_ref event_, int index_);
        float add_mission_event_handler(sqf_string_const_ref type_, const code &command_);
        float add_mission_event_handler(sqf_string_const_ref type_, sqf_string_const_ref command_);
        void remove_all_mission_event_handlers(sqf_string_const_ref value_);
        void remove_all_event_handlers(const object &value0_, sqf_string_const_ref value1_);
        void remove_all_mpevent_handlers(const object &value0_, sqf_string_const_ref value1_);
        void remove_mission_event_handler(sqf_string_const_ref type_, float index_);
        int add_mp_event_handler(const object &object_, sqf_string_const_ref type_, sqf_string_const_ref expression_);
        int add_mp_event_handler(const object &object_, sqf_string_const_ref type_, const code &expression_);
        void remove_mp_event_handler(const object &object_, sqf_string_const_ref event_, int index_);
        void add_public_variable_eventhandler(sqf_string_const_ref var_name_, const code &code_);
        void add_public_variable_eventhandler(sqf_string_const_ref var_name_, const object &target_, const code &code_);

        bool user_input_disabled();
        bool screen_shot(sqf_string_const_ref filename_);
        object cursor_object();
        object cursor_target();
        sqf_return_string_list support_info(sqf_string_const_ref mask_);
        
        std::vector<object> all_mission_objects(sqf_string_const_ref type_);

        std::vector<object> all_curators();
        std::vector<object> all_dead();
        std::vector<object> all_deadmen();
        std::vector<display> all_displays();
        std::vector<group> all_groups();
        std::vector<object> all_mines();
        std::vector<object> all_players();
        // std::vector<site> all_sites(); // This command is depecrated and no longer supported https://community.bistudio.com/wiki/allSites
        std::vector<object> all_units();
        std::vector<object> all_units_uav();
        sqf_return_string_list activated_addons();

        //diag
        void diag_capture_frame(float frame_);//#TODO make sure these don't call into engine if the funcptr is nullptr
        void diag_capture_frame_to_file(float frame_);
        void diag_capture_slow_frame(sqf_string_const_ref section_, float threshold_);
        void diag_code_performance(const code &code_, const game_value &arguments_, float cycles_);
        void diag_log_slow_frame(sqf_string_const_ref section_, float threshold_);
        std::vector<script> diag_active_scripts();
        void diag_log(sqf_string_const_ref text_);
        void halt(); //only in dev version - at least wiki says so





        //world
        float moon_phase(int year_, int month_, int day_, int hour_, float minute_);
        void set_waves(float time_, float waves_value_);
        void set_fog(float time_, float fog_);
        void set_fog(float time_, float fog_value_, float fog_decay_, float fog_base_);
        int get_terrain_grid();
        float view_distance();
        void enable_caustics(bool value_);
        void set_lightnings(float time_, float lightnings_value_);
        bool near_objects_ready(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_);
        std::vector<object> near_roads(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_);
        std::vector<object> near_supplies(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_);
        std::vector<rv_target> near_targets(const object &unit_, float radius_);
        object nearest_object(const vector3 &pos_);
        object nearest_object(const vector3 &pos_, sqf_string_const_ref type_);
        object nearest_object(const object &obj_, sqf_string_const_ref type_);
        object nearest_object(const vector3 &pos_, float id_);
        std::vector<object> nearest_objects(const vector3 &pos_, sqf_string_list_const_ref types_, float radius_);
        std::vector<object> nearest_objects(const object &obj_, sqf_string_list_const_ref types_, float radius_);
        std::vector<object> nearest_terrain_objects(const vector3 &pos_, sqf_string_list_const_ref types_, float radius_);
        std::vector<object> nearest_terrain_objects(const object &obj_, sqf_string_list_const_ref types_, float radius_);
        std::vector<object> units_below_height(const group &group_, float height_);
        std::vector<object> units_below_height(const group &group_, float height_);
        std::vector<object> units_below_height(const std::vector<object> &units_, float height_);
        bool surface_is_water(const vector3& pos_);
        vector3 surface_normal(const vector3& pos_);
        sqf_return_string surface_type(const vector3& pos_);
        std::vector<rv_best_place> select_best_places(const object &obj_, float radius_, sqf_string_const_ref expression_, float precision_, float max_results_);
        std::vector<rv_best_place> select_best_places(const vector3 &pos_, float radius_, sqf_string_const_ref expression_, float precision_, float max_results_);
        bool is_on_road(const object &object_);
        bool is_on_road(const vector3 &position_);
        float get_friend(const side &side1_, const side &side2_);
        void set_friend(const side &side1_, const side &side2_, float value_);
        std::vector<object> near_objects(const vector3 &pos_, float radius_);
        std::vector<object> near_objects(const object &object_, float radius_);
        std::vector<object> near_objects(const vector3 &pos_, sqf_string_const_ref type_, float radius_);
        std::vector<object> near_objects(const object &object_, sqf_string_const_ref type_, float radius_);
        object nearest_building(const object &value_);
        object nearest_building(const vector3 &value_);

        std::vector<object> entities(sqf_string_const_ref type_);
        std::vector<object> units(const object& unit_);



        //inventory
        rv_weapon_accessories weapon_accessories(const object &unit_, sqf_string_const_ref weapon_class_);
        rv_weapon_accessories weapon_accessories_cargo(const object &container_, int weapon_id_, int creator_id_);
        sqf_return_string_list magazines_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        int magazine_turret_ammo(sqf_string_const_ref magazine_class_, const std::vector<int> &turret_path_);
        void set_magazine_turret_ammo(const object &vehicle_, sqf_string_const_ref magazine_class_, int ammo_count_, const std::vector<int> &turret_path_);
        void set_vehicle_ammo(const object &value0_, float value1_);
        void set_vehicle_ammo_def(const object &value0_, float value1_);

        void set_fuel_cargo(const object &value0_, float value1_);
        void set_repair_cargo(const object &value0_, float value1_);
        void pick_weapon_pool(const object &value_);
        void put_weapon_pool(const object &value_);
        float query_items_pool(sqf_string_const_ref value_);
        float query_magazine_pool(sqf_string_const_ref value_);
        float query_weapon_pool(sqf_string_const_ref value_);
        float ammo(const object &value0_, sqf_string_const_ref value1_);
        void force_add_uniform(const object &value0_, sqf_string_const_ref value1_);
        void set_ammo_cargo(const object &value0_, float value1_);
        void add_weapon_pool(sqf_string_const_ref weapon_name_, int count_);
        sqf_return_string current_magazine_detail_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        sqf_return_string current_magazine_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        sqf_return_string current_weapon_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        sqf_return_string_list get_artillery_ammo(const std::vector<object> &units_);

        void clear_item_pool();
        void clear_magazine_pool();
        void clear_weapon_pool();

        sqf_return_string binocular(const object & unit_);

        float gear_idcammo_count(float value_);
        float get_aiming_coef(const object &value_);
        float get_ammo_cargo(const object &value_);

        float get_fuel_cargo(const object &value_);

        sqf_return_string goggles(const object &value_);
        sqf_return_string headgear(const object &value_);
        sqf_return_string hmd(const object &value_);


        //position
        vector3 model_to_world(const object &object_, const vector3 &offset_);
        bool in_area(t_sqf_in_area_position position_, const object &trigger_);
        bool in_area(t_sqf_in_area_position position_, sqf_string_const_ref marker_);
        bool in_area(t_sqf_in_area_position position_, t_sqf_in_area_position center_, float radius_x_, float radius_y_, float angle_, bool is_rectangle_, std::optional<float> radius_z_);
        bool in_area(const object &object_, const location &location_);
        bool in_area(t_sqf_in_area_position position_, const location &location_);
        typedef std::variant<std::reference_wrapper<const std::vector<object>>, std::reference_wrapper<const std::vector<vector2>>, std::reference_wrapper<const std::vector<vector3>>> t_sqf_in_area_position_array;
        bool in_area_array(t_sqf_in_area_position_array position_, const object &trigger_);
        bool in_area_array(t_sqf_in_area_position_array position_, sqf_string_const_ref marker_);
        bool in_area_array(t_sqf_in_area_position_array position_, t_sqf_in_area_position center_, float radius_x_, float radius_y_, float angle_, bool is_rectangle_, std::optional<float> radius_z_);
        bool in_area_array(t_sqf_in_area_position_array position_, const location &location_);
        std::vector<vector3> is_flat_empty(const vector3 &position_, float min_distance_, float max_gradient_, float max_gradient_radius_, float over_land_or_water, bool shore_line_, const object &ignore_object_);
        bool in_polygon(const vector3 &position_, const std::vector<vector3> &polygon_);
        vector3 find_empty_position(std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> center_, float min_distance_, float max_distance_, std::optional<std::string> vehicle_type_);
        bool find_empty_position_ready(std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> center_, float radius_, float max_distance_);
        float distance_2d(const object &object1_, const object &object2_);
        float distance_2d(const vector3 &position1_, const vector3 &position2_);
        float distance_2d(const object &object_, const vector3 &position_);
        float distance_2d(const vector3 &position_, const object &object_);
        float distance_sqr(const object &object1_, const object &object2_);
        float distance_sqr(const vector3 &position1_, const vector3 &position2_);
        float distance_sqr(const object &object_, const vector3 &position_);
        float distance_sqr(const vector3 &position_, const object &object_);
        float distance_sqr(const location &location1_, const location &location2_);
        float distance_sqr(const location &location_, const vector3 &position_);
        float distance_sqr(const vector3 &position_, const location &location_);
        std::vector<object> near_entities(const vector3 &pos_agl_, sqf_string_list_const_ref types_, float range_);
        float distance(const object& start_, const object& end_);
        float distance(const vector3& start_, const object& end_);
        float distance(const object& start_, const vector3& end_);
        float distance(const vector3& start_, const vector3& end_);
        bool set_vehicle_position(const object &object_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, const object> position_, sqf_string_list_const_ref markers_, float placement_radius_, std::optional<std::string> special_);



        /* potential namespace: actions */
        sqf_return_string_list action_keys(sqf_string_const_ref user_action_);

        std::vector<float> action_ids(const object& entity_);
        float input_action(sqf_string_const_ref value_);

        rv_text action_keys_images(sqf_string_const_ref user_action_);
        sqf_return_string action_keys_names(sqf_string_const_ref user_action_);
        sqf_return_string action_keys_names(sqf_string_const_ref user_action_, int max_keys_);
        sqf_return_string action_keys_names(sqf_string_const_ref user_action_, int max_keys_, sqf_string_const_ref input_device_priority_);

        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_);
        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_, int max_keys_);
        sqf_return_string_list action_keys_names_array(sqf_string_const_ref user_action_, int max_keys_, sqf_string_const_ref input_device_priority_);
        
        //TODO: arguments default value is nil
        float add_action(const object &object_, sqf_string_const_ref title_, sqf_string_const_ref script_, const std::vector<game_value> &arguments_, float priority_ = 1.5f, bool show_window_ = true, bool hide_on_use_ = true, sqf_string_const_ref shortcut_ = "", sqf_string_const_ref condition_ = "true");
        float add_action(const object &object_, sqf_string_const_ref title_, const code &script_, const std::vector<game_value> &arguments_, float priority_ = 1.5f, bool show_window_ = true, bool hide_on_use_ = true, sqf_string_const_ref shortcut_ = "", sqf_string_const_ref condition_ = "true");

        sqf_return_string commanding_menu();
        sqf_return_string action_name(sqf_string_const_ref action_);
        sqf_return_string key_image(float value_);
        sqf_return_string key_name(float value_);
        void remove_all_actions(const object &value_);
        void remove_action(const object &value0_, float value1_);
        rv_action_params action_params(const object &entity_, int id_);
        void set_user_action_text(const object &object_, int action_index_, std::variant<const std::string, const rv_text> text_menu_, std::variant<const std::string, const rv_text> text_window_background_, std::variant<const std::string, const rv_text> text_window_foreground_);
    

        //waypoints
        void create_guarded_point(const side &side_, const vector3 &pos_, float idstatic_, const object &veh_);
        



        //2d editor commands (probably unneeded)
        //#TODO check them
        void delete_editor_object(const control &map_, sqf_string_const_ref object_);
        sqf_return_string add_editor_object(const control &map_, sqf_string_const_ref type_, const game_value &values_, sqf_string_const_ref subtype_class_);
        game_value shown_editor_object(const control &map_, const game_value &params_right_);
        void set_from_editor(const team_member &value0_, bool value1_);
        bool from_editor(const team_member &value_);

        void editor_set_event_handler(const control &map_, sqf_string_const_ref event_type_, sqf_string_const_ref event_function_);
        game_value eval_object_argument(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref argument_);
        game_value exec_editor_script(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref script_);
        sqf_return_string get_object_argument(const control &map_, const object &object_, sqf_string_const_ref argument_);
        sqf_return_string_list get_object_children(const control &map_, sqf_string_const_ref object_);

        sqf_return_string insert_editor_object(const control &map_, sqf_string_const_ref type_, const game_value &value_, sqf_string_list_const_ref values_, sqf_string_const_ref sub_type_);

        game_value select_editor_object(const control& map_, sqf_string_const_ref object_);

        void set_editor_object_scope(const control &map_, sqf_string_list_const_ref objects_, sqf_string_const_ref editor_type_, sqf_string_const_ref condition_, sqf_string_const_ref scope_, bool sub_ordinates_also_);

        void set_visible_if_tree_collapsed(const control &map_, sqf_string_const_ref object_, bool visible_);
        int add_menu(const control &map_, sqf_string_const_ref text_, float priority_);
        int add_menu_item(const control &map_, sqf_string_const_ref menu_, sqf_string_const_ref text_, sqf_string_const_ref command_, float priority_);
        int add_menu_item(const control &map_, int menu_, sqf_string_const_ref text_, sqf_string_const_ref command_, float priority_);

        int nmenu_items(const control &map_, sqf_string_const_ref menu_name_);
        int nmenu_items(const control &map_, int index_);

        void update_menu_item(const control &map_, int menu_item_index_, sqf_string_const_ref text_, sqf_string_const_ref command_);

        game_value edit_object(const control &map_, sqf_string_const_ref object_);

        sqf_return_string_list list_objects(const control &map_, sqf_string_const_ref type_);
        game_value set_object_arguments(const control &map_, sqf_string_const_ref object_, sqf_string_list_const_ref values_);
        void set_object_proxy(const control &map_, sqf_string_const_ref object_, const object &proxy_object_);

        /* potential namespace: teams */
        team_member create_team(sqf_string_const_ref type_, sqf_string_const_ref name_);

        object agent(const team_member &value_);
        std::vector<team_member> agents();

        void set_combat_mode(const team_member &value0_, sqf_string_const_ref value1_);
        void set_formation(const team_member &value0_, sqf_string_const_ref value1_);

        void delete_team(const team_member &value_);
        sqf_return_string formation(const team_member &value_);

        bool is_agent(const team_member &value_);
        team_member leader(const team_member &value_);
        sqf_return_string team_name(const team_member &value_);
        sqf_return_string team_type(const team_member &value_);

        std::vector<object> members(const team_member &team_);
        void add_resources(const team_member &team_member_, sqf_string_list_const_ref resources_);
        void add_team_member(const team_member &team_, const team_member &member_);
        void delete_resources(const team_member &team_member_, sqf_string_list_const_ref resources_);
        void remove_team_member(const team_member &team_, const team_member &member_);
        void set_leader(const team_member &team_, const team_member &leader_);


        struct rv_ct_list
        {
            int header_index;
            std::vector<control> controls;
        };

        struct rv_weapon_state
        {
            std::string weapon;
            std::string muzzle;
            std::string firemode;
            std::string magazine;
            int ammo_count;
        };

        int admin(int owner_id_);
        int airplane_throttle(const object &airplane_);
        rv_ct_list ct_add_header(const control &control_);
        rv_ct_list ct_add_row(const control &control_);
        void ct_clear(const control &control_);
        int ct_cur_sel(const control &control_);
        int ct_header_count(const control &control_);
        int ct_row_count(const control &control_);
        sqf_return_string get_forced_flag_texture(const object &flag_pole_);
        sqf_return_string_list get_pylon_magazines(const object &vehicle_);
        bool is_damage_allowed(const object &object_);
        void lb_sort(const control &control_);
        void lb_sort(const control &control_, sqf_string_const_ref sort_order_);
        void lb_sort(int control_, sqf_string_const_ref sort_order_);
        void lb_sort(int control_);
        void lb_sort_by_value(const control control_);
        void lb_sort_by_value(int control_);
        bool vehicle_receive_remote_targets(const object &vehicle_);
        bool vehicle_report_own_position(const object &vehicle_);
        bool vehicle_report_remote_targets(const object &vehicle_);
        rv_weapon_state weapon_state(const object &unit_);
        rv_weapon_state weapon_state(const object &vehicle_, const std::vector<int> &turret_path_, sqf_string_const_ref weapon_);
        
        int ammo_on_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_);
        int ammo_on_pylon(const object &vehicle_, int pylon_index_);
        void animate_bay(const object &vehicle_, sqf_string_const_ref pylon_name_, float anim_phase_);
        void animate_bay(const object &vehicle_, int pylon_index_, float anim_phase_);
        void animate_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_, float anim_phase_);
        void animate_pylon(const object &vehicle_, int pylon_index_, float anim_phase_);
        void confirm_sensor_target(const object &vehicle_, const side &side_, bool is_confirmed_);
        sqf_return_string ct_data(const control &control_, int index_);
        std::vector<game_value> ct_find_header_rows(const control &control_, int index_);
        int ct_find_row_header(const control &control_, int index_);
        std::vector<control> ct_header_controls(const control &control_, int index_);
        void ct_remove_headers(const control &control_, const std::vector<int> &header_indexes_);
        void ct_remove_rows(const control &control_, const std::vector<int> &row_indexes_);
        std::vector<control> ct_row_controls(const control &control_, int index_);
        void ct_set_cur_sel(const control &control_, int index_);
        void ct_set_data(const control &control_, int index_, sqf_string_const_ref data_);
        void ct_set_header_template(const control &control_, const config &config_);
        void ct_set_row_template(const control &control_, const config &config_);
        void ct_set_value(const control &control_, float value_);
        float ct_value(const control &control_, float index_);
        void force_flag_texture(const object &object_, sqf_string_const_ref texture_);
        void forget_target(const object &unit_, const object target_);
        void forget_target(const group &group_, const object target_);
        bool is_sensor_target_confirmed(const object &object_, const side &side_);
        vector3 model_to_world_visual_world(const object &object_, const vector3 model_pos_);
        vector3 model_to_world_world(const object &object_, const vector3 model_pos_);
        void report_remote_target(const side &side_, const object &target_, float time_);
        void set_3den_logic_type(const std::vector<object> &objects_, sqf_string_const_ref class_name_);
        void set_air_plane_throttle(const object &airplane_, float throttle_);
        void set_ammo_on_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_, int ammo_count_);
        void set_ammo_on_pylon(const object &vehicle_, int pylon_index_, int ammo_count_);
        void set_dynamic_simulation_distance_coef(sqf_string_const_ref class_, float multiplayer_);
        bool set_pylon_loadout(const object &object_, game_value param_right);
        void set_pylons_priority(const object &object_, const std::vector<int> &priorities_);
        void set_skill(const object &object_, float skill_);
        void set_user_mfd_value(const object &object_, int index_, float value_);
        void set_vehicle_radar(const object &object_, int rules_);
        void set_vehicle_receive_remote_targets(const object &vehicle_, bool receive_);
        void set_vehicle_report_own_position(const object &vehicle_, bool report_);
        void set_vehicle_report_remote_targets(const object &vehicle_, bool report_);
        void targets(const object &unit_, std::optional<bool> enemy_only_, std::optional<float> max_distance_, std::optional<std::vector<side>> sides_, std::optional<float> max_age_, std::optional<std::variant<std::reference_wrapper<vector2>, std::reference_wrapper<vector3>>> alternate_center_);

        struct rv_cursor_object_params
        {
            object cursor_object;
            std::string cursor_object_named_sel;
            float distance;
        };

        sqf_return_string endl();
        rv_cursor_object_params get_cursor_object_params();
        int remote_executed_owner();
    }
}