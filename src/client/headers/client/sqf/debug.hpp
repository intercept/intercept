/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)
@author Senfo (lpsenfo@gmail.com)

@brief Debug/Diagnose commands

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

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
        std::vector<script> diag_active_scripts();

        //diag
        void diag_capture_frame(float frame_);
        void diag_capture_frame_to_file(float frame_);
        void diag_capture_slow_frame(sqf_string_const_ref section_, float threshold_);
        void diag_code_performance(const code &code_, const game_value &arguments_, float cycles_);
        void diag_log(game_value text_);
        void diag_log_slow_frame(sqf_string_const_ref section_, float threshold_);

        void enable_diag_legend(bool value_);
        void halt();  //only in dev version - at least wiki says so
        void throw_exception(game_value exception_);
    }  // namespace sqf
}  // namespace intercept
