#pragma once
#include "..\shared.hpp"
#include "types.hpp"

using namespace intercept::types;

namespace intercept {
    extern "C" {
        struct client_functions {
            rv_game_value(*invoke_raw_nular)(nular_function function_);
            rv_game_value(*invoke_raw_unary)(unary_function function_, const game_value &right_arg_);
            rv_game_value(*invoke_raw_binary)(binary_function function_, const game_value &left_arg_, const game_value &right_arg_);

            

            void(*get_type_structure)(char *type_name, uintptr_t &type_def_, uintptr_t &data_type_def_);

            game_value(*new_scalar)(float val_);
            game_value(*new_string)(const char *string_);
            game_value(*new_array)(size_t size_);
            rv_string *(*allocate_string)(size_t size_);
            void(*free_string)(rv_string *str_);

            void(*free_value)(game_value * value_);

            nular_function(*get_nular_function)(const char * function_name_);

            unary_function(*get_unary_function)(const char * function_name_);
            unary_function(*get_unary_function_typed)(const char * function_name_, const char * right_arg_type_);

            binary_function(*get_binary_function)(const char * function_name_);
            binary_function(*get_binary_function_typed)(const char * function_name_, const char * left_arg_type_, const char * right_arg_type_);
        };
    }
}