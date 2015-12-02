#pragma once
using namespace intercept::rv_types;
using namespace intercept::client;

namespace intercept {
    namespace client {
        intercept::client_functions functions;

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
}