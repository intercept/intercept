#include "client_types.hpp"
#include "client\client.hpp"
#include "shared\functions.hpp"

namespace intercept {
    namespace types {

        internal_object::internal_object() {}
        internal_object::internal_object(const rv_game_value &value_) : game_value(value_) {}
        internal_object::internal_object(const internal_object &copy_) : game_value(copy_) {}
        internal_object::internal_object(internal_object && move_) : game_value(move_) {};

        internal_object & internal_object::operator=(const internal_object & copy_)
        {
            game_value::operator=(copy_);
            return *this;
        }

        internal_object & internal_object::operator=(internal_object && move_)
        {
            game_value::operator=(move_);
            return *this;
        }

        internal_object::operator game_value*()
        {
            return (game_value *)this;
        }

        internal_object::operator game_value*() const
        {
            return (game_value *)this;
        }


#define RV_GENERIC_OBJECT_DEF(type)         type##::##type##() {}\
        type##::##type##(rv_game_value value_) : internal_object(value_) {}\
        type##::##type##(const type & copy_) : internal_object(copy_) {}\
        type##::##type##(type && move_) : internal_object(move_) {}\
        type & type##::operator=(const type & copy_)\
        {\
            game_value::operator=(copy_);\
            return *this;\
        }\
        type & type##::operator=(type && move_)\
        {\
            game_value::operator=(move_);\
            return *this;\
        }

        RV_GENERIC_OBJECT_DEF(object)

        RV_GENERIC_OBJECT_DEF(group)

        RV_GENERIC_OBJECT_DEF(code)

        RV_GENERIC_OBJECT_DEF(config)

        RV_GENERIC_OBJECT_DEF(control)

        RV_GENERIC_OBJECT_DEF(display)

        RV_GENERIC_OBJECT_DEF(location)

        RV_GENERIC_OBJECT_DEF(script)

        RV_GENERIC_OBJECT_DEF(side)

        RV_GENERIC_OBJECT_DEF(text)

        RV_GENERIC_OBJECT_DEF(team_member)

        RV_GENERIC_OBJECT_DEF(rv_namespace)

        RV_GENERIC_OBJECT_DEF(task)
    }
}