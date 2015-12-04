#include "client.hpp"
#include "pointers.hpp"
#include "client_types.hpp"
#include "vector.hpp"
#include "macros.hpp"


intercept::client_functions functions;
using namespace intercept::rv_types;
namespace intercept {
    namespace client {
        
        void __initialize();

        // Using __cdecl to prevent name mangling and provide better backwards compatibility
        void __cdecl assign_functions(const struct intercept::client_functions funcs) {
            functions = funcs;
            __initialize();

            uintptr_t type_def;
            uintptr_t data_type_def;

            functions.get_type_structure("ARRAY", type_def, data_type_def);
            game_data_array::type_def = type_def;
            game_data_array::data_type_def = data_type_def;
            game_data_array_stack::type_def = type_def;
            game_data_array_stack::data_type_def = data_type_def;


            functions.get_type_structure("SCALAR", type_def, data_type_def);
            game_data_number::type_def = type_def;
            game_data_number::data_type_def = data_type_def;

            functions.get_type_structure("STRING", type_def, data_type_def);
            game_data_string::type_def = type_def;
            game_data_string::data_type_def = data_type_def;

            functions.get_type_structure("OBJECT", type_def, data_type_def);
            game_data_object::type_def = type_def;
            game_data_object::data_type_def = data_type_def;

            functions.get_type_structure("GV", type_def, data_type_def);
            game_value::__vptr_def = type_def;

        }
    }

    namespace sqf {

        float random(float max_) {
            /*
            Why is there random junk here?

            This is a general purpose testing function.

            SQF's random implementation is redundant, so here be experiments!
            */
            client::types::vector3 test_vec;
            test_vec.x = 100.0f;
            test_vec.y = 200.0f;
            test_vec.z = 300.0f;

            STACK_3DARRAY(testers, test_vec);
            STACK_SCALAR(max_val, max_);
            game_value rand_val = functions.invoke_raw_unary(client::__sqf::unary__random__scalar_nan__ret__scalar_nan, &max_val);
            float rand = ((game_data_number *)rand_val.data)->number;
            functions.free_value(&rand_val);
            return rand;
        }

        object player() {
            game_value player_obj = functions.invoke_raw_nular(client::__sqf::nular__player__ret__object);
            return std::make_shared<object_ptr>(player_obj);
        }

        void side_chat(object obj_, const std::string &message_) {
            game_value message = functions.new_string(message_.c_str());
            functions.invoke_raw_binary(client::__sqf::binary__sidechat__object_array__string__ret__nothing, &obj_->rv_obj, &message);
            functions.free_value(&message);
        }

    }
}