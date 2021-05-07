#include "group.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"
#include "waypoint.hpp"
namespace intercept {
    namespace sqf {
        sqf_return_string combat_mode(const group &grp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__combatmode__object_group__ret__string, grp_);
        }

        float add_group_icon(const group &group_, sqf_string_const_ref icon_, std::optional<vector2> offset_) {
            game_value params(offset_.has_value() ? game_value{icon_, *offset_} : game_value{icon_});

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
                return group(host::functions.invoke_raw_unary(__sqf::unary__creategroup__side_array__ret__group, {value_, delete_when_empty_}));
            return group(host::functions.invoke_raw_unary(__sqf::unary__creategroup__side_array__ret__group, value_));
        }

        void delete_group(const group &value_) {
            host::functions.invoke_raw_unary(__sqf::unary__deletegroup__group__ret__nothing, value_);
        }

        group group_from_net_id(sqf_string_const_ref value_) {
            return group(host::functions.invoke_raw_unary(__sqf::unary__groupfromnetid__string__ret__group, value_));
        }

        sqf_return_string group_id(const group &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__groupid__group__ret__string, value_);
        }

        float group_owner(const group &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__groupowner__group__ret__scalar, value_);
        }

        bool set_group_owner(const group &group_, int client_id_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setgroupowner__group__scalar__ret__bool, static_cast<float>(client_id_), group_);
        }

        object leader(const group &value_) {
            return object(host::functions.invoke_raw_unary(__sqf::unary__leader__group__ret__object, value_));
        }

        void group_radio(const object &unit_, sqf_string_const_ref radio_name_) {
            host::functions.invoke_raw_binary(__sqf::binary__groupradio__object__string__ret__nothing, unit_, radio_name_);
        }

        void remove_group_icon(const group &group_, int icon_id_) {
            host::functions.invoke_raw_binary(__sqf::binary__removegroupicon__group__scalar__ret__nothing, static_cast<float>(icon_id_), group_);
        }

        void select_leader(const group &group_, const object &unit_) {
            host::functions.invoke_raw_binary(__sqf::binary__selectleader__group__object__ret__nothing, group_, unit_);
        }

        float current_waypoint(const group &group_) {
            return host::functions.invoke_raw_unary(__sqf::unary__currentwaypoint__group__ret__scalar, group_);
        }

        void set_group_icons_selectable(bool val_) {
            __helpers::__empty_unary_bool(__sqf::unary__setgroupiconsselectable__bool__ret__nothing, val_);
        }
        void set_current_waypoint(group &gp_, waypoint &wp_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcurrentwaypoint__group__array__ret__nothing, gp_, wp_);
        }
        rv_group_icon_params get_group_icon_params(const group &group_) {
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
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__joinsilent__array__object_group__ret__nothing, std::move(units), group_);
        }

        void join_silent(const std::vector<object> &units_, const object &unit_group_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__joinsilent__array__object_group__ret__nothing, std::move(units), unit_group_);
        }

        void join_as(const object &unit_, const group &group_, int pos_id_) {
            game_value params({group_,
                               static_cast<float>(pos_id_)});

            host::functions.invoke_raw_binary(__sqf::binary__joinas__object__array__ret__nothing, unit_, params);
        }

        void join_as_silent(const object &unit_, const group &group_, int pos_id_) {
            game_value params({group_,
                               static_cast<float>(pos_id_)});

            host::functions.invoke_raw_binary(__sqf::binary__joinassilent__object__array__ret__nothing, unit_, params);
        }
        std::vector<object> units(const group &gp_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__units__group__ret__array, gp_));
        }
        std::vector<object> units(const side &side) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__units__side__ret__any, side));
        }
        side get_side(const group &group_) {
            return side(host::functions.invoke_raw_unary(__sqf::unary__side__group__ret__side, group_));
        }

        side side_get(const group &group_) { return get_side(group_); }

        sqf_return_string_list all_variables(const group &value_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__group__ret__array, value_));
        }
        bool is_null(const group &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__group__ret__bool, value_);
        }

        bool is_group_deleted_when_empty(const group &group_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isgroupdeletedwhenempty__group__ret__bool, group_);
        }

        void delete_group_when_empty(const group &group_, bool delete_) {
            host::functions.invoke_raw_binary(__sqf::binary__deletegroupwhenempty__group__bool__ret__nothing, group_, delete_);
        }

        void add_vehicle(const group &value0_, const object &value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__addvehicle__group__object__ret__nothing, value0_, value1_);
        }
        void set_group_icons_visible(bool map_, bool hud_) {
            game_value params({map_,
                               hud_});

            host::functions.invoke_raw_unary(__sqf::unary__setgroupiconsvisible__array__ret__nothing, params);
        }

        std::vector<bool> group_icons_visible() {
            return __helpers::__convert_to_vector<bool>(host::functions.invoke_raw_nular(__sqf::nular__groupiconsvisible__ret__array));
        }
        rv_group_icon get_group_icon(const group &group_, int &id_) {
            game_value res = host::functions.invoke_raw_binary(__sqf::binary__getgroupicon__group__scalar__ret__array, group_, id_);

            return rv_group_icon({res[0], vector2(res[1][0], res[1][0])});
        }
        void group_select_unit(const object &player_, const object &unit_, bool select_) {
            game_value params_right({unit_,
                                     select_});

            host::functions.invoke_raw_binary(__sqf::binary__groupselectunit__object__array__ret__nothing, player_, params_right);
        }

        void set_group_icon(const group &group_, float icon_id, sqf_string_const_ref icon_path_, vector2 offset_) {
            host::functions.invoke_raw_binary(__sqf::binary__setgroupicon__group__array__ret__nothing, group_, {icon_id, icon_path_, offset_});
        }
        void set_formation(const group &group_, sqf_string_const_ref formation_) {
            host::functions.invoke_raw_binary(__sqf::binary__setformation__object_group__string__ret__nothing, group_, formation_);
        }

        void set_form_dir(const group &group_, float heading_) {
            host::functions.invoke_raw_binary(__sqf::binary__setformdir__object_group__scalar__ret__nothing, group_, heading_);
        }

        void set_group_icon(const group &group_, int id_, sqf_string_const_ref icon_, const vector2 &offset_) {
            host::functions.invoke_raw_binary(__sqf::binary__setgroupicon__group__array__ret__nothing, group_, {id_, icon_, offset_});
        }

        void set_group_icon_params(const group &group_, const rv_color &color_, sqf_string_const_ref text_, float scale_, bool visible_) {
            host::functions.invoke_raw_binary(__sqf::binary__setgroupiconparams__group__array__ret__nothing, group_, {color_, text_, scale_, visible_});
        }

        void set_group_id(const group &group_, sqf_string_const_ref name_format_, sqf_string_list_const_ref params_) {
            auto_array<game_value> params(params_.begin(), params_.end());
            params.emplace(params.begin(), name_format_.operator game_value());
            host::functions.invoke_raw_binary(__sqf::binary__setgroupid__object_group__array__ret__nothing, group_, std::move(params));
        }

        void set_group_id_global(const group &group_, sqf_string_const_ref name_format_, sqf_string_list_const_ref params_) {
            auto_array<game_value> params(params_.begin(), params_.end());
            params.emplace(params.begin(), name_format_.operator game_value());
            host::functions.invoke_raw_binary(__sqf::binary__setgroupidglobal__object_group__array__ret__nothing, group_, std::move(params));
        }
        void set_speed_mode(const group &group_, sqf_string_const_ref speed_mode_) {
            host::functions.invoke_raw_binary(__sqf::binary__setspeedmode__object_group__string__ret__nothing, group_, speed_mode_);
        }

        //Teams
        team_member create_team(sqf_string_const_ref type_, sqf_string_const_ref name_) {
            game_value args({
                type_,
                name_,
            });

            return team_member(host::functions.invoke_raw_unary(__sqf::unary__createteam__array__ret__team_member, args));
        }
        object agent(const team_member &value_) {
            return object(host::functions.invoke_raw_unary(__sqf::unary__agent__team_member__ret__object, value_));
        }
        std::vector<team_member> agents() {
            return __helpers::__convert_to_vector<team_member>(host::functions.invoke_raw_nular(__sqf::nular__agents__ret__array));
        }

        void set_formation(const team_member &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setformation__team_member__string__ret__nothing, value0_, value1_);
        }
        void delete_team(const team_member &value_) {
            host::functions.invoke_raw_unary(__sqf::unary__deleteteam__team_member__ret__nothing, value_);
        }
        sqf_return_string formation(const team_member &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__formation__team_member__ret__string, value_);
        }
        void set_from_editor(const team_member &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfromeditor__team_member__bool__ret__nothing, value0_, value1_);
        }
        bool from_editor(const team_member &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__fromeditor__team_member__ret__bool, value_);
        }
        bool is_agent(const team_member &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isagent__team_member__ret__bool, value_);
        }
        team_member leader(const team_member &value_) {
            return team_member(host::functions.invoke_raw_unary(__sqf::unary__leader__team_member__ret__team_member, value_));
        }

        sqf_return_string team_name(const team_member &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__teamname__team_member__ret__string, value_);
        }

        sqf_return_string team_type(const team_member &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__teamtype__team_member__ret__string, value_);
        }
        std::vector<object> members(const team_member &team_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__members__team_member__ret__array, team_));
        }

        void add_resources(const team_member &team_member_, sqf_string_list_const_ref resources_) {
            auto_array<game_value> resources(resources_.begin(), resources_.end());

            host::functions.invoke_raw_binary(__sqf::binary__addresources__team_member__array__ret__nothing, team_member_, std::move(resources));
        }

        void add_team_member(const team_member &team_, const team_member &member_) {
            host::functions.invoke_raw_binary(__sqf::binary__addteammember__team_member__team_member__ret__nothing, team_, member_);
        }
        void delete_resources(const team_member &team_member_, sqf_string_list_const_ref resources_) {
            auto_array<game_value> resources(resources_.begin(), resources_.end());

            host::functions.invoke_raw_binary(__sqf::binary__deleteresources__team_member__array__ret__nothing, team_member_, std::move(resources));
        }
        void remove_team_member(const team_member &team_, const team_member &member_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeteammember__team_member__team_member__ret__nothing, team_, member_);
        }
        void set_leader(const team_member &team_, const team_member &leader_) {
            host::functions.invoke_raw_binary(__sqf::binary__setleader__team_member__team_member__ret__nothing, team_, leader_);
        }

    }  // namespace sqf
}  // namespace intercept
