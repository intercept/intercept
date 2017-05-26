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
#include "shared.hpp"
#include "client/client.hpp"
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        /* - Markers - */

        std::string create_marker(const std::string &name_, const vector3 &pos_);
        std::string create_marker(const std::string &name_, const vector2 &pos_);
        std::string create_marker(const std::string &name_, const object &pos_);
        std::string create_marker_local(const std::string &name_, const vector3 &pos_);
        std::string create_marker_local(const std::string &name_, const vector2 &pos_);
        std::string create_marker_local(const std::string &name_, const object &pos_);

        void delete_marker(const std::string& value_);
        void delete_marker_local(const std::string& value_);

        void set_marker_size(const std::string& marker_, const vector2& size_);
        void set_marker_size_local(const std::string& marker_, const vector2& size_);
        void set_marker_type(const std::string& marker_, const std::string& type_);
        void set_marker_type_local(const std::string& marker_, const std::string& type_);
        void set_marker_text(const std::string& marker_, const std::string& text_);
        void set_marker_text_local(const std::string& marker_, const std::string& text_);
        void set_marker_shape(const std::string& marker_, const std::string& shape_);
        void set_marker_shape_local(const std::string& marker_, const std::string& shape_);
        void set_marker_pos(const std::string& marker_, const vector3& pos_);
        void set_marker_pos_local(const std::string& marker_, const vector3& pos_);
        void set_marker_pos(const std::string& marker_, const vector2& pos_);
        void set_marker_pos_local(const std::string& marker_, const vector2& pos_);
        void set_marker_brush(const std::string& marker_, const std::string& brush_);
        void set_marker_brush_local(const std::string& marker_, const std::string& brush_);
        void set_marker_color(const std::string& marker_, const std::string& color_);
        void set_marker_color_local(const std::string& marker_, const std::string& color_);
        void set_marker_alpha(const std::string& marker_, float alpha_);
        void set_marker_alpha_local(const std::string& marker_, float alpha_);
        void set_marker_dir(const std::string& marker_, float dir_);
        void set_marker_dir_local(const std::string& marker_, float dir_);

        float marker_alpha(const std::string& value_);
        float marker_dir(const std::string& value_);
        std::string marker_brush(const std::string& value_);
        std::string marker_color(const std::string& value_);
        std::string marker_shape(const std::string& value_);
        std::string marker_text(const std::string& value_);
        std::string marker_type(const std::string& value_);

        std::string get_marker_color(const std::string& value_);
        std::string get_marker_type(const std::string& value_);
        vector3 get_marker_pos(const std::string& value_);
        vector2 get_marker_size(const std::string& value_);

        std::vector<marker> all_map_markers();











        /* - Locations - */
        namespace __helpers {
            vector3 get_pos_loc(unary_function fnc_, const location & loc_);
        }
        void set_importance(const location &loc_, const float &value_);
        void set_side(const location &loc_, const side &side_);
        void set_position(const location &location_, const vector3 &position_);
        void delete_location(const location &loc_);
        void attach_object(const location& location_, const object& object_);
        bool is_null(const location& loc_);
        bool rectangular(const location& loc_);
        bool in(const vector3 &pos_, const location &loc_);
        float direction(const location &value_);
        float importance(const location &loc_);
        float distance(const location& start_, const location& end_);
        float distance(const location& start_, const vector3& end_);
        float distance(const vector3& start_, const location& end_);
        location nearest_location(const vector3& pos_, const std::string& location_class_);
        location nearest_location(const object& unit_, const std::string& location_class_);
        location nearest_location_with_dubbing(const vector3 &pos_);
        location nearest_location_with_dubbing(const object &obj_);
        object attached_object(const location &loc_);
        side get_side(const location &loc_);
        vector3 position(const location& loc_);
        vector2 size(const location &loc_);
        vector3 get_pos(const location & loc_);
        vector2 location_position(const location &loc_);
        std::vector<location> nearest_locations(const vector3& pos_, std::vector<std::string>& location_types_, float radius_);
        std::vector<location> nearest_locations(const vector3& pos_, std::vector<std::string>& location_types_, float radius_, const vector3& sort_position_);
        std::vector<location> nearest_locations(const object& unit_, std::vector<std::string>& location_types_, float radius_);
        std::vector<location> nearest_locations(const object& unit_, std::vector<std::string>& location_types_, float radius_, const vector3& sort_position_);
        std::vector<location> nearest_locations(const vector3 pos_, const std::vector<std::string> &loc_types_, float radius_);
        std::vector<location> nearest_locations(const vector3 pos_, const std::vector<std::string> &loc_types_, float radius_, const vector3 &sort_pos_);
        std::vector<location> nearest_locations(const vector3 pos_, const std::vector<std::string> &loc_types_, float radius_, const object &sort_obj_);
        std::vector<std::string> all_variables(const location &value_);
        std::string name(const location &loc_);
        std::string type(const location& loc_);
        game_value get_variable(const location & loc_, const std::string & var_name_);
        std::string class_name(const location &loc_);
        location create_location(const std::string &classname_, const vector3 &pos_, float size_x_, float size_y_);
        location create_location(const std::string &classname_, const vector2 & pos_, float size_x_, float size_y_);
        location create_location(const std::string &classname_, const object &obj_, float size_x_, float size_y_);
        location location_null();













        //Triggers

        struct rv_trigger_area {
            float x;
            float y;
            float angle;
            bool rectangle;
            float z; // since Arma 3 v1.59.135137

            rv_trigger_area(const game_value &ret_game_value_) :
                x(ret_game_value_[0]),
                y(ret_game_value_[1]),
                angle(ret_game_value_[2]),
                rectangle(ret_game_value_[3]),
                z(ret_game_value_[4]) {}
        };

        rv_trigger_area trigger_area(const object& trigger_);

        struct rv_trigger_timeout {
            float time_min;
            float time_mid;
            float time_max;
            bool interruptable;

            rv_trigger_timeout(const game_value &ret_game_value_) :
                time_min(ret_game_value_[0]),
                time_mid(ret_game_value_[1]),
                time_max(ret_game_value_[2]),
                interruptable(ret_game_value_[3]) {}
        };

        rv_trigger_timeout trigger_timeout(const object& trigger_);

        std::vector<object> list(const object& trigger_);
        void trigger_attach_object(const object &value0_, float value1_);
        void set_trigger_text(const object &value0_, const std::string& value1_);
        void set_trigger_type(const object &value0_, const std::string& value1_);
        bool trigger_activated(const object &value_);
        object trigger_attached_vehicle(const object &value_);
        std::string trigger_text(const object &value_);
        float trigger_timeout_current(const object &value_);
        std::string trigger_type(const object &value_);
        object create_trigger(const std::string &type_, const vector3 &pos_, bool make_global_ = true);
        object create_trigger(const std::string &type_, const object &pos_, bool make_global_ = true);

        void set_trigger_activation(const object &trigger_, const std::string &by_, const std::string &type_, bool repeating_);
        void set_trigger_area(const object &trigger_, float radius_x_, float radius_y_, float angle_, bool is_rectangle_, std::optional<float> radius_z_);
        void set_trigger_statements(const object &trigger_, const std::string &condition_, const std::string &activation_, const std::string &deactivation_);
        void set_trigger_timeout(const object &trigger_, float min_, float mid_, float max_, bool interruptable_);
        void synchronize_trigger(const object &trigger_, const std::vector<rv_waypoint> &waypoints_);
        void trigger_attach_vehicle(const object &trigger_, const std::vector<object> &objects_);


        //icons/draw
        void remove_draw_icon(const control &map_, const std::string &object_, const std::string &string_identifier);
        void remove_draw_links(const control &map_, const std::string &object_, const std::string &string_identifier);
        void set_draw_icon(const control &map_, const object &object_, const std::string &texture_, const rv_color &color_, const vector3 &offset_, float width_, float height_, float size_, float angle_, const std::string &identifier_, float shadow_, bool is_3d_, bool draw_line_, float priority_);
        void update_draw_icon(const control &map_, const std::string &object_, const std::string &string_identifier_, const rv_color &color_, const vector2 &offset_, float width_, float height_, bool maintain_size_, float angle_, int shadow_);
        void draw_arrow(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, const rv_color &color_);
        void draw_ellipse(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> center_, const vector2 &radius_, float angle_, const rv_color &color_, const std::string &fill_texture);
        void draw_line(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, const rv_color &color_);
        void draw_link(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, const std::string &param_type_, const std::string &line_type_, rv_color &color_);
        void draw_location(const control &map_, const location &location_);
        void draw_polygon(const control &map_, const std::vector<vector3> &polygon_, const rv_color &color_);

    }
}
