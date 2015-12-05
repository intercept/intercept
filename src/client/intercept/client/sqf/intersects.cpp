#include "intersects.hpp"
#include "client\pointers.hpp"


namespace intercept {
    namespace sqf {
        namespace __helpers {

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

        std::vector<object> line_intersects_objs(vector3 begin_position_, vector3 end_position_, object& with_obj_, object& ignore_obj_, bool sort_by_distance_, int flags_) {
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
