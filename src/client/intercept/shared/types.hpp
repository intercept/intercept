#pragma once
#include <stdio.h>
#include <set>
#include "vector.hpp"

namespace intercept {
    namespace types {
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

        class game_data {
        public:
            uintptr_t type;
            uint32_t ref_count_internal;
            uintptr_t data_type;
        };

        class game_data_number : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_number();
            game_data_number(float val_);
            game_data_number(const game_data_number &copy_);
            game_data_number(game_data_number &&move_);
            game_data_number & game_data_number::operator = (const game_data_number &copy_);
            game_data_number & game_data_number::operator = (game_data_number &&move_);
            float number;
        };

        class game_data_bool : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_bool();
            game_data_bool(bool val_);
            game_data_bool(const game_data_bool &copy_);
            game_data_bool(game_data_bool &&move_);
            game_data_bool & game_data_bool::operator = (const game_data_bool &copy_);
            game_data_bool & game_data_bool::operator = (game_data_bool &&move_);
            bool val;
        };

        class rv_game_value {
        public:
            static uintptr_t __vptr_def;
            rv_game_value() : __vptr(rv_game_value::__vptr_def), data(nullptr) {};
            uintptr_t __vptr;
            game_data *data;
        };

        class game_data_array;

        class game_value {
        public:
            game_value();
            void copy(const game_value & copy_);
            game_value(const game_value &copy_);
            game_value(game_value &&move_);

            game_value(uintptr_t internal_);
            game_value(float val_);
            game_value(bool val_);
            game_value(std::string &val_);
            game_value(const char *);
            game_value(std::initializer_list<game_value> list_);
            game_value(client::types::vector3 &vec_);
            game_value(client::types::vector2 &vec_);
            game_value & operator = (const game_value &copy_);
            game_value & operator = (game_value &&move_);

            game_value & operator = (float val_);
            game_value & operator = (bool val_);
            game_value & operator = (std::string val_);
            game_value & operator = (const char *val_);
            game_value & operator = (std::initializer_list<game_value> list_);
            game_value & operator = (client::types::vector3 vec_);
            game_value & operator = (client::types::vector2 vec_);



            operator float();
            operator bool();
            operator std::string();
            operator float() const;
            operator bool() const;
            operator std::string() const;

            game_value & operator [](int i_);
            game_value operator [](int i_) const;

            uintptr_t type() {
                return _rv_data.data->type;
            }

            bool client_owned() {
                if (_rv_data.data->ref_count_internal == 0x0000dede)
                    return true;
                return false;
            }


            ~game_value();
        protected:
            rv_game_value _rv_data;
        };

        class game_data_array : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_array();;
            game_data_array(size_t size_);;
            game_data_array(std::initializer_list<game_value> init_);;
            game_data_array(const game_data_array &copy_);
            game_data_array(game_data_array &&move_);
            game_data_array & game_data_array::operator = (const game_data_array &copy_);
            game_data_array & game_data_array::operator = (game_data_array &&move_);
            ~game_data_array();
            game_value *data;
            uint32_t length;
            uint32_t max_size;
        };

        class game_data_string : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_string();
            game_data_string(std::string str_);
            game_data_string(const game_data_string &copy_);
            game_data_string(game_data_string &&move_);
            game_data_string & game_data_string::operator = (const game_data_string &copy_);
            game_data_string & game_data_string::operator = (game_data_string &&move_);
            ~game_data_string();
            rv_string *raw_string;
        };

        rv_string *allocate_string(size_t size_);
        void free_string(rv_string *str_);
    }
}