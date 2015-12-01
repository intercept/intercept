#include "client.hpp"
using namespace intercept::rv_types;
namespace intercept {
    namespace client {
        intercept::client_functions functions;
        void __initialize();

        // Using __cdecl to prevent name mangling and provide better backwards compatibility
        void __cdecl assign_functions(const struct intercept::client_functions funcs) {
            functions = funcs;
            __initialize();
        }

        namespace __sqf {
            unary_function unary_random_scalar_raw;
            nular_function nular_player_raw;
        }

        void __initialize()
        {
            __sqf::unary_random_scalar_raw = (unary_function)functions.get_unary_function_typed("random", "SCALAR");
            __sqf::nular_player_raw = (nular_function)functions.get_nular_function("player");
        }
    }

    namespace sqf {
        float random(float max_) {
            game_value max = client::functions.new_scalar(max_);
            game_value rand_val = client::functions.invoke_raw_unary(client::__sqf::unary_random_scalar_raw, &max);
            client::functions.free_value(&max);
            float rand = ((game_data_number *)rand_val.data)->number;
            client::functions.free_value(&rand_val);
            return rand;
        }
    }
}