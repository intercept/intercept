/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Misc function wrappers.

This is basically stuff that has not been categorized yet. Compared to uncategorized.hpp,
which is functions that lack a clear category.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"
#include<vector>

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        float diag_fps();
        float diag_fpsmin();
        float diag_frameno();
        float diag_ticktime();

        std::vector<script> diag_active_mission_fsms();
        std::vector<script> diag_active_sqf_scripts();
        std::vector<script> diag_active_sqs_scripts();

    }
}
