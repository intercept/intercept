#include "intersects.hpp"
#include "client\pointers.hpp"


namespace intercept {
    namespace sqf {
        namespace __helpers {
            intersect_surfaces_list __line_intersects_surfaces(const game_value& intersects_value_) {
                intersect_surfaces_list output;
                output.reserve(intersects_value_.length());
                for (uint32_t i = 0; i < intersects_value_.length(); ++i) {
                    game_value element = intersects_value_[i];
                    intersect_surfaces surfaces; // Our intersecting surfaces
                    surfaces.intersect_pos_asl = element[0]; // the actual position where line intersects 1st surface

                    surfaces.surface_normal = element[1]; // a normal to the intersected surface

                    // translating objects
                    surfaces.intersect_object = element[2]; // the object the surface belongs to (could be proxy object)
                    surfaces.parent_object = element[3]; // the object proxy object belongs to (not always the same as intersect object)

                    output.push_back(surfaces); // Store the surfaces for our return
                }
                return output;
            }
        }

        bool intersect(const object& obj_, const std::string &lodname_, const vector3 &begin_pos_, const vector3 &end_pos_) {
            std::vector<game_value> params1{
                obj_,
                lodname_
            };
            std::vector<game_value> params2{
                begin_pos_,
                end_pos_
            };

            return game_value(host::functions.invoke_raw_binary(client::__sqf::binary__intersect__array__array__ret__array, params1, params2));
        }

        intersect_surfaces_list line_intersects_surfaces(const vector3 &begin_pos_asl_, const vector3 &end_pos_asl_) {
            game_value array_input({
                begin_pos_asl_,
                end_pos_asl_
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectssurfaces__array__ret__array, array_input);
            return __helpers::__line_intersects_surfaces(intersects_value);
        }

        intersect_surfaces_list line_intersects_surfaces(const vector3 &begin_pos_asl_, const vector3 &end_pos_asl_, const object &ignore_obj1_) {
            game_value array_input({
                begin_pos_asl_,
                end_pos_asl_,
                ignore_obj1_
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectssurfaces__array__ret__array, array_input);
            return __helpers::__line_intersects_surfaces(intersects_value);
        }

        intersect_surfaces_list line_intersects_surfaces(const vector3 &begin_pos_asl_, const vector3 &end_pos_asl_, const object & ignore_obj1_, const object & ignore_obj2_, bool sort_mode_, int max_results_, const std::string &lod1_, const std::string &lod2_) {
            game_value array_input = game_value({
                begin_pos_asl_,
                end_pos_asl_,
                ignore_obj1_,
                ignore_obj2_,
                sort_mode_,
                (float)max_results_,
                lod1_,
                lod2_
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectssurfaces__array__ret__array, array_input);
            return __helpers::__line_intersects_surfaces(intersects_value);
        }

        std::vector<object> line_intersects_with(const vector3 &begin_pos_, const vector3 &end_pos_, bool sort_by_distance_) {
            game_value array_input({
                begin_pos_,
                end_pos_,
                game_value(),
                game_value(),
                sort_by_distance_
            });
            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectswith__array__ret__array, array_input);

            game_data_array* intersects = static_cast<game_data_array*>(intersects_value.data.getRef());

            std::vector<object> output;
            for (uint32_t i = 0; i < intersects->length; ++i) {
                output.push_back(object(intersects->data[i]));
            }

            return output;
        }

        std::vector<object> line_intersects_with(const vector3 &begin_pos_, const vector3 &end_pos_, bool sort_by_distance_, const object & ignore_obj_one_) {
            game_value array_input({
                begin_pos_,
                end_pos_,
                ignore_obj_one_,
                game_value(),
                sort_by_distance_
            });
            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectswith__array__ret__array, array_input);

            game_data_array* intersects = static_cast<game_data_array*>(intersects_value.data.getRef());

            std::vector<object> output;
            for (uint32_t i = 0; i < intersects->length; ++i) {
                output.push_back(object(intersects->data[i]));
            }

            return output;
        }

        std::vector<object> line_intersects_with(const vector3 &begin_pos_, const vector3 &end_pos_, bool sort_by_distance_, const object & ignore_obj_one_, const object & ignore_obj_two_) {
            game_value array_input({
                begin_pos_,
                end_pos_,
                ignore_obj_one_,
                ignore_obj_two_,
                sort_by_distance_
            });
            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectswith__array__ret__array, array_input);

            game_data_array* intersects = static_cast<game_data_array*>(intersects_value.data.getRef());

            std::vector<object> output;
            for (uint32_t i = 0; i < intersects->length; ++i) {
                output.push_back(object(intersects->data[i]));
            }

            return output;
        }

        bool terrain_intersect(const vector3 &begin_pos_, const vector3 &end_pos_) {
            game_value array_input({
                begin_pos_,
                end_pos_
            });

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__terrainintersect__array__ret__bool, array_input));
        }

        bool terrain_intersect_asl(const vector3 &begin_pos_, const vector3 &end_pos_) {
            game_value array_input({
                begin_pos_,
                end_pos_
            });
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__terrainintersectasl__array__ret__bool, array_input));
        }

        bool line_intersects(const vector3 &begin_position_, const vector3 &end_position_) {

            game_value array_input({
                begin_position_,
                end_position_
            });
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lineintersects__array__ret__bool, array_input));
        }

        bool line_intersects(const vector3 &begin_position_, const vector3 &end_position_, const object & ignore_obj_one_) {
            game_value array_input({
                begin_position_,
                end_position_,
                ignore_obj_one_
            });
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lineintersects__array__ret__bool, array_input));
        }

        bool line_intersects(const vector3 &begin_position_, const vector3 &end_position_, const object & ignore_obj_one_, const object & ignore_obj_two_) {

            game_value array_input({
                begin_position_,
                end_position_,
                ignore_obj_one_,
                ignore_obj_two_
            });
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__lineintersects__array__ret__bool, array_input));
        }

        std::vector<object> line_intersects_objs(const vector3 &begin_position_, const vector3 &end_position_, const object & with_obj_, const object & ignore_obj_, bool sort_by_distance_, int flags_) {
            game_value array_input({
                begin_position_,
                end_position_,
                with_obj_,
                ignore_obj_,
                sort_by_distance_,
                (float)flags_
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectsobjs__array__ret__array, array_input);
            game_data_array* intersects = static_cast<game_data_array *>(intersects_value.data.getRef());

            std::vector<object> output;
            for (uint32_t i = 0; i < intersects->length; ++i) {
                output.push_back(object(intersects->data[i]));
            }
            return output;
        }
    }
}
