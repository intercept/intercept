#pragma once
#include "shared.hpp"
#include "client\client.hpp"


using namespace intercept::client::types;

namespace intercept {
    namespace sqf {
        namespace __helpers {
            void chat_message(binary_function fnc_, object obj_, const std::string &message_);
        }
        void side_chat(object obj_, const std::string &message_);
        void global_chat(object obj_, const std::string & message_);
        void group_chat(object obj_, const std::string & message_);
        void vehicle_chat(object obj_, const std::string & message_);
        void command_chat(object obj_, const std::string & message_);
    }
}
