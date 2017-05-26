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

        game_value call(const code &code_, game_value args_);
        game_value call(const code & code_);
        code compile(sqf_string_const_ref sqf_);
        sqf_return_string preprocess_file(sqf_string_const_ref value_);
        sqf_return_string preprocess_file_line_numbers(sqf_string_const_ref value_);
        sqf_return_string load_file(sqf_string_const_ref value_);
        float parse_number(sqf_string_const_ref value_);
        float parse_number(bool value_);
        rv_text parse_text(sqf_string_const_ref value_);
        std::vector<game_value> parse_simple_array(sqf_string_const_ref string_array_);
        //#TODO return game_value or split into vector of game_values? 
        game_value select(game_value array_, const code& code_);
        game_value select_max(const game_value &array_);
        game_value select_min(const game_value &array_);
        int push_back_unique(const std::vector<game_value> &array_, const game_value &element_);
        float random(float seed_, float x_, std::optional<float> y_);
        std::vector<game_value> apply(const std::vector<game_value> &array_, const code &code_);
        bool can_suspend();
        bool is_equal_to(const object& l_, const object& r_);
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




        sqf_return_string to_fixed(float number_, int decimals_);

        void set_variable(const display &display_, sqf_string_const_ref variable_, const game_value &value_);
        void set_variable(const control &control_, sqf_string_const_ref variable_, const game_value &value_);
        void set_variable(const object &object_, sqf_string_const_ref variable_, const game_value &value_);
        void set_variable(const group &group_, sqf_string_const_ref variable_, const game_value &value_);
        void set_variable(const team_member &team_member_, sqf_string_const_ref variable_, const game_value &value_);
        void set_variable(const task &task_, sqf_string_const_ref variable_, const game_value &value_);
        void set_variable(const location &location_, sqf_string_const_ref variable_, const game_value &value_);
        void set_variable(const rv_namespace &namespace_, sqf_string_const_ref var_name_, game_value value_);

        game_value get_variable(const rv_namespace &namespace_, sqf_string_const_ref var_name_);
        game_value get_variable(const rv_namespace &namespace_, sqf_string_const_ref var_name_, game_value default_value_);
        game_value get_variable(const display & display_, sqf_string_const_ref var_name_, game_value default_value_);
        game_value get_variable(const object & obj_, sqf_string_const_ref var_name_);
        game_value get_variable(const object & obj_, sqf_string_const_ref var_name_, game_value default_value_);
        game_value get_variable(const group & group_, sqf_string_const_ref var_name_);
        game_value get_variable(const group & group_, sqf_string_const_ref var_name_, game_value default_value_);//#TODO shouldn't pass game_values by reference. They are refcounted anyway and get copied into a vector anyway. Problem is this prevents automatic type conversion.
        game_value get_variable(const team_member & team_member_, sqf_string_const_ref var_name_);
        game_value get_variable(const team_member & team_member_, sqf_string_const_ref var_name_, game_value default_value_);
        game_value get_variable(const task & task_, sqf_string_const_ref var_name_);
        game_value get_variable(const control &control_, sqf_string_const_ref variable_, std::optional<game_value> default_value_);
        game_value get_variable(const task &task_, sqf_string_const_ref variable_, const game_value &default_value_);
        game_value get_variable(const location &location_, sqf_string_const_ref variable_, const game_value &default_value_);

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

    }
}
