#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\functions.hpp"
#include "client\sqf\sqf.hpp"

#define DLLEXPORT __declspec(dllexport)

namespace intercept {
    extern "C" {
        DLLEXPORT int  __cdecl api_version();
        DLLEXPORT void __cdecl pre_init();
        DLLEXPORT void __cdecl post_init();
        DLLEXPORT void __cdecl mission_end();
        DLLEXPORT void __cdecl on_frame();
    }
}