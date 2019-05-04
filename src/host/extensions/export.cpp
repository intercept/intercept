#include "export.hpp"
#include "invoker.hpp"
#include "extensions.hpp"


namespace intercept {
    namespace client_function_defs {

        game_value invoke_raw_nular_nolock(const nular_function function_) {
            return invoker::invoke_raw_nolock(function_);
        }

        game_value invoke_raw_unary_nolock(const unary_function function_, const game_value & right_arg_) {
            return invoker::invoke_raw_nolock(function_, right_arg_);
        }

        game_value invoke_raw_binary_nolock(const binary_function function_, const game_value & left_arg_, const game_value & right_arg_) {
            return invoker::invoke_raw_nolock(function_, left_arg_, right_arg_);
        }

        void get_type_structure(std::string_view type_name_, uintptr_t &type_def_, uintptr_t &data_type_def_) {
            auto structure = invoker::get().type_structures[std::string(type_name_)];
            type_def_ = structure.first;
            data_type_def_ = structure.second;
        }

        nular_function get_nular_function(std::string_view function_name_) {
            nular_function function;
            if (loader::get().get_function(std::string(function_name_), function)) {
                return function;
            }
            return nullptr;
        }

        unary_function get_unary_function(std::string_view function_name_) {
            unary_function function;
            if (loader::get().get_function(std::string(function_name_), function)) {
                return function;
            }
            return nullptr;
        }

        unary_function get_unary_function_typed(std::string_view function_name_, std::string_view right_arg_type_) {
            unary_function function;
            if (loader::get().get_function(std::string(function_name_), function, std::string(right_arg_type_))) {
                return function;
            }
            return nullptr;
        }

        binary_function get_binary_function(std::string_view function_name_) {
            binary_function function;
            if (loader::get().get_function(std::string(function_name_), function)) {
                return function;
            }
            return nullptr;
        }

        binary_function get_binary_function_typed(std::string_view function_name_, std::string_view left_arg_type_, std::string_view right_arg_type_) {
            binary_function function;
            if (loader::get().get_function(std::string(function_name_), function, std::string(left_arg_type_), std::string(right_arg_type_))) {
                return function;
            }
            return nullptr;
        }

        void invoker_lock() {
            invoker::get().lock();
        }

        void invoker_unlock() {
            invoker::get().unlock();
        }

        const types::__internal::allocatorInfo* get_engine_allocator() {
            return loader::get().get_allocator();
        }

        registered_sqf_function register_sqf_function(std::string_view name, std::string_view description, WrapperFunctionBinary function_, types::game_data_type return_arg_type, types::game_data_type left_arg_type, types::game_data_type right_arg_type) {
            CERT_ENTER;
            auto registered = sqf_functions::get().register_sqf_function(name, description, function_, return_arg_type, left_arg_type, right_arg_type);
            CERT_EXIT;
            return registered;
        }

        registered_sqf_function register_sqf_function_unary(std::string_view name, std::string_view description, WrapperFunctionUnary function_, types::game_data_type return_arg_type, types::game_data_type right_arg_type) {
            CERT_ENTER;
            auto registered = sqf_functions::get().register_sqf_function(name, description, function_, return_arg_type, right_arg_type);
            CERT_EXIT;
            return registered;
        }
        registered_sqf_function register_sqf_function_nular(std::string_view name, std::string_view description, WrapperFunctionNular function_, types::game_data_type return_arg_type) {
            CERT_ENTER;
            auto registered = sqf_functions::get().register_sqf_function(name, description, function_, return_arg_type);
            CERT_EXIT;
            return registered;
        }
        std::pair<types::game_data_type, sqf_script_type> register_sqf_type(std::string_view name, std::string_view localizedName, std::string_view description, std::string_view typeName, script_type_info::createFunc cf) {
            CERT_ENTER;
            auto registered = sqf_functions::get().register_sqf_type(name, localizedName, description, typeName, cf);
            CERT_EXIT;
            return registered;
        }

        sqf_script_type register_compound_sqf_type(auto_array<types::game_data_type> types) {
            CERT_ENTER;
            auto registered = sqf_functions::get().register_compound_sqf_type(types);
            CERT_EXIT;
            return registered;
        }

        const auto_array<r_string>* get_pbo_files_list() {
            return &invoker::get().files_in_pbo_banks;
        }
    }
}
