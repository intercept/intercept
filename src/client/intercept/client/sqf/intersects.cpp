#include "intersects.hpp"
#include "client\pointers.hpp"


namespace intercept {
    namespace sqf {
        namespace __helpers {            
            intersect_surfaces_list __line_intersects_surfaces(game_value& intersects_value_) {
                game_data_array* intersects = ((game_data_array *)intersects_value_.data);

                // TODO do we have to free memory of our array elements?
                intersect_surfaces_list output;
                for (int i = 0; i < intersects->length; ++i) {
                    game_data_array* element = ((game_data_array *)intersects->data[i].data); // our element array

                    intersect_surfaces surfaces; // Our intersecting surfaces
                    game_data_array* position = ((game_data_array *)element->data[0].data); // finding the position
                    surfaces.intersectPosASL = vector3(); // the actual position where line intersects 1st surface
                    surfaces.intersectPosASL.x = ((game_data_number *)position[0].data)->number;
                    surfaces.intersectPosASL.y = ((game_data_number *)position[1].data)->number;
                    surfaces.intersectPosASL.z = ((game_data_number *)position[2].data)->number;

                    // translating rv string to std string
                    surfaces.surfaceNormal = ((game_data_string *)element->data[1].data)->get_string(); // a normal to the intersected surface

                    // translating objects
                    surfaces.intersectObject = std::make_shared<object_ptr>(element->data[2]); // the object the surface belongs to (could be proxy object)
                    surfaces.parentObject = std::make_shared<object_ptr>(element->data[3]); // the object proxy object belongs to (not always the same as intersect object)

                    output.push_back(std::make_shared<intersect_surfaces>(surfaces)); // Store the surfaces for our return
                }

                host::functions.free_value(&intersects_value_);
                return output;
            }
        }

        bool intersect(vector3 begin_pos_, vector3 end_pos_, const object& obj_, std::string lodname_) {
            game_value intersects_value = host::functions.invoke_raw_binary(
                client::__sqf::binary__intersect__array__array__ret__array, 
                game_value_vector3(begin_pos_), 
                game_value_vector3(end_pos_));

            bool intersects = ((game_data_bool *)intersects_value.data)->value;

            host::functions.free_value(&intersects_value);
            return intersects;
        }

