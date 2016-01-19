#pragma once
#include "shared.hpp"
#include "types.hpp"
#include <vector>
#include <memory>
namespace intercept {
    namespace types {

        class internal_object : public game_value {
        public:
            internal_object();
            internal_object(const rv_game_value &value_);
            internal_object(const game_value &value_);
            internal_object(const internal_object &copy_);
            internal_object(internal_object &&move_);
            internal_object & operator = (internal_object &&move_);
            operator game_value *();
            operator game_value *() const;

            internal_object & operator = (const internal_object &copy_);

            bool operator<(const internal_object& compare_) const;
            bool operator>(const internal_object& compare_) const;

            bool is_null();

        };

#define RV_GENERIC_OBJECT_DEC(type) class type : public internal_object {\
            public:\
                type##();\
                type##(const rv_game_value &value_);\
                type##(const game_value &value_);\
                type##(const type &copy_);\
                type##(type &&move_);\
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

        class rv_list {
        public:

        protected:
        };

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
            std::string ammo_type;
            hit_part_ammo ammo_data;
            hit_part_impulse impulse_data;
            vector3 direction;
            float radius;
            std::string surface;
            bool direct;
        };
    }
}
