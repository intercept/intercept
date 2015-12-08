#pragma once
#include "shared.hpp"
#include "shared\types.hpp"
#include "vector.hpp"
#include "client\client.hpp"
#include <vector>
#include <memory>

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


            class game_value {
            public:
                rv_game_value data;
            };

            class game_value_number : public game_value {
            public:
                game_value_number() {
                    data.data = &_data;
                };
                game_value_number(float val_) {
                    data.data = &_data;
                    _data.number = val_;
                };

                game_data_number _data;
            };

            class game_value_bool : public game_value {
            public:
                game_value_bool() {
                    data.data = &_data;
                };
                game_value_bool(float val_) {
                    data.data = &_data;
                    _data.value = val_;
                };

                game_data_bool _data;
            };

            class game_value_vec3 : public game_value {
            public:
                game_value_vec3() {
                    data.data = &_data;
                };

                game_value_vec3(vector3 vec_) {
                    data.data = &_data;
                    _data.length = 3;
                    _data.max_size = 3;
                    _elements[0]._data.number = vec_.x;
                    _elements[1]._data.number = vec_.y;
                    _elements[2]._data.number = vec_.z;

                    _data.data[0] = _elements[0].data;
                    _data.data[1] = _elements[1].data;
                    _data.data[2] = _elements[2].data;

                };

                game_data_array_stack _data;
                game_value_number _elements[3];
            };

            class game_value_vec2 : public game_value {
            public:
                game_value_vec2() {
                    data.data = &_data;
                };

                game_value_vec2(vector2 vec_) {
                    data.data = &_data;
                    _data.length = 3;
                    _data.max_size = 3;
                    _elements[0]._data.number = vec_.x;
                    _elements[1]._data.number = vec_.y;

                    _data.data[0] = _elements[0].data;
                    _data.data[1] = _elements[1].data;

                };


                game_data_array_stack _data;
                game_value_number _elements[2];
            };



            class game_value_string_stack : public game_value {
            public:
                game_value_string_stack() {
                    data.data = &_data;
                }

                game_value_string_stack(std::string str_) {
                    data.data = &_data;
                    _data.raw_string = (rv_string *)&rv_string_raw;
                    _data.raw_string->length = str_.length() + 1;
                    _data.raw_string->ref_count_internal = 1;
                    strcpy(&_data.raw_string->char_string, str_.c_str());
                }

                char rv_string_raw[2048 + 8];
                game_data_string _data;
            };

            template<size_t SIZE>
            class game_value_array : public game_value {
            public:
                game_value_array() {
                    data.data = &_array;
                    _array.data = _elements;
                    _array.length = SIZE;
                    _array.max_size = SIZE;
                }

                game_value_array(std::initializer_list<game_value> values_) {
                    data.data = &_array;
                    _array.data = _elements;
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

            class game_value_array_dynamic : public game_value {
            public:
                game_value_array_dynamic(std::vector<game_value> init_) {
                    _array.data = &_elements[0].data;//new game_value[init_.size()];
                    data.data = &_array;
                    uint32_t i = 0;
                    for (auto el : init_) {
                        _array.data[i++] = el.data;
                    }
                    _array.length = init_.size();
                    _array.max_size = init_.size();
                }
            protected:
                game_data_array _array;
                game_value _elements[2048];
            };


        }
    }
}