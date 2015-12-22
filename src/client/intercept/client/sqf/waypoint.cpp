#include "waypoint.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
	namespace sqf {
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

		waypoint add_waypoint(group& gp_, const vector3& center_, float radius_, int index_, const std::string& name_)
		{
			game_value args({ 
                center_, 
                radius_, 
                (float)index_, 
                name_ 
            });

			return waypoint(game_value(host::functions.invoke_raw_binary(client::__sqf::binary__addwaypoint__group__array__ret__array, gp_, args)));
		}

		waypoint add_waypoint(group & gp_, const object & center_, float radius_, int index_, const std::string & name_)
		{
			game_value args({ 
                center_, 
                radius_, 
                (float)index_, 
                name_ 
            });
				
			return waypoint(game_value(host::functions.invoke_raw_binary(client::__sqf::binary__addwaypoint__group__array__ret__array, gp_, args)));
		}

		void delete_waypoint(waypoint & wp_)
		{
			host::functions.invoke_raw_unary(client::__sqf::unary__deletewaypoint__array__ret__nothing, wp_.__to_gv());
		}

		void copy_waypoints(group & to_, group & from_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__copywaypoints__group__group__ret__nothing, to_, from_);
		}

		std::vector<waypoint> synchronized_waypoints(waypoint & wp_)
		{
			game_value rv_ret_vals(host::functions.invoke_raw_unary(client::__sqf::unary__synchronizedwaypoints__array__ret__array, wp_.__to_gv()));
				
			// TODO test for logic.
			std::vector<waypoint> waypoints;
			for (uint32_t i = 0; i < rv_ret_vals.length() - 1; i++)
				waypoints.push_back(waypoint(rv_ret_vals[i]));

            return waypoints;
		}
		std::vector<waypoint> synchronized_waypoints(object & obj_)
		{
			game_value rv_ret_vals(host::functions.invoke_raw_unary(client::__sqf::unary__synchronizedwaypoints__object__ret__array, obj_));

			// TODO test for logic.
			std::vector<waypoint> waypoints;
			for (uint32_t i = 0; i < rv_ret_vals.length() - 1; i++)
				waypoints.push_back(waypoint(rv_ret_vals[i]));

            return waypoints;
		}

		void set_current_waypoint(group & gp_, waypoint & wp_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setcurrentwaypoint__group__array__ret__nothing, gp_, wp_.__to_gv());
		}

		void set_waypoint_behaviour(waypoint & wp_, waypoint::behaviour mode_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointbehaviour__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(mode_));
		}
		void set_waypoint_combat_mode(waypoint & wp_, waypoint::combat_mode mode_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointcombatmode__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(mode_));
		}
		void set_waypoint_completion_radius(waypoint & wp_, float radius_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointcompletionradius__array__scalar__ret__nothing, wp_.__to_gv(), radius_);
		}
		void set_waypoint_description(waypoint & wp_, std::string text_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointdescription__array__string__ret__nothing, wp_.__to_gv(), text_);
		}
		void set_waypoint_formation(waypoint & wp_, waypoint::formation formation_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointformation__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(formation_));
		}
		void set_waypoint_house_position(waypoint & wp_, float house_pos_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointhouseposition__array__scalar__ret__nothing, wp_.__to_gv(), house_pos_);
		}
		void set_waypoint_loiter_radius(waypoint & wp_, float radius_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointloiterradius__array__scalar__ret__nothing, wp_.__to_gv(), radius_);
		}
		void set_waypoint_loiter_type(waypoint & wp_, waypoint::loiter_type type_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointloitertype__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(type_));
		}
		void set_waypoint_name(waypoint & wp_, std::string name_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointname__array__string__ret__nothing, wp_.__to_gv(), name_);
		}
		void set_waypoint_position(waypoint & wp_, vector3 & pos_, float radius_)
		{
			game_value args({ pos_, radius_});
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointposition__array__array__ret__nothing, wp_.__to_gv(), args);
		}
		void set_waypoint_script(waypoint & wp_, std::string command_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointscript__array__string__ret__nothing, wp_.__to_gv(), command_);
		}
		void set_waypoint_speed(waypoint& wp_, waypoint::speed mode_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointspeed__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(mode_));
		}
		void set_waypoint_statements(waypoint& wp_, std::string condition_, std::string statement_)
		{
			game_value args({ condition_, statement_ });
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointstatements__array__array__ret__nothing, wp_.__to_gv(), args);
		}
		void set_waypoint_timeout(waypoint& wp_, float min_, float mid_, float max_)
		{
			game_value args({ std::vector<game_value> { min_, mid_, max_ } });
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointtimeout__array__array__ret__nothing, wp_.__to_gv(), args);
		}
		void set_waypoint_type(waypoint& wp_, waypoint::type type_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointtype__array__string__ret__nothing, wp_.__to_gv(), waypoint::__get_enum_as_str(type_));
		}
		void set_waypoint_visible(waypoint& wp_, bool visibility_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__setwaypointvisible__array__bool__ret__nothing, wp_.__to_gv(), visibility_);
		}

		void show_waypoint(waypoint& wp_, std::string show_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__showwaypoint__array__string__ret__nothing, wp_.__to_gv(), show_);
		}

		void synchronize_waypoint(waypoint& wp_, std::vector<waypoint> others_)
		{
			std::vector<game_value> waypoints;
			for (auto it : others_)
				waypoints.push_back(it.__to_gv());

			host::functions.invoke_raw_binary(client::__sqf::binary__synchronizewaypoint__array__array__ret__nothing, wp_.__to_gv(), waypoints);
		}
		void synchronize_waypoint(object& trigger_, std::vector<waypoint> others_)
		{
			std::vector<game_value> waypoints;
			for (auto it : others_)
				waypoints.push_back(it.__to_gv());

			host::functions.invoke_raw_binary(client::__sqf::binary__synchronizewaypoint__object__array__ret__nothing, trigger_, waypoints);
		}

		void waypoint_attach_object(waypoint& wp_, int obj_id_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__waypointattachobject__array__object_scalar__ret__nothing, wp_.__to_gv(), (float)obj_id_);
		}

		void waypoint_attach_object(waypoint& wp_, object obj_)
		{
			host::functions.invoke_raw_binary(client::__sqf::binary__waypointattachobject__array__object_scalar__ret__nothing, wp_.__to_gv(), obj_);
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
