#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;
namespace intercept {
	namespace sqf {

		struct game_date
		{
			float year;
			float month;
			float day;
			float hour;
			float minute;

			game_date(float year_, float month_, float day_, float hour_, float minute_)
			{
				year = year_;
				month = month_;
				day = day_;
				hour = hour_;
				minute = minute_;
			}

			static game_date from_vector(const std::vector<float> &date_vector_)
			{
				return game_date(date_vector_[0], date_vector_[1], date_vector_[2], date_vector_[3], date_vector_[4]);
			}

			std::vector<float> to_vector() const
			{
				std::vector<float> ret_val {year, month, day, hour, minute};
				return ret_val;
			}
		};

		namespace world {
			float world_size();
			std::string world_name();
			float wind_str();
			float wind_dir();

			vector3 wind();
			float waves();
			void set_waves(float lerp_time_, float val_); // TODO

			float time();
			float time_multiplier();

			float date_to_number(game_date date_);


		}
	}
}