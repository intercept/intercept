/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)
@author Dedmen (dedmen@dedmen.de)
@author Senfo (lpsenfo@gmail.com)

@brief Task related Function wrappers.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        void set_formation_task(const object &value0_, sqf_string_const_ref value1_);
        sqf_return_string formation_task(const object &value_);

        bool unregister_task(const team_member &value0_, sqf_string_const_ref value1_);
        task current_task(const object &value_);
        float priority(task value_);
        bool task_completed(task value_);
        task task_parent(task value_);
        sqf_return_string task_state(task value_);
        sqf_return_string type(task value_);
        sqf_return_string_list registered_tasks(const team_member &member_);
        std::vector<task> simple_tasks(const object &unit_);
        sqf_return_string_list task_description(const task &task_);
        vector3 task_destination(const task &task_);

        struct rv_task_custom_data {
            std::string icon_path;
            std::string icon_text;
            std::string description_text;
        };

        bool task_always_visible(const task &task_);
        rv_task_custom_data task_custom_data(const task &task_);
        vector3 task_marker_offset(const object &unit_);
        sqf_return_string task_type(const task &task_);

        struct rv_task_variables {
            std::string name;
            game_value value;
        };

        task create_simple_task(const object &unit_, sqf_string_const_ref name_, std::optional<task> parent_task_);
        void remove_simple_task(const object &unit_, const task &task_);
        task create_task(const team_member &member_, sqf_string_const_ref type_, float priority, const std::vector<std::pair<std::string, std::string>> &name_value_pairs_, std::optional<task> parent_task_ = {});
        //#TODO arguments incorrect
        task send_task(const team_member &sender_, const team_member &receiver_, sqf_string_const_ref type_, float priority_);
        task send_task(const team_member &sender_, const team_member &receiver_, sqf_string_const_ref type_, const task &parent_task_, float priority_, std::vector<rv_task_variables> &variables_);
        void send_task_result(const task &task_, const game_value &state_, const game_value &result_, const game_value &sentence_);
        void set_current_task(const object &object_, const task &task_);
        void set_simple_task_always_visible(const task &task_, bool always_visible_);
        void set_simple_task_custom_data(const task &task_, sqf_string_const_ref icon_path_, sqf_string_const_ref tool_tip_, sqf_string_const_ref description_);
        void set_simple_task_description(const task &task_, sqf_string_const_ref description_, sqf_string_const_ref description_short_, sqf_string_const_ref description_hud_);
        void set_simple_task_destination(const object &task_, const vector3 &position_);
        void set_simple_task_target(const task &task_, const object &target_, bool precise_position_);
        void set_simple_task_type(const task &task_, sqf_string_const_ref task_type_);
        void set_task_marker_offset(const object &task_, const vector3 &offset_);
        void set_task_result(const task &task_, const game_value &params_right);
        void set_task_state(const task &task_, sqf_string_const_ref state_);
        std::vector<task> current_tasks(const team_member &team_member_);
        bool register_task(const team_member &value0_, sqf_string_const_ref value1_);
        void cancel_simple_task_destination(task value_);

        //diary
        sqf_return_string create_diary_link(sqf_string_const_ref subject_, const object &object_, sqf_string_const_ref text_);
        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref text_);
        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref text_, const task &task_);
        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref text_, const task &task_, sqf_string_const_ref state_);
        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref title_, sqf_string_const_ref text_);
        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref title_, sqf_string_const_ref text_, const task &task_);
        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref title_, sqf_string_const_ref text_, const task &task_, sqf_string_const_ref state_);
        float create_diary_subject(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref name_);
        float create_diary_subject(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref name_, sqf_string_const_ref picture_);
        void process_diary_link(sqf_string_const_ref value_);
        bool diary_subject_exists(const object &value0_, sqf_string_const_ref value1_);
        bool select_diary_subject(const object &value0_, sqf_string_const_ref value1_);

        //(de-)briefing
        void set_debriefing_text(sqf_string_const_ref endType_, sqf_string_const_ref title_, sqf_string_const_ref description_);
        void enable_debriefing_stats(float left_, float top_, float width_, float height_);
        sqf_return_string briefing_name();
        void disable_debriefing_stats();
        float debriefing_text(sqf_string_const_ref debriefing_);
        void on_briefing_group(sqf_string_const_ref value_);
        void on_briefing_notes(sqf_string_const_ref value_);
        void on_briefing_plan(sqf_string_const_ref value_);
        void on_briefing_team_switch(sqf_string_const_ref value_);
        void obj_status(sqf_string_const_ref objective_number_, sqf_string_const_ref status_);
        std::vector<task> task_children(const task &task_);
        sqf_return_string task_name(const task &task_);
        
    }  // namespace sqf
}  // namespace intercept
