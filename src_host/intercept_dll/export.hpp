#pragma once

#define DLLEXPORT __declspec(dllimport)

extern "C" { 
    DLLEXPORT void * intercept_invoke_raw_nular(void *function_);
    DLLEXPORT void * intercept_invoke_raw_unary(void *function_, void *right_arg_);
    DLLEXPORT void * intercept_invoke_raw_binary(void *function_, void *left_arg_, void *right_arg_);

    DLLEXPORT void * intercept_free_value(void *value);

    DLLEXPORT uintptr_t intercept_get_nular_function(char *function_name_);

    DLLEXPORT uintptr_t intercept_get_unary_function(char *function_name_);
    DLLEXPORT uintptr_t intercept_get_unary_function_typed(char *function_name_, char *right_arg_type_);

    DLLEXPORT uintptr_t intercept_get_binary_function(char *function_name_);
    DLLEXPORT uintptr_t intercept_get_binary_function_typed(char *function_name_, char *left_arg_type_, char *right_arg_type_);
}