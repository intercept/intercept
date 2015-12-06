#include "group.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        bool group_icon_selectable() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__groupiconselectable__ret__bool);
        }

        // TODO std::array<bool, 2> group_icons_visible();

        group grp_null() {
            return __helpers::__retrieve_nular_group(client::__sqf::nular__grpnull__ret__group);
        }
        void clear_group_icons(group value_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__cleargroupicons__group__ret__nothing, *value_);
        }

        group create_group(side value_) {
            return nullptr; // TODO implement
        }

        void delete_group(group value_) {
            // TODO implement
        }

        group group_from_net_id(std::string value_) {
            return nullptr; // TODO implement
        }

        std::string group_id(group value_) {
            return nullptr; // TODO implement
        }

        float group_owner(group value_) {
            return 0.0f; // TODO implement
        }

        bool set_group_owner(float value0_, group value1_) {
            game_value ret_value = host::functions.invoke_raw_binary(client::__sqf::binary__setgroupowner__group__scalar__ret__bool, game_value_number(value0_), *value1_);
            bool rv = ((game_data_bool *)ret_value.data)->value;
            host::functions.free_value(&ret_value);
            return rv;
        }

        object leader(group value_) {
            return nullptr; // TODO implement
        }

        void group_radio(object value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__groupradio__object__string__ret__nothing, *value0_, game_value_string(value1_));
        }

        void remove_group_icon(float value0_, group value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__removegroupicon__group__scalar__ret__nothing, game_value_number(value0_), *value1_);
        }

        void select_leader(object value0_, group value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__selectleader__group__object__ret__nothing, *value0_, *value1_);
        }

        float current_waypoint(group value_) {
            return 0.0f; // TODO implement
        }
        
        void set_group_icons_selectable(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__setgroupiconsselectable__bool__ret__nothing, value_);
        }
    }
}
