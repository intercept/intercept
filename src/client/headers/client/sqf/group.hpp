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
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        class waypoint;

        std::string combat_mode(const group &loc_);
        float add_group_icon(const group& group_, const std::string& icon_, const std::vector<float>& offset_);



        /* Group */
        bool group_icon_selectable();
        // TODO std::array<bool, 2> group_icons_visible();
        group grp_null();
        void clear_group_icons(const group &value_);
        group create_group(const side &value_, bool delete_when_empty_ = false);
        void delete_group(const group &value_);

        group group_from_net_id(const std::string &value_);
        std::string group_id(const group &value_);
        float group_owner(const group &value_);
        bool set_group_owner(const group & group_, int client_id_);

        object leader(const group &value_);
        void group_radio(const object & unit_, const std::string& radio_name_);
        void remove_group_icon(const group & group_, int icon_id_);
        void select_leader(const group & group_, const object & unit_);
        float current_waypoint(const group & group_);
        void set_group_icons_selectable(bool val_);

        void set_current_waypoint(group & gp_, waypoint & wp_);

        struct rv_group_icon_params {
            rv_color color;
            std::string text;
            float scale;
            bool visible;

            rv_group_icon_params(const game_value &ret_game_value_) :
                color(ret_game_value_[0]),
                text(ret_game_value_[1]),
                scale(ret_game_value_[2]),
                visible(ret_game_value_[3]) {}
        };

        rv_group_icon_params get_group_icon_params(const group& group_);

        void join(const std::vector<object> &units_, const group &group_);
        void join(const std::vector<object> &units_, const object &unit_group_);
        void join_silent(const std::vector<object> &units_, const group &group_);
        void join_silent(const std::vector<object> &units_, const object &unit_group_);
        void join_as(const object &unit_, const group &group_, int pos_id_);
        void join_as_silent(const object &unit_, const group &group_, int pos_id_);

        std::vector<object> units(const group& gp_);
        side get_side(const group &group_);
        std::vector<std::string> all_variables(const group &value_);
        bool is_null(const group &value_);
    }
}
