#pragma once
#include "../shared.hpp"
#include "shared/functions.hpp"

namespace intercept {
    namespace client {








        class host {
        public:
            static client_functions functions;
            static r_string module_name;

            ///@copydoc intercept::sqf_functions::register_sqf_function(std::string_view, std::string_view, WrapperFunctionBinary, types::game_data_type, types::game_data_type, types::game_data_type)
            [[nodiscard]] static registered_sqf_function register_sqf_command(std::string_view name, std::string_view description, WrapperFunctionBinary function_, types::game_data_type return_arg_type, types::game_data_type left_arg_type, types::game_data_type right_arg_type);

            ///@copydoc intercept::sqf_functions::register_sqf_function(std::string_view, std::string_view, WrapperFunctionUnary, types::game_data_type, types::game_data_type)
            [[nodiscard]] static registered_sqf_function register_sqf_command(std::string_view name, std::string_view description, WrapperFunctionUnary function_, types::game_data_type return_arg_type, types::game_data_type right_arg_type);

            ///@copydoc intercept::sqf_functions::register_sqf_function(std::string_view, std::string_view, WrapperFunctionNular, types::game_data_type)
            [[nodiscard]] static registered_sqf_function register_sqf_command(std::string_view name, std::string_view description, WrapperFunctionNular function_, types::game_data_type return_arg_type);

            //Tmp for old syntax taking uintptr_t
            ///@copydoc intercept::sqf_functions::register_sqf_function(std::string_view, std::string_view, WrapperFunctionBinary, types::game_data_type, types::game_data_type, types::game_data_type)
            [[deprecated("use new game_state& syntax instead of uintptr_t")]] [[nodiscard]] static registered_sqf_function register_sqf_command(std::string_view name, std::string_view description, game_value (*function_)(uintptr_t, game_value_parameter, game_value_parameter), types::game_data_type return_arg_type, types::game_data_type left_arg_type, types::game_data_type right_arg_type) {
                return register_sqf_command(name, description, reinterpret_cast<WrapperFunctionBinary>(function_), return_arg_type, left_arg_type, right_arg_type);
            }

            ///@copydoc intercept::sqf_functions::register_sqf_function(std::string_view, std::string_view, WrapperFunctionUnary, types::game_data_type, types::game_data_type)
            [[deprecated("use new game_state& syntax instead of uintptr_t")]] [[nodiscard]] static registered_sqf_function register_sqf_command(std::string_view name, std::string_view description, game_value (*function_)(uintptr_t, game_value_parameter), types::game_data_type return_arg_type, types::game_data_type right_arg_type) {
                return register_sqf_command(name, description, reinterpret_cast<WrapperFunctionUnary>(function_), return_arg_type, right_arg_type);
            }

            ///@copydoc intercept::sqf_functions::register_sqf_function(std::string_view, std::string_view, WrapperFunctionNular, types::game_data_type)
            [[deprecated("use new game_state& syntax instead of uintptr_t")]] [[nodiscard]] static registered_sqf_function register_sqf_command(std::string_view name, std::string_view description, game_value (*function_)(uintptr_t), types::game_data_type return_arg_type) {
                return register_sqf_command(name, description, reinterpret_cast<WrapperFunctionNular>(function_), return_arg_type);
            }

            ///@copydoc intercept::sqf_functions::register_sqf_type
            [[nodiscard]] static std::pair<types::game_data_type, sqf_script_type*> register_sqf_type(std::string_view name, std::string_view localizedName, std::string_view description, std::string_view typeName, script_type_info::createFunc cf);

            ///@copydoc intercept::sqf_functions::register_sqf_type
            [[nodiscard]] static sqf_script_type* register_compound_sqf_type(const auto_array<types::game_data_type>& types);


            ///@copydoc intercept::extensions::register_plugin_interface
            static register_plugin_interface_result register_plugin_interface(std::string_view name_, uint32_t api_version_, void* interface_class_);
            ///@copydoc intercept::extensions::list_plugin_interfaces
            static std::pair<r_string, auto_array<uint32_t>> list_plugin_interfaces(std::string_view name_);
            ///@copydoc intercept::extensions::request_plugin_interface
            static std::optional<void*> request_plugin_interface(std::string_view name_, uint32_t api_version_);


        };


        
        extern "C" {
            /// @private
            DLLEXPORT void CDECL assign_functions(const struct client_functions funcs, r_string module_name);
        }
        /// @private
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
            void unlock();
        protected:
            bool _locked;
        };
    }


}
