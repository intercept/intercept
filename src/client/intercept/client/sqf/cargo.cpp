#include "cargo.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {

        //cargo
        bool set_vehicle_cargo(const object &vehicle_, const object &cargo_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setvehiclecargo__object__object__ret__bool, vehicle_, cargo_);
        }

        std::vector<object> assigned_cargo(const object &veh_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__assignedcargo__object__ret__array, veh_));
        }

        std::vector<object> get_vehicle_cargo(const object &vehicle_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__getvehiclecargo__object__ret__array, vehicle_));
        }

        object is_vehicle_cargo(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isvehiclecargo__object__ret__object, vehicle_);
        }

        bool vehicle_cargo_enabled(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__vehiclecargoenabled__object__ret__bool, vehicle_);
        }

        std::pair<bool, bool> can_vehicle_cargo(const object &vehicle_, const object &cargo_) {
            game_value res = host::functions.invoke_raw_binary(__sqf::binary__canvehiclecargo__object__object__ret__array, vehicle_, cargo_);

            return std::pair<bool, bool>({res[0], res[1]});
        }

        void enable_vehicle_cargo(const object &vehicle_, bool enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablevehiclecargo__object__bool__ret__nothing, vehicle_, enable_);
        }

        //sling
        bool can_sling_load(const object &vehicle_, const object &cargo_) {
            return host::functions.invoke_raw_binary(__sqf::binary__canslingload__object__object__ret__bool, vehicle_, cargo_);
        }

        bool set_sling_load(const object &vehicle_, const object &load_) {
            return host::functions.invoke_raw_binary(__sqf::binary__setslingload__object__object__ret__bool, vehicle_, load_);
        }

        bool sling_load_assistant_shown() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__slingloadassistantshown__ret__bool);
        }

        object get_sling_load(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__getslingload__object__ret__object, value_);
        }

        //rope
        bool rope_attach_enabled(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__ropeattachenabled__object__ret__bool, value_);
        }

        object rope_attached_to(const object &value_) {
            return __helpers::__object_unary_object(__sqf::unary__ropeattachedto__object__ret__object, value_);
        }

        void rope_destroy(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__ropedestroy__object__ret__nothing, value_);
        }

        float rope_length(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__ropelength__object__ret__scalar, value_);
        }

        bool rope_unwound(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__ropeunwound__object__ret__bool, value_);
        }

        void enable_rope_attach(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableropeattach__object__bool__ret__nothing, value0_, value1_);
        }

        std::vector<object> rope_attached_objects(const object &obj_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__ropeattachedobjects__object__ret__array, obj_));
        }

        std::vector<object> ropes(const object &obj_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__ropes__object__ret__array, obj_));
        }

        std::vector<object> ropes_attached_to(const object &cargo_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__ropesattachedto__object__ret__array, cargo_));
         }

        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, const vector3 &to_point_, float segments_) {
            game_value params({from_obj_,
                               from_point_,
                               to_obj_,
                               to_point_,
                               segments_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, const vector3 &to_point_, float segments_, float length_) {
            game_value params({from_obj_,
                               from_point_,
                               to_obj_,
                               to_point_,
                               segments_,
                               length_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_, const object &to_obj_, const vector3 &to_point_, float segments_) {
            game_value params({from_obj_,
                               from_point_,
                               to_obj_,
                               to_point_,
                               segments_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_, const object &to_obj_, const vector3 &to_point_, float segments_, float length_) {
            game_value params({from_obj_,
                               from_point_,
                               to_obj_,
                               to_point_,
                               segments_,
                               length_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, sqf_string_const_ref to_point_, float segments_) {
            game_value params({from_obj_,
                               from_point_,
                               to_obj_,
                               to_point_,
                               segments_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, sqf_string_const_ref to_point_, float segments_, float length_) {
            game_value params({from_obj_,
                               from_point_,
                               to_obj_,
                               to_point_,
                               segments_,
                               length_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_, const object &to_obj_, sqf_string_const_ref to_point_, float segments_) {
            game_value params({from_obj_,
                               from_point_,
                               to_obj_,
                               to_point_,
                               segments_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_, const object &to_obj_, sqf_string_const_ref to_point_, float segments_, float length_) {
            game_value params({from_obj_,
                               from_point_,
                               to_obj_,
                               to_point_,
                               segments_,
                               length_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        object rope_create(const object &from_obj_, const vector3 &from_point_) {
            game_value params({from_obj_,
                               from_point_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        object rope_create(const object &from_obj_, const vector3 &from_point_, float length_) {
            game_value params({from_obj_,
                               from_point_,
                               length_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_) {
            game_value params({from_obj_,
                               from_point_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_, float length_) {
            game_value params({from_obj_,
                               from_point_,
                               length_});

            return host::functions.invoke_raw_unary(__sqf::unary__ropecreate__array__ret__object, params);
        }

        void rope_cut(const object &rope_, float distance_) {
            game_value params({rope_,
                               distance_});

            host::functions.invoke_raw_unary(__sqf::unary__ropecut__array__ret__nothing, params);
        }

        std::vector<vector3> rope_end_position(const object &rope_) {
            game_value ret = host::functions.invoke_raw_unary(__sqf::unary__ropeendposition__object__ret__array, rope_);
            return __helpers::__convert_to_vector<vector3>(ret);
        }

        void rope_unwind(const object &rope_, float speed_, float length_) {
            game_value params({rope_,
                               speed_,
                               length_});

            host::functions.invoke_raw_unary(__sqf::unary__ropeunwind__array__ret__nothing, params);
        }

        void rope_unwind(const object &rope_, float speed_, float length_, bool relative_) {
            game_value params({rope_,
                               speed_,
                               length_,
                               relative_});

            host::functions.invoke_raw_unary(__sqf::unary__ropeunwind__array__ret__nothing, params);
        }

        void rope_attach_to(const object &vehicle_, const vector3 &offset_, const vector3 &rope_end_down_dir_, const object &rope_) {
            game_value params_left({vehicle_,
                                    offset_,
                                    rope_end_down_dir_});

            host::functions.invoke_raw_binary(__sqf::binary__ropeattachto__object_array__object__ret__nothing, params_left, rope_);
        }

        void rope_attach_to(const object &entity_, const object &rope_) {
            host::functions.invoke_raw_binary(__sqf::binary__ropeattachto__object_array__object__ret__nothing, entity_, rope_);
        }

        void rope_detach(const object &vehicle_, const object &rope_) {
            host::functions.invoke_raw_binary(__sqf::binary__ropedetach__object__object__ret__nothing, vehicle_, rope_);
        }

        //attach
        std::vector<object> attached_objects(const object &obj_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__attachedobjects__object__ret__array, obj_));
        }

        object attached_to(const object &obj_) {
            return object(host::functions.invoke_raw_unary(__sqf::unary__attachedto__object__ret__object, obj_));
        }

        void attach_to(const object &object1_, const object &object2_, const vector3 &offset_, sqf_string_const_ref memPoint_, bool follow_bone_) {
            host::functions.invoke_raw_binary(__sqf::binary__attachto__object__array__ret__nothing, object1_, {object2_, offset_, memPoint_, follow_bone_});
        }

        void attach_to(const object &object1_, const object &object2_, const vector3 &offset_) {
            host::functions.invoke_raw_binary(__sqf::binary__attachto__object__array__ret__nothing, object1_, {object2_, offset_});
        }

        void detach(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__detach__object__ret__nothing, value_);
        }

        void light_detach_object(const object &value_) {
            __helpers::__empty_unary_object(__sqf::unary__lightdetachobject__object__ret__nothing, value_);
        }

        void light_attach_object(const object &light_, const object &object_, const vector3 &offset_) {
            host::functions.invoke_raw_binary(__sqf::binary__lightattachobject__object__array__ret__nothing, light_, {object_, offset_});
        }

        int get_cargo_index(const object &vehicle_, const object &unit_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getcargoindex__object__object__ret__scalar, vehicle_, unit_);
        }

        std::vector<object> rope_segments(const object &rope_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__ropesegments__object__ret__array, rope_));
        }
    }  // namespace sqf
}  // namespace intercept
