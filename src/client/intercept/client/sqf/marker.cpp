#include "marker.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
		namespace markers {
			void delete_marker(const std::string& value_) {
				__helpers::__empty_unary_string(client::__sqf::unary__deletemarker__string__ret__nothing, value_);
			}

			void delete_marker_local(const std::string& value_) {
				__helpers::__empty_unary_string(client::__sqf::unary__deletemarkerlocal__string__ret__nothing, value_);
			}

			float marker_alpha(const std::string& value_) {
				return __helpers::__number_unary_string(client::__sqf::unary__markeralpha__string__ret__scalar, value_);
			}

			std::string marker_brush(const std::string& value_) {
				return __helpers::__string_unary_string(client::__sqf::unary__markerbrush__string__ret__string, value_);
			}

			std::string marker_color(const std::string& value_) {
				return __helpers::__string_unary_string(client::__sqf::unary__markercolor__string__ret__string, value_);
			}

			float marker_dir(const std::string& value_) {
				return __helpers::__number_unary_string(client::__sqf::unary__markerdir__string__ret__scalar, value_);
			}

			std::string marker_shape(const std::string& value_) {
				return __helpers::__string_unary_string(client::__sqf::unary__markershape__string__ret__string, value_);
			}

			std::string marker_text(const std::string& value_) {
				return __helpers::__string_unary_string(client::__sqf::unary__markertext__string__ret__string, value_);
			}

			std::string marker_type(const std::string& value_) {
				return __helpers::__string_unary_string(client::__sqf::unary__markertype__string__ret__string, value_);
			}

			void set_marker_alpha(float value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__setmarkeralpha__string__scalar__ret__nothing, value0_, value1_);
			}

			void set_marker_alpha_local(float value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__setmarkeralphalocal__string__scalar__ret__nothing, value0_, value1_);
			}

			void set_marker_dir(float value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerdir__string__scalar__ret__nothing, value0_, value1_);
			}

			void set_marker_dir_local(float value0_, const std::string& value1_) {
				host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerdirlocal__string__scalar__ret__nothing, value0_, value1_);
			}

			std::string get_marker_color(const std::string& value_) {
				return __helpers::__string_unary_string(client::__sqf::unary__getmarkercolor__string__ret__string, value_);
			}

			std::string get_marker_type(const std::string& value_) {
				return __helpers::__string_unary_string(client::__sqf::unary__getmarkertype__string__ret__string, value_);
			}

			vector3 get_marker_pos(const std::string& value_)
			{
				game_value function_return_array = host::functions.invoke_raw_unary(__sqf::unary__getmarkerpos__string__ret__array, game_value(value_));

				return __helpers::__convert_to_vector3(function_return_array);

				//float x = ((game_data_number *)((game_data_array *)function_return_array.data)->data[0].data)->number;
				//float y = ((game_data_number *)((game_data_array *)function_return_array.data)->data[1].data)->number;
				//float z = ((game_data_number *)((game_data_array *)function_return_array.data)->data[2].data)->number;
				//host::functions.free_value(&function_return_array);
				//return vector3(x, y, z);
			}

			vector2 get_marker_size(const std::string& value_)
			{
				game_value function_return_array = host::functions.invoke_raw_unary(__sqf::unary__getmarkersize__string__ret__array, game_value(value_));

				//float x = ((game_data_number *)((game_data_array *)function_return_array.data)->data[0].data)->number;
				//float y = ((game_data_number *)((game_data_array *)function_return_array.data)->data[1].data)->number;
				//host::functions.free_value(&function_return_array);
				return vector2(function_return_array[0], function_return_array[1]);
			}

			std::string create_marker(std::string name_, vector2 pos_)
			{
				game_value params({
					name_,
					pos_
				});

				return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params));
			}

			std::string create_marker(std::string name_, vector3 pos_)
			{
				game_value params({
					name_,
					pos_
				});

				return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params));
			}

			std::string create_marker(std::string name_, object pos_)
			{
				game_value params({
					name_,
					pos_
				});

				return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params));
			}

			std::string create_marker_local(std::string name_, vector2 pos_)
			{
				game_value params({
					name_,
					pos_,
				});

				return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params));
			}

			std::string create_marker_local(std::string name_, vector3 pos_)
			{
				game_value params({
					name_,
					pos_,
				});

				return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params));
			}

			std::string create_marker_local(std::string name_, object pos_)
			{
				game_value params({
					name_,
					pos_,
				});

				return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params));
			}
		}
    }
}
