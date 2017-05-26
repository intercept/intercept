#include "sound.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        std::string name_sound(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__namesound__object__ret__string, value_);
        }

        void set_name_sound(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setnamesound__object__string__ret__nothing, value0_, value1_);
        }

        void set_speaker(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setspeaker__object__string__ret__nothing, value0_, value1_);
        }

        void say(const object& from_, const std::string& sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say__object_array__string__ret__nothing, from_, sound_classname_);
        }

        void say(const object& from_, const std::string& sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say__object_array__array__ret__nothing, from_, { sound_classname_ ,max_tiles_distance ,speed });
        }

        void say(const object& from_, const object& to_, const std::string& sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say__object_array__string__ret__nothing, { from_, to_ }, sound_classname_);
        }

        void say(const object& from_, const object& to_, const std::string& sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say__object_array__array__ret__nothing, { from_, to_ }, { sound_classname_ ,max_tiles_distance ,speed });
        }

        void say_2d(const object& from_, const std::string& sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say2d__object_array__string__ret__nothing, from_, sound_classname_);
        }

        void say_2d(const object& from_, const std::string& sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say2d__object_array__array__ret__nothing, from_, { sound_classname_ ,max_tiles_distance ,speed });
        }

        void say_2d(const object& from_, const object& to_, const std::string& sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say2d__object_array__string__ret__nothing, { from_, to_ }, sound_classname_);
        }

        void say_2d(const object& from_, const object& to_, const std::string& sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say2d__object_array__array__ret__nothing, { from_, to_ }, { sound_classname_ ,max_tiles_distance ,speed });
        }

        void say_3d(const object& from_, const std::string& sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say3d__object_array__string__ret__nothing, from_, sound_classname_);
        }

        void say_3d(const object& from_, const std::string& sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say3d__object_array__array__ret__nothing, from_, { sound_classname_ ,max_tiles_distance ,speed });
        }

        void say_3d(const object& from_, const object& to_, const std::string& sound_classname_) {
            host::functions.invoke_raw_binary(__sqf::binary__say3d__object_array__string__ret__nothing, { from_, to_ }, sound_classname_);
        }

        void say_3d(const object& from_, const object& to_, const std::string& sound_classname_, float max_tiles_distance, float speed) {
            host::functions.invoke_raw_binary(__sqf::binary__say3d__object_array__array__ret__nothing, { from_, to_ }, { sound_classname_ ,max_tiles_distance ,speed });
        }

        void play_music(const std::string &class_) {
            __helpers::__empty_unary_string(__sqf::unary__playmusic__string__ret__nothing, class_);
        }

        void play_music(const std::string &class_, float start_) {
            game_value params({
                class_,
                start_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playmusic__array__ret__nothing, params);
        }

        void play_sound(const std::string &name_) {
            __helpers::__empty_unary_string(__sqf::unary__playsound__string__ret__nothing, name_);
        }

        void play_sound(const std::string &name_, bool force_) {
            game_value params({
                name_,
                force_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playsound__array__ret__nothing, params);
        }

        std::string pitch(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__pitch__object__ret__string, value_);
        }

        bool preload_sound(const std::string &value_) {
            return __helpers::__bool_unary_string(__sqf::unary__preloadsound__string__ret__bool, value_);
        }

        void set_pitch(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setpitch__object__scalar__ret__nothing, value0_, value1_);
        }

        void direct_say(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__directsay__object__string__ret__nothing, value0_, value1_);
        }

        void play_sound_3d(const std::string &name_, const object &source_) {
            game_value params({
                name_,
                source_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playsound3d__array__ret__nothing, params);
        }

        void play_sound_3d(const std::string &name_, const object &source_, vector3 &pos_) {
            game_value params({
                name_,
                source_,
                pos_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playsound3d__array__ret__nothing, params);
        }

        void play_sound_3d(const std::string &name_, const object &source_, vector3 &pos_, float volume_) {
            game_value params({
                name_,
                source_,
                pos_,
                volume_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playsound3d__array__ret__nothing, params);
        }

        void play_sound_3d(const std::string &name_, const object &source_, vector3 &pos_, float volume_, float pitch_) {
            game_value params({
                name_,
                source_,
                pos_,
                volume_,
                pitch_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playsound3d__array__ret__nothing, params);
        }

        void play_sound_3d(const std::string &name_, const object &source_, vector3 &pos_, float volume_, float pitch_, float distance_) {
            game_value params({
                name_,
                source_,
                pos_,
                volume_,
                pitch_,
                distance_
            });

            host::functions.invoke_raw_unary(__sqf::unary__playsound3d__array__ret__nothing, params);
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

        float get_env_sound_controller(const vector3 &position_, const std::string &controller_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getenvsoundcontroller__array__string__ret__scalar, position_, controller_);
        }

        float get_sound_controller(const object &vehicle_, const std::string &controller_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getsoundcontroller__object__string__ret__scalar, vehicle_, controller_);
        }

        float get_sound_controller_result(const object &object_, const config &config_entry_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getsoundcontrollerresult__object__config__ret__scalar, object_, config_entry_);
        }

        object create_sound_source(const std::string &type_, const vector3 &pos_, const std::vector<marker> &markers_/* = {}*/, float placement_/* = 0.0f*/) {
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


        void remove_all_music_event_handlers(const std::string &value_) {
            __helpers::__empty_unary_string(__sqf::unary__removeallmusiceventhandlers__string__ret__nothing, value_);
        }

        float add_music_event_handler(const std::string &type_, const code &command_) {
            game_value params({
                type_,
                command_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__addmusiceventhandler__array__ret__scalar, params);
        }

        float add_music_event_handler(const std::string &type_, const std::string &command_) {
            game_value params({
                type_,
                command_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__addmusiceventhandler__array__ret__scalar, params);
        }

        void remove_music_event_handler(const std::string &type_, float id_) {
            game_value params({
                type_,
                id_
            });

            host::functions.invoke_raw_unary(__sqf::unary__removemusiceventhandler__array__ret__nothing, params);
        }

        float set_music_event_handler(const std::string& type_, const std::string& command_) {
            game_value params({
                type_,
                command_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__setmusiceventhandler__array__ret__nothing, params);
        }

        float music_volume() {
            return __helpers::__retrieve_nular_number(__sqf::nular__musicvolume__ret__scalar);
        }

        float radio_volume() {
            return host::functions.invoke_raw_nular(__sqf::nular__radiovolume__ret__scalar);
        }


	}
}