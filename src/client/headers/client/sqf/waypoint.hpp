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
#include "client/client.hpp"
#include "shared/types.hpp"
#include "shared/client_types.hpp"

using namespace intercept::types;
namespace intercept {
    namespace sqf {
        /* Waypoint */
        //#TODO change this to rv_waypoint
        class waypoint {
        public:
            group wgroup;
            float windex;

            waypoint(const group& rv_game_value, uint32_t windex)
                : wgroup(rv_game_value),
                windex(static_cast<float>(windex)) {}

            waypoint(const game_value& from_)
                : wgroup(group(from_[0])),
                windex(from_[1]) {}

            operator game_value() const {
                return{ wgroup, windex };
            }

            static const std::string __speed_lookup[4];
            enum class speed {
                UNCHANGED = 0,
                LIMITED = 1,
                NORMAL = 2,
                FULL = 3
            };
            static const std::string __show_lookup[4];
            enum class show {
                NEVER,
                EASY,
                ALWAYS,
                WAYPOINT_ERROR
            };
            static const std::string __type_lookup[22];
            enum class type {
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
            enum class behaviour {
                UNCHANGED,
                CARELESS,
                SAFE,
                AWARE,
                COMBAT,
                STEALTH
            };
            static const std::string __combat_mode_lookup[6];
            enum class combat_mode {
                NO_CHANGE,
                BLUE,
                GREEN,
                WHITE,
                YELLOW,
                RED

            };
            static const std::string __formation_lookup[10];
            enum class formation {
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
            enum class loiter_type {
                CIRCLE,
                CIRCLE_L
            };


            static speed __parse_speed(const std::string& subject_) {
                for (size_t i = 0; i < __speed_lookup->length(); i++) {
                    if (subject_ == __speed_lookup[i]) {
                        return static_cast<speed>(i);
                    }
                }
                throw 712;
            }
            static show __parse_show(const std::string& subject_) {
                for (size_t i = 0; i < __show_lookup->length(); i++) {
                    if (subject_ == __show_lookup[i]) {
                        return static_cast<show>(i);
                    }
                }
                throw 712;
            }
            static type __parse_type(const std::string& subject_) {
                for (size_t i = 0; i < __type_lookup->length(); i++) {
                    if (subject_ == __type_lookup[i]) {
                        return static_cast<type>(i);
                    }
                }
                throw 712;
            }
            static behaviour __parse_behaviour(const std::string& subject_) {
                for (size_t i = 0; i < __behaviour_lookup->length(); i++) {
                    if (subject_ == __behaviour_lookup[i]) {
                        return static_cast<behaviour>(i);
                    }
                }
                throw 712;
            }
            static combat_mode __parse_combat_mode(const std::string& subject_) {
                for (size_t i = 0; i < __combat_mode_lookup->length(); i++) {
                    if (subject_ == __combat_mode_lookup[i]) {
                        return static_cast<combat_mode>(i);
                    }
                }
                throw 712;
            }
            static formation __parse_formation(const std::string& subject_) {
                for (size_t i = 0; i < __formation_lookup->length(); i++) {
                    if (subject_ == __formation_lookup[i]) {
                        return static_cast<formation>(i);
                    }
                }
                throw 712;
            }
            static loiter_type __parse_loiter_type(const std::string& subject_) {
                for (size_t i = 0; i < __loiter_lookup->length(); i++) {
                    if (subject_ == __loiter_lookup[i]) {
                        return static_cast<loiter_type>(i);
                    }
                }
                throw 712;
            }

            static std::string __get_enum_as_str(speed subject_) {
                return __speed_lookup[static_cast<int>(subject_)];
            }
            static std::string __get_enum_as_str(show subject_) {
                return __show_lookup[static_cast<int>(subject_)];
            }
            static std::string __get_enum_as_str(type subject_) {
                return __type_lookup[static_cast<int>(subject_)];
            }
            static std::string __get_enum_as_str(behaviour subject_) {
                return __behaviour_lookup[static_cast<int>(subject_)];
            }
            static std::string __get_enum_as_str(combat_mode subject_) {
                return __combat_mode_lookup[static_cast<int>(subject_)];
            }
            static std::string __get_enum_as_str(formation subject_) {
                return __formation_lookup[static_cast<int>(subject_)];
            }
            static std::string __get_enum_as_str(loiter_type subject_) {
                return __loiter_lookup[static_cast<int>(subject_)];
            }

        };
        // It's ficking replaced at compile time anyway, why is this nessecary.................
        /*

        */
        /*!
        @brief Adds (or inserts when index is given) a new waypoint to a group.

        The waypoint is placed randomly within a circle with the given center and radius. The function returns the placed waypoint.

        @param gp_ The group to add the waypoint to.
        @param center_ The poition of the center of the waypoint placement radius.
        @param radius_ The radius of the waypoint placement area.
        @param index_ [OPTIONAL] The index of the waypoint to insert this waypoint after.
        @param name_ [OPTIONAL] The waypoint name

        @return Returns the placed waypoint.

        @sa https://community.bistudio.com/wiki/addWaypoint
        */
        waypoint add_waypoint(group & gp_, const vector3 & center_, float radius_, int index_ = -1, const std::string & name_ = "");

