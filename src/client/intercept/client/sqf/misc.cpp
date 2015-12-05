#include "chat.hpp"
#include "client\pointers.hpp"
#include "common_helpers.h"

namespace intercept {
    namespace sqf {

        float random(float max_) {
            game_value rand_val = host::functions.invoke_raw_unary(client::__sqf::unary__random__scalar_nan__ret__scalar_nan, game_value_number(max_));
            float rand = ((game_data_number *)rand_val.data)->number;
            host::functions.free_value(&rand_val);
            return rand;
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
