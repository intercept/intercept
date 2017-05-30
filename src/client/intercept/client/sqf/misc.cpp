#include "chat.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"
#include <memory>

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
            game_value input = host::functions.invoke_raw_nular(__sqf::nular__diag_activemissionfsms__ret__array);
            std::vector<script> output;
            for (uint32_t i = 0; i < input.size(); ++i) {
                output.push_back(script(input[i]));
            }
            return output;
        }

        std::vector<script> diag_active_sqf_scripts() {
            game_value input = host::functions.invoke_raw_nular(__sqf::nular__diag_activesqfscripts__ret__array);
            std::vector<script> output;
            for (uint32_t i = 0; i < input.size(); ++i) {
                output.push_back(script(input[i]));
            }
            return output;
        }

        std::vector<script> diag_active_sqs_scripts() {
            game_value input = host::functions.invoke_raw_nular(__sqf::nular__diag_activesqsscripts__ret__array);
            std::vector<script> output;
            for (uint32_t i = 0; i < input.size(); ++i) {
                output.push_back(script(input[i]));
            }
            return output;
        }
    }
}
