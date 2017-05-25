#include "ai.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        bool attack_enabled(const object &unit_) {
            return __helpers::__bool_unary_object(__sqf::unary__attackenabled__object_group__ret__bool, unit_);
        }

        bool attack_enabled(const group &group_) {
            return host::functions.invoke_raw_unary(__sqf::unary__attackenabled__object_group__ret__bool, group_);
        }

        void command_artillery_fire(const object& unit_, const vector3& pos_, const std::string& type_, int rounds_) {
            game_value params({
                pos_,
                type_,
                static_cast<float>(rounds_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandartilleryfire__object_array__array__ret__nothing, unit_, params);
        }

        void command_artillery_fire(const object& unit_, const vector2& pos_, const std::string& type_, int rounds_) {
            game_value params({
                pos_,
                type_,
                static_cast<float>(rounds_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandartilleryfire__object_array__array__ret__nothing, unit_, params);
        }

        void command_artillery_fire(const std::vector<object>& units_, const vector3& pos_, const std::string& type_, int rounds_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            game_value params({
                pos_,
                type_,
                static_cast<float>(rounds_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandartilleryfire__object_array__array__ret__nothing, std::move(units), params);
        }

        void command_artillery_fire(const std::vector<object>& units_, const vector2& pos_, const std::string& type_, int rounds_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            game_value params({
                pos_,
                type_,
                static_cast<float>(rounds_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandartilleryfire__object_array__array__ret__nothing, std::move(units), params);
        }

        void command_fire(const object& unit_, const object& target_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandfire__object_array__object__ret__nothing, unit_, target_);
        }

        void command_fire(const std::vector<object>& units_, const object& target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__commandfire__object_array__object__ret__nothing, std::move(units), target_);
        }

        void command_follow(const object& unit_, const object& target_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandfollow__object_array__object__ret__nothing, unit_, target_);
        }

        void command_follow(const std::vector<object>& units_, const object& target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__commandfollow__object_array__object__ret__nothing, std::move(units), target_);
        }

        void command_fsm(const object& unit_, const std::string& fsm_, const vector3& pos_, const object& target_) {
            game_value params({
                fsm_,
                pos_,
                target_
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandfsm__object_array__array__ret__nothing, unit_, params);
        }

        void command_fsm(const object& unit_, const std::string& fsm_, const vector2& pos_, const object& target_) {
            game_value params({
                fsm_,
                pos_,
                target_
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandfsm__object_array__array__ret__nothing, unit_, params);
        }

        void command_fsm(const std::vector<object>& units_, const std::string& fsm_, const vector3& pos_, const object& target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            game_value params({
                fsm_,
                pos_,
                target_
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandfsm__object_array__array__ret__nothing, std::move(units), params);
        }

        void command_fsm(const std::vector<object>& units_, const std::string& fsm_, const vector2& pos_, const object& target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            game_value params({
                fsm_,
                pos_,
                target_
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandfsm__object_array__array__ret__nothing, std::move(units), params);
        }

        void command_move(const object& unit_, const vector3& pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandmove__object_array__array__ret__nothing, unit_, pos_);
        }

        void command_move(const object& unit_, const vector2& pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandmove__object_array__array__ret__nothing, unit_, pos_);
        }

        void command_move(const std::vector<object>& units_, const vector3& pos_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__commandmove__object_array__array__ret__nothing, std::move(units), pos_);
        }

        void command_move(const std::vector<object>& units_, const vector2& pos_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__commandmove__object_array__array__ret__nothing, std::move(units), pos_);
        }

        void command_radio(const object& unit_, const std::string& radio_name_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandradio__object_array__string__ret__nothing, unit_, radio_name_);
        }

        void command_radio(const std::vector<object>& units_, const std::string& radio_name_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__commandradio__object_array__string__ret__nothing, std::move(units), radio_name_);
        }

        void command_target(const object& unit_, const object& target_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandtarget__object_array__object__ret__nothing, unit_, target_);
        }

        void command_target(const std::vector<object>& units_, const object& target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__commandtarget__object_array__object__ret__nothing, std::move(units), target_);
        }

        void command_watch(const object& unit_, const vector3& pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandwatch__object_array__array__ret__nothing, unit_, pos_);
        }

        void command_watch(const object& unit_, const vector2& pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandwatch__object_array__array__ret__nothing, unit_, pos_);
        }

        void command_watch(const std::vector<object>& units_, const vector3& pos_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__commandwatch__object_array__array__ret__nothing, std::move(units), pos_);
        }

        void command_watch(const std::vector<object>& units_, const vector2& pos_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__commandwatch__object_array__array__ret__nothing, std::move(units), pos_);
        }

        void command_watch(const object& unit_, const object& target_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandwatch__object_array__object__ret__nothing, unit_, target_);
        }

        void command_watch(const std::vector<object>& units_, const object& target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__commandwatch__object_array__object__ret__nothing, std::move(units), target_);
        }

        void command_get_out(const object &unit_) {
            return __helpers::__empty_unary_object(__sqf::unary__commandgetout__object_array__ret__nothing, unit_);
        }

        void command_get_out(const std::vector<object> & units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_unary(__sqf::unary__commandgetout__object_array__ret__nothing, std::move(units));
        }

        void command_stop(const object &unit_) {
            return __helpers::__empty_unary_object(__sqf::unary__commandstop__object_array__ret__nothing, unit_);
        }

        void command_stop(const std::vector<object> & units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_unary(__sqf::unary__commandstop__object_array__ret__nothing, std::move(units));
        }

        void allow_fleeing(const object& object_, float cowardice_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowfleeing__object_group__scalar__ret__nothing, object_, cowardice_);
        }

        void allow_fleeing(const group& group_, float cowardice_) {
            host::functions.invoke_raw_binary(__sqf::binary__allowfleeing__object_group__scalar__ret__nothing, group_, cowardice_);
        }

        void allow_get_in(const std::vector<object>& units_, bool allow_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__allowgetin__array__bool__ret__nothing, std::move(units), allow_);
        }

        void assign_as_cargo(const object& unit_, const object& vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__assignascargo__object__object__ret__nothing, unit_, vehicle_);
        }

        void assign_as_commander(const object& unit_, const object& vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__assignascommander__object__object__ret__nothing, unit_, vehicle_);
        }

        void assign_as_driver(const object& unit_, const object& vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__assignasdriver__object__object__ret__nothing, unit_, vehicle_);
        }

        void assign_as_gunner(const object& unit_, const object& vehicle_) {
            host::functions.invoke_raw_binary(__sqf::binary__assignasgunner__object__object__ret__nothing, unit_, vehicle_);
        }

        void assign_as_turret(const object& unit_, const object& vehicle_, const std::vector<float>& turret_path_) {
            auto_array<game_value> turret_path(turret_path_.begin(), turret_path_.end());

            game_value params({
                vehicle_,
                std::move(turret_path)
            });

            host::functions.invoke_raw_binary(__sqf::binary__assignasgunner__object__object__ret__nothing, unit_, params);
        }

        void assign_as_cargo_index(const object& unit_, const object& vehicle_, int index_) {
            game_value params({
                vehicle_,
                static_cast<float>(index_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__assignascargoindex__object__array__ret__nothing, unit_, params);
        }

        bool kb_add_database(const object &value0_, const std::string& value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__kbadddatabase__object__string__ret__bool, value0_, value1_);
        }

        bool kb_add_database_targets(const object &value0_, const std::string& value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__kbadddatabasetargets__object__string__ret__bool, value0_, value1_);
        }

        bool kb_has_topic(const object &value0_, const std::string& value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__kbhastopic__object__string__ret__bool, value0_, value1_);
        }

        void kb_remove_topic(const object &value0_, const std::string& value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__kbremovetopic__object__string__ret__nothing, value0_, value1_);
        }

        void kb_add_topic(const object &unit_, const std::string &topic_name_, const std::string &bikb_file_, const std::string &fsm_file_, std::variant<std::reference_wrapper<const code>, std::reference_wrapper<const std::string>> event_handler_) {
            auto_array<game_value> params_right({
                topic_name_,
                bikb_file_,
                fsm_file_
            });

            switch (event_handler_.index()) {
            case 0: params_right.push_back(std::get<0>(event_handler_).get()); break;
            case 1: params_right.push_back(std::get<1>(event_handler_).get()); break;
            }

            host::functions.invoke_raw_binary(__sqf::binary__kbaddtopic__object__array__ret__nothing, unit_, std::move(params_right));
        }

        //#TODO: Find out what arguments this command takes
        void kb_react() {
            //host::functions.invoke_raw_binary(__sqf::binary__kbreact__object__array__ret__nothing, unit_, std::move(params_right));
        }

        void kb_tell(const object &unit_, const object &receiver_, const std::string &topic_name_, const std::string &sentence_class_, const std::string &argument_name_, const code &argument_value_, const std::string &argument_text_, const std::vector<std::string> &argument_speech_, std::variant<std::reference_wrapper<bool>, std::reference_wrapper<int>, std::reference_wrapper<const std::string>> force_radio_) {
            auto_array<game_value> params_right({
                receiver_,
                topic_name_,
                sentence_class_,
                argument_name_,
                argument_value_,
                argument_text_,
                std::move(auto_array<game_value>({ argument_speech_.begin(), argument_speech_.end() }))
            });

            switch (force_radio_.index()) {
            case 0: params_right.push_back(std::get<0>(force_radio_).get()); break;
            case 1: params_right.push_back(std::get<1>(force_radio_).get()); break;
            case 2: params_right.push_back(std::get<1>(force_radio_).get()); break;
            }

            host::functions.invoke_raw_binary(__sqf::binary__kbtell__object__array__ret__nothing, unit_, std::move(params_right));
        }

        bool kb_was_said(const object &unit_, const object &receiver_, const std::string &topic_, const std::string &sentence_id_, int max_age_) {
            game_value params_right({
                receiver_,
                topic_,
                sentence_id_,
                max_age_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__kbwassaid__object__array__ret__bool, unit_, params_right);
        }


    }
}
