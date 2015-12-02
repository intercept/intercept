#pragma once
using namespace intercept::rv_types;
using namespace intercept::client;

namespace intercept {
    namespace client {
        intercept::client_functions functions;

        namespace __sqf {
#include "sqf_pointers.hpp"
        }

        void __initialize()
        {
#include "sqf_assignments.hpp"
        }
    }
}