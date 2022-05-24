#include "position.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        /* Position */
        namespace __helpers {
            vector3 get_pos_obj(unary_function fnc_, const object &obj_) {
                return host::functions.invoke_raw_unary(fnc_, obj_);
            }
        }  // namespace __helpers

        vector3 get_pos(const object &obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getpos__object__ret__array, obj_);
        }

        vector3 get_pos_asl(const object &obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposasl__object__ret__array, obj_);
        }

        vector3 get_pos_atl(const object &obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposatl__object__ret__array, obj_);
        }

        vector3 get_pos_aslw(const object &obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposaslw__object__ret__array, obj_);
        }

        vector3 visible_position(const object &obj_) {
            return __helpers::get_pos_obj(__sqf::unary__visibleposition__object__ret__array, obj_);
        }

        vector3 visible_position_asl(const object &obj_) {
            return __helpers::get_pos_obj(__sqf::unary__visiblepositionasl__object__ret__array, obj_);
        }

        vector3 position(const object &obj_) {
            return __helpers::get_pos_obj(__sqf::unary__position__object__ret__array, obj_);
        }

        vector3 position_camera_to_world(const vector3 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__positioncameratoworld__array__ret__array, pos_);
        }

        vector3 get_pos_visual(const object &obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposvisual__object__ret__array, obj_);
        }
        vector3 get_pos_asl_visual(const object &obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposaslvisual__object__ret__array, obj_);
        }

        vector3 get_pos_atl_visual(const object &obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposatlvisual__object__ret__array, obj_);
        }

        vector3 aim_pos(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__aimpos__object__ret__array, obj_);
        }

        vector3 eye_pos(const object &object_) {
            return vector3(game_value(host::functions.invoke_raw_unary(__sqf::unary__eyepos__object__ret__array, object_)));
        }

        vector3 eye_direction(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__eyedirection__object__ret__array, unit_);
        }

        void set_pos(const object &obj_, const vector3 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpos__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_asl(const object &obj_, const vector3 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setposasl__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_asl2(const object &obj_, const vector3 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setposasl2__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_aslw(const object &obj_, const vector3 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setposaslw__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_atl(const object &obj_, const vector3 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setposatl__object__array__ret__nothing, obj_, pos_);
        }

        vector3 agl_to_asl(const vector3 &agl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__agltoasl__array__ret__array, agl_);
        }

        vector3 asl_to_agl(const vector3 &asl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__asltoagl__array__ret__array, asl_);
        }

        vector3 atl_to_asl(const vector3 &atl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__atltoasl__array__ret__array, atl_);
        }
        vector3 asl_to_atl(const vector3 &asl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__asltoatl__array__ret__array, asl_);
        }
        vector3 get_pos(const object &obj_, float distance_, float heading_) {
            game_value args({distance_,
                             heading_});

            return host::functions.invoke_raw_binary(__sqf::binary__getpos__object_array__array__ret__array, obj_, args);
        }

        vector3 get_pos(const vector3 &pos_, float distance_, float heading_) {
            game_value args({distance_,
                             heading_});

            return host::functions.invoke_raw_binary(__sqf::binary__getpos__object_array__array__ret__array, pos_, args);
        }

        vector3 get_rel_pos(const object &obj_, float distance_, float heading_) {
            game_value args({distance_,
                             heading_});

            return host::functions.invoke_raw_binary(__sqf::binary__getrelpos__object__array__ret__array, obj_, args);
        }

        vector3 get_rel_pos(const vector3 &pos_, float distance_, float heading_) {
            game_value args({distance_,
                             heading_});

            return host::functions.invoke_raw_binary(__sqf::binary__getrelpos__object__array__ret__array, pos_, args);
        }
        float get_rel_dir(const object &obj_, const object &pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getreldir__object__object_array__ret__scalar, obj_, pos_);
        }

        float get_rel_dir(const object &obj_, const vector3 &pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getreldir__object__object_array__ret__scalar, obj_, pos_);
        }
        void set_vector_up(const object &object_, const vector3 &vector_up_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvectorup__object__array__ret__nothing, object_, vector_up_);
        }

        void set_vector_dir_and_up(const object &object_, const vector3 &vector_dir_, const vector3 &vector_up_) {
            game_value vector({vector_dir_,
                               vector_up_});

            host::functions.invoke_raw_binary(__sqf::binary__setvectordirandup__object__array__ret__nothing, object_, vector);
        }

        void set_pos_world(const object &object_, const vector3 &position_) {
            host::functions.invoke_raw_binary(__sqf::binary__setposworld__object__array__ret__nothing, object_, position_);
        }
        vector3 get_pos_world(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getposworld__object__ret__array, unit_);
        }

        float get_terrain_height_asl(const vector3 &position_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getterrainheightasl__array__ret__scalar, position_);
        }

        float get_terrain_height_asl(const vector2 &position_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getterrainheightasl__array__ret__scalar, position_);
        }

        vector3 world_to_model(const object &object_, const vector3 &position_) {
            return host::functions.invoke_raw_binary(__sqf::binary__worldtomodel__object__array__ret__array, object_, position_);
        }

        vector3 world_to_model_visual(const object &object_, const vector3 &position_) {
            return host::functions.invoke_raw_binary(__sqf::binary__worldtomodelvisual__object__array__ret__array, object_, position_);
        }

        vector3 velocity_model_space(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__velocitymodelspace__object__ret__array, obj_);
        }

        vector3 vector_up_visual(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__vectorupvisual__object__ret__array, obj_);
        }

        vector3 vector_up(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__vectorup__object__ret__array, obj_);
        }
        vector3 model_to_world_visual(const object &model_, const vector3 &model_pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__modeltoworldvisual__object__array__ret__array, model_, model_pos_);
        }

        std::optional<vector2> world_to_screen(const vector3 &pos_agl_) {
            game_value result = host::functions.invoke_raw_unary(__sqf::unary__worldtoscreen__array__ret__array, pos_agl_);
            if (static_cast<game_data_array *>(result.data.get())->length() == 2)
                return game_value(result);
            return {};
        }
        void set_vector_dir(const object &obj_, const vector3 &vec_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvectordir__object__array__ret__nothing, obj_, vec_);
        }

        void set_velocity(const object &obj_, const vector3 &vel_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvelocity__object__array__ret__nothing, obj_, vel_);
        }
        vector3 velocity(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__velocity__object__ret__array, obj_);
        }

        float direction(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__direction__object__ret__scalar, value_);
        }

        vector3 vector_dir(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__vectordir__object__ret__array, obj_);
        }

        vector3 vector_dir_visual(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__vectordirvisual__object__ret__array, obj_);
        }

        vector3 selection_position(const object &obj_, sqf_string_const_ref selection_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__selectionposition__object__string__ret__array, obj_, selection_name_);
        }

        vector3 selection_position(const object &obj_, sqf_string_const_ref selection_name_, sqf_string_const_ref lod_) {
            return host::functions.invoke_raw_binary(__sqf::binary__selectionposition__object__array__ret__array, obj_, {selection_name_, lod_});
        }

        vector3 selection_position(const object &obj_, sqf_string_const_ref selection_name_, rv_selection_lods lod_) {
            game_value lod_name;
            switch (lod_) {
                case intercept::sqf::rv_selection_lods::Memory:
                    lod_name = "Memory"sv;
                    break;
                case intercept::sqf::rv_selection_lods::Geometry:
                    lod_name = "Geometry"sv;
                    break;
                case intercept::sqf::rv_selection_lods::FireGeometry:
                    lod_name = "FireGeometry"sv;
                    break;
                case intercept::sqf::rv_selection_lods::LandContact:
                    lod_name = "LandContact"sv;
                    break;
                case intercept::sqf::rv_selection_lods::HitPoints:
                    lod_name = "HitPoints"sv;
                    break;
                case intercept::sqf::rv_selection_lods::ViewGeometry:
                    lod_name = "ViewGeometry"sv;
                    break;
                default:
                    lod_name = ""sv;
                    break;
            }
            return host::functions.invoke_raw_binary(__sqf::binary__selectionposition__object__array__ret__array, obj_, {selection_name_, std::move(lod_name)});
        }
        
        vector3 selection_position(const object &obj_, sqf_string_const_ref selection_name_, float lod_res_) {
            return host::functions.invoke_raw_binary(__sqf::binary__selectionposition__object__array__ret__array, obj_, {selection_name_, lod_res_});
        }
        
        vector3 selection_position(const object &obj_, sqf_string_const_ref selection_name_, float lod_index_, bool is_visual_) {
            return host::functions.invoke_raw_unary(__sqf::unary__selectionposition__array__ret__array, {obj_, selection_name_, lod_index_, is_visual_} );
        }

        vector3 selection_position_avg(const object &obj_, sqf_string_const_ref selection_name_, sqf_string_const_ref lod_) {
            return host::functions.invoke_raw_binary(__sqf::binary__selectionposition__object__array__ret__array, obj_, {selection_name_, lod_, "AveragePoint"});
        }

        vector3 selection_position_avg(const object &obj_, sqf_string_const_ref selection_name_, rv_selection_lods lod_) {
            game_value lod_name;
            switch (lod_) {
                case intercept::sqf::rv_selection_lods::Memory:
                    lod_name = "Memory"sv;
                    break;
                case intercept::sqf::rv_selection_lods::Geometry:
                    lod_name = "Geometry"sv;
                    break;
                case intercept::sqf::rv_selection_lods::FireGeometry:
                    lod_name = "FireGeometry"sv;
                    break;
                case intercept::sqf::rv_selection_lods::LandContact:
                    lod_name = "LandContact"sv;
                    break;
                case intercept::sqf::rv_selection_lods::HitPoints:
                    lod_name = "HitPoints"sv;
                    break;
                case intercept::sqf::rv_selection_lods::ViewGeometry:
                    lod_name = "ViewGeometry"sv;
                    break;
                default:
                    lod_name = ""sv;
                    break;
            }
            return host::functions.invoke_raw_binary(__sqf::binary__selectionposition__object__array__ret__array, obj_, {selection_name_, std::move(lod_name), "AveragePoint"});
        }

        vector3 selection_position_avg(const object &obj_, sqf_string_const_ref selection_name_, float lod_res_) {
            return host::functions.invoke_raw_binary(__sqf::binary__selectionposition__object__array__ret__array, obj_, {selection_name_, lod_res_, "AveragePoint"});
        }

        vector3 selection_position_avg(const object &obj_, sqf_string_const_ref selection_name_, float lod_index_, bool is_visual_) {
            return host::functions.invoke_raw_unary(__sqf::unary__selectionposition__array__ret__array, {obj_, selection_name_, lod_index_, is_visual_, "AveragePoint"});
        }

        rv_bounding_box selection_position_bb(const object &obj_, sqf_string_const_ref selection_name_, sqf_string_const_ref lod_) {
            return rv_bounding_box(host::functions.invoke_raw_binary(__sqf::binary__selectionposition__object__array__ret__array, obj_, {selection_name_, lod_, "BoundingBox"}));
        }

        rv_bounding_box selection_position_bb(const object &obj_, sqf_string_const_ref selection_name_, rv_selection_lods lod_) {
            game_value lod_name;
            switch (lod_) {
                case intercept::sqf::rv_selection_lods::Memory:
                    lod_name = "Memory"sv;
                    break;
                case intercept::sqf::rv_selection_lods::Geometry:
                    lod_name = "Geometry"sv;
                    break;
                case intercept::sqf::rv_selection_lods::FireGeometry:
                    lod_name = "FireGeometry"sv;
                    break;
                case intercept::sqf::rv_selection_lods::LandContact:
                    lod_name = "LandContact"sv;
                    break;
                case intercept::sqf::rv_selection_lods::HitPoints:
                    lod_name = "HitPoints"sv;
                    break;
                case intercept::sqf::rv_selection_lods::ViewGeometry:
                    lod_name = "ViewGeometry"sv;
                    break;
                default:
                    lod_name = ""sv;
                    break;
            }
            return rv_bounding_box(host::functions.invoke_raw_binary(__sqf::binary__selectionposition__object__array__ret__array, obj_, {selection_name_, std::move(lod_name), "BoundingBox"}));
        }

        rv_bounding_box selection_position_bb(const object &obj_, sqf_string_const_ref selection_name_, float lod_res_) {
            return rv_bounding_box(host::functions.invoke_raw_binary(__sqf::binary__selectionposition__object__array__ret__array, obj_, {selection_name_, lod_res_, "BoundingBox"}));
        }

        rv_bounding_box selection_position_bb(const object &obj_, sqf_string_const_ref selection_name_, float lod_index_, bool is_visual_) {
            return rv_bounding_box(host::functions.invoke_raw_unary(__sqf::unary__selectionposition__array__ret__array, {obj_, selection_name_, lod_index_, is_visual_, "BoundingBox"}));
        }

        std::pair<vector3, vector3> selection_vector_dir_and_up(const object& obj_, sqf_string_const_ref selection_name_, rv_selection_lods lod_) {
            game_value lod_name;
            switch (lod_) {
                case intercept::sqf::rv_selection_lods::Memory:
                    lod_name = "Memory"sv;
                    break;
                case intercept::sqf::rv_selection_lods::Geometry:
                    lod_name = "Geometry"sv;
                    break;
                case intercept::sqf::rv_selection_lods::FireGeometry:
                    lod_name = "FireGeometry"sv;
                    break;
                case intercept::sqf::rv_selection_lods::LandContact:
                    lod_name = "LandContact"sv;
                    break;
                case intercept::sqf::rv_selection_lods::HitPoints:
                    lod_name = "HitPoints"sv;
                    break;
                case intercept::sqf::rv_selection_lods::ViewGeometry:
                    lod_name = "ViewGeometry"sv;
                    break;
                default:
                    lod_name = ""sv;
                    break;
            }
            game_value gv = host::functions.invoke_raw_binary(__sqf::binary__selectionvectordirandup__object__array__ret__array, obj_, {selection_name_, std::move(lod_name)});
            return {gv[0], gv[1]};
        }

        std::pair<vector3, vector3> selection_vector_dir_and_up(const object &obj_, sqf_string_const_ref selection_name_, float lod_index_) {
            game_value gv = host::functions.invoke_raw_binary(__sqf::binary__selectionvectordirandup__object__array__ret__array, obj_, {selection_name_, lod_index_});
            return {gv[0], gv[1]};
        }

        rv_bounding_box bounding_box(const object &model_) {
            return rv_bounding_box(host::functions.invoke_raw_unary(__sqf::unary__boundingbox__object__ret__array, model_));
        }

        rv_bounding_box bounding_box_real(const object &model_) {
            return rv_bounding_box(host::functions.invoke_raw_unary(__sqf::unary__boundingboxreal__object__ret__array, model_));
        }

        rv_bounding_box bounding_box(bounding_box_clipping_type type_, const object &model_) {
            return rv_bounding_box(host::functions.invoke_raw_binary(__sqf::binary__boundingbox__scalar__object__ret__array, static_cast<int>(type_), model_));
        }
        rv_bounding_box bounding_box_real(bounding_box_clipping_type type_, const object &model_) {
            return rv_bounding_box(host::functions.invoke_raw_binary(__sqf::binary__boundingboxreal__scalar__object__ret__array, static_cast<int>(type_), model_));
        }

        vector3 bounding_center(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__boundingcenter__object__ret__array, obj_);
        }

        float get_dir(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getdir__object__ret__scalar, value_);
        }

        float get_dir_visual(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getdirvisual__object__ret__scalar, value_);
        }

        void set_dir(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setdir__object__scalar__ret__nothing, value0_, value1_);
        }

        float get_dir(t_sqf_in_area_position from_, t_sqf_in_area_position to_) {
            game_value from;
            game_value to;

            if (from_.index() == 0) from = std::get<0>(from_).get();
            if (from_.index() == 1) from = std::get<1>(from_).get();
            if (to_.index() == 0) to = std::get<0>(to_).get();
            if (to_.index() == 1) to = std::get<1>(to_).get();

            return host::functions.invoke_raw_binary(__sqf::binary__getdir__object_array__object_array__ret__scalar, from, to);
        }

        void set_direction(const location &location_, float direction_) {
            host::functions.invoke_raw_binary(__sqf::binary__setdirection__location__scalar__ret__nothing, location_, direction_);
        }

        vector3 weapon_direction(const object &unit_, sqf_string_const_ref weapon_class_) {
            return host::functions.invoke_raw_binary(__sqf::binary__weapondirection__object__string__ret__array, unit_, weapon_class_);
        }

        void set_velocity_model_space(const object &vehicle_, const vector3 &relative_direction_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvelocitymodelspace__object__array__ret__nothing, vehicle_, relative_direction_);
        }

        void set_velocity_transformation(const object &object_, const vector3 &position1_, const vector3 &position2_, const vector3 &velocity1_, const vector3 &velocity2_, const vector3 &direction1_, const vector3 &direction2_, const vector3 &up1_, const vector3 &up2_, float time_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvelocitytransformation__object__array__ret__nothing, object_, {position1_, position2_, velocity1_, velocity2_, direction1_, direction2_, up1_, up2_, time_});
        }

        vector3 unit_aim_position(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__unitaimposition__object__ret__array, unit_);
        }

        vector3 unit_aim_position_visual(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__unitaimpositionvisual__object__ret__array, unit_);
        }
        vector3 model_to_world_visual_world(const object &object_, const vector3 &model_pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__modeltoworldvisualworld__object__array__ret__array, object_, model_pos_);
        }

        vector3 model_to_world_world(const object &object_, const vector3 &model_pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__modeltoworldworld__object__array__ret__array, object_, model_pos_);
        }
        vector3 screen_to_world(const vector2 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__screentoworld__array__ret__array, pos_);
        }
        vector3 model_to_world(const object &object_, const vector3 &offset_) {
            return host::functions.invoke_raw_binary(__sqf::binary__modeltoworld__object__array__ret__array, object_, offset_);
        }
        bool in_area(t_sqf_in_area_position position_, const object &trigger_) {
            game_value param_left;

            switch (position_.index()) {
                case 0: param_left = std::get<0>(position_).get(); break;
                case 1: param_left = std::get<1>(position_).get(); break;
                case 2: param_left = std::get<2>(position_).get(); break;
            }

            return host::functions.invoke_raw_binary(__sqf::binary__inarea__object_array__object__ret__bool, param_left, trigger_);
        }

        bool in_area(t_sqf_in_area_position position_, sqf_string_const_ref marker_) {
            game_value param_left;

            switch (position_.index()) {
                case 0: param_left = std::get<0>(position_).get(); break;
                case 1: param_left = std::get<1>(position_).get(); break;
                case 2: param_left = std::get<2>(position_).get(); break;
            }

            return host::functions.invoke_raw_binary(__sqf::binary__inarea__object_array__string__ret__bool, param_left, marker_);
        }

        bool in_area(t_sqf_in_area_position position_, t_sqf_in_area_position center_, float radius_x_, float radius_y_, float angle_, bool is_rectangle_, std::optional<float> radius_z_) {
            game_value param_left;
            auto_array<game_value> params_right;

            switch (position_.index()) {
                case 0: param_left = std::get<0>(position_).get(); break;
                case 1: param_left = std::get<1>(position_).get(); break;
                case 2: param_left = std::get<2>(position_).get(); break;
            }

            switch (center_.index()) {
                case 0: params_right.push_back(std::get<0>(center_).get()); break;
                case 1: params_right.push_back(std::get<1>(center_).get()); break;
                case 2: params_right.push_back(std::get<2>(center_).get()); break;
            }

            params_right.push_back(radius_x_);
            params_right.push_back(radius_y_);
            params_right.push_back(angle_);
            params_right.push_back(is_rectangle_);

            if (radius_z_.has_value()) params_right.push_back(*radius_z_);

            return host::functions.invoke_raw_binary(__sqf::binary__inarea__object_array__array__ret__bool, param_left, std::move(params_right));
        }

        bool in_area(const object &object_, const location &location_) {
            return host::functions.invoke_raw_binary(__sqf::binary__inarea__object__location__ret__bool, object_, location_);
        }

        bool in_area(t_sqf_in_area_position position_, const location &location_) {
            game_value param_left;

            switch (position_.index()) {
                case 0: param_left = std::get<0>(position_).get(); break;
                case 1: param_left = std::get<1>(position_).get(); break;
            }

            return host::functions.invoke_raw_binary(__sqf::binary__inarea__array__location__ret__bool, param_left, location_);
        }

        bool in_area_array(t_sqf_in_area_position_array position_, const object &trigger_) {
            game_value param_left;

            switch (position_.index()) {
                case 0: param_left = std::move(auto_array<game_value>({std::get<0>(position_).get().begin(), std::get<0>(position_).get().end()})); break;
                case 1: param_left = std::move(auto_array<game_value>({std::get<1>(position_).get().begin(), std::get<1>(position_).get().end()})); break;
                case 2: param_left = std::move(auto_array<game_value>({std::get<2>(position_).get().begin(), std::get<2>(position_).get().end()})); break;
            }

            return host::functions.invoke_raw_binary(__sqf::binary__inareaarray__array__object__ret__array, param_left, trigger_);
        }

        bool in_area_array(t_sqf_in_area_position_array position_, sqf_string_const_ref marker_) {
            game_value param_left;

            switch (position_.index()) {
                case 0: param_left = std::move(auto_array<game_value>({std::get<0>(position_).get().begin(), std::get<0>(position_).get().end()})); break;
                case 1: param_left = std::move(auto_array<game_value>({std::get<1>(position_).get().begin(), std::get<1>(position_).get().end()})); break;
                case 2: param_left = std::move(auto_array<game_value>({std::get<2>(position_).get().begin(), std::get<2>(position_).get().end()})); break;
            }

            return host::functions.invoke_raw_binary(__sqf::binary__inareaarray__array__string__ret__array, param_left, marker_);
        }

        bool in_area_array(t_sqf_in_area_position_array position_, t_sqf_in_area_position center_, float radius_x_, float radius_y_, float angle_, bool is_rectangle_, std::optional<float> radius_z_) {
            game_value param_left;
            auto_array<game_value> params_right;

            switch (position_.index()) {
                case 0: param_left = std::move(auto_array<game_value>({std::get<0>(position_).get().begin(), std::get<0>(position_).get().end()})); break;
                case 1: param_left = std::move(auto_array<game_value>({std::get<1>(position_).get().begin(), std::get<1>(position_).get().end()})); break;
                case 2: param_left = std::move(auto_array<game_value>({std::get<2>(position_).get().begin(), std::get<2>(position_).get().end()})); break;
            }

            switch (center_.index()) {
                case 0: params_right.push_back(std::get<0>(center_).get()); break;
                case 1: params_right.push_back(std::get<1>(center_).get()); break;
                case 2: params_right.push_back(std::get<2>(center_).get()); break;
            }

            params_right.push_back(radius_x_);
            params_right.push_back(radius_y_);
            params_right.push_back(angle_);
            params_right.push_back(is_rectangle_);

            if (radius_z_.has_value()) params_right.push_back(*radius_z_);

            return host::functions.invoke_raw_binary(__sqf::binary__inareaarray__array__array__ret__array, param_left, std::move(params_right));
        }

        bool in_area_array(t_sqf_in_area_position_array position_, const location &location_) {
            game_value param_left;

            switch (position_.index()) {
                case 0: param_left = std::move(auto_array<game_value>({std::get<0>(position_).get().begin(), std::get<0>(position_).get().end()})); break;
                case 1: param_left = std::move(auto_array<game_value>({std::get<1>(position_).get().begin(), std::get<1>(position_).get().end()})); break;
                case 2: param_left = std::move(auto_array<game_value>({std::get<2>(position_).get().begin(), std::get<2>(position_).get().end()})); break;
            }

            return host::functions.invoke_raw_binary(__sqf::binary__inareaarray__array__location__ret__array, param_left, location_);
        }
        std::vector<vector3> is_flat_empty(const vector3 &position_, float min_distance_, float max_gradient_, float max_gradient_radius_, float over_land_or_water_, bool shore_line_, const object &ignore_object_) {
            game_value params_right({min_distance_,
                                     max_gradient_,
                                     max_gradient_radius_,
                                     over_land_or_water_,
                                     shore_line_,
                                     ignore_object_});

            return __helpers::__convert_to_vector<vector3>(host::functions.invoke_raw_binary(__sqf::binary__isflatempty__array__array__ret__array, position_, params_right));
        }

        vector3 find_empty_position(std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> center_, float min_distance_, float max_distance_, std::optional<std::string> vehicle_type_) {
            auto_array<game_value> params_right({min_distance_,
                                                 max_distance_});

            if (vehicle_type_.has_value()) params_right.push_back(*vehicle_type_);

            if (center_.index() == 0) {
                return host::functions.invoke_raw_binary(__sqf::binary__findemptyposition__array__array__ret__array, std::get<0>(center_).get(), std::move(params_right));
            }
            return host::functions.invoke_raw_binary(__sqf::binary__findemptyposition__array__array__ret__array, std::get<1>(center_).get(), std::move(params_right));
        }

        bool find_empty_position_ready(std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>> center_, float radius_, float max_distance_) {
            game_value params_right({radius_,
                                     max_distance_});

            if (center_.index() == 0) {
                return host::functions.invoke_raw_binary(__sqf::binary__findemptypositionready__array__array__ret__bool, std::get<0>(center_).get(), params_right);
            }
            return host::functions.invoke_raw_binary(__sqf::binary__findemptypositionready__array__array__ret__bool, std::get<1>(center_).get(), params_right);
        }

        float distance_2d(std::variant<object, vector3> start_, std::variant<object, vector3> end_) {
            game_value from, to;
            switch (start_.index()) {
                case 0: from = (std::get<object>(start_)); break;
                case 1: from = (std::get<vector3>(start_)); break;
            }
            switch (end_.index()) {
                case 0: to = (std::get<object>(start_)); break;
                case 1: to = (std::get<vector3>(start_)); break;
            }
            return host::functions.invoke_raw_binary(__sqf::binary__distance2d__object_array__object_array__ret__scalar, from, to);
        }

        float distance_sqr(std::variant<object, vector3, location> start_, std::variant<object, vector3, location> end_) {
            game_value from, to;
            switch (start_.index()) {
                case 0: from = (std::get<object>(start_)); break;
                case 1: from = (std::get<vector3>(start_)); break;
                case 2: from = (std::get<location>(start_)); break;
            }
            switch (end_.index()) {
                case 0: to = (std::get<object>(end_)); break;
                case 1: to = (std::get<vector3>(end_)); break;
                case 2: to = (std::get<location>(end_)); break;
            }
            if (start_.index() == 2 && end_.index() == 2)
                return host::functions.invoke_raw_binary(__sqf::binary__distancesqr__location__location__ret__scalar, from, to);
            else if (start_.index() == 2 && end_.index() == 1)
                return host::functions.invoke_raw_binary(__sqf::binary__distancesqr__location__array__ret__scalar, from, to);
            else if (start_.index() == 1 && end_.index() == 2)
                return host::functions.invoke_raw_binary(__sqf::binary__distancesqr__array__location__ret__scalar, from, to);
            else if (start_.index() == 0 && end_.index() == 2)  //object->location
                return host::functions.invoke_raw_binary(__sqf::binary__distancesqr__array__location__ret__scalar, position(std::get<object>(start_)), to);
            else if (start_.index() == 2 && end_.index() == 0)  //location->object
                return host::functions.invoke_raw_binary(__sqf::binary__distancesqr__location__array__ret__scalar, from, position(std::get<object>(end_)));
            return host::functions.invoke_raw_binary(__sqf::binary__distancesqr__object_array__object_array__ret__scalar, from, to);
        }

        std::vector<object> near_entities(const object &position, sqf_string_list_const_ref types_, float range_) {
            auto_array<game_value> types(types_.begin(), types_.end());

            game_value args({std::move(types),
                             range_});

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__nearentities__object_array__scalar_array__ret__array, position, args));
        }

        std::vector<object> near_entities(const vector3 &pos_agl_, sqf_string_list_const_ref types_, float range_) {
            auto_array<game_value> types(types_.begin(), types_.end());

            game_value args({std::move(types),
                             range_});

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__nearentities__object_array__scalar_array__ret__array, pos_agl_, args));
        }

        std::vector<object> near_entities(const object &position, sqf_string_const_ref type_, float range_) {
            game_value args({std::move(type_),
                             range_});

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__nearentities__object_array__scalar_array__ret__array, position, args));
        }

        std::vector<object> near_entities(const vector3 &pos_agl_, sqf_string_const_ref type_, float range_) {
            game_value args({std::move(type_),
                             range_});

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_binary(__sqf::binary__nearentities__object_array__scalar_array__ret__array, pos_agl_, args));
        }

        float distance(object start_, vector3 end_) {
            return host::functions.invoke_raw_binary(__sqf::binary__distance__object_array__object_array__ret__scalar, start_, end_);
        }
        float distance(object start_, object end_) {
            return host::functions.invoke_raw_binary(__sqf::binary__distance__object_array__object_array__ret__scalar, start_, end_);
        }
        float distance(vector3 start_, vector3 end_) {
            return host::functions.invoke_raw_binary(__sqf::binary__distance__object_array__object_array__ret__scalar, start_, end_);
        }
        float distance(vector3 start_, object end_) {
            return host::functions.invoke_raw_binary(__sqf::binary__distance__object_array__object_array__ret__scalar, start_, end_);
        }

        bool set_vehicle_position(const object &object_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, const object> position_, sqf_string_list_const_ref markers_, float placement_radius_, std::optional<std::string> special_) {
            auto_array<game_value> params_right;

            switch (position_.index()) {
                case 0: params_right.emplace_back(std::move(std::get<0>(position_).get())); break;
                case 1: params_right.emplace_back(std::move(std::get<1>(position_).get())); break;
                case 2: params_right.emplace_back(std::move(std::get<2>(position_))); break;
            }

            params_right.push_back(std::move(auto_array<game_value>(markers_.begin(), markers_.end())));
            params_right.push_back(placement_radius_);

            if (special_.has_value()) params_right.push_back(*special_);

            return host::functions.invoke_raw_binary(__sqf::binary__setvehicleposition__object__array__ret__bool, object_, std::move(params_right));
        }
        vector3 building_exit(const object &building_, int index_) {
            return host::functions.invoke_raw_binary(__sqf::binary__buildingexit__object__scalar__ret__array, building_, index_);
        }

        std::vector<vector3> building_pos(const object &building_, int index_) {
            if (index_ > -1) {
                return {vector3(host::functions.invoke_raw_binary(__sqf::binary__buildingpos__object__scalar__ret__array, building_, static_cast<float>(index_)))};
            } else {
                return __helpers::__convert_to_vector<vector3>(host::functions.invoke_raw_binary(__sqf::binary__buildingpos__object__scalar__ret__array, building_, static_cast<float>(index_)));
            }
        }

        vector3 vector_model_to_world(const object &object_, const vector3 &modelDir_) {
            return host::functions.invoke_raw_binary(__sqf::binary__vectormodeltoworld__object__array__ret__array, object_, modelDir_);
        }
        vector3 vector_model_to_world_visual(const object &object_, const vector3 &modelDir_) {
            return host::functions.invoke_raw_binary(__sqf::binary__vectormodeltoworldvisual__object__array__ret__array, object_, modelDir_);
        }
        vector3 vector_world_to_model(const object &object_, const vector3 &worldDir_) {
            return host::functions.invoke_raw_binary(__sqf::binary__vectorworldtomodel__object__array__ret__array, object_, worldDir_);
        }
        vector3 vector_world_to_model_visual(const object &object_, const vector3 &worldDir_) {
            return host::functions.invoke_raw_binary(__sqf::binary__vectorworldtomodelvisual__object__array__ret__array, object_, worldDir_);
        }

        bool in_polygon(const vector3 &position_, const std::vector<vector3> &polygon_) {
            auto_array<game_value> polygon({polygon_.begin(), polygon_.end()});

            return host::functions.invoke_raw_binary(__sqf::binary__inpolygon__array__array__ret__bool, position_, std::move(polygon));
        }

        vector3 get_pos_world_visual(const object &object_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getposworldvisual__object__ret__array, object_);
        }

    }  // namespace sqf
}  // namespace intercept
