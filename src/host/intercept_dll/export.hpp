#pragma once
#include "shared.hpp"

#define DLLEXPORT __declspec(dllexport)

extern "C" { 
    DLLEXPORT void * intercept_invoke_raw_nular(const void *function_);
    DLLEXPORT void * intercept_invoke_raw_unary(const void *function_, void *right_arg_);
    DLLEXPORT void * intercept_invoke_raw_binary(const void *function_, void *left_arg_, void *right_arg_);

    DLLEXPORT void * intercept_free_value(void *value);

    DLLEXPORT uintptr_t intercept_get_nular_function(const char *function_name_);

    DLLEXPORT uintptr_t intercept_get_unary_function(const char *function_name_);
    DLLEXPORT uintptr_t intercept_get_unary_function_typed(const char *function_name_, const char *right_arg_type_);

    DLLEXPORT uintptr_t intercept_get_binary_function(const char *function_name_);
    DLLEXPORT uintptr_t intercept_get_binary_function_typed(const char *function_name_, const char *left_arg_type_, const char *right_arg_type_);
}