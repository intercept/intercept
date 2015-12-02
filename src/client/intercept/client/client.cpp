#include "client.hpp"
#include "pointers.hpp"
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
            game_value max = client::functions.new_scalar(max_);
            game_value rand_val = client::functions.invoke_raw_unary(client::__sqf::unary__random__scalar_nan__ret__scalar_nan, &max);
            client::functions.free_value(&max);
            float rand = ((game_data_number *)rand_val.data)->number;
            client::functions.free_value(&rand_val);
            return rand;
        }
    }
}