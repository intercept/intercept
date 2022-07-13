#include "intersects.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {

        intersect_surfaces::intersect_surfaces(const game_value &gv_)
            : intersect_pos_asl(gv_[0]),
              surface_normal(gv_[1]),
              intersect_object(gv_[2]),
              parent_object(gv_[3]),
              selection_names(__helpers::__convert_to_vector<sqf_return_string>(gv_[4])),
              bisurf_path(gv_[5])
        {
        }

        intersect_result_list intersect(const object &obj_, sqf_string_const_ref lodname_, const vector3 &begin_pos_, const vector3 &end_pos_) {
            return __helpers::__convert_to_vector<intersect_result>(host::functions.invoke_raw_binary(__sqf::binary__intersect__array__array__ret__array, {obj_, lodname_}, {begin_pos_, end_pos_}));
        }

        intersect_surfaces_list line_intersects_surfaces(const vector3 &begin_pos_asl_, const vector3 &end_pos_asl_) {
            return __helpers::__convert_to_vector<intersect_surfaces>(host::functions.invoke_raw_unary(__sqf::unary__lineintersectssurfaces__array__ret__array, {begin_pos_asl_, end_pos_asl_}));
        }

        intersect_surfaces_list line_intersects_surfaces(const vector3 &begin_pos_asl_, const vector3 &end_pos_asl_, const object &ignore_obj1_) {
            return __helpers::__convert_to_vector<intersect_surfaces>(host::functions.invoke_raw_unary(__sqf::unary__lineintersectssurfaces__array__ret__array, {begin_pos_asl_, end_pos_asl_, ignore_obj1_}));
        }

        intersect_surfaces_list line_intersects_surfaces(const vector3 &begin_pos_asl_, const vector3 &end_pos_asl_, const object &ignore_obj1_, const object &ignore_obj2_, bool sort_mode_, int max_results_, sqf_string_const_ref lod1_, sqf_string_const_ref lod2_, bool unique_objs_) {
            return __helpers::__convert_to_vector<intersect_surfaces>(host::functions.invoke_raw_unary(__sqf::unary__lineintersectssurfaces__array__ret__array, {begin_pos_asl_, end_pos_asl_, ignore_obj1_, ignore_obj2_, sort_mode_, static_cast<float>(max_results_), lod1_, lod2_, unique_objs_}));
        }

        std::vector<object> line_intersects_with(const vector3 &begin_pos_, const vector3 &end_pos_, bool sort_by_distance_) {
            game_value array_input({begin_pos_,
                                    end_pos_,
                                    game_value(),
                                    game_value(),
                                    sort_by_distance_});
            game_value intersects_value = host::functions.invoke_raw_unary(__sqf::unary__lineintersectswith__array__ret__array, array_input);

            return __helpers::__convert_to_vector<object>(intersects_value);
        }

        std::vector<object> line_intersects_with(const vector3 &begin_pos_, const vector3 &end_pos_, std::initializer_list<object> ignored_objects_, bool sort_by_distance_) {
            game_value array_input({ begin_pos_,
                end_pos_,
                ignored_objects_.size() > 0 ? game_value(*ignored_objects_.begin()) : game_value(),
                ignored_objects_.size() > 1 ? game_value(*(ignored_objects_.begin() + 1)) : game_value(),
                sort_by_distance_ });
            game_value intersects_value = host::functions.invoke_raw_unary(__sqf::unary__lineintersectswith__array__ret__array, array_input);
            if (ignored_objects_.size() > 2) {//filter out the other objects
                                              //modified variant of __helpers::__convert_to_vector<object>
                std::vector<object> output;
                if (intersects_value.size() == 0) return {};
                output.reserve(intersects_value.size());
                for (auto &gv : intersects_value.to_array()) {
                    if (std::find(ignored_objects_.begin(), ignored_objects_.end(), gv) == ignored_objects_.end())//Not in ignore list
                        output.emplace_back(object(gv));
                }
                return output;
            }

            return __helpers::__convert_to_vector<object>(intersects_value);
        }

        bool terrain_intersect(const vector3 &begin_pos_, const vector3 &end_pos_) {
            game_value array_input({begin_pos_,
                                    end_pos_});

            return host::functions.invoke_raw_unary(__sqf::unary__terrainintersect__array__ret__bool, array_input);
        }

        bool terrain_intersect_asl(const vector3 &begin_pos_, const vector3 &end_pos_) {
            game_value array_input({begin_pos_,
                                    end_pos_});
            return host::functions.invoke_raw_unary(__sqf::unary__terrainintersectasl__array__ret__bool, array_input);
        }

        bool line_intersects(const vector3 &begin_position_, const vector3 &end_position_) {
            game_value array_input({begin_position_,
                                    end_position_});
            return host::functions.invoke_raw_unary(__sqf::unary__lineintersects__array__ret__bool, array_input);
        }

        bool line_intersects(const vector3 &begin_position_, const vector3 &end_position_, const object &ignore_obj_one_) {
            game_value array_input({begin_position_,
                                    end_position_,
                                    ignore_obj_one_});
            return host::functions.invoke_raw_unary(__sqf::unary__lineintersects__array__ret__bool, array_input);
        }

        bool line_intersects(const vector3 &begin_position_, const vector3 &end_position_, const object &ignore_obj_one_, const object &ignore_obj_two_) {
            game_value array_input({begin_position_,
                                    end_position_,
                                    ignore_obj_one_,
                                    ignore_obj_two_});
            return host::functions.invoke_raw_unary(__sqf::unary__lineintersects__array__ret__bool, array_input);
        }

        std::vector<object> line_intersects_objs(const vector3 &begin_position_, const vector3 &end_position_, const object &with_obj_, std::initializer_list<object> ignored_objects_, bool sort_by_distance_, int flags_) {
            game_value array_input({begin_position_,
                                    end_position_,
                                    with_obj_,
                                    ignored_objects_.size() > 0 ? game_value(*ignored_objects_.begin()) : game_value(),
                                    sort_by_distance_,
                                    static_cast<float>(flags_)});

            game_value intersects_value = host::functions.invoke_raw_unary(__sqf::unary__lineintersectsobjs__array__ret__array, array_input);

            if (ignored_objects_.size() > 1) {//filter out the other objects
                                              //modified variant of __helpers::__convert_to_vector<object>
                std::vector<object> output;
                if (intersects_value.size() == 0) return {};
                output.reserve(intersects_value.size());
                for (auto &gv : intersects_value.to_array()) {
                    if (std::find(ignored_objects_.begin(), ignored_objects_.end(), gv) == ignored_objects_.end())//Not in ignore list
                        output.emplace_back(object(gv));
                }
                return output;
            }

            return __helpers::__convert_to_vector<object>(intersects_value);
        }

        vector3 terrain_intersect_at_asl(const vector3 &pos1_, const vector3 &pos2_) {
            game_value params({pos1_,
                               pos2_});

            return host::functions.invoke_raw_unary(__sqf::unary__terrainintersectatasl__array__ret__array, params);
        }

        float check_visibility(const object &ignore_, sqf_string_const_ref lodname_, const vector3 &begin_pos_, const vector3 &end_pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__checkvisibility__array__array__ret__scalar, {ignore_, lodname_}, {begin_pos_, end_pos_});
        }

        float check_visibility(const object &ignore_, sqf_string_const_ref lodname_, const object &ignore2_, const vector3 &begin_pos_, const vector3 &end_pos_) {
            return host::functions.invoke_raw_binary(__sqf::binary__checkvisibility__array__array__ret__scalar, {ignore_, lodname_, ignore2_}, {begin_pos_, end_pos_});
        }
    }  // namespace sqf
}  // namespace intercept
