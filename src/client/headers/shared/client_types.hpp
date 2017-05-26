#pragma once
#include "shared.hpp"
#include "types.hpp"

namespace intercept {
    namespace types {

        class internal_object : public game_value {
        public:
            internal_object();
            //internal_object(const rv_game_value &value_);  //deprecated
            internal_object(const game_value &value_);
            internal_object(const internal_object &copy_);
            internal_object(internal_object &&move_) noexcept;
            internal_object & operator = (internal_object &&move_) noexcept;

            internal_object & operator = (const internal_object &copy_);

            bool operator<(const internal_object& compare_) const;
            bool operator>(const internal_object& compare_) const;

            bool is_null() const;

        };

            //type(const rv_game_value &value_);\ deprecated
#define RV_GENERIC_OBJECT_DEC(type) class type : public internal_object {\
            public:\
                type();\
                type(const game_value &value_);\
                type(const type &copy_);\
                type(const internal_object &copy_) = delete;/*prevents code(object()) You can't convert object to code!*/\
                type(type &&move_);\
                type & operator = (type &&move_);\
                type & operator = (const type &copy_);\
            }

        RV_GENERIC_OBJECT_DEC(object);
        RV_GENERIC_OBJECT_DEC(group);
        RV_GENERIC_OBJECT_DEC(code);
        RV_GENERIC_OBJECT_DEC(config);
        RV_GENERIC_OBJECT_DEC(control);
        RV_GENERIC_OBJECT_DEC(display);
        RV_GENERIC_OBJECT_DEC(location);
        RV_GENERIC_OBJECT_DEC(script);
        RV_GENERIC_OBJECT_DEC(side);
        RV_GENERIC_OBJECT_DEC(rv_text);
        RV_GENERIC_OBJECT_DEC(team_member);
        RV_GENERIC_OBJECT_DEC(rv_namespace);
        RV_GENERIC_OBJECT_DEC(task);

        typedef std::string marker;

        struct hit_part_ammo {
            float hit;
            float indirect_hit;
            float indirect_hit_range;
            float explosive;
        };

        struct hit_part_impulse {

        };

        struct hit_part_data {
            object target;
            object shooter;
            object bullet;
            vector3 position;
            vector3 velocity;
            std::vector<std::string> selections;
            r_string ammo_type;
            hit_part_ammo ammo_data;
            hit_part_impulse impulse_data;
            vector3 direction;
            float radius;
            r_string surface;
            bool direct;
        };

        struct rv_color {
            float red{ 0.f };
            float green{ 0.f };
            float blue{ 0.f };
            float alpha{ 0.f };

            operator game_value() const {
                return game_value({
                    red,
                    green,
                    blue,
                    alpha
                });
            }

            rv_color(const game_value &ret_game_value_) :
                red(ret_game_value_[0]),
                green(ret_game_value_[1]),
                blue(ret_game_value_[2]),
                alpha(ret_game_value_[3]) {}

            rv_color(float red_, float green_, float blue_, float alpha_) :
                red(red_),
                green(green_),
                blue(blue_),
                alpha(alpha_) {}
        };

        typedef std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3> > t_sqf_in_area_position;

        struct rv_waypoint {
            group group;
            int index;
            //#TODO add to game_value conversion
        };
    }
}
