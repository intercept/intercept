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
            //internal_object(const rv_game_value &value_);  //deprecated
            internal_object(const game_value &value_);
            internal_object(const internal_object &copy_);
            internal_object(internal_object &&move_);
            internal_object & operator = (internal_object &&move_);

            internal_object & operator = (const internal_object &copy_);

            bool operator<(const internal_object& compare_) const;
            bool operator>(const internal_object& compare_) const;

            bool is_null();

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

        template<typename T>
        class rv_list {
        public:
            rv_list() : _length(0), _data(nullptr) {};
            rv_list(size_t _init_length) : _length(_init_length) {
                _data = new T[_init_length];
            }

            rv_list(const rv_list<T> &copy_) {
                _data = new T[copy_.length];
                memcpy(_data, copy_._data, sizeof(T)*copy_._length);
                _length = copy_._length;
            }

            rv_list(rv_list<T> &&move_) {
                if (this == &move_)
                    return;
                _length = move_._length;
                _data = move_._data;
                move_._data = nullptr;
                move_._length = 0;
            }

            ~rv_list() {
                if (_data)
                    delete[] _data;
            }

            rv_list<T> & operator= (const rv_list<T> &copy_) {
                _data = new T[copy_.length];
                memcpy(_data, copy_._data, sizeof(T)*copy_._length);
                _length = copy_._length;
                return *this;
            }

            rv_list<T> & operator= (rv_list<T> &&move_) {
                if (this == &move_)
                    return;
                _length = move_._length;
                _data = move_._data;
                move_._data = nullptr;
                move_._length = 0;
                return *this;
            }

            T & operator [](int i_) {
                return _data[i_];
            }

            T operator [](int i_) const {
                return _data[i_];
            }

            size_t length() { return _length; }
        protected:
            T *_data;
            size_t _length;
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
            rv_string ammo_type;
            hit_part_ammo ammo_data;
            hit_part_impulse impulse_data;
            vector3 direction;
            float radius;
            rv_string surface;
            bool direct;
        };
    }
}
