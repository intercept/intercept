#include "chat.hpp"
#include "client\pointers.hpp"
#include "common_helpers.h"

namespace intercept {
    namespace sqf {
        namespace __helpers {
            float nular_function(intercept::rv_types::nular_function fnc_) {
                game_value ret_val = host::functions.invoke_raw_nular(fnc_);
                float output_val = ((game_data_number *)ret_val.data)->number;
                host::functions.free_value(&ret_val);
                return output_val;
            }

            bool nular_function_bool(intercept::rv_types::nular_function fnc_) {
                game_value ret_val = host::functions.invoke_raw_nular(fnc_);
                bool output_val = ((game_data_bool *)ret_val.data)->value;
                host::functions.free_value(&ret_val);
                return output_val;
            }

        }

        float random(float max_) {
            game_value rand_val = host::functions.invoke_raw_unary(client::__sqf::unary__random__scalar_nan__ret__scalar_nan, game_value_number(max_));
            float rand = ((game_data_number *)rand_val.data)->number;
            host::functions.free_value(&rand_val);
            return rand;
        }

        float save_zone_x() {
            return __helpers::nular_function(client::__sqf::nular__safezonex__ret__scalar);
        }
        float save_zone_y() {
            return __helpers::nular_function(client::__sqf::nular__safezoney__ret__scalar);
        }
        float save_zone_h() {
            return __helpers::nular_function(client::__sqf::nular__safezoneh__ret__scalar);
        }
        float save_zone_w() {
            return __helpers::nular_function(client::__sqf::nular__safezonew__ret__scalar);
        }
        float save_zone_x_abs() {
            return __helpers::nular_function(client::__sqf::nular__safezonexabs__ret__scalar);
        }
        float save_zone_w_abs() {
            return __helpers::nular_function(client::__sqf::nular__safezonewabs__ret__scalar);
        }

        bool shown_artillerycomputer() {
            return __helpers::nular_function_bool(client::__sqf::nular__shownartillerycomputer__ret__bool);
        }
        bool shown_chat() {
            return __helpers::nular_function_bool(client::__sqf::nular__shownchat__ret__bool);
        }
        bool shown_compass() {
            return __helpers::nular_function_bool(client::__sqf::nular__showncompass__ret__bool);
        }
        bool shown_curatorcompass() {
            return __helpers::nular_function_bool(client::__sqf::nular__showncuratorcompass__ret__bool);
        }
        bool shown_gps() {
            return __helpers::nular_function_bool(client::__sqf::nular__showngps__ret__bool);
        }
        bool shown_hud__ret__array() {
            return __helpers::nular_function_bool(client::__sqf::nular__shownhud__ret__array);
        }
        bool shown_map() {
            return __helpers::nular_function_bool(client::__sqf::nular__shownmap__ret__bool);
        }
        bool shown_pad() {
            return __helpers::nular_function_bool(client::__sqf::nular__shownpad__ret__bool);
        }
        bool shown_radio() {
            return __helpers::nular_function_bool(client::__sqf::nular__shownradio__ret__bool);
        }
        bool shown_uavfeed() {
            return __helpers::nular_function_bool(client::__sqf::nular__shownuavfeed__ret__bool);
        }
        bool shown_warrant() {
            return __helpers::nular_function_bool(client::__sqf::nular__shownwarrant__ret__bool);
        }
        bool shown_watch() {
            return __helpers::nular_function_bool(client::__sqf::nular__shownwatch__ret__bool);
        }

		bool visible_watch()
        {
			return __helpers::__retrieve_nular_bool(client::__sqf::nular__visiblewatch__ret__bool);
        }

		bool visible_map()
		{
			return __helpers::__retrieve_nular_bool(client::__sqf::nular__visiblemap__ret__bool);
		}

		bool visible_gps()
		{
			return __helpers::__retrieve_nular_bool(client::__sqf::nular__visiblegps__ret__bool);
		}

		bool visible_compass()
		{
			return __helpers::__retrieve_nular_bool(client::__sqf::nular__visiblecompass__ret__bool);
		}
    }
}
