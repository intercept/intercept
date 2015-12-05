#pragma once
#include "../shared.hpp"
#include "client.hpp"
#include "shared\functions.hpp"
#include "client_types.hpp"

using namespace intercept::rv_types;
using namespace intercept::client;

namespace intercept {
    namespace client {

        class __sqf {
        public:
            static void __initialize();
#include "sqf_pointers_declaration.hpp"
        };

        
    }
}