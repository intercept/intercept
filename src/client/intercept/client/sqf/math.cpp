#include "math.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        namespace __math {
            float random(float max_) {
                return game_value(host::functions.invoke_raw_unary(client::__sqf::unary__random__scalar_nan__ret__scalar_nan, max_));
            }

            float abs(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__abs__scalar_nan__ret__scalar_nan, value_);
            }

            float acos(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__acos__scalar_nan__ret__scalar_nan, value_);
            }

            float asin(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__asin__scalar_nan__ret__scalar_nan, value_);
            }

            float atan(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__atan__scalar_nan__ret__scalar_nan, value_);
            }

            float atg(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__atg__scalar_nan__ret__scalar_nan, value_);
            }

            float ceil(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__ceil__scalar_nan__ret__scalar_nan, value_);
            }

            float cos(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__cos__scalar_nan__ret__scalar_nan, value_);
            }

            float deg(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__deg__scalar_nan__ret__scalar_nan, value_);
            }

            float exp(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__exp__scalar_nan__ret__scalar_nan, value_);
            }

            float floor(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__floor__scalar_nan__ret__scalar_nan, value_);
            }

            float ln(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__ln__scalar_nan__ret__scalar_nan, value_);
            }

            float log(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__log__scalar_nan__ret__scalar_nan, value_);
            }

            float rad(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__rad__scalar_nan__ret__scalar_nan, value_);
            }

            float round(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__round__scalar_nan__ret__scalar_nan, value_);
            }

            float sin(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__sin__scalar_nan__ret__scalar_nan, value_);
            }

            float sqrt(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__sqrt__scalar_nan__ret__scalar_nan, value_);
            }

            float tan(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__tan__scalar_nan__ret__scalar_nan, value_);
            }

            float tg(float value_) {
                return __helpers::__number_unary_number(client::__sqf::unary__tg__scalar_nan__ret__scalar_nan, value_);
            }
        }
    }
}
