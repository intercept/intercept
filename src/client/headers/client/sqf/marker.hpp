/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Marker function wrappers.

Functionality to create and manipulate map markers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        /* - Markers - */

        sqf_return_string create_marker(sqf_string_const_ref name_, const vector3 &pos_);
        sqf_return_string create_marker(sqf_string_const_ref name_, const vector2 &pos_);
        sqf_return_string create_marker(sqf_string_const_ref name_, const object &pos_);
        sqf_return_string create_marker_local(sqf_string_const_ref name_, const vector3 &pos_);
        sqf_return_string create_marker_local(sqf_string_const_ref name_, const vector2 &pos_);
        sqf_return_string create_marker_local(sqf_string_const_ref name_, const object &pos_);

        void delete_marker(sqf_string_const_ref value_);
        void delete_marker_local(sqf_string_const_ref value_);

        void set_marker_size(sqf_string_const_ref marker_, const vector2 &size_);
        void set_marker_size_local(sqf_string_const_ref marker_, const vector2 &size_);
        void set_marker_type(sqf_string_const_ref marker_, sqf_string_const_ref type_);
        void set_marker_type_local(sqf_string_const_ref marker_, sqf_string_const_ref type_);
        void set_marker_text(sqf_string_const_ref marker_, sqf_string_const_ref text_);
        void set_marker_text_local(sqf_string_const_ref marker_, sqf_string_const_ref text_);
        void set_marker_shape(sqf_string_const_ref marker_, sqf_string_const_ref shape_);
        void set_marker_shape_local(sqf_string_const_ref marker_, sqf_string_const_ref shape_);

        void set_marker_pos(sqf_string_const_ref marker_, const vector2 &pos_);
        void set_marker_pos(sqf_string_const_ref marker_, const vector3 &pos_);
        void set_marker_pos(sqf_string_const_ref marker_, const object& target_);
        void set_marker_pos_local(sqf_string_const_ref marker_, const vector3 &pos_);
        void set_marker_pos_local(sqf_string_const_ref marker_, const vector2 &pos_);
        void set_marker_pos_local(sqf_string_const_ref marker_, const object& target_);

        void set_marker_brush(sqf_string_const_ref marker_, sqf_string_const_ref brush_);
        void set_marker_brush_local(sqf_string_const_ref marker_, sqf_string_const_ref brush_);
        void set_marker_color(sqf_string_const_ref marker_, sqf_string_const_ref color_);
        void set_marker_color_local(sqf_string_const_ref marker_, sqf_string_const_ref color_);
        void set_marker_alpha(sqf_string_const_ref marker_, float alpha_);
        void set_marker_alpha_local(sqf_string_const_ref marker_, float alpha_);
        void set_marker_dir(sqf_string_const_ref marker_, float dir_);
        void set_marker_dir_local(sqf_string_const_ref marker_, float dir_);

        float marker_alpha(sqf_string_const_ref value_);
        float marker_dir(sqf_string_const_ref value_);
        sqf_return_string marker_brush(sqf_string_const_ref value_);
        sqf_return_string marker_color(sqf_string_const_ref value_);
        sqf_return_string marker_shape(sqf_string_const_ref value_);
        sqf_return_string marker_text(sqf_string_const_ref value_);
        sqf_return_string marker_type(sqf_string_const_ref value_);

        sqf_return_string get_marker_color(sqf_string_const_ref value_);
        sqf_return_string get_marker_type(sqf_string_const_ref value_);
        vector3 get_marker_pos(sqf_string_const_ref value_);
        vector3 get_marker_pos(sqf_string_const_ref marker_name_, bool preserveElevation);
        vector2 get_marker_size(sqf_string_const_ref value_);

        std::vector<marker> all_map_markers();

        /* - Locations - */
        namespace __helpers {
            vector3 get_pos_loc(unary_function fnc_, const location &loc_);
        }
        void set_importance(const location &loc_, const float &value_);
        void set_side(const location &loc_, const side &side_);
        void set_position(const location &location_, const vector3 &position_);
        void delete_location(const location &loc_);
        void attach_object(const location &location_, const object &object_);
        bool is_null(const location &loc_);
        bool rectangular(const location &loc_);
        bool in(const vector3 &pos_, const location &loc_);
        float direction(const location &value_);
        float importance(const location &loc_);
        float distance(const location &start_, const location &end_);
        float distance(const location &start_, const vector3 &end_);
        float distance(const vector3 &start_, const location &end_);
        location nearest_location(const vector3 &pos_, sqf_string_const_ref location_class_);
        location nearest_location(const object &unit_, sqf_string_const_ref location_class_);
        location nearest_location_with_dubbing(const vector3 &pos_);
        location nearest_location_with_dubbing(const object &obj_);
        object attached_object(const location &loc_);
        side get_side(const location &loc_);
        vector3 position(const location &loc_);
        vector2 size(const location &loc_);
        vector3 get_pos(const location &loc_);
        vector2 location_position(const location &loc_);
        std::vector<location> nearest_locations(const vector3 &pos_, sqf_string_list_const_ref location_types_, float radius_);
        std::vector<location> nearest_locations(const vector3 &pos_, sqf_string_list_const_ref location_types_, float radius_, const vector3 &sort_position_);
        std::vector<location> nearest_locations(const vector3 &pos_, sqf_string_list_const_ref location_types_, float radius_, const object &sort_obj_);
        std::vector<location> nearest_locations(const object &unit_, sqf_string_list_const_ref location_types_, float radius_);
        std::vector<location> nearest_locations(const object &unit_, sqf_string_list_const_ref location_types_, float radius_, const vector3 &sort_position_);
        std::vector<location> nearest_locations(const object &unit_, sqf_string_list_const_ref location_types_, float radius_, const object &sort_obj_);
        sqf_return_string_list all_variables(const location &value_);
        sqf_return_string name(const location &loc_);
        sqf_return_string type(const location &loc_);
        sqf_return_string class_name(const location &loc_);
        location create_location(sqf_string_const_ref classname_, const vector3 &pos_, float size_x_, float size_y_);
        location create_location(sqf_string_const_ref classname_, const vector2 &pos_, float size_x_, float size_y_);
        location create_location(sqf_string_const_ref classname_, const object &obj_, float size_x_, float size_y_);
        location location_null();

        void set_rectangular(const location &location_, bool rectangular_);
        void set_size(const location &location_, float size_x_, float size_y_);
        void set_name(const location &location_, sqf_string_const_ref name_);
        void set_speech(const location &location_, sqf_string_const_ref speech_);
        void set_text(const location &location_, sqf_string_const_ref text_);
        void set_type(const location &location_, sqf_string_const_ref type_);

        //icons/draw
        void remove_draw_icon(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref string_identifier);
        void remove_draw_links(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref string_identifier);
        void set_draw_icon(const control &map_, const object &object_, sqf_string_const_ref texture_, const rv_color &color_, const vector3 &offset_, float width_, float height_, float size_, float angle_, sqf_string_const_ref identifier_, float shadow_, bool is_3d_, bool draw_line_, float priority_);
        void update_draw_icon(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref string_identifier_, const rv_color &color_, const vector2 &offset_, float width_, float height_, bool maintain_size_, float angle_, int shadow_);
        void draw_arrow(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, const rv_color &color_);
        void draw_ellipse(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> center_, const vector2 &radius_, float angle_, const rv_color &color_, sqf_string_const_ref fill_texture);
        void draw_line(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, const rv_color &color_);
        void draw_link(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, sqf_string_const_ref param_type_, sqf_string_const_ref line_type_, rv_color &color_);
        void draw_location(const control &map_, const location &location_);
        void draw_polygon(const control &map_, const std::vector<vector3> &polygon_, const rv_color &color_);
        void disable_map_indicators(bool disableFriendly_, bool disableEnemy_, bool disableMines_, bool disablePing_);
        sqf_return_string get_player_id(const object &player_);
        sqf_return_string marker_channel(sqf_string_const_ref marker_);
        std::vector<float> marker_polyline(sqf_string_const_ref marker_);
        void set_marker_polyline(sqf_string_const_ref marker_, const std::vector<float> &polyline_);
        void set_marker_polyline_local(sqf_string_const_ref marker_, const std::vector<float> &polyline_);
        void set_marker_shadow(sqf_string_const_ref marker_, bool shadow_);
        void set_marker_shadow_local(sqf_string_const_ref marker_, bool shadow_);
        bool marker_shadow(sqf_string_const_ref marker_);
        float marker_draw_priority(sqf_string_const_ref marker_);
        void set_marker_draw_priority(sqf_string_const_ref marker_, float priority_);
    }  // namespace sqf
}  // namespace intercept
