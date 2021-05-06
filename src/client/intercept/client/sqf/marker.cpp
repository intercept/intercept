#include "marker.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {

        sqf_return_string create_marker(sqf_string_const_ref name_, const vector2 &pos_) {
            game_value params({name_,
                               pos_});

            return host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params);
        }

        sqf_return_string create_marker(sqf_string_const_ref name_, const vector3 &pos_) {
            game_value params({name_,
                               pos_});

            return host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params);
        }

        sqf_return_string create_marker(sqf_string_const_ref name_, const object &pos_) {
            game_value params({name_,
                               pos_});

            return host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params);
        }

        sqf_return_string create_marker_local(sqf_string_const_ref name_, const vector2 &pos_) {
            game_value params({
                name_,
                pos_,
            });

            return host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params);
        }

        sqf_return_string create_marker_local(sqf_string_const_ref name_, const vector3 &pos_) {
            game_value params({
                name_,
                pos_,
            });

            return host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params);
        }

        sqf_return_string create_marker_local(sqf_string_const_ref name_, const object &pos_) {
            game_value params({
                name_,
                pos_,
            });

            return host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params);
        }

        void delete_marker(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__deletemarker__string__ret__nothing, value_);
        }

        void delete_marker_local(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__deletemarkerlocal__string__ret__nothing, value_);
        }

        void set_marker_type(sqf_string_const_ref marker_, sqf_string_const_ref type_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkertype__string__string__ret__nothing, marker_, type_);
        }

        void set_marker_type_local(sqf_string_const_ref marker_, sqf_string_const_ref type_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkertypelocal__string__string__ret__nothing, marker_, type_);
        }

        void set_marker_text(sqf_string_const_ref marker_, sqf_string_const_ref text_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkertext__string__string__ret__nothing, marker_, text_);
        }

        void set_marker_text_local(sqf_string_const_ref marker_, sqf_string_const_ref text_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkertextlocal__string__string__ret__nothing, marker_, text_);
        }

        void set_marker_size(sqf_string_const_ref marker_, const vector2 &size_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkersize__string__array__ret__nothing, marker_, size_);
        }

        void set_marker_size_local(sqf_string_const_ref marker_, const vector2 &size_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkersizelocal__string__array__ret__nothing, marker_, size_);
        }

        void set_marker_shape(sqf_string_const_ref marker_, sqf_string_const_ref shape_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkershape__string__string__ret__nothing, marker_, shape_);
        }

        void set_marker_shape_local(sqf_string_const_ref marker_, sqf_string_const_ref shape_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkershapelocal__string__string__ret__nothing, marker_, shape_);
        }

        void set_marker_pos(sqf_string_const_ref marker_, const vector2 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerpos__string__object_array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos(sqf_string_const_ref marker_, const vector3 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerpos__string__object_array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos(sqf_string_const_ref marker_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerpos__string__object_array__ret__nothing, marker_, target_);
        }

        void set_marker_pos_local(sqf_string_const_ref marker_, const vector2 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerposlocal__string__object_array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos_local(sqf_string_const_ref marker_, const vector3 &pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerposlocal__string__object_array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos_local(sqf_string_const_ref marker_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerposlocal__string__object_array__ret__nothing, marker_, target_);
        }

        void set_marker_brush(sqf_string_const_ref marker_, sqf_string_const_ref brush_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerbrush__string__string__ret__nothing, marker_, brush_);
        }

        void set_marker_brush_local(sqf_string_const_ref marker_, sqf_string_const_ref brush_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerbrushlocal__string__string__ret__nothing, marker_, brush_);
        }

        void set_marker_color(sqf_string_const_ref marker_, sqf_string_const_ref color_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkercolor__string__string__ret__nothing, marker_, color_);
        }

        void set_marker_color_local(sqf_string_const_ref marker_, sqf_string_const_ref color_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkercolorlocal__string__string__ret__nothing, marker_, color_);
        }

        void set_marker_alpha(sqf_string_const_ref marker_, float alpha_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkeralpha__string__scalar__ret__nothing, marker_, alpha_);
        }

        void set_marker_alpha_local(sqf_string_const_ref marker_, float alpha_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkeralphalocal__string__scalar__ret__nothing, marker_, alpha_);
        }

        void set_marker_dir(sqf_string_const_ref marker_, float dir_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerdir__string__scalar__ret__nothing, marker_, dir_);
        }

        void set_marker_dir_local(sqf_string_const_ref marker_, float dir_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerdirlocal__string__scalar__ret__nothing, marker_, dir_);
        }

        float marker_alpha(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__markeralpha__string__ret__scalar, value_);
        }
        float marker_dir(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__markerdir__string__ret__scalar, value_);
        }
        sqf_return_string marker_brush(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__markerbrush__string__ret__string, value_);
        }

        sqf_return_string marker_color(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__markercolor__string__ret__string, value_);
        }
        sqf_return_string marker_shape(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__markershape__string__ret__string, value_);
        }
        sqf_return_string marker_text(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__markertext__string__ret__string, value_);
        }
        sqf_return_string marker_type(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__markertype__string__ret__string, value_);
        }

        sqf_return_string get_marker_color(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__getmarkercolor__string__ret__string, value_);
        }

        sqf_return_string get_marker_type(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__getmarkertype__string__ret__string, value_);
        }

        vector3 get_marker_pos(sqf_string_const_ref value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getmarkerpos__string__ret__array, value_);
            // Identical: unary__markerpos__string__ret__array
        }

        vector3 get_marker_pos(sqf_string_const_ref marker_name_, bool preserveElevation) {
            return host::functions.invoke_raw_unary(__sqf::unary__getmarkerpos__array__ret__array, {marker_name_, preserveElevation});
            // Identical: unary__markerpos__array__ret__array
        }

        vector2 get_marker_size(sqf_string_const_ref value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getmarkersize__string__ret__array, value_);
            // Identical: unary__markersize__string__ret__array
        }

        std::vector<marker> all_map_markers() {
            return __helpers::__convert_to_vector<marker>(host::functions.invoke_raw_nular(__sqf::nular__allmapmarkers__ret__array));
        }

        //Locations

        namespace __helpers {
            vector3 get_pos_loc(unary_function fnc_, const location &loc_) {
                return host::functions.invoke_raw_unary(fnc_, loc_);
            }
        }  // namespace __helpers

        void set_importance(const location &loc_, const float &value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setimportance__location__scalar__ret__nothing, loc_, value_);
        }
        void set_side(const location &loc_, const side &side_) {
            host::functions.invoke_raw_binary(__sqf::binary__setside__location__side__ret__nothing, loc_, side_);
        }
        void set_position(const location &location_, const vector3 &position_) {
            host::functions.invoke_raw_binary(__sqf::binary__setposition__location__array__ret__nothing, location_, position_);
        }
        void delete_location(const location &loc_) {
            host::functions.invoke_raw_unary(__sqf::unary__deletelocation__location__ret__nothing, loc_);
        }
        void attach_object(const location &location_, const object &object_) {
            host::functions.invoke_raw_binary(__sqf::binary__attachobject__location__object__ret__nothing, location_, object_);
        }
        bool is_null(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__location__ret__bool, loc_);
        }
        bool rectangular(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__rectangular__location__ret__bool, loc_);
        }
        bool in(const vector3 &pos_, const location &loc_) {
            return host::functions.invoke_raw_binary(__sqf::binary__in__array__location__ret__bool, pos_, loc_);
        }
        float direction(const location &value_) {
            return __helpers::__number_unary_location(__sqf::unary__direction__location__ret__scalar, value_);
        }
        float importance(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__importance__location__ret__scalar, loc_);
        }
        float distance(const location &start_, const location &end_) {
            return host::functions.invoke_raw_binary(__sqf::binary__distance__location__location__ret__scalar, start_, end_);
        }

        float distance(const location &start_, const vector3 &end_) {
            return host::functions.invoke_raw_binary(__sqf::binary__distance__location__array__ret__scalar, start_, end_);
        }

        float distance(const vector3 &start_, const location &end_) {
            return host::functions.invoke_raw_binary(__sqf::binary__distance__array__location__ret__scalar, start_, end_);
        }
        location nearest_location(const vector3 &pos_, sqf_string_const_ref location_class_) {
            game_value args({pos_,
                             location_class_});

            return location(host::functions.invoke_raw_unary(__sqf::unary__nearestlocation__array__ret__location, args));
        }

        location nearest_location(const object &unit_, sqf_string_const_ref location_class_) {
            game_value args({unit_,
                             location_class_});

            return location(host::functions.invoke_raw_unary(__sqf::unary__nearestlocation__array__ret__location, args));
        }
        location nearest_location_with_dubbing(const vector3 &pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__nearestlocationwithdubbing__array__ret__location, pos_);
        }

        location nearest_location_with_dubbing(const object &obj_) {
            return host::functions.invoke_raw_unary(__sqf::unary__nearestlocationwithdubbing__array__ret__location, obj_);
        }
        object attached_object(const location &loc_) {
            return object(host::functions.invoke_raw_unary(__sqf::unary__attachedobject__location__ret__object, loc_));
        }
        side get_side(const location &loc_) {
            return side(host::functions.invoke_raw_unary(__sqf::unary__side__location__ret__side, loc_));
        }
        vector3 position(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__position__location__ret__array, loc_);
        }
        vector2 size(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__size__location__ret__array, loc_);
        }
        vector3 get_pos(const location &loc_) {
            return __helpers::get_pos_loc(__sqf::unary__getpos__location__ret__array, loc_);
        }
        vector2 location_position(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__locationposition__location__ret__array, loc_);
        }
        
        std::vector<location> nearest_locations(const vector3 &pos_, sqf_string_list_const_ref location_types_, float radius_) {
            auto_array<game_value> loctypes(location_types_.begin(), location_types_.end());

            game_value args({pos_,
                             std::move(loctypes),
                             radius_});

            return __helpers::__convert_to_vector<location>(host::functions.invoke_raw_unary(__sqf::unary__nearestlocations__array__ret__array, args));
        }

        std::vector<location> nearest_locations(const vector3 &pos_, sqf_string_list_const_ref location_types_, float radius_, const vector3 &sort_position_) {
            auto_array<game_value> loctypes(location_types_.begin(), location_types_.end());

            game_value args({pos_,
                             std::move(loctypes),
                             radius_,
                             sort_position_});

            return __helpers::__convert_to_vector<location>(host::functions.invoke_raw_unary(__sqf::unary__nearestlocations__array__ret__array, args));
        }

        std::vector<location> nearest_locations(const vector3 &pos_, sqf_string_list_const_ref location_types_, float radius_, const object &sort_obj_) {
            auto_array<game_value> loc_types(location_types_.begin(), location_types_.end());

            game_value params({pos_,
                               std::move(loc_types),
                               radius_,
                               sort_obj_});

            return __helpers::__convert_to_vector<location>(host::functions.invoke_raw_unary(__sqf::unary__nearestlocations__array__ret__array, params));
        }

        std::vector<location> nearest_locations(const object &unit_, sqf_string_list_const_ref location_types_, float radius_) {
            auto_array<game_value> loctypes(location_types_.begin(), location_types_.end());

            game_value args({unit_,
                             std::move(loctypes),
                             radius_});

            return __helpers::__convert_to_vector<location>(host::functions.invoke_raw_unary(__sqf::unary__nearestlocations__array__ret__array, args));
        }

        std::vector<location> nearest_locations(const object &unit_, sqf_string_list_const_ref location_types_, float radius_, const vector3 &sort_position_) {
            auto_array<game_value> loctypes(location_types_.begin(), location_types_.end());

            game_value args({unit_,
                             std::move(loctypes),
                             radius_,
                             sort_position_});

            return __helpers::__convert_to_vector<location>(host::functions.invoke_raw_unary(__sqf::unary__nearestlocations__array__ret__array, args));
        }
        
        std::vector<location> nearest_locations(const object &unit_, sqf_string_list_const_ref location_types_, float radius_, const object &sort_obj_) {
            auto_array<game_value> loctypes(location_types_.begin(), location_types_.end());

            game_value args({unit_,
                             std::move(loctypes),
                             radius_,
                             sort_obj_});

            return __helpers::__convert_to_vector<location>(host::functions.invoke_raw_unary(__sqf::unary__nearestlocations__array__ret__array, args));
        }
        
        
        sqf_return_string_list all_variables(const location &value_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__location__ret__array, value_));
        }
        sqf_return_string name(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__name__location__ret__string, loc_);
        }
        sqf_return_string type(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__type__location__ret__string, loc_);
        }

        // What a confusing command name.
        sqf_return_string class_name(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__classname__location__ret__string, loc_);
        }
        location create_location(sqf_string_const_ref classname_, const vector3 &pos_, float size_x_, float size_y_) {
            game_value params({classname_,
                               pos_,
                               size_x_,
                               size_y_});

            return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
        }

        location create_location(sqf_string_const_ref classname_, const vector2 &pos_, float size_x_, float size_y_) {
            game_value params({classname_,
                               pos_,
                               size_x_,
                               size_y_});

            return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
        }
        location create_location(sqf_string_const_ref classname_, const object &obj_, float size_x_, float size_y_) {
            game_value params({classname_,
                               obj_,
                               size_x_,
                               size_y_});

            return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
        }
        location location_null() {
            return __helpers::__retrieve_nular_location(__sqf::nular__locationnull__ret__location);
        }

        void set_rectangular(const location &location_, bool rectangular_) {
            host::functions.invoke_raw_binary(__sqf::binary__setrectangular__location__bool__ret__nothing, location_, rectangular_);
        }
        void set_size(const location &location_, float size_x_, float size_y_) {
            host::functions.invoke_raw_binary(__sqf::binary__setsize__location__array__ret__nothing, location_, {size_x_, size_y_});
        }
        void set_name(const location &location_, sqf_string_const_ref name_) {
            host::functions.invoke_raw_binary(__sqf::binary__setname__location__string__ret__nothing, location_, name_);
        }
        void set_speech(const location &location_, sqf_string_const_ref speech_) {
            host::functions.invoke_raw_binary(__sqf::binary__setspeech__location__string__ret__nothing, location_, speech_);
        }
        void set_text(const location &location_, sqf_string_const_ref text_) {
            host::functions.invoke_raw_binary(__sqf::binary__settext__location__string__ret__nothing, location_, text_);
        }

        void set_type(const location &location_, sqf_string_const_ref type_) {
            host::functions.invoke_raw_binary(__sqf::binary__settype__location__string__ret__nothing, location_, type_);
        }

        //draw/icon
        void update_draw_icon(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref string_identifier_, const rv_color &color_, const vector2 &offset_, float width_, float height_, bool maintain_size_, float angle_, int shadow_) {
            host::functions.invoke_raw_binary(__sqf::binary__updatedrawicon__control__array__ret__nothing, map_, {object_, string_identifier_, color_, offset_, width_, height_, maintain_size_, angle_, shadow_});
        }

        void draw_arrow(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, const rv_color &color_) {
            auto_array<game_value> params_right;

            switch (from_.index()) {
                case 0: params_right.push_back(std::get<0>(from_).get()); break;
                case 1: params_right.push_back(std::get<1>(from_).get()); break;
                case 2: params_right.push_back(std::get<2>(from_).get()); break;
            }
            switch (to_.index()) {
                case 0: params_right.push_back(std::get<0>(to_).get()); break;
                case 1: params_right.push_back(std::get<1>(to_).get()); break;
                case 2: params_right.push_back(std::get<2>(to_).get()); break;
            }
            params_right.push_back(color_);

            host::functions.invoke_raw_binary(__sqf::binary__drawarrow__control__array__ret__nothing, map_, std::move(params_right));
        }

        void draw_ellipse(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> center_, const vector2 &radius_, float angle_, const rv_color &color_, sqf_string_const_ref fill_texture) {
            auto_array<game_value> params_right;

            switch (center_.index()) {
                case 0: params_right.push_back(std::get<0>(center_).get()); break;
                case 1: params_right.push_back(std::get<1>(center_).get()); break;
                case 2: params_right.push_back(std::get<2>(center_).get()); break;
            }

            params_right.push_back(radius_.x);
            params_right.push_back(radius_.y);
            params_right.push_back(angle_);
            params_right.push_back(color_);
            params_right.push_back(fill_texture);

            host::functions.invoke_raw_binary(__sqf::binary__drawellipse__control__array__ret__nothing, map_, std::move(params_right));
        }

        void draw_line(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, const rv_color &color_) {
            auto_array<game_value> params_right;

            switch (from_.index()) {
                case 0: params_right.push_back(std::get<0>(from_).get()); break;
                case 1: params_right.push_back(std::get<1>(from_).get()); break;
                case 2: params_right.push_back(std::get<2>(from_).get()); break;
            }
            switch (to_.index()) {
                case 0: params_right.push_back(std::get<0>(to_).get()); break;
                case 1: params_right.push_back(std::get<1>(to_).get()); break;
                case 2: params_right.push_back(std::get<2>(to_).get()); break;
            }
            params_right.push_back(color_);

            host::functions.invoke_raw_binary(__sqf::binary__drawline__control__array__ret__nothing, map_, std::move(params_right));
        }

        void draw_link(const control &map_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> from_, std::variant<std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3>, std::reference_wrapper<const object>> to_, sqf_string_const_ref param_type_, sqf_string_const_ref line_type_, rv_color &color_) {
            auto_array<game_value> params_right;

            switch (from_.index()) {
                case 0: params_right.push_back(std::get<0>(from_).get()); break;
                case 1: params_right.push_back(std::get<1>(from_).get()); break;
                case 2: params_right.push_back(std::get<2>(from_).get()); break;
            }
            switch (to_.index()) {
                case 0: params_right.push_back(std::get<0>(to_).get()); break;
                case 1: params_right.push_back(std::get<1>(to_).get()); break;
                case 2: params_right.push_back(std::get<2>(to_).get()); break;
            }
            params_right.push_back(param_type_);
            params_right.push_back(line_type_);
            params_right.push_back(color_);

            host::functions.invoke_raw_binary(__sqf::binary__drawlink__control__array__ret__nothing, map_, std::move(params_right));
        }

        void draw_location(const control &map_, const location &location_) {
            host::functions.invoke_raw_binary(__sqf::binary__drawlocation__control__location__ret__nothing, map_, location_);
        }

        void draw_polygon(const control &map_, const std::vector<vector3> &polygon_, const rv_color &color_) {
            auto_array<game_value> polygon(polygon_.begin(), polygon_.end());

            game_value params_right({std::move(polygon),
                                     color_});

            host::functions.invoke_raw_binary(__sqf::binary__drawpolygon__control__array__ret__nothing, map_, params_right);
        }

        void remove_draw_icon(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref string_identifier) {
            game_value params_right({object_,
                                     string_identifier});

            host::functions.invoke_raw_binary(__sqf::binary__removedrawicon__control__array__ret__nothing, map_, params_right);
        }

        void remove_draw_links(const control &map_, sqf_string_const_ref object_, sqf_string_const_ref string_identifier) {
            game_value params_right({object_,
                                     string_identifier});

            host::functions.invoke_raw_binary(__sqf::binary__removedrawlinks__control__array__ret__nothing, map_, params_right);
        }

        void set_draw_icon(const control &map_, const object &object_, sqf_string_const_ref texture_, const rv_color &color_, const vector3 &offset_, float width_, float height_, float size_, float angle_, sqf_string_const_ref identifier_, float shadow_, bool is_3d_, bool draw_line_, float priority_) {
            game_value params_right({object_,
                                     texture_,
                                     color_,
                                     offset_,
                                     width_,
                                     height_,
                                     size_,
                                     angle_,
                                     identifier_,
                                     shadow_,
                                     is_3d_,
                                     draw_line_,
                                     priority_});

            host::functions.invoke_raw_binary(__sqf::binary__setdrawicon__control__array__ret__nothing, map_, params_right);
        }

        void disable_map_indicators(bool disableFriendly_, bool disableEnemy_, bool disableMines_, bool disablePing_) {
            host::functions.invoke_raw_unary(__sqf::unary__disablemapindicators__array__ret__nothing, {disableFriendly_, disableEnemy_, disableMines_, disablePing_});
        }

        sqf_return_string get_player_id(const object &player_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getplayerid__object__ret__string, player_);
        }

        sqf_return_string marker_channel(marker marker_) {
            return host::functions.invoke_raw_unary(__sqf::unary__markerchannel__string__ret__string, marker_);
        }

        std::vector<float> marker_polyline(marker marker_) {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_unary(__sqf::unary__markerpolyline__string__ret__array, marker_));
        }

        bool marker_shadow(marker marker_) {
            return host::functions.invoke_raw_unary(__sqf::unary__markershadow__string__ret__bool, marker_);
        }

        void set_marker_polyline(marker marker_, const std::vector<float> &polyline_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerpolyline__string__array__ret__nothing, marker_, polyline_);
        }

        void set_marker_polyline_local(marker marker_, const std::vector<float> &polyline_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerpolylinelocal__string__array__ret__nothing, marker_, polyline_);
        }

        void set_marker_shadow(marker marker_, bool shadow_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkershadow__string__bool__ret__nothing, marker_, shadow_);
        }

        void set_marker_shadow_local(marker marker_, bool shadow_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkershadowlocal__string__bool__ret__nothing, marker_, shadow_);
        }
    }  // namespace sqf
}  // namespace intercept
