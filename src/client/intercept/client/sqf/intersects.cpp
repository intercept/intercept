#include "intersects.hpp"
#include "client\pointers.hpp"


namespace intercept {
	namespace sqf {
		namespace __helpers {
			intersect_surfaces_list __line_intersects_surfaces(game_value& intersects_value_) {
				game_data_array* intersects = ((game_data_array *)intersects_value_.rv_data.data);

				intersect_surfaces_list output;
				for (uint32_t i = 0; i < intersects->length; ++i) {
					game_data_array* element = ((game_data_array *)intersects->data[i].rv_data.data); // our element array

					intersect_surfaces surfaces; // Our intersecting surfaces
					game_data_array* position = ((game_data_array *)element->data[0].rv_data.data); // finding the position
					surfaces.intersectPosASL = vector3(); // the actual position where line intersects 1st surface
					surfaces.intersectPosASL.x = ((game_data_number *)position[0].data)->number;
					surfaces.intersectPosASL.y = ((game_data_number *)position[1].data)->number;
					surfaces.intersectPosASL.z = ((game_data_number *)position[2].data)->number;

					// translating rv string to std string
					surfaces.surfaceNormal = element->data[1]; // a normal to the intersected surface

					// translating objects
					surfaces.intersectObject = object(element->data[2].rv_data); // the object the surface belongs to (could be proxy object)
					surfaces.parentObject = object(element->data[3].rv_data); // the object proxy object belongs to (not always the same as intersect object)

					output.push_back(std::make_shared<intersect_surfaces>(surfaces)); // Store the surfaces for our return
				}
				return output;
			}
		}

		bool intersect(const vector3 &begin_pos_, const vector3 &end_pos_, const object& obj_, const std::string &lodname_) {
			return game_value(host::functions.invoke_raw_binary(
				client::__sqf::binary__intersect__array__array__ret__array,
				begin_pos_,
				end_pos_));
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
			});

			game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectssurfaces__array__ret__array, array_input);
			return __helpers::__line_intersects_surfaces(intersects_value);
		}

		intersect_surfaces_list line_intersects_surfaces(const vector3 &begin_pos_asl_, const vector3 &end_pos_asl_, const object & ignore_obj1_, const object & ignore_obj2_, bool sort_mode_ = true, int max_results_ = 1, const std::string &lod1_ = "VIEW", const std::string &lod2_ = "FIRE") {
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

		std::vector<object> line_intersects_with(const vector3 &begin_pos_, const vector3 &end_pos_, bool sort_by_distance_ = true) {
            game_value array_input({
                begin_pos_,
                end_pos_,
                game_value(),
                game_value(),
                sort_by_distance_
            });
            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectswith__array__ret__array, array_input);

			game_data_array* intersects = ((game_data_array *)intersects_value.rv_data.data);

			std::vector<object> output;
			for (uint32_t i = 0; i < intersects->length; ++i) {
				output.push_back(object(intersects->data[i].rv_data));
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

            game_data_array* intersects = ((game_data_array *)intersects_value.rv_data.data);

            std::vector<object> output;
            for (uint32_t i = 0; i < intersects->length; ++i) {
                output.push_back(object(intersects->data[i].rv_data));
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

            game_data_array* intersects = ((game_data_array *)intersects_value.rv_data.data);

            std::vector<object> output;
            for (uint32_t i = 0; i < intersects->length; ++i) {
                output.push_back(object(intersects->data[i].rv_data));
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
			game_data_array* intersects = ((game_data_array *)intersects_value.rv_data.data);

			std::vector<object> output;
			for (uint32_t i = 0; i < intersects->length; ++i) {
				output.push_back(object(intersects->data[i].rv_data));
			}
			return output;
		}
    }
}
