#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
		struct intersect_surfaces {
			vector3 intersectPosASL; // the actual position where line intersects 1st surface
			std::string surfaceNormal; // a normal to the intersected surface
			object intersectObject; // the object the surface belongs to(could be proxy object)
			object parentObject; // the object proxy object belongs to(not always the same as intersect object)
		};

		namespace intersects {

			typedef std::vector<std::shared_ptr<intersect_surfaces>> intersect_surfaces_list;

			namespace __helpers {
				intersect_surfaces_list __line_intersects_surfaces(game_value& intersects_value_);
			}

			/**
			* Finds named selections in object which are in specified LOD, intersected by given section of a line
			*/
			bool intersect(vector3 begin_pos_, vector3 end_pos_, const object& obj_, std::string lodname_);

			/**
			* Returns list of intersections with surfaces from begPosASL to endPosASL.
			* If there is ground intersection, it is also included. Works on units. Works underwater.
			* Doesn't return intersection with sea surface. Hardcoded max distance: 5000m.
			* Biki: https://community.bistudio.com/wiki/lineIntersectsSurfaces
			*
			* @params begin_pos_asl_: PositionASL - virtual line start
			* @params end_pos_asl_: PositionASL - virtual line end
			*
			* @returns vector of intersections in format [[intersectPosASL, surfaceNormal, intersectObj, parentObject],...]
			*/
			intersect_surfaces_list line_intersects_surfaces(vector3 begin_pos_asl_, vector3 end_pos_asl_);

			/**
			* Returns list of intersections with surfaces from begPosASL to endPosASL.
			* If there is ground intersection, it is also included. Works on units. Works underwater.
			* Doesn't return intersection with sea surface. Hardcoded max distance: 5000m.
			* Biki: https://community.bistudio.com/wiki/lineIntersectsSurfaces
			*
			* @params begin_pos_asl_: PositionASL - virtual line start
			* @params end_pos_asl_: PositionASL - virtual line end
			* @params ignore_obj1_ (Optional) first object to ignore or objNull: Default: objNull
			*
			* @returns vector of intersections in format [[intersectPosASL, surfaceNormal, intersectObj, parentObject],...]
			*/
			intersect_surfaces_list line_intersects_surfaces(vector3 begin_pos_asl_, vector3 end_pos_asl_, const object& ignore_obj1_);

			/**
			* Returns list of intersections with surfaces from begPosASL to endPosASL.
			* If there is ground intersection, it is also included. Works on units. Works underwater.
			* Doesn't return intersection with sea surface. Hardcoded max distance: 5000m.
			* Biki: https://community.bistudio.com/wiki/lineIntersectsSurfaces
			*
			* @params begin_pos_asl_: PositionASL - virtual line start
			* @params end_pos_asl_: PositionASL - virtual line end
			* @params ignore_obj1_ (Optional) first object to ignore or objNull: Default: objNull
			* @params ignore_obj2_ (Optional) second object to ignore or objNull: Default: objNull
			* @params sort_mode_ (Optional): true: closest to furthest, false: furthest to closest. Default: true
			* @params max_results_ (Optional) Max results to return. -1 to return every result. Default: 1
			* @params lod1_ (Optional) Primary LOD to look for intersection. Default: "VIEW"
			* @params lod2_ (Optional) Secondary LOD to look for intersection. Default: "FIRE"
			*
			* @returns vector of intersections in format [[intersectPosASL, surfaceNormal, intersectObj, parentObject],...]
			*/
			intersect_surfaces_list line_intersects_surfaces(vector3 begin_pos_asl_, vector3 end_pos_asl_, const object& ignore_obj1_, const object& ignore_obj2_, bool sort_mode_, int max_results_, std::string lod1_, std::string lod2_);

			/**
			* Returns objects intersecting with the virtual line from begPos to endPos
			*/
			std::vector<object> line_intersects_with(vector3 begin_pos_, vector3 end_pos_, bool sort_by_distance_);
            std::vector<object> line_intersects_with(vector3 begin_pos_, vector3 end_pos_, bool sort_by_distance_, const object & ignore_obj_one_);
            std::vector<object> line_intersects_with(vector3 begin_pos_, vector3 end_pos_, bool sort_by_distance_, const object & ignore_obj_one_, const object & ignore_obj_two_);

            /**
			* Checks for intersection of terrain between two positions. Returns true if intersects with terrain. Uses PositionAGL
			*/
			bool terrain_intersect(vector3 begin_pos_, vector3 end_pos_);

			/**
			* Checks for intersection of terrain between two positions. Returns true if intersects with terrain. Uses PositionASL
			*/
			bool terrain_intersect_asl(vector3 begin_pos_, vector3 end_pos_);

			/**
			* Checks for object intersection with a virtual line between two positions. Returns true if intersects with an object.
			*/
			bool line_intersects(vector3 begin_position_, vector3 end_position_);

			/**
			* Checks for object intersection with a virtual line between two positions. Returns true if intersects with an object.
			*/
			bool line_intersects(vector3 begin_position_, vector3 end_position_, const object& ignore_obj_one_);

			/**
			* Checks for object intersection with a virtual line between two positions. Returns true if intersects with an object.
			*/
			bool line_intersects(vector3 begin_position_, vector3 end_position_, const object& ignore_obj_one_, const object& ignore_obj_two_);

			/**
			* Find list of objects intersected by given line from begin_position_ to end_position_
			*/
			std::vector<object> line_intersects_objs(vector3 begin_position_, vector3 end_position_, const object& with_object_, const object& ignore_obj_, bool sort_by_distance_, int flags_);
		}
    }
}
