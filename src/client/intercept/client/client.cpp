#include "client.hpp"
#include "shared/client_types.hpp"
#include "pointers.hpp"

using namespace intercept::types;
namespace intercept {
    namespace client {
        client_functions host::functions;
        r_string host::module_name;

        registered_sqf_function host::registerFunction(std::string_view name, std::string_view description, WrapperFunctionBinary function_, game_data_type return_arg_type, game_data_type left_arg_type, game_data_type right_arg_type) {
            return functions.register_sqf_function(name, description, function_, return_arg_type, left_arg_type, right_arg_type);
        }
        registered_sqf_function host::registerFunction(std::string_view name, std::string_view description, WrapperFunctionUnary function_, game_data_type return_arg_type, game_data_type right_arg_type) {
            return functions.register_sqf_function_unary(name, description, function_, return_arg_type, right_arg_type);
        }
        registered_sqf_function host::registerFunction(std::string_view name, std::string_view description, WrapperFunctionNular function_, game_data_type return_arg_type) {
            return functions.register_sqf_function_nular(name, description, function_, return_arg_type);
        }
        std::pair<game_data_type, sqf_script_type> host::registerType(std::string_view name, std::string_view localizedName, std::string_view description, std::string_view typeName, script_type_info::createFunc cf) {
            return functions.register_sqf_type(name, localizedName, description, typeName, cf);
        }

        registered_sqf_function host::register_sqf_command(std::string_view name, std::string_view description, WrapperFunctionBinary function_, game_data_type return_arg_type, game_data_type left_arg_type, game_data_type right_arg_type) {
            return functions.register_sqf_function(name, description, function_, return_arg_type, left_arg_type, right_arg_type);
        }
        registered_sqf_function host::register_sqf_command(std::string_view name, std::string_view description, WrapperFunctionUnary function_, game_data_type return_arg_type, game_data_type right_arg_type) {
            return functions.register_sqf_function_unary(name, description, function_, return_arg_type, right_arg_type);
        }
        registered_sqf_function host::register_sqf_command(std::string_view name, std::string_view description, WrapperFunctionNular function_, game_data_type return_arg_type) {
            return functions.register_sqf_function_nular(name, description, function_, return_arg_type);
        }
        std::pair<game_data_type, sqf_script_type> host::register_sqf_type(std::string_view name, std::string_view localizedName, std::string_view description, std::string_view typeName, script_type_info::createFunc cf) {
            return functions.register_sqf_type(name, localizedName, description, typeName, cf);
        }

        sqf_script_type host::register_compound_sqf_type(auto_array<game_data_type> types) {
            return functions.register_compound_sqf_type(types);
        }

        register_plugin_interface_result host::register_plugin_interface(std::string_view name_, uint32_t api_version_, void* interface_class_) {
            if (!interface_class_) return register_plugin_interface_result::invalid_interface_class;
            auto result = functions.register_plugin_interface(module_name, name_, api_version_, interface_class_);
            return result;
        }
        std::pair<r_string, auto_array<uint32_t>> host::list_plugin_interfaces(std::string_view name_) {
            return functions.list_plugin_interfaces(name_);
        }
        std::optional<void*> host::request_plugin_interface(std::string_view name_, uint32_t api_version_) {
            auto result = functions.request_plugin_interface(module_name,name_, api_version_);
            if (result)
                return result;
            return {};
        }

        // Using __cdecl to prevent name mangling and provide better backwards compatibility
        void CDECL assign_functions(const struct client_functions funcs, r_string module_name) {
            host::functions = funcs;
            host::module_name = module_name;

#ifndef INTERCEPT_NO_SQF
            __sqf::__initialize();
#endif

            uintptr_t type_def;
            uintptr_t data_type_def;

            host::functions.get_type_structure("ARRAY"sv, type_def, data_type_def);
            auto allocator_info = host::functions.get_engine_allocator();
            game_data_array::type_def = type_def;
            game_data_array::data_type_def = data_type_def;
            game_data_array::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(game_data_type::ARRAY)];


