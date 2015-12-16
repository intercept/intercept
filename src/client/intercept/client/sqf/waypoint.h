#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\types.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;
namespace intercept {
	namespace sqf {

		struct waypoint
		{
			group wgroup;
			float windex;

			waypoint(const group& rv_game_value, uint32_t windex)
				: wgroup(rv_game_value),
				  windex((float)windex)
			{
			}
		};

		namespace waypoints {
			/* potential namespace: waypoint, waypoints */
			object waypoint_attached_object(waypoint wp_);
			object waypoint_attached_vehicle(waypoint wp_);

			std::string waypoint_behaviour(waypoint wp_);
			std::string waypoint_combat_mode(waypoint wp_);
			float waypoint_completeion_radius(waypoint wp_);
			std::string waypoint_description(waypoint wp_);
			std::string waypoint_formation(waypoint wp_);
			float waypoint_house_position(waypoint wp_);
			float waypoint_loiter_radius(waypoint wp_);
			std::string waypoint_loiter_type(waypoint wp_);
			std::string waypoint_name(waypoint wp_);
			vector3 waypoint_position(waypoint wp_);
			std::vector<waypoint> waypoints(group gp_);
			std::string waypoint_script(waypoint wp_); 
			std::string waypoint_show(waypoint wp_); // TODO enumerate waypoint_show return
			std::string waypoint_speed(waypoint wp_); // TODO enumerate waypoint_speed return
			// TODO waypoint_statements needs struct for return value
			// TODO waypoint_timeout needs struct for return value
			std::string waypoint_type(waypoint wp_); // TODO enumerate waypoint_type return
			bool waypoint_visible(waypoint wp_);

			bool waypoint_exists(waypoint wp_); // NOTE Not SQF command.
			//binary__waypointattachobject__array__object_scalar__ret__nothing
			//	binary__waypointattachvehicle__array__object__ret__nothing

		}
	}
}