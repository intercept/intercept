#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        namespace __helpers {
            bool line_intersects_with(game_value& array_input);
        }
        struct intersect_surfaces {
            vector3 intersectPosASL; //- the actual position where line intersects 1st surface
            std::string surfaceNormal; //- a normal to the intersected surface
            object intersectObject; //- the object the surface belongs to(could be proxy object)
            object parentObject; //- the object proxy object belongs to(not always the same as intersect object)
        };
        typedef std::vector<std::shared_ptr<intersect_surfaces>> intersect_surfaces_list;

        bool intersect (vector3 begin_pos_, vector3 end_pos_, const object& obj_, std::string lodname_); 
        
        intersect_surfaces_list line_intersects_surfaces (vector3 begin_pos_asl_, vector3 end_pos_asl_); 
        intersect_surfaces_list line_intersects_surfaces (vector3 begin_pos_asl_, vector3 end_pos_asl_, const object& ignore_obj1_); 
        intersect_surfaces_list line_intersects_surfaces (vector3 begin_pos_asl_, vector3 end_pos_asl_, const object& ignore_obj1_, const object& ignore_obj2_); 
        intersect_surfaces_list line_intersects_surfaces (vector3 begin_pos_asl_, vector3 end_pos_asl_, const object& ignore_obj1_, const object& ignore_obj2_, bool sort_mode_ = true, int max_results_ = 1, std::string lod1_ = "VIEW", std::string lod2_ = "FIRE"); 
        
        bool line_intersects_with (vector3 begin_pos_, vector3 end_pos_, const object& ignore_obj1_ = nullptr, const object& ignore_obj2_ = nullptr, bool sort_by_distance_ = true);
        
        bool terrain_intersect (vector3 begin_pos_, vector3 end_pos_); 
        bool terrain_intersect_asl (vector3 begin_pos_, vector3 end_pos_); 

        bool line_intersects(vector3 begin_position_, vector3 end_position_);
        bool line_intersects(vector3 begin_position_, vector3 end_position_, const object& ignore_obj_one_);
        bool line_intersects(vector3 begin_position_, vector3 end_position_, const object& ignore_obj_one_, const object& ignore_obj_two_);

        std::vector<object> line_intersects_objs(vector3 begin_position_, vector3 end_position_, const object& with_object_, const object& ignore_obj_, bool sort_by_distance_, int flags_);

    }
}