        /*!
        @brief Adds (or inserts when index is given) a new waypoint to a group.

        The waypoint is placed randomly within a circle with the given center and radius. The function returns the placed waypoint.

        @param gp_ The group to add the waypoint to.
        @param center_ An object to be the center of the waypoint placement radius.
        @param radius_ The radius of the waypoint placement area.
        @param index_ [OPTIONAL] The index of the waypoint to insert this waypoint after.
        @param name_ [OPTIONAL] The waypoint name

        @return Returns the placed waypoint.

        @sa         https://community.bistudio.com/wiki/addWaypoint
        */
        waypoint add_waypoint(group & gp_, const object & center_, float radius_, int index_ = -1, const std::string & name_ = "");

        /*!
        @brief  Removes the specified waypoint.

        @param  wp_ Waypoint to delete

        @sa https://community.bistudio.com/wiki/deleteWaypoint
        */
        void delete_waypoint(waypoint & wp_);


        void copy_waypoints(group & to_, group & from_);

        /************************************************  GETTERS   ************************************************/

        /*!
        @brief Gets the object attached to the waypoint.

        @param wp_ Waypoint to use

        @return Object attached to the waypoint, if any.
        */
        object waypoint_attached_object(waypoint& wp_);

        /*!
        @brief Gets the vehicle attached to the waypoint.

        @param wp_ Waypoint to use

        @return Vehicle attached to the waypoint, if any.

        @sa https://community.bistudio.com/wiki/waypointAttachedVehicle
        */
        object waypoint_attached_vehicle(waypoint & wp_);

        /*!
        @brief Gets the waypoint behavior.

        @param wp_ Waypoint to use

        @return Returns the behaviour of the waypoint.

        @sa waypoint::behaviour
        */
        waypoint::behaviour waypoint_behaviour(waypoint & wp_);

        /*!
        @brief Gets the waypoint combat mode.

        @param wp_ Waypoint to use

        @return Returns the combat mode of the waypoint.

        @sa waypoint::combat_mode
        @sa https://community.bistudio.com/wiki/2D_Editor:_Waypoints#Combat_Mode
        */
        waypoint::combat_mode waypoint_combat_mode(waypoint & wp_);

        /*!
        @brief Gets the radius around the waypoint where the waypoint is completed.

        @param wp_ Waypoint to use

        @return Returns the completeion radius of the waypoint.

        @sa https://community.bistudio.com/wiki/waypointCompletionRadius
        */
        float waypoint_completeion_radius(waypoint & wp_);

        /*!
        @brief Gets the waypoint description.

        @param wp_ Waypoint to use

        @return Returns the waypoint description

        @sa https://community.bistudio.com/wiki/waypointDescription
        */
        std::string waypoint_description(waypoint & wp_);

        /*!
        @brief Gets the waypoint description.

        @param wp_ Waypoint to use

        @return Returns the waypoint formation, enumeratred.

        @sa https://community.bistudio.com/wiki/waypointFormation
        */
        waypoint::formation waypoint_formation(waypoint & wp_);

        /*!
        @brief Gets the house position assigned to the waypoint.

        @param wp_ Waypoint to use

        @return Returns the house position.

        @sa https://community.bistudio.com/wiki/waypointHousePosition
        */
        float waypoint_house_position(waypoint & wp_);

        /*!
        @brief Gets the waypoint loiter radius.

        @param wp_ Waypoint to use

        @return Returns the loiter radius.

        @sa https://community.bistudio.com/wiki/waypointLoiterRadius
        */
        float waypoint_loiter_radius(waypoint & wp_);

        /*!
        @brief Gets the waypoint loiter type.

        @param wp_ Waypoint to use

        @return Returns the loiter type, enumerated.

        @sa https://community.bistudio.com/wiki/waypointLoiterType
        */
        waypoint::loiter_type waypoint_loiter_type(waypoint & wp_);

