#pragma once
#include <stdio.h>
#include <set>

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

        class game_data_group : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_group() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *group;
        };

        class game_data_config : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_config() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *config;
        };

        class game_data_control : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_control() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *control;
        };

        class game_data_display : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_display() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *display;
        };

        class game_data_location : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_location() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *location;
        };

        class game_data_script : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_script() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *script;
        };

        class game_data_side : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_side() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *side;
        };

        class game_data_text : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_text() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *text;
        };

        class game_data_team : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_team() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *team;
        };

        class game_data_namespace : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_namespace() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *rv_namespace;
        };

        class game_data_code : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_code() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
            };
            void *code;
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

        
    }
}