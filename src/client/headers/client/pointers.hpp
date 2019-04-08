#pragma once
#ifndef INTERCEPT_NO_SQF
#include "../shared.hpp"
#include "client.hpp"
#include "../shared/functions.hpp"
#include "../shared/client_types.hpp"

using namespace intercept::types;
using namespace intercept::client;

namespace intercept {
    namespace client {

        class __sqf {
        public:
            static void __initialize();
#include "sqf_pointers_declaration.hpp"
            static binary_function binary__configaccessor__config__string__ret__config;
        };

        
    }
}
#endif
