#include "group.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
		namespace groups {
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
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__creategroup__side__ret__group, *value_);
				return std::make_shared<group_ptr>(ret_value);
			}

			void delete_group(group value_) {
				host::functions.invoke_raw_unary(client::__sqf::unary__deletegroup__group__ret__nothing, *value_);
			}

			group group_from_net_id(const std::string& value_) {
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__groupfromnetid__string__ret__group, game_value_string(value_));
				return std::make_shared<group_ptr>(ret_value);
			}

			std::string group_id(group value_) {
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__groupid__group__ret__string, *value_);
				std::string rv = ((game_data_string *)ret_value.data)->get_string();
				host::functions.free_value(&ret_value);
				return rv;
			}

			float group_owner(group value_) {
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__groupowner__group__ret__scalar, *value_);
				float rv = ((game_data_number *)ret_value.data)->number;
				host::functions.free_value(&ret_value);
				return rv;
			}

			bool set_group_owner(float value0_, group value1_) {
				game_value ret_value = host::functions.invoke_raw_binary(client::__sqf::binary__setgroupowner__group__scalar__ret__bool, game_value_number(value0_), *value1_);
				bool rv = ((game_data_bool *)ret_value.data)->value;
				host::functions.free_value(&ret_value);
				return rv;
			}

			object leader(group value_) {
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__leader__group__ret__object, *value_);
				return std::make_shared<object_ptr>(ret_value);
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
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__currentwaypoint__group__ret__scalar, *value_);
				float rv = ((game_data_number *)ret_value.data)->number;
				host::functions.free_value(&ret_value);
				return rv;
			}

			void set_group_icons_selectable(bool value_) {
				__helpers::__empty_unary_bool(client::__sqf::unary__setgroupiconsselectable__bool__ret__nothing, value_);
			}
		}
    }
}
