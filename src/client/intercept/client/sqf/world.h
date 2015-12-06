#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;
namespace intercept {
	namespace sqf {
		float world_size();
		std::string world_name();
		float wind_str();
		float wind_dir();

		vector3 wind();
		float waves();
		void set_waves(float lerp_time_, float val_); // @TODO

		float time();
		float time_multiplier();
		

	}
}