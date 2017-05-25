/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)

@brief AI related Function wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client/client.hpp"
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        /* ai */
        bool attack_enabled(const object &unit_);
        bool attack_enabled(const group &group_);
        void command_artillery_fire(const object& unit_, const vector3& pos_, const std::string& type_, int rounds_);
        void command_artillery_fire(const object& unit_, const vector2& pos_, const std::string& type_, int rounds_);
        void command_artillery_fire(const std::vector<object>& units_, const vector3& pos_, const std::string& type_, int rounds_);
        void command_artillery_fire(const std::vector<object>& units_, const vector2& pos_, const std::string& type_, int rounds_);
        void command_fire(const object& unit_, const object& target_);
        void command_fire(const std::vector<object>& units_, const object& target_);
        void command_follow(const object& unit_, const object& target_);
        void command_follow(const std::vector<object>& units_, const object& target_);
        void command_fsm(const object& unit_, const std::string& fsm_, const vector3& pos_, const object& target_);
        void command_fsm(const object& unit_, const std::string& fsm_, const vector2& pos_, const object& target_);
        void command_fsm(const std::vector<object>& units_, const std::string& fsm_, const vector3& pos_, const object& target_);
        void command_fsm(const std::vector<object>& units_, const std::string& fsm_, const vector2& pos_, const object& target_);
        void command_move(const object& unit_, const vector3& pos_);
        void command_move(const object& unit_, const vector2& pos_);
        void command_move(const std::vector<object>& units_, const vector3& pos_);
        void command_move(const std::vector<object>& units_, const vector2& pos_);
        void command_radio(const object& unit_, const std::string& radio_name_);
        void command_radio(const std::vector<object>& units_, const std::string& radio_name_);
        void command_target(const object& unit_, const object& target_);
        void command_target(const std::vector<object>& units_, const object& target_);
        void command_watch(const object& unit_, const vector3& pos_);
        void command_watch(const object& unit_, const vector2& pos_);
        void command_watch(const std::vector<object>& units_, const vector3& pos_);
        void command_watch(const std::vector<object>& units_, const vector2& pos_);
        void command_watch(const object& unit_, const object& target_);
        void command_watch(const std::vector<object>& units_, const object& target_);
        void command_get_out(const object &unit_);
        void command_get_out(const std::vector<object> & units_);
        void command_stop(const object &unit_);
        void command_stop(const std::vector<object> & units_);
        void allow_fleeing(const object& object_, float cowardice_);
        void allow_fleeing(const group& group_, float cowardice_);
        void allow_get_in(const std::vector<object>& units_, bool allow_);
        void assign_as_commander(const object& unit_, const object& vehicle_);
        void assign_as_driver(const object& unit_, const object& vehicle_);
        void assign_as_gunner(const object& unit_, const object& vehicle_);
        void assign_as_turret(const object& unit_, const object& vehicle_, const std::vector<float>& turret_path_);
        void assign_as_cargo(const object& unit_, const object& vehicle_);
        void assign_as_cargo_index(const object& unit_, const object& vehicle_, int index_);

        void kb_add_topic(const object &unit_, const std::string &topic_name_, const std::string &bikb_file_, const std::string &fsm_file_, std::variant<std::reference_wrapper<const code>, std::reference_wrapper<const std::string>> event_handler_);
        void kb_react();
        void kb_tell(const object &unit_, const object &receiver_, const std::string &topic_name_, const std::string &sentence_class_, const std::string &argument_name_, const code &argument_value_, const std::string &argument_text_, const std::vector<std::string> &argument_speech_, std::variant<std::reference_wrapper<bool>, std::reference_wrapper<int>, std::reference_wrapper<const std::string>> force_radio_);
        bool kb_was_said(const object &unit_, const object &receiver_, const std::string &topic_, const std::string &sentence_id_, int max_age_);
        bool kb_add_database(const object &value0_, const std::string& value1_);
        bool kb_add_database_targets(const object &value0_, const std::string& value1_);
        bool kb_has_topic(const object &value0_, const std::string& value1_);
        void kb_remove_topic(const object &value0_, const std::string& value1_);

    }
}
