#pragma once
#include "../shared.hpp"
#include "shared\functions.hpp"
#include "client_types.hpp"




#define DLLEXPORT __declspec(dllexport)
using namespace intercept::client::types;
namespace intercept {
    namespace client {
        
        extern "C" {
            DLLEXPORT void __cdecl assign_functions(const struct intercept::client_functions funcs);
        }

        void __initialize();
    }

    namespace sqf {
        float random(float max_);
        object player();
        void side_chat(object obj_, const std::string &message_);
    }
}