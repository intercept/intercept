#include "chat.hpp"
#include "client\pointers.hpp"

namespace intercept {
    namespace sqf {
        namespace __helpers {
            float nular_function(intercept::rv_types::nular_function fnc_) {
                game_value ret_val = host::functions.invoke_raw_nular(fnc_);
                float output_val = ((game_data_number *)ret_val.data)->number;
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
    }
}
