#include "chat.hpp"
#include "client/pointers.hpp"
#include "position.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        /* Position */
        namespace __helpers {
            vector3 get_pos_obj(unary_function fnc_, const object & obj_) {
                return host::functions.invoke_raw_unary(fnc_, obj_);
            }
        }

        vector3 get_pos(const object & obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getpos__object__ret__array, obj_);
        }



        vector3 get_pos_asl(const object & obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposasl__object__ret__array, obj_);
        }

        vector3 get_pos_atl(const object & obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposatl__object__ret__array, obj_);
        }

        vector3 get_pos_aslw(const object & obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposaslw__object__ret__array, obj_);
        }

        vector3 visible_position(const object & obj_) {
            return __helpers::get_pos_obj(__sqf::unary__visibleposition__object__ret__array, obj_);
        }

        vector3 visible_position_asl(const object & obj_) {
            return __helpers::get_pos_obj(__sqf::unary__visiblepositionasl__object__ret__array, obj_);
        }

        vector3 position(const object & obj_) {
            return __helpers::get_pos_obj(__sqf::unary__position__object__ret__array, obj_);
        }

        vector3 position_camera_to_world(const vector3 & pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__positioncameratoworld__array__ret__array, pos_);
        }

        vector3 get_pos_visual(const object & obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposvisual__object__ret__array, obj_);
        }
        vector3 get_pos_asl_visual(const object & obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposaslvisual__object__ret__array, obj_);
        }

        vector3 get_pos_atl_visual(const object & obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getposatlvisual__object__ret__array, obj_);
        }

        vector3 aim_pos(const object & obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__aimpos__object__ret__array, obj_);
        }

        vector3 eye_pos(const object &object_) {
            return vector3(game_value(host::functions.invoke_raw_unary(__sqf::unary__eyepos__object__ret__array, object_)));
        }

        vector3 eye_direction(const object& unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__eyedirection__object__ret__array, unit_);
        }

        void set_pos(const object & obj_, const vector3 & pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpos__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_asl(const object & obj_, const vector3 & pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setposasl__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_asl2(const object & obj_, const vector3 & pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setposasl2__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_aslw(const object & obj_, const vector3 & pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setposaslw__object__array__ret__nothing, obj_, pos_);
        }

        void set_pos_atl(const object & obj_, const vector3 & pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setposatl__object__array__ret__nothing, obj_, pos_);
        }

        vector3 agl_to_asl(const vector3 & agl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__agltoasl__array__ret__array, agl_);
        }

        vector3 asl_to_agl(const vector3 & asl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__asltoagl__array__ret__array, asl_);
        }

        vector3 atl_to_asl(const vector3 & atl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__atltoasl__array__ret__array, atl_);
        }
        vector3 asl_to_atl(const vector3 & asl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__asltoatl__array__ret__array, asl_);
        }
        vector3 get_pos(const object& obj_, float distance_, float heading_) {
            game_value args({
                distance_,
                heading_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__getpos__object_array__array__ret__array, obj_, args);
        }

        vector3 get_pos(const vector3& pos_, float distance_, float heading_) {
            game_value args({
                distance_,
                heading_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__getpos__object_array__array__ret__array, pos_, args);
        }

        vector3 get_rel_pos(const object& obj_, float distance_, float heading_) {
            game_value args({
                distance_,
                heading_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__getrelpos__object__array__ret__array, obj_, args);
        }

        vector3 get_rel_pos(const vector3& pos_, float distance_, float heading_) {
            game_value args({
                distance_,
                heading_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__getrelpos__object__array__ret__array, pos_, args);
        }
        float get_rel_dir(const object& obj_, const object& pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getreldir__object__object_array__ret__scalar, obj_, pos_);
        }

        float get_rel_dir(const object& obj_, const vector3& pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getreldir__object__object_array__ret__scalar, obj_, pos_);
        }
        void set_vector_up(const object &object_, const vector3 &vector_up_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvectorup__object__array__ret__nothing, object_, vector_up_);
        }

        void set_vector_dir_and_up(const object &object_, const vector3 &vector_dir_, const vector3 &vector_up_) {
            game_value vector({
                vector_dir_,
                vector_up_
            });

            host::functions.invoke_raw_binary(__sqf::binary__setvectordirandup__object__array__ret__nothing, object_, vector);
        }

        void set_pos_world(const object &object_, const vector3 &position_) {
            host::functions.invoke_raw_binary(__sqf::binary__setposworld__object__array__ret__nothing, object_, position_);
        }
        vector3 get_pos_world(const object& unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getposworld__object__ret__array, unit_);
        }

        float get_terrain_height_asl(const vector3 position_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getterrainheightasl__array__ret__scalar, position_);
        }
        vector3 world_to_model(const object &object_, const vector3 &position_) {
            return host::functions.invoke_raw_binary(__sqf::binary__worldtomodel__object__array__ret__array, object_, position_);
        }

        vector3 world_to_model_visual(const object &object_, const vector3 &position_) {
            return host::functions.invoke_raw_binary(__sqf::binary__worldtomodelvisual__object__array__ret__array, object_, position_);
        }

        vector3 velocity_model_space(const object& obj_) {
            return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(__sqf::unary__velocitymodelspace__object__ret__array, obj_));
        }

        vector3 vector_up_visual(const object& obj_) {
            return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(__sqf::unary__vectorupvisual__object__ret__array, obj_));
        }

        vector3 vector_up(const object& obj_) {
            return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(__sqf::unary__vectorup__object__ret__array, obj_));
        }
        vector3 model_to_world_visual(const object & model_, const vector3 & model_pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__modeltoworldvisual__object__array__ret__array, model_, model_pos_);
        }

        vector2 world_to_screen(const vector3 & pos_agl_) {
            return host::functions.invoke_raw_unary(__sqf::unary__worldtoscreen__array__ret__array, pos_agl_);
        }

        vector2 world_to_screen(const vector3 & pos_agl_, bool & in_screen_) {
            game_value result = host::functions.invoke_raw_unary(__sqf::unary__worldtoscreen__array__ret__array, pos_agl_);
            if (static_cast<game_data_array *>(result.data.getRef())->length() == 2)
                in_screen_ = true;
            else
                in_screen_ = false;
            return game_value(result);
        }
        void set_vector_dir(const object & obj_, const vector3 & vec_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvectordir__object__array__ret__nothing, obj_, vec_);
        }

        void set_velocity(const object & obj_, const vector3 & vel_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvelocity__object__array__ret__nothing, obj_, vel_);
        }
        vector3 velocity(const object & obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__velocity__object__ret__array, obj_);
        }

        float direction(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__direction__object__ret__scalar, value_);
        }
    }
}


