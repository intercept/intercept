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
        std::string call_extension(const std::string& extension_, const std::string& arguments_);
        std::vector<game_value> call_extension(const std::string &extension_, const std::string &function_, std::vector<game_value> &arguments_);

        game_value call(const code &code_, game_value args_);
        game_value call(const code & code_);
        code compile(const std::string &sqf_);
        std::string preprocess_file(const std::string &value_);
        std::string preprocess_file_line_numbers(const std::string &value_);
        std::string load_file(const std::string &value_);
        float parse_number(const std::string &value_);
        float parse_number(bool value_);
        rv_text parse_text(const std::string &value_);
        std::vector<game_value> parse_simple_array(const std::string &string_array_);
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
        script exec_vm(const std::string& value_);
        bool script_done(script value_);
        void terminate(script value_);
        void debug_fsm(float value0_, bool value1_);
        void uisleep(float value_);
        std::string to_lower(const std::string &value_);
        std::string to_upper(const std::string &value_);
        void sleep(float value_);
        bool finite(float value_);
        float exec_fsm(const std::string &value_);
        void save_profile_namespace();
        void exit();
        std::string copy_from_clipboard();
        void copy_to_clipboard(const std::string & text_);
        bool completed_fsm(float handle_);
        game_value get_fsm_variable(int &fsm_handle_, const std::string &variable_, std::optional<game_value> default_value_);
        void set_fsm_variable(float handle_, const std::string& name_, game_value value_);
        void set_fsm_variable(int fsm_handle_, const std::string &variable_, const game_value &value_);
        int exec_fsm(const game_value &arguments_, const std::string &file_name_);
        script exec_vm(const game_value &arguments_, const std::string &file_name_);
        void exec(const game_value &argument_, const std::string &script_);




        std::string to_fixed(float number_, int decimals_);

        void set_variable(const display &display_, const std::string &variable_, const game_value &value_);
        void set_variable(const control &control_, const std::string &variable_, const game_value &value_);
        void set_variable(const object &object_, const std::string &variable_, const game_value &value_);
        void set_variable(const group &group_, const std::string &variable_, const game_value &value_);
        void set_variable(const team_member &team_member_, const std::string &variable_, const game_value &value_);
        void set_variable(const task &task_, const std::string &variable_, const game_value &value_);
        void set_variable(const location &location_, const std::string &variable_, const game_value &value_);
        void set_variable(const rv_namespace &namespace_, const std::string &var_name_, game_value value_);

        game_value get_variable(const rv_namespace &namespace_, const std::string &var_name_);
        game_value get_variable(const rv_namespace &namespace_, const std::string &var_name_, game_value default_value_);
        game_value get_variable(const display & display_, const std::string & var_name_, game_value default_value_);
        game_value get_variable(const object & obj_, const std::string & var_name_);
        game_value get_variable(const object & obj_, const std::string & var_name_, game_value default_value_);
        game_value get_variable(const group & group_, const std::string & var_name_);
        game_value get_variable(const group & group_, const std::string & var_name_, game_value default_value_);//#TODO shouldn't pass game_values by reference. They are refcounted anyway and get copied into a vector anyway. Problem is this prevents automatic type conversion.
        game_value get_variable(const team_member & team_member_, const std::string & var_name_);
        game_value get_variable(const team_member & team_member_, const std::string & var_name_, game_value default_value_);
        game_value get_variable(const task & task_, const std::string & var_name_);
        game_value get_variable(const control &control_, const std::string &variable_, std::optional<game_value> default_value_);
        game_value get_variable(const task &task_, const std::string &variable_, const game_value &default_value_);
        game_value get_variable(const location &location_, const std::string &variable_, const game_value &default_value_);

        bool is_null(const object &value_);
        bool is_null(const control &value_);
        bool is_null(const display &value_);
        bool is_null(const script &value_);
        bool is_null(const task &value_);

        script script_null();
        rv_namespace ui_namespace();

        task task_null();
        std::vector<std::string> all_variables(const object &value_);
        std::vector<std::string> all_variables(const team_member &value_);
        std::vector<std::string> all_variables(rv_namespace value_);
        std::vector<std::string> all_variables(const task &value_);
        std::vector<std::string> all_variables(const control &value_);
        rv_namespace current_namespace();
        std::string mission_name();
        rv_namespace mission_namespace();
        std::string profile_name();
        rv_namespace parsing_namespace();
        rv_namespace profile_namespace();
        std::string profile_namesteam();
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
        std::string line_break();

    }
}
