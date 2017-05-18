#include "marker.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {

        std::string create_marker(const std::string &name_, const vector2 &pos_) {
            game_value params({
                name_,
                pos_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params);
        }

        std::string create_marker(const std::string &name_, const vector3 &pos_) {
            game_value params({
                name_,
                pos_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params);
        }

        std::string create_marker(const std::string &name_, const object &pos_) {
            game_value params({
                name_,
                pos_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__createmarker__array__ret__string, params);
        }

        std::string create_marker_local(const std::string &name_, const vector2 &pos_) {
            game_value params({
                name_,
                pos_,
            });

            return host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params);
        }

        std::string create_marker_local(const std::string &name_, const vector3 &pos_) {
            game_value params({
                name_,
                pos_,
            });

            return host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params);
        }

        std::string create_marker_local(const std::string &name_, const object &pos_) {
            game_value params({
                name_,
                pos_,
            });

            return host::functions.invoke_raw_unary(__sqf::unary__createmarkerlocal__array__ret__string, params);
        }

        void delete_marker(const std::string& value_) {
            __helpers::__empty_unary_string(__sqf::unary__deletemarker__string__ret__nothing, value_);
        }

        void delete_marker_local(const std::string& value_) {
            __helpers::__empty_unary_string(__sqf::unary__deletemarkerlocal__string__ret__nothing, value_);
        }

        void set_marker_type(const std::string& marker_, const std::string& type_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkertype__string__string__ret__nothing, marker_, type_);
        }

        void set_marker_type_local(const std::string& marker_, const std::string& type_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkertypelocal__string__string__ret__nothing, marker_, type_);
        }

        void set_marker_text(const std::string& marker_, const std::string& text_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkertext__string__string__ret__nothing, marker_, text_);
        }

        void set_marker_text_local(const std::string& marker_, const std::string& text_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkertextlocal__string__string__ret__nothing, marker_, text_);
        }

        void set_marker_size(const std::string& marker_, const vector2& size_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkersize__string__array__ret__nothing, marker_, size_);
        }

        void set_marker_size_local(const std::string& marker_, const vector2& size_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkersizelocal__string__array__ret__nothing, marker_, size_);
        }

        void set_marker_shape(const std::string& marker_, const std::string& shape_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkershape__string__string__ret__nothing, marker_, shape_);
        }

        void set_marker_shape_local(const std::string& marker_, const std::string& shape_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkershapelocal__string__string__ret__nothing, marker_, shape_);
        }

        void set_marker_pos(const std::string& marker_, const vector3& pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerpos__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos_local(const std::string& marker_, const vector3& pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerposlocal__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos(const std::string& marker_, const vector2& pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerpos__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_pos_local(const std::string& marker_, const vector2& pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerposlocal__string__array__ret__nothing, marker_, pos_);
        }

        void set_marker_brush(const std::string& marker_, const std::string& brush_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerbrush__string__string__ret__nothing, marker_, brush_);
        }

        void set_marker_brush_local(const std::string& marker_, const std::string& brush_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerbrushlocal__string__string__ret__nothing, marker_, brush_);
        }

        void set_marker_color(const std::string& marker_, const std::string& color_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkercolor__string__string__ret__nothing, marker_, color_);
        }

        void set_marker_color_local(const std::string& marker_, const std::string& color_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkercolorlocal__string__string__ret__nothing, marker_, color_);
        }

        void set_marker_alpha(const std::string& marker_, float alpha_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkeralpha__string__scalar__ret__nothing, marker_, alpha_);
        }

        void set_marker_alpha_local(const std::string& marker_, float alpha_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkeralphalocal__string__scalar__ret__nothing, marker_, alpha_);
        }

        void set_marker_dir(const std::string& marker_, float dir_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerdir__string__scalar__ret__nothing, marker_, dir_);
        }

        void set_marker_dir_local(const std::string& marker_, float dir_) {
            host::functions.invoke_raw_binary(__sqf::binary__setmarkerdirlocal__string__scalar__ret__nothing, marker_, dir_);
        }


        float marker_alpha(const std::string& value_) {
            return __helpers::__number_unary_string(__sqf::unary__markeralpha__string__ret__scalar, value_);
        }
        float marker_dir(const std::string& value_) {
            return __helpers::__number_unary_string(__sqf::unary__markerdir__string__ret__scalar, value_);
        }
        std::string marker_brush(const std::string& value_) {
            return __helpers::__string_unary_string(__sqf::unary__markerbrush__string__ret__string, value_);
        }

        std::string marker_color(const std::string& value_) {
            return __helpers::__string_unary_string(__sqf::unary__markercolor__string__ret__string, value_);
        }
        std::string marker_shape(const std::string& value_) {
            return __helpers::__string_unary_string(__sqf::unary__markershape__string__ret__string, value_);
        }
        std::string marker_text(const std::string& value_) {
            return __helpers::__string_unary_string(__sqf::unary__markertext__string__ret__string, value_);
        }
        std::string marker_type(const std::string& value_) {
            return __helpers::__string_unary_string(__sqf::unary__markertype__string__ret__string, value_);
        }

        std::string get_marker_color(const std::string& value_) {
            return __helpers::__string_unary_string(__sqf::unary__getmarkercolor__string__ret__string, value_);
        }

        std::string get_marker_type(const std::string& value_) {
            return __helpers::__string_unary_string(__sqf::unary__getmarkertype__string__ret__string, value_);
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
            return __helpers::__convert_to_markers_vector(host::functions.invoke_raw_nular(__sqf::nular__allmapmarkers__ret__array));
        }













































        //Locations





        namespace __helpers {
            vector3 get_pos_loc(unary_function fnc_, const location & loc_) {
                return host::functions.invoke_raw_unary(fnc_, loc_);
            }
        }






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
        void attach_object(const location& location_, const object& object_) {
            host::functions.invoke_raw_binary(__sqf::binary__attachobject__location__object__ret__nothing, location_, object_);
        }
        bool is_null(const location& loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__location__ret__bool, loc_);
        }
        bool rectangular(const location& loc_) {
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
        float distance(const location& start_, const location& end_) {
            return host::functions.invoke_raw_binary(__sqf::binary__distance__location__location__ret__scalar, start_, end_);
        }

        float distance(const location& start_, const vector3& end_) {
            return host::functions.invoke_raw_binary(__sqf::binary__distance__location__array__ret__scalar, start_, end_);
        }

        float distance(const vector3& start_, const location& end_) {
            return host::functions.invoke_raw_binary(__sqf::binary__distance__array__location__ret__scalar, start_, end_);
        }
        location nearest_location(const vector3& pos_, const std::string& location_class_) {
            game_value args({
                pos_,
                location_class_
            });

            return location(host::functions.invoke_raw_unary(__sqf::unary__nearestlocation__array__ret__location, args));
        }

        location nearest_location(const object& unit_, const std::string& location_class_) {
            game_value args({
                unit_,
                location_class_
            });

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
        vector3 position(const location& loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__position__location__ret__array, loc_);
        }
        vector2 size(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__size__location__ret__array, loc_);
        }
        vector3 get_pos(const location & loc_) {
            return __helpers::get_pos_loc(__sqf::unary__getpos__location__ret__array, loc_);
        }
        vector2 location_position(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__locationposition__location__ret__array, loc_);
        }
        std::vector<location> nearest_locations(const vector3& pos_, std::vector<std::string>& location_types_, float radius_) {
            auto_array<game_value> loctypes(location_types_.begin(), location_types_.end());

            game_value args({
                pos_,
                std::move(loctypes),
                radius_
            });

            return __helpers::__convert_to_locations_vector(host::functions.invoke_raw_unary(__sqf::unary__nearestlocation__array__ret__location, args));
        }

        std::vector<location> nearest_locations(const vector3& pos_, std::vector<std::string>& location_types_, float radius_, const vector3& sort_position_) {
            auto_array<game_value> loctypes(location_types_.begin(), location_types_.end());

            game_value args({
                pos_,
                std::move(loctypes),
                radius_,
                sort_position_
            });

            return __helpers::__convert_to_locations_vector(host::functions.invoke_raw_unary(__sqf::unary__nearestlocation__array__ret__location, args));

        }

        std::vector<location> nearest_locations(const object& unit_, std::vector<std::string>& location_types_, float radius_) {
            auto_array<game_value> loctypes(location_types_.begin(), location_types_.end());

            game_value args({
                unit_,
                std::move(loctypes),
                radius_
            });

            return __helpers::__convert_to_locations_vector(host::functions.invoke_raw_unary(__sqf::unary__nearestlocation__array__ret__location, args));
        }

        std::vector<location> nearest_locations(const object& unit_, std::vector<std::string>& location_types_, float radius_, const vector3& sort_position_) {
            auto_array<game_value> loctypes(location_types_.begin(), location_types_.end());

            game_value args({
                unit_,
                std::move(loctypes),
                radius_,
                sort_position_
            });

            return __helpers::__convert_to_locations_vector(host::functions.invoke_raw_unary(__sqf::unary__nearestlocation__array__ret__location, args));
        }
        std::vector<location> nearest_locations(const vector3 pos_, const std::vector<std::string> &loc_types_, float radius_) {
            auto_array<game_value> loc_types(loc_types_.begin(), loc_types_.end());

            game_value params({
                pos_,
                std::move(loc_types),
                radius_
            });

            return __helpers::__convert_to_locations_vector(host::functions.invoke_raw_unary(__sqf::unary__nearestlocations__array__ret__array, params));
        }

        std::vector<location> nearest_locations(const vector3 pos_, const std::vector<std::string> &loc_types_, float radius_, const vector3 &sort_pos_) {
            auto_array<game_value> loc_types(loc_types_.begin(), loc_types_.end());

            game_value params({
                pos_,
                std::move(loc_types),
                radius_,
                sort_pos_
            });

            return __helpers::__convert_to_locations_vector(host::functions.invoke_raw_unary(__sqf::unary__nearestlocations__array__ret__array, params));
        }

        std::vector<location> nearest_locations(const vector3 pos_, const std::vector<std::string> &loc_types_, float radius_, const object &sort_obj_) {
            auto_array<game_value> loc_types(loc_types_.begin(), loc_types_.end());

            game_value params({
                pos_,
                std::move(loc_types),
                radius_,
                sort_obj_
            });

            return __helpers::__convert_to_locations_vector(host::functions.invoke_raw_unary(__sqf::unary__nearestlocations__array__ret__array, params));
        }
        std::vector<std::string> all_variables(const location &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__location__ret__array, value_));
        }
        std::string name(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__name__location__ret__string, loc_);
        }
        std::string type(const location& loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__type__location__ret__string, loc_);
        }
        game_value get_variable(const location & loc_, const std::string & var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__location__string__ret__any, loc_, var_name_);
        }
        // What a confusing command name.
        std::string class_name(const location &loc_) {
            return host::functions.invoke_raw_unary(__sqf::unary__classname__location__ret__string, loc_);
        }
        location create_location(const std::string &classname_, const vector3 &pos_, float size_x_, float size_y_) {
            game_value params({
                classname_,
                pos_,
                size_x_,
                size_y_
            });

            return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
        }

        location create_location(const std::string &classname_, const vector2 & pos_, float size_x_, float size_y_) {
            game_value params({
                classname_,
                pos_,
                size_x_,
                size_y_
            });

            return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
        }
        location create_location(const std::string &classname_, const object &obj_, float size_x_, float size_y_) {
            game_value params({
                classname_,
                obj_,
                size_x_,
                size_y_
            });

            return location(host::functions.invoke_raw_unary(__sqf::unary__createlocation__array__ret__location, params));
        }
        location location_null() {
            return __helpers::__retrieve_nular_location(__sqf::nular__locationnull__ret__location);
        }



















        //Trigger

        rv_trigger_area trigger_area(const object& trigger_) {
            return rv_trigger_area(host::functions.invoke_raw_unary(__sqf::unary__triggerarea__object__ret__array, trigger_));
        }

        rv_trigger_timeout trigger_timeout(const object& trigger_) {
            return rv_trigger_timeout(host::functions.invoke_raw_unary(__sqf::unary__triggertimeout__object__ret__array, trigger_));
        }
        std::vector<object> list(const object& trigger_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__list__object__ret__array, trigger_);

            if (ret.size() == 0) return {};
            
            return __helpers::__convert_to_objects_vector(ret);
        }
        void trigger_attach_object(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__triggerattachobject__object__scalar__ret__nothing, value0_, value1_);
        }
        void set_trigger_text(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__settriggertext__object__string__ret__nothing, value0_, value1_);
        }

        void set_trigger_type(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__settriggertype__object__string__ret__nothing, value0_, value1_);
        }
        bool trigger_activated(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__triggeractivated__object__ret__bool, value_);
        }

        object trigger_attached_vehicle(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__triggerattachedvehicle__object__ret__object, value_);
        }

        std::string trigger_text(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__triggertext__object__ret__string, value_);
        }

        float trigger_timeout_current(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__triggertimeoutcurrent__object__ret__scalar, value_);
        }

        std::string trigger_type(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__triggertype__object__ret__string, value_);
        }
        object create_trigger(const std::string &type_, const vector3 &pos_, bool make_global_/* = true*/) {
            game_value args({
                type_,
                pos_,
                make_global_
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createtrigger__array__ret__object, args));
        }

        object create_trigger(const std::string &type_, const object &pos_, bool make_global_ /*= true*/) {
            game_value args({
                type_,
                pos_,
                make_global_
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createtrigger__array__ret__object, args));
        }


    }
}
