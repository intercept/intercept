#pragma once
#include "shared.hpp"
#include "types.hpp"
#include "vector.hpp"
#include "client\client.hpp"
#include <vector>
#include <memory>
using namespace intercept::types;
namespace intercept {
    namespace client {
        namespace types {

            class game_value_shared_wrapper {
            public:
                game_value_shared_wrapper(game_value value_) : value(value_) {};
                ~game_value_shared_wrapper() {
                    host::functions.free_value(&value);
                }
                game_value value;
            };

            class internal {
            public:
                internal() { };
                internal(game_value value_) : _value(std::make_shared<game_value_shared_wrapper>(value_)) {}
                internal(const internal &copy_) : _value(copy_._value) {};
                operator game_value() { return _value->value; }
                operator game_value() const { return _value->value; }

                operator game_value &() { return _value->value; }

            protected:
                std::shared_ptr<game_value_shared_wrapper> _value;
            };

            class object : public internal {
            public:
                object() {};
                object(game_value value_) : internal(value_) {};
                object(const object &copy_) : internal(copy_) {};
            };
            class group : public internal {
            public:
                group() {};
                group(game_value value_) : internal(value_) {};
                group(const group &copy_) : internal(copy_) {};
            };
            class code : public internal {
            public:
                code() {};
                code(game_value value_) : internal(value_) {};
                code(const code &copy_) : internal(copy_) {};
            };
            class config : public internal {
            public:
                config() {};
                config(game_value value_) : internal(value_) {};
                config(const config &copy_) : internal(copy_) {};
            };
            class control : public internal {
            public:
                control() {};
                control(game_value value_) : internal(value_) {};
                control(const control &copy_) : internal(copy_) {};
            };
            class display : public internal {
            public:
                display() {};
                display(game_value value_) : internal(value_) {};
                display(const display &copy_) : internal(copy_) {};
            };
            class location : public internal {
            public:
                location() {};
                location(game_value value_) : internal(value_) {};
                location(const location &copy_) : internal(copy_) {};
            };
            class script : public internal {
            public:
                script() {};
                script(game_value value_) : internal(value_) {};
                script(const script &copy_) : internal(copy_) {};
            };
            class side : public internal {
            public:
                side() {};
                side(game_value value_) : internal(value_) {};
                side(const side &copy_) : internal(copy_) {};
            };
            class text : public internal {
            public:
                text() {};
                text(game_value value_) : internal(value_) {};
                text(const text &copy_) : internal(copy_) {};
            };
            class team_member : public internal {
            public:
                team_member() {};
                team_member(game_value value_) : internal(value_) {};
                team_member(const team_member &copy_) : internal(copy_) {};
            };
            class rv_namespace : public internal {
            public:
                rv_namespace() {};
                rv_namespace(game_value value_) : internal(value_) {};
                rv_namespace(const rv_namespace &copy_) : internal(copy_) {};
            };
            class task : public internal {
            public:
                task() {};
                task(game_value value_) : internal(value_) {};
                task(const task &copy_) : internal(copy_) {};
            };

            typedef std::string marker;
        }
    }
}