        /*!
        @brief Gets the waypoint name.

        @param wp_ Waypoint to use

        @return The name assigned to the waypoint.

        @sa https://community.bistudio.com/wiki/waypointName
        */
        std::string waypoint_name(waypoint & wp_);

        /*!
        @brief Get Waypoint's Position.

        @param wp_ Waypoint to use

        @return The position of the waypoint.

        @sa https://community.bistudio.com/wiki/waypointPosition
        */
        vector3 waypoint_position(waypoint & wp_);

        /*!
        @brief Gets the waypoint script.

        @param wp_ Waypoint to use

        @return The position of the waypoint.

        @sa https://community.bistudio.com/wiki/waypointScript
        */
        std::string waypoint_script(waypoint & wp_);

        /*!
        @brief Gets the waypoint show/hide status.

        @param wp_ Waypoint to use

        @return Gets the showhide status, enumerated.

        @sa https://community.bistudio.com/wiki/waypointShow
        */
        waypoint::show waypoint_show(waypoint & wp_);

        /*!
        @brief Gets the waypoint movement speed.

        @param wp_ Waypoint to use

        @return Gets the waypoint speed, enumerated.

        @sa https://community.bistudio.com/wiki/waypointSpeed
        */
        waypoint::speed waypoint_speed(waypoint & wp_);
        // TODO waypoint_statements needs struct for return value
        // TODO waypoint_timeout needs struct for return value

        /*!
        @brief Gets the waypoint type.

        @param wp_ Waypoint to use

        @return The waypoint type, enumerated.

        @sa https://community.bistudio.com/wiki/waypointType
        */
        waypoint::type waypoint_type(waypoint & wp_);

        /*!
        @brief Returns the visibility of the waypoint.

        @param wp_ Waypoint to use

        @return The waypoint visibility.

        @sa https://community.bistudio.com/wiki/waypointVisible
        */
        bool waypoint_visible(waypoint & wp_);

        std::vector<waypoint> synchronized_waypoints(waypoint & wp_);
        std::vector<waypoint> synchronized_waypoints(object & obj_);

        void set_waypoint_behaviour(waypoint & wp_, waypoint::behaviour mode_);
        void set_waypoint_combat_mode(waypoint & wp_, waypoint::combat_mode mode_);
        void set_waypoint_completion_radius(waypoint & wp_, float radius_);
        void set_waypoint_description(waypoint & wp_, std::string & text_);
        void set_waypoint_formation(waypoint & wp_, waypoint::formation formation_);
        void set_waypoint_house_position(waypoint & wp_, float house_pos_);
        void set_waypoint_loiter_radius(waypoint & wp_, float radius_);
        void set_waypoint_loiter_type(waypoint & wp_, waypoint::loiter_type type_);
        void set_waypoint_name(waypoint & wp_, std::string & name_);
        void set_waypoint_position(waypoint & wp_, vector3 & pos_, float radius_);
        void set_waypoint_script(waypoint & wp_, std::string & command_);
        void set_waypoint_speed(waypoint& wp_, waypoint::speed mode_);
        void set_waypoint_statements(waypoint& wp_, std::string condition_, std::string statement_);
        void set_waypoint_timeout(waypoint& wp_, float min_, float mid_, float max_);
        void set_waypoint_type(waypoint& wp_, waypoint::type type_);
        void set_waypoint_visible(waypoint& wp_, bool visibility_);

        void show_waypoint(waypoint& wp_, std::string & show_);

        void synchronize_waypoint(waypoint& wp_, const std::vector<waypoint> & others_);
        void synchronize_waypoint(object& trigger_, const std::vector<waypoint> & others_);

        void waypoint_attach_object(waypoint& wp_, int obj_id_);
        void waypoint_attach_object(waypoint& wp_, object & obj_);

        void show_waypoints(bool enabled_);
        bool waypoint_force_behaviour(const group &group_, int index_);
        void set_waypoint_force_behaviour(const group &group_, int index_, bool force_);
        float waypoint_timeout_current(const group &value_);
        bool waypoints_enabled_uav(const object &value_);
        void enable_uav_waypoints(object & uav_, bool enable_);


        void set_wp_pos(const group &group_, int index_, const vector2 &position_);
        vector3 get_wp_pos(const group &group_, int index_);
        void lock_wp(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const group>> target_, bool lock_);

    }
}
