/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief Chat function wrappers.

These are wrappers for the `sideChat`, `globalChat`, `commandChat`, etc SQF commands.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client/client.hpp"
#include "shared/client_types.hpp"
#include "shared/types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
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
        bool shown_chat();
        void show_chat(bool value_);
        void enable_channel(float value0_, bool value1_);
        void radio_channel_set_call_sign(float value0_, const std::string& value1_);
        void radio_channel_set_label(float value0_, const std::string& value1_);
        float radio_channel_create(const rv_color &color_, const std::string &label_, const std::string &callsign_, const std::vector<object> &units_);
        float radio_channel_create(const rv_color &color_, const std::string &label_, const std::string &callsign_, const std::vector<object> &units_, bool quote_);
        float current_channel();  
        /**
         * \brief channel_enabled
         * \see https://community.bistudio.com/wiki/channelEnabled
         * \param channel_ 
         * \return [chat enabled, VoN enabled]
         */
        std::pair<bool, bool> channel_enabled(float channel_);
        float get_player_channel(const object &value_);
        bool set_current_channel(float value_);
    }
}
