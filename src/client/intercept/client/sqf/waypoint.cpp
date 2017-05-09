#include "waypoint.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        const std::string waypoint::__speed_lookup[4] = { "UNCHANGED", "LIMITED", "NORMAL", "FULL" };
        const std::string waypoint::__show_lookup[4] = { "NEVER", "EASY", "ALWAYS", "ERROR" };
        const std::string waypoint::__type_lookup[22] = { "MOVE","DESTROY","GETIN","SAD","JOIN","LEADER","GETOUT","CYCLE","LOAD","UNLOAD","TR UNLOAD","HOLD","SENTRY","GUARD","TALK","SCRIPTED","SUPPORT","GETIN NEAREST","DISMISS","LOITER","AND","OR" };
        const std::string waypoint::__behaviour_lookup[6] = { "UNCHANGED", "CARELESS", "SAFE", "AWARE", "COMBAT", "STEALTH" };
        const std::string waypoint::__combat_mode_lookup[6] = { "NO CHANGE", "BLUE", "GREEN", "WHITE", "YELLOW", "RED" };
        const std::string waypoint::__formation_lookup[10] = { "NO_CHANGE","COLUMN","STAG_COLUMN","WEDGE","ECH_LEFT","ECH_RIGHT","VEE","LINE","FILE","DIAMOND" };
        const std::string waypoint::__loiter_lookup[2] = { "CIRCLE", "CIRCLE_L" };

        waypoint add_waypoint(group& gp_, const vector3& center_, float radius_, int index_, const std::string& name_) {
            game_value args({
                center_,
                radius_,
                static_cast<float>(index_),
                name_
            });

            return waypoint(game_value(host::functions.invoke_raw_binary(client::__sqf::binary__addwaypoint__group__array__ret__array, gp_, args)));
        }

        waypoint add_waypoint(group & gp_, const object & center_, float radius_, int index_, const std::string & name_) {
            game_value args({
                center_,
                radius_,
                static_cast<float>(index_),
                name_
            });

            return waypoint(game_value(host::functions.invoke_raw_binary(client::__sqf::binary__addwaypoint__group__array__ret__array, gp_, args)));
        }

        void delete_waypoint(waypoint & wp_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__deletewaypoint__array__ret__nothing, wp_.__to_gv());
        }

        void copy_waypoints(group & to_, group & from_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__copywaypoints__group__group__ret__nothing, to_, from_);
        }

        /* Waypoint */
        object waypoint_attached_object(waypoint &wp_) {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__waypointattachedobject__array__ret__object, wp_.__to_gv()));
        }

        object waypoint_attached_vehicle(waypoint & wp_) {
            return object(host::functions.invoke_raw_unary(client::__sqf::unary__waypointattachedvehicle__array__ret__object, wp_.__to_gv()));
        }

        waypoint::behaviour waypoint_behaviour(waypoint & wp_) {
            return waypoint::__parse_behaviour(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointbehaviour__array__ret__string, wp_.__to_gv())));
        }

        waypoint::combat_mode waypoint_combat_mode(waypoint & wp_) {
            return waypoint::__parse_combat_mode(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointcombatmode__array__ret__string, wp_.__to_gv())));
        }

        float waypoint_completeion_radius(waypoint & wp_) {
            return host::functions.invoke_raw_unary(client::__sqf::unary__waypointcompletionradius__array__ret__scalar, wp_.__to_gv());
        }

        std::string waypoint_description(waypoint & wp_) {
            return host::functions.invoke_raw_unary(client::__sqf::unary__waypointdescription__array__ret__string, wp_.__to_gv());
        }

        waypoint::formation waypoint_formation(waypoint & wp_) {
            return waypoint::__parse_formation(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointformation__array__ret__string, wp_.__to_gv())));
        }

        float waypoint_house_position(waypoint & wp_) {
            return host::functions.invoke_raw_unary(client::__sqf::unary__waypointhouseposition__array__ret__scalar, wp_.__to_gv());
        }

        float waypoint_loiter_radius(waypoint & wp_) {
            return host::functions.invoke_raw_unary(client::__sqf::unary__waypointloiterradius__array__ret__scalar, wp_.__to_gv());
        }

        waypoint::loiter_type waypoint_loiter_type(waypoint & wp_) {
            return waypoint::__parse_loiter_type(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointloitertype__array__ret__string, wp_.__to_gv())));
        }

        std::string waypoint_name(waypoint & wp_) {
            return host::functions.invoke_raw_unary(client::__sqf::unary__waypointname__array__ret__string, wp_.__to_gv());
        }
        vector3 waypoint_position(waypoint & wp_) {
            return host::functions.invoke_raw_unary(client::__sqf::unary__waypointposition__array__ret__array, wp_.__to_gv());
        }

        std::string waypoint_script(waypoint & wp_) {
            return host::functions.invoke_raw_unary(client::__sqf::unary__waypointscript__array__ret__string, wp_.__to_gv());
        }
        waypoint::show waypoint_show(waypoint & wp_) {
            return waypoint::__parse_show(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointshow__array__ret__string, wp_.__to_gv())));
        }
        waypoint::speed waypoint_speed(waypoint & wp_) {
            return waypoint::__parse_speed(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointspeed__array__ret__string, wp_.__to_gv())));
        }
        waypoint::type waypoint_type(waypoint & wp_) {
            return waypoint::__parse_type(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointtype__array__ret__string, wp_.__to_gv())));
        }
        bool waypoint_visible(waypoint & wp_) {
            // TODO THIS CAN RETURN 0, CHECK FOR 0 AND RETURN FALSE.
            return host::functions.invoke_raw_unary(client::__sqf::unary__waypointvisible__array__ret__scalar, wp_.__to_gv());
        }
        std::vector<waypoint> synchronized_waypoints(waypoint & wp_) {
            game_value rv_ret_vals(host::functions.invoke_raw_unary(client::__sqf::unary__synchronizedwaypoints__array__ret__array, wp_.__to_gv()));

            // TODO test for logic.
            std::vector<waypoint> waypoints;
            for (uint32_t i = 0; i < rv_ret_vals.length() - 1; i++)
                waypoints.push_back(waypoint(rv_ret_vals[i]));

            return waypoints;
        }
        std::vector<waypoint> synchronized_waypoints(object & obj_) {
            game_value rv_ret_vals(host::functions.invoke_raw_unary(client::__sqf::unary__synchronizedwaypoints__object__ret__array, obj_));

            // TODO test for logic.
            std::vector<waypoint> waypoints;
            for (uint32_t i = 0; i < rv_ret_vals.length() - 1; i++)
                waypoints.push_back(waypoint(rv_ret_vals[i]));

            return waypoints;
        }



        void set_waypoint_behaviour(waypoint & wp_, waypoint::behaviour mode_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointbehaviour__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(mode_));
        }
        void set_waypoint_combat_mode(waypoint & wp_, waypoint::combat_mode mode_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointcombatmode__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(mode_));
        }
        void set_waypoint_completion_radius(waypoint & wp_, float radius_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointcompletionradius__array__scalar__ret__nothing, wp_.__to_gv(), radius_);
        }
        void set_waypoint_description(waypoint & wp_, std::string & text_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointdescription__array__string__ret__nothing, wp_.__to_gv(), text_);
        }
        void set_waypoint_formation(waypoint & wp_, waypoint::formation formation_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointformation__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(formation_));
        }
        void set_waypoint_house_position(waypoint & wp_, float house_pos_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointhouseposition__array__scalar__ret__nothing, wp_.__to_gv(), house_pos_);
        }
        void set_waypoint_loiter_radius(waypoint & wp_, float radius_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointloiterradius__array__scalar__ret__nothing, wp_.__to_gv(), radius_);
        }
        void set_waypoint_loiter_type(waypoint & wp_, waypoint::loiter_type type_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointloitertype__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(type_));
        }
        void set_waypoint_name(waypoint & wp_, std::string & name_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointname__array__string__ret__nothing, wp_.__to_gv(), name_);
        }
        void set_waypoint_position(waypoint & wp_, vector3 & pos_, float radius_) {
            game_value args({ pos_, radius_ });
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointposition__array__array__ret__nothing, wp_.__to_gv(), args);
        }
        void set_waypoint_script(waypoint & wp_, std::string & command_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointscript__array__string__ret__nothing, wp_.__to_gv(), command_);
        }
        void set_waypoint_speed(waypoint& wp_, waypoint::speed mode_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointspeed__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(mode_));
        }
        void set_waypoint_statements(waypoint& wp_, std::string condition_, std::string statement_) {
            game_value args({ condition_, statement_ });
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointstatements__array__array__ret__nothing, wp_.__to_gv(), args);
        }
        void set_waypoint_timeout(waypoint& wp_, float min_, float mid_, float max_) {
            game_value args({
                game_value({
                    min_,
                    mid_,
                    max_
                })
            });
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointtimeout__array__array__ret__nothing, wp_.__to_gv(), args);
        }
        void set_waypoint_type(waypoint& wp_, waypoint::type type_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointtype__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(type_));
        }
        void set_waypoint_visible(waypoint& wp_, bool visibility_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointvisible__array__bool__ret__nothing, wp_.__to_gv(), visibility_);
        }

        void show_waypoint(waypoint& wp_, std::string & show_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__showwaypoint__array__string__ret__nothing, wp_.__to_gv(), show_);
        }

        void synchronize_waypoint(waypoint& wp_, const std::vector<waypoint> & others_) {
            std::vector<game_value> waypoints; //#TODO remove temp std::vector
            for (auto it : others_)
                waypoints.push_back(it.__to_gv());

            host::functions.invoke_raw_binary(client::__sqf::binary__synchronizewaypoint__array__array__ret__nothing, wp_.__to_gv(), waypoints);
        }
        void synchronize_waypoint(object& trigger_, const std::vector<waypoint> & others_) {
            std::vector<game_value> waypoints; //#TODO remove temp std::vector
            for (auto it : others_)
                waypoints.push_back(it.__to_gv());

            host::functions.invoke_raw_binary(client::__sqf::binary__synchronizewaypoint__object__array__ret__nothing, trigger_, waypoints);
        }

        void waypoint_attach_object(waypoint& wp_, int obj_id_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__waypointattachobject__array__object_scalar__ret__nothing, wp_.__to_gv(), static_cast<float>(obj_id_));
        }

        void waypoint_attach_object(waypoint& wp_, object & obj_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__waypointattachobject__array__object_scalar__ret__nothing, wp_.__to_gv(), obj_);
        }
    }
}