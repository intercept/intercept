/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Position functions.

These are used to get and set the position of various objects and other things
in the game world.
This includes everything defining an Objects Position in the world (Position, direction, velocity)
<
https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        /* Position */
        namespace __helpers {
            vector3 get_pos_obj(unary_function fnc_, const object &obj_);
        }

        vector3 get_pos(const object &obj_);
        vector3 get_pos_asl(const object &obj_);
        vector3 get_pos_atl(const object &obj_);
        vector3 get_pos_aslw(const object &obj_);
        vector3 visible_position(const object &obj_);
        vector3 visible_position_asl(const object &obj_);
        vector3 position(const object &obj_);
        vector3 position_camera_to_world(const vector3 &pos_);
        vector3 get_pos_visual(const object &obj_);
        vector3 get_pos_asl_visual(const object &obj_);
        vector3 get_pos_atl_visual(const object &obj_);
        vector3 aim_pos(const object &obj_);

        vector3 eye_pos(const object &object_);
        vector3 eye_direction(const object &unit_);

        void set_pos(const object &obj_, const vector3 &pos_);
        void set_pos_asl(const object &obj_, const vector3 &pos_);
        void set_pos_asl2(const object &obj_, const vector3 &pos_);
        void set_pos_aslw(const object &obj_, const vector3 &pos_);
        void set_pos_atl(const object &obj_, const vector3 &pos_);

        /////////////////////////////////////* Coordinate converters */
        vector3 agl_to_asl(const vector3 &agl_);
        vector3 asl_to_agl(const vector3 &asl_);
        vector3 atl_to_asl(const vector3 &atl_);
        vector3 asl_to_atl(const vector3 &asl_);

        vector3 get_pos(const object &obj_, float distance_, float heading_);
        vector3 get_pos(const vector3 &pos_, float distance_, float heading_);
        vector3 get_rel_pos(const object &obj_, float distance_, float heading_);
        vector3 get_rel_pos(const vector3 &pos_, float distance_, float heading_);
        float get_rel_dir(const object &obj_, const object &pos_);
        float get_rel_dir(const object &obj_, const vector3 &pos_);

        void set_vector_up(const object &object_, const vector3 &vector_up_);
        void set_vector_dir_and_up(const object &object_, const vector3 &vector_dir_, const vector3 &vector_up_);

        void set_pos_world(const object &object_, const vector3 &position_);
        vector3 get_pos_world(const object &unit_);
        float get_terrain_height_asl(vector3 position_);

        vector3 world_to_model(const object &object_, const vector3 &position_);
        vector3 world_to_model_visual(const object &object_, const vector3 &position_);

        vector3 velocity_model_space(const object &obj_);
        vector3 vector_up_visual(const object &obj_);
        vector3 vector_up(const object &obj_);

        vector3 model_to_world_visual(const object &model_, const vector3 &model_pos_);

        std::optional<vector2> world_to_screen(const vector3 &pos_agl_);

        void set_vector_dir(const object &obj_, const vector3 &vec_);
        void set_velocity(const object &obj_, const vector3 &vel_);
        vector3 velocity(const object &obj_);
        float direction(const object &value_);

        vector3 vector_dir(const object &obj_);
        vector3 vector_dir_visual(const object &obj_);
        vector3 selection_positon(const object &obj_, sqf_string_const_ref selection_name_);

        struct rv_bounding_box {
            vector3 min;
            vector3 max;
        };

        rv_bounding_box bounding_box(const object &model_);
        rv_bounding_box bounding_box_real(const object &model_);
        vector3 bounding_center(const object &obj_);
        void set_dir(const object &value0_, float value1_);
        float get_dir(t_sqf_in_area_position from_, t_sqf_in_area_position to_);
        void set_direction(const location &location_, float direction_);
        void set_velocity_model_space(const object &vehicle_, const vector3 &relative_direction_);
        void set_velocity_transformation(const object &object_, const vector3 &position1_, const vector3 &position2_, const vector3 &velocity1_, const vector3 &velocity2_, const vector3 &direction1_, const vector3 &direction2_, const vector3 &up1_, const vector3 &up2_, float time_);
        vector3 weapon_direction(const object &unit_, sqf_string_const_ref weapon_class_);
        float get_dir(const object &value_);
        float get_dir_visual(const object &value_);
        vector3 unit_aim_position(const object &unit_);
        vector3 unit_aim_position_visual(const object &unit_);

        //position
        vector3 model_to_world_visual_world(const object &object_, vector3 model_pos_);
        vector3 model_to_world_world(const object &object_, vector3 model_pos_);

        vector3 screen_to_world(const vector2 &pos_);
        vector3 model_to_world(const object &object_, const vector3 &offset_);
        bool in_area(t_sqf_in_area_position position_, const object &trigger_);
        bool in_area(t_sqf_in_area_position position_, sqf_string_const_ref marker_);
        bool in_area(t_sqf_in_area_position position_, t_sqf_in_area_position center_, float radius_x_, float radius_y_, float angle_, bool is_rectangle_, std::optional<float> radius_z_);
        bool in_area(const object &object_, const location &location_);
        bool in_area(t_sqf_in_area_position position_, const location &location_);
        typedef std::variant<std::reference_wrapper<const std::vector<object>>, std::reference_wrapper<const std::vector<vector2>>, std::reference_wrapper<const std::vector<vector3>>> t_sqf_in_area_position_array;
        bool in_area_array(t_sqf_in_area_position_array position_, const object &trigger_);
        bool in_area_array(t_sqf_in_area_position_array position_, sqf_string_const_ref marker_);
        bool in_area_array(t_sqf_in_area_position_array position_, t_sqf_in_area_position center_, float radius_x_, float radius_y_, float angle_, bool is_rectangle_, std::optional<float> radius_z_);
        bool in_area_array(t_sqf_in_area_position_array position_, const location &location_);
        std::vector<vector3> is_flat_empty(const vector3 &position_, float min_distance_, float max_gradient_, float max_gradient_radius_, float over_land_or_water, bool shore_line_, const object &ignore_object_);
        bool in_polygon(const vector3 &position_, const std::vector<vector3> &polygon_);
        //#Categorize are these two really position category? Sounds more worldish
        vector3 find_empty_position(std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> center_, float min_distance_, float max_distance_, std::optional<std::string> vehicle_type_);
        bool find_empty_position_ready(std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> center_, float radius_, float max_distance_);

        float distance_2d(std::variant<object, vector3> start_, std::variant<object, vector3> end_);
        float distance_sqr(std::variant<object, vector3, location> start_, std::variant<object, vector3, location> end_);
        //#Categorize is this really position category? Sounds more worldish
        std::vector<object> near_entities(const vector3 &pos_agl_, sqf_string_list_const_ref types_, float range_);
        float distance(object start_, vector3 end_);
        float distance(object start_, object end_);
        float distance(vector3 start_, vector3 end_);
        float distance(vector3 start_, object end_);
        bool set_vehicle_position(const object &object_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, const object> position_, sqf_string_list_const_ref markers_, float placement_radius_, std::optional<std::string> special_);
        vector3 building_exit(const object &building_, int index_);
        
        /*
            Be aware! This function always returns a vector of positions.
            This is unlike the documentation in the wiki!
            if the index given is > -1 is returns a vector with a single position in it
        */
        std::vector<vector3> building_pos(const object &building_, int index_);

        vector3 vector_model_to_world(const object &object_, vector3 modelDir_);
        vector3 vector_model_to_world_visual(const object &object_, vector3 modelDir_);
        vector3 vector_world_to_model(const object &object_, vector3 worldDir_);
        vector3 vector_world_to_model_visual(const object &object_, vector3 worldDir_);



    }  // namespace sqf
}  // namespace intercept
