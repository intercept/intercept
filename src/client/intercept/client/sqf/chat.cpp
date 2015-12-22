#include "chat.hpp"
#include "client\pointers.hpp"

namespace intercept {
	namespace sqf {
		namespace __helpers {
			void chat_message(binary_function fnc_, const object & obj_, const std::string &message_) {
				host::functions.invoke_raw_binary(fnc_, obj_, message_);
			}
		}

		void side_chat(const object & obj_, const std::string &message_) {
			__helpers::chat_message(client::__sqf::binary__sidechat__object_array__string__ret__nothing, obj_, message_);
		}

		void global_chat(const object & obj_, const std::string &message_) {
			__helpers::chat_message(client::__sqf::binary__globalchat__object__string__ret__nothing, obj_, message_);
		}

		void group_chat(const object & obj_, const std::string &message_) {
			__helpers::chat_message(client::__sqf::binary__groupchat__object__string__ret__nothing, obj_, message_);
		}

		void vehicle_chat(const object & obj_, const std::string &message_) {
			__helpers::chat_message(client::__sqf::binary__vehiclechat__object__string__ret__nothing, obj_, message_);
		}

		void command_chat(const object & obj_, const std::string &message_) {
			__helpers::chat_message(client::__sqf::binary__commandchat__object_array__string__ret__nothing, obj_, message_);
		}

		void system_chat(const std::string &message_) {
			host::functions.invoke_raw_unary(client::__sqf::unary__systemchat__string__ret__nothing, message_);
		}

		void custom_chat(const object & obj_, uint32_t channel_id_, const std::string &message_) {
			game_value args = game_value({ ((float)channel_id_), message_ });
			host::functions.invoke_raw_binary(client::__sqf::binary__customchat__object__array__ret__nothing, obj_, args);
		}
    }
}
