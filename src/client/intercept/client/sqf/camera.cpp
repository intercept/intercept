#include "chat.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"
#include "position.hpp"

namespace intercept {
    namespace sqf {
        /* potential namespace: camera */
        void add_cam_shake(float power_, float duration_, float frequency_) {
            std::vector<game_value> params{ power_, duration_, frequency_ };

            host::functions.invoke_raw_unary(client::__sqf::unary__addcamshake__array__ret__nothing, params);
        }
        void reset_cam_shake() {
            __helpers::__empty_nular(client::__sqf::nular__resetcamshake__ret__nothing);
        }

        void enable_cam_shake(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__enablecamshake__bool__ret__nothing, value_);
        }
        bool cam_committed(const object &camera_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__camcommitted__object__ret__bool, camera_);
        }

        void cam_destroy(const object &camera_) {
            __helpers::__empty_unary_object(client::__sqf::unary__camdestroy__object__ret__nothing, camera_);
        }

        bool cam_preloaded(const object &camera_) {
            return __helpers::__bool_unary_object(client::__sqf::unary__campreloaded__object__ret__bool, camera_);
        }

        object cam_target(const object &camera_) {
            return __helpers::__object_unary_object(client::__sqf::unary__camtarget__object__ret__object, camera_);
        }

        void cam_use_nvg(bool use_nvg_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__camusenvg__bool__ret__nothing, use_nvg_);
        }

        void camera_effect_enable_hud(bool enable_hud_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__cameraeffectenablehud__bool__ret__nothing, enable_hud_);
        }

        float camera_interest(const object &entity_) {
            return __helpers::__number_unary_object(client::__sqf::unary__camerainterest__object__ret__scalar, entity_);
        }

        void cam_constuction_set_params(const object &camera_, const vector3 & position_, float radius_, float max_above_land_) {
            std::vector<game_value> args{
                position_,
                radius_,
                max_above_land_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__camconstuctionsetparams__object__array__ret__nothing, camera_, args);
        }

        object cam_create(const std::string & type_, const vector3 & position_) {
            return host::functions.invoke_raw_binary(client::__sqf::binary__camcreate__string__array__ret__object, type_, position_);
        }

        void camera_effect(const object & camera_, const std::string & name_, const std::string & position_) {
            std::vector<game_value> args{
                name_,
                position_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__cameraeffect__object__array__ret__nothing, camera_, args);
        }

        void camera_effect(const object & camera_, const std::string & name_, const std::string & position_, const std::string & rtt_) {
            std::vector<game_value> args{
                name_,
                position_,
                rtt_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__cameraeffect__object__array__ret__nothing, camera_, args);
        }

        void cam_prepare_focus(const object & camera_, float distance_, float blur_) {
            std::vector<game_value> args{
                distance_,
                blur_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparefocus__object__array__ret__nothing, camera_, args);
        }

        void cam_prepare_fov_range(const object & camera_, float min_, float max_) {
            std::vector<game_value> args{
                min_,
                max_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparefovrange__object__array__ret__nothing, camera_, args);
        }

        void cam_prepare_pos(const object & camera_, const vector3 & position_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparepos__object__array__ret__nothing, camera_, position_);
        }

        void cam_prepare_rel_pos(const object & camera_, const vector3 & relative_position_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparerelpos__object__array__ret__nothing, camera_, relative_position_);
        }

        void cam_prepare_target(const object & camera_, const object & target_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparetarget__object__object__ret__nothing, camera_, target_);
        }

        void cam_prepare_target(const object & camera_, const vector3 & target_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparetarget__object__array__ret__nothing, camera_, target_);
        }

        void cam_set_focus(const object & camera_, float distance_, float blur_) {
            std::vector<game_value> args{
                distance_,
                blur_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetfocus__object__array__ret__nothing, camera_, args);
        }

        void cam_set_fov_range(const object & camera_, float min_, float max_) {
            std::vector<game_value> args{
                min_,
                max_
            };
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetfovrange__object__array__ret__nothing, camera_, args);
        }

        void cam_set_pos(const object & camera_, const vector3 & position_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetpos__object__array__ret__nothing, camera_, position_);
        }

        void cam_set_relative_pos(const object & camera_, const vector3 & relative_position_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetrelpos__object__array__ret__nothing, camera_, relative_position_);
        }

        void cam_set_target(const object & camera_, const object & target_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsettarget__object__object__ret__nothing, camera_, target_);
        }

        void cam_set_target(const object & camera_, const vector3 & target_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsettarget__object__array__ret__nothing, camera_, target_);
        }

        void cam_command(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camcommand__object__string__ret__nothing, value0_, value1_);
        }

        void cam_commit(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camcommit__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_commit_prepared(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camcommitprepared__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_preload(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreload__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_prepare_bank(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparebank__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_prepare_dir(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparedir__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_prepare_dive(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparedive__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_prepare_fov(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__campreparefov__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_set_bank(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetbank__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_set_dive(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetdive__object__scalar__ret__nothing, value0_, value1_);
        }

        void cam_set_fov(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__camsetfov__object__scalar__ret__nothing, value0_, value1_);
        }
        void set_cam_use_ti(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcamuseti__bool__scalar__ret__nothing, value0_, value1_);
        }
        void set_aperture(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__setaperture__scalar__ret__nothing, value_);
        }
        void set_aperture_new(float min_, float std_, float max_, float std_lum_) {
            std::vector<game_value> params{
                min_,
                std_,
                max_,
                std_lum_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__setaperturenew__array__ret__nothing, params);
        }

        void set_cam_shake_def_params(float power_, float duration_, float freq_, float min_speed_, float min_mass_, float caliber_coef_hit_, float vehicle_coef_) {
            std::vector<game_value> params{
                power_,
                duration_,
                freq_,
                min_speed_,
                min_mass_,
                caliber_coef_hit_,
                vehicle_coef_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__setcamshakedefparams__array__ret__nothing, params);
        }

        void set_cam_shake_params(float pos_coef_, float vert_coef_, float horz_coef_, float bank_coef_, bool interpolate_) {
            std::vector<game_value> params{
                pos_coef_,
                vert_coef_,
                horz_coef_,
                bank_coef_,
                interpolate_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__setcamshakeparams__array__ret__nothing, params);
        }
        bool preload_camera(const vector3 &pos_) {
            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__preloadcamera__array__ret__bool, pos_));
        }

        void set_default_camera(const vector3& pos_, const vector3& dir_) {
            std::vector<game_value> params{
                pos_,
                dir_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__setdefaultcamera__array__ret__nothing, params);
        }
        vector3 get_camera_view_direction(const object & obj_) {
            return __helpers::get_pos_obj(__sqf::unary__getcameraviewdirection__object__ret__array, obj_);
        }
        void switch_camera(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__switchcamera__object__string__ret__nothing, value0_, value1_);
        }
        void set_camera_interest(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setcamerainterest__object__scalar__ret__nothing, value0_, value1_);
        }
        std::string camera_view() {
            return __helpers::__retrieve_nular_string(client::__sqf::nular__cameraview__ret__string);
        }












        //post processing effects

        float pp_effect_create(const std::string& name_, const float& priority_) {
            std::vector<game_value> params{
                name_,
                priority_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__ppeffectcreate__array__ret__scalar_array, params));
        }

        std::vector<float> pp_effect_create(const std::vector<rv_pp_effect>& effects_) {
            std::vector<game_value> effects;
            for (rv_pp_effect item : effects_) {
                effects.push_back(game_value(item));
            }

            game_value ret = host::functions.invoke_raw_unary(client::__sqf::unary__ppeffectcreate__array__ret__scalar_array, effects);

            if (ret.length() == 0) {
                return {};
            } else {
                return __helpers::__convert_to_numbers_vector(ret);
            }
        }

        bool pp_effect_committed(const std::string &value_) {
            return __helpers::__bool_unary_string(client::__sqf::unary__ppeffectcommitted__string__ret__bool, value_);
        }

        bool pp_effect_committed(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__ppeffectcommitted__scalar__ret__bool, value_);
        }

        void pp_effect_destroy(float value_) {
            __helpers::__empty_unary_number(client::__sqf::unary__ppeffectdestroy__scalar__ret__nothing, value_);
        }

        bool pp_effect_enabled(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__ppeffectenabled__scalar__ret__bool, value_);
        }
        void pp_effect_commit(float value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ppeffectcommit__string__scalar__ret__nothing, value0_, value1_);
        }

        void pp_effect_enable(bool value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ppeffectenable__string__bool__ret__nothing, value0_, value1_);
        }

        void pp_effect_enable(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ppeffectenable__scalar__bool__ret__nothing, value0_, value1_);
        }

        void pp_effect_force_in_nvg(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__ppeffectforceinnvg__scalar__bool__ret__nothing, value0_, value1_);
        }
        void pp_effect_destroy(std::vector<float> effect_handles_) {
            std::vector<game_value> effect_handles;
            for (auto effect_handle : effect_handles_)
                effect_handles.push_back(game_value(effect_handle));

            host::functions.invoke_raw_unary(client::__sqf::unary__ppeffectdestroy__array__ret__nothing, effect_handles);
        }
    }
}
