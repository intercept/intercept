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
			bool group_icon_selectable();
			std::array<bool, 2> group_icons_visible();
			group grp_null();
			void clear_group_icons(const group &value_);
			group create_group(const side &value_);
			void delete_group(const group &value_);

			group group_from_net_id(const std::string &value_);
			std::string group_id(const group &value_);
			float group_owner(const group &value_);
			bool set_group_owner(const group &value0_, float value1_);

			object leader(const group &value_);
			void group_radio(const object &value0_, const std::string& value1_);
			void remove_group_icon(const group &value0_, float value1_);
			void select_leader(const object &value0_, const group &value1_);
			float current_waypoint(const group &value_);
			void set_group_icons_selectable(bool value_);
    }
}
