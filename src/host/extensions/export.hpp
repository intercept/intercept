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
    using WrapperFunctionBinary = game_value*(*)(game_value*, uintptr_t, uintptr_t, uintptr_t);
    using WrapperFunctionUnary = game_value*(*)(game_value*, uintptr_t, uintptr_t);
    using WrapperFunctionNular = game_value*(*)(game_value*, uintptr_t);

    namespace client_function_defs {
        /*!
        @brief Invokes a raw nular SQF function from a nular function pointer.

        @params function_ The nular_function pointer.

        @return rv_game_value The raw returned data from the function.
        */
        game_value invoke_raw_nular_nolock(const nular_function function_);

        /*!
        @brief Invokes a raw unary SQF function from a unary function pointer.

        @params function_ The unary_function pointer.
        @params right_arg_ A reference to a game_value argument.

        @return rv_game_value The raw returned data from the function.
        */
        game_value invoke_raw_unary_nolock(const unary_function function_, const game_value &right_arg_);

        /*!
        @brief Invokes a raw binary SQF function from a binary function pointer.

        @params function_ The binary_function pointer.
        @params left_arg_ A reference to a game_value argument for the left side.
        @params right_arg_ A reference to a game_value argument for the right side.

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
        void get_type_structure(const char *type_name_, uintptr_t &type_def_, uintptr_t &data_type_def_);

        /*!@{
        @brief Returns a function pointer of the type named based on the function name
        and argument signatures.
        */
        nular_function get_nular_function(const char * function_name_);

        unary_function get_unary_function(const char * function_name_);
        unary_function get_unary_function_typed(const char * function_name_, const char * right_arg_type_);

        binary_function get_binary_function(const char * function_name_);
        binary_function get_binary_function_typed(const char * function_name_, const char * left_arg_type_, const char * right_arg_type_);
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
        //#TODO need to keep interface C-like. use rstring's instead of std::string
        types::registered_sqf_function register_sqf_function(std::string name, std::string description, WrapperFunctionBinary function_, types::__internal::GameDataType return_arg_type, types::__internal::GameDataType left_arg_type, types::__internal::GameDataType right_arg_type);
        types::registered_sqf_function register_sqf_function_unary(std::string name, std::string description, WrapperFunctionUnary function_, types::__internal::GameDataType return_arg_type, types::__internal::GameDataType right_arg_type);
        types::registered_sqf_function register_sqf_function_nular(std::string name, std::string description, WrapperFunctionNular function_, types::__internal::GameDataType return_arg_type);
        std::pair<types::__internal::GameDataType, sqf_script_type> register_sqf_type(r_string name, r_string localizedName, r_string description, r_string typeName, script_type_info::createFunc cf);
    }
}