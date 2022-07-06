#include "sound.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        sqf_return_string name_sound(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__namesound__object__ret__string, value_);
        }

        void set_name_sound(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setnamesound__object__string__ret__nothing, value0_, value1_);
        }

        void set_speaker(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setspeaker__object__string__ret__nothing, value0_, value1_);
        }

        void say(const object &from_, sqf_string_const_ref sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say__object_array__string__ret__nothing, from_, sound_classname_);
        }

        void say(const object &from_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say__object_array__array__ret__nothing, from_, {sound_classname_, max_tiles_distance, speed});
        }

        void say(const object &from_, const object &to_, sqf_string_const_ref sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say__object_array__string__ret__nothing, {from_, to_}, sound_classname_);
        }

        void say(const object &from_, const object &to_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say__object_array__array__ret__nothing, {from_, to_}, {sound_classname_, max_tiles_distance, speed});
        }

        void say_2d(const object &from_, sqf_string_const_ref sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say2d__object_array__string__ret__nothing, from_, sound_classname_);
        }

        void say_2d(const object &from_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say2d__object_array__array__ret__nothing, from_, {sound_classname_, max_tiles_distance, speed});
        }

        void say_2d(const object &from_, const object &to_, sqf_string_const_ref sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say2d__object_array__string__ret__nothing, {from_, to_}, sound_classname_);
        }

        void say_2d(const object &from_, const object &to_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say2d__object_array__array__ret__nothing, {from_, to_}, {sound_classname_, max_tiles_distance, speed});
        }

        void say_3d(const object &from_, sqf_string_const_ref sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say3d__object_array__string__ret__object, from_, sound_classname_);
        }

        void say_3d(const object &from_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say3d__object_array__array__ret__object, from_, {sound_classname_, max_tiles_distance, speed});
        }

        void say_3d(const object &from_, const object &to_, sqf_string_const_ref sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say3d__object_array__string__ret__object, {from_, to_}, sound_classname_);
        }

        void say_3d(const object &from_, const object &to_, sqf_string_const_ref sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say3d__object_array__array__ret__object, {from_, to_}, {sound_classname_, max_tiles_distance, speed});
        }

        void play_music(sqf_string_const_ref class_) {
            __helpers::__empty_unary_string(__sqf::unary__playmusic__string__ret__nothing, class_);
        }

        void play_music(sqf_string_const_ref class_, float start_) {
            game_value params({class_,
                               start_});

            host::functions.invoke_raw_unary(__sqf::unary__playmusic__array__ret__nothing, params);
        }

        void play_sound(sqf_string_const_ref name_) {
            __helpers::__empty_unary_string(__sqf::unary__playsound__string__ret__object, name_);
        }

        void play_sound(sqf_string_const_ref name_, bool force_) {
            game_value params({name_,
                               force_});

            host::functions.invoke_raw_unary(__sqf::unary__playsound__array__ret__object, params);
        }

        sqf_return_string pitch(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__pitch__object__ret__string, value_);
        }

        bool preload_sound(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__preloadsound__string__ret__bool, value_);
        }

        void set_pitch(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpitch__object__scalar__ret__nothing, value0_, value1_);
        }

        void direct_say(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__directsay__object__string__ret__nothing, value0_, value1_);
        }

        void play_sound_3d(sqf_string_const_ref name_, const object &source_) {
            game_value params({name_,
                               source_});

            host::functions.invoke_raw_unary(__sqf::unary__playsound3d__array__ret__nothing, params);
        }

        void play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_) {
            game_value params({name_,
                               source_,
                               pos_});

            host::functions.invoke_raw_unary(__sqf::unary__playsound3d__array__ret__nothing, params);
        }

        void play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_, float volume_) {
            game_value params({name_,
                               source_,
                               pos_,
                               volume_});

            host::functions.invoke_raw_unary(__sqf::unary__playsound3d__array__ret__nothing, params);
        }

        void play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_, float volume_, float pitch_) {
            game_value params({name_,
                               source_,
                               pos_,
                               volume_,
                               pitch_});

            host::functions.invoke_raw_unary(__sqf::unary__playsound3d__array__ret__nothing, params);
        }

        void play_sound_3d(sqf_string_const_ref name_, const object &source_, vector3 &pos_, float volume_, float pitch_, float distance_) {
            game_value params({name_,
                               source_,
                               pos_,
                               volume_,
                               pitch_,
                               distance_});

            host::functions.invoke_raw_unary(__sqf::unary__playsound3d__array__ret__nothing, params);
        }

        void play_sound_ui(sqf_string_const_ref class_or_path_, float vol_, float pitch_) {
            host::functions.invoke_raw_unary(__sqf::unary__playsoundui__array__ret__nothing, {class_or_path_, vol_, pitch_});
        }

        game_value get_all_env_sound_controllers(const vector3 &position_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getallenvsoundcontrollers__array__ret__array, position_);
        }

        game_value get_all_sound_controllers(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getallsoundcontrollers__object__ret__array, vehicle_);
        }

        void fade_music(float time_, float volume_) {
            host::functions.invoke_raw_binary(__sqf::binary__fademusic__scalar__scalar__ret__nothing, time_, volume_);
        }

        void fade_radio(float time_, float volume_) {
            host::functions.invoke_raw_binary(__sqf::binary__faderadio__scalar__scalar__ret__nothing, time_, volume_);
        }

        void fade_sound(float time_, float volume_) {
            host::functions.invoke_raw_binary(__sqf::binary__fadesound__scalar__scalar__ret__nothing, time_, volume_);
        }

        void fade_speech(float time_, float volume_) {
            host::functions.invoke_raw_binary(__sqf::binary__fadespeech__scalar__scalar__ret__nothing, time_, volume_);
        }

        float get_env_sound_controller(const vector3 &position_, sqf_string_const_ref controller_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getenvsoundcontroller__array__string__ret__scalar, position_, controller_);
        }

        float get_sound_controller(const object &vehicle_, sqf_string_const_ref controller_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getsoundcontroller__object__string__ret__scalar, vehicle_, controller_);
        }

        float get_sound_controller_result(const object &object_, const config &config_entry_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getsoundcontrollerresult__object__config__ret__scalar, object_, config_entry_);
        }

        object create_sound_source(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_ /* = {}*/, float placement_ /* = 0.0f*/) {
            auto_array<game_value> markers(markers_.begin(), markers_.end());

            game_value args({
                type_,
                pos_,
                std::move(markers),
                placement_,
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createsoundsource__array__ret__object, args));
        }

        float sound_volume() {
            return __helpers::__retrieve_nular_number(__sqf::nular__soundvolume__ret__scalar);
        }

        void remove_all_music_event_handlers(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__removeallmusiceventhandlers__string__ret__nothing, value_);
        }

        float add_music_event_handler(sqf_string_const_ref type_, const code &command_) {
            game_value params({type_,
                               command_});

            return host::functions.invoke_raw_unary(__sqf::unary__addmusiceventhandler__array__ret__scalar, params);
        }

        float add_music_event_handler(sqf_string_const_ref type_, sqf_string_const_ref command_) {
            game_value params({type_,
                               command_});

            return host::functions.invoke_raw_unary(__sqf::unary__addmusiceventhandler__array__ret__scalar, params);
        }

        void remove_music_event_handler(sqf_string_const_ref type_, float id_) {
            game_value params({type_,
                               id_});

            host::functions.invoke_raw_unary(__sqf::unary__removemusiceventhandler__array__ret__nothing, params);
        }

        float set_music_event_handler(sqf_string_const_ref type_, sqf_string_const_ref command_) {
            game_value params({type_,
                               command_});

            return host::functions.invoke_raw_unary(__sqf::unary__setmusiceventhandler__array__ret__nothing, params);
        }

        float music_volume() {
            return __helpers::__retrieve_nular_number(__sqf::nular__musicvolume__ret__scalar);
        }

        float radio_volume() {
            return host::functions.invoke_raw_nular(__sqf::nular__radiovolume__ret__scalar);
        }

        rv_audio_options get_audio_option_volumes() {
            return rv_audio_options(host::functions.invoke_raw_nular(__sqf::nular__getaudiooptionvolumes__ret__array));
        }

        void fade_environment(float time_, float volume_) {
            host::functions.invoke_raw_binary(__sqf::binary__fadeenvironment__scalar__scalar__ret__nothing, time_, volume_);
        }

        void set_player_von_volume(const object &unit_, float vol_) {
            host::functions.invoke_raw_binary(__sqf::binary__setplayervonvolume__object__scalar__ret__nothing, unit_, vol_);
        }

        float environment_volume() {
            return host::functions.invoke_raw_nular(__sqf::nular__environmentvolume__ret__scalar);
        }

        float get_music_played_time() {
            return host::functions.invoke_raw_nular(__sqf::nular__getmusicplayedtime__ret__scalar);
        }

        float speech_volume() {
            return host::functions.invoke_raw_nular(__sqf::nular__speechvolume__ret__scalar);
        }

        void enable_audio_feature(sqf_string_const_ref feature_, bool enable_) {
            host::functions.invoke_raw_unary(__sqf::unary__enableaudiofeature__array__ret__bool, {feature_, enable_});
        }

        float get_custom_sound_controller(const object &vehicle_, sqf_string_const_ref controller_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getcustomsoundcontroller__array__ret__scalar, {vehicle_, controller_});
        }

        float get_custom_sound_controller_count(const object &vehicle_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getcustomsoundcontrollercount__object__ret__scalar, vehicle_);
        }

        float get_player_von_volume(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getplayervonvolume__object__ret__scalar, unit_);
        }

        bool set_custom_sound_controller(const object &vehicle_, sqf_string_const_ref controller_, float value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__setcustomsoundcontroller__array__ret__bool, {vehicle_, controller_, value_});
        }

        float get_env_3d_sound_controller(const object &obj_, sqf_string_const_ref controller_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getenv3dsoundcontroller__object__string__ret__scalar, obj_, controller_);
        }

        std::vector<rv_sound_controller> get_all_env_3d_sound_controllers(const object& obj_) {
            return __helpers::__convert_to_vector<rv_sound_controller>(host::functions.invoke_raw_unary(__sqf::unary__getallenv3dsoundcontrollers__object__ret__array, obj_));
        }

        std::vector<object> all_env_3d_sound_sources() {
            return __helpers::__convert_to_vector<object>(__sqf::nular__allenv3dsoundsources__ret__array);
        }
    }  // namespace sqf
}  // namespace intercept
