#include "group.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"
#include "waypoint.hpp"
namespace intercept {
    namespace sqf {
        std::string combat_mode(const group &grp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__combatmode__object_group__ret__string, grp_);
        }

        float add_group_icon(const group& group_, const std::string& icon_, std::optional<vector2> offset_) {
            game_value params(offset_.has_value() ? game_value{ icon_, *offset_ } : game_value{ icon_ });

            return host::functions.invoke_raw_binary(__sqf::binary__addgroupicon__group__array__ret__scalar, group_, params);
        }
        /* Group */
        bool group_icon_selectable() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__groupiconselectable__ret__bool);
        }

        group grp_null() {
            return __helpers::__retrieve_nular_group(__sqf::nular__grpnull__ret__group);
        }

        void clear_group_icons(const group &value_) {
            host::functions.invoke_raw_unary(__sqf::unary__cleargroupicons__group__ret__nothing, value_);
        }

        group create_group(const side &value_, bool delete_when_empty_) {
            if (delete_when_empty_)
                return group(host::functions.invoke_raw_unary(__sqf::unary__creategroup__side_array__ret__group, { value_ ,delete_when_empty_ }));
            return group(host::functions.invoke_raw_unary(__sqf::unary__creategroup__side_array__ret__group, value_));
        }

        void delete_group(const group &value_) {
            host::functions.invoke_raw_unary(__sqf::unary__deletegroup__group__ret__nothing, value_);
        }

        group group_from_net_id(const std::string& value_) {
            return group(host::functions.invoke_raw_unary(__sqf::unary__groupfromnetid__string__ret__group, value_));
        }

        std::string group_id(const group &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__groupid__group__ret__string, value_);
        }

        float group_owner(const group &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__groupowner__group__ret__scalar, value_);
        }

        bool set_group_owner(const group & group_, int client_id_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setgroupowner__group__scalar__ret__bool, static_cast<float>(client_id_), group_);
        }

        object leader(const group &value_) {
            return object(host::functions.invoke_raw_unary(__sqf::unary__leader__group__ret__object, value_));
        }

        void group_radio(const object & unit_, const std::string& radio_name_) {
            host::functions.invoke_raw_binary(__sqf::binary__groupradio__object__string__ret__nothing, unit_, radio_name_);
        }

        void remove_group_icon(const group & group_, int icon_id_) {
            host::functions.invoke_raw_binary(__sqf::binary__removegroupicon__group__scalar__ret__nothing, static_cast<float>(icon_id_), group_);
        }

        void select_leader(const group & group_, const object & unit_) {
            host::functions.invoke_raw_binary(__sqf::binary__selectleader__group__object__ret__nothing, group_, unit_);
        }

        float current_waypoint(const group & group_) {
            return host::functions.invoke_raw_unary(__sqf::unary__currentwaypoint__group__ret__scalar, group_);
        }

        void set_group_icons_selectable(bool val_) {
            __helpers::__empty_unary_bool(__sqf::unary__setgroupiconsselectable__bool__ret__nothing, val_);
        }
        void set_current_waypoint(group & gp_, waypoint & wp_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcurrentwaypoint__group__array__ret__nothing, gp_, wp_);
        }
        rv_group_icon_params get_group_icon_params(const group& group_) {
            return rv_group_icon_params(host::functions.invoke_raw_unary(__sqf::unary__getgroupiconparams__group__ret__array, group_));
        }
        void join(const std::vector<object> &units_, const group &group_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__join__array__object_group__ret__nothing, std::move(units), group_);
        }

        void join(const std::vector<object> &units_, const object &unit_group_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__join__array__object_group__ret__nothing, std::move(units), unit_group_);
        }

        void join_silent(const std::vector<object> &units_, const group &group_) {
            auto_array<game_value> units;
            for (object unit : units_) {
                units.push_back(unit);
            }

            host::functions.invoke_raw_binary(__sqf::binary__joinsilent__array__object_group__ret__nothing, std::move(units), group_);
        }

        void join_silent(const std::vector<object> &units_, const object &unit_group_) {
            auto_array<game_value> units;
            for (object unit : units_) {
                units.push_back(unit);
            }

            host::functions.invoke_raw_binary(__sqf::binary__joinsilent__array__object_group__ret__nothing, std::move(units), unit_group_);
        }

        void join_as(const object &unit_, const group &group_, int pos_id_) {
            game_value params({
                group_,
                static_cast<float>(pos_id_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__joinas__object__array__ret__nothing, unit_, params);
        }

        void join_as_silent(const object &unit_, const group &group_, int pos_id_) {
            game_value params({
                group_,
                static_cast<float>(pos_id_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__joinassilent__object__array__ret__nothing, unit_, params);
        }
        std::vector<object> units(const group& gp_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__units__group__ret__array, gp_));
        }
        side get_side(const group &group_) {
            return side(host::functions.invoke_raw_unary(__sqf::unary__side__group__ret__side, group_));
        }
        std::vector<std::string> all_variables(const group &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__group__ret__array, value_));
        }
        bool is_null(const group &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__group__ret__bool, value_);
        }

    }
}
