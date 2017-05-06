/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Position functions.

These are used to get and set the position of various objects and other things
in the game world.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        /* Position */
        namespace __helpers {
            vector3 get_pos_obj(unary_function fnc_, const object & obj_);
            vector3 get_pos_loc(unary_function fnc_, const location & loc_);
        }

        vector3 get_pos(const object & obj_);
        vector3 get_pos(const location & loc_);
        vector3 get_pos_asl(const object & obj_);
        vector3 get_pos_atl(const object & obj_);
        vector3 get_pos_aslw(const object & obj_);
        vector3 visible_position(const object & obj_);
        vector3 visible_position_asl(const object & obj_);
        vector3 position(const object & obj_);
        vector3 position_camera_to_world(const vector3 & pos_);
        vector3 get_pos_visual(const object & obj_);
        vector3 get_pos_asl_visual(const object & obj_);
        vector3 get_pos_atl_visual(const object & obj_);
        vector3 aim_pos(const object & obj_);

        void set_pos(const object & obj_, const vector3 &pos_);
        void set_pos_asl(const object & obj_, const vector3 & pos_);
        void set_pos_asl2(const object & obj_, const vector3 & pos_);
        void set_pos_aslw(const object & obj_, const vector3 & pos_);
        void set_pos_atl(const object & obj_, const vector3 & pos_);

        /////////////////////////////////////* Coordinate converters */
        vector3 agl_to_asl(const vector3 & agl_);
        vector3 asl_to_agl(const vector3 & asl_);
        vector3 atl_to_asl(const vector3 & atl_);
        vector3 asl_to_atl(const vector3 & asl_);








        vector3 get_pos(const object& obj_, float distance_, float heading_);
        vector3 get_pos(const vector3& pos_, float distance_, float heading_);
        vector3 get_rel_pos(const object& obj_, float distance_, float heading_);
        vector3 get_rel_pos(const vector3& pos_, float distance_, float heading_);
        float get_rel_dir(const object& obj_, const object& pos_);
        float get_rel_dir(const object& obj_, const vector3& pos_);


        void set_vector_up(const object &object_, const vector3 &vector_up_);
        void set_vector_dir_and_up(const object &object_, const vector3 &vector_dir_, const vector3 &vector_up_);

        void set_position(const location &location_, const vector3 &position_);
        void set_pos_world(const object &object_, const vector3 &position_);
    }
}
