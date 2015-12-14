#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
		namespace markers {
			void delete_marker(const std::string& value_);
			void delete_marker_local(const std::string& value_);
			float marker_alpha(const std::string& value_);
			float marker_dir(const std::string& value_);

			std::string marker_brush(const std::string& value_);
			std::string marker_color(const std::string& value_);
			std::string marker_shape(const std::string& value_);
			std::string marker_text(const std::string& value_);
			std::string marker_type(const std::string& value_);

			void set_marker_alpha(float value0_, const std::string& value1_);
			void set_marker_alpha_local(float value0_, const std::string& value1_);
			void set_marker_dir(float value0_, const std::string& value1_);
			void set_marker_dir_local(float value0_, const std::string& value1_);

			std::string get_marker_color(const std::string& value_);
			std::string get_marker_type(const std::string& value_);
			vector3 get_marker_pos(const std::string& value_);
			vector2 get_marker_size(const std::string& value_);

            std::string create_marker(std::string name_, vector3 pos_);
            std::string create_marker(std::string name_, vector2 pos_);
            std::string create_marker(std::string name_, object pos_);
            std::string create_marker_local(std::string name_, vector3 pos_);
            std::string create_marker_local(std::string name_, vector2 pos_);
            std::string create_marker_local(std::string name_, object pos_);
		}
    }
}
