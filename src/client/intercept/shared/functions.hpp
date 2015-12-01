#pragma once
#include "..\shared.hpp"
#include "shared\types.hpp"

using namespace intercept::rv_types;

namespace intercept {
    extern "C" {
        struct client_functions {
            game_value (*invoke_raw_nular)(nular_function function_);
            game_value(*invoke_raw_unary)(unary_function function_, game_value * right_arg_);
            game_value(*invoke_raw_binary)(binary_function function_, game_value * left_arg_, game_value * right_arg_);

            game_value(*new_scalar)(float val_);
            game_value(*new_string)(char *string_);

            void(*free_value)(game_value * value_);

            nular_function(*get_nular_function)(const char * function_name_);

            unary_function(*get_unary_function)(const char * function_name_);
            unary_function(*get_unary_function_typed)(const char * function_name_, const char * right_arg_type_);

            binary_function(*get_binary_function)(const char * function_name_);
            binary_function(*get_binary_function_typed)(const char * function_name_, const char * left_arg_type_, const char * right_arg_type_);
        };
    }
}