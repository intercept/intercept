#include "export.hpp"
#include "types.hpp"

void * intercept_invoke_raw_nular(const void *function_) {
    return NULL;
}

void * intercept_invoke_raw_unary(const void *function_, void *right_arg_) {
    return NULL;
}

void * intercept_invoke_raw_binary(const void *function_, void *left_arg_, void *right_arg_) {
    return NULL;
}

void * intercept_free_value(void *value) {
    return NULL;
}

uintptr_t intercept_get_nular_function(const char *function_name_) {
    return NULL;
}

uintptr_t intercept_get_unary_function(const char *function_name_) {
    return NULL;
}

uintptr_t intercept_get_unary_function_typed(const char *function_name_, const char *right_arg_type_) {
    return NULL;
}

uintptr_t intercept_get_binary_function(const char *function_name_) {
    return NULL;
}

uintptr_t intercept_get_binary_function_typed(const char *function_name_, const char *left_arg_type_, const char *right_arg_type_) {
    return NULL;
}