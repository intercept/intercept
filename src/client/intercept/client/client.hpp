#pragma once
#include "../shared.hpp"
#include "shared\types.hpp"
#include "shared\functions.hpp"

#define DLLEXPORT __declspec(dllexport)

namespace intercept {
    namespace client {
        extern "C" {
            DLLEXPORT void __cdecl assign_functions(const struct intercept::client_functions funcs);
        }

        void __initialize();

    }

    namespace sqf {
        float random(float max_);
    }
}