#include "client\pointers.hpp"
#include "common_helpers.hpp"
#include "world.h"

namespace intercept {
	namespace sqf {
		namespace world {
			float world_size() {
				return sqf::__helpers::__retrieve_nular_number(client::__sqf::nular__worldsize__ret__scalar);
			}

			std::string world_name()
			{
				game_value game_world_name = host::functions.invoke_raw_nular(client::__sqf::nular__worldname__ret__string);
				std::string w_name = ((game_data_string *)game_world_name.data)->get_string();
				host::functions.free_value(&game_world_name);

				return w_name;
			}

			float wind_str() {
				return __helpers::__retrieve_nular_number(client::__sqf::nular__windstr__ret__scalar);
			}

			float wind_dir() {
				return __helpers::__retrieve_nular_number(client::__sqf::nular__winddir__ret__scalar);
			}

			vector3 wind() {
				return __helpers::__retrieve_nular_vector3(client::__sqf::nular__wind__ret__array);
			}

			float waves() {
				return __helpers::__retrieve_nular_number(client::__sqf::nular__waves__ret__scalar);
			}

			float time() {
				return __helpers::__retrieve_nular_number(client::__sqf::nular__time__ret__scalar);
			}

			float time_multiplier() {
				return __helpers::__retrieve_nular_number(client::__sqf::nular__timemultiplier__ret__scalar);
			}

			float date_to_number(game_date date_)
			{
				game_value_array<5> date_array({
					game_value_number(date_.year),
					game_value_number(date_.month),
					game_value_number(date_.day),
					game_value_number(date_.hour),
					game_value_number(date_.minute)
				});

				game_value date_number = host::functions.invoke_raw_unary(client::__sqf::unary__datetonumber__array__ret__scalar, date_array);
				float rv = ((game_data_number *)date_number.data)->number;

				host::functions.free_value(&date_number);
				return rv;
			}
		}

	}
}