#include "export.hpp"
#include "invoker.hpp"


namespace intercept {
    namespace client_function_defs {
        game_value invoke_raw_nular(nular_function function_) {
            return intercept::invoker::get().invoke_raw(function_);
        }

        game_value invoke_raw_unary(unary_function function_, game_value *right_arg_) {
            return intercept::invoker::get().invoke_raw(function_, right_arg_);
        }

        game_value invoke_raw_binary(binary_function function_, game_value *left_arg_, game_value *right_arg_) {
            return intercept::invoker::get().invoke_raw(function_, left_arg_, right_arg_);
        }

        game_value new_scalar(float val_)
        {
            game_value scalar = intercept::invoker::get().create_type<intercept::invoker_type::scalar>();
            ((game_data_number *)scalar.data)->number = val_;
            return scalar;
        }

        game_value new_string(char *string_) {
            game_value string = intercept::invoker::get().create_type<intercept::invoker_type::string>();
            ((game_data_string *)string.data)->set_string(std::string(string_));
            return string;
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