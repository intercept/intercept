/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)
@author Senfo (lpsenfo@gmail.com)

@brief Unit related Function wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        struct rv_zeroing {
            float distance{};
            int zeroing_index{};
        };

        struct rv_target_knowledge {
            //example [true,true,0,-2.14748e+006,WEST,0,[4556.26,5862.7,6.22729]]
            side target_side;
            float last_seen_by_unit;
            float last_endangered_by_unit;
            float position_error;
            vector3 target_position;
            bool known_by_group;
            bool known_by_unit;
            explicit rv_target_knowledge(const game_value &gv_)
                : known_by_group(gv_[0]),
                  known_by_unit(gv_[1]),
                  last_seen_by_unit(gv_[2]),
                  last_endangered_by_unit(gv_[3]),
                  target_side(gv_[4]),
                  position_error(gv_[5]),
                  target_position(gv_[6]) {}
        };

        struct rv_vision_mode {
            int vision_mode;
            int FLIR_index;
            explicit rv_vision_mode(const game_value &gv_)
                : vision_mode(gv_[0]), FLIR_index(gv_[1]) {}

        };

        struct rv_move_info {
            float move_progress;     // 0 -  - move progress in range 0-1;
            float move_time;         // 1 -  - move elapsed time (move progress * move duration);
            float move_duration;     // 2 -  - move duration;
            float move_factor;       // 3 -  - move blend factor;
            vector3 rtm_step;        // 4 -  - rtm step (how many meters the unit will move after finishing the animation);
            float gesture_progress;  // 5 -  - gesture progress in range 0-1;
            float gesture_time;      // 6 -  - gesture elapsed time (gesture progress * gesture duration);
            float gesture_duration;  // 7 -  - gesture duration;
            float gesture_factor;    // 8 -  - gesture blend factor
            explicit rv_move_info(const game_value &gv_) : move_progress{gv_[0]},
                                                           move_time{gv_[1]},
                                                           move_duration{gv_[2]},
                                                           move_factor{gv_[3]},
                                                           rtm_step{gv_[4]},
                                                           gesture_progress{gv_[5]},
                                                           gesture_time{gv_[6]},
                                                           gesture_duration{gv_[7]},
                                                           gesture_factor{gv_[8]} {}
        };

        void set_user_mfd_value(const object &object_, int index_, float value_);
        
        bool is_uav_connectable(const object &unit_, const object &uav_, bool check_all_items_);
        object camera_on();
        object focus_on();
        bool can_unload_in_combat(const object &unit_);

        void ais_finish_heal(const object &wounded_, const object &medic_, bool medic_can_heal_);

        void set_hide_behind(const object &unit_, const object &object_where_hide_, const vector3 &hide_position_);
        bool in(const object &unit_, const object &vehicle_);

        rv_target_knowledge target_knowledge(const object &unit_, const object &target_);
        game_value targets_aggregate(const object &speaker_, const side &side_, const object &unit_, const vector3 &place_, float time_, game_value &candidates_);
        rv_query_target targets_query(const object &unit_, const object &target_ignore_, const side &target_side, sqf_string_const_ref target_type_, const vector3 &target_position_, float target_max_age_);

        void action(const object &unit_, const std::vector<game_value> &action_array_);
        void action(const std::vector<game_value> &action_array_);
        void action_now(const object &unit_, const std::vector<game_value> &action_array_);

        void create_unit(sqf_string_const_ref type_, const vector3 &pos_, const group &group_, sqf_string_const_ref init_ = "", float skill_ = 0.5f, sqf_string_const_ref rank_ = "PRIVATE");
        object create_unit(const group &group_, sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f, sqf_string_const_ref special_ = "NONE");
        sqf_return_string animation_state(const object &unit_);
        sqf_return_string gesture_state(const object &unit_);
        sqf_return_string assigned_team(const object &unit_);
        object assigned_vehicle(const object &unit_);

        bool can_fire(const object &unit_);
        bool can_move(const object &unit_);
        bool can_stand(const object &unit_);
        bool captive(const object &unit_);
        float captive_num(const object &unit_);
        sqf_return_string current_command(const object &veh_);
        int current_vision_mode(const object &unit_);
        rv_vision_mode current_vision_mode_alt(const object &unit_);
        rv_vision_mode current_vision_mode(const object &unit_, sqf_string_const_ref weapon_);
        rv_vision_mode current_vision_mode(const object &vehicle_, const rv_turret_path &turret_path_);
        float current_zeroing(const object &gunner_);
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
        bool is_player(const std::vector<object> &player_); 
        bool is_sprint_allowed(const object &value_);
        bool is_stamina_enabled(const object &value_);
        bool is_turned_out(const object &value_);
        bool is_uavconnected(const object &value_);
        bool is_walking(const object &value_);
        bool is_weapon_deployed(const object &obj_);
        bool is_weapon_deployed(const object &obj_, bool on_ground_);
        bool can_deploy_weapon(const object &obj_);
        bool is_weapon_rested(const object &value_);
        void move(const object &unit_, const vector3 &pos_);
        void move(const group &group_, const vector3 &pos_);
        bool move_in_any(const object &unit_, const object &vehicle_);
        void move_in_cargo(const object &unit_, const object &vehicle_, int cargo_index_ = -1);
        void move_in_commander(const object &unit_, const object &vehicle_);
        void move_in_driver(const object &unit_, const object &vehicle_);
        void move_in_gunner(const object &unit_, const object &vehicle_);
        void move_in_turret(const object &unit_, const object &vehicle_, rv_turret_path turret_path_);

        object remote_controlled(const object &obj_);
        bool is_remote_controlling(const object &unit_);
        void remote_control(const object &controller_, const object &controlled_);
        rv_vehicle_role assigned_vehicle_role(const object &unit_);
        group get_group(const object &unit_);  // originally "group", but is already a type
        group group_get(const object &unit_);
        std::vector<object> group_selected_units(const object &unit_);
        std::pair<sqf_return_string_list, sqf_return_string_list> squad_params(const object &unit_); //#TODO correct return type
        bool unit_ready(const object &unit_);
        sqf_return_string_list unit_addons(sqf_string_const_ref class_);
        std::vector<object> get_all_owned_mines(const object &unit_);
        void remove_all_owned_mines(const object &unit_);
        bool unit_is_uav(const object &unit_);
        void add_owned_mine(const object &unit_, const object &mine_);
        void add_player_scores(const object &unit_, int kills_infantry_, int kills_soft_, int kills_armor_, int kills_air_, int killed_);
        void assign_as_turret(const object &unit_, const object &vehicle_, rv_turret_path turret_path_);
        bool connect_terminal_to_uav(const object &unit_, const object &uav_);
        void disable_uav_connectability(const object &object_, const object &uav_, bool check_all_items_);
        void enable_uav_connect_ability(const object &unit_, const object &uav_, bool check_all_items_);
        void enable_weapon_disassembly(const object &unit_, bool enable_);

        object find_nearest_enemy(const object &unit_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> position_);
        object find_nearest_enemy(const object &unit_, const object &object_);
        void fire(const object &unit_, sqf_string_const_ref muzzle_, sqf_string_const_ref mode_, sqf_string_const_ref magazine_);
        bool fire_at_target(const object &unit_, const object &target_, std::optional<std::string> muzzle_);
        vector3 get_hide_from(const object &unit_, const object &enemy_);
        std::variant<bool, float> get_unit_trait(const object &unit_, sqf_string_const_ref skill_name_);
        void set_captive(const object &object_, bool status);
        /**
        * \brief Mark a unit as captive. If unit is a vehicle, commander is marked. A captive is neutral to everyone (belong to civilian side), and will not trigger "detected by" conditions for its original side.
        * \param object_
        * \param status Using a number (instead of a boolean) for the status has no further effect on the engine's behavior, but can be used by captiveNum to keep track of the captivity status at a finer resolution (e.g. handcuffed, grouped, etc.). The numbered status syntax was introduced in Arma 2.
        */
        void set_captive(const object &object_, float status);
        void set_name(const object &unit_, sqf_string_const_ref name_, sqf_string_const_ref first_name_, sqf_string_const_ref last_name_);
        void set_unit_trait(const object &unit_, sqf_string_const_ref skill_name_, std::variant<bool, float> value_, bool is_custom_);

        void leave_vehicle(const object &unit_, const object &vehicle_);
        void look_at(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const std::vector<object>>> units_, std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector3>> target_);

        void leave_vehicle(const object &value0_, const group &value1_);
        void play_action(const object &unit_, sqf_string_const_ref action_);
        void play_action_now(const object &unit_, sqf_string_const_ref action_);
        void play_gesture(const object &unit_, sqf_string_const_ref anim_);
        void play_move(const object &unit_, sqf_string_const_ref anim_);
        void play_move_now(const object &unit_, sqf_string_const_ref anim_);
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
        void switch_action(const object &unit_, sqf_string_const_ref action_);

        void switch_gesture(const object &unit_, sqf_string_const_ref anim_);
        void switch_gesture(const object &unit_, sqf_string_const_ref anim_, float time_, float factor_ = 1.f);
        void switch_move(const object &unit_, sqf_string_const_ref anim_);
        void switch_move(const object &unit_, sqf_string_const_ref anim_, float time_, float factor_ = 1.f, bool reset_aim_ = true);
        void use_audio_time_for_moves(const object &value0_, bool value1_);

        object leader(const object &value_);
        sqf_return_string life_state(const object &value_);
        bool lock_identity(const object &value_);
        float morale(const object &value_);
        void move_out(const object &unit_);
        void move_out(const object &unit_, const object &vehicle_);
        float move_time(const object &unit_);
        sqf_return_string name(const object &value_);
        float need_reload(const object &value_);
        float precision(const object &value_);
        sqf_return_string rank(const object &value_);
        float rank_id(const object &value_);
        float rating(const object &value_);
        void reload(const object &unit_);
        bool reload(const object &unit_, sqf_string_const_ref muzzle_, sqf_string_const_ref magazine_);
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
        sqf_return_string unit_pos(const object &value_);  //#sort
        float unit_recoil_coefficient(const object &value_);
        bool weapon_lowered(const object &value_);
        void add_rating(const object &value0_, float value1_);
        void add_score(const object &value0_, float value1_);

        enum class team_color {
            MAIN,    //White
            RED,     //Red
            GREEN,   //Green
            BLUE,    //Blue
            YELLOW,  //Yellow
        };

        void assign_team(const object &value0_, team_color team_);
        void unassign_team(const object &value_);
        void disable_conversation(const object &value0_, bool value1_);
        void enable_aim_precision(const object &value0_, bool value1_);
        void enable_fatigue(const object &value0_, bool value1_);
        void enable_mimics(const object &value0_, bool value1_);
        void enable_reload(const object &value0_, bool value1_);
        void enable_stamina(const object &value0_, bool value1_);
        void fire(const object &value0_, sqf_string_const_ref value1_);
        void force_speed(const object &value0_, float value1_);
        float get_forced_speed(const object &unit_);
        void force_walk(const object &value0_, bool value1_);
        bool is_flashlight_on(const object &value0_, sqf_string_const_ref value1_);
        bool is_irlaser_on(const object &value0_, sqf_string_const_ref value1_);
        void set_custom_aim_coef(const object &value0_, float value1_);
        void allow_sprint(const object &value0_, bool value1_);
        float animation_phase(const object &value0_, sqf_string_const_ref value1_);
        object get_connected_uav(const object &value_);
        float get_custom_aim_coef(const object &value_);
        void remove_owned_mine(const object &unit_, const object &mine_);
        void reveal(std::variant<object, group> unit_, const object &target_);
        void reveal(std::variant<object, group> unit_, const std::vector<object> &targets_);
        float get_aiming_coef(const object &value_);
        
        void calculate_player_visibility_by_friendly(bool calc_);
        bool get_calculate_player_visibility_by_friendly();

        bool get_diver_state(const object &unit_);

        float get_object_fov(const object &unit_);

        vector2 weapon_inertia(const object &unit_);
        rv_zeroing current_zeroing(const object &vehicle_, sqf_string_const_ref weapon_class_, sqf_string_const_ref muzzle_class_);

        object get_connected_uav_unit(const object &unit_);

        sqf_return_string pose(const object &unit_);

        struct rv_freefall_info {
            float min_height;
            bool is_falling;
            bool is_in_halo_pose;
            explicit rv_freefall_info(const game_value &gv_)
                : is_falling(gv_[0]), is_in_halo_pose(gv_[1]), min_height(gv_[2]) {}
        };

        void set_unit_freefall_height(const object &unit_, float height_);
        rv_freefall_info get_unit_freefall_info(const object &unit_);

        void set_optics_mode(const object &unit_, sqf_string_const_ref mode_);
        void set_optics_mode(const object &unit_, float index_);
        void set_optics_mode(const object &unit_, int slot_index_, float optic_mode_);
        void set_optics_mode(const object &unit_, int slot_index_, sqf_string_const_ref mode_);

        struct rv_weapons_info {
            sqf_string weapon_name;    // weapon name
            sqf_string muzzle_name;    // muzzle name
            sqf_string fire_mode;      // firemode that is set for this 'weaponIndex'
            sqf_string magazine_name;  // name of the loaded magazine or ""
            float weapon_index;        // internal weapon index (changes frequently) used with "SwitchWeapon" and "UseWeapon" actions
            float ammo_count;          // magazine ammo count or -1
            bool is_selected;          // true if this weapon is currently selected
            bool is_primary;           // true if this muzzle is considered primary by the engine (Since Arma 3 2.14)

            explicit rv_weapons_info(const game_value &gv_)
                : weapon_index(gv_[0]),
                  is_selected(gv_[1]),
                  weapon_name(gv_[2]),
                  muzzle_name(gv_[3]),
                  fire_mode(gv_[4]),
                  magazine_name(gv_[5]),
                  ammo_count(gv_[6]),
                  is_primary(gv_[7]) {}
        };
        rv_weapons_info weapons_info(const object &unit_, sqf_string_const_ref wpnOrMuzzle_, bool onlyLoaded_ = false);
        sqf_return_string get_optics_mode(const object &unit_, int slot);

        sqf_return_string_list compatible_magazines(sqf_string_const_ref weapon_);
        sqf_return_string_list compatible_magazines(sqf_string_const_ref weapon_, sqf_string_const_ref muzzle_);
        sqf_return_string_list compatible_items(sqf_string_const_ref weapon_);
        sqf_return_string_list compatible_items(sqf_string_const_ref weapon_, sqf_string_const_ref slot_);

        object get_corpse(const object &holder_);
        // returns primary and secondary weapon holders
        std::pair<object, object> get_corpse_weapon_holders(const object &corpse_);

        float inside_building(const object &unit_);

        enum class slot_item {
            Goggles = 603,
            Headgear = 605,
            Map = 608,
            Compass = 609,
            Watch = 610,
            Radio = 611,
            GPS = 612,
            HMD = 616,
            Binoculars = 617,
            Vest = 701,
            Uniform = 801,
            Backpack = 901
        };

        sqf_return_string get_slot_item_name(const object &unit_, slot_item item_);

        float get_leaning(const object &unit_);
        rv_move_info get_unit_moves_info(const object &unit_);
        game_value get_unit_moves_info(const object &unit_, int index_);

        struct rv_player_target_lock {
            object target;     // the locked object;
            config config;     // used weapon's CfgWeapons config;
            float lock_value;  // in range 0..1 where 1 is fully locked
            explicit rv_player_target_lock(const game_value &gv_) : target{gv_[0]},
                                                                    config{gv_[2]},
                                                                    lock_value{gv_[1]} {}
        };

        rv_player_target_lock player_target_lock();

        bool has_custom_face(const object &unit_);
    }  // namespace sqf
}  // namespace intercept
