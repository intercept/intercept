#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        namespace __helpers {
        }

        bool line_intersects(vector3 begin_position_, vector3 end_position_);
        bool line_intersects(vector3 begin_position_, vector3 end_position_, const object& ignore_obj_one_);
        bool line_intersects(vector3 begin_position_, vector3 end_position_, const object& ignore_obj_one_, const object& ignore_obj_two_);

        std::vector<object> line_intersects_objs(vector3 begin_position_, vector3 end_position_, const object& with_object_, const object& ignore_obj_, bool sort_by_distance_, int flags_);

    }
}
