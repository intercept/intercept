#include "waypoint.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        //#TODO move to headerfile once inline variables is implemented in MSVC2017
        const std::string_view waypoint::__speed_lookup[4] = {"UNCHANGED"sv, "LIMITED"sv, "NORMAL"sv, "FULL"sv};
        const std::string_view waypoint::__show_lookup[4] = {"NEVER"sv, "EASY"sv, "ALWAYS"sv, "ERROR"sv};
        const std::string_view waypoint::__type_lookup[22] = {"MOVE"sv, "DESTROY"sv, "GETIN"sv, "SAD"sv, "JOIN"sv, "LEADER"sv, "GETOUT"sv, "CYCLE"sv, "LOAD"sv, "UNLOAD"sv, "TR UNLOAD"sv, "HOLD"sv, "SENTRY"sv, "GUARD"sv, "TALK"sv, "SCRIPTED"sv, "SUPPORT"sv, "GETIN NEAREST"sv, "DISMISS"sv, "LOITER"sv, "AND"sv, "OR"sv};
        const std::string_view waypoint::__behaviour_lookup[6] = {"UNCHANGED"sv, "CARELESS"sv, "SAFE"sv, "AWARE"sv, "COMBAT"sv, "STEALTH"sv};
        const std::string_view waypoint::__combat_mode_lookup[6] = {"NO CHANGE"sv, "BLUE"sv, "GREEN"sv, "WHITE"sv, "YELLOW"sv, "RED"sv};
        const std::string_view waypoint::__formation_lookup[10] = {"NO CHANGE"sv, "COLUMN"sv, "STAG COLUMN"sv, "WEDGE"sv, "ECH LEFT"sv, "ECH RIGHT"sv, "VEE"sv, "LINE"sv, "FILE"sv, "DIAMOND"sv};
        const std::string_view waypoint::__loiter_lookup[2] = {"CIRCLE"sv, "CIRCLE_L"sv};

        waypoint add_waypoint(group &gp_, const vector3 &center_, float radius_, int index_, sqf_string_const_ref name_) {
            game_value args({center_,
                             radius_,
                             static_cast<float>(index_),
                             name_});

            return waypoint(game_value(host::functions.invoke_raw_binary(__sqf::binary__addwaypoint__group__array__ret__array, gp_, args)));
        }

        waypoint add_waypoint(group &gp_, const object &center_, float radius_, int index_, sqf_string_const_ref name_) {
            game_value args({center_,
                             radius_,
                             static_cast<float>(index_),
                             name_});

            return waypoint(game_value(host::functions.invoke_raw_binary(__sqf::binary__addwaypoint__group__array__ret__array, gp_, args)));
        }

        void delete_waypoint(waypoint &wp_) {
            host::functions.invoke_raw_unary(__sqf::unary__deletewaypoint__array__ret__nothing, wp_);
        }

        void copy_waypoints(group &to_, group &from_) {
            host::functions.invoke_raw_binary(__sqf::binary__copywaypoints__group__group__ret__nothing, to_, from_);
        }

        /* Waypoint */
        object waypoint_attached_object(waypoint &wp_) {
            return object(host::functions.invoke_raw_unary(__sqf::unary__waypointattachedobject__array__ret__object, wp_));
        }

        object waypoint_attached_vehicle(waypoint &wp_) {
            return object(host::functions.invoke_raw_unary(__sqf::unary__waypointattachedvehicle__array__ret__object, wp_));
        }

        waypoint::behaviour waypoint_behaviour(waypoint &wp_) {
            return waypoint::__parse_behaviour(host::functions.invoke_raw_unary(__sqf::unary__waypointbehaviour__array__ret__string, wp_));
        }

        waypoint::combat_mode waypoint_combat_mode(waypoint &wp_) {
            return waypoint::__parse_combat_mode(host::functions.invoke_raw_unary(__sqf::unary__waypointcombatmode__array__ret__string, wp_));
        }

        float waypoint_completeion_radius(waypoint &wp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__waypointcompletionradius__array__ret__scalar, wp_);
        }

        sqf_return_string waypoint_description(waypoint &wp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__waypointdescription__array__ret__string, wp_);
        }

        waypoint::formation waypoint_formation(waypoint &wp_) {
            return waypoint::__parse_formation(host::functions.invoke_raw_unary(__sqf::unary__waypointformation__array__ret__string, wp_));
        }

        float waypoint_house_position(waypoint &wp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__waypointhouseposition__array__ret__scalar, wp_);
        }

        float waypoint_loiter_radius(waypoint &wp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__waypointloiterradius__array__ret__scalar, wp_);
        }

        waypoint::loiter_type waypoint_loiter_type(waypoint &wp_) {
            return waypoint::__parse_loiter_type(host::functions.invoke_raw_unary(__sqf::unary__waypointloitertype__array__ret__string, wp_));
        }

        sqf_return_string waypoint_name(waypoint &wp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__waypointname__array__ret__string, wp_);
        }
        vector3 waypoint_position(waypoint &wp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__waypointposition__array__ret__array, wp_);
        }

        sqf_return_string waypoint_script(waypoint &wp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__waypointscript__array__ret__string, wp_);
        }
        waypoint::show waypoint_show(waypoint &wp_) {
            return waypoint::__parse_show(host::functions.invoke_raw_unary(__sqf::unary__waypointshow__array__ret__string, wp_));
        }
        waypoint::speed waypoint_speed(waypoint &wp_) {
            return waypoint::__parse_speed(host::functions.invoke_raw_unary(__sqf::unary__waypointspeed__array__ret__string, wp_));
        }

        rv_waypoint_statements waypoint_statements(const waypoint &wp_) {
            return rv_waypoint_statements(host::functions.invoke_raw_unary(__sqf::unary__waypointstatements__array__ret__array, wp_));
        }

        rv_waypoint_timeout waypoint_timeout(const waypoint &wp_) {
            return rv_waypoint_timeout(host::functions.invoke_raw_unary(__sqf::unary__waypointtimeout__array__ret__array, wp_));
        }

        waypoint::type waypoint_type(waypoint &wp_) {
            return waypoint::__parse_type(host::functions.invoke_raw_unary(__sqf::unary__waypointtype__array__ret__string, wp_));
        }
        bool waypoint_visible(waypoint &wp_) {
            //#TODO THIS CAN RETURN 0, CHECK FOR 0 AND RETURN FALSE.
            return host::functions.invoke_raw_unary(__sqf::unary__waypointvisible__array__ret__scalar, wp_);
        }
        std::vector<waypoint> synchronized_waypoints(waypoint &wp_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__synchronizedwaypoints__array__ret__array, wp_);
            return __helpers::__convert_to_vector<waypoint>(ret);
        }
        std::vector<waypoint> synchronized_waypoints(object &obj_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__synchronizedwaypoints__object__ret__array, obj_);
            return __helpers::__convert_to_vector<waypoint>(ret);
        }

        void set_waypoint_behaviour(waypoint &wp_, waypoint::behaviour mode_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointbehaviour__array__string__ret__nothing, wp_, waypoint::__get_enum_as_str(mode_));
        }
        void set_waypoint_combat_mode(waypoint &wp_, waypoint::combat_mode mode_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointcombatmode__array__string__ret__nothing, wp_, waypoint::__get_enum_as_str(mode_));
        }
        void set_waypoint_completion_radius(waypoint &wp_, float radius_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointcompletionradius__array__scalar__ret__nothing, wp_, radius_);
        }
        void set_waypoint_description(waypoint &wp_, std::string &text_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointdescription__array__string__ret__nothing, wp_, text_);
        }
        void set_waypoint_formation(waypoint &wp_, waypoint::formation formation_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointformation__array__string__ret__nothing, wp_, waypoint::__get_enum_as_str(formation_));
        }
        void set_waypoint_house_position(waypoint &wp_, float house_pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointhouseposition__array__scalar__ret__nothing, wp_, house_pos_);
        }
        void set_waypoint_loiter_radius(waypoint &wp_, float radius_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointloiterradius__array__scalar__ret__nothing, wp_, radius_);
        }
        void set_waypoint_loiter_type(waypoint &wp_, waypoint::loiter_type type_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointloitertype__array__string__ret__nothing, wp_, waypoint::__get_enum_as_str(type_));
        }
        void set_waypoint_name(waypoint &wp_, std::string &name_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointname__array__string__ret__nothing, wp_, name_);
        }
        void set_waypoint_position(waypoint &wp_, vector3 &pos_, float radius_) {
            game_value args({pos_, radius_});
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointposition__array__array__ret__nothing, wp_, args);
        }
        void set_waypoint_script(waypoint &wp_, std::string &command_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointscript__array__string__ret__nothing, wp_, command_);
        }
        void set_waypoint_speed(waypoint &wp_, waypoint::speed mode_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointspeed__array__string__ret__nothing, wp_, waypoint::__get_enum_as_str(mode_));
        }
        void set_waypoint_statements(waypoint &wp_, std::string condition_, std::string statement_) {
            game_value args({condition_, statement_});
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointstatements__array__array__ret__nothing, wp_, args);
        }
        void set_waypoint_timeout(waypoint &wp_, float min_, float mid_, float max_) {
            game_value args({game_value({min_,
                                         mid_,
                                         max_})});
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointtimeout__array__array__ret__nothing, wp_, args);
        }
        void set_waypoint_type(waypoint &wp_, waypoint::type type_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointtype__array__string__ret__nothing, wp_, waypoint::__get_enum_as_str(type_));
        }
        void set_waypoint_visible(waypoint &wp_, bool visibility_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointvisible__array__bool__ret__nothing, wp_, visibility_);
        }

        void show_waypoint(waypoint &wp_, std::string &show_) {
            host::functions.invoke_raw_binary(__sqf::binary__showwaypoint__array__string__ret__nothing, wp_, show_);
        }

        void synchronize_waypoint(waypoint &wp_, const std::vector<waypoint> &others_) {
            auto_array<game_value> waypoints(others_.begin(), others_.end());

            host::functions.invoke_raw_binary(__sqf::binary__synchronizewaypoint__array__array__ret__nothing, wp_, std::move(waypoints));
        }
        void synchronize_waypoint(object &trigger_, const std::vector<waypoint> &others_) {
            auto_array<game_value> waypoints(others_.begin(), others_.end());

            host::functions.invoke_raw_binary(__sqf::binary__synchronizewaypoint__object__array__ret__nothing, trigger_, std::move(waypoints));
        }

        void waypoint_attach_object(waypoint &wp_, int obj_id_) {
            host::functions.invoke_raw_binary(__sqf::binary__waypointattachobject__array__object_scalar__ret__nothing, wp_, static_cast<float>(obj_id_));
        }

        void waypoint_attach_object(waypoint &wp_, object &obj_) {
            host::functions.invoke_raw_binary(__sqf::binary__waypointattachobject__array__object_scalar__ret__nothing, wp_, obj_);
        }

        void show_waypoints(bool enabled_) {
            host::functions.invoke_raw_unary(__sqf::unary__showwaypoints__bool__ret__nothing, enabled_);
        }

        bool waypoint_force_behaviour(const group &group_, int index_) {
            game_value params({group_,
                               static_cast<float>(index_)});

            return host::functions.invoke_raw_unary(__sqf::unary__waypointforcebehaviour__array__ret__bool, params);
        }

        void set_waypoint_force_behaviour(const group &group_, int index_, bool force_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointforcebehaviour__array__bool__ret__nothing, {group_, index_}, force_);
        }

        float waypoint_timeout_current(const group &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__waypointtimeoutcurrent__group__ret__scalar, value_);
        }

        bool waypoints_enabled_uav(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__waypointsenableduav__object__ret__bool, value_);
        }

        void enable_uavwaypoints(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableuavwaypoints__object__bool__ret__nothing, value0_, value1_);
        }

        void enable_uav_waypoints(object &uav_, bool enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableuavwaypoints__object__bool__ret__nothing, enable_, uav_);
        }

        void lock_wp(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const group>> target_, bool lock_) {
            game_value param_left;

            switch (target_.index()) {
                case 0: param_left = std::get<0>(target_).get(); break;
                case 1: param_left = std::get<1>(target_).get(); break;
            }

            host::functions.invoke_raw_binary(__sqf::binary__lockwp__object_group__bool__ret__nothing, param_left, lock_);
        }

        void set_wp_pos(const group &group_, int index_, const vector2 &position_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwppos__array__array__ret__nothing, {group_, index_}, position_);
        }

        vector3 get_wp_pos(const group &group_, int index_) {
            game_value params({group_,
                               static_cast<float>(index_)});

            return host::functions.invoke_raw_unary(__sqf::unary__getwppos__array__ret__array, params);
        }

        std::vector<waypoint> waypoints(const object &player_) {
            game_value res = host::functions.invoke_raw_unary(__sqf::unary__waypoints__object_group__ret__array, player_);
            return __helpers::__convert_to_vector<waypoint>(res);
        }

        std::vector<waypoint> waypoints(const group &group_) {
            game_value res = host::functions.invoke_raw_unary(__sqf::unary__waypoints__object_group__ret__array, group_);
            return __helpers::__convert_to_vector<waypoint>(res);
        }

        void set_effect_condition(std::variant<object, waypoint> unit_, sqf_string_const_ref statement_) {
            game_value param_left;
            switch (unit_.index()) {
                case 0: param_left = std::get<0>(unit_); break;
                case 1: param_left = std::get<1>(unit_); break;
            }

            host::functions.invoke_raw_binary(__sqf::binary__seteffectcondition__object_array__string__ret__nothing, param_left, statement_);
        }

        void waypoint_attach_vehicle(const waypoint &waypoint_, const object &vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__waypointattachvehicle__array__object__ret__nothing, {waypoint_.wgroup, waypoint_.windex}, vehicle_);
        }

        void create_guarded_point(const side &side_, const vector3 &pos_, float idstatic_, const object &veh_) {
            game_value params({side_,
                               pos_,
                               idstatic_,
                               veh_});

            host::functions.invoke_raw_unary(__sqf::unary__createguardedpoint__array__ret__nothing, params);
        }

        //Trigger

        rv_trigger_area trigger_area(const object &trigger_) {
            return rv_trigger_area(host::functions.invoke_raw_unary(__sqf::unary__triggerarea__object__ret__array, trigger_));
        }

        rv_trigger_timeout trigger_timeout(const object &trigger_) {
            return rv_trigger_timeout(host::functions.invoke_raw_unary(__sqf::unary__triggertimeout__object__ret__array, trigger_));
        }
        std::vector<object> list(const object &trigger_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__list__object__ret__array, trigger_));
        }
        void trigger_attach_object(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__triggerattachobject__object__scalar__ret__nothing, value0_, value1_);
        }
        void set_trigger_text(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__settriggertext__object__string__ret__nothing, value0_, value1_);
        }

        void set_trigger_type(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__settriggertype__object__string__ret__nothing, value0_, value1_);
        }
        bool trigger_activated(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__triggeractivated__object__ret__bool, value_);
        }

        object trigger_attached_vehicle(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__triggerattachedvehicle__object__ret__object, value_);
        }

        sqf_return_string trigger_text(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__triggertext__object__ret__string, value_);
        }

        float trigger_timeout_current(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__triggertimeoutcurrent__object__ret__scalar, value_);
        }

        sqf_return_string trigger_type(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__triggertype__object__ret__string, value_);
        }
        object create_trigger(sqf_string_const_ref type_, const vector3 &pos_, bool make_global_ /* = true*/) {
            game_value args({type_,
                             pos_,
                             make_global_});

            return object(host::functions.invoke_raw_unary(__sqf::unary__createtrigger__array__ret__object, args));
        }

        object create_trigger(sqf_string_const_ref type_, const object &pos_, bool make_global_ /*= true*/) {
            game_value args({type_,
                             pos_,
                             make_global_});

            return object(host::functions.invoke_raw_unary(__sqf::unary__createtrigger__array__ret__object, args));
        }

        void set_trigger_activation(const object &trigger_, sqf_string_const_ref by_, sqf_string_const_ref type_, bool repeating_) {
            host::functions.invoke_raw_binary(__sqf::binary__settriggeractivation__object__array__ret__nothing, trigger_, {by_, repeating_});
        }

        void set_trigger_area(const object &trigger_, float radius_x_, float radius_y_, float angle_, bool is_rectangle_, std::optional<float> radius_z_) {
            if (radius_z_.has_value())
                host::functions.invoke_raw_binary(__sqf::binary__settriggerarea__object__array__ret__nothing, trigger_, {radius_x_, radius_y_, angle_, is_rectangle_, *radius_z_});
            host::functions.invoke_raw_binary(__sqf::binary__settriggerarea__object__array__ret__nothing, trigger_, {radius_x_, radius_y_, angle_, is_rectangle_});
        }

        void set_trigger_statements(const object &trigger_, sqf_string_const_ref condition_, sqf_string_const_ref activation_, sqf_string_const_ref deactivation_) {
            host::functions.invoke_raw_binary(__sqf::binary__settriggerstatements__object__array__ret__nothing, trigger_, {condition_, activation_, deactivation_});
        }

        void set_trigger_timeout(const object &trigger_, float min_, float mid_, float max_, bool interruptable_) {
            host::functions.invoke_raw_binary(__sqf::binary__settriggertimeout__object__array__ret__nothing, trigger_, {min_, mid_, max_, interruptable_});
        }

        void synchronize_trigger(const object &trigger_, const std::vector<waypoint> &waypoints_) {
            auto_array<game_value> waypoints;
            for (auto &waypoint : waypoints_) waypoints.push_back({waypoint.wgroup, waypoint.windex});

            host::functions.invoke_raw_binary(__sqf::binary__synchronizetrigger__object__array__ret__nothing, trigger_, std::move(waypoints));
        }

        std::vector<object> synchronized_triggers(const waypoint &wp_) {
            const game_value ret = host::functions.invoke_raw_unary(__sqf::unary__synchronizedtriggers__array__ret__array, wp_);
            return __helpers::__convert_to_vector<object>(ret);
        }

        void trigger_attach_vehicle(const object &trigger_, const std::vector<object> &objects_) {
            host::functions.invoke_raw_binary(__sqf::binary__triggerattachvehicle__object__array__ret__nothing, trigger_, std::move(auto_array<game_value>(objects_.begin(), objects_.end())));
        }

        //both
        void set_music_effect(const object &trigger_, sqf_string_const_ref track_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmusiceffect__object_array__string__ret__nothing, trigger_, track_);
        }

        void set_music_effect(const group &group_, int index_, sqf_string_const_ref track_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmusiceffect__object_array__string__ret__nothing, {group_, index_}, track_);
        }

        void set_sound_effect(const object &trigger, sqf_string_const_ref sound_, sqf_string_const_ref voice_, sqf_string_const_ref sound_env_, sqf_string_const_ref sound_det_) {
            host::functions.invoke_raw_binary(__sqf::binary__setsoundeffect__object_array__array__ret__nothing, trigger, {sound_, voice_, sound_env_, sound_det_});
        }

        void set_sound_effect(const group &group, int index_, sqf_string_const_ref sound_, sqf_string_const_ref voice_, sqf_string_const_ref sound_env_, sqf_string_const_ref sound_det_) {
            host::functions.invoke_raw_binary(__sqf::binary__setsoundeffect__object_array__array__ret__nothing, {group, index_}, {sound_, voice_, sound_env_, sound_det_});
        }

        void set_title_effect(const object &trigger_, sqf_string_const_ref type_, sqf_string_const_ref effect_, sqf_string_const_ref text_) {
            host::functions.invoke_raw_binary(__sqf::binary__settitleeffect__object_array__array__ret__nothing, trigger_, {type_, effect_, text_});
        }

        void set_title_effect(const group &group_, int index_, sqf_string_const_ref type_, sqf_string_const_ref effect_, sqf_string_const_ref text_) {
            host::functions.invoke_raw_binary(__sqf::binary__settitleeffect__object_array__array__ret__nothing, {group_, index_}, {type_, effect_, text_});
        }

        vector3 custom_waypoint_position() {
            return __helpers::__retrieve_nular_vector3(__sqf::nular__customwaypointposition__ret__array);
        }

        void set_trigger_interval(const object &trigger_, float interval_) {
            host::functions.invoke_raw_binary(__sqf::binary__settriggerinterval__object__scalar__ret__nothing, trigger_, interval_);
        }

        void set_waypoint_loiter_altitude(waypoint wp_, float alt_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwaypointloiteraltitude__array__scalar__ret__nothing, wp_, alt_);
        }

        rv_trigger_activation trigger_activation(const object &trigger_) {
            return rv_trigger_activation(host::functions.invoke_raw_unary(__sqf::unary__triggeractivation__object__ret__array, trigger_));
        }

        float trigger_interval(const object &trigger_) {
            return host::functions.invoke_raw_unary(__sqf::unary__triggerinterval__object__ret__scalar, trigger_);
        }

        rv_trigger_statements trigger_statements(const object &trigger_) {
            return rv_trigger_statements(host::functions.invoke_raw_unary(__sqf::unary__triggerstatements__object__ret__array, trigger_));
        }

        float waypoint_loiter_altitude(const waypoint &wp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__waypointloiteraltitude__array__ret__scalar, wp_);
        }
    }  // namespace sqf
}  // namespace intercept
