#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        namespace __helpers {
        }

        bool line_intersects(vector3 beginPosition_, vector3 endPosition_);
        bool line_intersects(vector3 beginPosition_, vector3 endPosition_, const object& ignore_obj_one_);
        bool line_intersects(vector3 beginPosition_, vector3 endPosition_, const object& ignore_obj_one_, const object& ignore_obj_two_);
        
        void line_intersects_objs(vector3 beginPosition_, vector3 endPosition_, const object& withObj_, const object& ignoreObj_, bool sortByDistance_, int flags_);

    }
}
