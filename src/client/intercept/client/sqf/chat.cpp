#include "chat.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        namespace __helpers {
            void chat_message(binary_function fnc_, const object & obj_, const std::string &message_) {
                host::functions.invoke_raw_binary(fnc_, obj_, message_);
            }
        }

        void side_chat(const object & obj_, const std::string &message_) {
            __helpers::chat_message(__sqf::binary__sidechat__object_array__string__ret__nothing, obj_, message_);
        }

        void global_chat(const object & obj_, const std::string &message_) {
            __helpers::chat_message(__sqf::binary__globalchat__object__string__ret__nothing, obj_, message_);
        }

        void group_chat(const object & obj_, const std::string &message_) {
            __helpers::chat_message(__sqf::binary__groupchat__object__string__ret__nothing, obj_, message_);
        }

        void vehicle_chat(const object & obj_, const std::string &message_) {
            __helpers::chat_message(__sqf::binary__vehiclechat__object__string__ret__nothing, obj_, message_);
        }

        void command_chat(const object & obj_, const std::string &message_) {
            __helpers::chat_message(__sqf::binary__commandchat__object_array__string__ret__nothing, obj_, message_);
        }

        void system_chat(const std::string &message_) {
            host::functions.invoke_raw_unary(__sqf::unary__systemchat__string__ret__nothing, message_);
        }

        void custom_chat(const object & obj_, uint32_t channel_id_, const std::string &message_) {
            game_value args({ static_cast<float>( channel_id_), message_ });
            host::functions.invoke_raw_binary(__sqf::binary__customchat__object__array__ret__nothing, obj_, args);
        }

        bool shown_chat() {
            return __helpers::__retrieve_nular_bool(__sqf::nular__shownchat__ret__bool);
        }

        void show_chat(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__showchat__bool__ret__nothing, value_);
        }

        void enable_channel(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enablechannel__scalar__bool__ret__nothing, value0_, value1_);
        }

        void radio_channel_set_call_sign(float value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__radiochannelsetcallsign__scalar__string__ret__nothing, value0_, value1_);
        }

        void radio_channel_set_label(float value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__radiochannelsetlabel__scalar__string__ret__nothing, value0_, value1_);
        }

        float radio_channel_create(const rv_color &color_, const std::string &label_, const std::string &callsign_, const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            game_value params({
                color_,
                label_,
                callsign_,
                std::move(units)
            });

            return host::functions.invoke_raw_unary(__sqf::unary__radiochannelcreate__array__ret__scalar, params);
        }

        float radio_channel_create(const rv_color &color_, const std::string &label_, const std::string &callsign_, const std::vector<object> &units_, bool quote_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            game_value params({
                color_,
                label_,
                callsign_,
                std::move(units),
                quote_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__radiochannelcreate__array__ret__scalar, params);
        }

        float current_channel() {
            return __helpers::__retrieve_nular_number(__sqf::nular__currentchannel__ret__scalar);
        }

        std::pair<bool, bool> channel_enabled(float channel_) {
            auto ret = host::functions.invoke_raw_unary(__sqf::unary__channelenabled__scalar__ret__array, channel_);
            return { ret[0],ret[1] };
        }

        float get_player_channel(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__getplayerchannel__object__ret__scalar, value_);
        }

        bool set_current_channel(float value_) {
            return __helpers::__bool_unary_number(__sqf::unary__setcurrentchannel__scalar__ret__bool, value_);
        }

        void radio_channel_add(int index_, const std::vector<object> &units_) {
            auto_array<game_value> units({ units_.begin(), units_.end() });

            host::functions.invoke_raw_binary(__sqf::binary__radiochanneladd__scalar__array__ret__nothing, index_, std::move(units));
        }

        void radio_channel_remove(int index_, const std::vector<object> &units_) {
            auto_array<game_value> units({ units_.begin(), units_.end() });

            host::functions.invoke_raw_binary(__sqf::binary__radiochannelremove__scalar__array__ret__nothing, index_, std::move(units));
        }

        void clear_radio() {
            __helpers::__empty_nular(__sqf::nular__clearradio__ret__nothing);
        }

        void enable_radio(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__enableradio__bool__ret__nothing, value_);
        }

        void global_radio(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__globalradio__object__string__ret__nothing, value0_, value1_);
        }

        void set_radio_msg(float value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setradiomsg__scalar__string__ret__nothing, value0_, value1_);
        }

        void vehicle_radio(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__vehicleradio__object__string__ret__nothing, value0_, value1_);
        }

        void custom_radio(const object &unit_, int channel_, std::string &message_) {
            game_value params_right({
                static_cast<float>(channel_),
                message_
            });

            host::functions.invoke_raw_binary(__sqf::binary__customradio__object__array__ret__nothing, unit_, params_right);
        }
    }
}
