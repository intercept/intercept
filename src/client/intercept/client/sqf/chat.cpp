#include "chat.hpp"
#include "client\pointers.hpp"
#include "common_helpers.hpp"

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
            game_value args({ ((float) channel_id_), message_ });
            host::functions.invoke_raw_binary(client::__sqf::binary__customchat__object__array__ret__nothing, obj_, args);
        }

        bool shown_chat() {
            return __helpers::__retrieve_nular_bool(client::__sqf::nular__shownchat__ret__bool);
        }

        void show_chat(bool value_) {
            __helpers::__empty_unary_bool(client::__sqf::unary__showchat__bool__ret__nothing, value_);
        }

        void enable_channel(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__enablechannel__scalar__bool__ret__nothing, value0_, value1_);
        }

        void radio_channel_set_call_sign(float value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__radiochannelsetcallsign__scalar__string__ret__nothing, value0_, value1_);
        }

        void radio_channel_set_label(float value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(client::__sqf::binary__radiochannelsetlabel__scalar__string__ret__nothing, value0_, value1_);
        }

        float radio_channel_create(const rv_color &color_, const std::string &label_, const std::string &callsign_, const std::vector<object> &units_) {
            std::vector<game_value> units; //#TODO remove temp std::vector
            for (auto unit : units_)
                units.push_back(game_value(unit));

            game_value params({
                color_,
                label_,
                callsign_,
                units
            });

            return host::functions.invoke_raw_unary(client::__sqf::unary__radiochannelcreate__array__ret__scalar, params);
        }

        float radio_channel_create(const rv_color &color_, const std::string &label_, const std::string &callsign_, const std::vector<object> &units_, bool quote_) {
            std::vector<game_value> units; //#TODO remove temp std::vector
            for (auto unit : units_)
                units.push_back(game_value(unit));

            game_value params({
                color_,
                label_,
                callsign_,
                units,
                quote_
            });

            return host::functions.invoke_raw_unary(client::__sqf::unary__radiochannelcreate__array__ret__scalar, params);
        }

        float current_channel() {
            return __helpers::__retrieve_nular_number(client::__sqf::nular__currentchannel__ret__scalar);
        }

        std::pair<bool, bool> channel_enabled(float channel_) {
            auto ret = host::functions.invoke_raw_unary(client::__sqf::unary__channelenabled__scalar__ret__array, channel_);
            return { ret[0],ret[1] };
        }

        float get_player_channel(const object &value_) {
            return __helpers::__number_unary_object(client::__sqf::unary__getplayerchannel__object__ret__scalar, value_);
        }

        bool set_current_channel(float value_) {
            return __helpers::__bool_unary_number(client::__sqf::unary__setcurrentchannel__scalar__ret__bool, value_);
        }
    }
}
