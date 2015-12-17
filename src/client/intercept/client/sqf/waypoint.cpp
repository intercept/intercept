#include "waypoint.h"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
	namespace sqf {
		namespace waypoints {
			object waypoint_attached_object(waypoint &wp_)
			{
				return object(host::functions.invoke_raw_unary(client::__sqf::unary__waypointattachedobject__array__ret__object, wp_.__to_gv()));
			}

			object waypoint_attached_vehicle(waypoint & wp_)
			{
				return object(host::functions.invoke_raw_unary(client::__sqf::unary__waypointattachedvehicle__array__ret__object, wp_.__to_gv()));
			}

			waypoint::behaviour waypoint_behaviour(waypoint & wp_)
			{
				return waypoint::__parse_behaviour(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointbehaviour__array__ret__string, wp_.__to_gv())));
			}

			waypoint::combat_mode waypoint_combat_mode(waypoint & wp_)
			{
				return waypoint::__parse_combat_mode(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointcombatmode__array__ret__string, wp_.__to_gv())));
			}

			float waypoint_completeion_radius(waypoint & wp_)
			{
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointcompletionradius__array__ret__scalar, wp_.__to_gv()));
			}

			std::string waypoint_description(waypoint & wp_)
			{
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointdescription__array__ret__string, wp_.__to_gv()));
			}

			waypoint::formation waypoint_formation(waypoint & wp_)
			{
				return waypoint::__parse_formation( game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointformation__array__ret__string, wp_.__to_gv())) );
			}

			float waypoint_house_position(waypoint & wp_)
			{
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointhouseposition__array__ret__scalar, wp_.__to_gv()));
			}

			float waypoint_loiter_radius(waypoint & wp_)
			{
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointloiterradius__array__ret__scalar, wp_.__to_gv()));
			}

			waypoint::loiter_type waypoint_loiter_type(waypoint & wp_)
			{
				return waypoint::__parse_loiter_type(game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointloitertype__array__ret__string, wp_.__to_gv())));
			}

			std::string waypoint_name(waypoint & wp_)
			{
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointname__array__ret__string, wp_.__to_gv()));
			}
			vector3 waypoint_position(waypoint & wp_)
			{
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointposition__array__ret__array, wp_.__to_gv()));
			}
			std::vector<waypoint> waypoints(group & gp_)
			{
				// TODO return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypoints__object_group__ret__array, gp_));
				throw 713;
			}
			std::string waypoint_script(waypoint & wp_)
			{
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointscript__array__ret__string, wp_.__to_gv()));
			}
			waypoint::show waypoint_show(waypoint & wp_)
			{
				return waypoint::__parse_show( game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointshow__array__ret__string, wp_.__to_gv())) );
			}
			waypoint::speed waypoint_speed(waypoint & wp_)
			{
				return waypoint::__parse_speed( game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointspeed__array__ret__string, wp_.__to_gv())) );
			}
			waypoint::type waypoint_type(waypoint & wp_)
			{
				return waypoint::__parse_type( game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointtype__array__ret__string, wp_.__to_gv())) );
			}
			bool waypoint_visible(waypoint & wp_)
			{
				// TODO THIS CAN RETURN 0, CHECK FOR 0 AND RETURN FALSE.
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointvisible__array__ret__scalar, wp_.__to_gv()));
			}

			bool waypoint_exists(waypoint & wp_)
			{
				// TODO THIS CAN RETURN 0, CHECK FOR 0 AND RETURN FALSE.
				//if (game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointvisible__array__ret__scalar, wp_.__to_gv())).type == "number") return false;
				throw 713;
			}

			waypoint add_waypoint(group& gp_, vector3& center_, float radius_, int index_, const std::string& name_)
			{

			}


			float current_waypoint(group gp_) {
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__currentwaypoint__group__ret__scalar, gp_));
			}

			bool waypoints_enabled_uav(object value_) {
				return __helpers::__bool_unary_object(client::__sqf::unary__waypointsenableduav__object__ret__bool, value_);
			}

			void enable_uavwaypoints(bool value0_, object value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__enableuavwaypoints__object__bool__ret__nothing, value0_, value1_);
			}

			float waypoint_timeout_current(group value_) {
				return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__waypointtimeoutcurrent__group__ret__scalar, value_));
			}
		}
	}
}
