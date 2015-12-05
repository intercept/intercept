#include "intersects.hpp"
#include "client\pointers.hpp"


namespace intercept {
    namespace sqf {
        namespace __helpers {
            
        }
        bool line_intersects(vector3 beginPosition_, vector3 endPosition_) {

            game_value_array<2> array_input({
                game_value_vector3(beginPosition_),
                game_value_vector3(endPosition_)
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersects__array__ret__bool, array_input);
            bool intersects = ((game_data_bool *)intersects_value.data)->value;

            host::functions.free_value(&intersects_value);
            return intersects;
        }

        bool line_intersects(vector3 beginPosition_, vector3 endPosition_, const object& ignore_obj_one_) {
            game_value_array<3> array_input({
                game_value_vector3(beginPosition_),
                game_value_vector3(endPosition_),
                game_value_object(ignore_obj_one_)
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersects__array__ret__bool, &array_input);
            bool intersects = ((game_data_bool *)intersects_value.data)->value;
            host::functions.free_value(&intersects_value);
            return intersects;
        }

        bool line_intersects(vector3 beginPosition_, vector3 endPosition_, const object& ignore_obj_one_, const object& ignore_obj_two_) {
            
            game_value_array<4> array_input({
                game_value_vector3(beginPosition_),
                game_value_vector3(endPosition_),
                game_value_object(ignore_obj_one_),
                game_value_object(ignore_obj_two_)
            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersects__array__ret__bool, &array_input);
            bool intersects = ((game_data_bool *)intersects_value.data)->value;
            host::functions.free_value(&intersects_value);
            return intersects;
        }

        void line_intersects_objs(vector3 beginPosition_, vector3 endPosition_, const object& withObj_, const object& ignoreObj_, bool sortByDistance_, int flags_) {
            game_value_array<6> array_input({
                game_value_vector3(beginPosition_),
                game_value_vector3(endPosition_),
                game_value_object(withObj_),
                game_value_object(ignoreObj_),
                game_value_bool(sortByDistance_),
                game_value_number(flags_),

            });

            game_value intersects_value = host::functions.invoke_raw_unary(client::__sqf::unary__lineintersectsobjs__array__ret__array, &array_input);
            game_data_array* intersects = ((game_data_array *)intersects_value.data);

            // TODO
            // std::array requires us to know the exact length at compile time. So use vector instead?
            // std::vector<game_data_object> arr(intersects->length);
        }

    }
}
