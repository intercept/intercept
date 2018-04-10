/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Curator functionality, aka Zeus

These are functions for working with the Zeus game master system.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"
#include "client/sqf/waypoint.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        /* Curator */
        object curator_camera();
        object curator_mouse_over();
        
        struct curator_selected_return {
            curator_selected_return(
                std::vector<object> _objs,
                std::vector<group> _g,
                std::vector<intercept::sqf::waypoint> _wps,
                std::vector<marker> _m
            ): _objects(std::move(_objs)),
                _groups(std::move(_g)),
                _waypoints(std::move(_wps)),
                _marker(std::move(_m)) {}

            std::vector<object> _objects;
            std::vector<group> _groups;
            std::vector<intercept::sqf::waypoint> _waypoints;
            std::vector<marker> _marker;
        };
        
        curator_selected_return curator_selected();
        void open_curator_interface();
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
        void add_curator_points(const object &value0_, float value1_);
        void allow_curator_logic_ignore_areas(const object &value0_, bool value1_);
        float curator_coef(const object &value0_, sqf_string_const_ref value1_);
        void remove_curator_camera_area(const object &value0_, float value1_);
        void remove_curator_editing_area(const object &value0_, float value1_);
        void set_curator_camera_area_ceiling(const object &value0_, float value1_);
        void set_curator_editing_area_type(const object &value0_, bool value1_);
        void set_curator_waypoint_cost(const object &value0_, float value1_);
        void add_curator_addons(const object &curator_object_, sqf_string_list_const_ref addons_);
        void add_curator_camera_area(const object &curator_object_, int camera_area_id_, const vector2 &position_, float radius_);
        void add_curator_camera_area(const object &curator_object_, int camera_area_id_, const vector3 &position_, float radius_);
        void add_curator_editable_objects(const object &curator_object_, const std::vector<object> &objects_, bool add_crew_);
        void add_curator_editing_area(const object &curator_object_, int edit_area_id_, const vector2 &position_, float radius_);

        sqf_return_string_list curator_addons(const object &curator_module_);
        std::vector<object> curator_editable_objects(const object &curator_module_);
        std::vector<object> curator_registered_objects(const object &curator_);
        std::vector<object> object_curators(const object &obj_);

        void remove_curator_addons(const object &curator_module_, sqf_string_list_const_ref addons_);
        void remove_curator_editable_objects(const object &curator_module, const std::vector<object> &objects_, bool &remove_crew_);
        void set_curator_coef(const object &curator_, sqf_string_const_ref action_, std::variant<float, bool> coef_);
        void assign_curator(const object &player_, const object &curator_module_);

    }  // namespace sqf
}  // namespace intercept
