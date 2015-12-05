#include "client.hpp"
#include "client_types.hpp"
#include "vector.hpp"
#include "macros.hpp"
#include "pointers.hpp"


using namespace intercept::rv_types;
namespace intercept {
    namespace client {
        client_functions host::functions;

        // Using __cdecl to prevent name mangling and provide better backwards compatibility
        void __cdecl assign_functions(const struct intercept::client_functions funcs) {
            host::functions = funcs;
            __sqf::__initialize();

            uintptr_t type_def;
            uintptr_t data_type_def;

            host::functions.get_type_structure("ARRAY", type_def, data_type_def);
            game_data_array::type_def = type_def;
            game_data_array::data_type_def = data_type_def;
            game_data_array_stack::type_def = type_def;
            game_data_array_stack::data_type_def = data_type_def;


            host::functions.get_type_structure("SCALAR", type_def, data_type_def);
            game_data_number::type_def = type_def;
            game_data_number::data_type_def = data_type_def;

            host::functions.get_type_structure("STRING", type_def, data_type_def);
            game_data_string::type_def = type_def;
            game_data_string::data_type_def = data_type_def;

            host::functions.get_type_structure("OBJECT", type_def, data_type_def);
            game_data_object::type_def = type_def;
            game_data_object::data_type_def = data_type_def;

            host::functions.get_type_structure("BOOL", type_def, data_type_def);
            game_data_bool::type_def = type_def;
            game_data_bool::data_type_def = data_type_def;

            host::functions.get_type_structure("GV", type_def, data_type_def);
            game_value::__vptr_def = type_def;

        }
    }
}