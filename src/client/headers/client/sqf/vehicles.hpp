/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)
@author Senfo (lpsenfo@gmail.com)

@brief Vehicle related Function wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {

        struct rv_crew_member {
            object unit;
            std::string role;
            float cargo_index;
            rv_turret_path turret_path;
            bool person_turret;

            rv_crew_member(game_value gv_)
                : unit(gv_[0]),
                role(gv_[1]),
                cargo_index(gv_[2]),
                turret_path(gv_[3]),
                person_turret(gv_[4]) {}

            rv_crew_member(object unit_, std::string role_, float cargo_index_, rv_turret_path turret_path_, bool person_turret_)
                : unit(std::move(unit_)),
                  role(std::move(role_)),
                  cargo_index(cargo_index_),
                  turret_path(std::move(turret_path_)),
                  person_turret(person_turret_) {}
        };

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
        float set_flag_animation_phase(const object &object_, float phase);
        void set_flag_owner(const object &flag_, const object &owner_);
        void set_flag_animation_phase(const object &flag_, float &animation_phase_);
        object create_vehicle_local(sqf_string_const_ref type_, const vector3 &pos_atl_);
        void add_to_remains_collector(const std::vector<object> &objects_);
        void remove_from_remains_collector(const std::vector<object> &remains_);
        std::vector<rv_crew_member> full_crew(const object &veh_);
        std::vector<rv_crew_member> full_crew(const object &veh_, sqf_string_const_ref filter_, bool include_empty_ = false);
        std::vector<object> crew(const object &_veh);
        float aimed_at_target(const object &vehicle_, const object &target_);
        float aimed_at_target(const object &vehicle_, const object &target_, sqf_string_const_ref weapon_);
        void animate(const object &obj_, sqf_string_const_ref animation_name_, float phase_);
        void animate(const object &obj_, sqf_string_const_ref animation_name_, float phase_, bool instant_);
        void animate_door(const object &obj_, sqf_string_const_ref door_name_, float phase_, bool now_);
        vector3 get_center_of_mass(const object &obj_);
        object create_vehicle(sqf_string_const_ref type_, const vector3 &pos_);
        object create_vehicle(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_, float placement_ = 0.0f, sqf_string_const_ref special_ = "NONE");
        void delete_vehicle(const object &obj_);
        std::vector<rv_turret_path> all_turrets(const object &vehicle_, bool person_turrets_);

        std::vector<rv_turret_path> all_turrets(const object &vehicle_);
        bool alive(const object &obj_);
        object assigned_commander(const object &veh_);
        object assigned_driver(const object &veh_);
        object assigned_gunner(const object &veh_);
        object assigned_target(const object &veh_);
        object commander(const object &veh_);
        void create_vehicle_crew(const object &veh_);
        float damage(const object &object_);
        object driver(const object &value_);
        object effective_commander(const object &value_);

        void fill_weapons_from_pool(const object &value_);  //#categorize inventory? to the other weapon pool stuff

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
        std::vector<object> synchronized_objects(const object &obj_);
        rv_model_info get_model_info(const object &object_);
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
        void lock_camera_to(const object &vehicle_, const object &target_, rv_turret_path turret_path_);
        void lock_cargo(const object &vehicle_, int index_, bool lock_);
        bool locked_turret(const object &vehicle_, rv_turret_path turret_path_);
        void lock_turret(const object &vehicle_, rv_turret_path turret_path_, bool lock_);
        void respawn_vehicle(const object &vehicle_, float delay_, int count_);
        void select_weapon_turret(const object &, sqf_string_const_ref weapon_, rv_turret_path turret_path_);
        void set_center_of_mass(const object &object_, const vector3 &offset_, float time_ = 0.f);
        enum class feature_type {
            disabled = 0,                 ///< Feature disabled
            visible_object_distance = 1,  ///< Object is always visible within object view distance
            visible_terrain_distance = 2  ///< Object is always visible within terrain view distance
        };
        bool set_feature_type(const object &object_, feature_type type_);
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
        object turret_unit(const object &vehicle_, rv_turret_path turret_path_);
        sqf_return_string_list weapons_turret(const object &vehicle_, rv_turret_path turret_path_);
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
        sqf_return_string wf_side_text(const object &object_);  //https://community.bistudio.com/wiki/WFSideText
        sqf_return_string wf_side_text(const group &group_);
        sqf_return_string wf_side_text(const side &side_);
        rv_uav_control uav_control(const object &uav_);
        bool is_vehicle_radar_on(const object &vehicle_);
        sqf_return_string_list list_vehicle_sensors(const object &vehicle_);
        void add_force(const object &object_, vector3 force_, vector3 position_);
        void add_torque(const object &object_, vector3 torque_);

    }  // namespace sqf
}  // namespace intercept
