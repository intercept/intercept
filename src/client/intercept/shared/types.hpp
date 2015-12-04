#pragma once
#include <stdio.h>
#include <set>
#include "client\vector.hpp"

namespace intercept {
    namespace rv_types {
        typedef uintptr_t(__cdecl *nular_function)(char *, uintptr_t);
        typedef uintptr_t(__cdecl *unary_function)(char *, uintptr_t, uintptr_t);
        typedef uintptr_t(__cdecl *binary_function)(char *, uintptr_t, uintptr_t, uintptr_t);

        typedef std::set<std::string> value_type;

        class rv_string {
        public:
            uint32_t ref_count_internal;
            uint32_t length;
            char char_string;
            std::string string();
        };

        struct value_entry {
            rv_string *type_name;
        };

        struct compound_value_pair {
            value_entry *first;
            value_entry *second;
        };

        struct compound_value_entry {
            uintptr_t           v_table;
            compound_value_pair *types;
        };

        class op_value_entry {
        public:
            uintptr_t               v_table;
            value_entry             *single_type;
            compound_value_entry    *compound_type;
            value_type type();
            std::string type_str();
        };

        struct unary_operator {
            uintptr_t        v_table;
            uint32_t         ref_count;
            unary_function   *procedure_addr;
            op_value_entry   return_type;
            op_value_entry   arg_type;
        };

        struct unary_entry {
            char *name;
            unary_operator *op;
        };

        struct binary_operator {
            uintptr_t        v_table;
            uint32_t         ref_count;
            unary_function   *procedure_addr;
            op_value_entry   return_type;
            op_value_entry   arg1_type;
            op_value_entry   arg2_type;
        };

        struct binary_entry {
            char *name;
            binary_operator *op;
        };

        struct nular_operator {
            uintptr_t        v_table;
            uint32_t         ref_count;
            nular_function   *procedure_addr;
            op_value_entry   return_type;
        };

        struct nular_entry {
            char *name;
            nular_operator *op;
        };

        class game_value;

        class game_data {
        public:
            uintptr_t type;
            uint32_t ref_count_internal;
            uintptr_t data_type;
        };

        class game_data_object : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_object() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *object;
        };

        class game_data_array : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_array() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            ~game_data_array() {
                free(data);
            }
            void allocate(size_t size_);
            game_value *data;
            uint32_t length;
            uint32_t max_size;
        };

        class game_data_array_stack : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_array_stack() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            ~game_data_array_stack() {
            }
            game_value *data;
            uint32_t length;
            uint32_t max_size;
        };

        class game_data_string : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_string() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            ~game_data_string() {
                free(raw_string);
            };
            rv_string *raw_string;
            std::string get_string();
            bool set_string(std::string val_);
            
        };

        class game_data_number : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_number() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            }
            float number;
        };

        class game_data_bool : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_bool() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            }
            bool value;
        };

        class game_value {
        public:
            static uintptr_t __vptr_def;
            game_value();
            uintptr_t __vptr;
            game_data *data;
        };

        class game_value_helper {
        public:
            game_value value;
            operator game_value() { return value; }
            operator game_value *() { return &value; }

        };

        class game_value_number : public game_value_helper {
        public:
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
                _elements[0] = game_value_number(vec_.x);
                _elements[1] = game_value_number(vec_.y);
                _elements[2] = game_value_number(vec_.z);
                _array.data = _elements;
                value.data = &_array;
            }
        protected:
            game_data_array_stack _array;
            game_value _elements[3];
        };

        class game_value_vector2 : public game_value_helper {
        public:
            game_value_vector2(client::types::vector2 vec_) {
                _elements[0] = game_value_number(vec_.x);
                _elements[1] = game_value_number(vec_.y);
                _array.data = _elements;
                value.data = &_array;
            }
        protected:
            game_data_array_stack _array;
            game_value _elements[2];
        };

        template<size_t SIZE>
        class game_value_array : public game_value_helper {
        public:
            game_value_array() {
                _array.data = _elements;
                value.data = &_array;
            }
            game_value & operator [](uint32_t i_) const { return _elements[i]; }
        protected:
            game_data_array_stack _array;
            game_value _elements[SIZE];
        };
    }
}