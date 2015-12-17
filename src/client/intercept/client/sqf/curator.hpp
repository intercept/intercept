#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
		namespace curator {
			object curatorcamera();
			object curatormouseover();
			std::vector<object> curatorselected();
			void opencuratorinterface();
			bool shown_curatorcompass();
			float curator_camera_area_ceiling(const object &value_);
			bool curator_editing_area_type(const object &value_);
			float curator_points(const object &value_);
			float curator_waypoint_cost(const object &value_);
			object get_assigned_curator_logic(const object &value_);
			object get_assigned_curator_unit(const object &value_);
			void remove_all_curator_addons(const object &value_);
			void remove_all_curator_camera_areas(const object &value_);
			void remove_all_curator_editing_areas(const object &value_);
			void show_curator_compass(bool value_);
			void unassign_curator(const object &value_);
			void add_curator_points(float value0_, const object &value1_);
			void allow_curator_logic_ignore_areas(bool value0_, const object &value1_);
			float curator_coef(const object &value0_, const std::string &value1_);
			void remove_curator_camera_area(float value0_, const object &value1_);
			void remove_curator_editing_area(float value0_, const object &value1_);
			void set_curator_camera_area_ceiling(float value0_, const object &value1_);
			void set_curator_editing_area_type(bool value0_, const object &value1_);
			void set_curator_waypoint_cost(float value0_, const object &value1_);

			std::vector<std::string> curator_addons(const object &curator_module_);
			std::vector<object> curator_editable_objects(const object &curator_module_);
		}
    }
}
