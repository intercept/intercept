/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)
@author Senfo (lpsenfo@gmail.com)

@brief Cargo related Function wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {

        //cargo
        bool set_vehicle_cargo(const object &vehicle_, const object &cargo_);
        std::vector<object> assigned_cargo(const object &veh_);
        std::vector<object> get_vehicle_cargo(const object &vehicle_);
        object is_vehicle_cargo(const object &vehicle_);
        bool vehicle_cargo_enabled(const object &vehicle_);
        std::pair<bool, bool> can_vehicle_cargo(const object &vehicle_, const object &cargo_);
        void enable_vehicle_cargo(const object &vehicle_, bool enable_);

        bool can_sling_load(const object &vehicle_, const object &cargo_);
        bool sling_load_assistant_shown();
        bool set_sling_load(const object &vehicle_, const object &load_);
        object get_sling_load(const object &value_);

        //rope
        void rope_attach_to(const object &vehicle_, const vector3 &offset_, const vector3 &rope_end_down_dir_, const object &rope_);
        void rope_detach(const object &vehicle_, const object &rope_);
        bool rope_attach_enabled(const object &value_);
        object rope_attached_to(const object &value_);
        void rope_destroy(const object &value_);
        float rope_length(const object &value_);
        bool rope_unwound(const object &value_);
        void enable_rope_attach(const object &value0_, bool value1_);
        std::vector<object> rope_attached_objects(const object &obj_);
        std::vector<object> ropes(const object &obj_);
        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, const vector3 &to_point_, float segments_);
        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, const vector3 &to_point_, float segments_, float length_);
        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_, const object &to_obj_, const vector3 &to_point_, float segments_);
        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_, const object &to_obj_, const vector3 &to_point_, float segments_, float length_);
        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, sqf_string_const_ref to_point_, float segments_);
        object rope_create(const object &from_obj_, const vector3 &from_point_, const object &to_obj_, sqf_string_const_ref to_point_, float segments_, float length_);
        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_, const object &to_obj_, sqf_string_const_ref to_point_, float segments_);
        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_, const object &to_obj_, sqf_string_const_ref to_point_, float segments_, float length_);
        object rope_create(const object &from_obj_, const vector3 &from_point_);
        object rope_create(const object &from_obj_, const vector3 &from_point_, float length_);
        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_);
        object rope_create(const object &from_obj_, sqf_string_const_ref from_point_, float length_);

        void rope_cut(const object &rope_, float distance_);

        std::vector<vector3> rope_end_position(const object &rope_);

        void rope_unwind(const object &rope_, float speed_, float length_);
        void rope_unwind(const object &rope_, float speed_, float length_, bool relative_);

        //attach
        void light_attach_object(const object &light_, const object &object_, const vector3 &offset_);
        void light_detach_object(const object &value_);

        std::vector<object> attached_objects(const object &obj_);
        object attached_to(const object &obj_);
        void attach_to(const object &object1_, const object &object2_, const vector3 &offset_, sqf_string_const_ref memPoint_);
        void attach_to(const object &object1_, const object &object2_, const vector3 &offset_);
        void detach(const object &value_);
        int get_cargo_index(const object &vehicle_, const object &unit_);
    }  // namespace sqf
}  // namespace intercept
