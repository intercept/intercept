/*!
@file
@author Nou (korewananda@gmail.com)

@brief Exported functions for client plugins.

These are the exported functions that the client interfaces with to invoke SQF
functions, allocate and free memory, etc. Almost all of these are hidden and will
never be exposed to the end client developer. If the client developer has found
themselves using these functions they are most likely doing something unintentional.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "shared/types.hpp"

using namespace intercept::types;

namespace intercept {
    using WrapperFunctionBinary = intercept::types::binary_function;
    using WrapperFunctionUnary = intercept::types::unary_function;
    using WrapperFunctionNular = intercept::types::nular_function;

    namespace client_function_defs {
        /*!
        @brief Invokes a raw nular SQF function from a nular function pointer.

        @param function_ The nular_function pointer.

        @return rv_game_value The raw returned data from the function.
        */
        game_value invoke_raw_nular_nolock(const nular_function function_);

        /*!
        @brief Invokes a raw unary SQF function from a unary function pointer.

        @param function_ The unary_function pointer.
        @param right_arg_ A reference to a game_value argument.

        @return rv_game_value The raw returned data from the function.
        */
        game_value invoke_raw_unary_nolock(const unary_function function_, const game_value &right_arg_);

        /*!
        @brief Invokes a raw binary SQF function from a binary function pointer.

        @param function_ The binary_function pointer.
        @param left_arg_ A reference to a game_value argument for the left side.
        @param right_arg_ A reference to a game_value argument for the right side.

        @return rv_game_value The raw returned data from the function.
        */
        game_value invoke_raw_binary_nolock(const binary_function function_, const game_value &left_arg_, const game_value &right_arg_);

        /*!
        @brief Returns type definitions for a given type string.
        
        @param [in] type_name_ A char string of the type, "ARRAY", "SCALAR", etc.
        @param [out] type_def_ A reference to a uintptr_t to store the type address.
        @param [out] data_type_def_ A reference to a uintptr_t to store the data
        type address.
        */
        void get_type_structure(std::string_view type_name_, uintptr_t &type_def_, uintptr_t &data_type_def_);

        /*!@{
        @brief Returns a function pointer of the type named based on the function name
        and argument signatures.
        */
        nular_function get_nular_function(std::string_view function_name_);

        unary_function get_unary_function(std::string_view function_name_);
        unary_function get_unary_function_typed(std::string_view function_name_, std::string_view right_arg_type_);

        binary_function get_binary_function(std::string_view function_name_);
        binary_function get_binary_function_typed(std::string_view function_name_, std::string_view left_arg_type_, std::string_view right_arg_type_);
        //!@}

        void invoker_lock();

        void invoker_unlock();

        /*!
        @brief Get's a pointer to Arma's memory allocator

        This returns a pointer to Arma's internal memory allocator for use by rv_allocator

        @return A pointer to the allocator
        */
        const types::__internal::allocatorInfo* get_engine_allocator();    
        /*!
        @brief Registers SQF Function
        */
        [[nodiscard]] types::registered_sqf_function register_sqf_function(std::string_view name, std::string_view description, WrapperFunctionBinary function_, types::game_data_type return_arg_type, types::game_data_type left_arg_type, types::game_data_type right_arg_type);
        [[nodiscard]] types::registered_sqf_function register_sqf_function_unary(std::string_view name, std::string_view description, WrapperFunctionUnary function_, types::game_data_type return_arg_type, types::game_data_type right_arg_type);
        [[nodiscard]] types::registered_sqf_function register_sqf_function_nular(std::string_view name, std::string_view description, WrapperFunctionNular function_, types::game_data_type return_arg_type);
        [[nodiscard]] std::pair<types::game_data_type, sqf_script_type> register_sqf_type(std::string_view name, std::string_view localizedName, std::string_view description, std::string_view typeName, script_type_info::createFunc cf);
        [[nodiscard]] sqf_script_type register_compound_sqf_type(auto_array<types::game_data_type> types);


        const auto_array<r_string>* get_pbo_files_list();
    }
}
