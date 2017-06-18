#include "client.hpp"
#include "shared/client_types.hpp"
#include "pointers.hpp"

using namespace intercept::types;
namespace intercept {
    namespace client {
        client_functions host::functions;

        registered_sqf_function host::registerFunction(std::string_view name, std::string_view description, WrapperFunctionBinary function_, GameDataType return_arg_type, GameDataType left_arg_type, GameDataType right_arg_type) {
            return functions.register_sqf_function(name, description, function_, return_arg_type, left_arg_type, right_arg_type);
        }

        registered_sqf_function host::registerFunction(std::string_view name, std::string_view description, WrapperFunctionUnary function_, GameDataType return_arg_type, GameDataType right_arg_type) {
            return functions.register_sqf_function_unary(name, description, function_, return_arg_type, right_arg_type);
        }
        registered_sqf_function host::registerFunction(std::string_view name, std::string_view description, WrapperFunctionNular function_, GameDataType return_arg_type) {
            return functions.register_sqf_function_nular(name, description, function_, return_arg_type);
        }
        std::pair<GameDataType, sqf_script_type> host::registerType(std::string_view name, std::string_view localizedName, std::string_view description, std::string_view typeName, script_type_info::createFunc cf) {
            return functions.register_sqf_type(name, localizedName, description, typeName, cf);
        }

        // Using __cdecl to prevent name mangling and provide better backwards compatibility
        void CDECL assign_functions(const struct client_functions funcs) {
            host::functions = funcs;

            __sqf::__initialize();

            uintptr_t type_def;
            uintptr_t data_type_def;

            host::functions.get_type_structure("ARRAY", type_def, data_type_def);
            auto allocator_info = host::functions.get_engine_allocator();
            game_data_array::type_def = type_def;
            game_data_array::data_type_def = data_type_def;
            game_data_array::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(GameDataType::ARRAY)];


            host::functions.get_type_structure("SCALAR", type_def, data_type_def);
            game_data_number::type_def = type_def;
            game_data_number::data_type_def = data_type_def;
            game_data_number::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(GameDataType::SCALAR)];

            host::functions.get_type_structure("STRING", type_def, data_type_def);
            game_data_string::type_def = type_def;
            game_data_string::data_type_def = data_type_def;
            game_data_string::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(GameDataType::STRING)];

            host::functions.get_type_structure("OBJECT", type_def, data_type_def);
            game_data_object::type_def = type_def;
            game_data_object::data_type_def = data_type_def;

            host::functions.get_type_structure("BOOL", type_def, data_type_def);
            game_data_bool::type_def = type_def;
            game_data_bool::data_type_def = data_type_def;
            game_data_bool::pool_alloc_base = allocator_info->_poolAllocs[static_cast<size_t>(GameDataType::BOOL)];


            host::functions.get_type_structure("CODE", type_def, data_type_def);
            game_data_code::type_def = type_def;
            game_data_code::data_type_def = data_type_def;

            host::functions.get_type_structure("GROUP", type_def, data_type_def);
            game_data_group::type_def = type_def;
            game_data_group::data_type_def = data_type_def;

            host::functions.get_type_structure("CONFIG", type_def, data_type_def);
            game_data_config::type_def = type_def;
            game_data_config::data_type_def = data_type_def;

            host::functions.get_type_structure("CONTROL", type_def, data_type_def);
            game_data_control::type_def = type_def;
            game_data_control::data_type_def = data_type_def;

            host::functions.get_type_structure("DISPLAY", type_def, data_type_def);
            game_data_display::type_def = type_def;
            game_data_display::data_type_def = data_type_def;

            host::functions.get_type_structure("LOCATION", type_def, data_type_def);
            game_data_location::type_def = type_def;
            game_data_location::data_type_def = data_type_def;

            host::functions.get_type_structure("SCRIPT", type_def, data_type_def);
            game_data_script::type_def = type_def;
            game_data_script::data_type_def = data_type_def;

            host::functions.get_type_structure("SIDE", type_def, data_type_def);
            game_data_side::type_def = type_def;
            game_data_side::data_type_def = data_type_def;

            host::functions.get_type_structure("TEXT", type_def, data_type_def);
            game_data_rv_text::type_def = type_def;
            game_data_rv_text::data_type_def = data_type_def;

            host::functions.get_type_structure("TEAM_MEMBER", type_def, data_type_def);
            game_data_team::type_def = type_def;
            game_data_team::data_type_def = data_type_def;

            host::functions.get_type_structure("NAMESPACE", type_def, data_type_def);
            game_data_rv_namespace::type_def = type_def;
            game_data_rv_namespace::data_type_def = data_type_def;



            host::functions.get_type_structure("GV", type_def, data_type_def);
            game_value::__vptr_def = type_def;
        }

        void CDECL handle_unload() {

        }

        invoker_lock::invoker_lock(bool delayed_) : _locked(false) {
            if (!delayed_)
                lock();
        }

        invoker_lock::~invoker_lock() {
            if (_locked)
                host::functions.invoker_unlock();
        }

        inline void invoker_lock::lock() {
            if (!_locked) {
                host::functions.invoker_lock();
                _locked = true;
            }
        }

    }
}