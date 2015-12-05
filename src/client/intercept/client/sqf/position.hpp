#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        /*
        getPosASLVisual
        getPosATLVisual
        getPosVisual
        */
        namespace __helpers {
            vector3 get_pos_obj(unary_function fnc_, object obj_);
        }
        vector3 get_pos(object obj_);
        vector3 get_pos(location loc_);
        vector3 get_pos_asl(object obj_);
        vector3 get_pos_atl(object obj_);
        vector3 get_pos_aslw(object obj_);
        vector3 visible_position(object obj_);
        vector3 visible_position_asl(object obj_);
        vector3 position(object obj_);
        vector3 get_pos_visual(object obj_);
        vector3 get_pos_asl_visual(object obj_);
        vector3 get_pos_atl_visual(object obj_);

        void set_pos(object obj_, vector3 pos_);
        void set_pos_asl(object obj_, vector3 pos_);
        void set_pos_asl2(object obj_, vector3 pos_);
        void set_pos_aslw(object obj_, vector3 pos_);
        void set_pos_atl(object obj_, vector3 pos_);



    }
}
