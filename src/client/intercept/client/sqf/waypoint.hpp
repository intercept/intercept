/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Wrappers for the waypoint family of commands.

This file contains all the wrappers for the Waypoint family of commands and
associated structs and enumerations.

https://github.com/NouberNou/intercept
*/
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

			waypoint( const group& rv_game_value, uint32_t windex)
				: wgroup(rv_game_value),
				  windex((float)windex)
			{
			}

			waypoint(const game_value& rv_game_value)
				: wgroup(group(rv_game_value[0].rv_data)),
				windex(rv_game_value[1])
			{
			}

			std::vector<game_value> __to_gv_vec()
			{
				return std::vector<game_value>{wgroup, game_value(windex)};
			}

			game_value __to_gv()
			{
				return game_value(std::vector<game_value>{ wgroup, windex });
			}

			static const std::string __speed_lookup[4];
			enum class speed
			{
				UNCHANGED = 0,
				LIMITED = 1,
				NORMAL = 2,
				FULL = 3
			};
			static const std::string __show_lookup[4];
			enum class show
			{
				NEVER,
				EASY,
				ALWAYS,
				WAYPOINT_ERROR
			};
			static const std::string __type_lookup[22];
			enum class type
			{
				MOVE,
				DESTROY,
				GETIN,
				SAD,
				JOIN,
				LEADER,
				GETOUT,
				CYCLE,
				LOAD,
				UNLOAD,
				TR_UNLOAD,
				HOLD,
				SENTRY,
				GUARD,
				TALK,
				SCRIPTED,
				SUPPORT,
				GETIN_NEAREST,
				DISMISS,
				LOITER,
				AND,
				OR
			};
			static const std::string __behaviour_lookup[6];
			enum class behaviour
			{
				UNCHANGED,
				CARELESS,
				SAFE,
				AWARE,
				COMBAT,
				STEALTH
			};
			static const std::string __combat_mode_lookup[6];
			enum class combat_mode
			{
				NO_CHANGE,
				BLUE,
				GREEN,
				WHITE,
				YELLOW,
				RED

			};
			static const std::string __formation_lookup[10];
			enum class formation
			{
				NO_CHANGE,
				COLUMN,
				STAG_COLUMN,
				WEDGE,
				ECH_LEFT,
				ECH_RIGHT,
				VEE,
				LINE,
				FILE,
				DIAMOND
			};
			static const std::string __loiter_lookup[2];
			enum class loiter_type
			{
				CIRCLE,
				CIRCLE_L
			};


			static speed __parse_speed(const std::string& subject_)
			{
				for (size_t i = 0; i < __speed_lookup->length(); i++)
				{
					if (subject_ == __speed_lookup[i])
					{
						return static_cast<speed>(i);
					}
				}
				throw 712;
			}
			static show __parse_show(const std::string& subject_)
			{
				for (size_t i = 0; i < __show_lookup->length(); i++)
				{
					if (subject_ == __show_lookup[i])
					{
						return static_cast<show>(i);
					}
				}
				throw 712;
			}
			static type __parse_type(const std::string& subject_)
			{
				for (size_t i = 0; i < __type_lookup->length(); i++)
				{
					if (subject_ == __type_lookup[i])
					{
						return static_cast<type>(i);
					}
				}
				throw 712;
			}
			static behaviour __parse_behaviour(const std::string& subject_)
			{
				for (size_t i = 0; i < __behaviour_lookup->length(); i++)
				{
					if (subject_ == __behaviour_lookup[i])
					{
						return static_cast<behaviour>(i);
					}
				}
				throw 712;
			}
			static combat_mode __parse_combat_mode(const std::string& subject_)
			{
				for (size_t i = 0; i < __combat_mode_lookup->length(); i++)
				{
					if (subject_ == __combat_mode_lookup[i])
					{
						return static_cast<combat_mode>(i);
					}
				}
				throw 712;
			}
			static formation __parse_formation(const std::string& subject_)
			{
				for (size_t i = 0; i < __formation_lookup->length(); i++)
				{
					if (subject_ == __formation_lookup[i])
					{
						return static_cast<formation>(i);
					}
				}
				throw 712;
			}
			static loiter_type __parse_loiter_type(const std::string& subject_)
			{
				for (size_t i = 0; i < __loiter_lookup->length(); i++)
				{
					if (subject_ == __loiter_lookup[i])
					{
						return static_cast<loiter_type>(i);
					}
				}
				throw 712;
			}

			static std::string __get_enum_as_str(speed subject_)
			{
				return __speed_lookup[(int)subject_];
			}
			static std::string __get_enum_as_str(show subject_)
			{
				return __show_lookup[(int)subject_];
			}
			static std::string __get_enum_as_str(type subject_)
			{
				return __type_lookup[(int)subject_];
			}
			static std::string __get_enum_as_str(behaviour subject_)
			{
				return __behaviour_lookup[(int)subject_];
			}
			static std::string __get_enum_as_str(combat_mode subject_)
			{
				return __combat_mode_lookup[(int)subject_];
			}
			static std::string __get_enum_as_str(formation subject_)
			{
				return __formation_lookup[(int)subject_];
			}
			static std::string __get_enum_as_str(loiter_type subject_)
			{
				return __loiter_lookup[(int)subject_];
			}

		};
		// It's ficking replaced at compile time anyway, why is this nessecary.................
		const std::string waypoint::__speed_lookup[4] = { "UNCHANGED", "LIMITED", "NORMAL", "FULL" };
		const std::string waypoint::__show_lookup[4] = { "NEVER", "EASY", "ALWAYS", "ERROR" };
		const std::string waypoint::__type_lookup[22] = { "MOVE","DESTROY","GETIN","SAD","JOIN","LEADER","GETOUT","CYCLE","LOAD","UNLOAD","TR UNLOAD","HOLD","SENTRY","GUARD","TALK","SCRIPTED","SUPPORT","GETIN NEAREST","DISMISS","LOITER","AND","OR" };
		const std::string waypoint::__behaviour_lookup[6] = { "UNCHANGED", "CARELESS", "SAFE", "AWARE", "COMBAT", "STEALTH" };
		const std::string waypoint::__combat_mode_lookup[6] = { "NO CHANGE", "BLUE", "GREEN", "WHITE", "YELLOW", "RED" };
		const std::string waypoint::__formation_lookup[10] = { "NO_CHANGE","COLUMN","STAG_COLUMN","WEDGE","ECH_LEFT","ECH_RIGHT","VEE","LINE","FILE","DIAMOND" };
		const std::string waypoint::__loiter_lookup[2] = { "CIRCLE", "CIRCLE_L" };

		/*!
		 * @namespace waypoints
		 * @brief The namespace housing the Waypoint family of commands.
		 */
		namespace waypoints {
			/*!
			 * @brief  Gets the object attached to the waypoint.
		     * @method waypoint_attached_object
			 * @param  wp_                      Waypoint to use
			 * @return                          Object attached to the waypoint, if any.
			 */
			object waypoint_attached_object(waypoint& wp_);

			/*!
			 * @brief  Gets the vehicle attached to the waypoint.
			 * @method waypoint_attached_vehicle
			 * @param  wp_                      Waypoint to use
			 * @return                          Vehicle attached to the waypoint, if any.
			 */
			object waypoint_attached_vehicle(waypoint & wp_);

			/*!
			 * @brief  	Gets the waypoint behavior.
			 * @method 	waypoint_behaviour
			 * @param  	wp_                     	 	Waypoint to use
			 * @return                          		Returns the behaviour of the waypoint.
			 * @sa		waypoint::behaviour
			 */
			waypoint::behaviour waypoint_behaviour(waypoint & wp_);

			/*!
			 * @brief  	Gets the waypoint combat mode.
			 * @method 	waypoint_combat_mode
			 * @param  	wp_                     	 	Waypoint to use
			 * @return                          		Returns the combat mode of the waypoint.
			 * @sa		waypoint::combat_mode
			 * @sa 		<a href="linkURL">https://community.bistudio.com/wiki/2D_Editor:_Waypoints#Combat_Mode</a>
			 */
			waypoint::combat_mode waypoint_combat_mode(waypoint & wp_);

			/*!
			 * @brief  	Gets the radius around the waypoint where the waypoint is completed.
			 * @method 	waypoint_completeion_radius
			 * @param  	wp_                     	 	Waypoint to use
			 * @return                          		Returns the completeion radius of the waypoint.
			 * @sa 		<a href="linkURL">https://community.bistudio.com/wiki/waypointCompletionRadius</a>
			 */
			float waypoint_completeion_radius(waypoint & wp_);

			/*!
			 * @brief  	Gets the waypoint description.
			 * @method 	waypoint_description
			 * @param  	wp_                     	 	Waypoint to use
			 * @return                          		Returns the waypoint description
			 * @sa 		<a href="linkURL">https://community.bistudio.com/wiki/waypointDescription</a>
			 */
			std::string waypoint_description(waypoint & wp_);

			/*!
			 * @brief  	Gets the waypoint description.
			 * @method 	waypoint_formation
			 * @param  	wp_                     	 	Waypoint to use
			 * @return                          		Returns the waypoint formation, enumeratred.
			 * @sa 		<a href="linkURL">https://community.bistudio.com/wiki/waypointFormation</a>
			 */
			waypoint::formation waypoint_formation(waypoint & wp_);
			float waypoint_house_position(waypoint & wp_);
			float waypoint_loiter_radius(waypoint & wp_);
			waypoint::loiter_type waypoint_loiter_type(waypoint & wp_);
			std::string waypoint_name(waypoint & wp_);
			vector3 waypoint_position(waypoint & wp_);
			std::vector<waypoint> waypoints( group & gp_);
			std::string waypoint_script(waypoint & wp_);
			waypoint::show waypoint_show(waypoint & wp_);
			waypoint::speed waypoint_speed(waypoint & wp_);
			// TODO waypoint_statements needs struct for return value
			// TODO waypoint_timeout needs struct for return value
			waypoint::type waypoint_type(waypoint & wp_); // TODO enumerate waypoint_type return
			bool waypoint_visible(waypoint & wp_);

			bool waypoint_exists(waypoint & wp_); // NOTE Not SQF command.

			waypoint add_waypoint(group & gp_, const vector3 & center_, float radius_, int index_, const std::string & name_);
			waypoint add_waypoint(group & gp_, const object & center_, float radius_, int index_, const std::string & name_);
			void delete_waypoint(waypoint & wp_);
			void copy_waypoints(group & to_, group & from_);

			std::vector<waypoint> synchronized_waypoints(waypoint & wp_);
			std::vector<waypoint> synchronized_waypoints(object & obj_);

			void set_current_waypoint(group & gp_, waypoint & wp_);
			void set_waypoint_behaviour(waypoint & wp_, waypoint::behaviour mode_);
			void set_waypoint_combat_mode(waypoint & wp_, waypoint::combat_mode mode_);
			void set_waypoint_completion_radius(waypoint & wp_, float radius_);
			void set_waypoint_description(waypoint & wp_, std::string text_);
			void set_waypoint_formation(waypoint & wp_, waypoint::formation formation_);
			void set_waypoint_house_position(waypoint & wp_, float house_pos_);
			void set_waypoint_loiter_radius(waypoint & wp_, float radius_);
			void set_waypoint_loiter_type(waypoint & wp_, waypoint::loiter_type type_);
			void set_waypoint_name(waypoint & wp_, std::string name_);
			void set_waypoint_position(waypoint & wp_, vector3 & pos_, float radius_);
			void set_waypoint_script(waypoint & wp_, std::string command_);
			void set_waypoint_speed(waypoint& wp_, waypoint::speed mode_);
			void set_waypoint_statements(waypoint& wp_, std::string condition_, std::string statement_);
			void set_waypoint_timeout(waypoint& wp_, float min_, float mid_, float max_);
			void set_waypoint_type(waypoint& wp_, waypoint::type type_);
			void set_waypoint_visible(waypoint& wp_, bool visibility_);

			void show_waypoint(waypoint& wp_, std::string show_);

			void synchronize_waypoint(waypoint& wp_, std::vector<waypoint> others_);
			void synchronize_waypoint(object& trigger_, std::vector<waypoint> others_);

			void waypoint_attach_object(waypoint& wp_, int obj_id_);
			void waypoint_attach_object(waypoint& wp_, object obj_);

			float current_waypoint(group gp_);
			bool waypoints_enabled_uav(object value_);
			void enable_uavwaypoints(bool value0_, object value1_);
			float waypoint_timeout_current(group value_);

			// TODO Does `unary__curatorwaypointcost__object__ret__scalar` and `binary__setcuratorwaypointcost__object__scalar__ret__nothing` belong in curator namespace or waypoint namespace.
		}
	}
}
