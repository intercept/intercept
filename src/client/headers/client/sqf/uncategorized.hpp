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

using namespace intercept::types;

namespace intercept {
    namespace sqf {

        
        // TODO void edit(sqf_string_const_ref value_); // Are we sure this is a valid sqf script command?


        //these 3 into one category like post process?
        //3D stuff
        void draw_line_3d(const vector3 &pos1_, const vector3 &pos2_, const rv_color &color_);
        void draw_icon_3d(sqf_string_const_ref texture_, const rv_color &color_, const vector3 &pos_agl_, float width_, float height_, float angle_, sqf_string_const_ref text_ = "", float shadow_ = 1.0f, float text_size_ = 1.0f, sqf_string_const_ref font_ = "TahomaB");
        
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
       
        

        
        
                
        //vehicles - new cat
        int airplane_throttle(const object &airplane_);
        sqf_return_string_list get_pylon_magazines(const object &vehicle_);
        sqf_return_string get_forced_flag_texture(const object &flag_pole_);
        bool is_damage_allowed(const object &object_);

        bool vehicle_receive_remote_targets(const object &vehicle_);
        bool vehicle_report_own_position(const object &vehicle_);
        bool vehicle_report_remote_targets(const object &vehicle_);

        int ammo_on_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_);
        int ammo_on_pylon(const object &vehicle_, int pylon_index_);
        void animate_bay(const object &vehicle_, sqf_string_const_ref pylon_name_, float anim_phase_);
        void animate_bay(const object &vehicle_, int pylon_index_, float anim_phase_);
        void animate_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_, float anim_phase_);
        void animate_pylon(const object &vehicle_, int pylon_index_, float anim_phase_);
        void confirm_sensor_target(const object &vehicle_, const side &side_, bool is_confirmed_);

        void force_flag_texture(const object &object_, sqf_string_const_ref texture_);
        bool is_sensor_target_confirmed(const object &object_, const side &side_);
        void report_remote_target(const side &side_, const object &target_, float time_);
        void set_air_plane_throttle(const object &airplane_, float throttle_);
        void set_ammo_on_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_, int ammo_count_);
        void set_ammo_on_pylon(const object &vehicle_, int pylon_index_, int ammo_count_);
        bool set_pylon_loadout(const object &object_, game_value param_right);
        void set_pylons_priority(const object &object_, const std::vector<int> &priorities_);
        void set_vehicle_radar(const object &object_, int rules_);
        void set_vehicle_receive_remote_targets(const object &vehicle_, bool receive_);
        void set_vehicle_report_own_position(const object &vehicle_, bool report_);
        void set_vehicle_report_remote_targets(const object &vehicle_, bool report_);
        
        bool is_collision_light_on(const object &value_);
        void enable_copilot(const object &value0_, bool value1_);
        void set_pilot_light(const object &value0_, bool value1_);
        void set_collision_light(const object &value0_, bool value1_);
        float set_flag_animation_phase(const object& object_, float phase);
        void set_flag_owner(const object& flag_, const object& owner_);
        void set_flag_animation_phase(const object &flag_, float &animation_phase_);
        object create_vehicle_local(sqf_string_const_ref type_, const vector3 &pos_atl_);
        void add_to_remains_collector(const std::vector<object> & objects_);
        void remove_from_remains_collector(const std::vector<object> &remains_);
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
        float flag_animation_phase(const object &flag_);
        object create_mine(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f);


        void unassign_vehicle(const object &value_);

        void assign_to_airport(const object &value0_, float value1_);
        void assign_to_airport(const object &value0_, const object &target_);

        void set_light_brightness(const object &value0_, float value1_);
        void set_light_day_light(const object &value0_, bool value1_);
        void set_light_flare_max_distance(const object &value0_, float value1_);
        void set_light_flare_size(const object &value0_, float value1_);
        void set_light_intensity(const object &value0_, float value1_);
        void set_light_use_flare(const object &value0_, bool value1_);
        void set_light_ambient(const object &light_, float r_, float g_, float b_);
        void set_light_attenuation(const object &light_, float start_, float constant_, float linear_, float quadratic_, float hard_limit_start_, float hard_limit_end_);
        void set_light_color(const object &light_, float r_, float g_, float b_);

        std::vector<object> roads_connected_to(const object &obj_);

        // originally "side", but is already a type
        side get_side(const object &object_);
        sqf_return_string wf_side_text(const object &object_); //https://community.bistudio.com/wiki/WFSideText
        sqf_return_string wf_side_text(const group &group_);
        sqf_return_string wf_side_text(const side &side_);
        rv_uav_control uav_control(const object& uav_);


        //units - new cat
        void set_user_mfd_value(const object &object_, int index_, float value_);
        void forget_target(const object &unit_, const object target_);
        void forget_target(const group &group_, const object target_);
        void targets(const object &unit_, std::optional<bool> enemy_only_, std::optional<float> max_distance_, std::optional<std::vector<side>> sides_, std::optional<float> max_age_, std::optional<std::variant<std::reference_wrapper<vector2>, std::reference_wrapper<vector3>>> alternate_center_);
        
        bool is_uav_connectable(const object &unit_, const object &uav_, bool check_all_items_);
        object camera_on();
        bool can_unload_in_combat(const object & unit_);

        void ais_finish_heal(const object &wounded_, const object &medic_, bool medic_can_heal_);

        void set_hide_behind(const object &unit_, const object &object_where_hide_, const vector3 &hide_position_);
        bool in(const object &unit_, const object &vehicle_);

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
        void set_custom_aim_coef(const object &value0_, float value1_);
        void allow_sprint(const object &value0_, bool value1_);
        float animation_phase(const object &value0_, sqf_string_const_ref value1_);
        void unassign_team(const object &value_);
        object get_connected_uav(const object &value_);
        float get_custom_aim_coef(const object &value_);
        void remove_owned_mine(const object &unit_, const object &mine_);
        void reveal(std::variant<object, group> &unit_, const object &target_);
        void reveal(std::variant<object, group> &unit_, const std::vector<object> &targets_);
        float get_aiming_coef(const object &value_);

        
        //core
        //onEvent
        void on_command_mode_changed(const code &command_);
        void on_command_mode_changed(sqf_string_const_ref command_);
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

        sqf_return_string image(sqf_string_const_ref value_);
        bool is_localized(sqf_string_const_ref value_);
        sqf_return_string localize(sqf_string_const_ref value_);
        game_value text(sqf_string_const_ref value_);
        sqf_return_string format(const std::vector<game_value> &params_);
        sqf_return_string compose_text(sqf_string_list_const_ref texts_);
        sqf_return_string endl();
        bool verify_signature(sqf_string_const_ref value_);
        void script_name(sqf_string_const_ref value_);
        bool required_version(sqf_string_const_ref value_);
        void save_var(sqf_string_const_ref value_);
        void scope_name(sqf_string_const_ref value_);
        float playable_slots_number(const side &value_);
        float players_number(const side &value_);
        //Seriously? Either remove this or just return PI instead of calling into Arma
        float pi();
        std::vector<object> playable_units();
        object player();
        float player_respawn_time();
        side player_side();
        std::vector<object> switchable_units();
        void add_switchable_unit(const object & unit_);
        side create_center(const side & side_); //not used in A3
        void delete_center(const side & side_);
        void disable_user_input(bool value_);
        void echo(sqf_string_const_ref value_);
        void end_mission(sqf_string_const_ref value_);
        void estimated_time_left(float value_);
        void fail_mission(sqf_string_const_ref value_);
        int count_enemy(const object &unit_, const std::vector<object> &units_);
        int count_friendly(const object &unit_, const std::vector<object> &units_);
        int count_type(sqf_string_const_ref type_, const std::vector<object> &objects_);
        int count_unknown(const object &unit_, const std::vector<object> &units_);
        rv_cursor_object_params get_cursor_object_params();
        

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
    

        
        //potential new cat: side
        std::vector<object> detected_mines(const side &side_);
        float count_side(const side &side_, std::vector<object> &objects_);
        void set_airport_side(float value0_, const side &value1_);
        void set_airport_side(const object & target_, const side &value1_);
        void reveal_mine(const object &value0_, const side &value1_);
        bool mine_detected_by(const object &value0_, const side &value1_);
        void add_score_side(const side &value0_, float value1_);
        void airport_side(int id_);
        void airport_side(const object & target_);
        float score_side(const side &value_);


        //2d editor commands (probably unneeded)
        //#TODO check them
        void delete_editor_object(const control &map_, sqf_string_const_ref object_);
        sqf_return_string add_editor_object(const control &map_, sqf_string_const_ref type_, const game_value &values_, sqf_string_const_ref subtype_class_);
        game_value shown_editor_object(const control &map_, const game_value &params_right_);
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
        

        //doesn't work in A3 (comment from KK) - Should probably check if that's true tho
        rv_text set_attributes(const rv_text &text_, const std::vector<std::pair<std::string, std::variant<rv_text, sqf_string_const_ref_wrapper>>> &attributes_);
        //buldozer
        bool buldozer_is_enabled_road_diag();
        void buldozer_reload_oper_map();
        void buldozer_enable_road_diag(bool value_);
        bool buldozer_load_new_roads(sqf_string_const_ref value_);
    }
}