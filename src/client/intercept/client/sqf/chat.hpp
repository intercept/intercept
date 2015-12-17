#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"
#include "shared\types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
		namespace chat {
			namespace __helpers {
				void chat_message(binary_function fnc_, const object &obj_, const std::string &message_);
			}
			void side_chat(const object & obj_, const std::string &message_);
			void global_chat(const object & obj_, const std::string & message_);
			void group_chat(const object & obj_, const std::string & message_);
			void vehicle_chat(const object & obj_, const std::string & message_);
			void command_chat(const object & obj_, const std::string & message_);
			void system_chat(const std::string &message_);
			void custom_chat(const object & obj_, uint32_t channel_id_, const std::string &message_);
		}
    }
}
