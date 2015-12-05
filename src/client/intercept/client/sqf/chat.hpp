#pragma once
#include "shared.hpp"
#include "client\client.hpp"


using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        float random(float max_);
        void side_chat(object obj_, const std::string &message_);
    }
}
