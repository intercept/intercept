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

        std::vector<float> diag_active_scripts() {
            return __helpers::__convert_to_vector<float>(host::functions.invoke_raw_nular(__sqf::nular__diag_activescripts__ret__array));
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

        void diag_enable(debug_toggles mode_, bool enable_) {
            game_value mode;
            switch (mode_) {
                case debug_toggles::AIAiming: mode = "AIAiming"sv; break;
                case debug_toggles::AIBrain: mode = "AIBrain"sv; break;
                case debug_toggles::AIDynamicError: mode = "AIDynamicError"sv; break;
                case debug_toggles::AISkill: mode = "AISkill"sv; break;
                case debug_toggles::AISuppression: mode = "AISuppression"sv; break;
                case debug_toggles::AIDriving: mode = "AIDriving"sv; break;
                case debug_toggles::DynSimEntities: mode = "DynSimEntities"sv; break;
                case debug_toggles::DynSimGrid: mode = "DynSimGrid"sv; break;
                case debug_toggles::DynSimGroups: mode = "DynSimGroups"sv; break;
                case debug_toggles::Animation: mode = "Animation"sv; break;
                case debug_toggles::AnimSrcTarget: mode = "AnimSrcTarget"sv; break;
                case debug_toggles::AnimSrcUnit: mode = "AnimSrcUnit"sv; break;
                case debug_toggles::EPEVehicle: mode = "EPEVehicle"sv; break;
                case debug_toggles::EPEForce: mode = "EPEForce"sv; break;
                case debug_toggles::Force: mode = "Force"sv; break;
                case debug_toggles::Suspension: mode = "Suspension"sv; break;
                case debug_toggles::HitPoints: mode = "HitPoints"sv; break;
                case debug_toggles::Mines: mode = "Mines"sv; break;
                case debug_toggles::Particles: mode = "Particles"sv; break;
                case debug_toggles::ParticleNames: mode = "ParticleNames"sv; break;
                case debug_toggles::Shots: mode = "Shots"sv; break;
                case debug_toggles::SurfaceUnder: mode = "SurfaceUnder"sv; break;
                case debug_toggles::CursorTargetObject: mode = "CursorTargetObject"sv; break;
                default: return;
            }
            host::functions.invoke_raw_binary(__sqf::binary__diag_enable__string__bool__ret__nothing, std::move(mode), enable_);
        }

        auto_array<game_value> diag_all_mission_eventhandlers() {
            return host::functions.invoke_raw_nular(__sqf::nular__diag_allmissioneventhandlers__ret__array).to_array();
        }

        float diag_delta_time() {
            return host::functions.invoke_raw_nular(__sqf::nular__diag_deltatime__ret__scalar);
        }

        auto_array<game_value> diag_dump_terrain_synth() {
            return host::functions.invoke_raw_nular(__sqf::nular__diag_dumpterrainsynth__ret__array).to_array();
        }

        void diag_reset_fsm() {
            host::functions.invoke_raw_nular(__sqf::nular__diag_resetfsm__ret__nothing);
        }

        void diag_reset_shapes() {
            host::functions.invoke_raw_nular(__sqf::nular__diag_resetshapes__ret__nothing);
        }

        void diag_draw_mode(debug_draw_modes mode_) {
            game_value draw_mode;
            switch (mode_) {
                case intercept::sqf::debug_draw_modes::Normal:
                    draw_mode = "Normal"sv;
                    break;
                case intercept::sqf::debug_draw_modes::Roadway:
                    draw_mode = "Roadway"sv;
                    break;
                case intercept::sqf::debug_draw_modes::Geometry:
                    draw_mode = "Geometry"sv;
                    break;
                case intercept::sqf::debug_draw_modes::ViewGeometry:
                    draw_mode = "ViewGeometry"sv;
                    break;
                case intercept::sqf::debug_draw_modes::FireGeometry:
                    draw_mode = "FireGeometry"sv;
                    break;
                case intercept::sqf::debug_draw_modes::Paths:
                    draw_mode = "Paths"sv;
                    break;
                case intercept::sqf::debug_draw_modes::ShadowVolume:
                    draw_mode = "ShadowVolume"sv;
                    break;
                case intercept::sqf::debug_draw_modes::ShadowBuffer:
                    draw_mode = "ShadowBuffer"sv;
                    break;
                case intercept::sqf::debug_draw_modes::Buoyancy:
                    draw_mode = "Buoyancy"sv;
                    break;
                default:
                    return;
            }
            host::functions.invoke_raw_unary(__sqf::unary__diag_drawmode__string__ret__nothing, std::move(draw_mode));
        }

        vector2 diag_get_terrain_segment_offset(const vector2& pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__diag_getterrainsegmentoffset__array__ret__array, pos_);
        }

        void diag_light_new_load(sqf_string_const_ref path_) {
            host::functions.invoke_raw_unary(__sqf::unary__diag_lightnewload__string__ret__nothing, path_);
        }

        sqf_return_string_list diag_list(sqf_string_const_ref name_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__diag_list__string__ret__array, name_));
        }

        sqf_return_string_list diag_localized(sqf_string_const_ref stringtable_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__diag_localized__string__ret__array, stringtable_));
        }

        void diag_set_light_new(sqf_string_const_ref str_config_) {
            host::functions.invoke_raw_unary(__sqf::unary__diag_setlightnew__string__ret__nothing, str_config_);
        }

        void diag_toggle(debug_toggles mode_) {
            game_value mode;
            switch (mode_) {
                case debug_toggles::AIAiming: mode = "AIAiming"sv; break;
                case debug_toggles::AIBrain: mode = "AIBrain"sv; break;
                case debug_toggles::AIDynamicError: mode = "AIDynamicError"sv; break;
                case debug_toggles::AISkill: mode = "AISkill"sv; break;
                case debug_toggles::AISuppression: mode = "AISuppression"sv; break;
                case debug_toggles::AIDriving: mode = "AIDriving"sv; break;
                case debug_toggles::DynSimEntities: mode = "DynSimEntities"sv; break;
                case debug_toggles::DynSimGrid: mode = "DynSimGrid"sv; break;
                case debug_toggles::DynSimGroups: mode = "DynSimGroups"sv; break;
                case debug_toggles::Animation: mode = "Animation"sv; break;
                case debug_toggles::AnimSrcTarget: mode = "AnimSrcTarget"sv; break;
                case debug_toggles::AnimSrcUnit: mode = "AnimSrcUnit"sv; break;
                case debug_toggles::EPEVehicle: mode = "EPEVehicle"sv; break;
                case debug_toggles::EPEForce: mode = "EPEForce"sv; break;
                case debug_toggles::Force: mode = "Force"sv; break;
                case debug_toggles::Suspension: mode = "Suspension"sv; break;
                case debug_toggles::HitPoints: mode = "HitPoints"sv; break;
                case debug_toggles::Mines: mode = "Mines"sv; break;
                case debug_toggles::Particles: mode = "Particles"sv; break;
                case debug_toggles::ParticleNames: mode = "ParticleNames"sv; break;
                case debug_toggles::Shots: mode = "Shots"sv; break;
                case debug_toggles::SurfaceUnder: mode = "SurfaceUnder"sv; break;
                case debug_toggles::CursorTargetObject: mode = "CursorTargetObject"sv; break;
                default: return;
            }

            host::functions.invoke_raw_unary(__sqf::unary__diag_toggle__string__ret__nothing, std::move(mode));
        }

        bool diag_enabled(sqf_string_const_ref mode_) {
            return host::functions.invoke_raw_unary(__sqf::unary__diag_enabled__string__ret__bool, mode_);
        }


    }  // namespace sqf
}  // namespace intercept
