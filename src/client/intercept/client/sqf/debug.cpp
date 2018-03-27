#include "debug.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        float diag_fps() {
            return __helpers::__retrieve_nular_number(__sqf::nular__diag_fps__ret__scalar);
        }
        float diag_fpsmin() {
            return __helpers::__retrieve_nular_number(__sqf::nular__diag_fpsmin__ret__scalar);
        }
        float diag_frameno() {
            return __helpers::__retrieve_nular_number(__sqf::nular__diag_frameno__ret__scalar);
        }
        float diag_ticktime() {
            return __helpers::__retrieve_nular_number(__sqf::nular__diag_ticktime__ret__scalar);
        }
        std::vector<script> diag_active_mission_fsms() {
            game_value ret = host::functions.invoke_raw_nular(__sqf::nular__diag_activemissionfsms__ret__array);
            return __helpers::__convert_to_vector<script>(ret);
        }

        std::vector<script> diag_active_sqf_scripts() {
            game_value ret = host::functions.invoke_raw_nular(__sqf::nular__diag_activesqfscripts__ret__array);
            return __helpers::__convert_to_vector<script>(ret);
        }

        std::vector<script> diag_active_sqs_scripts() {
            game_value ret = host::functions.invoke_raw_nular(__sqf::nular__diag_activesqsscripts__ret__array);
            return __helpers::__convert_to_vector<script>(ret);
        }

        std::vector<script> diag_active_scripts() {
            return __helpers::__convert_to_vector<script>(host::functions.invoke_raw_nular(__sqf::nular__diag_activescripts__ret__array));
        }

        void diag_capture_frame(float frame_) {
            if (!__sqf::unary__diag_captureframe__scalar__ret__nothing) return;
            host::functions.invoke_raw_unary(__sqf::unary__diag_captureframe__scalar__ret__nothing, frame_);
        }

        void diag_capture_frame_to_file(float frame_) {
            if (!__sqf::unary__diag_captureframetofile__scalar__ret__nothing) return;
            host::functions.invoke_raw_unary(__sqf::unary__diag_captureframetofile__scalar__ret__nothing, frame_);
        }

        void diag_capture_slow_frame(sqf_string_const_ref section_, float threshold_) {
            if (!__sqf::unary__diag_captureslowframe__array__ret__nothing) return;
            game_value params({section_,
                               threshold_});

            host::functions.invoke_raw_unary(__sqf::unary__diag_captureslowframe__array__ret__nothing, params);
        }

        void diag_code_performance(const code &code_, const game_value &arguments_, float cycles_) {
            game_value params({code_,
                               arguments_,
                               cycles_});

            host::functions.invoke_raw_unary(__sqf::unary__diag_codeperformance__array__ret__array, params);
        }

        void diag_log(game_value text_) {
            host::functions.invoke_raw_unary(client::__sqf::unary__diag_log__any__ret__nothing, text_);
        }
        void diag_log_slow_frame(sqf_string_const_ref section_, float threshold_) {
            if (!__sqf::unary__diag_logslowframe__array__ret__nothing) return;
            game_value params({section_,
                               threshold_});

            host::functions.invoke_raw_unary(__sqf::unary__diag_logslowframe__array__ret__nothing, params);
        }

        void enable_diag_legend(bool value_) {
            if (!__sqf::unary__enablediaglegend__bool__ret__nothing) return;
            __helpers::__empty_unary_bool(__sqf::unary__enablediaglegend__bool__ret__nothing, value_);
        }
        void halt() {
            __helpers::__empty_nular(__sqf::nular__halt__ret__nothing);
        }
        void throw_exception(game_value exception_) {
            host::functions.invoke_raw_unary(__sqf::unary__throw__any__ret__nothing, exception_);
        }
    }  // namespace sqf
}  // namespace intercept
