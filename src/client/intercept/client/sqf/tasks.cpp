#include "tasks.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        void remove_simple_task(const object &unit_, const task &task_) {
            host::functions.invoke_raw_binary(__sqf::binary__removesimpletask__object__task__ret__nothing, unit_, task_);
        }

        task create_task(const team_member &member_, sqf_string_const_ref type_, float priority, const std::vector<std::pair<std::string, std::string>> &name_value_pairs_, std::optional<task> parent_task_) {
            auto_array<game_value> p1{type_};
            if (parent_task_)
                p1.push_back(*parent_task_);
            auto_array<game_value> params{std::move(p1), priority};
            for (auto &it : name_value_pairs_) {
                params.push_back(it.first);
                params.push_back(it.second);
            }

            return host::functions.invoke_raw_binary(__sqf::binary__createtask__team_member__array__ret__task, member_, std::move(params));
        }

        task send_task(const team_member &sender_, const team_member &receiver_, sqf_string_const_ref type_, float priority_) {
            game_value params_right({receiver_,
                                     std::move(auto_array<game_value>{type_}),
                                     priority_});

            return host::functions.invoke_raw_binary(__sqf::binary__sendtask__team_member__array__ret__task, sender_, params_right);
        }

        task send_task(const team_member &sender_, const team_member &receiver_, sqf_string_const_ref type_, const task &parent_task_, float priority_, std::vector<rv_task_variables> &variables_) {
            auto_array<game_value> variables;

            for (auto &variable : variables_) {
                variables.push_back(variable.name);
                variables.push_back(variable.value);
            }

            return host::functions.invoke_raw_binary(__sqf::binary__sendtask__team_member__array__ret__task, sender_, {receiver_, {type_, parent_task_}, std::move(variables)});
        }

        //#TODO: Find out which types state_, result_ and sentence_ are
        void send_task_result(const task &task_, const game_value &state_, const game_value &result_, const game_value &sentence_) {
            game_value params_right({state_,
                                     result_,
                                     sentence_});

            host::functions.invoke_raw_binary(__sqf::binary__sendtaskresult__task__array__ret__nothing, task_, params_right);
        }

        void set_current_task(const object &object_, const task &task_) {
            host::functions.invoke_raw_binary(__sqf::binary__setcurrenttask__object__task__ret__nothing, object_, task_);
        }

        void set_simple_task_always_visible(const task &task_, bool always_visible_) {
            host::functions.invoke_raw_binary(__sqf::binary__setsimpletaskalwaysvisible__task__bool__ret__nothing, task_, always_visible_);
        }

        void set_simple_task_custom_data(const task &task_, sqf_string_const_ref icon_path_, sqf_string_const_ref tool_tip_, sqf_string_const_ref description_) {
            host::functions.invoke_raw_binary(__sqf::binary__setsimpletaskcustomdata__task__array__ret__nothing, task_, {icon_path_, tool_tip_, description_});
        }

        void set_simple_task_description(const task &task_, sqf_string_const_ref description_, sqf_string_const_ref description_short_, sqf_string_const_ref description_hud_) {
            host::functions.invoke_raw_binary(__sqf::binary__setsimpletaskdescription__task__array__ret__nothing, task_, {description_, description_short_, description_hud_});
        }

        void set_simple_task_destination(const object &task_, const vector3 &position_) {
            host::functions.invoke_raw_binary(__sqf::binary__setsimpletaskdestination__task__array__ret__nothing, task_, position_);
        }

        void set_simple_task_target(const task &task_, const object &target_, bool precise_position_) {
            host::functions.invoke_raw_binary(__sqf::binary__setsimpletasktarget__task__array__ret__nothing, task_, {target_, precise_position_});
        }

        void set_simple_task_type(const task &task_, sqf_string_const_ref task_type_) {
            host::functions.invoke_raw_binary(__sqf::binary__setsimpletasktype__task__string__ret__nothing, task_, task_type_);
        }

        void set_task_marker_offset(const object &task_, const vector3 &offset_) {
            host::functions.invoke_raw_binary(__sqf::binary__settaskmarkeroffset__object__array__ret__nothing, task_, offset_);
        }

        //#TODO: Find out what the right parameters are
        void set_task_result(const task &task_, const game_value &params_right) {
            host::functions.invoke_raw_binary(__sqf::binary__settaskresult__task__array__ret__nothing, task_, params_right);
        }

        void set_task_state(const task &task_, sqf_string_const_ref state_) {
            host::functions.invoke_raw_binary(__sqf::binary__settaskstate__task__string__ret__nothing, task_, state_);
        }

        std::vector<task> current_tasks(const team_member &team_member_) {
            return __helpers::__convert_to_vector<task>(host::functions.invoke_raw_unary(__sqf::unary__currenttasks__team_member__ret__array, team_member_));
        }

        sqf_return_string formation_task(const object &value_) {
            return __helpers::__string_unary_object(__sqf::unary__formationtask__object__ret__string, value_);
        }

        bool register_task(const team_member &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__registertask__team_member__string__ret__bool, value0_, value1_);
        }

        void set_formation_task(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__setformationtask__object__string__ret__nothing, value0_, value1_);
        }

        bool unregister_task(const team_member &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__unregistertask__team_member__string__ret__bool, value0_, value1_);
        }

        void cancel_simple_task_destination(task value_) {
            host::functions.invoke_raw_unary(__sqf::unary__cancelsimpletaskdestination__task__ret__nothing, value_);
        }

        task current_task(const object &value_) {
            return task(host::functions.invoke_raw_unary(__sqf::unary__currenttask__object__ret__task, value_));
        }

        float priority(task value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__priority__task__ret__scalar, value_);
        }

        bool task_completed(task value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__taskcompleted__task__ret__bool, value_);
        }

        task task_parent(task value_) {
            return task(host::functions.invoke_raw_unary(__sqf::unary__taskparent__task__ret__task, value_));
        }

        sqf_return_string task_state(task value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__taskstate__task__ret__string, value_);
        }

        sqf_return_string type(task value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__type__task__ret__string, value_);
        }

        sqf_return_string_list registered_tasks(const team_member &member_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__registeredtasks__team_member__ret__array, member_));
        }

        std::vector<task> simple_tasks(const object &unit_) {
            return __helpers::__convert_to_vector<task>(host::functions.invoke_raw_unary(__sqf::unary__simpletasks__object__ret__array, unit_));
        }

        sqf_return_string_list task_description(const task &task_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__taskdescription__task__ret__array, task_));
        }

        vector3 task_destination(const task &task_) {
            return host::functions.invoke_raw_unary(__sqf::unary__taskdestination__task__ret__array, task_);
        }

        bool task_always_visible(const task &task_) {
            return host::functions.invoke_raw_unary(__sqf::unary__taskalwaysvisible__task__ret__bool, task_);
        }

        rv_task_custom_data task_custom_data(const task &task_) {
            game_value res = host::functions.invoke_raw_unary(__sqf::unary__taskcustomdata__task__ret__array, task_);

            return rv_task_custom_data({res[0], res[1], res[2]});
        }

        vector3 task_marker_offset(const object &unit_) {
            return host::functions.invoke_raw_unary(__sqf::unary__taskmarkeroffset__object__ret__array, unit_);
        }

        sqf_return_string task_type(const task &task_) {
            return host::functions.invoke_raw_unary(__sqf::unary__tasktype__task__ret__string, task_);
        }

        task create_simple_task(const object &unit_, sqf_string_const_ref name_, std::optional<task> parent_task_) {
            game_value params_right(parent_task_.has_value() ? game_value{name_, *parent_task_} : game_value{name_});

            return host::functions.invoke_raw_binary(__sqf::binary__createsimpletask__object__array__ret__task, unit_, params_right);
        }

        //diary
        void process_diary_link(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__processdiarylink__string__ret__nothing, value_);
        }

        bool diary_subject_exists(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__diarysubjectexists__object__string__ret__bool, value0_, value1_);
        }

        bool select_diary_subject(const object &value0_, sqf_string_const_ref value1_) {
            return host::functions.invoke_raw_binary(__sqf::binary__selectdiarysubject__object__string__ret__bool, value0_, value1_);
        }

        sqf_return_string create_diary_link(sqf_string_const_ref subject_, const object &object_, sqf_string_const_ref text_) {
            game_value params({subject_,
                               object_,
                               text_});

            return host::functions.invoke_raw_unary(__sqf::unary__creatediarylink__array__ret__string, params);
        }

        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref text_) {
            game_value params({subject_,
                               text_});

            return host::functions.invoke_raw_binary(__sqf::binary__creatediaryrecord__object__array__ret__diary_record, object_, params);
        }

        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref text_, const task &task_) {
            game_value params({subject_,
                               text_,
                               task_});

            return host::functions.invoke_raw_binary(__sqf::binary__creatediaryrecord__object__array__ret__diary_record, object_, params);
        }

        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref text_, const task &task_, sqf_string_const_ref state_) {
            game_value params({subject_,
                               text_,
                               task_,
                               state_});

            return host::functions.invoke_raw_binary(__sqf::binary__creatediaryrecord__object__array__ret__diary_record, object_, params);
        }

        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref title_, sqf_string_const_ref text_) {
            game_value params({subject_,
                               game_value({title_,
                                           text_})});

            return host::functions.invoke_raw_binary(__sqf::binary__creatediaryrecord__object__array__ret__diary_record, object_, params);
        }

        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref title_, sqf_string_const_ref text_, const task &task_) {
            game_value params({subject_,
                               game_value({
                                   title_,
                                   text_,
                               }),
                               task_});

            return host::functions.invoke_raw_binary(__sqf::binary__creatediaryrecord__object__array__ret__diary_record, object_, params);
        }

        sqf_return_string create_diary_record(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref title_, sqf_string_const_ref text_, const task &task_, sqf_string_const_ref state_) {
            game_value params({subject_,
                               game_value({title_,
                                           text_}),
                               task_,
                               state_});

            return host::functions.invoke_raw_binary(__sqf::binary__creatediaryrecord__object__array__ret__diary_record, object_, params);
        }

        float create_diary_subject(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref name_) {
            game_value params({subject_,
                               name_});

            return host::functions.invoke_raw_binary(__sqf::binary__creatediarysubject__object__array__ret__scalar, object_, params);
        }

        float create_diary_subject(const object &object_, sqf_string_const_ref subject_, sqf_string_const_ref name_, sqf_string_const_ref picture_) {
            game_value params({subject_,
                               name_,
                               picture_});

            return host::functions.invoke_raw_binary(__sqf::binary__creatediarysubject__object__array__ret__scalar, object_, params);
        }

        //(de-)briefing
        void set_debriefing_text(sqf_string_const_ref endType_, sqf_string_const_ref title_, sqf_string_const_ref description_) {
            host::functions.invoke_raw_binary(__sqf::binary__setdebriefingtext__string__array__ret__nothing, endType_, {title_, description_});
        }

        sqf_return_string briefing_name() {
            return __helpers::__retrieve_nular_string(__sqf::nular__briefingname__ret__string);
        }

        void disable_debriefing_stats() {
            __helpers::__empty_nular(__sqf::nular__disabledebriefingstats__ret__nothing);
        }

        float debriefing_text(sqf_string_const_ref debriefing_) {
            return __helpers::__number_unary_string(__sqf::unary__debriefingtext__string__ret__scalar, debriefing_);
        }

        void on_briefing_group(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__onbriefinggroup__string__ret__nothing, value_);
        }

        void on_briefing_notes(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__onbriefingnotes__string__ret__nothing, value_);
        }

        void on_briefing_plan(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__onbriefingplan__string__ret__nothing, value_);
        }

        void on_briefing_team_switch(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__onbriefingteamswitch__string__ret__nothing, value_);
        }

        void enable_debriefing_stats(float left_, float top_, float width_, float height_) {
            game_value params({left_,
                               top_,
                               width_,
                               height_});

            host::functions.invoke_raw_unary(__sqf::unary__enabledebriefingstats__array__ret__nothing, params);
        }

        void obj_status(sqf_string_const_ref objective_number_, sqf_string_const_ref status_) {
            host::functions.invoke_raw_binary(__sqf::binary__objstatus__string__string__ret__nothing, objective_number_, status_);
        }

        std::vector<task> task_children(const task &task_) {
            return __helpers::__convert_to_vector<task>(host::functions.invoke_raw_unary(__sqf::unary__taskchildren__task__ret__array, task_));
        }

        sqf_return_string task_name(const task &task_) {
            return host::functions.invoke_raw_unary(__sqf::unary__taskname__task__ret__string, task_);
        }
    }  // namespace sqf
}  // namespace intercept
