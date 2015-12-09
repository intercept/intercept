#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
		namespace multiplayer {
			bool local(object value_);
			bool local(group value_);
			bool is_server();
			bool is_multiplayer();
			bool is_dedicated();
			bool did_jip();
		}
    }
}
