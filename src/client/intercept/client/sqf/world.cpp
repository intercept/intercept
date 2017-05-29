#include "client\pointers.hpp"
#include "common_helpers.hpp"
#include "world.hpp"

namespace intercept {
    namespace sqf {
        /* World */
        float world_size() {
            return sqf::__helpers::__retrieve_nular_number(client::__sqf::nular__worldsize__ret__scalar);
        }

        std::string world_name() {
            return game_value(host::functions.invoke_raw_nular(client::__sqf::nular__worldname__ret__string));
        }

        float wind_str() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__windstr__ret__scalar);
        }

        float wind_dir() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__winddir__ret__scalar);
        }

        void set_wind(float x_, float y_) {
            std::vector<game_value> params{
                x_,
                y_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__setwind__array__ret__nothing, params);
        }
        void set_wind(float x_, float y_, bool force_) {
            std::vector<game_value> params{
                x_,
                y_,
                force_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__setwind__array__ret__nothing, params);
        }
        vector3 wind() {
            return __helpers::__retrieve_nular_vector3(client::__sqf::nular__wind__ret__array);
        }

        float gusts() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__gusts__ret__scalar);
        }

        float humidity() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__humidity__ret__scalar);
        }

        float waves() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__waves__ret__scalar);
        }

        float lightnings() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__lightnings__ret__scalar);
        }

        float moon_intensity() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__moonintensity__ret__scalar);
        }

        float next_weather_change() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__nextweatherchange__ret__scalar);
        }

        float overcast() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__overcast__ret__scalar);
        }

        float overcast_forecast() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__overcastforecast__ret__scalar);
        }

        float rain() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__rain__ret__scalar);
        }

        float rainbow() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__rainbow__ret__scalar);
        }

        float sun_or_moon() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__sunormoon__ret__scalar);
        }

        bool fog() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__fog__ret__scalar);
        }

        float fog_forecast() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__fogforecast__ret__scalar);
        }

        void set_fog(float time_, float fog_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__setfog__scalar__scalar_array__ret__nothing, time_, fog_);
        }
        void set_fog(float time_, float fog_, float fog_decay_, float fog_base_) {
            std::vector<game_value> params{
                fog_,
                fog_decay_,
                fog_base_
            };

            host::functions.invoke_raw_binary(client::__sqf::binary__setfog__scalar__scalar_array__ret__nothing, time_, params);
        }

        float time() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__time__ret__scalar);
        }

        float time_multiplier() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__timemultiplier__ret__scalar);
        }

        float date_to_number(int year_, int month_, int day_, int hour_, float minute_) {
            std::vector<game_value> date{
                (float) year_,
                (float) month_,
                (float) day_,
                (float) hour_,
                minute_
            };

            return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__datetonumber__array__ret__scalar, date));
        }

        rv_date number_to_date(int year_, float time_) {
            std::vector<game_value> params{
                (float) year_,
                time_
            };

            return rv_date::from_vector(__helpers::__convert_to_numbers_vector(host::functions.invoke_raw_unary(client::__sqf::unary__numbertodate__array__ret__array, params)));
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
            std::vector<game_value> date{
                (float) year_,
                (float) month_,
                (float) day_,
                (float) hour_,
                minute_
            };

            host::functions.invoke_raw_unary(client::__sqf::unary__setdate__array__ret__nothing, date);
        }
    }
}
