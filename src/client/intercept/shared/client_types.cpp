#include "client_types.hpp"
#include "client\client.hpp"
#include "shared\functions.hpp"

namespace intercept {
    namespace types {
        game_value_shared_wrapper::game_value_shared_wrapper(rv_game_value value_) : value(value_) {}
        game_value_shared_wrapper::~game_value_shared_wrapper() {
            client::host::functions.free_value(&value);
        }
        internal_object::internal_object() {}

        internal_object::internal_object(rv_game_value value_) : value(std::make_shared<game_value_shared_wrapper>(value_)) {}
        internal_object::internal_object(const internal_object &copy_) : value(copy_.value) {}
        internal_object::operator game_value() { return value->value; }
        internal_object::operator game_value() const { return value->value; }
        internal_object::operator game_value *() { return &value->value; }
        internal_object::operator game_value *() const { return &value->value; }

        internal_object::operator game_value&() const
        {
            return value->value;
        }


#define RV_GENERIC_OBJECT_DEF(type)         type##::##type##() {}\
        type##::##type##(rv_game_value value_) : internal_object(value_) {}\
        type##::##type##(const type & copy_) : internal_object(copy_) {}


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