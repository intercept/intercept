﻿#include "ai.hpp"
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

        void command_artillery_fire(const object& unit_, const vector3& pos_, sqf_string_const_ref type_, int rounds_) {
            game_value params({
                pos_,
                type_,
                static_cast<float>(rounds_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandartilleryfire__object_array__array__ret__nothing, unit_, params);
        }

        void command_artillery_fire(const object& unit_, const vector2& pos_, sqf_string_const_ref type_, int rounds_) {
            game_value params({
                pos_,
                type_,
                static_cast<float>(rounds_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandartilleryfire__object_array__array__ret__nothing, unit_, params);
        }

        void command_artillery_fire(const std::vector<object>& units_, const vector3& pos_, sqf_string_const_ref type_, int rounds_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            game_value params({
                pos_,
                type_,
                static_cast<float>(rounds_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandartilleryfire__object_array__array__ret__nothing, std::move(units), params);
        }

        void command_artillery_fire(const std::vector<object>& units_, const vector2& pos_, sqf_string_const_ref type_, int rounds_) {
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

        void command_fsm(const object& unit_, sqf_string_const_ref fsm_, const vector3& pos_, const object& target_) {
            game_value params({
                fsm_,
                pos_,
                target_
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandfsm__object_array__array__ret__nothing, unit_, params);
        }

        void command_fsm(const object& unit_, sqf_string_const_ref fsm_, const vector2& pos_, const object& target_) {
            game_value params({
                fsm_,
                pos_,
                target_
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandfsm__object_array__array__ret__nothing, unit_, params);
        }

        void command_fsm(const std::vector<object>& units_, sqf_string_const_ref fsm_, const vector3& pos_, const object& target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            game_value params({
                fsm_,
                pos_,
                target_
            });

            host::functions.invoke_raw_binary(__sqf::binary__commandfsm__object_array__array__ret__nothing, std::move(units), params);
        }

        void command_fsm(const std::vector<object>& units_, sqf_string_const_ref fsm_, const vector2& pos_, const object& target_) {
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

        void command_radio(const object& unit_, sqf_string_const_ref radio_name_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandradio__object_array__string__ret__nothing, unit_, radio_name_);
        }

        void command_radio(const std::vector<object>& units_, sqf_string_const_ref radio_name_) {
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

        bool kb_add_database(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__kbadddatabase__object__string__ret__bool, value0_, value1_);
        }

        bool kb_add_database_targets(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__kbadddatabasetargets__object__string__ret__bool, value0_, value1_);
        }

        bool kb_has_topic(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__kbhastopic__object__string__ret__bool, value0_, value1_);
        }

        void kb_remove_topic(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__kbremovetopic__object__string__ret__nothing, value0_, value1_);
        }

        void kb_add_topic(const object &unit_, sqf_string_const_ref topic_name_, sqf_string_const_ref bikb_file_, sqf_string_const_ref fsm_file_, std::variant<std::reference_wrapper<const code>, sqf_string_const_ref_wrapper> event_handler_) {
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

        void kb_tell(const object &unit_, const object &receiver_, sqf_string_const_ref topic_name_, sqf_string_const_ref sentence_class_, sqf_string_const_ref argument_name_, const code &argument_value_, sqf_string_const_ref argument_text_, sqf_string_list_const_ref argument_speech_, std::variant<std::reference_wrapper<bool>, std::reference_wrapper<int>, sqf_string_const_ref_wrapper> force_radio_) {
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

        bool kb_was_said(const object &unit_, const object &receiver_, sqf_string_const_ref topic_, sqf_string_const_ref sentence_id_, int max_age_) {
            game_value params_right({
                receiver_,
                topic_,
                sentence_id_,
                max_age_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__kbwassaid__object__array__ret__bool, unit_, params_right);
        }


        void set_skill(const object &vehicle_, float skill_) {
            host::functions.invoke_raw_binary(__sqf::binary__setskill__object__scalar__ret__nothing, vehicle_, skill_);
        }

        void send_simple_command(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__sendsimplecommand__object__string__ret__nothing, value0_, value1_);
        }
        sqf_return_string speed_mode(const object &obj_) {
            return __helpers::__string_unary_object(__sqf::unary__speedmode__object_group__ret__string, obj_);
        }

        sqf_return_string speed_mode(const group &grp_) {
            return host::functions.invoke_raw_unary(__sqf::unary__speedmode__object_group__ret__string, grp_);
        }

        object create_agent(sqf_string_const_ref type_, const vector3 &pos_, const std::vector<marker> &markers_ /* = {}*/, float placement_ /*= 0.0f*/, sqf_string_const_ref special_ /*= "NONE"*/) {
            auto_array<game_value> markers(markers_.begin(), markers_.end());

            game_value args({
                type_,
                pos_,
                std::move(markers),
                placement_,
                special_
            });

            return object(host::functions.invoke_raw_unary(__sqf::unary__createagent__array__ret__object, args));

        }
        void do_artillery_fire(const object &unit_, const vector3 &position_, float radius_, int rounds_) {
            game_value params_right({
                position_,
                radius_,
                static_cast<float>(rounds_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__doartilleryfire__object_array__array__ret__nothing, unit_, params_right);
        }

        void do_artillery_fire(const std::vector<object> &units_, const vector3 &position_, float radius_, int rounds_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            game_value params_right({
                position_,
                radius_,
                static_cast<float>(rounds_)
            });

            host::functions.invoke_raw_binary(__sqf::binary__doartilleryfire__object_array__array__ret__nothing, std::move(units), params_right);
        }

        void do_fire(const object &unit_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__dofire__object_array__object__ret__nothing, unit_, target_);
        }

        void do_fire(const std::vector<object> &units_, const object &target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__dofire__object_array__object__ret__nothing, std::move(units), target_);
        }

        void do_follow(const object &unit_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__dofollow__object_array__object__ret__nothing, unit_, target_);
        }

        void do_follow(const std::vector<object> &units_, const object &target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__dofollow__object_array__object__ret__nothing, std::move(units), target_);
        }

        void do_fsm(const object &unit_, sqf_string_const_ref fsm_name_, const vector3 &position_, const object &target_) {
            game_value params_right({
                fsm_name_,
                position_,
                target_
            });

            host::functions.invoke_raw_binary(__sqf::binary__dofsm__object_array__array__ret__nothing, unit_, params_right);
        }

        void do_fsm(const std::vector<object> &units_, sqf_string_const_ref fsm_name_, const vector3 &position_, const object &target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            game_value params_right({
                fsm_name_,
                position_,
                target_
            });

            host::functions.invoke_raw_binary(__sqf::binary__dofsm__object_array__array__ret__nothing, std::move(units), params_right);
        }

        void do_move(const object &unit_, const vector3 &position_) {
            host::functions.invoke_raw_binary(__sqf::binary__domove__object_array__array__ret__nothing, unit_, position_);
        }

        void do_move(const std::vector<object> &units_, const vector3 &position_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__domove__object_array__array__ret__nothing, std::move(units), position_);
        }

        void do_suppressive_fire(const object &unit_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__dosuppressivefire__object_array__object_array__ret__nothing, unit_, target_);
        }

        void do_suppressive_fire(const object &unit_, const vector3 &position_) {
            host::functions.invoke_raw_binary(__sqf::binary__dosuppressivefire__object_array__object_array__ret__nothing, unit_, position_);
        }

        void do_suppressive_fire(const std::vector<object> &units_, const object &target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__dosuppressivefire__object_array__object_array__ret__nothing, std::move(units), target_);
        }

        void do_suppressive_fire(const std::vector<object> &units_, const vector3 &position_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__dosuppressivefire__object_array__object_array__ret__nothing, std::move(units), position_);
        }

        void do_target(const object &unit_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__dotarget__object_array__object__ret__nothing, unit_, target_);
        }

        void do_target(const std::vector<object> &units_, const object &target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__dotarget__object_array__object__ret__nothing, std::move(units), target_);
        }

        void do_watch(const object &unit_, const vector3 &position_) {
            host::functions.invoke_raw_binary(__sqf::binary__dowatch__object_array__array__ret__nothing, unit_, position_);
        }

        void do_watch(const std::vector<object> &units_, const vector3 &position_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__dowatch__object_array__array__ret__nothing, std::move(units), position_);
        }

        void do_watch(const object &unit_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__dowatch__object_array__object__ret__nothing, unit_, target_);
        }

        void do_watch(const std::vector<object> &units_, const object &target_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            host::functions.invoke_raw_binary(__sqf::binary__dowatch__object_array__object__ret__nothing, std::move(units), target_);
        }

        void enable_attack(const group &group_, bool enable_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableattack__object_group__bool__ret__nothing, group_, enable_);
        }
        sqf_return_string combat_mode(const object &unit_) {
            return __helpers::__string_unary_object(__sqf::unary__combatmode__object_group__ret__string, unit_);
        }
        sqf_return_string formation(const object &leader_) {
            return host::functions.invoke_raw_unary(__sqf::unary__formation__object_group__ret__string, leader_);
        }

        sqf_return_string formation(const group &group_) {
            return host::functions.invoke_raw_unary(__sqf::unary__formation__object_group__ret__string, group_);
        }

        std::vector<object> formation_members(const object &unit_) {
            return __helpers::__convert_to_objects_vector(host::functions.invoke_raw_unary(__sqf::unary__formationmembers__object__ret__array, unit_));
        }

        vector3 formation_position(const object &unit_) {
            return __helpers::__convert_to_vector3(host::functions.invoke_raw_unary(__sqf::unary__formationposition__object__ret__array, unit_));
        }
        sqf_return_string behaviour(const object & unit_) {
            return __helpers::__string_unary_object(__sqf::unary__behaviour__object__ret__string, unit_);
        }
        bool check_aifeature(sqf_string_const_ref feature_) {
            return __helpers::__bool_unary_string(__sqf::unary__checkaifeature__string__ret__bool, feature_);
        }
        bool fleeing(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__fleeing__object__ret__bool, value_);
        }
        float skill(const object &value_) {
            return __helpers::__number_unary_object(__sqf::unary__skill__object__ret__scalar, value_);
        }
        sqf_return_string land_result(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__landresult__object__ret__string, value_);
        }
        bool move_to_completed(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__movetocompleted__object__ret__bool, value_);
        }

        bool move_to_failed(const object &value_) {
            return __helpers::__bool_unary_object(__sqf::unary__movetofailed__object__ret__bool, value_);
        }
        void disable_ai(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__disableai__object__string__ret__nothing, value0_, value1_);
        }
        void enable_ai(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableai__object__string__ret__nothing, value0_, value1_);
        }

        void enable_aifeature(bool value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__enableaifeature__string__bool__ret__nothing, value0_, value1_);
        }
        void fly_in_height(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__flyinheight__object__scalar__ret__nothing, value0_, value1_);
        }
        float knows_about(const object &source_, const object &target_) {
            return host::functions.invoke_raw_binary(__sqf::binary__knowsabout__object_group__object__ret__scalar, source_, target_);
        }

        float knows_about(const group &source_, const object &target_) {
            return host::functions.invoke_raw_binary(__sqf::binary__knowsabout__object_group__object__ret__scalar, source_, target_);
        }

        float knows_about(const side &side_, const object &target_) {
            return host::functions.invoke_raw_binary(__sqf::binary__knowsabout__side__object__ret__scalar, side_, target_);
        }
        void land(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__land__object__string__ret__nothing, value0_, value1_);
        }

        void land_at(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__landat__object__object_scalar__ret__nothing, value0_, value1_);
        }

        void land_at(const object &value0_, const object & helipad_) {
            host::functions.invoke_raw_binary(__sqf::binary__landat__object__object_scalar__ret__nothing, value0_, helipad_);
        }
        float skill(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__skill__object__string__ret__scalar, value0_, value1_);
        }
        float skill_final(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__skillfinal__object__string__ret__scalar, value0_, value1_);
        }
        void stop(const object &value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__stop__object__bool__ret__nothing, value0_, value1_);
        }
        void suppress_for(const object &value0_, float value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__suppressfor__object__scalar__ret__nothing, value0_, value1_);
        }
        void move_to(const object& unit_, const vector3& pos_) {
            host::functions.invoke_raw_binary(__sqf::binary__moveto__object__array__ret__nothing, unit_, pos_);
        }
        rv_expected_destination expected_destination(const object& unit_) {
            return rv_expected_destination(host::functions.invoke_raw_unary(__sqf::unary__expecteddestination__object__ret__array, unit_));
        }
        void use_ai_oper_map_obstruction_test(bool use_) {
            host::functions.invoke_raw_unary(__sqf::unary__useaiopermapobstructiontest__bool__ret__nothing, use_);
        }

        void use_ai_steering_component(bool use_) {
            host::functions.invoke_raw_unary(__sqf::unary__useaisteeringcomponent__bool__ret__nothing, use_);
        }
        void command_suppressive_fire(const object &unit_, const object &target_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandsuppressivefire__object_array__object_array__ret__nothing, unit_, target_);
        }

        void command_suppressive_fire(const object &unit_, const vector3 &target_position_) {
            host::functions.invoke_raw_binary(__sqf::binary__commandsuppressivefire__object_array__object_array__ret__nothing, unit_, target_position_);
        }





















    }
}
