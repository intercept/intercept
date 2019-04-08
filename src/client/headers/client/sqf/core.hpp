/*!
@file
@author Verox (verox.averre@gmail.com)
@author Nou (korewananda@gmail.com)
@author Glowbal (thomasskooi@live.nl)

@brief "Core" functionality wrappers. `player`, `createVehicle`, etc.

These are functions that are determined to be "core" functionality to the RV Engine.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "client/client.hpp"
#include "shared/client_types.hpp"

using namespace intercept::types;

namespace intercept {
    namespace sqf {
        sqf_return_string call_extension(sqf_string_const_ref extension_, sqf_string_const_ref arguments_);
        std::vector<game_value> call_extension(sqf_string_const_ref extension_, sqf_string_const_ref function_, std::vector<game_value> &arguments_);

        ///Use this to check if fastCall is available. Which calls the engine function directly instead of going through a isNil wrapper
        bool _has_fast_call();
        //This variant is special in that it works before preInit. The one without args doesn't
        game_value call(const code &code_, game_value args_);
        game_value call(const code &code_);
        game_value call2(const code &code_, game_value args_);
        game_value call2(const code &code_);
        script spawn(game_value args, const code &code_);


        bool is_nil_code(const code &code_);
        code compile(sqf_string_const_ref sqf_);
        code compile_final(sqf_string_const_ref sqf_);
        bool is_nil(sqf_string_const_ref var_);
        sqf_return_string preprocess_file(sqf_string_const_ref value_);
        sqf_return_string preprocess_file_line_numbers(sqf_string_const_ref value_);
        sqf_return_string load_file(sqf_string_const_ref value_);
        float parse_number(sqf_string_const_ref value_);
        float parse_number(bool value_);
        rv_text parse_text(sqf_string_const_ref value_);
        std::vector<game_value> parse_simple_array(sqf_string_const_ref string_array_);
        game_value select(game_value array_, const code &code_);
        game_value select_max(const game_value &array_);
        game_value select_min(const game_value &array_);
        int push_back_unique(const std::vector<game_value> &array_, const game_value &element_);
        float random(float seed_, float x_, std::optional<float> y_);
        std::vector<game_value> apply(const std::vector<game_value> &array_, const code &code_);
        bool can_suspend();
        float linear_conversion(float min_, float max_, float value_, float new_min_, float new_max_);
        float linear_conversion(float min_, float max_, float value_, float new_min_, float new_max_, bool clamp_);
        script exec_vm(sqf_string_const_ref value_);
        bool script_done(script value_);
        void terminate(script value_);
        void debug_fsm(float value0_, bool value1_);
        void uisleep(float value_);
        sqf_return_string to_lower(sqf_string_const_ref value_);
        sqf_return_string to_upper(sqf_string_const_ref value_);
        void sleep(float value_);
        bool finite(float value_);
        float exec_fsm(sqf_string_const_ref value_);
        void save_profile_namespace();
        void exit();
        sqf_return_string copy_from_clipboard();
        void copy_to_clipboard(sqf_string_const_ref text_);
        bool completed_fsm(float handle_);
        game_value get_fsm_variable(int &fsm_handle_, sqf_string_const_ref variable_, std::optional<game_value> default_value_);
        void set_fsm_variable(float handle_, sqf_string_const_ref name_, game_value value_);
        void set_fsm_variable(int fsm_handle_, sqf_string_const_ref variable_, const game_value &value_);
        int exec_fsm(const game_value &arguments_, sqf_string_const_ref file_name_);
        script exec_vm(const game_value &arguments_, sqf_string_const_ref file_name_);
        void exec(const game_value &argument_, sqf_string_const_ref script_);
        sqf_return_string str(game_value data_);

        sqf_return_string to_fixed(float number_, int decimals_);

        void set_variable(const display &display_, sqf_string_const_ref variable_, game_value value_);
        void set_variable(const control &control_, sqf_string_const_ref variable_, game_value value_);
        void set_variable(const object &object_, sqf_string_const_ref variable_, game_value value_, bool public_ = false);
        void set_variable(const group &group_, sqf_string_const_ref variable_, game_value value_, bool public_ = false);
        void set_variable(const team_member &team_member_, sqf_string_const_ref variable_, game_value value_);
        void set_variable(const task &task_, sqf_string_const_ref variable_, game_value value_);
        void set_variable(const location &location_, sqf_string_const_ref variable_, game_value value_, bool public_ = false);
        
        void set_variable(const rv_namespace &namespace_, sqf_string_const_ref var_name_, game_value value_, bool public_ = false);

        game_value get_variable(const rv_namespace &namespace_, sqf_string_const_ref var_name_);
        game_value get_variable(const rv_namespace &namespace_, sqf_string_const_ref var_name_, game_value default_value_);
        game_value get_variable(const display &display_, sqf_string_const_ref var_name_, game_value default_value_);
        game_value get_variable(const object &obj_, sqf_string_const_ref var_name_);
        game_value get_variable(const object &obj_, sqf_string_const_ref var_name_, game_value default_value_);
        game_value get_variable(const group &group_, sqf_string_const_ref var_name_);
        game_value get_variable(const group &group_, sqf_string_const_ref var_name_, game_value default_value_);
        game_value get_variable(const team_member &team_member_, sqf_string_const_ref var_name_);
        game_value get_variable(const team_member &team_member_, sqf_string_const_ref var_name_, game_value default_value_);
        game_value get_variable(const task &task_, sqf_string_const_ref var_name_);
        game_value get_variable(const task &task_, sqf_string_const_ref var_name_, game_value default_value_);
        game_value get_variable(const control &control_, sqf_string_const_ref var_name_);
        game_value get_variable(const control &control_, sqf_string_const_ref var_name_, game_value default_value_);
        game_value get_variable(const location &loc_, sqf_string_const_ref var_name_);
        game_value get_variable(const location &location_, sqf_string_const_ref var_name_, game_value default_value_);

        bool is_null(const object &value_);
        bool is_null(const control &value_);
        bool is_null(const display &value_);
        bool is_null(const script &value_);
        bool is_null(const task &value_);

        script script_null();
        rv_namespace ui_namespace();

        task task_null();
        sqf_return_string_list all_variables(const object &value_);
        sqf_return_string_list all_variables(const team_member &value_);
        sqf_return_string_list all_variables(rv_namespace value_);
        sqf_return_string_list all_variables(const task &value_);
        sqf_return_string_list all_variables(const control &value_);
        rv_namespace current_namespace();
        sqf_return_string mission_name();
        rv_namespace mission_namespace();
        sqf_return_string profile_name();
        rv_namespace parsing_namespace();
        rv_namespace profile_namespace();
        sqf_return_string profile_namesteam();
        bool __sqfassert(bool test_);

        object obj_null();
        side blufor();
        side civilian();
        side east();
        side independent();

        side opfor();

        side resistance();
        side side_enemy();
        side side_friendly();
        side side_logic();
        side side_unknown();
        team_member team_member_null();
        side west();
        side side_ambient_life();
        side side_empty();
        sqf_return_string line_break();

        //onEvent
        void on_command_mode_changed(const code &command_);
        void on_command_mode_changed(sqf_string_const_ref command_);
        game_value on_double_click(const control &map_, sqf_string_const_ref command_);
        void on_map_single_click(const game_value &params_, std::variant<sqf_string_const_ref_wrapper, std::reference_wrapper<const code>> command_);
        game_value on_show_new_object(const object &control_, sqf_string_const_ref command_);
        //eventhandler
        int add_event_handler(const object &object_, sqf_string_const_ref type_, const code &command_);
        int add_event_handler(const object &object_, sqf_string_const_ref type_, sqf_string_const_ref command_);
        void remove_event_handler(const object &object_, sqf_string_const_ref event_, int index_);
        int add_mission_event_handler(sqf_string_const_ref type_, const code &command_);
        int add_mission_event_handler(sqf_string_const_ref type_, sqf_string_const_ref command_);
        void remove_all_mission_event_handlers(sqf_string_const_ref value_);
        void remove_all_event_handlers(const object &value0_, sqf_string_const_ref value1_);
        void remove_all_mpevent_handlers(const object &value0_, sqf_string_const_ref value1_);
        void remove_mission_event_handler(sqf_string_const_ref type_, int index_);
        int add_mp_event_handler(const object &object_, sqf_string_const_ref type_, sqf_string_const_ref expression_);
        int add_mp_event_handler(const object &object_, sqf_string_const_ref type_, const code &expression_);
        void remove_mp_event_handler(const object &object_, sqf_string_const_ref event_, int index_);
        void add_public_variable_eventhandler(sqf_string_const_ref var_name_, const code &code_);
        void add_public_variable_eventhandler(sqf_string_const_ref var_name_, const object &target_, const code &code_);

        bool user_input_disabled();
        bool screen_shot(sqf_string_const_ref filename_);
        object cursor_object();
        object cursor_target();
        sqf_return_string_list support_info(sqf_string_const_ref mask_);

        std::vector<object> all_mission_objects(sqf_string_const_ref type_);

        std::vector<object> all_curators();
        std::vector<object> all_dead();
        std::vector<object> all_deadmen();
        std::vector<display> all_displays();
        std::vector<group> all_groups();
        std::vector<object> all_mines();
        std::vector<object> all_players();
        // std::vector<site> all_sites(); // This command is depecrated and no longer supported https://community.bistudio.com/wiki/allSites
        std::vector<object> all_units();
        std::vector<object> all_units_uav();
        std::vector<object> all_simple_objects(sqf_string_list_const_ref params_);

        sqf_return_string_list activated_addons();

        sqf_return_string image(sqf_string_const_ref value_);
        bool is_localized(sqf_string_const_ref value_);
        sqf_return_string localize(sqf_string_const_ref value_);
        game_value text(sqf_string_const_ref value_);
        sqf_return_string text(const location &value_);
        sqf_return_string format(const std::vector<game_value> &params_);
        sqf_return_string compose_text(sqf_string_list_const_ref texts_);
        sqf_return_string endl();
        bool verify_signature(sqf_string_const_ref value_);
        void script_name(sqf_string_const_ref value_);
        bool required_version(sqf_string_const_ref value_);
        void save_var(sqf_string_const_ref value_);
        void scope_name(sqf_string_const_ref value_);
        float playable_slots_number(const side &value_);
        float players_number(const side &value_);
        //Seriously? Either remove this or just return PI instead of calling into Arma
        float pi();
        std::vector<object> playable_units();
        object player();
        float player_respawn_time();
        side player_side();
        std::vector<object> switchable_units();
        void add_switchable_unit(const object &unit_);
        side create_center(const side &side_);  //not used in A3
        void delete_center(const side &side_);
        void disable_user_input(bool value_);
        void echo(sqf_string_const_ref value_);
        void end_mission(sqf_string_const_ref value_);
        void estimated_time_left(float value_);
        void fail_mission(sqf_string_const_ref value_);
        int count_enemy(const object &unit_, const std::vector<object> &units_);
        int count_friendly(const object &unit_, const std::vector<object> &units_);
        int count_type(sqf_string_const_ref type_, const std::vector<object> &objects_);
        int count_unknown(const object &unit_, const std::vector<object> &units_);
        rv_cursor_object_params get_cursor_object_params();


        bool is_equal_to(game_value left_, game_value right_);
        bool is_equal_type(game_value left_, game_value right_);
        bool is_equal_type_all(game_value value_array_, game_value type_);
        bool is_equal_type_any(game_value value_, game_value types_array_);
        bool is_equal_type_array(game_value left_array_, game_value right_array_);
        bool is_equal_type_params(game_value value_, game_value template_);
        int get_mission_version();





    }  // namespace sqf
}  // namespace intercept
