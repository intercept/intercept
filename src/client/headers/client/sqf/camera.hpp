/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)

@brief Camera related Function wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {

        /* potential namespace: camera */
        void add_cam_shake(float power_, float duration_, float frequency_);
        void reset_cam_shake();
        void enable_cam_shake(bool value_);

        /* potential namespace: camera */
        bool cam_committed(const object &camera_);
        void cam_destroy(const object &camera_);
        bool cam_preloaded(const object &camera_);
        object cam_target(const object &camera_);
        void cam_use_nvg(bool use_nvg_);
        void camera_effect_enable_hud(bool enable_hud_);
        float camera_interest(const object &entity_);
        void cam_constuction_set_params(const object &camera_, const vector3 &position_, float radius, float max_above_land_);
        object cam_create(sqf_string_const_ref type_, const vector3 &position_);
        void camera_effect(const object &camera_, sqf_string_const_ref name_, sqf_string_const_ref position_);
        void camera_effect(const object &camera_, sqf_string_const_ref name_, sqf_string_const_ref position_, sqf_string_const_ref rtt_);
        void cam_prepare_focus(const object &camera_, float distance_, float blur_);
        void cam_prepare_fov_range(const object &camera_, float min_, float max_);
        void cam_prepare_pos(const object &camera_, const vector3 &position_);
        void cam_prepare_rel_pos(const object &camera_, const vector3 &relative_position_);
        void cam_prepare_target(const object &camera_, const object &target_);
        void cam_prepare_target(const object &camera_, const vector3 &target_);
        // Broken command cam_set_dir
        void cam_set_focus(const object &camera_, float distance_, float blur_);
        void cam_set_fov_range(const object &camera_, float min_, float max_);
        void cam_set_pos(const object &camera_, const vector3 &position_);
        void cam_set_relative_pos(const object &camera_, const vector3 &relative_position_);
        void cam_set_target(const object &camera_, const object &target_);
        void cam_set_target(const object &camera_, const vector3 &target_);

        void cam_command(const object &value0_, sqf_string_const_ref value1_);
        void cam_commit(const object &value0_, float value1_);
        void cam_commit_prepared(const object &value0_, float value1_);
        void cam_preload(const object &value0_, float value1_);
        void cam_prepare_bank(const object &value0_, float value1_);
        void cam_prepare_dir(const object &value0_, float value1_);
        void cam_prepare_dive(const object &value0_, float value1_);
        void cam_prepare_fov(const object &value0_, float value1_);
        void cam_set_bank(const object &value0_, float value1_);
        void cam_set_dive(const object &value0_, float value1_);
        void cam_set_fov(const object &value0_, float value1_);

        enum class thermal_modes {
            white_hot = 0,
            black_hot = 1,
            lightgreen_hot = 2,        ///< Light Green Hot / Darker Green cold
            black_hot_green_cold = 3,  ///< Black Hot / Darker Green cold
            red_hot = 4,               ///< Light Red Hot / Darker Red Cold
            black_hot_red_cold = 5,    ///< Black Hot / Darker Red Cold
            white_hot_red_cold = 6,    ///< White Hot.Darker Red Cold
            thermal = 7                ///< Shade of Red and Green, Bodies are white
        };

        void set_cam_use_ti(thermal_modes mode_, bool value1_);

        void set_aperture(float value_);
        void set_aperture_new(float min_, float std_, float max_, float std_lum_);
        void set_cam_shake_def_params(float power_, float duration_, float freq_, float min_speed_, float min_mass_, float caliber_coef_hit_, float vehicle_coef_);
        void set_cam_shake_params(float pos_coef_, float vert_coef_, float horz_coef_, float bank_coef_, bool interpolate_);

        bool preload_camera(const vector3 &pos_);

        void set_default_camera(const vector3 &pos_, const vector3 &dir_);

        vector3 get_camera_view_direction(const object &obj_);
        void switch_camera(const object &value0_, sqf_string_const_ref value1_);
        void set_camera_interest(const object &value0_, float value1_);
        sqf_return_string camera_view();

        //postprocessing effects

        struct rv_pp_effect {
            std::string name;
            float priority;

            operator game_value() {
                return game_value(std::vector<game_value>({name,
                                                           priority}));
            }

            operator game_value() const {
                return game_value(std::vector<game_value>({name,
                                                           priority}));
            }
        };

        float pp_effect_create(sqf_string_const_ref name_, const float &priority_);
        std::vector<float> pp_effect_create(const std::vector<rv_pp_effect> &effects_);

        bool pp_effect_committed(sqf_string_const_ref value_);
        bool pp_effect_committed(float value_);
        void pp_effect_destroy(float value_);
        bool pp_effect_enabled(float value_);

        void pp_effect_commit(float value0_, sqf_string_const_ref value1_);
        void pp_effect_enable(bool value0_, sqf_string_const_ref value1_);
        void pp_effect_enable(float value0_, bool value1_);
        void pp_effect_force_in_nvg(float value0_, bool value1_);

        void pp_effect_destroy(std::vector<float> effect_handles_);
        //#TODO: Replace &settings_ with the right pp_effect_parameters
        void pp_effect_adjust(std::variant<sqf_string_const_ref_wrapper, std::reference_wrapper<int>> effect_, const game_value &settings_);
        void pp_effect_commit(std::variant<std::reference_wrapper<const std::vector<int>>, std::reference_wrapper<int>> effect_, const float &duration_);
        void pp_effect_enable(const std::vector<int> &effets_, bool enable_);

        struct rv_camera_target {
            bool is_tracking;
            vector3 target_position;
            object target_object;
        };

        vector3 get_pilot_camera_direction(const object &object_);
        vector3 get_pilot_camera_position(const object &object_);
        vector3 get_pilot_camera_rotation(const object &object_);
        rv_camera_target get_pilot_camera_target(const object &object_);
        bool has_pilot_camera(const object &object_);

    }  // namespace sqf
}  // namespace intercept
