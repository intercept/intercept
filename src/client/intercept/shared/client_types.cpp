#include "client_types.hpp"
#include "client\client.hpp"
#include "shared\functions.hpp"

namespace intercept {
    namespace types {
        game_value_shared_wrapper::game_value_shared_wrapper(game_value value_) : value(value_) {}
        game_value_shared_wrapper::~game_value_shared_wrapper() {
            client::host::functions.free_value(&value);
        }

        internal_object::internal_object()
        {
        }

        internal_object::internal_object(game_value value_) : value(std::make_shared<game_value_shared_wrapper>(value_)) {}
        internal_object::internal_object(const internal_object &copy_) : value(copy_.value) {}
        internal_object::operator game_value() { return value->value; }
        internal_object::operator game_value() const { return value->value; }
        internal_object::operator game_value&() { return value->value; }



        object::object() {}
        object::object(game_value value_) : internal_object(value_) {}
        object::object(const object & copy_) : internal_object(copy_) {}

        group::group() {}
        group::group(game_value value_) : internal_object(value_) {}
        group::group(const group & copy_) : internal_object(copy_) {}

        code::code() {}
        code::code(game_value value_) : internal_object(value_) {}
        code::code(const code & copy_) : internal_object(copy_) {}

        config::config() {}
        config::config(game_value value_) : internal_object(value_) {}
        config::config(const config & copy_) : internal_object(copy_) {}

        control::control() {}
        control::control(game_value value_) : internal_object(value_) {}
        control::control(const control & copy_) : internal_object(copy_) {}

        display::display() {}
        display::display(game_value value_) : internal_object(value_) {}
        display::display(const display & copy_) : internal_object(copy_) {}

        location::location() {}
        location::location(game_value value_) : internal_object(value_) {}
        location::location(const location & copy_) : internal_object(copy_) {}

        script::script() {}
        script::script(game_value value_) : internal_object(value_) {}
        script::script(const script & copy_) : internal_object(copy_) {}

        side::side() {}
        side::side(game_value value_) : internal_object(value_) {}
        side::side(const side & copy_) : internal_object(copy_) {}

        text::text() {}
        text::text(game_value value_) : internal_object(value_) {}
        text::text(const text & copy_) : internal_object(copy_) {}

        team_member::team_member() {}
        team_member::team_member(game_value value_) : internal_object(value_) {}
        team_member::team_member(const team_member & copy_) : internal_object(copy_) {}

        rv_namespace::rv_namespace() {}
        rv_namespace::rv_namespace(game_value value_) : internal_object(value_) {}
        rv_namespace::rv_namespace(const rv_namespace & copy_) : internal_object(copy_) {}

        task::task() {}
        task::task(game_value value_) : internal_object(value_) {}
        task::task(const task & copy_) : internal_object(copy_) {}
    }
}