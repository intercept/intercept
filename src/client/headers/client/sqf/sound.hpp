/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)
@author Senfo (lpsenfo@gmail.com)

@brief Sound related Function wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        float sound_volume();

        //might be AI too
        sqf_return_string name_sound(const object &value_);
        void set_name_sound(const object &value0_, sqf_string_const_ref value1_);
        void set_speaker(const object &value0_, sqf_string_const_ref value1_);
        void say(const object &from_, sqf_string_const_ref sound_classname_);
        sqf_return_string pitch(const object &value_);
        void set_pitch(const object &value0_, float value1_);

        void say(const object &from_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed = 1.f);
        void say(const object &from_, const object &to_, sqf_string_const_ref sound_classname_);
        void say(const object &from_, const object &to_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed = 1.f);

        void say_2d(const object &from_, sqf_string_const_ref sound_classname_);
        void say_2d(const object &from_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed = 1.f);
        void say_2d(const object &from_, const object &to_, sqf_string_const_ref sound_classname_);
        void say_2d(const object &from_, const object &to_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed = 1.f);

        void say_3d(const object &from_, sqf_string_const_ref sound_classname_);
        void say_3d(const object &from_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed = 1.f);
        void say_3d(const object &from_, const object &to_, sqf_string_const_ref sound_classname_);
        void say_3d(const object &from_, const object &to_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed = 1.f);
        void direct_say(const object &value0_, sqf_string_const_ref value1_);

        void play_music(sqf_string_const_ref class_);
        void play_music(sqf_string_const_ref class_, float start_);
        void play_sound(sqf_string_const_ref name_);
        void play_sound(sqf_string_const_ref name_, bool force_);
        bool preload_sound(sqf_string_const_ref value_);
        void play_sound_3d(sqf_string_const_ref name_, const object &source_);
        void play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_);
        void play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_, float volume_);
        void play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_, float volume_, float pitch_);
        void play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_, float volume_, float pitch_, float distance_);
        game_value get_all_env_sound_controllers(const vector3 &position_);
        game_value get_all_sound_controllers(const object &vehicle_);
        void fade_music(float time_, float volume_);
        void fade_radio(float time_, float volume_);
        void fade_sound(float time_, float volume_);
        void fade_speech(float time_, float volume_);
        float get_env_sound_controller(const vector3 &position_, sqf_string_const_ref controller_);
        float get_sound_controller(const object &vehicle_, sqf_string_const_ref controller_);
        float get_sound_controller_result(const object &object_, const config &config_entry_);
        object create_sound_source(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f);
        float radio_volume();
        float music_volume();

        void remove_all_music_event_handlers(sqf_string_const_ref value_);
        float add_music_event_handler(sqf_string_const_ref type_, const code &command_);
        float add_music_event_handler(sqf_string_const_ref type_, sqf_string_const_ref command_);
        void remove_music_event_handler(sqf_string_const_ref type_, float id_);
        float set_music_event_handler(sqf_string_const_ref type_, sqf_string_const_ref command_);

    }  // namespace sqf
}  // namespace intercept
