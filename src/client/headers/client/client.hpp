#pragma once
#include "../shared.hpp"
#include "shared/functions.hpp"

namespace intercept {
    namespace client {








        class host {
        public:
            static client_functions functions;
           
            /**
            * \brief Registers a custom SQF Binary Command
            * \param name
            * \param description
            * \param function_
            * \param return_arg_type
            * \param left_arg_type
            * \param right_arg_type
            * \return A wrapper that should be kept alive as long as the function should be usable
            */
            [[nodiscard]] static registered_sqf_function registerFunction(std::string_view name, std::string_view description, WrapperFunctionBinary function_, types::GameDataType return_arg_type, types::GameDataType left_arg_type, types::GameDataType right_arg_type);
            /**
            * \brief Registers a custom SQF Unary Command
            * \param name
            * \param description
            * \param function_
            * \param return_arg_type
            * \param right_arg_type
            * \return A wrapper that should be kept alive as long as the function should be usable
            */
            [[nodiscard]] static registered_sqf_function registerFunction(std::string_view name, std::string_view description, WrapperFunctionUnary function_, types::GameDataType return_arg_type, types::GameDataType right_arg_type);
            /**
            * \brief Registers a custom SQF Nular Command
            * \param name
            * \param description
            * \param function_
            * \param return_arg_type
            * \return A wrapper that should be kept alive as long as the function should be usable
            */
            [[nodiscard]] static registered_sqf_function registerFunction(std::string_view name, std::string_view description, WrapperFunctionNular function_, types::GameDataType return_arg_type);
            
            /**
            * \brief Registers a custom SQF script type
            * \param name
            * \param localizedName
            * \param description
            * \param typeName
            * \param cf
            * \return The resulting GameDataType enum value and a instantiated sqf_script_type
            */
            static std::pair<types::GameDataType, sqf_script_type> registerType(std::string_view name, std::string_view localizedName, std::string_view description, std::string_view typeName, script_type_info::createFunc cf);
        
        
        };


        
        extern "C" {
            DLLEXPORT void CDECL assign_functions(const struct client_functions funcs);
            DLLEXPORT void CDECL handle_unload();
        }

        void __initialize();

        class invoker_lock {
        public:
            explicit invoker_lock(bool delayed_ = false);
            invoker_lock(const invoker_lock &) = delete;
            invoker_lock(invoker_lock &&) = delete;
            invoker_lock & operator=(const invoker_lock &) = delete;
            invoker_lock & operator=(invoker_lock &&) = delete;
            ~invoker_lock();
            void lock();
        protected:
            bool _locked;
        };
    }


}
