#pragma once
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;
namespace intercept {
	namespace sqf {
		namespace __helpers
		{
			float __retrieve_nular_number(nular_function fnc_);
			vector3 __retrieve_nular_vector3(nular_function fnc_);
			bool __retrieve_nular_bool(nular_function fnc_);
		}
	}
}