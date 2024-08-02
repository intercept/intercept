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
        struct rv_remote_target_info {
            object target;
            float last_detected;
            explicit rv_remote_target_info(const game_value &gv_)
                : target(gv_[0]),
                  last_detected(gv_[1]) {}
        };

        struct rv_named_properties {
            sqf_string property;
            sqf_string value;
            explicit rv_named_properties(const game_value &gv_)
                : property(gv_[0]),
                  value(gv_[1]) {}
        };
        struct rv_pylon_info {
            sqf_string pylon_name;
            sqf_string magazine_classname;
            sqf_string magazine_ammo_count;
            sqf_string magazine_detail;
            float pylon_index{};
            rv_turret_path assigned_turret;
            explicit rv_pylon_info(const game_value &gv_)
                : pylon_index(gv_[0]),
                  pylon_name(gv_[1]),
                  assigned_turret(gv_[2]),
                  magazine_classname(gv_[3]),
                  magazine_ammo_count(gv_[4]),
                  magazine_detail(gv_[5]) {}
        };

        struct rv_lod_info {
            sqf_string lod_name;           // String - LOD description name for LOD identification
            float lod_index;               // Number - direct index of the LOD for fast access
            float lod_resolution;          // Number - the actual LOD resolution, could be used to select LOD in selectionNames and selectionPosition
            float count_named_selections;  // Number - number of named selections in this LOD, could be returned with selectionNames command
            explicit rv_lod_info(const game_value &gv_)
                : lod_index(gv_[0]),
                  lod_name(gv_[1]),
                  lod_resolution(gv_[2]),
                  count_named_selections(gv_[3]) {}
        };

        struct rv_crew_member {
            object unit;
            sqf_string role;
            rv_turret_path turret_path;
            float cargo_index;
            bool person_turret;

            rv_crew_member(const game_value &gv_)
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

        struct rv_cruise_params {
            float speed{};
            bool auto_thrust{};
            explicit rv_cruise_params(const game_value &gv_)
                : speed(gv_[0]), auto_thrust(gv_[1]) {}
        };

        struct rv_periscope_state {
            float elevation{};
            bool is_locked{};
            explicit rv_periscope_state(const game_value &gv_)
                : elevation(gv_[0]), is_locked(gv_[1]) {}
        };

        struct rv_vehicle_sensor {
            sqf_string sensor_name{};
            bool is_enabled{};
            explicit rv_vehicle_sensor(const game_value &gv_)
                : sensor_name(gv_[0]), is_enabled(gv_[1]) {}
        };

        struct rv_info_panel {
            sqf_string class_name{};
            sqf_string component_type{};
            explicit rv_info_panel(const game_value &gv_)
                : class_name(gv_[0]),
                  component_type(gv_[1]) {}
        };

        struct rv_info_panel_component {
            sqf_string class_name{};
            sqf_string component_type{};
            bool is_accessible{};
            explicit rv_info_panel_component(const game_value &gv_)
                : class_name(gv_[0]),
                component_type(gv_[1]),
                is_accessible(gv_[2]) {}
        };

        struct rv_sensor_target {
            object target;
            sqf_string type;
            sqf_string relationship;
            sqf_string sensor;
            explicit rv_sensor_target(const game_value &gv_)
                : target(gv_[0]),
                  type(gv_[1]),
                  relationship(gv_[2]),
                  sensor(gv_[3]) {}
        };

        struct rv_sensor_threat {
            object target;
            sqf_string type;
            sqf_string sensor;
            explicit rv_sensor_threat(const game_value &gv_)
                : target(gv_[0]),
                  type(gv_[1]),
                  sensor(gv_[2]) {}
        };

        struct rv_collision_status {
            object obj;
            bool mutual;
            explicit rv_collision_status(const game_value &gv_) : obj(gv_[0]), mutual(gv_[1]) {}
        };

        struct rv_entity_info {
            object last_entity_causing_damage;  // 4 - objNull or the entity that last caused damage to this entity. Is not the same as the killer but could be the same. Killed entity might not have this set either. The entity does not have to be dead in order to have last entity that caused damage assigned.;
            float dead_set_time;                // 3 - for how long the entity was dead;
            float last_damage_time;             // 5 - how long ago was lastEntityCausingDamage assigned;
            float upside_down_time;             // 7 - how long the entity was upside down.;
            bool is_man;                        // 0 - true if the entity is a man;
            bool is_animal;                     // 1 - true if the entity is an animal;
            bool is_dead_set;                   // 2 - true if the entity has dead flag set. Often has the same value as !alive, but is not the same, as alive checks the total damage.;
            bool is_upside_down;                // 6 - true if the entity is upside down. The engine considers this to be vectorUp ent select 2 < 0.3;
            bool is_stopped;                    // 8 - true when the entity does not need to be actively simulated.;
            bool can_float;                     // 9 - true if the entity is able to float on water.;
            bool has_terminal_opened;           // 10 - true if the UAV terminal is opened for the given entity.;
            bool is_weaponholder;               // 11 - true if the entity is weaponholder.;
            bool is_wreck;                      // 12 - true if the entity is wreck.;
			bool is_smoking;                    // 13 - true if the entity has smoke and fire destruction effect active.
			bool is_set_for_deletion;           // 14 - true if the entity was set for deletion, but is not yet removed from the simulation.
            explicit rv_entity_info(const game_value &gv_)
                : last_entity_causing_damage{gv_[4]},
                  dead_set_time{gv_[3]},
                  last_damage_time{gv_[5]},
                  upside_down_time{gv_[7]},
                  is_man{gv_[0]},
                  is_animal{gv_[1]},
                  is_dead_set{gv_[2]},
                  is_upside_down{gv_[6]},
                  is_stopped{gv_[8]},
                  can_float{gv_[9]},
                  has_terminal_opened{gv_[10]},
                  is_weaponholder{gv_[11]},
                  is_wreck{gv_[12]},
                  is_smoking{gv_[13]},
                  is_set_for_deletion{gv_[14]} {}
        };

        struct rv_vehicle_respawn_info {
            object respawn_unit;             // 5 - pilot/driver unit that will be placed into the new vehicle.;
            side respawn_side;               // 7 - what side markers to use for respawn. For example if 'respawnSide' set to east the markers with names 'respawn_vehicle_eastXXX' and 'respawn_eastXXX' will be used.;
            sqf_string respawn_marker_name;  // 11 - Chosen vehicle respawn marker, when vehicle respawns it will use the marker params. The respawn marker is processed instantly uppon vehicle's death.;
            float respawn_delay;             // 0 - how long the vehicle will be in respawn queue after death. -1 - 'missionRespawnDelay' value is used.;
            float respawn_count;             // 1 - how many times left for the vehicle to respawn. -1 - indefinite, 0 - no more respawns;
            float respawn_mode;              // 6 - individual respawn mode for this vehicle. Any mode other than 2,3 or -1 means disabled respawn. -1 - use 'missionRespawnMode';
            float respawn_time_remaining;    // 12 - how long left before the respawn. -1 after vehicle has respawned or has respawn disabled.;
            float mission_respawn_delay;     // 13 - global mission vehicle respawn delay. script command > mission param > 3DEN param;
            float mission_respawn_mode;      // 14 - global mission vehicle respawn mode. script command > mission param > 3DEN param;
            bool delete_old_wreck;           // 2 - if true then the old wreck will be deleted when vehicle respawns.;
            bool respawn_on_server;          // 3 - if true the wreck will be transfered to the server and vehicle will respawn on server.;
            bool respawn_flying;             // 4 - if true vehicle will not be forced to the ground and if can fly and has pilot will be spawned flying.;
            bool use_respawn_marker_dir;     // 8 - align respawned vehicle with respawn marker direction or with wreck direction if no marker found or "INSTANT" mode is used. Otherwise, direction is random.;
            bool can_respawn;                // 9 - true if vehicle is respawnable (all conditions for respawn are ok);
            bool is_respawning;              // 10 - true if vehicle is currently in the respawn queue awaiting respawn.
            explicit rv_vehicle_respawn_info(const game_value &gv_) : respawn_unit{gv_[5]},
                                                                      respawn_side{gv_[7]},
                                                                      respawn_marker_name{gv_[11]},
                                                                      respawn_delay{gv_[0]},
                                                                      respawn_count{gv_[1]},
                                                                      respawn_mode{gv_[6]},
                                                                      respawn_time_remaining{gv_[12]},
                                                                      mission_respawn_delay{gv_[13]},
                                                                      mission_respawn_mode{gv_[14]},
                                                                      delete_old_wreck{gv_[2]},
                                                                      respawn_on_server{gv_[3]},
                                                                      respawn_flying{gv_[4]},
                                                                      use_respawn_marker_dir{gv_[8]},
                                                                      can_respawn{gv_[9]},
                                                                      is_respawning{gv_[10]} {}
        };

        struct rv_shot_info {
            float effective_time_to_live;   // 0 - how much more shot has to live.;
            float fuse_distance_left;       // 1 - how long shot has to travel more to get fused (undebarrel grenade for example).;
            float time_to_explosion;        // 2 - how long before shot fuse explodes (hand grenade for example).;
            bool trigger_is_forced;         // 3 - true if shot ammo was triggered with triggerAmmo.;
            bool shown_tracer;              // 4 - true if the shot shown as tracer.;
            bool is_real;                   // 5 - true if the shot is considered in damage events.;
            bool is_submunition_triggered;  // 6 - true if the shot contains submunition and it is triggered.
            explicit rv_shot_info(const game_value &gv_) : effective_time_to_live{gv_[0]},
                                                           fuse_distance_left{gv_[1]},
                                                           time_to_explosion{gv_[2]},
                                                           trigger_is_forced{gv_[3]},
                                                           shown_tracer{gv_[4]},
                                                           is_real{gv_[5]},
                                                           is_submunition_triggered{gv_[6]} {}
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
        object create_vehicle_local(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_, float placement_ = 0.0f, sqf_string_const_ref special_ = "NONE");
        void delete_vehicle(const object &obj_);
        void delete_vehicle(const std::vector<object> &obj_);
        std::vector<rv_turret_path> all_turrets(const object &vehicle_, bool person_turrets_);

        std::vector<rv_turret_path> all_turrets(const object &vehicle_);
        bool alive(const object &obj_);
        object assigned_commander(const object &veh_);
        object assigned_driver(const object &veh_);
        object assigned_gunner(const object &veh_);
        object assigned_target(const object &veh_);
        group assigned_group(const object &veh_);
        std::vector<object> assigned_vehicles(const group &grp_);
        object commander(const object &veh_);
        group create_vehicle_crew(const object &veh_);
        group create_vehicle_crew(const group &grp_, const object &veh_);
        group create_vehicle_crew(const side &side_, const object &veh_);
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
        bool water_damaged(const object &obj_);
        float get_mass(const object &value_);
        float get_object_dlc(const object &value_);
        int get_object_type(const object &value_);
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
        bool is_light_on(const object &value_, const auto_array<float> &turret_);
        bool is_manual_fire(const object &value_);
        bool is_marked_for_collection(const object &value_);
        bool is_object_hidden(const object &value_);
        bool is_touching_ground(const object &value_);
        object laser_target(const object &value_);
        sqf_return_string light_is_on(const object &value_);
        float locked(const object &value_);
        bool mine_active(const object &value_);
        object missile_target(const object &value_);
        vector3 missile_target_pos(const object &value_);
        bool set_missile_target(const object &value_, const object &target_);
        bool set_missile_target(const object &value_, const object &target_, bool force_);
        void set_missile_target_pos(const object &value_, const vector3 &position_);
        bool locked_driver(const object &value_);
        object object_parent(const object &value_);
        float score(const object &value_);
        float scud_state(const object &value_);
        float size_of(sqf_string_const_ref value_);
        float speed(const object &value_);
        object vehicle(const object &value_);
        sqf_return_string vehicle_var_name(const object &value_);
        void allow_crew_in_immobile(const object &veh_, bool allow_);
        void allow_crew_in_immobile(const object &veh_, bool broken_wheel_, bool upside_down_);
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
        bool set_autonomous(const object &value0_, bool value1_);
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
        object create_simple_object(sqf_string_const_ref shapename_, const vector3 &positionworld, bool local_ = false);
        float get_container_max_load(sqf_string_const_ref containerclass_);
        rv_shot_parents get_shot_parents(const object &projectile_);
        bool is_simple_object(const object &object_);
        sqf_return_string_list selection_names(const object &object_);
        sqf_return_string_list selection_names(const object &object_, float lod_res_);
        sqf_return_string_list selection_names(const object &object_, rv_selection_lods lod_);
        sqf_return_string_list get_bone_names(const object &object_);
        sqf_return_string_list get_selection_bones(const object &object_, sqf_string_const_ref selection_, float lod_res_);
        sqf_return_string_list get_selection_bones(const object &object_, sqf_string_const_ref selection_, rv_selection_lods lod_);
        void switch_camera(const object &target_);
        void animate_source(const object &object_, sqf_string_const_ref source_, float phase_, bool speed_);
        void animate_source(const object &object_, sqf_string_const_ref source_, float phase_, float speed_);
        float animation_source_phase(const object &object_, sqf_string_const_ref source_);
        void delete_vehicle_crew(const object &vehicle_, const object &unit_);
        void disable_collision_with(const object &object1_, const object &object2_);
        void enable_collision_with(const object &object1_, const object &object2_);
        void hide_selection(const object &object_, sqf_string_const_ref selection_, bool hide_);
        void lock_camera_to(const object &vehicle_, const object &target_, const rv_turret_path &turret_path_);
        game_value locked_camera_to(const object &vehicle_, const rv_turret_path &turret_path_);
        void lock_cargo(const object &vehicle_, int index_, bool lock_);
        bool locked_turret(const object &vehicle_, const rv_turret_path &turret_path_);
        void lock_turret(const object &vehicle_, const rv_turret_path &turret_path_, bool lock_);
        void respawn_vehicle(const object &vehicle_, float delay_, int count_);
        void select_weapon_turret(const object &, sqf_string_const_ref weapon_, const rv_turret_path &turret_path_);
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
        float weapon_reloading_time(const object &vehicle_, const object &gunner_, sqf_string_const_ref muzzle_name_);
        void synchronize_objects_add(const object &unit_, const std::vector<object> &objects_);
        void synchronize_objects_remove(const object &unit_, const std::vector<object> &objects_);
        object turret_unit(const object &vehicle_, const rv_turret_path &turret_path_);
        sqf_return_string_list weapons_turret(const object &vehicle_, const rv_turret_path &turret_path_);
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
        void set_light_cone_pars(const object &lightcone_, float outer_angle_, float inner_angle_, float fade_coef_);
        void set_light_ir(const object &lightcone_, bool ir_);
        void set_light_volume_shape(const object &lightcone_, sqf_string_const_ref shape_path_, float scale_);

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

        void trigger_ammo(const object& object_);

        void elevate_periscope(const object &vehicle_, const rv_turret_path &turret_, float elevation_, float speed_ = -1, bool blockuser_ = false);
        void elevate_periscope(const object &vehicle_, const rv_turret_path &turret_, float elevation_, bool instant_ = false, bool blockuser_ = false);
        rv_periscope_state periscope_elevation(const object &vehicle_, const rv_turret_path &turret_);

        bool enable_info_panel_component(const object &vehicle_, const rv_turret_path &turret_, sqf_string_const_ref panel_id_, sqf_string_const_ref componentClassOrType_, bool enable_);
        bool enable_info_panel_component(const object &vehicle_, sqf_string_const_ref panel_id_, sqf_string_const_ref componentClassOrType_, bool enable_);
        bool info_panel_component_enabled(const object &vehicle_, const rv_turret_path &turret_, sqf_string_const_ref panel_id_, sqf_string_const_ref componentClassOrType_);
        bool info_panel_component_enabled(const object &vehicle_, sqf_string_const_ref panel_id_, sqf_string_const_ref componentClassOrType_);
        std::vector<rv_info_panel_component> info_panel_components(const object &vehicle_, sqf_string_const_ref panel_id_);
        std::vector<rv_info_panel_component> info_panel_components(const object &vehicle_, const rv_turret_path &turret_, sqf_string_const_ref panel_id_);

        void enable_vehicle_sensor(const object &vehicle_, sqf_string_const_ref component_, bool enable_);
        std::vector<rv_vehicle_sensor> is_vehicle_sensor_enabled(const object &vehicle_, sqf_string_const_ref component_);
        
        std::variant<sqf_return_string_list, std::vector<sqf_return_string_list>> get_compatible_pylon_magazines(std::variant<const object, sqf_string_const_ref> vehicle_, std::variant<float, sqf_string_const_ref> pylon_);
        void set_effective_commander(const object &vehicle_, const object &commander_);
        void set_plate_number(const object &vehicle_, sqf_string_const_ref str_number_);
        rv_turret_path unit_turret(const object &vehicle_, const object &gunner_);
        sqf_return_string_list animation_names(const object &vehicle_);
        object current_pilot(const object &vehicle_);
        bool set_weapon_zeroing(const object &vehicle_, sqf_string_const_ref weapon_class_, sqf_string_const_ref muzzle_class_, float zeroing_index_);
        std::vector<rv_pylon_info> get_all_pylons_info(const object &vehicle_);
        void set_user_mfd_text(const object &vehicle_, float index_, sqf_string_const_ref text_);
        sqf_return_string get_plate_number(const object &vehicle_);
        sqf_return_string_list get_user_mfd_text(const object &vehicle_);
        std::vector<float> get_user_mfd_value(const object &vehicle_);
        std::vector<float> get_vehicle_ti_pars(const object &vehicle_);
        void set_vehicle_ti_pars(const object &vehicle_, const std::vector<float> &pars_);
        std::vector<rv_info_panel> info_panels(const object &vehicle_);
        std::vector<rv_info_panel> info_panels(const object &vehicle_, const rv_turret_path &turret_);
        bool is_laser_on(const object &vehicle_);
        std::vector<rv_remote_target_info> list_remote_targets(side side_);
        std::vector<rv_named_properties> named_properties(const object &obj_);
        rv_hashmap named_properties(const object &obj_, float lod_res_);
        rv_hashmap named_properties(const object &obj_, sqf_string_const_ref lod_);
        bool set_info_panel(sqf_string_const_ref infopanelId_, sqf_string_const_ref componentClassOrType_);
        void set_cruise_control(const object &veh_, float speed_, bool auto_thrust_);
        void set_tow_parent(const object &towed_vehicle_, const object &towing_vehicle_);
        object get_tow_parent(const object &towed_vehicle_);
        rv_cruise_params get_cruise_control(const object &veh_);
        std::vector<rv_lod_info> all_lods(const object &obj_);
        std::vector<rv_lod_info> all_lods(sqf_string_const_ref model_path_);
        void delete_vehicle_crew(const object &vehicle_);

        bool direction_stabilization_enabled(const object &vehicle_, const rv_turret_path &turret_);
        void enable_direction_stabilization(const object &vehicle_, bool enabled_, const rv_turret_path &turret_);

        std::vector<rv_sensor_target> get_sensor_targets(const object &vehicle_);
        std::vector<rv_sensor_threat> get_sensor_threats(const object &vehicle_);

        struct rv_disabled_equipment {
            bool nvg;
            bool ti;
            explicit rv_disabled_equipment(const game_value &gv_)
                : nvg(gv_[0]),
                  ti(gv_[1]) {}
        };

        rv_disabled_equipment equipment_disabled(const object &veh_);

        void set_max_load(const object &container_, float load_);
        float max_load(const object &container_);

        bool is_awake(const object &obj_);
        void awake(const object &obj_, bool awake_);

        bool brakes_disabled(const object &veh_);
        void disable_brakes(const object &veh_, bool disable_);

        std::vector<rv_collision_status> collision_disabled_with(const object &obj_);

        struct rv_physics_flags
        {
            bool collision;
            explicit rv_physics_flags(const game_value &gv_)
                : collision(gv_[0]) {}
        };

        rv_physics_flags get_physics_collision_flag(const object &obj_);
        void set_physics_collision_flag(const object &obj_, bool enabled_);

        bool is_allowed_crew_in_immobile(const object &veh_);

        // return 0: none, 1: auto, 2: manual, 3: both, -1: unsupported
        int allowed_service(const object &veh_);
        // 0: none, 1: auto, 2: manual, 3: both
        void allow_service(const object &veh_, int service_);
        bool need_service(const object &veh_);

        void set_turret_optics_mode(const object &veh_, int index_);
        int get_turret_optics_mode(const object &veh_);
        void set_turret_optics_mode(const object &veh_, const rv_turret_path &turret_, int index_);
        int get_turret_optics_mode(const object &veh_, const rv_turret_path &turret_);

        struct rv_turret_limits {
            float min_turn;   // from 0 to -angle in degrees (left)
            float max_turn;   // from 0 to +angle in degrees (right)
            float min_elev;   // from 0 to -angle in degrees (down)
            float max_elev;   // from 0 to +angle in degrees (up)
            bool overridden;  // if custom limits were applied

            explicit rv_turret_limits(const game_value &gv_)
                : min_turn(gv_[0]),
                  max_turn(gv_[1]),
                  min_elev(gv_[2]),
                  max_elev(gv_[3]),
                  overridden(gv_[4]) {}
        };

        rv_turret_limits get_turret_limits(const object &veh_, const rv_turret_path &turret_);
        void set_turret_limits(const object &veh_, const rv_turret_path &turret_, float min_turn_, float max_turn_, float min_elev_, float max_elev_);
        bool force_hitpoints_damage_sync(const object &entity_);

        rv_entity_info get_entity_info(const object &obj_);
        game_value get_entity_info(const object &obj_, int index_);
        rv_shot_info get_shot_info(const object &obj_);
        game_value get_shot_info(const object &obj_, int index_);

        float get_fuel_consumption_coef(const object &veh_);
        void set_fuel_consumption_coef(const object &veh_, float value_);

        rv_vehicle_respawn_info get_vehicle_respawn_info(const object &veh_);
        game_value get_vehicle_respawn_info(const object &veh_, int index_);

        float get_water_fill_percentage(const object &veh_);
        void set_water_fill_percentage(const object &veh_, float value_);
        float get_water_leakiness(const object &veh_);
        void set_water_leakiness(const object &veh_, float value_);

        struct rv_missile_state
        {
            enum class engine
            {
                INIT,THRUST,FLY,NONE
            };
            enum class lock
            {
                MANUAL,LOCKED,LOST,INITIAL,SEEKING,NONE
            };
            enum class flight
            {
                DEFAULT,DIRECT,TOPDOWN,LOALDISTANCE,OVERFLY,CRUISE,NONE
            };
            engine engine_state = engine::NONE; // one of the "INIT", "THRUST", "FLY" or "".;
            lock lock_state = lock::NONE;       // one of the "MANUAL", "LOCKED", "LOST", "INITIAL", "SEEKING" or "".;
            flight flight_state = flight::NONE; // one of the "DEFAULT", "DIRECT", "TOPDOWN", "LOALDISTANCE", "LOALALTITUDE", "OVERFLY", "CRUISE" or "". LOAL stands for "Lock-on after launch".
        };

        rv_missile_state missile_state(const object &missile_);
    }  // namespace sqf
}  // namespace intercept
