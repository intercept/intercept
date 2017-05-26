#include "client/pointers.hpp"
#include "common_helpers.hpp"
#include "world.hpp"

namespace intercept {
    namespace sqf {
        /* World */
        float world_size() {
            return sqf::__helpers::__retrieve_nular_number(__sqf::nular__worldsize__ret__scalar);
        }

        sqf_return_string world_name() {
            return host::functions.invoke_raw_nular(__sqf::nular__worldname__ret__string);
        }

        float wind_str() {
            return __helpers::__retrieve_nular_number(__sqf::nular__windstr__ret__scalar);
        }

        float wind_dir() {
            return __helpers::__retrieve_nular_number(__sqf::nular__winddir__ret__scalar);
        }
        void set_wind(float x_, float y_) {
            game_value params({
                x_,
                y_
            });

            host::functions.invoke_raw_unary(__sqf::unary__setwind__array__ret__nothing, params);
        }

        void set_wind(float x_, float y_, bool force_) {
            game_value params({
                x_,
                y_,
                force_
            });

            host::functions.invoke_raw_unary(__sqf::unary__setwind__array__ret__nothing, params);
        }
        vector3 wind() {
            return __helpers::__retrieve_nular_vector3(__sqf::nular__wind__ret__array);
        }

        float gusts() {
            return __helpers::__retrieve_nular_number(__sqf::nular__gusts__ret__scalar);
        }

        float humidity() {
            return __helpers::__retrieve_nular_number(__sqf::nular__humidity__ret__scalar);
        }

        float waves() {
            return __helpers::__retrieve_nular_number(__sqf::nular__waves__ret__scalar);
        }

        float lightnings() {
            return __helpers::__retrieve_nular_number(__sqf::nular__lightnings__ret__scalar);
        }

        float moon_intensity() {
            return __helpers::__retrieve_nular_number(__sqf::nular__moonintensity__ret__scalar);
        }

        float next_weather_change() {
            return __helpers::__retrieve_nular_number(__sqf::nular__nextweatherchange__ret__scalar);
        }

        float overcast() {
            return __helpers::__retrieve_nular_number(__sqf::nular__overcast__ret__scalar);
        }

        float overcast_forecast() {
            return __helpers::__retrieve_nular_number(__sqf::nular__overcastforecast__ret__scalar);
        }

        float rain() {
            return __helpers::__retrieve_nular_number(__sqf::nular__rain__ret__scalar);
        }

        float rainbow() {
            return __helpers::__retrieve_nular_number(__sqf::nular__rainbow__ret__scalar);
        }

        float sun_or_moon() {
            return __helpers::__retrieve_nular_number(__sqf::nular__sunormoon__ret__scalar);
        }

