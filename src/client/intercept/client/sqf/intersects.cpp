#include "intersects.hpp"
#include "client\pointers.hpp"


namespace intercept {
    namespace sqf {
        namespace __helpers {
            bool line_intersects_with(game_value& array_input) {
                game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectswith__array__ret__array, &array_input);
                bool intersects = ((game_data_bool *)intersects_value.data)->value;

                host::functions.free_value(&intersects_value);
                return intersects;
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

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectssurfaces__array__ret__array, &array_input);
            game_data_array* intersects = ((game_data_array *)intersects_value.data);

            intersect_surfaces_list output;
            for (int i = 0; i < intersects->length; ++i) {
                game_value element = intersects->data[i];

                intersect_surfaces surfaces;
                surfaces.intersectObject = //(((game_value_array<4> *)&element)->value.data[2]);
          
                output.push_back(std::make_shared<intersect_surfaces>(surfaces));
            }
            host::functions.free_value(&intersects_value);
            return output;
        }

        intersect_surfaces_list line_intersects_surfaces(vector3 begin_pos_asl_, vector3 end_pos_asl_, const object& ignore_obj1_) {
            return true;
        }

        intersect_surfaces_list line_intersects_surfaces(vector3 begin_pos_asl_, vector3 end_pos_asl_, const object& ignore_obj1_, const object& ignore_obj2_) {
            return true;
        }

        intersect_surfaces_list line_intersects_surfaces(vector3 begin_pos_asl_, vector3 end_pos_asl_, const object& ignore_obj1_, const object& ignore_obj2_, bool sort_mode_ = true, int max_results_ = 1, std::string lod1_ = "VIEW", std::string lod2_ = "FIRE") {
            return true;
        }

        bool line_intersects_with(vector3 begin_pos_, vector3 end_pos_, const object& ignore_obj1_ = nullptr, const object& ignore_obj2_ = nullptr, bool sort_by_distance_ = true) {
            
            if (ignore_obj1_ != nullptr && ignore_obj2_ != nullptr) {
                game_value_array<5> array_input({
                    game_value_vector3(begin_pos_),
                    game_value_vector3(end_pos_),
                    ignore_obj1_->value,
                    ignore_obj1_->value,
                    game_value_bool(sort_by_distance_)
                });
                return __helpers::line_intersects_with((game_value)array_input);
            }
            else {
                game_value_array<2> array_input({
                    game_value_vector3(begin_pos_),
                    game_value_vector3(end_pos_)
                });
                return __helpers::line_intersects_with((game_value)array_input);
            }
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

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersects__array__ret__bool, &array_input);
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

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersects__array__ret__bool, &array_input);
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

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectsobjs__array__ret__array, &array_input);
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
