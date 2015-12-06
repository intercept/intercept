#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        void delete_marker(std::string value_);
        void delete_marker_local(std::string value_);
        float marker_alpha(std::string value_);
        std::string marker_brush(std::string value_);
        std::string marker_color(std::string value_);
        float marker_dir(std::string value_);
        std::string marker_shape(std::string value_);
        std::string marker_text(std::string value_);
        std::string marker_type(std::string value_);
        void set_marker_alpha(float value0_, std::string value1_);
        void set_marker_alpha_local(float value0_, std::string value1_);
        void set_marker_dir(float value0_, std::string value1_);
        void set_marker_dir_local(float value0_, std::string value1_);
        std::string get_marker_color(std::string value_);
        std::string get_marker_type(std::string value_);
    }
}
