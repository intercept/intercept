/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Intersection command wrappers.

These are commands that are used to test 3D intersections and collisions in the
game world.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        struct intersect_surfaces {
            vector3 intersect_pos_asl;  ///< the actual position where line intersects 1st surface
            vector3 surface_normal;     ///< a normal to the intersected surface
            object intersect_object;    ///< the object the surface belongs to(could be proxy object)
            object parent_object;       ///< the object proxy object belongs to(not always the same as intersect object)
            sqf_return_string_list selection_names;  // selection name
            sqf_return_string bisurf_path;     // path to the bisurf (surfuse properties)
            explicit intersect_surfaces(const game_value &gv_);
        };
        typedef std::vector<intersect_surfaces> intersect_surfaces_list;

        struct intersect_result {
            sqf_string selection_name;
            float intersect_distance;
            explicit intersect_result(const game_value &gv_)
                : selection_name(gv_[0]),
                  intersect_distance(gv_[1]) {}
        };
        typedef std::vector<intersect_result> intersect_result_list;

        /**
        * Finds named selections in object which are in specified LOD, intersected by given section of a line
        */
        intersect_result_list intersect(const object& obj_, sqf_string_const_ref lodname_, const vector3 &begin_pos_, const vector3& end_pos_);

        /**
        * Returns list of intersections with surfaces from begPosASL to endPosASL.
        * If there is ground intersection, it is also included. Works on units. Works underwater.
        * Doesn't return intersection with sea surface. Hardcoded max distance: 5000m.
        * Biki: https://community.bistudio.com/wiki/lineIntersectsSurfaces
        *
        * @param begin_pos_asl_: PositionASL - virtual line start
        * @param end_pos_asl_: PositionASL - virtual line end
        *
        * @returns vector of intersections in format [[intersectPosASL, surfaceNormal, intersectObj, parentObject],...]
        */
        intersect_surfaces_list line_intersects_surfaces(const vector3 &begin_pos_asl_, const vector3 &end_pos_asl_);

        /**
        * Returns list of intersections with surfaces from begPosASL to endPosASL.
        * If there is ground intersection, it is also included. Works on units. Works underwater.
        * Doesn't return intersection with sea surface. Hardcoded max distance: 5000m.
        * Biki: https://community.bistudio.com/wiki/lineIntersectsSurfaces
        *
        * @param begin_pos_asl_: PositionASL - virtual line start
        * @param end_pos_asl_: PositionASL - virtual line end
        * @param ignore_obj1_ (Optional) first object to ignore or objNull: Default: objNull
        *
        * @returns vector of intersections in format [[intersectPosASL, surfaceNormal, intersectObj, parentObject],...]
        */
        intersect_surfaces_list line_intersects_surfaces(const vector3 &begin_pos_asl_, const vector3 &end_pos_asl_, const object &ignore_obj1_);

        /**
        * Returns list of intersections with surfaces from begPosASL to endPosASL.
        * If there is ground intersection, it is also included. Works on units. Works underwater.
        * Doesn't return intersection with sea surface. Hardcoded max distance: 5000m.
        * Biki: https://community.bistudio.com/wiki/lineIntersectsSurfaces
        *
        * @param begin_pos_asl_: PositionASL - virtual line start
        * @param end_pos_asl_: PositionASL - virtual line end
        * @param ignore_obj1_ (Optional) first object to ignore or objNull: Default: objNull
        * @param ignore_obj2_ (Optional) second object to ignore or objNull: Default: objNull
        * @param sort_mode_ (Optional): true: closest to furthest, false: furthest to closest. Default: true
        * @param max_results_ (Optional) Max results to return. -1 to return every result. Default: 1
        * @param lod1_ (Optional) Primary LOD to look for intersection. Default: "VIEW"
        * @param lod2_ (Optional) Secondary LOD to look for intersection. Default: "FIRE"
        *
        * @returns vector of intersections in format [[intersectPosASL, surfaceNormal, intersectObj, parentObject],...]
        */
        intersect_surfaces_list line_intersects_surfaces(const vector3 &begin_pos_asl_, const vector3 &end_pos_asl_, const object &ignore_obj1_, const object &ignore_obj2_, bool sort_mode_ = true, int max_results_ = 1, sqf_string_const_ref lod1_ = "VIEW", sqf_string_const_ref lod2_ = "FIRE", bool unique_objs_ = true);

        /**
        * Returns objects intersecting with the virtual line from begPos to endPos
        */
        std::vector<object> line_intersects_with(const vector3 &begin_pos_, const vector3 &end_pos_, bool sort_by_distance_ = false);
        std::vector<object> line_intersects_with(const vector3 &begin_pos_, const vector3 &end_pos_, std::initializer_list<object> ignored_objects_, bool sort_by_distance_ = false);

        /**
        * Checks for intersection of terrain between two positions. Returns true if intersects with terrain. Uses PositionAGL
        */
        bool terrain_intersect(const vector3 &begin_pos_, const vector3 &end_pos_);

        /**
        * Checks for intersection of terrain between two positions. Returns true if intersects with terrain. Uses PositionASL
        */
        bool terrain_intersect_asl(const vector3 &begin_pos_, const vector3 &end_pos_);

        /**
        * Checks for object intersection with a virtual line between two positions. Returns true if intersects with an object.
        */
        bool line_intersects(const vector3 &begin_position_, const vector3 &end_position_);

        /**
        * Checks for object intersection with a virtual line between two positions. Returns true if intersects with an object.
        */
        bool line_intersects(const vector3 &begin_position_, const vector3 &end_position_, const object &ignore_obj_one_);

        /**
        * Checks for object intersection with a virtual line between two positions. Returns true if intersects with an object.
        */
        bool line_intersects(const vector3 &begin_position_, const vector3 &end_position_, const object &ignore_obj_one_, const object &ignore_obj_two_);

        /**
        * Find list of objects intersected by given line from begin_position_ to end_position_
        */
        std::vector<object> line_intersects_objs(const vector3 &begin_position_, const vector3 &end_position_, const object &with_object_, std::initializer_list<object> ignored_objects_, bool sort_by_distance_, int flags_);

        vector3 terrain_intersect_at_asl(const vector3 &pos1_, const vector3 &pos2_);

        float check_visibility(const object& ignore_, sqf_string_const_ref lodname_, const vector3 &begin_pos_, const vector3 &end_pos_);

        float check_visibility(const object& ignore_, sqf_string_const_ref lodname_, const object& ignore2_, const vector3 &begin_pos_, const vector3 &end_pos_);
    }  // namespace sqf
}  // namespace intercept
