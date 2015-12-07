#pragma once
#include "shared.hpp"
#include "shared\types.hpp"
#include "vector.hpp"
#include "client\client.hpp"
#include <vector>
#include <memory>
using namespace intercept::rv_types;
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
                internal(game_value value_) {
                    _value = std::make_shared<game_value_shared_wrapper>(value_);
                }
                internal(const internal &copy_) : _value(copy_._value) {};
                operator game_value() { return _value->value; }
                operator game_value() const { return _value->value; }

                operator game_value *() { return &(_value->value); }

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

            class game_value_helper {
            public:
                game_value value;
                operator game_value() { return value; }
                operator game_value *() { return &value; }

            };

            class game_value_number : public game_value_helper {
            public:
                game_value_number() {
                    _number.number = 0.0f;
                    value.data = &_number;
                };
                game_value_number(float value_) {
                    _number.number = value_;
                    value.data = &_number;
                }
            protected:
                game_data_number _number;
            };

            class game_value_bool : public game_value_helper {
            public:
                game_value_bool(bool val_) {
                    _val.value = val_;
                    value.data = &_val;
                }
            protected:
                game_data_bool _val;
            };

            class game_value_vector3 : public game_value_helper {
            public:
                game_value_vector3(client::types::vector3 vec_) {
                    ((game_data_number *)_vals[0].value.data)->number = vec_.x;
                    ((game_data_number *)_vals[1].value.data)->number = vec_.y;
                    ((game_data_number *)_vals[2].value.data)->number = vec_.z;
                    _elements[0] = _vals[0];
                    _elements[1] = _vals[1];
                    _elements[2] = _vals[2];
                    _array.data = &_elements[0];
                    _array.length = 3;
                    _array.max_size = 3;
                    value.data = &_array;
                }
            protected:
                game_data_array_stack _array;
                game_value_number _vals[3];
                game_value _elements[3];
            };

            class game_value_vector2 : public game_value_helper {
            public:
                game_value_vector2(client::types::vector2 vec_) {
                    ((game_data_number *)_vals[0].value.data)->number = vec_.x;
                    ((game_data_number *)_vals[1].value.data)->number = vec_.y;
                    _elements[0] = _vals[0];
                    _elements[1] = _vals[1];
                    _array.data = &_elements[0];
                    _array.length = 3;
                    _array.max_size = 3;
                    value.data = &_array;
                }
            protected:
                game_data_array_stack _array;
                game_value_number _vals[2];
                game_value _elements[2];
            };

            template<size_t SIZE>
            class game_value_array : public game_value_helper {
            public:
                game_value_array() {
                    _array.data = _elements;
                    value.data = &_array;
                    _array.length = SIZE;
                    _array.max_size = SIZE;
                }

                game_value_array(std::initializer_list<game_value> values_) {
                    _array.data = _elements;
                    value.data = &_array;
                    _array.length = SIZE;
                    _array.max_size = SIZE;
                    uint32_t i = 0;
                    for (auto val : values_) {
                        _elements[i++] = val;
                    }
                }
                game_value & operator [](int i_) { return _elements[i_]; }
                game_value operator [](int i_) const { return _elements[i_]; }

            protected:
                game_data_array_stack _array;
                game_value _elements[SIZE];
            };

            template<typename T, typename Allocator>
            class game_value_array_dynamic : public game_value_helper {
            public:
                game_value_array_dynamic(std::vector<T> init_) {
                    _array.allocate(init_.size());
                    uint32_t i = 0;
                    for (auto el : init_) {
                        _array.data[i] = Allocator(el);
                    }
                    _array.length = init_.size();
                    _array.max_size = init_.size();
                    value.data = &_array;
                }
            protected:
                game_data_array _array;
            };

            class game_value_string : public game_value_helper {
            public:
                game_value_string(std::string str_) {
                    value = host::functions.new_string(str_.c_str());
                }
                ~game_value_string() {
                    host::functions.free_value(&value);
                }
            };

        }
    }
}