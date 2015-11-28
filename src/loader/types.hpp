#pragma once
#include "shared.hpp"


namespace intercept {
    namespace rv_types {
        typedef uintptr_t(__cdecl *nular_function)(char *, uintptr_t);
        typedef uintptr_t(__cdecl *unary_function)(char *, uintptr_t, uintptr_t);
        typedef uintptr_t(__cdecl *binary_function)(char *, uintptr_t, uintptr_t, uintptr_t);

        struct unary_operator {
            uintptr_t        v_table;
            uint32_t         ref_count;
            unary_function  *procedure_addr;
            uintptr_t        return_type;
            uintptr_t        arg_type;
        };

        struct unary_entry {
            char *name;
            unary_operator *op;
        };

        struct binary_operator {
            uintptr_t        v_table;
            uint32_t         ref_count;
            unary_function  *procedure_addr;
            uintptr_t        return_type;
            uintptr_t        arg1_type;
            uintptr_t        arg2_type;
        };

        struct binary_entry {
            char *name;
            binary_operator *op;
        };

        struct nular_operator {
            uintptr_t        v_table;
            uint32_t         ref_count;
            nular_function  *procedure_addr;
            uintptr_t        return_type;
        };

        struct nular_entry {
            char *name;
            nular_operator *op;
        };

        struct rv_string {
            uint32_t ref_count_internal;
            uint32_t length;
            char char_string;
        };

        class game_value;

        class game_data {
        public:
            uintptr_t type;
            uint32_t ref_count_internal;
            uintptr_t data_type;
        };

        class game_data_array : public game_data {
        public:
            game_value *data;
            uint32_t length;
            uint32_t max_size;
        };

        class game_data_string : public game_data {
        public:
            rv_string *string;
            std::string get_string() {
                return std::string((char *)&string->char_string);
            }
        };

        class game_data_number : public game_data {
        public:
            float number;
        };

        class game_data_object : public game_data {
        public:
            void *object;
        };

        class game_data_bool : public game_data {
        public:
            bool val;
        };

        class game_value {
        public:
            game_value() : __vptr(NULL), data(NULL) {};
            uintptr_t __vptr;
            game_data *data;
        };
    }
}