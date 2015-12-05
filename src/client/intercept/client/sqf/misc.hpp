#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        float random(float max_);
		bool visible_watch();
		bool visible_map();
		bool visible_gps();
		bool visible_compass();

    }
}
