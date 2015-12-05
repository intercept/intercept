#pragma once
#include "../shared.hpp"
#include "shared\functions.hpp"

#define DLLEXPORT __declspec(dllexport)

namespace intercept {
    namespace client {

        class host {
        public:
            static client_functions functions;
        };
        
        extern "C" {
            DLLEXPORT void __cdecl assign_functions(const struct intercept::client_functions funcs);
        }

        void __initialize();
    }


}