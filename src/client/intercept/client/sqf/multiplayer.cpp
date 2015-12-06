#include "multiplayer.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
		namespace multiplayer {
			bool local(object value_) {
				return __helpers::__bool_unary_object(client::__sqf::unary__local__object__ret__bool, value_);
			}

			bool local(group value_) {
				game_value ret_value = host::functions.invoke_raw_unary(client::__sqf::unary__local__group__ret__bool, *value_);
				bool rv = ((game_data_bool *)ret_value.data)->value;
				host::functions.free_value(&ret_value);
				return rv;
			}

			bool is_server() {
				return __helpers::__retrieve_nular_bool(client::__sqf::nular__isserver__ret__bool);
			}

			bool is_multiplayer() {
				return __helpers::__retrieve_nular_bool(client::__sqf::nular__ismultiplayer__ret__bool);
			}

			bool is_dedicated() {
				return __helpers::__retrieve_nular_bool(client::__sqf::nular__isdedicated__ret__bool);
			}

			bool did_jip() {
				return __helpers::__retrieve_nular_bool(client::__sqf::nular__didjip__ret__bool);
			}
		}
    }
}
