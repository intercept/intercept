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
#include "shared/client_types.hpp"
#include "shared/types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        namespace __helpers {
            void chat_message(binary_function fnc_, const object &obj_, sqf_string_const_ref message_);
        }
        struct rv_channel_info {
            rv_color colour;
            sqf_string label;
            sqf_string callSign;
            std::vector<object> units{};
            bool isProtocol;
            bool exists;
            explicit rv_channel_info(const game_value &gv_)
                : colour(gv_[0]),
                  label(gv_[1]),
                  callSign(gv_[2]),
                  isProtocol(gv_[4]),
                  exists(gv_[5])
            {
                auto &arr = gv_[3].to_array();
                units = std::vector<object>(arr.begin(), arr.end());
            }
        };

        void side_chat(const object &obj_, sqf_string_const_ref message_);
        void global_chat(const object &obj_, sqf_string_const_ref message_);
        void group_chat(const object &obj_, sqf_string_const_ref message_);
        void vehicle_chat(const object &obj_, sqf_string_const_ref message_);
        void command_chat(const object &obj_, sqf_string_const_ref message_);
        void system_chat(sqf_string_const_ref message_);
        void custom_chat(const object &obj_, uint32_t channel_id_, sqf_string_const_ref message_);
        bool shown_chat();
        void show_chat(bool value_);
        void enable_channel(float value0_, bool value1_);
        void radio_channel_set_call_sign(float value0_, sqf_string_const_ref value1_);
        void radio_channel_set_label(float value0_, sqf_string_const_ref value1_);
        float radio_channel_create(const rv_color &color_, sqf_string_const_ref label_, sqf_string_const_ref callsign_, const std::vector<object> &units_);
        float radio_channel_create(const rv_color &color_, sqf_string_const_ref label_, sqf_string_const_ref callsign_, const std::vector<object> &units_, bool quote_);
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

        void radio_channel_add(int index_, const std::vector<object> &units_);
        void radio_channel_remove(int index_, const std::vector<object> &units_);
        void clear_radio();
        void enable_radio(bool value_);
        void global_radio(const object &value0_, sqf_string_const_ref value1_);
        void set_radio_msg(float value0_, sqf_string_const_ref value1_);
        void vehicle_radio(const object &value0_, sqf_string_const_ref value1_);
        void custom_radio(const object &unit_, int channel_, sqf_string_const_ref message_);

        //chat
        void sideradio(const object &unit_, sqf_string_const_ref radio_name_);
        void sideradio(const side &side_, sqf_string_const_ref identity_, sqf_string_const_ref radio_name_);
        void enable_channel(int channel_, bool chat_, bool voice_over_net_);

        rv_channel_info radio_channel_info(float channelID_);
        bool radio_enabled();
        bool sentences_enabled();
        bool shown_subtitles();
        bool conversation_disabled(const object &obj_);
    }  // namespace sqf
}  // namespace intercept
