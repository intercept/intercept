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
#include <utility>
#include "shared/types.hpp"
#include "shared/client_types.hpp"

using namespace intercept::types;
namespace intercept {
    namespace sqf {
        /* Waypoint */
        class waypoint {
        public:
            group wgroup;
            float windex;

            waypoint(group rv_game_value, uint32_t windex)
                : wgroup(std::move(rv_game_value)),
                  windex(static_cast<float>(windex)) {}

            waypoint(const game_value &from_)
                : wgroup(group(from_[0])),
                  windex(from_[1]) {}

            operator game_value() const {
                return {static_cast<game_value>(wgroup), windex};
            }

            static const std::string_view __speed_lookup[4];
            enum class speed {
                UNCHANGED = 0,
                LIMITED = 1,
                NORMAL = 2,
                FULL = 3
            };
            static const std::string_view __show_lookup[4];
            enum class show {
                NEVER,
                EASY,
                ALWAYS,
                WAYPOINT_ERROR
            };
            static const std::string_view __type_lookup[22];
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
            static const std::string_view __behaviour_lookup[6];
            enum class behaviour {
                UNCHANGED,
                CARELESS,
                SAFE,
                AWARE,
                COMBAT,
                STEALTH
            };
            static const std::string_view __combat_mode_lookup[6];
            enum class combat_mode {
                NO_CHANGE,
                BLUE,
                GREEN,
                WHITE,
                YELLOW,
                RED

            };
            static const std::string_view __formation_lookup[10];
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
            static const std::string_view __loiter_lookup[2];
            enum class loiter_type {
                CIRCLE,
                CIRCLE_L
            };

            static speed __parse_speed(sqf_string_const_ref subject_) {
                for (size_t i = 0; i < __speed_lookup->length(); i++) {
                    if (subject_ == __speed_lookup[i]) {
                        return static_cast<speed>(i);
                    }
                }
                throw 712;
            }
            static show __parse_show(sqf_string_const_ref subject_) {
                for (size_t i = 0; i < __show_lookup->length(); i++) {
                    if (subject_ == __show_lookup[i]) {
                        return static_cast<show>(i);
                    }
                }
                throw 712;
            }
            static type __parse_type(sqf_string_const_ref subject_) {
                for (size_t i = 0; i < __type_lookup->length(); i++) {
                    if (subject_ == __type_lookup[i]) {
                        return static_cast<type>(i);
                    }
                }
                throw 712;
            }
            static behaviour __parse_behaviour(sqf_string_const_ref subject_) {
                for (size_t i = 0; i < __behaviour_lookup->length(); i++) {
                    if (subject_ == __behaviour_lookup[i]) {
                        return static_cast<behaviour>(i);
                    }
                }
                throw 712;
            }
            static combat_mode __parse_combat_mode(sqf_string_const_ref subject_) {
                for (size_t i = 0; i < __combat_mode_lookup->length(); i++) {
                    if (subject_ == __combat_mode_lookup[i]) {
                        return static_cast<combat_mode>(i);
                    }
                }
                throw 712;
            }
            static formation __parse_formation(sqf_string_const_ref subject_) {
                for (size_t i = 0; i < __formation_lookup->length(); i++) {
                    if (subject_ == __formation_lookup[i]) {
                        return static_cast<formation>(i);
                    }
                }
                throw 712;
            }
            static loiter_type __parse_loiter_type(sqf_string_const_ref subject_) {
                for (size_t i = 0; i < __loiter_lookup->length(); i++) {
                    if (subject_ == __loiter_lookup[i]) {
                        return static_cast<loiter_type>(i);
                    }
                }
                throw 712;
            }

