#include "ctrl.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        void delete_marker(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__deletemarker__string__ret__nothing, value_);
        }

        void delete_marker_local(std::string value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__deletemarkerlocal__string__ret__nothing, value_);
        }

        float marker_alpha(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__markeralpha__string__ret__scalar, value_);
        }

        std::string marker_brush(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markerbrush__string__ret__string, value_);
        }

        std::string marker_color(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markercolor__string__ret__string, value_);
        }

        float marker_dir(std::string value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__markerdir__string__ret__scalar, value_);
        }

        std::string marker_shape(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markershape__string__ret__string, value_);
        }

        std::string marker_text(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markertext__string__ret__string, value_);
        }

        std::string marker_type(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markertype__string__ret__string, value_);
        }

        void set_marker_alpha(float value0_, std::string value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkeralpha__string__scalar__ret__nothing, game_value_number(value0_), game_value_string(value1_));
        }

        void set_marker_alpha_local(float value0_, std::string value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkeralphalocal__string__scalar__ret__nothing, game_value_number(value0_), game_value_string(value1_));
        }

        void set_marker_dir(float value0_, std::string value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerdir__string__scalar__ret__nothing, game_value_number(value0_), game_value_string(value1_));
        }

        void set_marker_dir_local(float value0_, std::string value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerdirlocal__string__scalar__ret__nothing, game_value_number(value0_), game_value_string(value1_));
        }

        std::string get_marker_color(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__getmarkercolor__string__ret__string, value_);
        }

        std::string get_marker_type(std::string value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__getmarkertype__string__ret__string, value_);
        }
        
    }
}
