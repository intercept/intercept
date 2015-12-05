#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        object player();
        object create_vehicle(std::string type_, vector3 pos_);
        object create_vehicle(std::string type_, vector3 pos_, std::vector<marker> markers_, float placement_, std::string special_);
        void delete_vehicle(object obj_);
    }
}
