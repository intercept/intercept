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
            class internal_ptr {
            public:
                internal_ptr();
                internal_ptr(game_value value_);
                ~internal_ptr();
                game_value value;
                operator game_value() { return value; }
                operator game_value *() { return &value; }
            };

            class object_ptr : public internal_ptr {
            public:
                object_ptr(game_value value_) : internal_ptr(value_) {};
                ~object_ptr();
            };
            class group_ptr : public internal_ptr {
            public:
                group_ptr(game_value value_) : internal_ptr(value_) {};
                ~group_ptr();
            };
            class code_ptr : public internal_ptr {
            public:
                code_ptr(game_value value_) : internal_ptr(value_) {};
                ~code_ptr();
            };
            class config_ptr : public internal_ptr {
            public:
                config_ptr(game_value value_) : internal_ptr(value_) {};
                ~config_ptr();

                config operator>>(std::string& value_);
                config operator>>(const char* value_);
            };
            class control_ptr : public internal_ptr {
            public:
                control_ptr(game_value value_) : internal_ptr(value_) {};
                ~control_ptr();
            };
            class display_ptr : public internal_ptr {
            public:
                display_ptr(game_value value_) : internal_ptr(value_) {};
                ~display_ptr();
            };
            class location_ptr : public internal_ptr {
            public:
                location_ptr(game_value value_) : internal_ptr(value_) {};
                ~location_ptr();
            };
            class script_ptr : public internal_ptr {
            public:
                script_ptr(game_value value_) : internal_ptr(value_) {};
                ~script_ptr();
            };
            class side_ptr : public internal_ptr {
            public:
                side_ptr(game_value value_) : internal_ptr(value_) {};
                ~side_ptr();
            };
            class text_ptr : public internal_ptr {
            public:
                text_ptr(game_value value_) : internal_ptr(value_) {};
                ~text_ptr();
            };
            class team_member_ptr : public internal_ptr {
            public:
                team_member_ptr(game_value value_) : internal_ptr(value_) {};
                ~team_member_ptr();
            };
            class rv_namespace_ptr : public internal_ptr {
            public:
                rv_namespace_ptr(game_value value_) : internal_ptr(value_) {};
                ~rv_namespace_ptr();
            };
            class task_ptr : public internal_ptr {
            public:
                task_ptr(game_value value_) : internal_ptr(value_) {};
                ~task_ptr();
            };
            
            typedef std::shared_ptr<object_ptr> object;
            typedef std::shared_ptr<group_ptr> group;
            typedef std::shared_ptr<code_ptr> code;
            typedef std::shared_ptr<config_ptr> config;
            typedef std::shared_ptr<control_ptr> control;
            typedef std::shared_ptr<display_ptr> display;
            typedef std::shared_ptr<location_ptr> location;
            typedef std::shared_ptr<script_ptr> script;
            typedef std::shared_ptr<side_ptr> side;
            typedef std::shared_ptr<text_ptr> text;
            typedef std::shared_ptr<team_member_ptr> team_member;
            typedef std::shared_ptr<rv_namespace_ptr> rv_namespace;
            typedef std::shared_ptr<task_ptr> task;

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