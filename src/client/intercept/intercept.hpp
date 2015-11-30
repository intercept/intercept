#pragma once
#include <stdio.h>
#include "client\client.hpp"

#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

DLLIMPORT void * intercept_invoke_raw_nular(const void *function_);
DLLIMPORT void * intercept_invoke_raw_unary(const void *function_, void *right_arg_);
DLLIMPORT void * intercept_invoke_raw_binary(const void *function_, void *left_arg_, void *right_arg_);

DLLIMPORT void * intercept_free_value(void *value);

DLLIMPORT uintptr_t intercept_get_nular_function(const char *function_name_);

DLLIMPORT uintptr_t intercept_get_unary_function(const char *function_name_);
DLLEXPORT uintptr_t intercept_get_unary_function_typed(const char *function_name_, const char *right_arg_type_);

DLLIMPORT uintptr_t intercept_get_binary_function(const char *function_name_);
DLLIMPORT uintptr_t intercept_get_binary_function_typed(const char *function_name_, const char *left_arg_type_, const char *right_arg_type_);

extern "C" {
    DLLEXPORT void intercept_pre_init();
    DLLEXPORT void intercept_post_init();
    DLLEXPORT void intercept_mission_end();
    DLLEXPORT void intercept_on_frame();
}