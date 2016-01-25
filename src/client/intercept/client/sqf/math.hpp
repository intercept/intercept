/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Math functions.

These are hidden, as they are useless when native math functions work faster.

Basically do not use any of these. They are only provided here for code completion.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        namespace __math {
            float random(float max_);
            float abs(float value_);
            float acos(float value_);
            float atan(float value_);
            float atg(float value_);
            float ceil(float value_);
            float cos(float value_);
            float exp(float value_);
            float floor(float value_);
            float ln(float value_);
            float log(float value_);
            float rad(float value_);
            float round(float value_);
            float sin(float value_);
            float sqrt(float value_);
            float tan(float value_);
            float tg(float value_);
            float asin(float value_);
            float deg(float value_);
        }
    }
}
