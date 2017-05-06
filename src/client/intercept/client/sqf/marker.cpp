#include "marker.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {

        std::string create_marker(const std::string &name_, const vector2 &pos_) {
            game_value params({
                name_,
                pos_
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params));
        }

        std::string create_marker(const std::string &name_, const vector3 &pos_) {
            game_value params({
                name_,
                pos_
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params));
        }

        std::string create_marker(const std::string &name_, const object &pos_) {
            game_value params({
                name_,
                pos_
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params));
        }

        std::string create_marker_local(const std::string &name_, const vector2 &pos_) {
            game_value params({
                name_,
                pos_,
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params));
        }

        std::string create_marker_local(const std::string &name_, const vector3 &pos_) {
            game_value params({
                name_,
                pos_,
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params));
        }

        std::string create_marker_local(const std::string &name_, const object &pos_) {
            game_value params({
                name_,
                pos_,
            });

            return game_value(host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params));
        }

        void delete_marker(const std::string& value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__deletemarker__string__ret__nothing, value_);
        }

        void delete_marker_local(const std::string& value_) {
            __helpers::__empty_unary_string(client::__sqf::unary__deletemarkerlocal__string__ret__nothing, value_);
        }

        void set_marker_type(const std::string& marker_, const std::string& type_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkertype__string__string__ret__nothing, marker_, type_);
        }

        void set_marker_type_local(const std::string& marker_, const std::string& type_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkertypelocal__string__string__ret__nothing, marker_, type_);
        }

        void set_marker_text(const std::string& marker_, const std::string& text_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkertext__string__string__ret__nothing, marker_, text_);
        }

        void set_marker_text_local(const std::string& marker_, const std::string& text_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkertextlocal__string__string__ret__nothing, marker_, text_);
        }

        void set_marker_size(const std::string& marker_, const vector2& size_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkersize__string__array__ret__nothing, marker_, size_);
        }

        void set_marker_size_local(const std::string& marker_, const vector2& size_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkersizelocal__string__array__ret__nothing, marker_, size_);
        }

        void set_marker_shape(const std::string& marker_, const std::string& shape_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkershape__string__string__ret__nothing, marker_, shape_);
        }

        void set_marker_shape_local(const std::string& marker_, const std::string& shape_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkershapelocal__string__string__ret__nothing, marker_, shape_);
        }

        void set_marker_pos(const std::string& marker_, const vector3& pos_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerpos__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos_local(const std::string& marker_, const vector3& pos_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerposlocal__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos(const std::string& marker_, const vector2& pos_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerpos__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos_local(const std::string& marker_, const vector2& pos_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerposlocal__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_brush(const std::string& marker_, const std::string& brush_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerbrush__string__string__ret__nothing, marker_, brush_);
        }

        void set_marker_brush_local(const std::string& marker_, const std::string& brush_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerbrushlocal__string__string__ret__nothing, marker_, brush_);
        }

        void set_marker_color(const std::string& marker_, const std::string& color_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkercolor__string__string__ret__nothing, marker_, color_);
        }

        void set_marker_color_local(const std::string& marker_, const std::string& color_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkercolorlocal__string__string__ret__nothing, marker_, color_);
        }

        void set_marker_alpha(const std::string& marker_, float alpha_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkeralpha__string__scalar__ret__nothing, marker_, alpha_);
        }

        void set_marker_alpha_local(const std::string& marker_, float alpha_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkeralphalocal__string__scalar__ret__nothing, marker_, alpha_);
        }

        void set_marker_dir(const std::string& marker_, float dir_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerdir__string__scalar__ret__nothing, marker_, dir_);
        }

        void set_marker_dir_local(const std::string& marker_, float dir_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setmarkerdirlocal__string__scalar__ret__nothing, marker_, dir_);
        }


        float marker_alpha(const std::string& value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__markeralpha__string__ret__scalar, value_);
        }
        float marker_dir(const std::string& value_) {
            return __helpers::__number_unary_string(client::__sqf::unary__markerdir__string__ret__scalar, value_);
        }
        std::string marker_brush(const std::string& value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markerbrush__string__ret__string, value_);
        }

        std::string marker_color(const std::string& value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__markercolor__string__ret__string, value_);
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

        std::string get_marker_color(const std::string& value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__getmarkercolor__string__ret__string, value_);
        }

        std::string get_marker_type(const std::string& value_) {
            return __helpers::__string_unary_string(client::__sqf::unary__getmarkertype__string__ret__string, value_);
        }

        vector3 get_marker_pos(const std::string& value_) {
            return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(__sqf::unary__getmarkerpos__string__ret__array, value_));
            // Identical: unary__markerpos__string__ret__array
        }

        vector2 get_marker_size(const std::string& value_) {
            game_value function_return_array = host::functions.invoke_raw_unary(__sqf::unary__getmarkersize__string__ret__array, value_);
            return vector2(function_return_array[0], function_return_array[1]);
            // Identical: unary__markersize__string__ret__array
        }

        std::vector<marker> all_map_markers() {
            return __helpers::__convert_to_markers_vector(host::functions.invoke_raw_nular(client::__sqf::nular__allmapmarkers__ret__array));
        }













































        //Locations

















        location nearest_location(const vector3& pos_, const std::string& location_class_) {
            game_value args({
                pos_,
                location_class_
            });

            return location(host::functions.invoke_raw_unary(client::__sqf::unary__nearestlocation__array__ret__location, args));
        }

        location nearest_location(const object& unit_, const std::string& location_class_) {
            game_value args({
                unit_,
                location_class_
            });

            return location(host::functions.invoke_raw_unary(client::__sqf::unary__nearestlocation__array__ret__location, args));
        }

        std::vector<location> nearest_locations(const vector3& pos_, std::vector<std::string>& location_types_, float radius_) {
            std::vector<game_value> loctypes;
            for (std::string l_ : location_types_)
                loctypes.push_back(l_);

            game_value args({
                pos_,
                loctypes,
                radius_
            });

            game_value rval(host::functions.invoke_raw_unary(client::__sqf::unary__nearestlocation__array__ret__location, args));

            std::vector<location> output;
            for (uint32_t i = 0; i < rval.length(); ++i) {
                output.push_back(location(rval[i]));
            }
            return output;
        }

        std::vector<location> nearest_locations(const vector3& pos_, std::vector<std::string>& location_types_, float radius_, const vector3& sort_position_) {
            std::vector<game_value> loctypes;
            for (std::string l_ : location_types_)
                loctypes.push_back(l_);

            game_value args({
                pos_,
                loctypes,
                radius_,
                sort_position_
            });

            game_value rval(host::functions.invoke_raw_unary(client::__sqf::unary__nearestlocation__array__ret__location, args));

            std::vector<location> output;
            for (uint32_t i = 0; i < rval.length(); ++i) {
                output.push_back(location(rval[i]));
            }
            return output;
        }

        std::vector<location> nearest_locations(const object& unit_, std::vector<std::string>& location_types_, float radius_) {
            std::vector<game_value> loctypes;
            for (std::string l_ : location_types_)
                loctypes.push_back(l_);

            game_value args({
                unit_,
                loctypes,
                radius_
            });

            game_value rval(host::functions.invoke_raw_unary(client::__sqf::unary__nearestlocation__array__ret__location, args));

            std::vector<location> output;
            for (uint32_t i = 0; i < rval.length(); ++i) {
                output.push_back(location(rval[i]));
            }
            return output;
        }

        std::vector<location> nearest_locations(const object& unit_, std::vector<std::string>& location_types_, float radius_, const vector3& sort_position_) {
            std::vector<game_value> loctypes;
            for (std::string l_ : location_types_)
                loctypes.push_back(l_);

            game_value args({
                unit_,
                loctypes,
                radius_,
                sort_position_
            });

            game_value rval(host::functions.invoke_raw_unary(client::__sqf::unary__nearestlocation__array__ret__location, args));

            std::vector<location> output;
            for (uint32_t i = 0; i < rval.length(); ++i) {
                output.push_back(location(rval[i]));
            }
            return output;
        }
        std::vector<location> nearest_locations(const vector3 pos_, const std::vector<std::string> &loc_types_, float radius_) {
            std::vector<game_value> loc_types;
            for (auto loc_type : loc_types_)
                loc_types.push_back(game_value(loc_type));

            std::vector<game_value> params{
                pos_,
                loc_types,
                radius_
            };

            return __helpers::__convert_to_locations_vector(host::functions.invoke_raw_unary(client::__sqf::unary__nearestlocations__array__ret__array, params));
        }

        std::vector<location> nearest_locations(const vector3 pos_, const std::vector<std::string> &loc_types_, float radius_, const vector3 &sort_pos_) {
            std::vector<game_value> loc_types;
            for (auto loc_type : loc_types_)
                loc_types.push_back(game_value(loc_type));

            std::vector<game_value> params{
                pos_,
                loc_types,
                radius_,
                sort_pos_
            };

            return __helpers::__convert_to_locations_vector(host::functions.invoke_raw_unary(client::__sqf::unary__nearestlocations__array__ret__array, params));
        }

        std::vector<location> nearest_locations(const vector3 pos_, const std::vector<std::string> &loc_types_, float radius_, const object &sort_obj_) {
            std::vector<game_value> loc_types;
            for (auto loc_type : loc_types_)
                loc_types.push_back(game_value(loc_type));

            std::vector<game_value> params{
                pos_,
                loc_types,
                radius_,
                sort_obj_
            };

            return __helpers::__convert_to_locations_vector(host::functions.invoke_raw_unary(client::__sqf::unary__nearestlocations__array__ret__array, params));
        }

        location nearest_location_with_dubbing(const vector3 &pos_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__nearestlocationwithdubbing__array__ret__location, pos_));
        }

        location nearest_location_with_dubbing(const object &obj_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__nearestlocationwithdubbing__array__ret__location, obj_));
        }
    }
}
