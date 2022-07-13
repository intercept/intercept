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
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__getpylonmagazines__object__ret__array, vehicle_));
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
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__crew__object__ret__array, _veh));
        }

        std::vector<rv_crew_member> full_crew(const object &veh_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__object__ret__array, veh_);
            return __helpers::__convert_to_vector<rv_crew_member>(ret);
        }

        std::vector<rv_crew_member> full_crew(const object &veh_, sqf_string_const_ref filter_, bool include_empty_) {
            game_value params({veh_,
                               filter_,
                               include_empty_});

            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__fullcrew__array__ret__array, params);
            return __helpers::__convert_to_vector<rv_crew_member>(ret);
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
            return host::functions.invoke_raw_unary(__sqf::unary__getcenterofmass__object__ret__array, obj_);
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

        std::vector<rv_turret_path> all_turrets(const object &vehicle_, bool person_turrets_) {
            game_value array_input({vehicle_,
                                    person_turrets_});
            return __helpers::__convert_to_vector<rv_turret_path>(host::functions.invoke_raw_unary(
                __sqf::unary__allturrets__array__ret__array, array_input));
        }

        std::vector<rv_turret_path> all_turrets(const object &vehicle_) {
            return __helpers::__convert_to_vector<rv_turret_path>(host::functions.invoke_raw_unary(
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

        group create_vehicle_crew(const object &veh_) {
            return group(host::functions.invoke_raw_unary(__sqf::unary__createvehiclecrew__object__ret__group, veh_));
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

        int get_object_type(const object &value_) {
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
            return __helpers::__bool_unary_object(__sqf::unary__islighton__object_array__ret__bool, value_);
        }

        bool is_light_on(const object &value_, const auto_array<float>& turret_) {
            game_value params({ value_, turret_ });
            return host::functions.invoke_raw_unary(__sqf::unary__islighton__object_array__ret__bool, params);
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

        object missile_target(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__missiletarget__object__ret__object, value_);
        }

        vector3 missile_target_pos(const object &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__missiletargetpos__object__ret__array, value_);
        }

        bool set_missile_target(const object &value_, const object &target_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setmissiletarget__object__object__ret__bool, value_, target_);
        }

        void set_missile_target_pos(const object &value_, const vector3 &position_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmissiletargetpos__object__array__ret__nothing, value_, position_);
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

        void allow_crew_in_immobile(const object &veh_, bool allow_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowcrewinimmobile__object__bool_array__ret__nothing, veh_, allow_);
        }

        void allow_crew_in_immobile(const object& veh_, bool broken_wheel_, bool upside_down_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowcrewinimmobile__object__bool_array__ret__nothing, veh_, {broken_wheel_, upside_down_});
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

        bool set_autonomous(const object &value0_, bool value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setautonomous__object__bool__ret__bool, value0_, value1_);
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
            host::functions.invoke_raw_binary(__sqf::binary__sethitpointdamage__object__array__ret__nothing, object_, {hit_point_, damage_});
        }

        rv_hit_points_damage get_all_hit_points_damage(const object &veh_) {
            return rv_hit_points_damage(host::functions.invoke_raw_unary(__sqf::unary__getallhitpointsdamage__object__ret__array, veh_));
        }

        sqf_return_string_list get_object_materials(const object &object_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__getobjectmaterials__object__ret__array, object_));
        }

        sqf_return_string_list get_object_textures(const object &object_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__getobjecttextures__object__ret__array, object_));
        }

        std::vector<object> synchronized_objects(const object &obj_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__synchronizedobjects__object__ret__array, obj_));
        }

        rv_model_info get_model_info(const object &object_) {
            return rv_model_info(host::functions.invoke_raw_unary(__sqf::unary__getmodelinfo__object__ret__array, object_));
        }

        object create_simple_object(sqf_string_const_ref shapename_, const vector3 &positionworld_, bool local_) {
            return host::functions.invoke_raw_unary(__sqf::unary__createsimpleobject__array__ret__object, {shapename_, positionworld_, local_});
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
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__selectionnames__object__ret__array, object_));
        }

        sqf_return_string_list selection_names(const object &object_, float lod_res_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_binary(__sqf::binary__selectionnames__object__string_scalar__ret__array, object_, lod_res_));
        }

        sqf_return_string_list selection_names(const object &object_, rv_selection_lods lod_) {
            game_value lod_name;
            switch (lod_) {
                case intercept::sqf::rv_selection_lods::Memory:
                    lod_name = "Memory"sv;
                    break;
                case intercept::sqf::rv_selection_lods::Geometry:
                    lod_name = "Geometry"sv;
                    break;
                case intercept::sqf::rv_selection_lods::FireGeometry:
                    lod_name = "FireGeometry"sv;
                    break;
                case intercept::sqf::rv_selection_lods::LandContact:
                    lod_name = "LandContact"sv;
                    break;
                case intercept::sqf::rv_selection_lods::HitPoints:
                    lod_name = "HitPoints"sv;
                    break;
                case intercept::sqf::rv_selection_lods::ViewGeometry:
                    lod_name = "ViewGeometry"sv;
                    break;
                default:
                    lod_name = ""sv;
                    break;
            }
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_binary(__sqf::binary__selectionnames__object__string_scalar__ret__array, object_, std::move(lod_name)));
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

        void lock_camera_to(const object &vehicle_, const object &target_, const rv_turret_path &turret_path_) {
            host::functions.invoke_raw_binary(__sqf::binary__lockcamerato__object__array__ret__nothing, vehicle_, {target_, turret_path_});
        }

        object locked_camera_to(const object &vehicle_, const rv_turret_path &turret_path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lockedcamerato__object__array__ret__nothing_object, vehicle_, turret_path_);
        }

        void lock_cargo(const object &vehicle_, int index_, bool lock_) {
            game_value params_right({index_,
                                     lock_});

            host::functions.invoke_raw_binary(__sqf::binary__lockcargo__object__array__ret__nothing, vehicle_, params_right);
        }

        bool locked_turret(const object &vehicle_, const rv_turret_path &turret_path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__lockedturret__object__array__ret__bool, vehicle_, turret_path_);
        }

        void lock_turret(const object &vehicle_, const rv_turret_path &turret_path_, bool lock_) {
            host::functions.invoke_raw_binary(__sqf::binary__lockturret__object__array__ret__nothing, vehicle_, {turret_path_, lock_});
        }

        void respawn_vehicle(const object &vehicle_, float delay_, int count_) {
            game_value params_right({delay_,
                                     count_});

            host::functions.invoke_raw_binary(__sqf::binary__respawnvehicle__object__array__ret__nothing, vehicle_, params_right);
        }

        void select_weapon_turret(const object &vec_, sqf_string_const_ref weapon_, rv_turret_path turret_path_) {
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

        float weapon_reloading_time(const object& vehicle_, const object& gunner_, sqf_string_const_ref muzzle_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__weaponreloadingtime__object__array__ret__scalar, vehicle_, {gunner_, muzzle_name_});
        }

        void synchronize_objects_add(const object &unit_, const std::vector<object> &objects_) {
            host::functions.invoke_raw_binary(__sqf::binary__synchronizeobjectsadd__object__array__ret__nothing, unit_, std::move(auto_array<game_value>(objects_.begin(), objects_.end())));
        }

        void synchronize_objects_remove(const object &unit_, const std::vector<object> &objects_) {
            host::functions.invoke_raw_binary(__sqf::binary__synchronizeobjectsremove__object__array__ret__nothing, unit_, std::move(auto_array<game_value>(objects_.begin(), objects_.end())));
        }

        object turret_unit(const object &vehicle_, const rv_turret_path &turret_path_) {
            return host::functions.invoke_raw_binary(__sqf::binary__turretunit__object__array__ret__object, vehicle_, turret_path_);
        }

        sqf_return_string_list weapons_turret(const object &vehicle_, const rv_turret_path &turret_path_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_binary(__sqf::binary__weaponsturret__object__array__ret__array, vehicle_, turret_path_));
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

        void set_light_cone_pars(const object &lightcone_, float outer_angle_, float inner_angle_, float fade_coef_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightconepars__object__array__ret__nothing, lightcone_, {outer_angle_, inner_angle_, fade_coef_});
        }

        void set_light_ir(const object &lightcone_, bool ir_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightir__object__bool__ret__nothing, lightcone_, ir_);
        }

        void set_light_volume_shape(const object& lightcone_, sqf_string_const_ref shape_path_, float scale_) {
            host::functions.invoke_raw_binary(__sqf::binary__setlightvolumeshape__object__array__ret__nothing, lightcone_, {shape_path_, scale_});
        }

        rv_uav_control uav_control(const object &uav_) {
            return rv_uav_control(host::functions.invoke_raw_unary(__sqf::unary__uavcontrol__object__ret__array, uav_));
        }

        bool is_vehicle_radar_on(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isvehicleradaron__object__ret__bool, vehicle_);
        }

        sqf_return_string_list list_vehicle_sensors(const object &vehicle_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__listvehiclesensors__object__ret__array, vehicle_));
        }

        void add_force(const object &object_, vector3 force_, vector3 position_) {
            host::functions.invoke_raw_binary(__sqf::binary__addforce__object__array__ret__nothing, object_, { force_, position_ });
        }
        void add_torque(const object &object_, vector3 torque_) {
            host::functions.invoke_raw_binary(__sqf::binary__addtorque__object__array__ret__nothing, object_, torque_);
        }

        void trigger_ammo(const object &object_) {
            __helpers::__empty_unary_object(__sqf::unary__triggerammo__object__ret__nothing, object_);
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
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__roadsconnectedto__object_array__ret__array, obj_));
        }

        void elevate_periscope(const object &vehicle_, const rv_turret_path &turret_, float elevation_, float speed_, bool blockuser_) {
            host::functions.invoke_raw_binary(__sqf::binary__elevateperiscope__object__array__ret__nothing, vehicle_, {turret_, elevation_, speed_, blockuser_});
        }
        void elevate_periscope(const object &vehicle_, const rv_turret_path &turret_, float elevation_, bool instant_, bool blockuser_) {
            host::functions.invoke_raw_binary(__sqf::binary__elevateperiscope__object__array__ret__nothing, vehicle_, {turret_, elevation_, instant_, blockuser_});
        }

        rv_periscope_state periscope_elevation(const object &vehicle_, const rv_turret_path &turret_) {
            return rv_periscope_state(host::functions.invoke_raw_binary(__sqf::binary__periscopeelevation__object__array__ret__nothing, vehicle_, turret_));
        }

        bool enable_info_panel_component(const object &vehicle_, const rv_turret_path &turret_, sqf_string_const_ref panel_id_, sqf_string_const_ref componentClassOrType_, bool enable_) {
            return host::functions.invoke_raw_binary(__sqf::binary__enableinfopanelcomponent__object_array__array__ret__bool, {vehicle_, turret_}, {panel_id_, componentClassOrType_, enable_});
        }
        bool enable_info_panel_component(const object &vehicle_, sqf_string_const_ref panel_id_, sqf_string_const_ref componentClassOrType_, bool enable_) {
            return host::functions.invoke_raw_binary(__sqf::binary__enableinfopanelcomponent__object_array__array__ret__bool, vehicle_, {panel_id_, componentClassOrType_, enable_});
        }
        bool info_panel_component_enabled(const object &vehicle_, const rv_turret_path &turret_, sqf_string_const_ref panel_id_, sqf_string_const_ref componentClassOrType_) {
            return host::functions.invoke_raw_binary(__sqf::binary__infopanelcomponentenabled__object_array__array__ret__bool, {vehicle_, turret_}, {panel_id_, componentClassOrType_});
        }
        bool info_panel_component_enabled(const object &vehicle_, sqf_string_const_ref panel_id_, sqf_string_const_ref componentClassOrType_) {
            return host::functions.invoke_raw_binary(__sqf::binary__infopanelcomponentenabled__object_array__array__ret__bool, vehicle_, {panel_id_, componentClassOrType_});
        }

        std::vector<rv_info_panel_component> info_panel_components(const object &vehicle_, sqf_string_const_ref panel_id_) {
            return __helpers::__convert_to_vector<rv_info_panel_component>(host::functions.invoke_raw_binary(__sqf::binary__infopanelcomponents__object_array__string__ret__array, vehicle_, panel_id_));
        }
        std::vector<rv_info_panel_component> info_panel_components(const object &vehicle_, const rv_turret_path &turret_, sqf_string_const_ref panel_id_) {
            return __helpers::__convert_to_vector<rv_info_panel_component>(host::functions.invoke_raw_binary(__sqf::binary__infopanelcomponents__object_array__string__ret__array, {vehicle_, turret_}, panel_id_));
        }

        void enable_vehicle_sensor(const object &vehicle_, sqf_string_const_ref component_, bool enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablevehiclesensor__object__array__ret__nothing, vehicle_, {component_, enable_});
        }

        std::vector<rv_vehicle_sensor> is_vehicle_sensor_enabled(const object &vehicle_, sqf_string_const_ref component_) {
            return __helpers::__convert_to_vector<rv_vehicle_sensor>(host::functions.invoke_raw_binary(__sqf::binary__isvehiclesensorenabled__object__string__ret__array, vehicle_, component_));
        }

        std::variant<sqf_return_string_list, std::vector<sqf_return_string_list>> get_compatible_pylon_magazines(std::variant<const object, sqf_string_const_ref> vehicle_, std::variant<float, sqf_string_const_ref> pylon_) {
            if (vehicle_.index() == 0) {
                game_value gv;
                if (pylon_.index() == 0) {
                    gv = host::functions.invoke_raw_binary(__sqf::binary__getcompatiblepylonmagazines__object__string_scalar__ret__array, std::get<0>(vehicle_), std::get<0>(pylon_));
                } else {
                    gv = host::functions.invoke_raw_binary(__sqf::binary__getcompatiblepylonmagazines__object__string_scalar__ret__array, std::get<0>(vehicle_), std::get<1>(pylon_));
                }
                auto& game_return = gv.to_array();
                if (game_return.is_empty()) return sqf_return_string_list();
                try {
                    std::vector<sqf_return_string_list> temp_return{};
                    temp_return.reserve(game_return.size());
                    for (auto &item : game_return) {
                        auto& temp_array = item.to_array();
                        temp_return.emplace_back(std::vector<sqf_return_string>(temp_array.begin(), temp_array.end()));
                    }
                    return temp_return;
                } catch (const game_value_conversion_error &) {
                    return __helpers::__convert_to_vector<sqf_return_string>(game_return);
                }
            } else {
                game_value gv;
                if (pylon_.index() == 0) {
                    gv = host::functions.invoke_raw_binary(__sqf::binary__getcompatiblepylonmagazines__string__string_scalar__ret__array, std::get<1>(vehicle_), std::get<0>(pylon_));
                } else {
                    gv = host::functions.invoke_raw_binary(__sqf::binary__getcompatiblepylonmagazines__string__string_scalar__ret__array, std::get<1>(vehicle_), std::get<1>(pylon_));
                }
                auto& game_return = gv.to_array();
                if (game_return.is_empty()) return sqf_return_string_list();
                try {
                    std::vector<sqf_return_string_list> temp_return{};
                    temp_return.reserve(game_return.size());
                    for (auto &item : game_return) {
                        auto &temp_array = item.to_array();
                        temp_return.emplace_back(std::vector<sqf_return_string>(temp_array.begin(), temp_array.end()));
                    }
                    return temp_return;
                } catch (const game_value_conversion_error &) {
                    return __helpers::__convert_to_vector<sqf_return_string>(game_return);
                }
            }
        }

        void set_effective_commander(const object &vehicle_, const object &commander_) {
            host::functions.invoke_raw_binary(__sqf::binary__seteffectivecommander__object__object__ret__nothing, vehicle_, commander_);
        }

        void set_plate_number(const object &vehicle_, sqf_string_const_ref str_number_) {
            host::functions.invoke_raw_binary(__sqf::binary__setplatenumber__object__string__ret__nothing, vehicle_, str_number_);
        }

        rv_turret_path unit_turret(const object &vehicle_, const object &gunner_) {
            return rv_turret_path(host::functions.invoke_raw_binary(__sqf::binary__unitturret__object__object__ret__array, vehicle_, gunner_));
        }

        sqf_return_string_list animation_names(const object &vehicle_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__animationnames__object__ret__array, vehicle_));
        }

        object current_pilot(const object &vehicle_) {
            return __helpers::__object_unary_object(__sqf::unary__currentpilot__object__ret__object, vehicle_);
        }

        std::vector<rv_pylon_info> get_all_pylons_info(const object &vehicle_) {
            return __helpers::__convert_to_vector<rv_pylon_info>(host::functions.invoke_raw_unary(__sqf::unary__getallpylonsinfo__object__ret__array, vehicle_));
        }

        bool set_weapon_zeroing(const object &vehicle_, sqf_string_const_ref weapon_class_, sqf_string_const_ref muzzle_class_, float zeroing_index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setweaponzeroing__object__array__ret__bool, vehicle_, {weapon_class_, muzzle_class_, zeroing_index_});
        }

        void set_user_mfd_text(const object &vehicle_, float index_, sqf_string_const_ref text_) {
            host::functions.invoke_raw_binary(__sqf::binary__setusermfdtext__object__array__ret__nothing, vehicle_, {index_, text_});
        }

        sqf_return_string get_plate_number(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getplatenumber__object__ret__string, vehicle_);
        }

        sqf_return_string_list get_user_mfd_text(const object &vehicle_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__getusermfdtext__object__ret__array, vehicle_));
        }

        std::vector<float> get_user_mfd_value(const object &vehicle_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__getusermfdvalue__object__ret__array, vehicle_));
        }

        std::vector<float> get_vehicle_ti_pars(const object &vehicle_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__getvehicletipars__object__ret__array, vehicle_));
        }

        void set_vehicle_ti_pars(const object &vehicle_, const std::vector<float> &pars_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvehicletipars__object__array__ret__nothing, vehicle_, pars_);
        }

        rv_info_panel info_panel(sqf_string_const_ref panel_id_) {
            return rv_info_panel(host::functions.invoke_raw_unary(__sqf::unary__infopanel__string__ret__array, panel_id_));
        }

        std::vector<rv_info_panel> info_panels(const object &vehicle_) {
            return __helpers::__convert_to_vector<rv_info_panel>(host::functions.invoke_raw_unary(__sqf::unary__infopanels__object_array__ret__array, vehicle_));
        }

        std::vector<rv_info_panel> info_panels(const object &vehicle_, const rv_turret_path &turret_) {
            return __helpers::__convert_to_vector<rv_info_panel>(host::functions.invoke_raw_unary(__sqf::unary__infopanels__object_array__ret__array, {vehicle_, turret_}));
        }

        bool is_laser_on(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__islaseron__object__ret__bool, vehicle_);
        }

        std::vector<rv_remote_target_info> list_remote_targets(side side_) {
            return __helpers::__convert_to_vector<rv_remote_target_info>(host::functions.invoke_raw_unary(__sqf::unary__listremotetargets__side__ret__array, side_));
        }

        std::vector<rv_named_properties> named_properties(const object &vehicle_) {
            return __helpers::__convert_to_vector<rv_named_properties>(host::functions.invoke_raw_unary(__sqf::unary__namedproperties__object__ret__array, vehicle_));
        }

        bool set_info_panel(sqf_string_const_ref infopanelId_, sqf_string_const_ref componentClassOrType_) {
            return host::functions.invoke_raw_unary(__sqf::unary__setinfopanel__array__ret__bool, {infopanelId_, componentClassOrType_});
        }

        void set_cruise_control(const object &veh_, float speed_, bool auto_thrust_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcruisecontrol__object__array__ret__nothing, veh_, {speed_, auto_thrust_});
        }

        void set_tow_parent(const object &towed_vehicle_, const object &towing_vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__settowparent__object__object__ret__nothing, towed_vehicle_, towing_vehicle_);
        }

        std::vector<rv_lod_info> all_lods(const object &obj_) {
            return __helpers::__convert_to_vector<rv_lod_info>(host::functions.invoke_raw_unary(__sqf::unary__alllods__object_string__ret__array, obj_));
        }

        std::vector<rv_lod_info> all_lods(sqf_string_const_ref model_path_) {
            return __helpers::__convert_to_vector<rv_lod_info>(host::functions.invoke_raw_unary(__sqf::unary__alllods__object_string__ret__array, model_path_));
        }

        void delete_vehicle_crew(const object &vehicle_) {
            host::functions.invoke_raw_unary(__sqf::unary__deletevehiclecrew__object__ret__nothing, vehicle_);
        }

        rv_cruise_params get_cruise_control(const object &veh_) {
            return rv_cruise_params(host::functions.invoke_raw_unary(__sqf::unary__getcruisecontrol__object__ret__array, veh_));
        }

        bool direction_stabilization_enabled(const object &vehicle_, const rv_turret_path &turret_) {
            return host::functions.invoke_raw_binary(__sqf::binary__directionstabilizationenabled__object__array__ret__bool, vehicle_, turret_);
        }

        void enable_direction_stabilization(const object &vehicle_, bool enabled_, const rv_turret_path &turret_) {
            host::functions.invoke_raw_binary(__sqf::binary__enabledirectionstabilization__object__array__ret__nothing, vehicle_, {enabled_, turret_});
        }

        std::vector<rv_sensor_target> get_sensor_targets(const object &vehicle_) {
            return __helpers::__convert_to_vector<rv_sensor_target>(host::functions.invoke_raw_unary(__sqf::unary__getsensortargets__object__ret__array, vehicle_));
        }

        std::vector<rv_sensor_threat> get_sensor_threats(const object &vehicle_) {
            return __helpers::__convert_to_vector<rv_sensor_threat>(host::functions.invoke_raw_unary(__sqf::unary__getsensorthreats__object__ret__array, vehicle_));
        }

        void set_max_load(const object &container_, float load_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmaxload__object__scalar__ret__nothing, container_, load_);
        }

        float max_load(const object& container_) {
            return host::functions.invoke_raw_unary(__sqf::unary__maxload__object__ret__scalar, container_);
        }

        bool is_awake(const object& obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isawake__object__ret__bool, obj_);
        }

        void awake(const object& obj_, bool awake_) {
            host::functions.invoke_raw_binary(__sqf::binary__awake__object__bool__ret__nothing, obj_, awake_);
        }

        bool brakes_disabled(const object& veh_) {
            return host::functions.invoke_raw_unary(__sqf::unary__brakesdisabled__object__ret__bool, veh_);
        }

        void disable_brakes(const object& veh_, bool disable_) {
            host::functions.invoke_raw_binary(__sqf::binary__disablebrakes__object__bool__ret__nothing, veh_, disable_);
        }

        std::vector<rv_collision_status> collision_disabled_with(const object& obj_) {
            return __helpers::__convert_to_vector<rv_collision_status>(host::functions.invoke_raw_unary(__sqf::unary__collisiondisabledwith__object__ret__array, obj_));
        }

        bool is_allowed_crew_in_immobile(const object& veh_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isallowedcrewinimmobile__object__ret__bool, veh_);
        }

        void set_turret_optics_mode(const object &veh_, int index_) {
            host::functions.invoke_raw_binary(__sqf::binary__setturretopticsmode__object__scalar__ret__nothing, veh_, index_);
        }

        int get_turret_optics_mode(const object &veh_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getturretopticsmode__object__ret__array, veh_);
        }

        void set_turret_optics_mode(const object &veh_, const rv_turret_path &turret_, int index_) {
            host::functions.invoke_raw_binary(__sqf::binary__setturretopticsmode__object__array__ret__nothing, veh_, {turret_, index_});
        }

        int get_turret_optics_mode(const object &veh_, const rv_turret_path &turret_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getturretopticsmode__object__array__ret__nothing, veh_, turret_);
        }
    }  // namespace sqf
}  // namespace intercept
