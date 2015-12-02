#include "client.hpp"
#include "pointers.hpp"
#include "client_types.hpp"
intercept::client_functions functions;
using namespace intercept::rv_types;
namespace intercept {
    namespace client {
        
        void __initialize();

        // Using __cdecl to prevent name mangling and provide better backwards compatibility
        void __cdecl assign_functions(const struct intercept::client_functions funcs) {
            functions = funcs;
            __initialize();
        }
    }

    namespace sqf {

        float random(float max_) {
            game_value max = functions.new_scalar(max_);
            game_value rand_val = functions.invoke_raw_unary(client::__sqf::unary__random__scalar_nan__ret__scalar_nan, &max);
            functions.free_value(&max);
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