            static std::string_view __get_enum_as_str(speed subject_) {
                return __speed_lookup[static_cast<int>(subject_)];
            }
            static std::string_view __get_enum_as_str(show subject_) {
                return __show_lookup[static_cast<int>(subject_)];
            }
            static std::string_view __get_enum_as_str(type subject_) {
                return __type_lookup[static_cast<int>(subject_)];
            }
            static std::string_view __get_enum_as_str(behaviour subject_) {
                return __behaviour_lookup[static_cast<int>(subject_)];
            }
            static std::string_view __get_enum_as_str(combat_mode subject_) {
                return __combat_mode_lookup[static_cast<int>(subject_)];
            }
            static std::string_view __get_enum_as_str(formation subject_) {
                return __formation_lookup[static_cast<int>(subject_)];
            }
            static std::string_view __get_enum_as_str(loiter_type subject_) {
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
        waypoint add_waypoint(group &gp_, const vector3 &center_, float radius_, int index_ = -1, sqf_string_const_ref name_ = "");

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
        waypoint add_waypoint(group &gp_, const object &center_, float radius_, int index_ = -1, sqf_string_const_ref name_ = "");

        /*!
        @brief  Removes the specified waypoint.

        @param  wp_ Waypoint to delete

        @sa https://community.bistudio.com/wiki/deleteWaypoint
        */
        void delete_waypoint(waypoint &wp_);

        void copy_waypoints(group &to_, group &from_);

        /************************************************  GETTERS   ************************************************/

        /*!
        @brief Gets the object attached to the waypoint.

        @param wp_ Waypoint to use

        @return Object attached to the waypoint, if any.
        */
        object waypoint_attached_object(waypoint &wp_);

        /*!
        @brief Gets the vehicle attached to the waypoint.

        @param wp_ Waypoint to use

        @return Vehicle attached to the waypoint, if any.

        @sa https://community.bistudio.com/wiki/waypointAttachedVehicle
        */
        object waypoint_attached_vehicle(waypoint &wp_);

        /*!
        @brief Gets the waypoint behavior.

        @param wp_ Waypoint to use

        @return Returns the behaviour of the waypoint.

        @sa waypoint::behaviour
        */
        waypoint::behaviour waypoint_behaviour(waypoint &wp_);

        /*!
        @brief Gets the waypoint combat mode.

        @param wp_ Waypoint to use

        @return Returns the combat mode of the waypoint.

        @sa waypoint::combat_mode
        @sa https://community.bistudio.com/wiki/2D_Editor:_Waypoints#Combat_Mode
        */
        waypoint::combat_mode waypoint_combat_mode(waypoint &wp_);

        /*!
        @brief Gets the radius around the waypoint where the waypoint is completed.

        @param wp_ Waypoint to use

        @return Returns the completeion radius of the waypoint.

        @sa https://community.bistudio.com/wiki/waypointCompletionRadius
        */
        float waypoint_completeion_radius(waypoint &wp_);

        /*!
        @brief Gets the waypoint description.

        @param wp_ Waypoint to use

        @return Returns the waypoint description

        @sa https://community.bistudio.com/wiki/waypointDescription
        */
        sqf_return_string waypoint_description(waypoint &wp_);

        /*!
        @brief Gets the waypoint description.

        @param wp_ Waypoint to use

        @return Returns the waypoint formation, enumeratred.

        @sa https://community.bistudio.com/wiki/waypointFormation
        */
        waypoint::formation waypoint_formation(waypoint &wp_);

        /*!
        @brief Gets the house position assigned to the waypoint.

        @param wp_ Waypoint to use

        @return Returns the house position.

        @sa https://community.bistudio.com/wiki/waypointHousePosition
        */
        float waypoint_house_position(waypoint &wp_);

        /*!
        @brief Gets the waypoint loiter radius.

        @param wp_ Waypoint to use

        @return Returns the loiter radius.

        @sa https://community.bistudio.com/wiki/waypointLoiterRadius
        */
        float waypoint_loiter_radius(waypoint &wp_);

        /*!
        @brief Gets the waypoint loiter type.

        @param wp_ Waypoint to use

        @return Returns the loiter type, enumerated.

        @sa https://community.bistudio.com/wiki/waypointLoiterType
        */
        waypoint::loiter_type waypoint_loiter_type(waypoint &wp_);

        /*!
        @brief Gets the waypoint name.

        @param wp_ Waypoint to use

        @return The name assigned to the waypoint.

        @sa https://community.bistudio.com/wiki/waypointName
        */
        sqf_return_string waypoint_name(waypoint &wp_);

        /*!
        @brief Get Waypoint's Position.

        @param wp_ Waypoint to use

        @return The position of the waypoint.

        @sa https://community.bistudio.com/wiki/waypointPosition
        */
        vector3 waypoint_position(waypoint &wp_);

        /*!
        @brief Gets the waypoint script.

        @param wp_ Waypoint to use

        @return The position of the waypoint.

        @sa https://community.bistudio.com/wiki/waypointScript
        */
        sqf_return_string waypoint_script(waypoint &wp_);

        /*!
        @brief Gets the waypoint show/hide status.

        @param wp_ Waypoint to use

        @return Gets the showhide status, enumerated.

        @sa https://community.bistudio.com/wiki/waypointShow
        */
        waypoint::show waypoint_show(waypoint &wp_);

        /*!
        @brief Gets the waypoint movement speed.

        @param wp_ Waypoint to use

        @return Gets the waypoint speed, enumerated.

        @sa https://community.bistudio.com/wiki/waypointSpeed
        */
        waypoint::speed waypoint_speed(waypoint &wp_);
        // TODO waypoint_statements needs struct for return value
        // TODO waypoint_timeout needs struct for return value

        /*!
        @brief Gets the waypoint type.

        @param wp_ Waypoint to use

        @return The waypoint type, enumerated.

        @sa https://community.bistudio.com/wiki/waypointType
        */
        waypoint::type waypoint_type(waypoint &wp_);

        /*!
        @brief Returns the visibility of the waypoint.

        @param wp_ Waypoint to use

        @return The waypoint visibility.

        @sa https://community.bistudio.com/wiki/waypointVisible
        */
        bool waypoint_visible(waypoint &wp_);

        std::vector<waypoint> synchronized_waypoints(waypoint &wp_);
        std::vector<waypoint> synchronized_waypoints(object &obj_);

        void set_waypoint_behaviour(waypoint &wp_, waypoint::behaviour mode_);
        void set_waypoint_combat_mode(waypoint &wp_, waypoint::combat_mode mode_);
        void set_waypoint_completion_radius(waypoint &wp_, float radius_);
        void set_waypoint_description(waypoint &wp_, std::string &text_);
        void set_waypoint_formation(waypoint &wp_, waypoint::formation formation_);
        void set_waypoint_house_position(waypoint &wp_, float house_pos_);
        void set_waypoint_loiter_radius(waypoint &wp_, float radius_);
        void set_waypoint_loiter_type(waypoint &wp_, waypoint::loiter_type type_);
        void set_waypoint_name(waypoint &wp_, std::string &name_);
        void set_waypoint_position(waypoint &wp_, vector3 &pos_, float radius_);
        void set_waypoint_script(waypoint &wp_, std::string &command_);
        void set_waypoint_speed(waypoint &wp_, waypoint::speed mode_);
        void set_waypoint_statements(waypoint &wp_, std::string condition_, std::string statement_);
        void set_waypoint_timeout(waypoint &wp_, float min_, float mid_, float max_);
        void set_waypoint_type(waypoint &wp_, waypoint::type type_);
        void set_waypoint_visible(waypoint &wp_, bool visibility_);

        void show_waypoint(waypoint &wp_, std::string &show_);

        void synchronize_waypoint(waypoint &wp_, const std::vector<waypoint> &others_);
        void synchronize_waypoint(object &trigger_, const std::vector<waypoint> &others_);

        void waypoint_attach_object(waypoint &wp_, int obj_id_);
        void waypoint_attach_object(waypoint &wp_, object &obj_);

        void show_waypoints(bool enabled_);
        bool waypoint_force_behaviour(const group &group_, int index_);
        void set_waypoint_force_behaviour(const group &group_, int index_, bool force_);
        float waypoint_timeout_current(const group &value_);
        bool waypoints_enabled_uav(const object &value_);
        void enable_uav_waypoints(object &uav_, bool enable_);

        void set_wp_pos(const group &group_, int index_, const vector2 &position_);
        vector3 get_wp_pos(const group &group_, int index_);
        void lock_wp(std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const group>> target_, bool lock_);

        std::vector<waypoint> waypoints(const object &player_);
        std::vector<waypoint> waypoints(const group &group_);
        void set_effect_condition(std::variant<object, waypoint> unit_, sqf_string_const_ref statement_);
        void waypoint_attach_vehicle(const waypoint &waypoint_, const object &vehicle_);
        void enable_uavwaypoints(const object &value0_, bool value1_);

        void create_guarded_point(const side &side_, const vector3 &pos_, float idstatic_, const object &veh_);

        //TRIGGERS
        //Triggers

        struct rv_trigger_area {
            float x;
            float y;
            float angle;
            bool rectangle;
            float z;  // since Arma 3 v1.59.135137

            rv_trigger_area(const game_value &ret_game_value_) : x(ret_game_value_[0]),
                                                                 y(ret_game_value_[1]),
                                                                 angle(ret_game_value_[2]),
                                                                 rectangle(ret_game_value_[3]),
                                                                 z(ret_game_value_[4]) {}
        };

        rv_trigger_area trigger_area(const object &trigger_);

        struct rv_trigger_timeout {
            float time_min;
            float time_mid;
            float time_max;
            bool interruptable;

            rv_trigger_timeout(const game_value &ret_game_value_) : time_min(ret_game_value_[0]),
                                                                    time_mid(ret_game_value_[1]),
                                                                    time_max(ret_game_value_[2]),
                                                                    interruptable(ret_game_value_[3]) {}
        };

        rv_trigger_timeout trigger_timeout(const object &trigger_);

        std::vector<object> list(const object &trigger_);
        void trigger_attach_object(const object &value0_, float value1_);
        void set_trigger_text(const object &value0_, sqf_string_const_ref value1_);
        void set_trigger_type(const object &value0_, sqf_string_const_ref value1_);
        bool trigger_activated(const object &value_);
        object trigger_attached_vehicle(const object &value_);
        sqf_return_string trigger_text(const object &value_);
        float trigger_timeout_current(const object &value_);
        sqf_return_string trigger_type(const object &value_);
        object create_trigger(sqf_string_const_ref type_, const vector3 &pos_, bool make_global_ = true);
        object create_trigger(sqf_string_const_ref type_, const object &pos_, bool make_global_ = true);

        void set_trigger_activation(const object &trigger_, sqf_string_const_ref by_, sqf_string_const_ref type_, bool repeating_);
        void set_trigger_area(const object &trigger_, float radius_x_, float radius_y_, float angle_, bool is_rectangle_, std::optional<float> radius_z_);
        void set_trigger_statements(const object &trigger_, sqf_string_const_ref condition_, sqf_string_const_ref activation_, sqf_string_const_ref deactivation_);
        void set_trigger_timeout(const object &trigger_, float min_, float mid_, float max_, bool interruptable_);

        void synchronize_trigger(const object &trigger_, const std::vector<waypoint> &waypoints_);
        std::vector<object> synchronized_triggers(const waypoint& wp_);

        void trigger_attach_vehicle(const object &trigger_, const std::vector<object> &objects_);

        //both
        void set_music_effect(const object &trigger_, sqf_string_const_ref track_);
        void set_music_effect(const group &group_, int index_, sqf_string_const_ref track_);
        void set_sound_effect(const object &trigger, sqf_string_const_ref sound_, sqf_string_const_ref voice_, sqf_string_const_ref sound_env_, sqf_string_const_ref sound_det_);
        void set_sound_effect(const group &group, int index_, sqf_string_const_ref sound_, sqf_string_const_ref voice_, sqf_string_const_ref sound_env_, sqf_string_const_ref sound_det_);
        void set_title_effect(const object &trigger_, sqf_string_const_ref type_, sqf_string_const_ref effect_, sqf_string_const_ref text_);
        void set_title_effect(const group &group_, int index_, sqf_string_const_ref type_, sqf_string_const_ref effect_, sqf_string_const_ref text_);

    }  // namespace sqf
}  // namespace intercept
