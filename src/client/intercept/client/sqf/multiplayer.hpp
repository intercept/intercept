/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Multiplayer commands.

Check the locality and other multiplayer related facets of objects and the environment.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
			bool local(const object &value_);
			bool local(const group &value_);
			bool is_server();
			bool is_multiplayer();
			bool is_dedicated();
			bool did_jip();
    }
}
