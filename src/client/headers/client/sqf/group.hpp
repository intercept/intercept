/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Group function wrappers.

These are functions used to handle AI or player groups.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        class waypoint;
        struct rv_group_icon {
            sqf_string icon;
            vector2 offset;
        };
        sqf_return_string combat_mode(const group &loc_);
        float add_group_icon(const group &group_, sqf_string_const_ref icon_, std::optional<vector2> offset_ = std::optional<vector2>());

        /* Group */
        bool group_icon_selectable();
        group grp_null();
        void clear_group_icons(const group &value_);
        group create_group(const side &value_, bool delete_when_empty_ = false);
        void delete_group(const group &value_);

        group group_from_net_id(sqf_string_const_ref value_);
        sqf_return_string group_id(const group &value_);
        int group_id(const object &unit_);
        float group_owner(const group &value_);
        bool set_group_owner(const group &group_, int client_id_);

        object leader(const group &value_);
        void group_radio(const object &unit_, sqf_string_const_ref radio_name_);
        void remove_group_icon(const group &group_, int icon_id_);
        void select_leader(const group &group_, const object &unit_);
        float current_waypoint(const group &group_);
        void set_group_icons_selectable(bool val_);

        void set_current_waypoint(group &gp_, waypoint &wp_);

        struct rv_group_icon_params {
            rv_color color;
            std::string text;
            float scale;
            bool visible;

            explicit rv_group_icon_params(const game_value &ret_game_value_) : color(ret_game_value_[0]),
                                                                               text(ret_game_value_[1]),
                                                                               scale(ret_game_value_[2]),
                                                                               visible(ret_game_value_[3]) {}
        };

        rv_group_icon_params get_group_icon_params(const group &group_);

        void join(const std::vector<object> &units_, const group &group_);
        void join(const std::vector<object> &units_, const object &unit_group_);
        void join_silent(const std::vector<object> &units_, const group &group_);
        void join_silent(const std::vector<object> &units_, const object &unit_group_);
        void join_as(const object &unit_, const group &group_, int pos_id_);
        void join_as_silent(const object &unit_, const group &group_, int pos_id_);

        std::vector<object> units(const group &gp_);
        std::vector<object> units(const side &side_);
        side get_side(const group &group_);
        side side_get(const group& group_);
        sqf_return_string_list all_variables(const group &value_);
        bool is_null(const group &value_);

        bool is_group_deleted_when_empty(const group &group_);
        void delete_group_when_empty(const group &group_, bool delete_);

        //group
        void add_vehicle(const group &value0_, const object &value1_);
        void set_group_icons_visible(bool map_, bool hud_);
        std::vector<bool> group_icons_visible();
        rv_group_icon get_group_icon(const group &group_, int &id_);
        void group_select_unit(const object &player_, const object &unit_, bool select_);
        void set_group_icon(const group &group_, float icon_id, sqf_string_const_ref icon_path_, vector2 offset_);
        void set_formation(const group &group_, sqf_string_const_ref formation_);
        void set_form_dir(const group &group_, float heading_);
        void set_group_icon(const group &group_, int id_, sqf_string_const_ref icon_, const vector2 &offset_);
        void set_group_icon_params(const group &group_, const rv_color &color_, sqf_string_const_ref text_, float scale_, bool visible_);
        void set_group_id(const group &group_, sqf_string_const_ref name_format_, sqf_string_list_const_ref params_);
        void set_group_id_global(const group &group_, sqf_string_const_ref name_format_, sqf_string_list_const_ref params_);

        void set_speed_mode(const group &group_, sqf_string_const_ref speed_mode_);

        //Teams
        /* potential namespace: teams */
        team_member create_team(sqf_string_const_ref type_, sqf_string_const_ref name_);

        object agent(const team_member &value_);
        std::vector<team_member> agents();

        void set_formation(const team_member &value0_, sqf_string_const_ref value1_);

        void delete_team(const team_member &value_);
        sqf_return_string formation(const team_member &value_);
        void set_from_editor(const team_member &value0_, bool value1_);
        bool from_editor(const team_member &value_);
        bool is_agent(const team_member &value_);
        team_member leader(const team_member &value_);
        sqf_return_string team_name(const team_member &value_);
        sqf_return_string team_type(const team_member &value_);

        std::vector<object> members(const team_member &team_);
        void add_resources(const team_member &team_member_, sqf_string_list_const_ref resources_);
        void add_team_member(const team_member &team_, const team_member &member_);
        void delete_resources(const team_member &team_member_, sqf_string_list_const_ref resources_);
        void remove_team_member(const team_member &team_, const team_member &member_);
        void set_leader(const team_member &team_, const team_member &leader_);
    }  // namespace sqf
}  // namespace intercept
