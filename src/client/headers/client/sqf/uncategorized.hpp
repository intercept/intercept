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
#include "client/client.hpp"
#include "shared/client_types.hpp"
#include <variant> //#TODO move that into shared
#include <optional>

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        struct rv_bounding_box {
            vector3 min;
            vector3 max;
        };

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

            rv_crew_member(const object &unit_, const std::string &role_, float cargo_index_, const std::vector<int> &turret_path_, bool person_turret_) {
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


        game_value call(const code &code_, game_value args_);
        game_value call(const code & code_);
        code compile(const std::string &sqf_);

        void set_variable(const rv_namespace &namespace_, const std::string &var_name_, game_value value_);

        void draw_line_3d(const vector3 &pos1_, const vector3 &pos2_, const rv_color &color_);
        void draw_icon_3d(const std::string &texture_, const rv_color &color_, const vector3 &pos_agl_, float width_, float height_, float angle_, const std::string &text_ = "", float shadow_ = 1.0f, float text_size_ = 1.0f, const std::string &font_ = "TahomaB");

        vector3 vector_dir(const object & obj_);
        vector3 vector_dir_visual(const object & obj_);
        vector3 selection_positon(const object & obj_, const std::string & selection_name_);

        game_value get_variable(const rv_namespace &namespace_, const std::string &var_name_);
        game_value get_variable(const rv_namespace &namespace_, const std::string &var_name_, game_value default_value_);
        game_value get_variable(const display & display_, const std::string & var_name_, game_value default_value_);
        game_value get_variable(const object & obj_, const std::string & var_name_);
        game_value get_variable(const object & obj_, const std::string & var_name_, game_value default_value_);
        game_value get_variable(const group & group_, const std::string & var_name_);
        game_value get_variable(const group & group_, const std::string & var_name_, game_value default_value_);//#TODO shouldn't pass game_values by reference. They are refcounted anyway and get copied into a vector anyway. Problem is this prevents automatic type conversion.
        game_value get_variable(const team_member & team_member_, const std::string & var_name_);
        game_value get_variable(const team_member & team_member_, const std::string & var_name_, game_value default_value_);
        game_value get_variable(const task & task_, const std::string & var_name_);



        std::vector<object> near_entities(const vector3 &pos_agl_, const std::vector<std::string> &types_, float range_);


        object create_vehicle_local(const std::string &type_, const vector3 &pos_atl_);



        /* potential namespace: */
        std::vector<std::string> action_keys(const std::string &user_action_);

        rv_text action_keys_images(const std::string &user_action_);
        std::string action_keys_names(const std::string &user_action_);
        std::string action_keys_names(const std::string &user_action_, int max_keys_);
        std::string action_keys_names(const std::string &user_action_, int max_keys_, const std::string &input_device_priority_);

        std::vector<std::string> action_keys_names_array(const std::string &user_action_);
        std::vector<std::string> action_keys_names_array(const std::string &user_action_, int max_keys_);
        std::vector<std::string> action_keys_names_array(const std::string &user_action_, int max_keys_, const std::string &input_device_priority_);

        /* potential namespace: misc, missions */
        void activate_addons(std::vector<std::string> &addons_);


        /* potential namespace: core, misc, world */
        void add_to_remains_collector(const std::vector<object> & objects_);

        /* potential namespace: medical, misc, unit */
        void ais_finish_heal(const object &wounded_, const object &medic_, bool medic_can_heal_);

        /* potential namespace: core, all */
        std::vector<object> all_mission_objects(const std::string &type_);

        /* potential namespace: vehicle, core, cargo */
        std::vector<object> assigned_cargo(const object &veh_);


        /* potential namespace: misc, attach */
        std::vector<object> attached_objects(const object &obj_);
        object attached_to(const object &obj_);
        void attach_to(const object &object1_, const object &object2_, const vector3 &offset_, const std::string &memPoint_);
        void attach_to(const object &object1_, const object &object2_, const vector3 &offset_);

        /* potential namespace: ai */
        bool attack_enabled(const object &unit_);
        bool attack_enabled(const group &group_);
        void command_artillery_fire(const object& unit_, const vector3& pos_, const std::string& type_, int rounds_);
        void command_artillery_fire(const object& unit_, const vector2& pos_, const std::string& type_, int rounds_);
        void command_artillery_fire(const std::vector<object>& units_, const vector3& pos_, const std::string& type_, int rounds_);
        void command_artillery_fire(const std::vector<object>& units_, const vector2& pos_, const std::string& type_, int rounds_);
        void command_fire(const object& unit_, const object& target_);
        void command_fire(const std::vector<object>& units_, const object& target_);
        void command_follow(const object& unit_, const object& target_);
        void command_follow(const std::vector<object>& units_, const object& target_);
        void command_fsm(const object& unit_, const std::string& fsm_, const vector3& pos_, const object& target_);
        void command_fsm(const object& unit_, const std::string& fsm_, const vector2& pos_, const object& target_);
        void command_fsm(const std::vector<object>& units_, const std::string& fsm_, const vector3& pos_, const object& target_);
        void command_fsm(const std::vector<object>& units_, const std::string& fsm_, const vector2& pos_, const object& target_);
        void command_move(const object& unit_, const vector3& pos_);
        void command_move(const object& unit_, const vector2& pos_);
        void command_move(const std::vector<object>& units_, const vector3& pos_);
        void command_move(const std::vector<object>& units_, const vector2& pos_);
        void command_radio(const object& unit_, const std::string& radio_name_);
        void command_radio(const std::vector<object>& units_, const std::string& radio_name_);
        void command_target(const object& unit_, const object& target_);
        void command_target(const std::vector<object>& units_, const object& target_);
        void command_watch(const object& unit_, const vector3& pos_);
        void command_watch(const object& unit_, const vector2& pos_);
        void command_watch(const std::vector<object>& units_, const vector3& pos_);
        void command_watch(const std::vector<object>& units_, const vector2& pos_);
        void command_watch(const object& unit_, const object& target_);
        void command_watch(const std::vector<object>& units_, const object& target_);

        /* potential namespace: cargo */
        bool can_sling_load(const object& vehicle_, const object& cargo_);

        /* potential namespace: misc, model, position? */
        rv_bounding_box bounding_box(const object &model_);
        rv_bounding_box bounding_box_real(const object &model_);
        vector3 bounding_center(const object &obj_);

        /* potential namespace: ai, group, unit */
        std::string combat_mode(const object &loc_);

        void assign_curator(const object& player_, const object& curator_module_);

        /* potential namespace: ai */
        void command_get_out(const object &unit_);
        void command_get_out(const std::vector<object> & units_);
        void command_stop(const object &unit_);
        void command_stop(const std::vector<object> & units_);
        void allow_fleeing(const object& object_, float cowardice_);
        void allow_fleeing(const group& group_, float cowardice_);
        void allow_get_in(const std::vector<object>& units_, bool allow_);
        void assign_as_commander(const object& unit_, const object& vehicle_);
        void assign_as_driver(const object& unit_, const object& vehicle_);
        void assign_as_gunner(const object& unit_, const object& vehicle_);
        void assign_as_turret(const object& unit_, const object& vehicle_, const std::vector<float>& turret_path_);
        void assign_as_cargo(const object& unit_, const object& vehicle_);
        void assign_as_cargo_index(const object& unit_, const object& vehicle_, int index_);

        /* potential namespace: core, create */
        object create_agent(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f, const std::string &special_ = "NONE");
        object create_mine(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f);
        object create_sound_source(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f);


        /* potential namespace: core, create, teams */
        team_member create_team(const std::string &type_, const std::string &name_);

        /* potential namespace: gui, ui */
        void create_gear_dialog(const object &unit_, const std::string &resource_);

        /* potential namespace: misc */
        void create_guarded_point(const side &side_, const vector3 &pos_, float idstatic_, const object &veh_);
        void action(const object &unit_, const std::vector<game_value> &action_array_);
        float add_event_handler(const object &object_, const std::string &type_, const code &command_);
        float add_event_handler(const object &object_, const std::string &type_, const std::string &command_);

        /* potential namespace: vehicle */
        std::vector<object> crew(const object & _veh);
        float aimed_at_target(const object& vehicle_, const object& target_);
        float aimed_at_target(const object& vehicle_, const object& target_, const std::string& weapon_);
        void animate(const object& obj_, const std::string& animation_name_, float phase_);
        void animate(const object& obj_, const std::string& animation_name_, float phase_, bool instant_);
        void animate_door(const object& obj_, const std::string& door_name_, float phase_, bool now_);

        /* potential namespace: teams */
        std::vector<task> current_tasks(const team_member &team_member_);


        //TODO: arguments default value is nil
        float add_action(const object &object_, const std::string &title_, const std::string &script_, const std::vector<game_value> &arguments_, float priority_ = 1.5f, bool show_window_ = true, bool hide_on_use_ = true, const std::string &shortcut_ = "", const std::string &condition_ = "true");
        float add_action(const object &object_, const std::string &title_, const code &script_, const std::vector<game_value> &arguments_, float priority_ = 1.5f, bool show_window_ = true, bool hide_on_use_ = true, const std::string &shortcut_ = "", const std::string &condition_ = "true");

        /* potential namespace: misc */
        void enable_saving(bool enable_);
        void enable_saving(bool enable_, bool autosave_);



        /* potential namespace: groups, ai */
        std::string formation(const object &leader_);
        std::string formation(const group &group_);

        std::vector<object> formation_members(const object &unit_);
        vector3 formation_position(const object &unit_);

        /* Potential namespace: core */
        std::vector<rv_crew_member> full_crew(const object &veh_);
        std::vector<rv_crew_member> full_crew(const object &veh_, const std::string &filter_, bool include_empty_ = false);

        /* potential namespace: misc */
        std::vector<std::string> get_artillery_ammo(const std::vector<object> &units_);

        /* potential namespace: physics, physx, core */
        vector3 get_center_of_mass(const object &obj_);

        /* potential namespace: misc */
        std::vector<float> get_dlcs(float filter_);
        float distance(const object& start_, const object& end_);
        float distance(const vector3& start_, const object& end_);
        float distance(const object& start_, const vector3& end_);
        float distance(const vector3& start_, const vector3& end_);

        /* potential namespace: particles */
        /* potential namespace: particles */
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
        void set_particle_params(const object &particle_source_, const rv_particle_array &particle_array_);
        void set_particle_random(const object &particle_source_, const rv_particle_random &particle_random_);
        void set_particle_circle(const object &particle_source_, float radius_, const vector3 &velocity_);
        void set_particle_fire(const object &particle_source_, float core_intensity_, float core_distance_, float damage_time_);
        void set_particle_class(const object &particle_source_, const std::string& particle_class_);
        void drop(const rv_particle_array &particle_array_);

        /* Core */
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

        object create_vehicle(const std::string &type_, const vector3 &pos_);
        object create_vehicle(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_, float placement_ = 0.0f, const std::string &special_ = "NONE");
        void delete_vehicle(const object &obj_);

        void create_unit(const std::string &type_, const vector3 &pos_, const group &group_, const std::string &init_ = "", float skill_ = 0.5f, const std::string &rank_ = "PRIVATE");
        object create_unit(const group &group_, const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f, const std::string &special_ = "NONE");

        float server_time();
        std::string server_name();

        bool is_null(const object &value_);
        bool is_null(const control &value_);
        bool is_null(const display &value_);
        bool is_null(const script &value_);
        bool is_null(const task &value_);

        script script_null();
        task task_null();
        rv_namespace ui_namespace();

        bool __sqfassert(bool test_);

        std::vector<std::string> all_turrets(const object &vehicle_, bool person_turrets_);

        std::vector<std::string> all_turrets(const object &vehicle_);

        std::vector<std::string> all_variables(const object &value_);
        std::vector<std::string> all_variables(const team_member &value_);
        std::vector<std::string> all_variables(rv_namespace value_);
        std::vector<std::string> all_variables(const task &value_);
        std::vector<std::string> all_variables(const control &value_);



        /* Multiplayer */
        bool local(const object &value_);
        bool local(const group &value_);
        bool is_server();
        bool is_multiplayer();
        bool is_dedicated();
        bool did_jip();

        float acc_time();
        object agent(const team_member &value_);
        std::vector<std::string> activated_addons();
        std::vector<team_member> agents();

        struct rv_credit {
            std::string library_name;
            std::string credits;

            rv_credit(const game_value &rv_game_value_)
                : library_name(rv_game_value_[0]),
                credits(rv_game_value_[1]) {}
        };

        float armory_points();
        float benchmark();
        side blufor();
        std::string briefing_name();
        bool cadet_mode();
        object camera_on();

        bool cheats_enabled();
        side civilian();
        void clear_forces_rtd();
        void clear_item_pool();
        void clear_magazine_pool();
        void clear_radio();
        void clear_weapon_pool();
        float client_owner();
        std::string commanding_menu();
        std::string copy_from_clipboard();
        rv_namespace current_namespace();
        object cursor_target();
        float daytime();

        bool dialog();
        float difficulty();
        bool difficulty_enabled_rtd();
        void disable_debriefing_stats();
        void disable_serialization();
        display display_null();
        float distribution_region();
        side east();
        void enable_end_dialog();
        void end_loading_screen();
        float estimated_end_server_time();
        void exit();
        void finish_mission_init();

        void force_end();
        void force_weather_change();
        bool free_look();
        std::string getclientstate();
        float getelevationoffset();
        bool get_remote_sensors_disabled();
        float get_shadow_distance();
        float get_total_dlc_usage_time();

        void halt();
        bool has_interface();

        side independent();
        void init_ambient_life();
        bool is_autotest();
        bool is_filepatching_enabled();
        bool is_instructor_figure_enabled();
        bool is_pip_enabled();
        bool is_steam_mission();
        bool is_stream_friendly_ui_enabled();
        bool is_stress_damage_enabled();
        bool is_tut_hints_enabled();
        std::string language();
        std::vector<rv_credit> library_credits();
        std::vector<std::string> library_disclaimers();

        std::string line_break();
        void load_game();
        void log_entities();
        bool mark_as_finished_on_steam();
        float mission_difficulty();
        std::string mission_name();
        rv_namespace mission_namespace();

        float music_volume();
        object obj_null();
        side opfor();
        rv_namespace parsing_namespace();
        float particles_quality();
        float pi();
        float pixel_h();
        float pixel_w();
        std::vector<object> playable_units();
        object player();
        float player_respawn_time();
        side player_side();
        std::string profile_name();
        rv_namespace profile_namespace();
        std::string profile_namesteam();

        side resistance();
        bool reversed_mouse_y();
        void run_init_script();
        float view_distance();
        bool team_switch_enabled();
        void team_switch();

        float system_of_units();

        float sound_volume();
        void simul_weather_sync();
        void select_no_player();
        bool saving_enabled();
        void save_profile_namespace();

        std::vector<object> switchable_units();

        std::string action_name(const std::string & action_);
        void activate_key(const std::string & keyname_);
        void add_switchable_unit(const object & unit_);
        float air_density_rtd(float altitude_);
        void airport_side(int id_);
        void airport_side(const object & target_);
        bool alive(const object & obj_);
        std::string animation_state(const object & unit_);
        object assigned_commander(const object & veh_);
        object assigned_driver(const object & veh_);
        object assigned_gunner(const object & veh_);
        object assigned_target(const object & veh_);
        std::string assigned_team(const object & unit_);
        object assigned_vehicle(const object & unit_);

        std::string behaviour(const object & unit_);
        std::string binocular(const object & unit_);
        void buldozer(bool value_);
        bool buldozer(const std::string &value_);
        bool can_fire(const object & unit_);
        bool can_move(const object & unit_);
        bool can_stand(const object & unit_);
        bool can_unload_in_combat(const object & unit_);
        bool captive(const object & unit_);
        float captive_num(const object & unit_);
        bool check_aifeature(const std::string & feature_);

        float collective_rtd(const object & helicopter_);
        object commander(const object & veh_);
        bool completed_fsm(float handle_);
        void copy_to_clipboard(const std::string & text_);
        side create_center(const side & side_);
        void create_vehicle_crew(const object & veh_);
        std::string current_command(const object & veh_);

        int current_vision_mode(const object & unit_);
        float current_zeroing(const object & gunner_);
        float damage(const object & object_);
        void de_activate_key(const std::string & key_);
        float debriefing_text(const std::string & debriefing_);
        void delete_center(const side & side_);
        void delete_collection(const object & collection_);
        bool delete_identity(const std::string & identity_);

        void delete_site(const object &value_);
        bool delete_status(const std::string &value_);
        void detach(const object &value_);
        bool did_jipowner(const object &value_);
        bool difficulty_enabled(const std::string &value_);

        void disable_remote_sensors(bool value_);
        void disable_user_input(bool value_);
        void dissolve_team(const std::string &value_);
        object driver(const object &value_);
        void echo(const std::string &value_);
        // TODO void edit(const std::string &value_); // Are we sure this is a valid sqf script command?
        object effective_commander(const object &value_);

        void enable_caustics(bool value_);
        void enable_diag_legend(bool value_);
        void enable_engine_artillery(bool value_);
        void enable_environment(bool ambient_life_, bool ambient_sound_ = true);
        void enable_radio(bool value_);
        void enable_sat_normal_on_detail(bool value_);
        void enable_sentences(bool value_);
        void enable_stress_damage(bool value_);
        void enable_team_switch(bool value_);
        void enable_traffic(bool value_);
        void end_mission(const std::string &value_);
        void estimated_time_left(float value_);
        float exec_fsm(const std::string &value_);
        void export_jipmessages(const std::string &value_);
        std::string face(const object &value_);
        std::string faction(const object &value_);
        void fail_mission(const std::string &value_);
        void fill_weapons_from_pool(const object &value_);
        display find_display(float value_);
        bool finite(float value_);

        object flag(const object &value_);
        object flag_owner(const object &value_);
        side flag_side(const object &value_);
        std::string flag_texture(const object &value_);
        bool fleeing(const object &value_);
        void force_respawn(const object &value_);
        object form_leader(const object &value_);
        float formation_direction(const object &value_);
        object formation_leader(const object &value_);
        std::string formation_task(const object &value_);
        float fuel(const object &value_);
        float gear_idcammo_count(float value_);
        float get_aiming_coef(const object &value_);
        float get_ammo_cargo(const object &value_);
        float get_anim_aim_precision(const object &value_);
        float get_anim_speed_coef(const object &value_);
        float get_bleeding_remaining(const object &value_);
        float get_burning_value(const object &value_);
        object get_connected_uav(const object &value_);
        float get_custom_aim_coef(const object &value_);
        float get_dlcusage_time(float value_);
        float get_dammage(const object &value_);
        float get_dir(const object &value_);
        float get_dir_visual(const object &value_);
        float get_fatigue(const object &value_);
        float get_fuel_cargo(const object &value_);

        float get_mass(const object &value_);
        float get_object_dlc(const object &value_);
        float get_object_type(const object &value_);
        float get_oxygen_remaining(const object &value_);
        std::string get_player_uid(const object &value_);
        float get_repair_cargo(const object &value_);
        float get_rotor_brake_rtd(const object &value_);
        object get_sling_load(const object &value_);
        float get_stamina(const object &value_);
        float get_stat_value(const std::string &value_);
        float get_suppression(const object &value_);
        float get_weapon_sway(const object &value_);
        float get_wings_orientation_rtd(const object &value_);
        float get_wings_position_rtd(const object &value_);
        std::string goggles(const object &value_);

        object gunner(const object &value_);
        float hands_hit(const object &value_);
        object hc_leader(const group &value_);
        void hc_remove_all_groups(const object &value_);
        std::string headgear(const object &value_);
        void hide_body(const object &value_);
        void hide_object(const object &value_);
        void hide_object_global(const object &value_);
        void hint_c(const std::string &value_);
        std::string hmd(const object &value_);
        std::string image(const std::string &value_);
        std::string incapacitated_state(const object &value_);
        bool inflamed(const object &value_);
        float input_action(const std::string &value_);
        bool is_able_to_breathe(const object &value_);
        bool is_aim_precision_enabled(const object &value_);
        bool is_auto_hover_on(const object &value_);
        bool is_auto_trim_on_rtd(const object &value_);
        bool is_autonomous(const object &value_);
        bool is_bleeding(const object &value_);
        bool is_burning(const object &value_);
        bool is_collision_light_on(const object &value_);
        bool is_copilot_enabled(const object &value_);
        bool is_dlcavailable(float value_);
        bool is_engine_on(const object &value_);
        bool is_forced_walk(const object &value_);
        bool is_formation_leader(const object &value_);
        bool is_hidden(const object &value_);
        bool is_in_remains_collector(const object &value_);
        bool is_key_active(const std::string &value_);
        bool is_light_on(const object &value_);
        bool is_localized(const std::string &value_);
        bool is_manual_fire(const object &value_);
        bool is_marked_for_collection(const object &value_);

        bool is_object_hidden(const object &value_);
        bool is_object_rtd(const object &value_);
        bool is_player(const object &value_);
        bool is_sprint_allowed(const object &value_);
        bool is_stamina_enabled(const object &value_);
        bool is_touching_ground(const object &value_);
        bool is_turned_out(const object &value_);
        bool is_uavconnected(const object &value_);
        bool is_walking(const object &value_);
        bool is_weapon_deployed(const object &value_);
        bool is_weapon_rested(const object &value_);
        std::string key_image(float value_);
        std::string key_name(float value_);
        std::string land_result(const object &value_);
        object laser_target(const object &value_);
        object leader(const object &value_);
        bool leaderboard_de_init(const std::string &value_);
        bool leaderboard_init(const std::string &value_);
        bool leaderboard_request_rows_friends(const std::string &value_);
        float leaderboard_state(const std::string &value_);
        std::string life_state(const object &value_);
        void light_detach_object(const object &value_);
        std::string light_is_on(const object &value_);

        std::string load_file(const std::string &value_);

        std::string localize(const std::string &value_);
        bool lock_identity(const object &value_);
        float locked(const object &value_);
        bool locked_driver(const object &value_);
        bool mine_active(const object &value_);
        float morale(const object &value_);
        void move_out(const object &value_);
        float move_time(const object &value_);
        bool move_to_completed(const object &value_);
        bool move_to_failed(const object &value_);
        std::string name(const object &value_);
        std::string name_sound(const object &value_);
        object nearest_building(const object &value_);
        object nearest_building(const vector3 &value_);
        float need_reload(const object &value_);
        std::string net_id(const object &value_);
        std::string net_id(const group &value_);
        float number_of_engines_rtd(const object &value_);
        object object_from_net_id(const std::string &value_);
        object object_parent(const object &value_);
        void on_briefing_group(const std::string &value_);
        void on_briefing_notes(const std::string &value_);
        void on_briefing_plan(const std::string &value_);
        void on_briefing_team_switch(const std::string &value_);
        float owner(const object &value_);
        float parse_number(const std::string &value_);
        float parse_number(bool value_);
        rv_text parse_text(const std::string &value_);
        void pick_weapon_pool(const object &value_);
        std::string pitch(const object &value_);
        void play_music(const std::string &class_);
        void play_music(const std::string &class_, float start_);
        void play_sound(const std::string &name_);
        void play_sound(const std::string &name_, bool force_);
        float playable_slots_number(const side &value_);
        float players_number(const side &value_);


        float precision(const object &value_);
        bool preload_sound(const std::string &value_);
        std::string preprocess_file(const std::string &value_);
        std::string preprocess_file_line_numbers(const std::string &value_);

        void process_diary_link(const std::string &value_);
        void progress_loading_screen(float value_);
        void public_variable(const std::string &value_);
        void public_variable_server(const std::string &value_);
        void put_weapon_pool(const object &value_);
        float query_items_pool(const std::string &value_);
        float query_magazine_pool(const std::string &value_);
        float query_weapon_pool(const std::string &value_);

        std::string rank(const object &value_);
        float rank_id(const object &value_);
        float rating(const object &value_);
        void reload(const object &value_);
        bool reload_enabled(const object &value_);
        void remove_all_actions(const object &value_);


        void remove_all_mission_event_handlers(const std::string &value_);
        void remove_all_music_event_handlers(const std::string &value_);

        void remove_switchable_unit(const object &value_);
        bool required_version(const std::string &value_);
        void reset_subgroup_direction(const object &value_);
        std::string role_description(const object &value_);
        bool rope_attach_enabled(const object &value_);
        object rope_attached_to(const object &value_);
        void rope_destroy(const object &value_);
        float rope_length(const object &value_);
        bool rope_unwound(const object &value_);
        void save_var(const std::string &value_);
        void scope_name(const std::string &value_);
        float score(const object &value_);
        float score_side(const side &value_);
        void script_name(const std::string &value_);
        float scud_state(const object &value_);

        void select_player(const object &value_);
        bool server_command(const std::string &value_);
        bool server_command_available(const std::string &value_);
        bool server_command_executable(const std::string &value_);
        void set_acc_time(float value_);

        void set_armory_points(float value_);

        void set_horizon_parallax_coef(float value_);
        void set_object_view_distance(float distance_);
        void set_object_view_distance(float object_distance_, float shadow_distance_);
        void set_playable(const object &value_);
        void set_player_respawn_time(float value_);
        void set_shadow_distance(float value_);
        void set_simul_weather_layers(float value_);
        void set_stamina_scheme(const std::string &value_);
        void set_system_of_units(float value_);
        void set_terrain_grid(float value_);
        void set_time_multiplier(float value_);
        void set_traffic_distance(float value_);
        void set_view_distance(float value_);
        bool simulation_enabled(const object &value_);
        float size_of(const std::string &value_);
        float skill(const object &value_);
        void skip_time(float value_);
        void sleep(float value_);

        bool some_ammo(const object &value_);
        std::string speaker(const object &value_);
        float speed(const object &value_);
        std::string stance(const object &value_);
        void stop_engine_rtd(const object &value_);
        bool stopped(const object &value_);
        std::string text(const std::string &value_);
        void title_fade_out(float value_);
        std::string to_lower(const std::string &value_);
        std::string to_upper(const std::string &value_);


        std::string type_of(const object &value_);
        void uisleep(float value_);
        void unassign_team(const object &value_);
        void unassign_vehicle(const object &value_);
        bool underwater(const object &value_);

        std::string unit_pos(const object &value_);//#sort
        float unit_recoil_coefficient(const object &value_);
        bool unlock_achievement(const std::string &value_);

        object vehicle(const object &value_);
        std::string vehicle_var_name(const object &value_);
        bool verify_signature(const std::string &value_);
        float waypoint_timeout_current(const group &value_);
        bool waypoints_enabled_uav(const object &value_);
        void enable_uav_waypoints(object & uav_, bool enable_);
        bool weapon_lowered(const object &value_);

        void add_live_stats(const object &value0_, float value1_);
        void add_rating(const object &value0_, float value1_);
        void add_score(const object &value0_, float value1_);
        void add_score_side(const side &value0_, float value1_);
        void add_vehicle(const group &value0_, const object &value1_);

        void allow_crew_in_immobile(const object &value0_, bool value1_);
        void allow_damage(const object &value0_, bool value1_);
        void allow_dammage(const object &value0_, bool value1_);

        void allow_sprint(const object &value0_, bool value1_);
        float ammo(const object &value0_, const std::string& value1_);
        float animation_phase(const object &value0_, const std::string& value1_);
        void assign_team(const object &value0_, const std::string& value1_);
        void assign_to_airport(const object &value0_, float value1_);
        void assign_to_airport(const object &value0_, const object &target_);




        void debug_fsm(float value0_, bool value1_);
        bool diary_subject_exists(const object &value0_, const std::string& value1_);
        void direct_say(const object &value0_, const std::string& value1_);
        void disable_ai(const object &value0_, const std::string& value1_);
        void disable_conversation(const object &value0_, bool value1_);
        void disable_nvgequipment(const object &value0_, bool value1_);
        void disable_tiequipment(const object &value0_, bool value1_);
        void display_remove_all_event_handlers(const std::string& value0_, const display &value1_);
        float door_phase(const object &value0_, const std::string& value1_);
        float empty_positions(const object &value0_, const std::string& value1_);
        void enable_ai(const object &value0_, const std::string& value1_);
        void enable_aifeature(bool value0_, const std::string& value1_);
        void enable_aim_precision(const object &value0_, bool value1_);
        void enable_auto_start_up_rtd(const object &value0_, bool value1_);
        bool enable_auto_trim_rtd(const object &value0_, bool value1_);
        void enable_copilot(const object &value0_, bool value1_);
        void enable_fatigue(const object &value0_, bool value1_);
        void enable_mimics(const object &value0_, bool value1_);
        void enable_reload(const object &value0_, bool value1_);
        void enable_rope_attach(const object &value0_, bool value1_);
        void enable_simulation(const object &value0_, bool value1_);
        void enable_simulation_global(const object &value0_, bool value1_);
        void enable_stamina(const object &value0_, bool value1_);
        void enable_uavwaypoints(const object &value0_, bool value1_);
        void engine_on(const object &value0_, bool value1_);
        void fire(const object &value0_, const std::string& value1_);
        void fly_in_height(const object &value0_, float value1_);
        void force_add_uniform(const object &value0_, const std::string& value1_);
        void force_speed(const object &value0_, float value1_);
        void force_walk(const object &value0_, bool value1_);

        float get_hit(const object &value0_, const std::string& value1_);
        float get_hit_index(const object &value0_, float value1_);
        float get_hit_point_damage(const object &value0_, const std::string& value1_);

        float get_speed(const object &value0_, const std::string& value1_);
        void global_radio(const object &value0_, const std::string& value1_);

        void hc_remove_group(const object &value0_, const group &value1_);
        void hide_object(const object &value0_, bool value1_);
        void hide_object_global(const object &value0_, bool value1_);
        void hint_c(const std::string& value0_, const std::string& value1_);

        void inflame(const object &value0_, bool value1_);
        bool is_flashlight_on(const object &value0_, const std::string& value1_);
        bool is_irlaser_on(const object &value0_, const std::string& value1_);
        bool is_kind_of(const object &obj_, const std::string &type_);
        bool is_kind_of(const std::string &type1_, const std::string &type2_);
        bool is_kind_of(const std::string &type1_, const std::string &type2_, const config &target_config_);

        bool kb_add_database(const object &value0_, const std::string& value1_);
        bool kb_add_database_targets(const object &value0_, const std::string& value1_);
        bool kb_has_topic(const object &value0_, const std::string& value1_);
        void kb_remove_topic(const object &value0_, const std::string& value1_);
        float knows_about(const object &source_, const object &target_);
        float knows_about(const group &source_, const object &target_);
        float knows_about(const side &side_, const object &target_);
        void land(const object &value0_, const std::string& value1_);
        void land_at(const object &value0_, float value1_);
        void land_at(const object &value0_, const object & helipad_);




        void leave_vehicle(const object &value0_, const group &value1_);
        void limit_speed(const object &value0_, float value1_);

        bool load_identity(const object &value0_, const std::string& value1_);
        bool load_status(const object &value0_, const std::string& value1_);
        void lock(const object &value0_, bool value1_);
        void lock(const object &value0_, float value1_);
        void lock_cargo(const object &value0_, bool value1_);
        void lock_driver(const object &value0_, bool value1_);
        bool locked_cargo(const object &value0_, float value1_);


        bool mine_detected_by(const object &value0_, const side &value1_);

        void play_action(const object &value0_, const std::string& value1_);
        void play_action_now(const object &value0_, const std::string& value1_);
        void play_gesture(const object &value0_, const std::string& value1_);
        void play_move(const object &value0_, const std::string& value1_);
        void play_move_now(const object &value0_, const std::string& value1_);


        void public_variable_client(float value0_, const std::string& value1_);
        bool register_task(const team_member &value0_, const std::string& value1_);
        void remove_action(const object &value0_, float value1_);
        void remove_all_event_handlers(const object &value0_, const std::string& value1_);
        void remove_all_mpevent_handlers(const object &value0_, const std::string& value1_);

        void reveal_mine(const object &value0_, const side &value1_);
        bool save_identity(const object &value0_, const std::string& value1_);
        bool save_status(const object &value0_, const std::string& value1_);
        void select_diary_subject(const object &value0_, const std::string& value1_);
        void send_simple_command(const object &value0_, const std::string& value1_);
        void set_actual_collective_rtd(const object &value0_, float value1_);
        void set_airport_side(float value0_, const side &value1_);
        void set_airport_side(const object & target_, const side &value1_);
        void set_ammo_cargo(const object &value0_, float value1_);
        void set_anim_speed_coef(const object &value0_, float value1_);
        void set_autonomous(const object &value0_, bool value1_);
        void set_bleeding_remaining(const object &value0_, float value1_);


        void set_collision_light(const object &value0_, bool value1_);
        void set_combat_mode(const team_member &value0_, const std::string& value1_);
        void set_custom_aim_coef(const object &value0_, float value1_);
        void set_custom_weight_rtd(const object &value0_, float value1_);
        void set_damage(const object &value0_, float value1_, bool use_effects_ = true);
        void set_dammage(const object &value0_, float value1_);
        void set_dir(const object &value0_, float value1_);
        void set_drop_interval(const object &value0_, float value1_);

        void set_face(const object &value0_, const std::string& value1_);
        void set_faceanimation(const object &value0_, float value1_);
        void set_fatigue(const object &value0_, float value1_);
        void set_flag_side(const object &value0_, const side &value1_);
        void set_flag_texture(const object &value0_, const std::string& value1_);
        void set_formation(const team_member &value0_, const std::string& value1_);
        void set_formation_task(const object &value0_, const std::string& value1_);
        void set_from_editor(const team_member &value0_, bool value1_);
        void set_fuel(const object &value0_, float value1_);
        void set_fuel_cargo(const object &value0_, float value1_);

        void set_identity(const object &value0_, const std::string& value1_);
        void set_light_brightness(const object &value0_, float value1_);
        void set_light_day_light(const object &value0_, bool value1_);
        void set_light_flare_max_distance(const object &value0_, float value1_);
        void set_light_flare_size(const object &value0_, float value1_);
        void set_light_intensity(const object &value0_, float value1_);
        void set_light_use_flare(const object &value0_, bool value1_);

        void set_mimic(const object &value0_, const std::string& value1_);
        void set_name(const object &value0_, const std::string& value1_);
        void set_name_sound(const object &value0_, const std::string& value1_);
        bool set_owner(const object &value0_, float value1_);
        void set_oxygen_remaining(const object &value0_, float value1_);
        void set_pilot_light(const object &value0_, bool value1_);
        void set_pitch(const object &value0_, float value1_);
        void set_radio_msg(float value0_, const std::string& value1_);
        void set_random_lip(const object &value0_, bool value1_);
        void set_rank(const object &value0_, const std::string& value1_);
        void set_repair_cargo(const object &value0_, float value1_);
        void set_rotor_brake_rtd(const object &value0_, float value1_);
        void set_skill(const object &value0_, float value1_);
        void set_speaker(const object &value0_, const std::string& value1_);
        void set_stamina(const object &value0_, float value1_);
        void set_suppression(const object &value0_, float value1_);
        void set_target_age(const object &value0_, const std::string& value1_);
        void set_unconscious(const object &value0_, bool value1_);
        void set_unit_ability(const object &value0_, float value1_);
        void set_unit_pos(const object &value0_, const std::string& value1_);
        void set_unit_pos_weak(const object &value0_, const std::string& value1_);
        void set_unit_rank(const object &value0_, const std::string& value1_);
        void set_unit_recoil_coefficient(const object &value0_, float value1_);
        void set_vehicle_ammo(const object &value0_, float value1_);
        void set_vehicle_ammo_def(const object &value0_, float value1_);
        void set_vehicle_armor(const object &value0_, float value1_);
        void set_vehicle_id(const object &value0_, float value1_);
        void set_vehicle_lock(const object &value0_, const std::string& value1_);
        void set_vehicle_var_name(const object &value0_, const std::string& value1_);

        float skill(const object &value0_, const std::string& value1_);
        float skill_final(const object &value0_, const std::string& value1_);


        void stop(const object &value0_, bool value1_);
        void suppress_for(const object &value0_, float value1_);
        void switch_action(const object &value0_, const std::string& value1_);

        void switch_gesture(const object &value0_, const std::string& value1_);
        void switch_light(const object &value0_, const std::string& value1_);
        void switch_move(const object &value0_, const std::string& value1_);



        bool unregister_task(const team_member &value0_, const std::string& value1_);
        void use_audio_time_for_moves(const object &value0_, bool value1_);
        void vehicle_radio(const object &value0_, const std::string& value1_);

        void delete_team(const team_member &value_);
        std::string formation(const team_member &value_);
        bool from_editor(const team_member &value_);
        bool is_agent(const team_member &value_);
        team_member leader(const team_member &value_);
        std::string team_name(const team_member &value_);
        std::string team_type(const team_member &value_);

        float radio_volume();
        void save_game();
        void save_joysticks();
        side side_enemy();
        side side_friendly();
        side side_logic();
        side side_unknown();
        team_member team_member_null();
        side west();
        bool buldozer_is_enabled_road_diag();
        void buldozer_reload_oper_map();
        void cancel_simple_task_destination(task value_);
        task current_task(const object &value_);
        script exec_vm(const std::string& value_);
        float priority(task value_);
        bool script_done(script value_);
        bool task_completed(task value_);
        task task_parent(task value_);
        std::string task_state(task value_);
        void terminate(script value_);
        std::string type(task value_);

        std::vector<object> near_objects(const vector3 &pos_, float radius_);
        std::vector<object> near_objects(const object &object_, float radius_);
        std::vector<object> near_objects(const vector3 &pos_, const std::string &type_, float radius_);
        std::vector<object> near_objects(const object &object_, const std::string &type_, float radius_);

        void hint(const std::string &text_);
        void hint_cadet(const std::string &text_);
        void hint_silent(const std::string &text_);


        std::vector<object> roads_connected_to(const object &obj_);
        std::vector<object> rope_attached_objects(const object &obj_);
        std::vector<object> ropes(const object &obj_);

        vector3 screen_to_world(const vector2 &pos_);


        std::string speed_mode(const object &obj_);
        std::string speed_mode(const group &grp_);

        rv_resolution get_resolution();

        std::vector<object> vehicles();

        game_value get_mission_config_value(const std::string& attribute_);
        game_value get_mission_config_value(const std::string& attribute_, game_value default_value_);

        void move(const object &unit_, const vector3 &pos_);
        void move(const group &group_, const vector3 &pos_);
        bool move_in_any(const object &unit_, const object &vehicle_);
        void move_in_cargo(const object &unit_, const object &vehicle_, int cargo_index_ = -1);
        void move_in_commander(const object &unit_, const object &vehicle_);
        void move_in_driver(const object &unit_, const object &vehicle_);
        void move_in_gunner(const object &unit_, const object &vehicle_);
        void move_in_turret(const object &unit_, const object &vehicle_, const std::vector<int> turret_path_);
        void move_to(const object &unit_, const vector3 &pos_);


        struct rv_artillery_computer_settings {
            std::string name;
            std::string ammo;
            int mode; // TODO investigate what this actually is

            rv_artillery_computer_settings(const game_value &rv_game_value_)
                : name(rv_game_value_[0]),
                ammo(rv_game_value_[1]),
                mode(rv_game_value_[2]) {}
        };

        rv_artillery_computer_settings get_artillery_computer_settings();

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

        rv_product_version product_version();

        // originally "side", but is already a type
        side get_side(const object &object_);


        std::string wf_side_text(const object &object_);
        std::string wf_side_text(const group &group_);
        std::string wf_side_text(const side &side_);

        float count_side(const side &side_, std::vector<object> &objects_);

        float get_friend(const side &side1_, const side &side2_);
        void set_friend(const side &side1_, const side &side2_, float value_);

        std::vector<object> entities(const std::string& type_);


        std::vector<object> nearest_terrain_objects(const vector3& pos_, const std::vector<std::string> types_, float radius_);
        std::vector<object> nearest_terrain_objects(const object& unit_, const std::vector<std::string> types_, float radius_);



        std::vector<object> units(const object& unit_);

        std::string call_extension(const std::string& extension_, const std::string& arguments_);


        void hintc(const std::string& title_, std::vector<std::string> content_);




        void remote_control(const object &controller_, const object &controlled_);

        void set_hit(const object &object_, const std::string &part_, float damage_);
        void set_hit_index(const object &object_, int part_index_, float damage_);
        void set_hit_point_damage(const object &object_, const std::string &hit_point_, float damage_);





        bool in(const object &unit_, const object &vehicle_);

        float add_mission_event_handler(const std::string &type_, const code &command_);
        float add_mission_event_handler(const std::string &type_, const std::string &command_);
        float add_music_event_handler(const std::string &type_, const code &command_);
        float add_music_event_handler(const std::string &type_, const std::string &command_);

        void add_weapon_pool(const std::string &weapon_name_, int count_);

        struct rv_vehicle_role {
            std::string role;
            std::vector<int> turret_path;
        };

        rv_vehicle_role assigned_vehicle_role(const object &unit_);


        std::string compose_text(const std::vector<std::string> &texts_);
        //#categorize this goes into tasks together with other tasks stuff 
        std::string create_diary_link(const std::string &subject_, const object &object_, const std::string &text_);
        std::string create_diary_record(const object &object_, const std::string &subject_, const std::string &text_);
        std::string create_diary_record(const object &object_, const std::string &subject_, const std::string &text_, const task &task_);
        std::string create_diary_record(const object &object_, const std::string &subject_, const std::string &text_, const task &task_, const std::string &state_);
        std::string create_diary_record(const object &object_, const std::string &subject_, const std::string &title_, const std::string &text_);
        std::string create_diary_record(const object &object_, const std::string &subject_, const std::string &title_, const std::string &text_, const task &task_);
        std::string create_diary_record(const object &object_, const std::string &subject_, const std::string &title_, const std::string &text_, const task &task_, const std::string &state_);
        float create_diary_subject(const object &object_, const std::string &subject_, const std::string &name_);
        float create_diary_subject(const object &object_, const std::string &subject_, const std::string &name_, const std::string &picture_);




        float linear_conversion(float min_, float max_, float value_, float new_min_, float new_max_);
        float linear_conversion(float min_, float max_, float value_, float new_min_, float new_max_, bool clamp_);

        bool is_on_road(const object &object_);
        bool is_on_road(const vector3 &position_);

        void host_mission(const config &config_, const display &display_);

        std::vector<group> hc_selected(const object &unit_);
        std::vector<group> hc_all_groups(const object &unit_);

        group get_group(const object &unit_); // originally "group", but is already a type

        vector3 get_wp_pos(const group &group_, int index_);

        void do_stop(const object &unit_);
        void do_stop(const std::vector<object> &units_);
        void do_get_out(const object &unit_);
        void do_get_out(const std::vector<object> &units_);

        std::vector<object> detected_mines(const side &side_);

        void diag_log(const std::string &text_);

        std::vector<bool> engines_is_on_rtd(const object &heli_);
        std::vector<float> engines_rpm_rtd(const object &heli_);
        std::vector<float> engines_torque_rtd(const object &heli_);

        struct rv_hit_points_damage {
            std::vector<std::string> hit_points;
            std::vector<std::string> hit_selections;
            std::vector<float> damages;
        };

        rv_hit_points_damage get_all_hit_points_damage(const object &veh_);

        struct rv_forces_rtd {
            float roll;
            float pitch;
            float collective;
        };

        std::vector<rv_forces_rtd> rotors_forces_rtd(const object &heli_);
        std::vector<rv_forces_rtd> wings_forces_rtd(const object &heli_);

        std::vector<float> rotors_rpm_rtd(const object &heli_);

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

        rv_weight_rtd weight_rtd(const object &heli_);

        void set_brakes_rtd(const object &heli_, float amount_, int wheel_index_);
        void set_engine_rpm_rtd(const object &heli_, float rpms_, int engine_index_);
        void set_wanted_rpm_rtd(const object &heli_, float rpms_, float time_, int engine_index_);


        int get_cargo_index(const object &vehicle_, const object &unit_);




        std::vector<std::string> get_object_materials(const object &object_);
        std::vector<std::string> get_object_textures(const object &object_);

        std::vector<object> group_selected_units(const object &unit_);


        std::vector<object> members(const team_member &team_);



        object nearest_object(const vector3 &pos_);
        object nearest_object(const vector3 &pos_, const std::string &type_);
        object nearest_object(const object &obj_, const std::string &type_);
        object nearest_object(const vector3 &pos_, float id_);
        std::vector<object> nearest_objects(const vector3 &pos_, const std::vector<std::string> &types_, float radius_);
        std::vector<object> nearest_objects(const object &obj_, const std::vector<std::string> &types_, float radius_);
        std::vector<object> nearest_terrain_objects(const vector3 &pos_, const std::vector<std::string> &types_, float radius_);
        std::vector<object> nearest_terrain_objects(const object &obj_, const std::vector<std::string> &types_, float radius_);


        void on_command_mode_changed(const code &command_);
        void on_command_mode_changed(const std::string &command_);

        void play_mission(const std::string &campaign_, const std::string &mission_);
        void play_mission(const std::string &campaign_, const std::string &mission_, bool skip_briefing_);
        void play_mission(const std::string &campaign_, const config &mission_);
        void play_mission(const std::string &campaign_, const config &mission_, bool skip_briefing_);

        void play_scripted_mission(const std::string &world_, const code &command_);
        void play_scripted_mission(const std::string &world_, const code &command_, const config &config_);
        void play_scripted_mission(const std::string &world_, const code &command_, const config &config_, bool ignore_child_window_);

        void play_sound_3d(const std::string &name_, const object &source_);
        void play_sound_3d(const std::string &name_, const object &source_, vector3 &pos_);
        void play_sound_3d(const std::string &name_, const object &source_, vector3 &pos_, float volume_);
        void play_sound_3d(const std::string &name_, const object &source_, vector3 &pos_, float volume_, float pitch_);
        void play_sound_3d(const std::string &name_, const object &source_, vector3 &pos_, float volume_, float pitch_, float distance_);





        std::vector<std::string> registered_tasks(const team_member &member_);

        void remove_from_remains_collector(const std::vector<object> &remains_);

        void remove_mission_event_handler(const std::string &type_, float index_);
        void remove_music_event_handler(const std::string &type_, float id_);

        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, const vector3 &to_point_, float segments_);
        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, const vector3 &to_point_, float segments_, float length_);
        object rope_create(const object &from_obj_, const std::string &from_point_, const object &to_obj_, const vector3 &to_point_, float segments_);
        object rope_create(const object &from_obj_, const std::string &from_point_, const object &to_obj_, const vector3 &to_point_, float segments_, float length_);
        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, const std::string &to_point_, float segments_);
        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, const std::string &to_point_, float segments_, float length_);
        object rope_create(const object &from_obj_, const std::string &from_point_, const object &to_obj_, const std::string &to_point_, float segments_);
        object rope_create(const object &from_obj_, const std::string &from_point_, const object &to_obj_, const std::string &to_point_, float segments_, float length_);
        object rope_create(const object &from_obj_, const vector3 &from_point_);
        object rope_create(const object &from_obj_, const vector3 &from_point_, float length_);
        object rope_create(const object &from_obj_, const std::string &from_point_);
        object rope_create(const object &from_obj_, const std::string &from_point_, float length_);

        void rope_cut(const object &rope_, float distance_);

        std::vector<vector3> rope_end_position(const object &rope_);

        void rope_unwind(const object &rope_, float speed_, float length_);
        void rope_unwind(const object &rope_, float speed_, float length_, bool relative_);



        struct rv_best_place {
            vector2 pos;
            float result;
        };

        std::vector<rv_best_place> select_best_places(const object &obj_, float radius_, const std::string &expression_, float precision_, float max_results_);
        std::vector<rv_best_place> select_best_places(const vector3 &pos_, float radius_, const std::string &expression_, float precision_, float max_results_);


        void set_compass_oscillation(float angle_, float freq_min_, float freq_max_);

        void set_detail_map_blend_pars(float full_detail_, float no_detail_);
        void set_group_icons_visible(bool map_, bool hud_);
        std::vector<bool> group_icons_visible();
        void set_hud_movement_levels(float min_speed_, float max_speed_, float min_alt_, float max_alt_, float min_dir_, float max_dir_, const object &obj_);
        void set_hud_movement_levels(float min_speed_, float max_speed_, float min_alt_, float max_alt_, float min_dir_, float max_dir_, const vector3 &pos_);
        void set_local_wind_params(float strength_, float diameter_);
        void set_mouse_position(float x_, float y_);
        float set_music_event_handler(const std::string &type_, const std::string &command_);
        bool set_stat_value(const std::string &name_, float value_);
        void set_traffic_density(float density_, float x_min_, float x_max_, float z_min_, float z_max_);
        void set_traffic_gap(float gap_, float x_min_, float x_max_, float z_min_, float z_max_);
        void set_traffic_speed(float speed_, float x_min_, float x_max_, float z_min_, float z_max_);

        std::vector<task> simple_tasks(const object& unit_);
        void simul_cloud_density(const vector3& pos_);
        void simul_cloud_occlusion(const vector3& pos1_, const vector3& pos2_);
        bool simul_in_clouds(const vector3& pos_);

        std::vector<std::string> squad_params(const object& unit_);
        void start_loading_screen(const std::string& text_);
        void start_loading_screen(const std::string& text_, const std::string& resource_);
        std::vector<std::string> support_info(const std::string& mask_);
        bool surface_is_water(const vector3& pos_);
        vector3 surface_normal(const vector3& pos_);
        std::string surface_type(const vector3& pos_);
        std::vector<object> synchronized_objects(const object& obj_);

        object cursor_object();
        float get_client_state_number();



        bool unit_ready(const object& unit_);
        std::vector<std::string> unit_addons(const std::string& class_);


        struct rv_uav_control {
            object unit;
            std::string position;

            rv_uav_control(const game_value &ret_game_value_) :
                unit(ret_game_value_[0]),
                position(ret_game_value_[1]) {}
        };

        rv_uav_control uav_control(const object& uav_);



        std::vector<std::string> task_description(const task& task_);
        void task_hint(const std::string& text_, const rv_color& color_, const std::string& icon_);

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



        struct rv_model_info {
            std::string name;
            std::string path;
            bool skeleton;

            rv_model_info(const game_value &ret_game_value_) :
                name(ret_game_value_[0]),
                path(ret_game_value_[1]),
                skeleton(ret_game_value_[2]) {}
        };

        rv_model_info get_model_info(const object& object_);



        void log_network_terminate(float handle_);




        vector3 task_destination(const task& task_);


        bool is_equal_to(const object& l_, const object& r_);
        std::string format(const std::vector<game_value> &params_);
        bool open_dlc_page(float value_);
        bool open_map(bool value_);
        bool open_youtube_video(const std::string &value_);
        bool show_subtitles(bool value_);
        bool open_map(bool show_, bool forced_);
        bool sling_load_assistant_shown();

        struct rv_camera_target {
            bool is_tracking;
            vector3 target_position;
            object target_object;
        };

        struct rv_shot_parents {
            object vehicle;
            object instigator;
        };

        struct rv_task_custom_data {
            std::string icon_path;
            std::string icon_text;
            std::string description_text;
        };

        struct rv_waypoint {
            group group;
            int index;
            //#TODO add to game_value conversion
        };

        //UNARY -- https://github.com/intercept/intercept/issues/13
        std::vector<float> action_ids(const object& entity_);
        std::vector<object> all_simple_objects(const std::vector<std::string> &params_);
        bool can_trigger_dynamic_simulation(const object &unit_);
        std::vector<std::string> config_source_addon_list(const config &config_);
        object create_simple_object(const std::string &shapename_, const vector3 &positionworld);
        void diag_capture_frame(float frame_);//#TODO make sure these don't call into engine if the funcptr is nullptr
        void diag_capture_frame_to_file(float frame_);
        void diag_capture_slow_frame(const std::string &section_, float threshold_);
        void diag_code_performance(const code &code_, const game_value &arguments_, float cycles_);
        void diag_dynamic_simulation_end(const std::string &type_);
        void diag_log_slow_frame(const std::string &section_, float threshold_);
        float difficulty_option(const std::string &optionname_);
        display display_parent(const display &display_);
        float dynamic_simulation_distance(const std::string &category_);
        float dynamic_simulation_distance_coef(const std::string &class_);
        bool dynamic_simulation_enabled(const object &object_);
        bool dynamic_simulation_enabled(const group &group_);
        void enable_debriefing_stats(float left_, float top_, float width_, float height_);
        void enable_dynamic_simulation_system(bool enable_);
        void enable_weapon_disassembly(bool enable_);
        std::vector<object> entities(const std::vector<std::string> &typesinclude_, const std::vector<std::string> &typesexclude_, bool includeCrews_, bool excludeDead_);
        float flag_animation_phase(const object &flag_);
        game_value get_all_env_sound_controllers(const vector3 &position_);
        std::vector<object> get_all_owned_mines(const object &unit_);
        game_value get_all_sound_controllers(const object &vehicle_);
        game_value get_array(const config config_);
        float get_container_max_load(const std::string &containerclass_);
        std::vector<object> get_mission_layer_entities(const std::string &layername_);
        vector3 get_pilot_camera_direction(const object &object_);
        vector3 get_pilot_camera_position(const object &object_);
        vector3 get_pilot_camera_rotation(const object &object_);
        rv_camera_target get_pilot_camera_target(const object &object_);
        rv_shot_parents get_shot_parents(const object &projectile_);
        std::vector<object> get_vehicle_cargo(const object &vehicle_);
        bool has_pilot_camera(const object &object_);
        bool is_group_deleted_when_empty(const group &group_);
        bool is_simple_object(const object &object_);
        object is_vehicle_cargo(const object &vehicle_);
        int lnb_add_row(int idc_, const std::vector<std::string> &items_);
        game_value mod_params(const std::string &mod_class_, const std::vector<std::string> &options_);
        float moon_phase(int year_, int month_, int day_, int hour_, float minute_);
        std::vector<game_value> parse_simple_array(const std::string &string_array_);
        
        game_value remote_exec(const std::string &function_name_, const std::string &jip_id_);
        game_value remote_exec(const std::string &function_name_, std::variant<int, object, side, group, std::reference_wrapper<const std::string>> target_, const std::string &jip_id_);
        game_value remote_exec(const std::string &function_name_, const game_value &targets_, const std::string &jip_id_);
        game_value remote_exec_call(const std::string &function_name_, const std::string &jip_id_);
        game_value remote_exec_call(const std::string &function_name_, std::variant<int, object, side, group, std::reference_wrapper<const std::string>> target_, const std::string &jip_id_);
        game_value remote_exec_call(const std::string &function_name_, const game_value &targets_, const std::string &jip_id_);
        void remove_3den_connection(const std::string &type_, const std::vector<object> &from_, const std::string &to_); //#TODO: Create class 'rv_eden_entity'
        void remove_all_owned_mines(const object &unit_);
        object road_at(const object &object_);
        object road_at(const vector3 &position_);
        bool screen_shot(const std::string &filename_);
        std::vector<std::string> selection_names(const object &object_);
        game_value select_max(const game_value &array_);
        game_value select_min(const game_value &array_);
        void set_3den_selected(const std::vector<object> &entites_);
        void show_score_table(int force_);
        void show_waypoints(bool enabled_);
        void switch_camera(const object &target_);
        bool task_always_visible(const task &task_);
        rv_task_custom_data task_custom_data(const task &task_);
        vector3 task_marker_offset(const object &unit_);
        std::string task_type(const task &task_);
        vector3 terrain_intersect_at_asl(const vector3 &pos1_, const vector3 &pos2_);
        void tv_collapse_all(int idc_);
        void tv_collapse_all(const control &control_);
        void tv_expand_all(int idc_);
        void tv_expand_all(const control &control_);
        vector3 unit_aim_position(const object &unit_);
        vector3 unit_aim_position_visual(const object &unit_);
        bool unit_is_uav(const object &unit_);
        void use_ai_oper_map_obstruction_test(bool use_);
        void use_ai_steering_component(bool use_);
        bool vehicle_cargo_enabled(const object &vehicle_);
        bool waypoint_force_behaviour(const group &group_, int index_);
        std::vector<rv_waypoint> waypoints(const object &player_);
        std::vector<rv_waypoint> waypoints(const group &group_);

        //NULAR -- https://github.com/intercept/intercept/issues/13
        std::vector<std::string> all_cut_layers();
        bool can_suspend();
        std::vector<script> diag_active_scripts();
        bool dynamic_simulation_system_enabled();
        std::pair<bool, bool> environment_enabled();
        std::pair<bool, bool> forced_map();
        std::vector<std::string> get_mission_layers();
        int get_terrain_grid();
        bool is_multiplayer_solo();
        bool is_remote_executed();
        bool is_remote_executed_jip();
        float pixel_grid();
        float pixel_grid_base();
        float pixel_grid_no_ui_scale();
        int shown_score_table();
        side side_ambient_life();
        side side_empty();
        bool user_input_disabled();
        bool visible_score_table();

        //BINARY -- https://github.com/intercept/intercept/issues/13
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
        struct rv_hc_group_params {
            std::string string;
            float f1;
            float f2;
            float f3;
            float f4;
        };
        struct rv_target {
            vector3 position;
            std::string type;
            side side;
            float subjective_cost;
            object object_;
            float position_accuracy;
        };

        rv_action_params action_params(const object &entity_, int id_);
        std::string add_editor_object(const control &map_, const std::string &type_, const game_value &values_, const std::string &subtype_class_);
        int add_menu(const control &map_, const std::string &text_, float priority_);
        int add_menu_item(const control &map_, const std::string &menu_, const std::string &text_, const std::string &command_, float priority_);
        int add_menu_item(const control &map_, int menu_, const std::string &text_, const std::string &command_, float priority_);
        int add_mp_event_handler(const object &object_, const std::string &type_, const std::string &expression_);
        int add_mp_event_handler(const object &object_, const std::string &type_, const code &expression_);
        void add_owned_mine(const object &unit_, const object &mine_);
        void add_player_scores(const object &unit_, int kills_infantry_, int kills_soft_, int kills_armor_, int kills_air_, int killed_);
        void add_public_variable_eventhandler(const std::string &var_name_, const code &code_);
        void add_public_variable_eventhandler(const std::string &var_name_, const object &target_, const code &code_);
        void add_resources(const team_member &team_member_, const std::vector<std::string> &resources_);
        void add_team_member(const team_member &team_, const team_member &member_);
        void animate_source(const object &object_, const std::string &source_, float phase_, bool speed_);
        void animate_source(const object &object_, const std::string &source_, float phase_, float speed_);
        float animation_source_phase(const object &object_, const std::string &source_);
        std::vector<game_value> apply(const std::vector<game_value> &array_, const code &code_);
        void assign_as_turret(const object &unit_, const object &vehicle_, const std::vector<int> &turret_path_);
        vector3 building_exit(const object &building_, int index_);
        vector3 building_pos(const object &building_, int index_);
        std::vector<game_value> call_extension(const std::string &extension_, const std::string &function_, std::vector<game_value> &arguments_);
        std::pair<bool, bool> can_vehicle_cargo(const object &vehicle_, const object &cargo_);
        void clear_3den_attribute(const game_value &unknown_, const std::string &attribute_);
        void command_suppressive_fire(const object &unit_, const object &target_);
        void command_suppressive_fire(const object &unit_, const vector3 &target_position_);
        bool connect_terminal_to_uav(const object &unit_, const object &uav_);
        int count_enemy(const object &unit_, const std::vector<object> &units_);
        int count_friendly(const object &unit_, const std::vector<object> &units_);
        int count_type(const std::string &type_, const std::vector<object> &objects_);
        int count_unknown(const object &unit_, const std::vector<object> &units_);
        game_value create_3den_entity(const group &group_, const std::string &mode_, const std::string &class_, const vector3 &position_, bool is_empty = false);
        display create_mission_display(const display &display_, const std::string &mission_);
        display create_mp_campaign_display(const display &display_, const std::string &mission_);
        task create_simple_task(const object &unit_, const std::string &name_, std::optional<task> parent_task_);
        object create_site(const std::string &type_, const vector3 &pos_);
        void ctrl_set_disabled_color(const control &control_, const rv_color &color_);
        std::string current_magazine_detail_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        std::string current_magazine_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        std::string current_weapon_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        void custom_radio(const object &unit_, int channel_, std::string &message_);
        int cut_fade_out(const std::string &layer_name_, float duration_);
        int cut_fade_out(int layer_, float duration_);
        int cut_obj(const std::string &layer_name_, const std::string &class_, const std::string &type_, float speed_, bool show_on_map_);
        int cut_obj(int layer_, const std::string &class_, const std::string &type_, float speed_, bool show_on_map_);
        int cut_rsc(const std::string &layer_name_, const std::string &class_, const std::string &type_, float speed_, bool show_on_map_);
        int cut_rsc(int layer_, const std::string &class_, const std::string &type_, float speed_, bool show_on_map_);
        int cut_text(const std::string &layer_name_, const std::string &text_, const std::string &type_, float speed_, bool show_on_map_);
        int cut_text(int layer_, const std::string &text_, const std::string &type_, float speed_, bool show_on_map_);
        void delete_editor_object(const control &map_, const std::string &object_);
        void delete_group_when_empty(const group &group_, bool delete_);
        void delete_resources(const team_member &team_member_, const std::vector<std::string> resources_);
        void delete_vehicle_crew(const object &vehicle_, const object &unit_);
        void disable_collision_with(const object &object1_, const object &object2_);
        void disable_uav_connectability(const object &object_, const object &uav_, bool check_all_items_);
        int display_add_event_handler(const display &display_, const std::string &event_name_, const std::string &code_);
        int display_add_event_handler(const display &display_, const std::string &event_name_, const code &code_);
        void display_remove_eventhandler(const display &display_, const std::string &event_name_, int id_);
        void display_set_eventhandler(const display &display_, const std::string &event_name_, const std::string &code_);
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
        void do_artillery_fire(const object &unit_, const vector3 &position_, float radius_, int rounds_);
        void do_artillery_fire(const std::vector<object> &units_, const vector3 &position_, float radius_, int rounds_);
        void do_fire(const object &unit_, const object &target_);
        void do_fire(const std::vector<object> &units_, const object &target_);
        void do_follow(const object &unit_, const object &target_);
        void do_follow(const std::vector<object> &units_, const object &target_);
        void do_fsm(const object &unit_, const std::string &fsm_name_, const vector3 &position_, const object &target_);
        void do_fsm(const std::vector<object> &units_, const std::string &fsm_name_, const vector3 &position_, const object &target_);
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
        void draw_arrow(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, const rv_color &color_);
        void draw_ellipse(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> center_, const vector2 &radius_, float angle_, const rv_color &color_, const std::string &fill_texture);
        void draw_line(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, const rv_color &color_);
        void draw_link(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, const std::string &param_type_, const std::string &line_type_, rv_color &color_);
        void draw_location(const control &map_, const location &location_);
        void draw_polygon(const control &map_, const std::vector<vector3> &polygon_, const rv_color &color_);
        game_value edit_object(const control &map_, const std::string &object_);
        void editor_set_event_handler(const control &map_, const std::string &event_type_, std::string &event_function_);
        void enable_attack(const group &group_, bool enable_);
        void enable_channel(int channel_, bool chat_, bool voice_over_net_);
        void enable_collision_with(const object &object1_, const object &object2_);
        void enable_dynamic_simulation(const object &object_, bool enable_);
        void enable_dynamic_simulation(const group &group_, bool enable_);
        void enable_gun_lights(const object &unit_, bool &enable_);
        void enable_gun_lights(const group &group_, bool &enable_);
        void enable_ir_lasers(const object &unit_, bool &enable_);
        void enable_ir_lasers(const group &group_, bool &enable_);
        void enable_person_turret(const object &vehicle_, const std::vector<int> &turrent_path_, bool enable_);
        void enable_uav_connect_ability(const object &unit_, const object &uav_, bool check_all_items_);
        void enable_vehicle_cargo(const object &vehicle_, bool enable_);
        void enable_weapon_disassembly(const object &unit_, bool enable_);
        game_value eval_object_argument(const control &map_, const std::string &object_, const std::string &argument_);
        void exec(const game_value &argument_, const std::string &script_);
        game_value exec_editor_script(const control &map_, std::string &object_, std::string &script_);
        int exec_fsm(const game_value &arguments_, const std::string &file_name_);
        script exec_vm(const game_value &arguments_, const std::string &file_name_);
        void fade_music(float time_, float volume_);
        void fade_radio(float time_, float volume_);
        void fade_sound(float time_, float volume_);
        void fade_speech(float time_, float volume_);
        object find_cover(const object &object_, const vector3 &position_, const vector3 &hide_position_, float max_dist_, std::optional<float> min_dist_, std::optional<vector3> visible_position_, std::optional<object> ignore_object_);
        vector3 find_empty_position(std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> center_, float min_distance_, float max_distance_, std::optional<std::string> vehicle_type_);
        bool find_empty_position_ready(std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> center_, float radius_, float max_distance_);
        //#TODO use t_in_area typedef for position
        object find_nearest_enemy(const object &unit_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_);
        object find_nearest_enemy(const object &unit_, const object &object_);
        void fire(const object &unit_, const std::string &muzzle_, const std::string &mode_, const std::string &magazine_);
        bool fire_at_target(const object &unit_, const object &target_, std::optional<std::string> muzzle_);
        void fly_in_height_asl(const object &aircraft_, float height_careless_safe_aware_, float height_combat_, float height_stealth_);
        void force_follow_road(const object &vehicle_, bool follow_);
        void force_weapon_fire(const object &unit_, const std::string &muzzle_, const std::string &fire_mode_);
        std::vector<game_value> get_3den_attribute(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const group>, std::reference_wrapper<const std::string>, std::reference_wrapper<float>> entity_, const std::string &attribute_);
        game_value get_3den_mission_attribute(const std::string &section_, const std::string &class_);
        float get_artillery_eta(const object &unit_, const vector3 &target_position_, const std::string &magazine_type_);
        typedef std::variant<std::reference_wrapper<const object> , std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> t_sqf_in_area_position;
        float get_dir(t_sqf_in_area_position from_, t_sqf_in_area_position to_);
        float get_env_sound_controller(const vector3 &position_, const std::string &controller_);
        game_value get_fsm_variable(int &fsm_handle_, const std::string &variable_, std::optional<game_value> default_value_);
        std::vector<game_value> get_group_icon(const group &group_, int &id_);
        vector3 get_hide_from(const object &unit_, const object &enemy_);
        std::string get_object_argument(const control &map_, const object &object_, const std::string &argument_);
        std::vector<std::string> get_object_children(const control &map_, const std::string &object_);
        float get_sound_controller(const object &vehicle_, const std::string &controller_);
        float get_sound_controller_result(const object &object_, const config &config_entry_);
        std::variant<bool, float> get_unit_trait(const object &unit_, const std::string &skill_name_);
        game_value get_variable(const control &control_, const std::string &variable_, std::optional<game_value> default_value_);
        game_value get_variable(const task &task_, const std::string &variable_, const game_value &default_value_);
        game_value get_variable(const location &location_, const std::string &variable_, const game_value &default_value_);
        void glance_at(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const std::vector<object>>> unit_, std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector3>> target_);
        void group_select_unit(const object &player_, const object &unit_, bool select_);
        rv_hc_group_params hc_group_params(const object &unit_, const group &group_);
        void hc_select_group(const object &unit, const std::vector<game_value> &array_);
        void hc_set_group(const object &unit_, const group &group_, std::optional<std::string> group_name_, std::optional<game_value> team_);
        void hide_selection(const object &object_, const std::string &selection_, bool hide_);
        bool in_area(t_sqf_in_area_position position_, const object &trigger_);
        bool in_area(t_sqf_in_area_position position_, const std::string &marker_);
        bool in_area(t_sqf_in_area_position position_, t_sqf_in_area_position center_, float radius_x_, float radius_y_, float angle_, bool is_rectangle_, std::optional<float> radius_z_);
        bool in_area(const object &object_, const location &location_);
        bool in_area(t_sqf_in_area_position position_, const location &location_);
        typedef std::variant<std::reference_wrapper<const std::vector<object>>, std::reference_wrapper<const std::vector<vector2>>, std::reference_wrapper<const std::vector<vector3>>> t_sqf_in_area_position_array;
        bool in_area_array(t_sqf_in_area_position_array position_, const object &trigger_);
        bool in_area_array(t_sqf_in_area_position_array position_, const std::string &marker_);
        bool in_area_array(t_sqf_in_area_position_array position_, t_sqf_in_area_position center_, float radius_x_, float radius_y_, float angle_, bool is_rectangle_, std::optional<float> radius_z_);
        bool in_area_array(t_sqf_in_area_position_array position_, const location &location_);
        bool in_polygon(const vector3 &position_, const std::vector<vector3> &polygon_);
        bool in_range_of_artillery(const vector3 &position_, const std::vector<object> &units_, const std::string &magazine_type_);
        std::string insert_editor_object(const control &map_, const std::string &type_, const game_value &value_, const std::vector<std::string> &values_, const std::string &sub_type_);
        std::vector<vector3> is_flat_empty(const vector3 &position_, float min_distance_, float max_gradient_, float max_gradient_radius_, float over_land_or_water, bool shore_line_, const object &ignore_object_);
        bool is_uav_connectable(const object &unit_, const object &uav_, bool check_all_items_);
        void kb_add_topic(const object &unit_, const std::string &topic_name_, const std::string &bikb_file_, const std::string &fsm_file_, std::variant<std::reference_wrapper<const code>, std::reference_wrapper<const std::string>> event_handler_);
        void kb_react();
        void kb_tell(const object &unit_, const object &receiver_, const std::string &topic_name_, const std::string &sentence_class_, const std::string &argument_name_, const code &argument_value_, const std::string &argument_text_, const std::vector<std::string> &argument_speech_, std::variant<std::reference_wrapper<bool>, std::reference_wrapper<int>, std::reference_wrapper<const std::string>> force_radio_);
        bool kb_was_said(const object &unit_, const object &receiver_, const std::string &topic_, const std::string &sentence_id_, int max_age_);
        void lb_set_text(const control &control_, int index_, const std::string &text_);
        void leave_vehicle(const object &unit_, const object &vehicle_);
        void light_attach_object(const object &light_, const object &object_, const vector3 &offset_);
        std::vector<std::string> list_objects(const control &map_, const std::string &type_);
        void lock_camera_to(const object &vehicle_, const object &target_, const std::vector<int> &turret_path_);
        void lock_cargo(const object &vehicle_, int index_, bool lock_);
        bool locked_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        void lock_turret(const object &vehicle_, const std::vector<int> &turret_path_, bool lock_);
        void lock_wp(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const group>> target_, bool lock_);
        void look_at(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const std::vector<object>>> units_, std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector3>> target_);
        void look_at_pos(const control &map_, const vector3 &position_);
        std::vector<std::string> magazines_turret(const object &vehicle_, const std::vector<int> &turret_path_);
        int magazine_turret_ammo(const std::string &magazine_class_, const std::vector<int> &turret_path_);
        vector3 model_to_world(const object &object_, const vector3 &offset_);
        bool near_objects_ready(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_);
        std::vector<object> near_roads(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_);
        std::vector<object> near_supplies(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_, float radius_);
        std::vector<rv_target> near_targets(const object &unit_, float radius_);
        int nmenu_items(const control &map_, const std::string &menu_name_);
        int nmenu_items(const control &map_, int index_);
        void obj_status(const std::string &objective_number_, const std::string &status_);
        game_value on_double_click(const control &map_, const std::string &command_);
        void on_map_single_click(const game_value &params_, std::variant<std::reference_wrapper<const std::string>, std::reference_wrapper<const code>> command_);
        game_value on_show_new_object(const object &control_, const std::string &command_);
        void order_get_in(const std::vector<object> &units_, bool order_);
        void pp_effect_adjust(std::variant<std::reference_wrapper<const std::string>, std::reference_wrapper<int>> effect_, const game_value &settings_);
        void pp_effect_commit(std::variant<std::reference_wrapper<const std::vector<int>>, std::reference_wrapper<int>> effect_, const float &duration_);
        void pp_effect_enable(const std::vector<int> &effets_, bool enable_);
        bool preload_object(float distance_, const object &object_);
        bool preload_object(float distance_, const std::string &class_name_);
        int push_back_unique(const std::vector<game_value> &array_, const game_value &element_);
        void radio_channel_add(int index_, const std::vector<object> &units_);
        void radio_channel_remove(int index_, const std::vector<object> &units_);
        float random(float seed_, float x_, std::optional<float> y_);
        game_value remote_exec(const game_value &params_, const std::string &function_, std::variant<int, object, std::reference_wrapper<const std::string>, side, group, std::reference_wrapper<const std::vector<game_value>>> targets_, std::optional<std::variant<std::reference_wrapper<const std::string>, bool, object, group>> jip_);
        game_value remote_exec_call(const game_value &params_, const std::string &function_, std::variant<int, object, std::reference_wrapper<const std::string>, side, group, std::reference_wrapper<const std::vector<game_value>>> targets_, std::optional<std::variant<std::reference_wrapper<const std::string>, bool, object, group>> jip_);
        void remove_curator_addons(const object &curator_module_, const std::vector<std::string> &addons_);
        void remove_curator_editable_objects(const object &curator_module, const std::vector<object> &objects_, bool &remove_crew_);
        void remove_draw_icon(const control &map_, const std::string &object_, const std::string &string_identifier);
        void remove_draw_links(const control &map_, const std::string &object_, const std::string &string_identifier);
        void remove_event_handler(const object &object_, const std::string &event_, int index_);
        void remove_mp_event_handler(const object &object_, const std::string &event_, int index_);
        void remove_owned_mine(const object &unit_, const object &mine_);
        void remove_simple_task(const object &unit_, const task &task_);
        void remove_team_member(const team_member &team_, const team_member &member_);
        void respawn_vehicle(const object &vehicle_, float delay_, int count_);
        void reveal(std::variant<object, group> &unit_, const object &target_);
        void reveal(std::variant<object, group> &unit_, const std::vector<object> &targets_);
        void rope_attach_to(const object &vehicle_, const vector3 &offset_, const vector3 &rope_end_down_dir_, const object &rope_);
        void rope_detach(const object &vehicle_, const object &rope_);
        
        
        
        task create_task(const team_member& member_, const std::string& type_, float priority, const std::vector<std::pair<std::string, std::string>>& name_value_pairs_, std::optional<task> parent_task_ = {});

        void say(const object& from_, const std::string& sound_classname_);
        void say(const object& from_, const std::string& sound_classname_, float max_tiles_distance, float speed = 1.f);
        void say(const object& from_, const object& to_, const std::string& sound_classname_);
        void say(const object& from_, const object& to_, const std::string& sound_classname_, float max_tiles_distance, float speed = 1.f);

        void say_2d(const object& from_, const std::string& sound_classname_);
        void say_2d(const object& from_, const std::string& sound_classname_, float max_tiles_distance, float speed = 1.f);
        void say_2d(const object& from_, const object& to_, const std::string& sound_classname_);
        void say_2d(const object& from_, const object& to_, const std::string& sound_classname_, float max_tiles_distance, float speed = 1.f);

        void say_3d(const object& from_, const std::string& sound_classname_);
        void say_3d(const object& from_, const std::string& sound_classname_, float max_tiles_distance, float speed = 1.f);
        void say_3d(const object& from_, const object& to_, const std::string& sound_classname_);
        void say_3d(const object& from_, const object& to_, const std::string& sound_classname_, float max_tiles_distance, float speed = 1.f);

        //#TODO return game_value or split into vector of game_values? 
        game_value select(game_value array_, const code& code_);
        game_value select_editor_object(const control& map_, const std::string& object_);
        void select_weapon_turret(const object&, const std::string& weapon_, const std::vector<int>& turretPath_);
        //#TODO arguments incorrect
        task send_task(const team_member &sender_, const team_member &receiver_, const std::string &type_);
        task send_task(const team_member &sender_, const team_member &receiver_, const std::string &type_, const task &parent_task_, float priority_, std::vector<std::string> &values_);
        void send_task_result(const task &task_, const game_value &state_, const game_value &result_, const game_value &sentence_);
        //Server/Headless Client only! 
        void serverCommand(const std::string& command_, const std::string& password_);
        bool set_3den_mission_attribute(const std::string& section_, const std::string& attribute_class_, game_value _attribute_value);

        //#TODO not object but Eden_Entity 
        //#TODO typedef variant for Eden_Entity 
        //#TODO use it for https://community.bistudio.com/wiki/Special:WhatLinksHere/Eden_Entity 
        bool set_3den_attribute(const object& entity_, const std::string& attribute_class_, game_value _attribute_value);
        //#TODO not object but Eden_Entity 
        bool set_3den_layer(const object& entity_, float layer_);
        void set_3den_object_type(const std::vector<object> & objects_, const std::string& classname_);

        rv_text set_attributes(const rv_text &text_, const std::vector<std::pair<std::string, std::variant<rv_text, std::reference_wrapper<const std::string>>>> &attributes_);
        //#TODO take Enum as behaviour 
        void set_behaviour(std::variant<group, object> group_, const std::string& behaviour_);
        void set_captive(const object& object_, bool status);
        /**
        * \brief Mark a unit as captive. If unit is a vehicle, commander is marked. A captive is neutral to everyone (belong to civilian side), and will not trigger "detected by" conditions for its original side.
        * \param object_
        * \param status Using a number (instead of a boolean) for the status has no further effect on the engine's behavior, but can be used by captiveNum to keep track of the captivity status at a finer resolution (e.g. handcuffed, grouped, etc.). The numbered status syntax was introduced in Arma 2.
        */
        void set_captive(const object& object_, float status);

        void set_center_of_mass(const object& object_, const vector3& offset_, float time_ = 0.f);

        //#TODO take enum 
        void set_combat_mode(std::variant<group, object> group_, const std::string& mode_);
        //#TODO take enum 
        void set_formation(std::variant<group, object> group_, const std::string& mode_);
        void set_convoy_seperation(const object& object_, float distance_);
        void set_curator_coef(const object& curator_, const std::string& action_, std::variant<float, bool> coef_);
        void set_current_task(const object& object_, const task& task_);

        void set_debriefing_text(const std::string& endType_, const std::string& title_, const std::string& description_);
        //#TODO Enum for planningMode 
        void set_destination(const object& object_, const vector3& position_, const std::string& planning_mode_, bool force_replan);
        void set_direction(const location& location_, float direction_);
        void set_draw_icon(const control &map_, const object &object_, const std::string &texture_, const rv_color &color_, const vector3 &offset_, float width_, float height_, float size_, float angle_, const std::string &identifier_, float shadow_, bool is_3d_, bool draw_line_, float priority_);
        //category AI 
        void set_drive_on_path(const object& object_, const std::vector<vector3>& points_);
        /**
        * \brief
        * \param category_ - one of:

        "Group" - Infantry units. Set to a reasonable distance, player should not see disabled infantry units. Default: 500m
        "Vehicle" - Vehicles with crew. Set to a reasonable distance, player should not see disabled vehicles. Default: 350m
        "EmptyVehicle" - All vehicles without crew. Separated from Props as Empty Vehicles have often more complex damage states and selective destruction. Their activation distance should by larger that the one used for Props. Default: 250m
        "Prop" - Static objects. Anything from a small tin can to a building. Default: 50m

        * \param distance_
        */
        void set_dynamic_simulation_distance(const std::string& category_, float distance_);
        //#TODO add BIKI entry and implement 
        //void set_dynamic_simulation_distance_coef(const std::string&, float); //binary__setdynamicsimulationdistancecoef__string__scalar__ret__nothing 
        enum class feature_type {
            disabled = 0,// - Feature disabled 
            visible_object_distance = 1,// - Object is always visible within object view distance 
            visible_terrain_distance = 2// - Object is always visible within terrain view distance 
        };
        bool set_feature_type(const object& object_, feature_type type_);

        float set_flag_animation_phase(const object& object_, float phase);
        void set_flag_owner(const object& flag_, const object& owner_);
        void set_fog(float time_, float fog_);
        void set_fog(float time_, float fog_value_, float fog_decay_, float fog_base_);
        //category AI 
        void set_form_dir(std::variant<group, object> group_, float heading_);

        void set_fsm_variable(float handle_, const std::string& name_, game_value value_);
        void set_group_icon(const group& group_, float icon_id, const std::string& icon_path_, const vector2 offset_);



        void set_editor_object_scope(const control &map_, const std::vector<std::string> &objects_, const std::string &editor_type_, const std::string &condition_, const std::string &scope_, bool sub_ordinates_also_);
        void set_effect_condition(std::variant<object, rv_waypoint> unit_, const std::string &statement_);
        bool set_feature_type(const object &object_, int type_);
        void set_flag_animation_phase(const object &flag_, float &animation_phase_);
        void set_flag_owner(const object &flag_, const object &owner_);
        void set_fog(float &time_, float &fog_value_, std::optional<float> fog_decay_, std::optional<float> fog_base_);
        void set_formation(const group &group_, const std::string &formation_);
        void set_form_dir(const group &group_, float heading_);
        void set_fsm_variable(int fsm_handle_, const std::string &variable_, const game_value &value_);
        void set_group_icon(const group &group_, int id_, const std::string &icon_, const vector2 &offset_);
        void set_group_icon_params(const group &group_, const rv_color &color_, const std::string &text_, float scale_, bool visible_);
        void set_group_id(const group &group_, const std::string &name_format_, const std::vector<std::string> &params_);
        void set_group_id_global(const group &group_, const std::string &name_format_, const std::vector<std::string> &params_);
        void set_gusts(float time_, float gusts_value_);
        void set_hide_behind(const object &unit_, const object &object_where_hide_, const vector3 &hide_position_);

    }
}