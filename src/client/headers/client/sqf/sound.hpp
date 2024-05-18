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
        float play_sound_3d(sqf_string_const_ref name_, const object &source_);
        float play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_);
        float play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_, float volume_);
        float play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_, float volume_, float pitch_);
        float play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_, float volume_, float pitch_, float distance_);
        float play_sound_ui(sqf_string_const_ref class_or_path_, float vol_ = 1.f, float pitch_ = 1.f);

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
        object create_sound_source(sqf_string_const_ref type_, const object &obj_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f);
        object create_sound_source_local(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f);
        object create_sound_source_local(sqf_string_const_ref type_, const object &obj_, const std::vector<marker> &markers_ = {}, float placement_ = 0.0f);
        float radio_volume();
        float music_volume();

        struct rv_audio_options {
            float effects;
            float music;
            float radio;
            float von;

            rv_audio_options(const game_value &data_) :
                effects(data_[0]),
                music(data_[1]),
                radio(data_[2]),
                von(data_[3]) {
            }
        };

        struct rv_sound_controller {
            sqf_string name;
            float value;
            explicit rv_sound_controller(const game_value &gv_) : name(gv_[0]), value(gv_[1]) {}
        };

        rv_audio_options get_audio_option_volumes();
        
        void remove_all_music_event_handlers(sqf_string_const_ref value_);
        float add_music_event_handler(sqf_string_const_ref type_, const code &command_);
        float add_music_event_handler(sqf_string_const_ref type_, sqf_string_const_ref command_);
        void remove_music_event_handler(sqf_string_const_ref type_, float id_);
        float set_music_event_handler(sqf_string_const_ref type_, sqf_string_const_ref command_);
        void fade_environment(float time_, float volume_);
        void set_player_von_volume(const object &unit_, float vol_);
        float environment_volume();
        float get_music_played_time();
        float speech_volume();
        bool enable_audio_feature(sqf_string_const_ref feature_, bool enable_ = true);
        bool enable_audio_feature(const object &building_, sqf_string_const_ref feature_, bool enable_ = true);
        float get_custom_sound_controller(const object &vehicle_, sqf_string_const_ref controller_);
        float get_custom_sound_controller_count(const object &vehicle_);
        float get_player_von_volume(const object &unit_);
        bool set_custom_sound_controller(const object &vehicle_, sqf_string_const_ref controller_, float value_);

        std::vector<rv_sound_controller> get_all_env_3d_sound_controllers(const object &obj_);
        float get_env_3d_sound_controller(const object &obj_, sqf_string_const_ref controller_);

        std::vector<object> all_env_3d_sound_sources();

        struct rv_sound_params {
            sqf_string path;  // the path to the played sound file
            float cur_pos;    // current play position in 0...1 range
            float length;     // total sound duration in seconds
            float time;       // time passed since the start of playback
            float volume;     // playback volume

            explicit rv_sound_params(const game_value &gv_)
                : path(gv_[0]),
                  cur_pos(gv_[1]),
                  length(gv_[2]),
                  time(gv_[3]),
                  volume(gv_[4]) {}
        };

        rv_sound_params sound_params(float id_);
        void stop_sound(float id_);

    }  // namespace sqf
}  // namespace intercept
