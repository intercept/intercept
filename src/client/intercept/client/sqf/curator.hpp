#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
		namespace curator {
			object curatorcamera();
			object curatormouseover();
			std::vector<object> curatorselected();
			void opencuratorinterface();
			bool shown_curatorcompass();
			float curator_camera_area_ceiling(object value_);
			bool curator_editing_area_type(object value_);
			float curator_points(object value_);
			float curator_waypoint_cost(object value_);
			object get_assigned_curator_logic(object value_);
			object get_assigned_curator_unit(object value_);
			void remove_all_curator_addons(object value_);
			void remove_all_curator_camera_areas(object value_);
			void remove_all_curator_editing_areas(object value_);
			void show_curator_compass(bool value_);
			void unassign_curator(object value_);
			void add_curator_points(float value0_, object value1_);
			void allow_curator_logic_ignore_areas(bool value0_, object value1_);
			float curator_coef(object value0_, std::string value1_);
			void remove_curator_camera_area(float value0_, object value1_);
			void remove_curator_editing_area(float value0_, object value1_);
			void set_curator_camera_area_ceiling(float value0_, object value1_);
			void set_curator_editing_area_type(bool value0_, object value1_);
			void set_curator_waypoint_cost(float value0_, object value1_);
		}
    }
}
