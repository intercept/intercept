#include "export.hpp"
#include "invoker.hpp"


namespace intercept {
    namespace client_function_defs {
        rv_game_value invoke_raw_nular(nular_function function_) {
            return intercept::invoker::get().invoke_raw(function_);
        }

        rv_game_value invoke_raw_unary(unary_function function_, const game_value &right_arg_) {
            return intercept::invoker::get().invoke_raw(function_, &right_arg_);
        }

        rv_game_value invoke_raw_binary(binary_function function_, const game_value &left_arg_, const game_value &right_arg_) {
            return intercept::invoker::get().invoke_raw(function_, &left_arg_, &right_arg_);
        }

        void get_type_structure(const char *type_name_, uintptr_t &type_def_, uintptr_t &data_type_def_) {
            auto structure = invoker::get().type_structures[std::string(type_name_)];
            type_def_ = structure.first;
            data_type_def_ = structure.second;
        }

        rv_string * allocate_string(size_t size_) {
            char *raw_data = new char[sizeof(uint32_t) + sizeof(uint32_t) + size_];
            ((rv_string *)raw_data)->length = size_;
            ((rv_string *)raw_data)->ref_count_internal = 1;
            return (rv_string *)raw_data;
        }

        void free_string(rv_string *value_) {
            if (value_->ref_count_internal <= 1)
                delete[] value_;
            else {
                invoker::get().collect_string(value_);
            }
        }

        void free_value(game_value *value_) {
            intercept::invoker::get().release_value(value_);
        }

        nular_function get_nular_function(const char *function_name_) {
            nular_function function;
            if (intercept::loader::get().get_function(std::string(function_name_), function)) {
                return function;
            }
            return NULL;
        }

        unary_function get_unary_function(const char *function_name_) {
            unary_function function;
            if (intercept::loader::get().get_function(std::string(function_name_), function)) {
                return function;
            }
            return NULL;
        }

        unary_function get_unary_function_typed(const char *function_name_, const char *right_arg_type_) {
            unary_function function;
            if (intercept::loader::get().get_function(std::string(function_name_), function, std::string(right_arg_type_))) {
                return function;
            }
            return NULL;
        }

        binary_function get_binary_function(const char *function_name_) {
            binary_function function;
            if (intercept::loader::get().get_function(std::string(function_name_), function)) {
                return function;
            }
            return NULL;
        }

        binary_function get_binary_function_typed(const char *function_name_, const char *left_arg_type_, const char *right_arg_type_) {
            binary_function function;
            if (intercept::loader::get().get_function(std::string(function_name_), function, std::string(left_arg_type_), std::string(right_arg_type_))) {
                return function;
            }
            return NULL;
        }
    }
}