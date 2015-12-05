#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        namespace __helpers {
            float nular_function(intercept::rv_types::nular_function fnc_);
        }

        float random(float max_);

        float save_zone_x();
        float save_zone_y();
        float save_zone_h();
        float save_zone_w();
        float save_zone_x_abs();
        float save_zone_w_abs();
    }
}
