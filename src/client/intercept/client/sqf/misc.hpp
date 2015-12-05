#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        namespace __helpers {
            float nular_function(intercept::rv_types::nular_function fnc_);
            bool nular_function_bool(intercept::rv_types::nular_function fnc_);
        }

        float random(float max_);
		bool visible_watch();
		bool visible_map();
		bool visible_gps();
		bool visible_compass();


        float save_zone_x();
        float save_zone_y();
        float save_zone_h();
        float save_zone_w();
        float save_zone_x_abs();
        float save_zone_w_abs();
        
        bool shown_artillerycomputer();
        bool shown_chat();
        bool shown_compass();
        bool shown_curatorcompass();
        bool shown_gps();
        bool shown_hud__ret__array;
        bool shown_map();
        bool shown_pad();
        bool shown_radio();
        bool shown_uavfeed();
        bool shown_warrant();
        bool shown_watch();
    }
}
