#pragma once

using namespace intercept::rv_types;
using namespace intercept::client;

extern intercept::client_functions functions;

namespace intercept {
    namespace client {

        namespace __sqf {
#include "sqf_pointers.hpp"
        }

        void __initialize()
        {
#include "sqf_assignments.hpp"
        }
    }
}