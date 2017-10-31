#include "vehicles.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        int airplane_throttle(const object &airplane_) {
            return host::functions.invoke_raw_unary(__sqf::unary__airplanethrottle__object__ret__scalar, airplane_);
        }

        sqf_return_string get_forced_flag_texture(const object &flag_pole_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getforcedflagtexture__object__ret__string, flag_pole_);
        }

        sqf_return_string_list get_pylon_magazines(const object &vehicle_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__getpylonmagazines__object__ret__array, vehicle_));
        }

        bool is_damage_allowed(const object &object_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isdamageallowed__object__ret__bool, object_);
        }

        bool vehicle_receive_remote_targets(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__vehiclereceiveremotetargets__object__ret__bool, vehicle_);
        }

        bool vehicle_report_own_position(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__vehiclereportownposition__object__ret__bool, vehicle_);
        }

        bool vehicle_report_remote_targets(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__vehiclereportremotetargets__object__ret__bool, vehicle_);
        }

        int ammo_on_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ammoonpylon__object__string_scalar__ret__scalar, vehicle_, pylon_name_);
        }

        int ammo_on_pylon(const object &vehicle_, int pylon_index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ammoonpylon__object__string_scalar__ret__scalar, vehicle_, pylon_index_);
        }

        void animate_bay(const object &vehicle_, sqf_string_const_ref pylon_name_, float anim_phase_) {
            host::functions.invoke_raw_binary(__sqf::binary__animatebay__object__array__ret__nothing, vehicle_, {pylon_name_, anim_phase_});
        }

        void animate_bay(const object &vehicle_, int pylon_index_, float anim_phase_) {
            host::functions.invoke_raw_binary(__sqf::binary__animatebay__object__array__ret__nothing, vehicle_, {pylon_index_, anim_phase_});
        }

        void animate_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_, float anim_phase_) {
            host::functions.invoke_raw_binary(__sqf::binary__animatepylon__object__array__ret__nothing, vehicle_, {pylon_name_, anim_phase_});
        }

        void animate_pylon(const object &vehicle_, int pylon_index_, float anim_phase_) {
            host::functions.invoke_raw_binary(__sqf::binary__animatepylon__object__array__ret__nothing, vehicle_, {pylon_index_, anim_phase_});
        }

        void confirm_sensor_target(const object &vehicle_, const side &side_, bool is_confirmed_) {
            host::functions.invoke_raw_binary(__sqf::binary__confirmsensortarget__object__array__ret__nothing, vehicle_, {side_, is_confirmed_});
        }

        void force_flag_texture(const object &object_, sqf_string_const_ref texture_) {
            host::functions.invoke_raw_binary(__sqf::binary__forceflagtexture__object__string__ret__nothing, object_, texture_);
        }

        bool is_sensor_target_confirmed(const object &object_, const side &side_) {
            return host::functions.invoke_raw_binary(__sqf::binary__issensortargetconfirmed__object__side__ret__bool, object_, side_);
        }

        void report_remote_target(const side &side_, const object &target_, float time_) {
            host::functions.invoke_raw_binary(__sqf::binary__reportremotetarget__side__array__ret__nothing, side_, {target_, time_});
        }

        void set_air_plane_throttle(const object &airplane_, float throttle_) {
            host::functions.invoke_raw_binary(__sqf::binary__setairplanethrottle__object__scalar__ret__nothing, airplane_, throttle_);
        }

        void set_ammo_on_pylon(const object &vehicle_, sqf_string_const_ref pylon_name_, int ammo_count_) {
            host::functions.invoke_raw_binary(__sqf::binary__setammoonpylon__object__array__ret__nothing, vehicle_, {pylon_name_, ammo_count_});
        }

        void set_ammo_on_pylon(const object &vehicle_, int pylon_index_, int ammo_count_) {
            host::functions.invoke_raw_binary(__sqf::binary__setammoonpylon__object__array__ret__nothing, vehicle_, {pylon_index_, ammo_count_});
        }

        //#TODO: Find out what the right parameter is
        bool set_pylon_loadout(const object &object_, game_value param_right) {
            return host::functions.invoke_raw_binary(__sqf::binary__setpylonloadout__object__array__ret__bool, object_, param_right);
        }

        void set_pylons_priority(const object &object_, const std::vector<int> &priorities_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpylonspriority__object__array__ret__nothing, object_, auto_array<game_value>(priorities_.begin(), priorities_.end()));
        }

        void set_vehicle_radar(const object &vehicle_, int rules_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehicleradar__object__scalar__ret__nothing, vehicle_, rules_);
        }

        void set_vehicle_receive_remote_targets(const object &vehicle_, bool receive_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclereceiveremotetargets__object__bool__ret__nothing, vehicle_, receive_);
        }

        void set_vehicle_report_own_position(const object &vehicle_, bool report_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclereportownposition__object__bool__ret__nothing, vehicle_, report_);
        }

        void set_vehicle_report_remote_targets(const object &vehicle_, bool report_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclereportremotetargets__object__bool__ret__nothing, vehicle_, report_);
        }

        bool is_collision_light_on(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__iscollisionlighton__object__ret__bool, value_);
        }

        void enable_copilot(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablecopilot__object__bool__ret__nothing, value0_, value1_);
        }

        void set_pilot_light(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpilotlight__object__bool__ret__nothing, value0_, value1_);
        }

        void set_collision_light(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcollisionlight__object__bool__ret__nothing, value0_, value1_);
        }

        float set_flag_animation_phase(const object &object_, float phase) {
            return host::functions.invoke_raw_binary(__sqf::binary__setflaganimationphase__object__scalar__ret__nothing, object_, phase);
        }

        void set_flag_animation_phase(const object &flag_, float &animation_phase_) {
            host::functions.invoke_raw_binary(__sqf::binary__setflaganimationphase__object__scalar__ret__nothing, flag_, animation_phase_);
        }

        void set_flag_owner(const object &flag_, const object &owner_) {
            host::functions.invoke_raw_binary(__sqf::binary__setflagowner__object__object__ret__nothing, flag_, owner_);
        }

        object create_vehicle_local(sqf_string_const_ref type_, const vector3 &pos_atl_) {
            return object(host::functions.invoke_raw_binary(__sqf::binary__createvehiclelocal__string__array__ret__object, type_, pos_atl_));
        }

        void add_to_remains_collector(const std::vector<object> &objects_) {
            auto_array<game_value> objects(objects_.begin(), objects_.end());

            host::functions.invoke_raw_unary(__sqf::unary__addtoremainscollector__array__ret__nothing, std::move(objects));
        }

        void remove_from_remains_collector(const std::vector<object> &remains_) {
            auto_array<game_value> remains(remains_.begin(), remains_.end());

            host::functions.invoke_raw_unary(__sqf::unary__removefromremainscollector__array__ret__nothing, std::move(remains));
        }

        std::vector<object> crew(const object &_veh) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__crew__object__ret__array, _veh));
        }

        std::vector<rv_crew_member> full_crew(const object &veh_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__object__ret__array, veh_);

            std::vector<rv_crew_member> crew_members;
            for (uint32_t i = 0; i < ret.size(); ++i) {
                std::vector<int> turret_path = __helpers::__convert_to_integers_vector(ret[i][3]);
                crew_members.push_back(rv_crew_member(ret[i][0], ret[i][1], ret[i][2], turret_path, ret[i][4]));
            }

            return crew_members;
        }

        std::vector<rv_crew_member> full_crew(const object &veh_, sqf_string_const_ref filter_, bool include_empty_) {
            game_value params({veh_,
                               filter_,
                               include_empty_});

            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__array__ret__array, params);

            std::vector<rv_crew_member> crew_members;
            for (uint32_t i = 0; i < ret.size(); ++i) {
                std::vector<int> turret_path = __helpers::__convert_to_integers_vector(ret[i][3]);
                crew_members.push_back(rv_crew_member(ret[i][0], ret[i][1], ret[i][2], turret_path, ret[i][4]));
            }

            return crew_members;
        }

        float aimed_at_target(const object &vehicle_, const object &target_) {
            game_value params({target_});

            return host::functions.invoke_raw_binary(__sqf::binary__aimedattarget__object__array__ret__scalar, vehicle_, params);
        }

        float aimed_at_target(const object &vehicle_, const object &target_, sqf_string_const_ref weapon_) {
            game_value params({target_,
                               weapon_});

            return host::functions.invoke_raw_binary(__sqf::binary__aimedattarget__object__array__ret__scalar, vehicle_, params);
        }

        void animate(const object &obj_, sqf_string_const_ref animation_name_, float phase_) {
            game_value params({animation_name_,
                               phase_});

            host::functions.invoke_raw_binary(__sqf::binary__animate__object__array__ret__nothing, obj_, params);
        }

        void animate(const object &obj_, sqf_string_const_ref animation_name_, float phase_, bool instant_) {
            game_value params({animation_name_,
                               phase_,
                               instant_});

            host::functions.invoke_raw_binary(__sqf::binary__animate__object__array__ret__nothing, obj_, params);
        }

        void animate_door(const object &obj_, sqf_string_const_ref door_name_, float phase_, bool now_) {
            game_value params({door_name_,
                               phase_,
                               now_});

            host::functions.invoke_raw_binary(__sqf::binary__animatedoor__object__array__ret__nothing, obj_, params);
        }

        vector3 get_center_of_mass(const object &obj_) {
            return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(__sqf::unary__getcenterofmass__object__ret__array, obj_));
        }

        object create_vehicle(sqf_string_const_ref type_, const vector3 &pos_) {
            return object(host::functions.invoke_raw_binary(__sqf::binary__createvehicle__string__array__ret__object, type_, pos_));
        }

        object create_vehicle(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_, float placement_, sqf_string_const_ref special_) {
            auto_array<game_value> markers(markers_.begin(), markers_.end());
            game_value args({type_,
                             pos_,
                             std::move(markers),
                             placement_,
                             special_});

            return object(host::functions.invoke_raw_unary(__sqf::unary__createvehicle__array__ret__object, args));
        }

        void delete_vehicle(const object &obj_) {
            host::functions.invoke_raw_unary(__sqf::unary__deletevehicle__object__ret__nothing, obj_);
        }

        sqf_return_string_list all_turrets(const object &vehicle_, bool person_turrets_) {
            game_value array_input({vehicle_,
                                    person_turrets_});

            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                __sqf::unary__allturrets__array__ret__array, array_input));
        }

        sqf_return_string_list all_turrets(const object &vehicle_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                __sqf::unary__allturrets__object__ret__array, vehicle_));
        }

        bool alive(const object &obj_) {
            return __helpers::__bool_unary_object(__sqf::unary__alive__object__ret__bool, obj_);
        }

        object assigned_commander(const object &veh_) {
            return __helpers::__object_unary_object(__sqf::unary__assignedcommander__object__ret__object, veh_);
        }

        object assigned_driver(const object &veh_) {
            return __helpers::__object_unary_object(__sqf::unary__assigneddriver__object__ret__object, veh_);
        }

        object assigned_gunner(const object &veh_) {
            return __helpers::__object_unary_object(__sqf::unary__assignedgunner__object__ret__object, veh_);
        }

        object assigned_target(const object &veh_) {
            return __helpers::__object_unary_object(__sqf::unary__assignedtarget__object__ret__object, veh_);
        }

        object commander(const object &veh_) {
            return __helpers::__object_unary_object(__sqf::unary__commander__object__ret__object, veh_);
        }

        void create_vehicle_crew(const object &veh_) {
            __helpers::__empty_unary_object(__sqf::unary__createvehiclecrew__object__ret__nothing, veh_);
        }

        float damage(const object &object_) {
            return __helpers::__number_unary_object(__sqf::unary__damage__object__ret__scalar, object_);
        }

        object driver(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__driver__object__ret__object, value_);
        }

        object effective_commander(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__effectivecommander__object__ret__object, value_);
        }

        void fill_weapons_from_pool(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__fillweaponsfrompool__object__ret__nothing, value_);
        }

        object flag(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__flag__object__ret__object, value_);
        }

        object flag_owner(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__flagowner__object__ret__object, value_);
        }

        sqf_return_string flag_texture(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__flagtexture__object__ret__string, value_);
        }

        side flag_side(const object &value_) {
            return side(host::functions.invoke_raw_unary(__sqf::unary__flagside__object__ret__side, value_));
        }

        float fuel(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__fuel__object__ret__scalar, value_);
        }

        float get_dammage(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getdammage__object__ret__scalar, value_);
        }

        float get_mass(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getmass__object__ret__scalar, value_);
        }

        float get_object_dlc(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getobjectdlc__object__ret__scalar, value_);
        }

        float get_object_type(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getobjecttype__object__ret__scalar, value_);
        }

        void hide_object(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__hideobject__object__ret__nothing, value_);
        }

        void hide_object_global(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__hideobjectglobal__object__ret__nothing, value_);
        }

        bool inflamed(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__inflamed__object__ret__bool, value_);
        }

        bool is_auto_hover_on(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isautohoveron__object__ret__bool, value_);
        }

        bool is_autonomous(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isautonomous__object__ret__bool, value_);
        }

        bool is_burning(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isburning__object__ret__bool, value_);
        }

        bool is_copilot_enabled(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__iscopilotenabled__object__ret__bool, value_);
        }

        bool is_engine_on(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isengineon__object__ret__bool, value_);
        }

        bool is_hidden(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__ishidden__object__ret__bool, value_);
        }

        bool is_in_remains_collector(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isinremainscollector__object__ret__bool, value_);
        }

        bool is_light_on(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__islighton__object__ret__bool, value_);
        }

        bool is_manual_fire(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__ismanualfire__object__ret__bool, value_);
        }

        bool is_marked_for_collection(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__ismarkedforcollection__object__ret__bool, value_);
        }

        bool is_object_hidden(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__isobjecthidden__object__ret__bool, value_);
        }

        bool is_touching_ground(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__istouchingground__object__ret__bool, value_);
        }

        object laser_target(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__lasertarget__object__ret__object, value_);
        }

        sqf_return_string light_is_on(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__lightison__object__ret__string, value_);
        }

        float locked(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__locked__object__ret__scalar, value_);
        }

        bool locked_driver(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__lockeddriver__object__ret__bool, value_);
        }

        bool mine_active(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__mineactive__object__ret__bool, value_);
        }

        object object_parent(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__objectparent__object__ret__object, value_);
        }

        float score(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__score__object__ret__scalar, value_);
        }

        float scud_state(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__scudstate__object__ret__scalar, value_);
        }

        float size_of(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__sizeof__string__ret__scalar, value_);
        }

        float speed(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__speed__object__ret__scalar, value_);
        }

        object vehicle(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__vehicle__object__ret__object, value_);
        }

        sqf_return_string vehicle_var_name(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__vehiclevarname__object__ret__string, value_);
        }

        void allow_crew_in_immobile(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowcrewinimmobile__object__bool__ret__nothing, value0_, value1_);
        }

        void allow_damage(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowdamage__object__bool__ret__nothing, value0_, value1_);
        }

        void allow_dammage(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowdammage__object__bool__ret__nothing, value0_, value1_);
        }

        void disable_nvgequipment(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__disablenvgequipment__object__bool__ret__nothing, value0_, value1_);
        }

        void disable_tiequipment(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__disabletiequipment__object__bool__ret__nothing, value0_, value1_);
        }

        float door_phase(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__doorphase__object__string__ret__scalar, value0_, value1_);
        }

        float empty_positions(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__emptypositions__object__string__ret__scalar, value0_, value1_);
        }

        void engine_on(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__engineon__object__bool__ret__nothing, value0_, value1_);
        }

        float get_hit(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__gethit__object__string__ret__scalar, value0_, value1_);
        }

        float get_hit_index(const object &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__gethitindex__object__scalar__ret__scalar, value0_, value1_);
        }

        float get_hit_point_damage(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__gethitpointdamage__object__string__ret__scalar, value0_, value1_);
        }

        float get_speed(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getspeed__object__string__ret__scalar, value0_, value1_);
        }

        void hide_object(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__hideobject__object__bool__ret__nothing, value0_, value1_);
        }

        void hide_object_global(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__hideobjectglobal__object__bool__ret__nothing, value0_, value1_);
        }

        void inflame(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__inflame__object__bool__ret__nothing, value0_, value1_);
        }

        void limit_speed(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__limitspeed__object__scalar__ret__nothing, value0_, value1_);
        }

        void lock(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__lock__object__bool__ret__nothing, value0_, value1_);
        }

        void lock(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__lock__object__scalar__ret__nothing, value0_, value1_);
        }

        void lock_cargo(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__lockcargo__object__bool__ret__nothing, value0_, value1_);
        }

        void lock_driver(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__lockdriver__object__bool__ret__nothing, value0_, value1_);
        }

        bool locked_cargo(const object &value0_, float value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lockedcargo__object__scalar__ret__bool, value0_, value1_);
        }

        void set_autonomous(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setautonomous__object__bool__ret__nothing, value0_, value1_);
        }

        void set_damage(const object &value0_, float value1_, bool use_effects_) {
            if (use_effects_)
                host::functions.invoke_raw_binary(__sqf::binary__setdamage__object__scalar_array__ret__nothing, value0_, value1_);
            else
                host::functions.invoke_raw_binary(__sqf::binary__setdamage__object__scalar_array__ret__nothing, value0_, {value1_, use_effects_});
        }

        void set_dammage(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setdammage__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_flag_side(const object &value0_, const side &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setflagside__object__side__ret__nothing, value0_, value1_);
        }

        void set_flag_texture(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setflagtexture__object__string__ret__nothing, value0_, value1_);
        }

        void set_fuel(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfuel__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_vehicle_armor(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclearmor__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_vehicle_id(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehicleid__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_vehicle_lock(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclelock__object__string__ret__nothing, value0_, value1_);
        }

        void set_vehicle_var_name(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehiclevarname__object__string__ret__nothing, value0_, value1_);
        }

        void switch_light(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__switchlight__object__string__ret__nothing, value0_, value1_);
        }

        void set_hit(const object &object_, sqf_string_const_ref part_, float damage_) {
            game_value params({part_,
                               damage_});

            host::functions.invoke_raw_binary(__sqf::binary__sethit__object__array__ret__nothing, object_, params);
        }

        void set_hit_index(const object &object_, int part_index_, float damage_) {
            game_value params({static_cast<float>(part_index_),
                               damage_});

            host::functions.invoke_raw_binary(__sqf::binary__sethitindex__object__array__ret__nothing, object_, params);
        }

        void set_hit_point_damage(const object &object_, sqf_string_const_ref hit_point_, float damage_) {
            game_value params({hit_point_,
                               damage_});

            host::functions.invoke_raw_binary(__sqf::binary__sethitpointdamage__object__array__ret__nothing, object_, params);
        }

        rv_hit_points_damage get_all_hit_points_damage(const object &veh_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__getallhitpointsdamage__object__ret__array, veh_);

            return rv_hit_points_damage(ret);
        }

        sqf_return_string_list get_object_materials(const object &object_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__getobjectmaterials__object__ret__array, object_));
        }

        sqf_return_string_list get_object_textures(const object &object_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__getobjecttextures__object__ret__array, object_));
        }

        std::vector<object> synchronized_objects(const object &obj_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__synchronizedobjects__object__ret__array, obj_));
        }

        rv_model_info get_model_info(const object &object_) {
            return rv_model_info(host::functions.invoke_raw_unary(__sqf::unary__getmodelinfo__object__ret__array, object_));
        }

        object create_simple_object(sqf_string_const_ref shapename_, const vector3 &positionworld_) {
            game_value params({shapename_,
                               positionworld_});

            return host::functions.invoke_raw_unary(__sqf::unary__createsimpleobject__array__ret__object, params);
        }

        float get_container_max_load(sqf_string_const_ref containerclass_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getcontainermaxload__string__ret__scalar, containerclass_);
        }

        rv_shot_parents get_shot_parents(const object &projectile_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__getshotparents__object__ret__array, projectile_);

            return rv_shot_parents({ret[0],
                                    ret[1]});
        }

        bool is_simple_object(const object &object_) {
            return host::functions.invoke_raw_unary(__sqf::unary__issimpleobject__object__ret__bool, object_);
        }

        sqf_return_string_list selection_names(const object &object_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(__sqf::unary__selectionnames__object__ret__array, object_));
        }

        void switch_camera(const object &target_) {
            host::functions.invoke_raw_unary(__sqf::unary__switchcamera__object__ret__nothing, target_);
        }

        void animate_source(const object &object_, sqf_string_const_ref source_, float phase_, bool speed_) {
            game_value params_right({source_,
                                     phase_,
                                     speed_});

            host::functions.invoke_raw_binary(__sqf::binary__animatesource__object__array__ret__nothing, object_, params_right);
        }

        void animate_source(const object &object_, sqf_string_const_ref source_, float phase_, float speed_) {
            game_value params_right({source_,
                                     phase_,
                                     speed_});

            host::functions.invoke_raw_binary(__sqf::binary__animatesource__object__array__ret__nothing, object_, params_right);
        }

        float animation_source_phase(const object &object_, sqf_string_const_ref source_) {
            return host::functions.invoke_raw_binary(__sqf::binary__animationsourcephase__object__string__ret__scalar, object_, source_);
        }

        void delete_vehicle_crew(const object &vehicle_, const object &unit_) {
            host::functions.invoke_raw_binary(__sqf::binary__deletevehiclecrew__object__object__ret__nothing, vehicle_, unit_);
        }

        void disable_collision_with(const object &object1_, const object &object2_) {
            host::functions.invoke_raw_binary(__sqf::binary__disablecollisionwith__object__object__ret__nothing, object1_, object2_);
        }

        void enable_collision_with(const object &object1_, const object &object2_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablecollisionwith__object__object__ret__nothing, object1_, object2_);
        }

        void hide_selection(const object &object_, sqf_string_const_ref selection_, bool hide_) {
            game_value params_right({selection_,
                                     hide_});

            host::functions.invoke_raw_binary(__sqf::binary__hideselection__object__array__ret__nothing, object_, params_right);
        }

        void lock_camera_to(const object &vehicle_, const object &target_, const std::vector<int> &turret_path_) {
            game_value params_right({target_,
                                     std::move(auto_array<game_value>({turret_path_.begin(), turret_path_.end()}))});

            host::functions.invoke_raw_binary(__sqf::binary__lockcamerato__object__array__ret__nothing, vehicle_, params_right);
        }

        void lock_cargo(const object &vehicle_, int index_, bool lock_) {
            game_value params_right({index_,
                                     lock_});

            host::functions.invoke_raw_binary(__sqf::binary__lockcargo__object__array__ret__nothing, vehicle_, params_right);
        }

        bool locked_turret(const object &vehicle_, const std::vector<int> &turret_path_) {
            auto_array<game_value> turret_path({turret_path_.begin(), turret_path_.end()});

            return host::functions.invoke_raw_binary(__sqf::binary__lockedturret__object__array__ret__bool, vehicle_, std::move(turret_path));
        }

        void lock_turret(const object &vehicle_, const std::vector<int> &turret_path_, bool lock_) {
            game_value params_right({std::move(auto_array<game_value>({turret_path_.begin(), turret_path_.end()})),
                                     lock_});

            host::functions.invoke_raw_binary(__sqf::binary__lockturret__object__array__ret__nothing, vehicle_, params_right);
        }

        void respawn_vehicle(const object &vehicle_, float delay_, int count_) {
            game_value params_right({delay_,
                                     count_});

            host::functions.invoke_raw_binary(__sqf::binary__respawnvehicle__object__array__ret__nothing, vehicle_, params_right);
        }

        void select_weapon_turret(const object &vec_, sqf_string_const_ref weapon_, const std::vector<int> &turretPath_) {
            auto_array<game_value> turret_path_(turretPath_.begin(), turretPath_.end());
            host::functions.invoke_raw_binary(__sqf::binary__selectweaponturret__object__array__ret__nothing, vec_, {weapon_, std::move(turret_path_)});
        }

        void set_center_of_mass(const object &object_, const vector3 &offset_, float time_ /*= 0.f*/) {
            if (time_ == 0.f)
                host::functions.invoke_raw_binary(__sqf::binary__setcenterofmass__object__array__ret__nothing, object_, offset_);
            else
                host::functions.invoke_raw_binary(__sqf::binary__setcenterofmass__object__array__ret__nothing, object_, {offset_, time_});
        }

        bool set_feature_type(const object &object_, feature_type type_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setfeaturetype__object__scalar__ret__bool, object_, static_cast<int>(type_));
        }

        bool set_feature_type(const object &object_, int type_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setfeaturetype__object__scalar__ret__bool, object_, type_);
        }

        void set_mass(const object &object_, float mass_, std::optional<float> time_) {
            if (time_.has_value())
                host::functions.invoke_raw_binary(__sqf::binary__setmass__object__scalar_array__ret__nothing, object_, {mass_, *time_});
            host::functions.invoke_raw_binary(__sqf::binary__setmass__object__scalar_array__ret__nothing, object_, mass_);
        }

        void set_object_material(const object &object_, int index_, sqf_string_const_ref material_) {
            host::functions.invoke_raw_binary(__sqf::binary__setobjectmaterial__object__array__ret__nothing, object_, {index_, material_});
        }

        void set_object_material_global(const object &object_, int index_, sqf_string_const_ref material_) {
            host::functions.invoke_raw_binary(__sqf::binary__setobjectmaterialglobal__object__array__ret__nothing, object_, {index_, material_});
        }

        void set_object_texture(const object &object_, int index_, sqf_string_const_ref texture_) {
            host::functions.invoke_raw_binary(__sqf::binary__setobjecttexture__object__array__ret__nothing, object_, {index_, texture_});
        }

        void set_object_texture_global(const object &object_, int index_, sqf_string_const_ref texture_) {
            host::functions.invoke_raw_binary(__sqf::binary__setobjecttextureglobal__object__array__ret__nothing, object_, {index_, texture_});
        }

        void set_pilot_camera_direction(const object &vehicle_, const vector3 &direction_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpilotcameradirection__object__array__ret__nothing, vehicle_, direction_);
        }

        void set_pilot_camera_rotation(const object &vehicle_, float yaw_, float pitch_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpilotcamerarotation__object__array__ret__nothing, vehicle_, {yaw_, pitch_});
        }

        bool set_pilot_camera_target(const object &vehicle_, std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector3>> target_) {
            if (target_.index() == 0)
                return host::functions.invoke_raw_binary(__sqf::binary__setpilotcameratarget__object__object_array__ret__bool, vehicle_, std::get<0>(target_));
            return host::functions.invoke_raw_binary(__sqf::binary__setpilotcameratarget__object__object_array__ret__bool, vehicle_, std::get<1>(target_).get());
        }

        void set_shot_parents(const object &projectile_, const object &vehicle_, const object &instigator_) {
            host::functions.invoke_raw_binary(__sqf::binary__setshotparents__object__array__ret__nothing, projectile_, {vehicle_, instigator_});
        }

        //#TODO: Find out which params are to the right
        void set_vehicle_ti_parts(const object &vehicle_, const game_value &params_right_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehicletipars__object__array__ret__nothing, vehicle_, params_right_);
        }

        void set_weapon_reloading_time(const object &vehicle_, const object &gunner_, sqf_string_const_ref muzzle_class_, float reload_time_) {
            host::functions.invoke_raw_binary(__sqf::binary__setweaponreloadingtime__object__array__ret__bool, vehicle_, {gunner_, muzzle_class_, reload_time_});
        }

        void synchronize_objects_add(const object &unit_, const std::vector<object> &objects_) {
            host::functions.invoke_raw_binary(__sqf::binary__synchronizeobjectsadd__object__array__ret__nothing, unit_, std::move(auto_array<game_value>(objects_.begin(), objects_.end())));
        }

        void synchronize_objects_remove(const object &unit_, const std::vector<object> &objects_) {
            host::functions.invoke_raw_binary(__sqf::binary__synchronizeobjectsremove__object__array__ret__nothing, unit_, std::move(auto_array<game_value>(objects_.begin(), objects_.end())));
        }

        object turret_unit(const object &vehicle_, const std::vector<int> &turret_path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__turretunit__object__array__ret__object, vehicle_, std::move(auto_array<game_value>(turret_path_.begin(), turret_path_.end())));
        }

        sqf_return_string_list weapons_turret(const object &vehicle_, const std::vector<int> &turret_path_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_binary(__sqf::binary__weaponsturret__object__array__ret__array, vehicle_, std::move(auto_array<game_value>(turret_path_.begin(), turret_path_.end()))));
        }

        float flag_animation_phase(const object &flag_) {
            return host::functions.invoke_raw_unary(__sqf::unary__flaganimationphase__object__ret__scalar, flag_);
        }

        object create_mine(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_ /* = {}*/, float placement_ /* = 0.0f*/) {
            auto_array<game_value> markers(markers_.begin(), markers_.end());

            game_value args({
                type_,
                pos_,
                std::move(markers),
                placement_,
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createmine__array__ret__object, args));
        }

        void unassign_vehicle(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__unassignvehicle__object__ret__nothing, value_);
        }

        void assign_to_airport(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__assigntoairport__object__object_scalar__ret__nothing, value0_, value1_);
        }

        void assign_to_airport(const object &value0_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__assigntoairport__object__object_scalar__ret__nothing, value0_, target_);
        }

        void set_light_brightness(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightbrightness__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_day_light(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightdaylight__object__bool__ret__nothing, value0_, value1_);
        }

        void set_light_flare_max_distance(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightflaremaxdistance__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_flare_size(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightflaresize__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_intensity(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightintensity__object__scalar__ret__nothing, value0_, value1_);
        }

        void set_light_use_flare(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightuseflare__object__bool__ret__nothing, value0_, value1_);
        }

        rv_uav_control uav_control(const object &uav_) {
            return rv_uav_control(host::functions.invoke_raw_unary(__sqf::unary__uavcontrol__object__ret__array, uav_));
        }

        side get_side(const object &object_) {
            return side(host::functions.invoke_raw_unary(__sqf::unary__side__object__ret__side, object_));
        }

        sqf_return_string wf_side_text(const object &object_) {
            return __helpers::__string_unary_object(__sqf::unary__wfsidetext__object__ret__string, object_);
        }

        sqf_return_string wf_side_text(const group &group_) {
            return host::functions.invoke_raw_unary(__sqf::unary__wfsidetext__group__ret__string, group_);
        }

        sqf_return_string wf_side_text(const side &side_) {
            return host::functions.invoke_raw_unary(__sqf::unary__wfsidetext__side__ret__string, side_);
        }

        void set_light_ambient(const object &light_, float r_, float g_, float b_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightambient__object__array__ret__nothing, light_, {r_, g_, b_});
        }

        void set_light_attenuation(const object &light_, float start_, float constant_, float linear_, float quadratic_, float hard_limit_start_, float hard_limit_end_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightattenuation__object__array__ret__nothing, light_, {start_, start_, constant_, linear_, quadratic_, hard_limit_start_, hard_limit_end_});
        }

        void set_light_color(const object &light_, float r_, float g_, float b_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightcolor__object__array__ret__nothing, light_, {r_, g_, b_});
        }

        std::vector<object> roads_connected_to(const object &obj_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__roadsconnectedto__object__ret__array, obj_));
        }

    }  // namespace sqf
}  // namespace intercept