            host::functions.get_type_structure("SCALAR"sv, type_def, data_type_def);
            game_data_number::type_def = type_def;
            game_data_number::data_type_def = data_type_def;
            game_data_number::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(game_data_type::SCALAR)];

            host::functions.get_type_structure("STRING"sv, type_def, data_type_def);
            game_data_string::type_def = type_def;
            game_data_string::data_type_def = data_type_def;
            game_data_string::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(game_data_type::STRING)];

            host::functions.get_type_structure("OBJECT"sv, type_def, data_type_def);
            game_data_object::type_def = type_def;
            game_data_object::data_type_def = data_type_def;

            host::functions.get_type_structure("BOOL"sv, type_def, data_type_def);
            game_data_bool::type_def = type_def;
            game_data_bool::data_type_def = data_type_def;
            game_data_bool::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(game_data_type::BOOL)];


            host::functions.get_type_structure("CODE"sv, type_def, data_type_def);
            game_data_code::type_def = type_def;
            game_data_code::data_type_def = data_type_def;
            game_data_code::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(game_data_type::CODE)];

            host::functions.get_type_structure("GROUP"sv, type_def, data_type_def);
            game_data_group::type_def = type_def;
            game_data_group::data_type_def = data_type_def;

            host::functions.get_type_structure("CONFIG"sv, type_def, data_type_def);
            game_data_config::type_def = type_def;
            game_data_config::data_type_def = data_type_def;

            host::functions.get_type_structure("CONTROL"sv, type_def, data_type_def);
            game_data_control::type_def = type_def;
            game_data_control::data_type_def = data_type_def;

            host::functions.get_type_structure("DISPLAY"sv, type_def, data_type_def);
            game_data_display::type_def = type_def;
            game_data_display::data_type_def = data_type_def;

            host::functions.get_type_structure("LOCATION"sv, type_def, data_type_def);
            game_data_location::type_def = type_def;
            game_data_location::data_type_def = data_type_def;

            host::functions.get_type_structure("SCRIPT"sv, type_def, data_type_def);
            game_data_script::type_def = type_def;
            game_data_script::data_type_def = data_type_def;

            host::functions.get_type_structure("SIDE"sv, type_def, data_type_def);
            game_data_side::type_def = type_def;
            game_data_side::data_type_def = data_type_def;

            host::functions.get_type_structure("TEXT"sv, type_def, data_type_def);
            game_data_rv_text::type_def = type_def;
            game_data_rv_text::data_type_def = data_type_def;

            host::functions.get_type_structure("TEAM_MEMBER"sv, type_def, data_type_def);
            game_data_team_member::type_def = type_def;
            game_data_team_member::data_type_def = data_type_def;

            host::functions.get_type_structure("NAMESPACE"sv, type_def, data_type_def);
            game_data_namespace::type_def = type_def;
            game_data_namespace::data_type_def = data_type_def;
            
            host::functions.get_type_structure("NOTHING"sv, type_def, data_type_def);
            game_data_nothing::type_def = type_def;
            game_data_nothing::data_type_def = data_type_def;
            
            host::functions.get_type_structure("GV"sv, type_def, data_type_def);
            intercept::types::__internal::set_game_value_vtable(type_def);

            host::functions.get_type_structure("SQF_SCRIPT_TYPE"sv, type_def, data_type_def);
            sqf_script_type::type_def = type_def;
        }

        invoker_lock::invoker_lock(bool delayed_) : _locked(false) {
            if (!delayed_)
                lock();
        }

        invoker_lock::~invoker_lock() {
            if (_locked)
                host::functions.invoker_unlock();
        }

        void invoker_lock::lock() {
            if (!_locked) {
                host::functions.invoker_lock();
                _locked = true;
            }
        }

        void invoker_lock::unlock() {
            if (_locked) {
                host::functions.invoker_unlock();
                _locked = false;
            }
        }

    }
}
