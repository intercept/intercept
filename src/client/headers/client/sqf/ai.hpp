/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)

@brief AI related Function wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        /* ai */
        struct rv_unit_trait {
            sqf_string trait;
            float value;
            explicit rv_unit_trait(const game_value &gv_)
                : trait(gv_[0]),
                  value(gv_[1]) {}
        };

        enum class ai_behavior {
            CARELESS,
            SAFE,
            AWARE,
            COMBAT,
            STEALTH
        };
        enum class ai_combat_modes {
            BLUE,    // Never fire, keep formation
            GREEN,   // Hold fire, keep formation
            WHITE,   // Hold fire, engage at will/loose formation
            YELLOW,  // Fire at will, keep formation
            RED      // Fire at will, engage at will/loose formation
        };
        bool attack_enabled(const object &unit_);
        bool attack_enabled(const group &group_);
        void command_artillery_fire(const object &unit_, const vector3 &pos_, sqf_string_const_ref type_, int rounds_);
        void command_artillery_fire(const object &unit_, const vector2 &pos_, sqf_string_const_ref type_, int rounds_);
        void command_artillery_fire(const std::vector<object> &units_, const vector3 &pos_, sqf_string_const_ref type_, int rounds_);
        void command_artillery_fire(const std::vector<object> &units_, const vector2 &pos_, sqf_string_const_ref type_, int rounds_);
        void command_fire(const object &unit_, const object &target_);
        void command_fire(const std::vector<object> &units_, const object &target_);
        void command_follow(const object &unit_, const object &target_);
        void command_follow(const std::vector<object> &units_, const object &target_);
        void command_fsm(const object &unit_, sqf_string_const_ref fsm_, const vector3 &pos_, const object &target_);
        void command_fsm(const object &unit_, sqf_string_const_ref fsm_, const vector2 &pos_, const object &target_);
        void command_fsm(const std::vector<object> &units_, sqf_string_const_ref fsm_, const vector3 &pos_, const object &target_);
        void command_fsm(const std::vector<object> &units_, sqf_string_const_ref fsm_, const vector2 &pos_, const object &target_);
        void command_move(const object &unit_, const vector3 &pos_);
        void command_move(const object &unit_, const vector2 &pos_);
        void command_move(const std::vector<object> &units_, const vector3 &pos_);
        void command_move(const std::vector<object> &units_, const vector2 &pos_);
        void command_radio(const object &unit_, sqf_string_const_ref radio_name_);
        void command_radio(const std::vector<object> &units_, sqf_string_const_ref radio_name_);
        void command_target(const object &unit_, const object &target_);
        void command_target(const std::vector<object> &units_, const object &target_);
        void command_watch(const object &unit_, const vector3 &pos_);
        void command_watch(const object &unit_, const vector2 &pos_);
        void command_watch(const std::vector<object> &units_, const vector3 &pos_);
        void command_watch(const std::vector<object> &units_, const vector2 &pos_);
        void command_watch(const object &unit_, const object &target_);
        void command_watch(const std::vector<object> &units_, const object &target_);
        void command_get_out(const object &unit_);
        void command_get_out(const std::vector<object> &units_);
        void command_stop(const object &unit_);
        void command_stop(const std::vector<object> &units_);
        void allow_fleeing(const object &object_, float cowardice_);
        void allow_fleeing(const group &group_, float cowardice_);
        void allow_get_in(const std::vector<object> &units_, bool allow_);
        void assign_as_commander(const object &unit_, const object &vehicle_);
        void assign_as_driver(const object &unit_, const object &vehicle_);
        void assign_as_gunner(const object &unit_, const object &vehicle_);
        void assign_as_gunner(const object &unit_, const object &vehicle_, rv_turret_path turret_path_);
        void assign_as_cargo(const object &unit_, const object &vehicle_);
        void assign_as_cargo_index(const object &unit_, const object &vehicle_, int index_);

        void kb_add_topic(const object &unit_, sqf_string_const_ref topic_name_, sqf_string_const_ref bikb_file_, sqf_string_const_ref fsm_file_, std::variant<std::reference_wrapper<const code>, sqf_string_const_ref_wrapper> event_handler_);
        void kb_react();
        void kb_tell(const object &unit_, const object &receiver_, sqf_string_const_ref topic_name_, sqf_string_const_ref sentence_class_, sqf_string_const_ref argument_name_, const code &argument_value_, sqf_string_const_ref argument_text_, sqf_string_list_const_ref argument_speech_, std::variant<std::reference_wrapper<bool>, std::reference_wrapper<int>, sqf_string_const_ref_wrapper> force_radio_);
        bool kb_was_said(const object &unit_, const object &receiver_, sqf_string_const_ref topic_, sqf_string_const_ref sentence_id_, int max_age_);
        bool kb_add_database(const object &obj0_, sqf_string_const_ref value1_);
        bool kb_add_database_targets(const object &obj0_, sqf_string_const_ref value1_);
        bool kb_has_topic(const object &obj0_, sqf_string_const_ref value1_);
        void kb_remove_topic(const object &obj0_, sqf_string_const_ref value1_);

        //ai
        void set_skill(const object &object_, float skill_);
        enum class set_skill_type {
            aimingAccuracy,
            aimingShake,
            aimingSpeed,
            endurance,
            spotDistance,
            spotTime,
            courage,
            reloadSpeed,
            commanding,
            general
        };
        void set_skill(const object &object_, set_skill_type type_, float skill_);
        enum class simple_command_type {
            //Gunner commands
            FIRE,
            CEASE_FIRE,
            MANUAL_FIRE,
            CANCEL_MANUAL_FIRE,
            KEY_FIRE,
            //Driver commands
            FORWARD,
            STOP,
            BACK,
            FAST,
            KEY_FAST,
            SLOW,
            KEY_SLOW,
            LEFT,
            RIGHT,
            KEY_UP,
            KEY_DOWN
        };
        void send_simple_command(const object &obj0_, simple_command_type command_);
        sqf_return_string speed_mode(const object &obj_);
        sqf_return_string speed_mode(const group &grp_);
        object create_agent(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f, sqf_string_const_ref special_ = "NONE"sv);
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
        sqf_return_string behaviour(const object &unit_);
        bool check_aifeature(sqf_string_const_ref feature_);
        bool fleeing(const object &obj_);
        float skill(const object &obj_);
        sqf_return_string land_result(const object &obj_);
        bool move_to_completed(const object &obj_);
        bool move_to_failed(const object &obj_);

        enum class ai_behaviour_types {
            TARGET,        // Stop the unit to watch the assigned target / group commander may not assign targets
            AUTOTARGET,    // Prevent the unit from assigning a target independently and watching unknown objects / no automatic target selection
            MOVE,          // Disable the AI's movement / do not move
            ANIM,          // Disable ability of AI to change animation.
            WEAPONAIM,     // Disabled weapon aiming.
            TEAMSWITCH,    // AI disabled because of Team Switch
            FSM,           // Disable the execution of AI behavior scripts.
            AIMINGERROR,   // Prevents AI's aiming from being distracted by its shooting, moving, turning, reloading, hit, injury, fatigue, suppression or concealed/lost target.
            SUPPRESSION,   // Prevents AI from being suppressed.
            CHECKVISIBLE,  // Disables visibility raycasts.
            COVER,         // Disables usage of cover positions by the AI.
            AUTOCOMBAT,    // Disables autonomous switching to COMBAT when in danger.
            PATH,          // Stops the AI’s movement but not the target alignment.
            MINEDETECTION, // Disable AI's mine detection.
            NVG,           // Stops AI from putting NVGs on but not taking them off.
            LIGHTS,        // Stops AI from operating vehicle headlights as well as collision lights.
            RADIOPROTOCOL, // Stops AI from talking and texting while still being able to issue orders.
            ALL            // All of the above.
        };

        void disable_ai(const object &obj0_, ai_behaviour_types type_);
        void enable_ai(const object &obj0_, ai_behaviour_types type_);
        enum class ai_feature_types {
            AwareFormationSoft,
            CombatFormationSoft
        };
        void enable_aifeature(bool value0_, ai_feature_types value1_);
        void fly_in_height(const object &veh_, float height_);
        void fly_in_height(const object &veh_, float height_, bool forced_);
        float knows_about(const object &source_, const object &target_);
        float knows_about(const group &source_, const object &target_);
        float knows_about(const side &side_, const object &target_);
        void land(const object &veh_, sqf_string_const_ref mode_);
        void land_at(const object &veh_, float id_);
        bool land_at(const object &veh_, const object &helipad_, sqf_string_const_ref mode_);
        float skill(const object &obj0_, sqf_string_const_ref value1_);
        float skill_final(const object &obj0_, sqf_string_const_ref value1_);
        void stop(const object &obj0_, bool value1_);
        void suppress_for(const object &obj0_, float value1_);
        void move_to(const object &unit_, const vector3 &pos_);
        struct rv_expected_destination {
            vector3 position;
            std::string planning_mode;
            bool force_replan;

            rv_expected_destination(const game_value &ret_game_value_) : position(ret_game_value_[0]),
                                                                         planning_mode(ret_game_value_[1]),
                                                                         force_replan(ret_game_value_[2]) {}
        };

        rv_expected_destination expected_destination(const object &unit_);

        void use_ai_oper_map_obstruction_test(bool use_);
        void use_ai_steering_component(bool use_);
        void use_ai_steering_component(const object &veh_, bool use_);
        bool is_ai_steering_component_enabled(const object &veh_);
        bool is_using_ai_steering_component();
        void command_suppressive_fire(const object &unit_, const object &target_);
        void command_suppressive_fire(const object &unit_, const vector3 &target_position_);

        void set_behaviour(std::variant<group, object> group_, sqf_string_const_ref behaviour_);
        void set_behaviour_strong(std::variant<group, object> group_, sqf_string_const_ref behaviour_);
        void set_combat_mode(std::variant<group, object, team_member> group_, sqf_string_const_ref mode_);
        void set_formation(std::variant<group, object> group_, sqf_string_const_ref mode_);
        void set_convoy_seperation(const object &object_, float distance_);
        void set_destination(const object &object_, const vector3 &position_, sqf_string_const_ref planning_mode_, bool force_replan);
        void set_drive_on_path(const object &object_, const std::vector<vector3> &points_);
        void set_form_dir(std::variant<group, object> group_, float heading_);

        void enable_gun_lights(const object &unit_, bool &enable_);
        void enable_gun_lights(const group &group_, bool &enable_);
        void enable_ir_lasers(const object &unit_, bool &enable_);
        void enable_ir_lasers(const group &group_, bool &enable_);
        void enable_person_turret(const object &vehicle_, rv_turret_path turret_path_, bool enable_);
        object find_cover(const object &object_, const vector3 &position_, const vector3 &hide_position_, float max_dist_, std::optional<float> min_dist_, std::optional<vector3> visible_position_, std::optional<object> ignore_object_);
        void fly_in_height_asl(const object &aircraft_, float height_careless_safe_aware_, float height_combat_, float height_stealth_);
        void force_follow_road(const object &vehicle_, bool follow_);
        void force_weapon_fire(const object &unit_, sqf_string_const_ref muzzle_, sqf_string_const_ref fire_mode_);
        void glance_at(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const std::vector<object>>> unit_, std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector3>> target_);
        void order_get_in(const std::vector<object> &units_, bool order_);

        void set_unload_in_combat(const object &unit_, bool allowCargo, bool allowTurrets);

        struct rv_unload_in_combat {
            bool allow_cargo;
            bool allow_turrets;
            explicit rv_unload_in_combat(const game_value &gv_)
                : allow_cargo(gv_[0]),
                  allow_turrets(gv_[1]) {}
        };

        rv_unload_in_combat get_unload_in_combat(const object &unit_);
        void swim_in_depth(const object &unit_, float depth_);

        object calculate_path(sqf_string_const_ref type_, sqf_string_const_ref behaviour_, const vector3& from_, const vector3& to_);

        bool check_ai_feature(ai_feature_types feature_);
        bool check_ai_feature(const object &unit_, ai_behaviour_types feature_);
        void enable_aifeature(const object &unit_, ai_behaviour_types feature_, bool enable_);
        void set_combat_behaviour(const object &unit_, ai_behavior behavior_);
        void set_combat_behaviour(const group &group_, ai_behavior behavior_);
        void set_combat_behaviour(const object &unit_, sqf_string_const_ref behavior_);
        void set_combat_behaviour(const group &group_, sqf_string_const_ref behavior_);
        sqf_return_string combat_behaviour(const object &unit_);
        sqf_return_string combat_behaviour(const group &group_);
        void set_unit_combat_mode(const object &unit_, ai_combat_modes mode_);
        void set_unit_combat_mode(const object &unit_, sqf_string_const_ref mode_);
        sqf_return_string unit_combat_mode(const object &unit_);
        std::vector<rv_unit_trait> get_all_unit_traits(const object &unit_);
        std::vector<rv_unit_trait> get_all_unit_traits(sqf_string_const_ref class_);
        object get_attack_target(const object &unit_);
        std::pair<sqf_return_string, sqf_return_string> vehicle_move_info(const object &vehicle_);

        void forget_target(const object &unit_, const object& target_);
        void forget_target(const group &group_, const object& target_);
        std::vector<object> targets(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const group>> unit_, std::optional<bool> enemy_only_, std::optional<float> max_distance_, std::optional<std::vector<side>> sides_, std::optional<float> max_age_, std::optional<std::variant<std::reference_wrapper<vector2>, std::reference_wrapper<vector3>>> alternate_center_);
        void ignore_target(const group& group_, const object& target_, bool is_ignored_ = true);
    }  // namespace sqf
}  // namespace intercept