        bool fog() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__fog__ret__scalar);
        }

        float fog_forecast() {
            return __helpers::__retrieve_nular_number(__sqf::nular__fogforecast__ret__scalar);
        }

        float time() {
            return __helpers::__retrieve_nular_number(__sqf::nular__time__ret__scalar);
        }

        float time_multiplier() {
            return __helpers::__retrieve_nular_number(__sqf::nular__timemultiplier__ret__scalar);
        }

        float date_to_number(int year_, int month_, int day_, int hour_, float minute_) {
            game_value date({
                static_cast<float>(year_),
                static_cast<float>(month_),
                static_cast<float>(day_),
                static_cast<float>(hour_),
                minute_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__datetonumber__array__ret__scalar, date);
        }

        rv_date number_to_date(int year_, float time_) {
            game_value params({
                static_cast<float>(year_),
                time_
            });

            return rv_date::from_vector(__helpers::__convert_to_numbers_vector(host::functions.invoke_raw_unary(__sqf::unary__numbertodate__array__ret__array, params)));
        }
        rv_date date() {
            return rv_date::from_vector(__helpers::__convert_to_numbers_vector(host::functions.invoke_raw_nular(__sqf::nular__date__ret__array)));
        }
        rv_date mission_start() {
            return rv_date::from_vector(__helpers::__convert_to_numbers_vector(host::functions.invoke_raw_nular(__sqf::nular__missionstart__ret__array)));
        }

        rv_fog_parameters fog_params() {
            return rv_fog_parameters::from_vector(__helpers::__convert_to_numbers_vector(host::functions.invoke_raw_nular(__sqf::nular__fogparams__ret__array)));
        }

        rv_rendering_distances get_object_view_distance() {
            return rv_rendering_distances::from_vector(__helpers::__convert_to_numbers_vector(host::functions.invoke_raw_nular(__sqf::nular__getobjectviewdistance__ret__array)));
        }
        void set_date(int year_, int month_, int day_, int hour_, float minute_) {
            game_value date({
                static_cast<float>(year_),
                static_cast<float>(month_),
                static_cast<float>(day_),
                static_cast<float>(hour_),
                minute_
            });

            host::functions.invoke_raw_unary(__sqf::unary__setdate__array__ret__nothing, date);
        }

        std::vector<object> entities(sqf_string_list_const_ref typesinclude_, sqf_string_list_const_ref typesexclude_, bool includeCrews_, bool excludeDead_) {
            auto_array<game_value> typesinclude(typesinclude_.begin(), typesinclude_.end());
            auto_array<game_value> typesexclude(typesexclude_.begin(), typesexclude_.end());

            game_value params({
                std::move(typesinclude),
                std::move(typesexclude),
                includeCrews_,
                excludeDead_
            });

            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__entities__array__ret__array, params));
        }

        void set_horizon_parallax_coef(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__sethorizonparallaxcoef__scalar__ret__nothing, value_);
        }

        void set_detail_map_blend_pars(float full_detail_, float no_detail_) {
            game_value params({
                full_detail_,
                no_detail_
            });

            host::functions.invoke_raw_unary(__sqf::unary__setdetailmapblendpars__array__ret__nothing, params);
        }

        void simul_cloud_density(const vector3& pos_) {
            host::functions.invoke_raw_unary(__sqf::unary__simulclouddensity__array__ret__scalar, pos_);
        }

        void simul_cloud_occlusion(const vector3& pos1_, const vector3& pos2_) {
            game_value params({
                pos1_,
                pos2_
            });

            host::functions.invoke_raw_unary(__sqf::unary__simulcloudocclusion__array__ret__scalar, params);
        }

        bool simul_in_clouds(const vector3& pos_) {
            return host::functions.invoke_raw_unary(__sqf::unary__simulinclouds__array__ret__bool, pos_);
        }

        void set_fog(float time_, float fog_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfog__scalar__scalar_array__ret__nothing, time_, fog_);
        }

        void set_fog(float time_, float fog_value_, float fog_decay_, float fog_base_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfog__scalar__scalar_array__ret__nothing, time_, { fog_value_ ,fog_decay_, fog_base_ });
        }

        void set_gusts(float time_, float gusts_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setgusts__scalar__scalar__ret__nothing, time_, gusts_value_);
        }

        void set_rain(float time_, float rain_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setrain__scalar__scalar__ret__nothing, time_, rain_value_);
        }

        void set_rainbow(float time_, float rainbow_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setrainbow__scalar__scalar__ret__nothing, time_, rainbow_value_);
        }

        void set_overcast(float time_, float overcast_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setovercast__scalar__scalar__ret__nothing, time_, overcast_value_);
        }

        void set_wind_dir(float time_, float wind_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwinddir__scalar__scalar__ret__nothing, time_, wind_value_);
        }

        void set_wind_force(float time_, float force_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwindforce__scalar__scalar__ret__nothing, time_, force_value_);
        }

        void set_wind_str(float time_, float strength_value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setwindstr__scalar__scalar__ret__nothing, time_, strength_value_);
        }

        void set_acc_time(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setacctime__scalar__ret__nothing, value_);
        }
        
        void set_object_view_distance(float distance_) {
            __helpers::__empty_unary_number(__sqf::unary__setobjectviewdistance__scalar__ret__nothing, distance_);
        }

        void set_object_view_distance(float object_distance_, float shadow_distance_) {
            game_value params({
                object_distance_,
                shadow_distance_
            });

            host::functions.invoke_raw_unary(__sqf::unary__setobjectviewdistance__array__ret__nothing, params);
        }

        void set_shadow_distance(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setshadowdistance__scalar__ret__nothing, value_);
        }

        void set_simul_weather_layers(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setsimulweatherlayers__scalar__ret__nothing, value_);
        }

        void set_terrain_grid(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setterraingrid__scalar__ret__nothing, value_);
        }

        void set_time_multiplier(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__settimemultiplier__scalar__ret__nothing, value_);
        }

        void set_view_distance(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__setviewdistance__scalar__ret__nothing, value_);
        }

        void skip_time(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__skiptime__scalar__ret__nothing, value_);
        }

        void enable_environment(bool ambient_life_, bool ambient_sound_) {
            host::functions.invoke_raw_unary(__sqf::unary__enableenvironment__bool_array__ret__nothing, { ambient_life_, ambient_sound_ });
        }

        void enable_sat_normal_on_detail(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__enablesatnormalondetail__bool__ret__nothing, value_);
        }

        float acc_time() {
            return __helpers::__retrieve_nular_number(__sqf::nular__acctime__ret__scalar);
        }

        float daytime() {
            return __helpers::__retrieve_nular_number(__sqf::nular__daytime__ret__scalar);
        }

        void force_weather_change() {
            __helpers::__empty_nular(__sqf::nular__forceweatherchange__ret__nothing);
        }

        float get_shadow_distance() {
            return __helpers::__retrieve_nular_number(__sqf::nular__getshadowdistance__ret__scalar);
        }

        void init_ambient_life() {
            __helpers::__empty_nular(__sqf::nular__initambientlife__ret__nothing);
        }

        void simul_weather_sync() {
            __helpers::__empty_nular(__sqf::nular__simulweathersync__ret__nothing);
        }

        std::pair<bool, bool> environment_enabled() {
            game_value res = host::functions.invoke_raw_nular(__sqf::nular__environmentenabled__ret__array);

            return std::pair<bool, bool>({ res[0], res[1] });
        }
    }
}