        intersect_surfaces_list line_intersects_surfaces(vector3 begin_pos_asl_, vector3 end_pos_asl_) {
            game_value_array<2> array_input({
                game_value_vector3(begin_pos_asl_),
                game_value_vector3(end_pos_asl_)
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectssurfaces__array__ret__array, array_input);
            return __helpers::__line_intersects_surfaces(intersects_value);
        }

        intersect_surfaces_list line_intersects_surfaces(vector3 begin_pos_asl_, vector3 end_pos_asl_, const object& ignore_obj1_) {
            game_value_array<3> array_input({
                game_value_vector3(begin_pos_asl_),
                game_value_vector3(end_pos_asl_),
                ignore_obj1_->value
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectssurfaces__array__ret__array, array_input);
            return __helpers::__line_intersects_surfaces(intersects_value);
        }

        intersect_surfaces_list line_intersects_surfaces(vector3 begin_pos_asl_, vector3 end_pos_asl_, const object& ignore_obj1_, const object& ignore_obj2_, bool sort_mode_ = true, int max_results_ = 1, std::string lod1_ = "VIEW", std::string lod2_ = "FIRE") {
            game_value_array<8> array_input({
                game_value_vector3(begin_pos_asl_),
                game_value_vector3(end_pos_asl_),
                ignore_obj1_->value,
                ignore_obj2_->value,
                game_value_bool(sort_mode_),
                game_value_number(max_results_),
                game_value_string(lod1_),
                game_value_string(lod2_)
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectssurfaces__array__ret__array, array_input);
            return __helpers::__line_intersects_surfaces(intersects_value);
        }

        std::vector<object> line_intersects_with(vector3 begin_pos_, vector3 end_pos_, const object& ignore_obj1_, const object& ignore_obj2_, bool sort_by_distance_ = true) {
            game_value intersects_value;
            if (ignore_obj1_ != nullptr && ignore_obj2_ != nullptr) {
                game_value_array<5> array_input({
                    game_value_vector3(begin_pos_),
                    game_value_vector3(end_pos_),
                    ignore_obj1_->value,
                    ignore_obj1_->value,
                    game_value_bool(sort_by_distance_)
                });
                intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectswith__array__ret__array, array_input);
            }
            else {
                game_value_array<2> array_input({
                    game_value_vector3(begin_pos_),
                    game_value_vector3(end_pos_)
                });
                intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectswith__array__ret__array, array_input);
            }
            game_data_array* intersects = ((game_data_array *)intersects_value.data);

            std::vector<object> output;
            for (int i = 0; i < intersects->length; ++i) {
                output.push_back(std::make_shared<object_ptr>(intersects->data[i]));
            }
            host::functions.free_value(&intersects_value);
            return output;
        }

        bool terrain_intersect(vector3 begin_pos_, vector3 end_pos_) {
            game_value_array<2> array_input({
                game_value_vector3(begin_pos_),
                game_value_vector3(end_pos_)
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__terrainintersect__array__ret__bool, array_input);
            bool intersects = ((game_data_bool *)intersects_value.data)->value;

            host::functions.free_value(&intersects_value);
            return intersects;
        }

        bool terrain_intersect_asl(vector3 begin_pos_, vector3 end_pos_) {
            game_value_array<2> array_input({
                game_value_vector3(begin_pos_),
                game_value_vector3(end_pos_)
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__terrainintersectasl__array__ret__bool, array_input);
            bool intersects = ((game_data_bool *)intersects_value.data)->value;

            host::functions.free_value(&intersects_value);
            return intersects;
        }

        bool line_intersects(vector3 begin_position_, vector3 end_position_) {

            game_value_array<2> array_input({
                game_value_vector3(begin_position_),
                game_value_vector3(end_position_)
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersects__array__ret__bool, array_input);
            bool intersects = ((game_data_bool *)intersects_value.data)->value;

            host::functions.free_value(&intersects_value);
            return intersects;
        }

        bool line_intersects(vector3 begin_position_, vector3 end_position_, const object& ignore_obj_one_) {
            game_value_array<3> array_input({
                game_value_vector3(begin_position_),
                game_value_vector3(end_position_),
                ignore_obj_one_->value
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersects__array__ret__bool, array_input);
            bool intersects = ((game_data_bool *)intersects_value.data)->value;
            host::functions.free_value(&intersects_value);
            return intersects;
        }

        bool line_intersects(vector3 begin_position_, vector3 end_position_, const object& ignore_obj_one_, const object& ignore_obj_two_) {

            game_value_array<4> array_input({
                game_value_vector3(begin_position_),
                game_value_vector3(end_position_),
                ignore_obj_one_->value,
                ignore_obj_two_->value
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersects__array__ret__bool, array_input);
            bool intersects = ((game_data_bool *)intersects_value.data)->value;
            host::functions.free_value(&intersects_value);
            return intersects;
        }

        std::vector<object> line_intersects_objs(vector3 begin_position_, vector3 end_position_, const object& with_obj_, const object& ignore_obj_, bool sort_by_distance_, int flags_) {
            game_value_array<6> array_input({
                game_value_vector3(begin_position_),
                game_value_vector3(end_position_),
                with_obj_->value,
                ignore_obj_->value,
                game_value_bool(sort_by_distance_),
                game_value_number(flags_)
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectsobjs__array__ret__array, array_input);
            game_data_array* intersects = ((game_data_array *)intersects_value.data);

            std::vector<object> output;
            for (int i = 0; i < intersects->length; ++i) {
                output.push_back(std::make_shared<object_ptr>(intersects->data[i]));
            }
            host::functions.free_value(&intersects_value);
            return output;
        }

    }
}
