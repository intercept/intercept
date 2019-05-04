/*!
@file
@author Dedmen (dedmen@dedmen.de)

@brief Contains the intercept::sqf_functions class.
@defgroup RSQF Registered SQF Functions
@ingroup RSQF
https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"
#include "loader.hpp"
#include "shared/types.hpp"
#include <mutex>
#include <condition_variable>
#include <queue>

namespace intercept {

    namespace __internal {
        enum class functionType {
            sqf_nular,
            sqf_function,
            sqf_operator
        };

        class registered_sqf_func_wrapper {
            using GameDataType = types::game_data_type;
        public:
            struct undo_info {
                r_string _description;
                union {
                    binary_function* _procB;
                    unary_function* _procU;
                    nular_function* _procN;
                };
            };


            registered_sqf_func_wrapper(GameDataType return_type_, __internal::gsNular* func_);
            registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, __internal::gsFunction* func_);
            registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, GameDataType right_arg_type_, __internal::gsOperator* func_);
            registered_sqf_func_wrapper(GameDataType return_type_, __internal::gsNular* func_, undo_info undo);
            registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, __internal::gsFunction* func_, undo_info undo);
            registered_sqf_func_wrapper(GameDataType return_type_, GameDataType left_arg_type_, GameDataType right_arg_type_, __internal::gsOperator* func_, undo_info undo);
            void setUnused() noexcept;

            const functionType _type;
            const r_string _name;
            union {
                __internal::gsNular* _nular;
                __internal::gsFunction* _func;
                __internal::gsOperator* _op;
            };
            const types::game_data_type _lArgType;
            const types::game_data_type _rArgType;
            const types::game_data_type _returnType;
            std::unique_ptr<undo_info> undo;

        };
    }

    class registered_sqf_function_impl {
    public:
        registered_sqf_function_impl(std::shared_ptr<__internal::registered_sqf_func_wrapper> func_) noexcept;
        /*!
        @brief Gets called when Plugin unloads. This replaces the Function that will get unloaded by a dummy function
        */
        ~registered_sqf_function_impl();

        std::shared_ptr<__internal::registered_sqf_func_wrapper> _func;
    };

    /*!
    @brief Takes care of Wrapper functions for registered SQF Functions
    */
    class sqf_functions
        : public singleton<sqf_functions> {
        friend class registered_sqf_function_impl;
    public:
        sqf_functions() noexcept;
        ~sqf_functions();
        void initialize() noexcept;
        void setDisabled() noexcept;
        using WrapperFunctionBinary = intercept::types::binary_function;
        using WrapperFunctionUnary = intercept::types::unary_function;
        using WrapperFunctionNular = intercept::types::nular_function;
        /**
        * @brief Registers a custom SQF Binary Command
        * @param name
        * @param description
        * @param function_ Your function wrapped into [userFunctionWrapper](https://github.com/intercept/intercept/wiki/Registered-Functions)
        * @param return_arg_type A value from intercept::types::game_data_type
        * @param left_arg_type A value from intercept::types::game_data_type
        * @param right_arg_type A value from intercept::types::game_data_type
        * @return A wrapper that should be kept alive as long as the function should be usable
        * @ingroup RSQF
        */
        [[nodiscard]] registered_sqf_function register_sqf_function(std::string_view name, std::string_view description, WrapperFunctionBinary function_, types::game_data_type return_arg_type, types::game_data_type left_arg_type, types::game_data_type right_arg_type);
        /**
        * @brief Registers a custom SQF Unary Command
        * @param name
        * @param description
        * @param function_ Your function wrapped into [userFunctionWrapper](https://github.com/intercept/intercept/wiki/Registered-Functions)
        * @param return_arg_type A value from intercept::types::game_data_type
        * @param right_arg_type A value from intercept::types::game_data_type
        * @return A wrapper that should be kept alive as long as the function should be usable
        * @ingroup RSQF
        */
        [[nodiscard]] registered_sqf_function register_sqf_function(std::string_view name, std::string_view description, WrapperFunctionUnary function_, types::game_data_type return_arg_type, types::game_data_type right_arg_type);
        /**
        * @brief Registers a custom SQF Nular Command
        * @param name
        * @param description
        * @param function_ Your function wrapped into [userFunctionWrapper](https://github.com/intercept/intercept/wiki/Registered-Functions)
        * @param return_arg_type A value from intercept::types::game_data_type
        * @return A wrapper that should be kept alive as long as the function should be usable
        * @ingroup RSQF
        */
        [[nodiscard]] registered_sqf_function register_sqf_function(std::string_view name, std::string_view description, WrapperFunctionNular function_, types::game_data_type return_arg_type);


        bool unregister_sqf_function(const std::shared_ptr<__internal::registered_sqf_func_wrapper>& shared);

        /**
        * @brief Registers a custom SQF script type
        * @param name
        * @param localizedName
        * @param description
        * @param typeName
        * @param cf
        * @return The resulting game_data_type enum value and a instantiated sqf_script_type
        * @ingroup RSQF
        */
        std::pair<types::game_data_type, sqf_script_type> register_sqf_type(std::string_view name, std::string_view localizedName, std::string_view description, std::string_view typeName, script_type_info::createFunc cf);

        /**
        * @brief Registers a custom SQF Compound script type
        * @param types
        * @return a instantiated sqf_script_type
        * @ingroup RSQF
        */
        sqf_script_type register_compound_sqf_type(auto_array<types::game_data_type> types);


    private:
        __internal::gsNular* findNular(std::string name) const;
        __internal::gsFunction* findUnary(std::string name, types::game_data_type argument_type) const;
        __internal::gsOperator* findBinary(std::string name, types::game_data_type left_argument_type, types::game_data_type right_argument_type) const;
        __internal::game_operators* findOperators(std::string name) const;
        __internal::game_functions* findFunctions(std::string name) const;
        sqf_register_functions _registerFuncs;
        std::map<uintptr_t, auto_array<char>> _keeper;
        /**
         * \brief If true then we can carelessly modify the script command tables
         */
        bool _canRegister {false};
    };

}
