#include "chat.hpp"
#include "client/pointers.hpp"
#include "core.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        sqf_return_string call_extension(sqf_string_const_ref extension_, sqf_string_const_ref arguments_) {
            return host::functions.invoke_raw_binary(__sqf::binary__callextension__string__string__ret__string, extension_, arguments_);
        }

        std::vector<game_value> call_extension(sqf_string_const_ref extension_, sqf_string_const_ref function_, std::vector<game_value> &arguments_) {
            auto_array<game_value> arguments(arguments_.begin(), arguments_.end());

            game_value params_right({function_,
                                     std::move(arguments)});

            return __helpers::__convert_to_vector<game_value>(host::functions.invoke_raw_binary(__sqf::binary__callextension__string__array__ret__array, extension_, params_right));
        }

        game_value call2(const code &code_, game_value args_) {
            game_value args({args_, code_});

            set_variable(mission_namespace(), "INTERCEPT_CALL_ARGS"sv, args);
            /*
            Why is this in a wrapper? Because calling the code would only add a new item to the script
            stack. Meaning it will only get executed after we return back to the engine but we want 
            the call to be done after this function returns.
            isNil is executing the whole code inside it's function and it's done executing when it returns,
            which makes it suitable for us.
            */
            code wrapper = get_variable(mission_namespace(), "intercept_fnc_isNilWrapper"sv);
            if (wrapper.is_nil()) {  //Can happen when executed before preInit
                wrapper = sqf::compile(
                    "\
                    (missionNamespace getVariable \"INTERCEPT_CALL_ARGS\") params[\"_args\", \"_code\"];\
                    missionNamespace setVariable[\"INTERCEPT_CALL_RETURN\", if (isNil \"_args\") then {call _code} else {_args call _code}];\
                    "sv);
                set_variable(mission_namespace(), "intercept_fnc_isNilWrapper"sv, static_cast<game_value>(wrapper));
            }

            host::functions.invoke_raw_unary(
                __sqf::unary__isnil__code_string__ret__bool,
                wrapper);

            // Sadly isNil doesn't return anything so we have to grab it from a variable.
            return get_variable(mission_namespace(), "INTERCEPT_CALL_RETURN"sv);
        }

        game_value call2(const code &code_) {
            game_value args({game_value(), code_});

            set_variable(mission_namespace(), "INTERCEPT_CALL_ARGS"sv, args);
            /*
            Why is this in a wrapper? Because calling the code would only add a new item to the script
            stack. Meaning it will only get executed after we return back to the engine but we want
            the call to be done after this function returns.
            isNil is executing the whole code inside it's function and it's done executing when it returns,
            which makes it suitable for us.
            */
            code wrapper = get_variable(mission_namespace(), "intercept_fnc_isNilWrapper"sv);
            if (wrapper.is_nil()) {  //Can happen when executed before preInit
                wrapper = sqf::compile(
                    "\
                    (missionNamespace getVariable \"INTERCEPT_CALL_ARGS\") params[\"_args\", \"_code\"];\
                    missionNamespace setVariable[\"INTERCEPT_CALL_RETURN\", if (isNil \"_args\") then {call _code} else {_args call _code}];\
                    "sv);
                set_variable(mission_namespace(), "intercept_fnc_isNilWrapper"sv, static_cast<game_value>(wrapper));
            }
            host::functions.invoke_raw_unary(
                __sqf::unary__isnil__code_string__ret__bool,
                wrapper);

            // Sadly isNil doesn't return anything so we have to grab it from a variable.
            return get_variable(mission_namespace(), "INTERCEPT_CALL_RETURN"sv);
        }

        bool _has_fast_call() {
            auto ef = host::functions.get_engine_allocator()->evaluate_func;
            return ef;
        }

        game_value call(const code &code_, game_value args_) {
            auto allo = host::functions.get_engine_allocator();
            auto ef = allo->evaluate_func;
            auto gs = allo->gameState;
            if (!_has_fast_call()) return call2(code_, std::move(args_));

            static game_value_static wrapper = sqf::compile("_i135_ar_ call _i135_cc_");

            auto data = static_cast<game_data_code*>(wrapper.data.get());
            
            auto ns = gs->get_global_namespace(game_state::namespace_type::mission);
            static r_string fname = "interceptCall"sv;
            static r_string arname = "_i135_ar_"sv;
            static r_string codename = "_i135_cc_"sv;

            gs->set_local_variable(arname, std::move(args_));
            gs->set_local_variable(codename, code_);

            auto ret = ef(*data, ns, fname);
            return ret;
        }

        game_value call(const code &code_) {
            auto allo = host::functions.get_engine_allocator();
            auto ef = allo->evaluate_func;
            auto gs = allo->gameState;
            if (!ef) return call2(code_);

            auto data = static_cast<game_data_code*>(code_.data.get());

            auto ns = gs->get_global_namespace(game_state::namespace_type::mission);
            static r_string fname = "interceptCall"sv;
            auto ret = ef(*data, ns, fname);
            return ret;
        }


        script spawn(game_value args, const code &code_) {
            return host::functions.invoke_raw_binary(
                __sqf::binary__spawn__any__code__ret__script,
                args,
                code_);
        }

        bool is_nil_code(const code &code_) {
            return host::functions.invoke_raw_unary(
                __sqf::unary__isnil__code_string__ret__bool,
                code_);
        }

        code compile(sqf_string_const_ref sqf_) {
            return code(host::functions.invoke_raw_unary(__sqf::unary__compile__string__ret__code, sqf_));
        }

        code compile_final(sqf_string_const_ref sqf_) {
            return code(host::functions.invoke_raw_unary(__sqf::unary__compilefinal__string__ret__code, sqf_));
        }

        bool is_nil(sqf_string_const_ref var_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnil__code_string__ret__bool, var_);
        }

        sqf_return_string preprocess_file(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__preprocessfile__string__ret__string, value_);
        }

        sqf_return_string preprocess_file_line_numbers(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__preprocessfilelinenumbers__string__ret__string, value_);
        }

        sqf_return_string load_file(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__loadfile__string__ret__string, value_);
        }

        float parse_number(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__parsenumber__string__ret__scalar, value_);
        }

        float parse_number(bool value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__parsenumber__bool__ret__scalar, value_);
        }

        rv_text parse_text(sqf_string_const_ref value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__parsetext__string__ret__text, value_);
        }

        game_value select_max(const game_value &array_) {
            return host::functions.invoke_raw_unary(__sqf::unary__selectmax__array__ret__any, array_);
        }

        game_value select_min(const game_value &array_) {
            return host::functions.invoke_raw_unary(__sqf::unary__selectmin__array__ret__any, array_);
        }

        game_value select(game_value array_, const code &code_) {
            return host::functions.invoke_raw_binary(__sqf::binary__select__array__code__ret__array, array_, code_);
        }

        int push_back_unique(const std::vector<game_value> &array_, const game_value &element_) {
            auto_array<game_value> base_array({array_.begin(), array_.end()});

            return host::functions.invoke_raw_binary(__sqf::binary__pushbackunique__array__any__ret__scalar, std::move(base_array), element_);
        }

        float random(float seed_, float x_, std::optional<float> y_) {
            if (y_.has_value()) {
                game_value params_right({x_,
                                         *y_});

                return host::functions.invoke_raw_binary(__sqf::binary__random__scalar__scalar_array__ret__scalar, seed_, params_right);
            }

            return host::functions.invoke_raw_binary(__sqf::binary__random__scalar__scalar_array__ret__scalar, seed_, x_);
        }

        std::vector<game_value> apply(const std::vector<game_value> &array_, const code &code_) {
            return __helpers::__convert_to_vector<game_value>(host::functions.invoke_raw_binary(__sqf::binary__apply__array__code__ret__array, array_, code_));
        }

        bool can_suspend() {
            return host::functions.invoke_raw_nular(__sqf::nular__cansuspend__ret__bool);
        }

        float linear_conversion(float min_, float max_, float value_, float new_min_, float new_max_) {
            game_value params({min_,
                               max_,
                               value_,
                               new_min_,
                               new_max_});

            return host::functions.invoke_raw_unary(__sqf::unary__linearconversion__array__ret__scalar, params);
        }

        float linear_conversion(float min_, float max_, float value_, float new_min_, float new_max_, bool clamp_) {
            game_value params({min_,
                               max_,
                               value_,
                               new_min_,
                               new_max_,
                               clamp_});

            return host::functions.invoke_raw_unary(__sqf::unary__linearconversion__array__ret__scalar, params);
        }

        int exec_fsm(const game_value &arguments_, sqf_string_const_ref file_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__execfsm__any__string__ret__scalar, arguments_, file_name_);
        }

        script exec_vm(const game_value &arguments_, sqf_string_const_ref file_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__execvm__any__string__ret__script, arguments_, file_name_);
        }

        script exec_vm(sqf_string_const_ref value_) {
            return script(host::functions.invoke_raw_unary(__sqf::unary__execvm__string__ret__script, value_));
        }

        bool script_done(script value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__scriptdone__script__ret__bool, value_);
        }

        void terminate(script value_) {
            host::functions.invoke_raw_unary(__sqf::unary__terminate__script__ret__nothing, value_);
        }
        void debug_fsm(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__debugfsm__scalar__bool__ret__nothing, value0_, value1_);
        }

        void sleep(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__sleep__scalar__ret__nothing, value_);
        }

        void uisleep(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__uisleep__scalar__ret__nothing, value_);
        }

        bool finite(float value_) {
            return __helpers::__bool_unary_number(__sqf::unary__finite__scalar_nan__ret__bool, value_);
        }

        sqf_return_string to_lower(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__tolower__string__ret__string, value_);
        }

        sqf_return_string to_upper(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__toupper__string__ret__string, value_);
        }

        float exec_fsm(sqf_string_const_ref value_) {
            return __helpers::__number_unary_string(__sqf::unary__execfsm__string__ret__scalar, value_);
        }

        void exit() {
            __helpers::__empty_nular(__sqf::nular__exit__ret__nothing);
        }

        void save_profile_namespace() {
            __helpers::__empty_nular(__sqf::nular__saveprofilenamespace__ret__nothing);
        }

        bool save_mission_profile_namespace() {
            return host::functions.invoke_raw_nular(__sqf::nular__savemissionprofilenamespace__ret__bool);
        }

        void copy_to_clipboard(sqf_string_const_ref text_) {
            __helpers::__empty_unary_string(__sqf::unary__copytoclipboard__string__ret__nothing, text_);
        }

        sqf_return_string copy_from_clipboard() {
            return __helpers::__retrieve_nular_string(__sqf::nular__copyfromclipboard__ret__string);
        }

        bool completed_fsm(float handle_) {
            return __helpers::__bool_unary_number(__sqf::unary__completedfsm__scalar__ret__bool, handle_);
        }

        game_value get_fsm_variable(int &fsm_handle_, sqf_string_const_ref variable_, std::optional<game_value> default_value_) {
            if (default_value_.has_value()) {
                game_value params_right({variable_,
                                         *default_value_});

                return host::functions.invoke_raw_binary(__sqf::binary__getfsmvariable__scalar__string_array__ret__any, fsm_handle_, params_right);
            }
            return host::functions.invoke_raw_binary(__sqf::binary__getfsmvariable__scalar__string_array__ret__any, fsm_handle_, variable_);
        }

        void set_fsm_variable(float handle_, sqf_string_const_ref name_, game_value value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfsmvariable__scalar__array__ret__nothing, handle_, {name_, value_});
        }

        void set_fsm_variable(int fsm_handle_, sqf_string_const_ref variable_, const game_value &value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfsmvariable__scalar__array__ret__nothing, fsm_handle_, {variable_, value_});
        }

        void exec(const game_value &argument_, sqf_string_const_ref script_) {
            host::functions.invoke_raw_binary(__sqf::binary__exec__any__string__ret__nothing, argument_, script_);
        }

        sqf_return_string str(game_value data_) {
            return host::functions.invoke_raw_unary(__sqf::unary__str__any__ret__string, data_);
        }

        void set_variable(const display &display_, sqf_string_const_ref variable_, game_value value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__display__array__ret__nothing, display_, {variable_, std::move(value_)});
        }

        void set_variable(const control &control_, sqf_string_const_ref variable_, game_value value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__control__array__ret__nothing, control_, {variable_, std::move(value_)});
        }

        void set_variable(const object &object_, sqf_string_const_ref variable_, game_value value_, bool public_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__object__array__ret__nothing, object_, {variable_, std::move(value_), public_});
        }

        void set_variable(const group &group_, sqf_string_const_ref variable_, game_value value_, bool public_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__group__array__ret__nothing, group_, {variable_, std::move(value_), public_ });
        }

        void set_variable(const team_member &team_member_, sqf_string_const_ref variable_, game_value value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__team_member__array__ret__nothing, team_member_, {variable_, std::move(value_)});
        }

        void set_variable(const task &task_, sqf_string_const_ref variable_, game_value value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__task__array__ret__nothing, task_, {variable_, std::move(value_)});
        }

        void set_variable(const location &location_, sqf_string_const_ref variable_, game_value value_, bool public_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__location__array__ret__nothing, location_, {variable_, std::move(value_), public_ });
        }

        void set_variable(const rv_namespace &namespace_, sqf_string_const_ref var_name_, game_value value_, bool public_) {
            if (public_)
                host::functions.invoke_raw_binary(__sqf::binary__setvariable__namespace__array__ret__nothing, namespace_, { var_name_, std::move(value_), public_ });
            else
                host::functions.invoke_raw_binary(__sqf::binary__setvariable__namespace__array__ret__nothing, namespace_, { var_name_, std::move(value_)});
        }

        game_value get_variable(const rv_namespace &namespace_, sqf_string_const_ref var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__namespace__string__ret__any, namespace_, var_name_);
        }

        game_value get_variable(const rv_namespace &namespace_, sqf_string_const_ref var_name_, game_value default_value_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__namespace__array__ret__any, namespace_, {var_name_, std::move(default_value_)});
        }

        game_value get_variable(const display &display_, sqf_string_const_ref var_name_, game_value default_value_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__display__string_array__ret__any, display_, {var_name_, std::move(default_value_)});
        }

        game_value get_variable(const object &obj_, sqf_string_const_ref var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__object__string__ret__any, obj_, var_name_);
        }

        game_value get_variable(const object &obj_, sqf_string_const_ref var_name_, game_value default_value_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__object__array__ret__any, obj_, {var_name_, std::move(default_value_)});
        }

        game_value get_variable(const group &group_, sqf_string_const_ref var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__group__string__ret__any, group_, var_name_);
        }

        game_value get_variable(const group &group_, sqf_string_const_ref var_name_, game_value default_value_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__group__array__ret__any, group_, {var_name_, std::move(default_value_)});
        }

        game_value get_variable(const team_member &team_member_, sqf_string_const_ref var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__team_member__string__ret__any, team_member_, var_name_);
        }

        game_value get_variable(const team_member &team_member_, sqf_string_const_ref var_name_, game_value default_value_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__team_member__array__ret__any, team_member_, {var_name_, std::move(default_value_)});
        }

        game_value get_variable(const task &task_, sqf_string_const_ref var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__task__string__ret__any, task_, var_name_);
        }

        game_value get_variable(const task &task_, sqf_string_const_ref var_name_, game_value default_value_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__task__array__ret__any, task_, {var_name_, std::move(default_value_)});
        }

        game_value get_variable(const control &control_, sqf_string_const_ref var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__control__string_array__ret__any, control_, var_name_);
        }

        game_value get_variable(const control &control_, sqf_string_const_ref var_name_, game_value default_value_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__control__string_array__ret__any, control_, {var_name_, std::move(default_value_)});
        }

        game_value get_variable(const location &loc_, sqf_string_const_ref var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__location__string__ret__any, loc_, var_name_);
        }

        game_value get_variable(const location &location_, sqf_string_const_ref var_name_, game_value default_value_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__location__array__ret__any, location_, {var_name_, std::move(default_value_)});
        }

        bool is_null(const object &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__object__ret__bool, value_);
        }

        bool is_null(const control &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__control__ret__bool, value_);
        }

        bool is_null(const display &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__display__ret__bool, value_);
        }

        bool is_null(const script &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__script__ret__bool, value_);
        }

        bool is_null(const task &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__task__ret__bool, value_);
        }

        script script_null() {
            return script(host::functions.invoke_raw_nular(__sqf::nular__scriptnull__ret__script));
        }

        task task_null() {
            return task(host::functions.invoke_raw_nular(__sqf::nular__tasknull__ret__task));
        }

        rv_namespace ui_namespace() {
            return rv_namespace(host::functions.invoke_raw_nular(__sqf::nular__uinamespace__ret__namespace));
        }

        sqf_return_string_list all_variables(const object &value_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__object__ret__array, value_));
        }
        sqf_return_string_list all_variables(const team_member &value_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__team_member__ret__array, value_));
        }
        sqf_return_string_list all_variables(rv_namespace value_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__namespace__ret__array, value_));
        }

        sqf_return_string_list all_variables(const task &value_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__task__ret__array, value_));
        }

        sqf_return_string_list all_variables(const control &value_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__control__ret__array, value_));
        }

        sqf_return_string_list all_variables(const display &value_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__display__ret__array, value_));
        }

        side blufor() {
            return __helpers::__retrieve_nular_side(__sqf::nular__blufor__ret__side);
        }

        object obj_null() {
            return __helpers::__retrieve_nular_object(__sqf::nular__objnull__ret__object);
        }

        side opfor() {
            return __helpers::__retrieve_nular_side(__sqf::nular__opfor__ret__side);
        }

        rv_namespace parsing_namespace() {
            return __helpers::__retrieve_nular_namespace(__sqf::nular__parsingnamespace__ret__namespace);
        }

        sqf_return_string mission_name() {
            return __helpers::__retrieve_nular_string(__sqf::nular__missionname__ret__string);
        }

        rv_namespace mission_namespace() {
            return __helpers::__retrieve_nular_namespace(__sqf::nular__missionnamespace__ret__namespace);
        }

        sqf_return_string line_break() {
            return host::functions.invoke_raw_nular(__sqf::nular__linebreak__ret__text);
        }

        side side_enemy() {
            return side(host::functions.invoke_raw_nular(__sqf::nular__sideenemy__ret__side));
        }

        side side_friendly() {
            return side(host::functions.invoke_raw_nular(__sqf::nular__sidefriendly__ret__side));
        }

        side side_logic() {
            return side(host::functions.invoke_raw_nular(__sqf::nular__sidelogic__ret__side));
        }

        side side_unknown() {
            return side(host::functions.invoke_raw_nular(__sqf::nular__sideunknown__ret__side));
        }

        team_member team_member_null() {
            game_value ret_value = host::functions.invoke_raw_nular(__sqf::nular__teammembernull__ret__team_member);
            return team_member(host::functions.invoke_raw_nular(__sqf::nular__teammembernull__ret__team_member));
        }

        side west() {
            return side(host::functions.invoke_raw_nular(__sqf::nular__west__ret__side));
        }

        side east() {
            return __helpers::__retrieve_nular_side(__sqf::nular__east__ret__side);
        }

        side independent() {
            return __helpers::__retrieve_nular_side(__sqf::nular__independent__ret__side);
        }

        sqf_return_string profile_name() {
            return __helpers::__retrieve_nular_string(__sqf::nular__profilename__ret__string);
        }
        rv_namespace profile_namespace() {
            return __helpers::__retrieve_nular_namespace(__sqf::nular__profilenamespace__ret__namespace);
        }

        sqf_return_string profile_namesteam() {
            return __helpers::__retrieve_nular_string(__sqf::nular__profilenamesteam__ret__string);
        }

        side resistance() {
            return __helpers::__retrieve_nular_side(__sqf::nular__resistance__ret__side);
        }
        side side_ambient_life() {
            return host::functions.invoke_raw_nular(__sqf::nular__sideambientlife__ret__side);
        }

        side side_empty() {
            return host::functions.invoke_raw_nular(__sqf::nular__sideempty__ret__side);
        }

        side civilian() {
            return __helpers::__retrieve_nular_side(__sqf::nular__civilian__ret__side);
        }

        rv_namespace current_namespace() {
            return __helpers::__retrieve_nular_namespace(__sqf::nular__currentnamespace__ret__namespace);
        }

        sqf_return_string to_fixed(float number_, int decimals_) {
            return host::functions.invoke_raw_binary(__sqf::binary__tofixed__scalar__scalar__ret__string, number_, decimals_);
        }

        void to_fixed(int decimals_) {
            host::functions.invoke_raw_unary(__sqf::unary__tofixed__scalar__ret__nothing, decimals_);
        }

        bool user_input_disabled() {
            return host::functions.invoke_raw_nular(__sqf::nular__userinputdisabled__ret__bool);
        }

        bool screen_shot(sqf_string_const_ref filename_) {
            return host::functions.invoke_raw_unary(__sqf::unary__screenshot__string__ret__bool, filename_);
        }

        rv_cursor_object_params get_cursor_object_params() {
            game_value res = host::functions.invoke_raw_nular(__sqf::nular__getcursorobjectparams__ret__array);

            return rv_cursor_object_params({res[0], res[1], res[2]});
        }

        object cursor_target() {
            return __helpers::__retrieve_nular_object(__sqf::nular__cursortarget__ret__object);
        }

        object cursor_object() {
            return game_value(__helpers::__retrieve_nular_object(__sqf::nular__cursorobject__ret__object));
        }

        sqf_return_string_list support_info(sqf_string_const_ref mask_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__supportinfo__string__ret__array, mask_));
        }

        std::vector<object> all_simple_objects(sqf_string_list_const_ref params_) {
            auto_array<game_value> params(params_.begin(), params_.end());

            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__allsimpleobjects__array__ret__array, std::move(params)));
        }

        std::vector<object> all_mission_objects(sqf_string_const_ref type_) {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_unary(__sqf::unary__allmissionobjects__string__ret__array, type_));
        }

        std::vector<object> all_curators() {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_nular(__sqf::nular__allcurators__ret__array));
        }

        std::vector<object> all_dead() {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_nular(__sqf::nular__alldead__ret__array));
        }

        std::vector<object> all_deadmen() {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_nular(__sqf::nular__alldeadmen__ret__array));
        }

        std::vector<display> all_displays() {
            return __helpers::__convert_to_vector<display>(host::functions.invoke_raw_nular(__sqf::nular__alldisplays__ret__array));
        }

        std::vector<group> all_groups() {
            return __helpers::__convert_to_vector<group>(host::functions.invoke_raw_nular(__sqf::nular__allgroups__ret__array));
        }

        std::vector<object> all_mines() {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_nular(__sqf::nular__allmines__ret__array));
        }

        std::vector<object> all_players() {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_nular(__sqf::nular__allplayers__ret__array));
        }

        std::vector<object> all_units() {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_nular(__sqf::nular__allunits__ret__array));
        }

        std::vector<object> all_units_uav() {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_nular(__sqf::nular__allunitsuav__ret__array));
        }

        sqf_return_string_list activated_addons() {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_nular(__sqf::nular__activatedaddons__ret__array));
        }

        sqf_return_string image(sqf_string_const_ref value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__image__string__ret__text, value_);
        }

        bool is_localized(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__islocalized__string__ret__bool, value_);
        }

        sqf_return_string localize(sqf_string_const_ref value_) {
            return __helpers::__string_unary_string(__sqf::unary__localize__string__ret__string, value_);
        }

        rv_text text(sqf_string_const_ref value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__text__string__ret__text, value_);
        }

        sqf_return_string text(const location &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__text__location__ret__string, value_);
        }

        sqf_return_string format(const std::vector<game_value> &params_) {
            return host::functions.invoke_raw_unary(__sqf::unary__format__array__ret__string, params_);
        }

        rv_text compose_text(sqf_string_list_const_ref texts_) {
            auto_array<game_value> texts(texts_.begin(), texts_.end());

            return host::functions.invoke_raw_unary(__sqf::unary__composetext__array__ret__text, std::move(texts));
        }

        sqf_return_string endl() {
            return host::functions.invoke_raw_nular(__sqf::nular__endl__ret__string);
        }

        bool verify_signature(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__verifysignature__string__ret__bool, value_);
        }

        void script_name(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__scriptname__string__ret__nothing, value_);
        }

        void save_var(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__savevar__string__ret__nothing, value_);
        }

        void scope_name(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__scopename__string__ret__nothing, value_);
        }

        bool required_version(sqf_string_const_ref value_) {
            return __helpers::__bool_unary_string(__sqf::unary__requiredversion__string__ret__bool, value_);
        }

        float playable_slots_number(const side &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__playableslotsnumber__side__ret__scalar, value_);
        }

        float players_number(const side &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__playersnumber__side__ret__scalar, value_);
        }

        float pi() {
            return __helpers::__retrieve_nular_number(__sqf::nular__pi__ret__scalar);
        }

        std::vector<object> playable_units() {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_nular(__sqf::nular__playableunits__ret__array));
        }

        float player_respawn_time() {
            return __helpers::__retrieve_nular_number(__sqf::nular__playerrespawntime__ret__scalar);
        }

        side player_side() {
            return __helpers::__retrieve_nular_side(__sqf::nular__playerside__ret__side);
        }

        std::vector<object> switchable_units() {
            return __helpers::__convert_to_vector<object>(host::functions.invoke_raw_nular(__sqf::nular__switchableunits__ret__array));
        }

        object player() {
            return object(host::functions.invoke_raw_nular(__sqf::nular__player__ret__object));
        }

        void add_switchable_unit(const object &unit_) {
            __helpers::__empty_unary_object(__sqf::unary__addswitchableunit__object__ret__nothing, unit_);
        }

        side create_center(const side &side_) {
            return side(host::functions.invoke_raw_unary(__sqf::unary__createcenter__side__ret__side, side_));
        }

        void delete_center(const side &side_) {
            host::functions.invoke_raw_unary(__sqf::unary__deletecenter__side__ret__nothing, side_);
        }

        void disable_user_input(bool value_) {
            __helpers::__empty_unary_bool(__sqf::unary__disableuserinput__bool__ret__nothing, value_);
        }

        void echo(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__echo__string__ret__nothing, value_);
        }

        void end_mission(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__endmission__string__ret__nothing, value_);
        }

        std::vector<game_value> mission_end() {
            return __helpers::__convert_to_vector<game_value>(host::functions.invoke_raw_nular(__sqf::nular__missionend__ret__array));
        }

        void estimated_time_left(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__estimatedtimeleft__scalar__ret__nothing, value_);
        }

        void fail_mission(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__failmission__string__ret__nothing, value_);
        }

        int count_enemy(const object &unit_, const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__countenemy__object__array__ret__scalar, unit_, std::move(units));
        }

        int count_friendly(const object &unit_, const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__countfriendly__object__array__ret__scalar, unit_, std::move(units));
        }

        int count_type(sqf_string_const_ref type_, const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__counttype__string__array__ret__scalar, type_, std::move(units));
        }

        int count_unknown(const object &unit_, const std::vector<object> &units_) {
            auto_array<game_value> units(units_.begin(), units_.end());

            return host::functions.invoke_raw_binary(__sqf::binary__countunknown__object__array__ret__scalar, unit_, std::move(units));
        }

        std::vector<game_value> parse_simple_array(sqf_string_const_ref string_array_) {
            return __helpers::__convert_to_vector<game_value>(
                host::functions.invoke_raw_unary(__sqf::unary__parsesimplearray__string__ret__array, string_array_));
        }

        //on_ events
        void on_command_mode_changed(const code &command_) {
            host::functions.invoke_raw_unary(__sqf::unary__oncommandmodechanged__code_string__ret__nothing, command_);
        }

        void on_command_mode_changed(sqf_string_const_ref command_) {
            host::functions.invoke_raw_unary(__sqf::unary__oncommandmodechanged__code_string__ret__nothing, command_);
        }

        game_value on_double_click(const control &map_, sqf_string_const_ref command_) {
            return host::functions.invoke_raw_binary(__sqf::binary__ondoubleclick__control__string__ret__any, map_, command_);
        }

        void on_map_single_click(const game_value &params_, std::variant<sqf_string_const_ref_wrapper, std::reference_wrapper<const code>> command_) {
            game_value param_right;
            switch (command_.index()) {
                case 0: param_right = std::get<0>(command_).get(); break;
                case 1: param_right = std::get<1>(command_).get(); break;
            }

            host::functions.invoke_raw_binary(__sqf::binary__onmapsingleclick__any__code_string__ret__nothing, params_, param_right);
        }

        game_value on_show_new_object(const object &control_, sqf_string_const_ref command_) {
            return host::functions.invoke_raw_binary(__sqf::binary__onshownewobject__control__string__ret__any, control_, command_);
        }

        //eventhandlers
        void remove_event_handler(const object &object_, sqf_string_const_ref event_, int index_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeeventhandler__object__array__ret__nothing, object_, {event_, index_});
        }

        void remove_event_handler(const group &group_, sqf_string_const_ref event_, int index_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeeventhandler__group__array__ret__nothing, group_, {event_, index_});
        }

        int add_event_handler(const object &object_, sqf_string_const_ref type_, const code &command_) {
            return host::functions.invoke_raw_binary(__sqf::binary__addeventhandler__object__array__ret__nothing_scalar, object_, {type_, command_});
        }

        int add_event_handler(const group &group_, sqf_string_const_ref type_, const code &command_) {
            return host::functions.invoke_raw_binary(__sqf::binary__addeventhandler__group__array__ret__nothing_scalar, group_, {type_, command_});
        }

        int add_event_handler(const object &object_, sqf_string_const_ref type_, sqf_string_const_ref command_) {
            return host::functions.invoke_raw_binary(__sqf::binary__addeventhandler__object__array__ret__nothing_scalar, object_, {type_, command_});
        }

        int add_event_handler(const group &group_, sqf_string_const_ref type_, sqf_string_const_ref command_) {
            return host::functions.invoke_raw_binary(__sqf::binary__addeventhandler__group__array__ret__nothing_scalar, group_, {type_, command_});
        }

        void remove_all_mission_event_handlers(sqf_string_const_ref value_) {
            __helpers::__empty_unary_string(__sqf::unary__removeallmissioneventhandlers__string__ret__nothing, value_);
        }

        void remove_mp_event_handler(const object &object_, sqf_string_const_ref event_, int index_) {
            host::functions.invoke_raw_binary(__sqf::binary__removempeventhandler__object__array__ret__nothing, object_, {event_, index_});
        }

        void add_public_variable_eventhandler(sqf_string_const_ref var_name_, const code &code_) {
            host::functions.invoke_raw_binary(__sqf::binary__addpublicvariableeventhandler__string__code__ret__nothing, var_name_, code_);
        }

        void add_public_variable_eventhandler(sqf_string_const_ref var_name_, const object &target_, const code &code_) {
            host::functions.invoke_raw_binary(__sqf::binary__addpublicvariableeventhandler__string__array__ret__nothing, var_name_, {target_, code_});
        }

        int add_user_action_event_handler(sqf_string_const_ref action_name_, user_action_modes mode_, const code &code_) {
            game_value mode_str;
            switch (mode_) {
                case intercept::sqf::user_action_modes::Activate:
                    mode_str = "Activate"sv;
                    break;
                case intercept::sqf::user_action_modes::Deactivate:
                    mode_str = "Deactivate"sv;
                    break;
                case intercept::sqf::user_action_modes::Analog:
                    mode_str = "Analog"sv;
                    break;
                default:
                    return -1;
            }
            return host::functions.invoke_raw_unary(__sqf::unary__adduseractioneventhandler__array__ret__scalar, {action_name_, std::move(mode_str), code_});
        }
        void remove_all_user_action_event_handlers(sqf_string_const_ref action_name_, user_action_modes mode_) {
            game_value mode_str;
            switch (mode_) {
                case intercept::sqf::user_action_modes::Activate:
                    mode_str = "Activate"sv;
                    break;
                case intercept::sqf::user_action_modes::Deactivate:
                    mode_str = "Deactivate"sv;
                    break;
                case intercept::sqf::user_action_modes::Analog:
                    mode_str = "Analog"sv;
                    break;
                default:
                    return;
            }
            host::functions.invoke_raw_unary(__sqf::unary__removealluseractioneventhandlers__array__ret__nothing, {action_name_, std::move(mode_str)});
        }

        void remove_user_action_event_handler(sqf_string_const_ref action_name_, user_action_modes mode_, int index_) {
            game_value mode_str;
            switch (mode_) {
                case intercept::sqf::user_action_modes::Activate:
                    mode_str = "Activate"sv;
                    break;
                case intercept::sqf::user_action_modes::Deactivate:
                    mode_str = "Deactivate"sv;
                    break;
                case intercept::sqf::user_action_modes::Analog:
                    mode_str = "Analog"sv;
                    break;
                default:
                    return;
            }
            host::functions.invoke_raw_unary(__sqf::unary__removeuseractioneventhandler__array__ret__nothing, {action_name_, std::move(mode_str), index_});
        }

        int add_mp_event_handler(const object &object_, sqf_string_const_ref type_, sqf_string_const_ref expression_) {
            return host::functions.invoke_raw_binary(__sqf::binary__addmpeventhandler__object__array__ret__nothing_scalar, object_, {type_, expression_});
        }

        int add_mp_event_handler(const object &object_, sqf_string_const_ref type_, const code &expression_) {
            return host::functions.invoke_raw_binary(__sqf::binary__addmpeventhandler__object__array__ret__nothing_scalar, object_, {type_, expression_});
        }

        void remove_all_event_handlers(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removealleventhandlers__object__string__ret__nothing, value0_, value1_);
        }

        void remove_all_event_handlers(const group &group_, sqf_string_const_ref type_) {
            host::functions.invoke_raw_binary(__sqf::binary__removealleventhandlers__group__string__ret__nothing, group_, type_);
        }

        void remove_all_mpevent_handlers(const object &value0_, sqf_string_const_ref value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__removeallmpeventhandlers__object__string__ret__nothing, value0_, value1_);
        }

        int add_mission_event_handler(sqf_string_const_ref type_, const code &command_) {
            return host::functions.invoke_raw_unary(__sqf::unary__addmissioneventhandler__array__ret__scalar, {type_, command_});
        }

        int add_mission_event_handler(sqf_string_const_ref type_, sqf_string_const_ref command_) {
            return host::functions.invoke_raw_unary(__sqf::unary__addmissioneventhandler__array__ret__scalar, {type_, command_});
        }

        void remove_mission_event_handler(sqf_string_const_ref type_, int index_) {
            host::functions.invoke_raw_unary(__sqf::unary__removemissioneventhandler__array__ret__nothing, {type_, index_});
        }

        rv_event_handler_info get_event_handler_info(const object &obj_, sqf_string_const_ref event_, int id_) {
            return rv_event_handler_info(host::functions.invoke_raw_binary(__sqf::binary__geteventhandlerinfo__object__array__ret__array, obj_, {event_, id_}));
        }

        rv_event_handler_info get_event_handler_info(sqf_string_const_ref event_, int id_) {
            return rv_event_handler_info(host::functions.invoke_raw_unary(__sqf::unary__geteventhandlerinfo__array__ret__array, {event_, id_}));
        }


        bool is_equal_to(game_value left_, game_value right_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isequalto__any__any__ret__bool, left_, right_);
        }

        bool is_equal_type(game_value left_, game_value right_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isequaltype__any__any__ret__bool, left_, right_);
        }

        bool is_equal_type_all(game_value value_array_, game_value type_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isequaltypeall__any__any__ret__bool, value_array_, type_);
        }

        bool is_equal_type_any(game_value value_, game_value types_array_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isequaltypeany__any__array__ret__bool, value_, types_array_);
        }

        bool is_equal_type_array(game_value left_array_, game_value right_array_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isequaltypearray__any__array__ret__bool, left_array_, right_array_);
        }

        bool is_equal_type_params(game_value value_, game_value template_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isequaltypeparams__any__array__ret__bool, value_, template_);
        }

        int get_mission_version() {
            return host::functions.invoke_raw_nular(__sqf::nular__missionversion__ret__scalar);
        }

        sqf_return_string get_mission_path(sqf_string_const_ref path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__getmissionpath__string__ret__string, path_);
        }

        std::vector<rv_addon_info> all_addons_info() {
            return __helpers::__convert_to_vector<rv_addon_info>(host::functions.invoke_raw_nular(__sqf::nular__alladdonsinfo__ret__array));
        }

        std::vector<rv_dlc_usage_stats> get_dlc_assets_usage() {
            return __helpers::__convert_to_vector<rv_dlc_usage_stats>(host::functions.invoke_raw_nular(__sqf::nular__getdlcassetsusage__ret__array));
        }

        std::vector<rv_mod_info> get_loaded_mods_info() {
            return __helpers::__convert_to_vector<rv_mod_info>(host::functions.invoke_raw_nular(__sqf::nular__getloadedmodsinfo__ret__array));
        }

        sqf_return_string_list get_mission_dlcs() {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_nular(__sqf::nular__getmissiondlcs__ret__array));
        }

        std::vector<rv_friend_servers> get_steam_friends_servers() {
            return __helpers::__convert_to_vector<rv_friend_servers>(host::functions.invoke_raw_nular(__sqf::nular__getsteamfriendsservers__ret__array));
        }

        bool is_3den_preview() {
            return host::functions.invoke_raw_nular(__sqf::nular__is3denpreview__ret__bool);
        }

        bool is_game_focused() {
            return host::functions.invoke_raw_nular(__sqf::nular__isgamefocused__ret__bool);
        }

        bool is_game_paused() {
            return host::functions.invoke_raw_nular(__sqf::nular__isgamepaused__ret__bool);
        }

        rv_namespace local_namespace() {
            return host::functions.invoke_raw_nular(__sqf::nular__localnamespace__ret__namespace);
        }

        rv_namespace server_namespace() {
            return host::functions.invoke_raw_nular(__sqf::nular__servernamespace__ret__namespace);
        }

         rv_namespace mission_profile_namespace() {
            return host::functions.invoke_raw_nular(__sqf::nular__missionprofilenamespace__ret__namespace);
        }

        sqf_return_string mission_name_source() {
            return host::functions.invoke_raw_nular(__sqf::nular__missionnamesource__ret__string);
        }

        sqf_return_string_list addon_files(sqf_string_const_ref pboPrefix_, sqf_string_const_ref fileExt_) {
            return __helpers::__convert_to_vector<sqf_return_string>(host::functions.invoke_raw_unary(__sqf::unary__addonfiles__array__ret__array, {pboPrefix_, fileExt_}));
        }

        code compile_script(sqf_string_const_ref path_, bool final_, sqf_string_const_ref prefix_header_) {
            return code(host::functions.invoke_raw_unary(__sqf::unary__compilescript__array__ret__code, {path_, final_, prefix_header_}));
        }

        bool file_exists(sqf_string_const_ref path_) {
            return host::functions.invoke_raw_unary(__sqf::unary__fileexists__string__ret__bool, path_);
        }

        std::pair<bool, bool> force_cadet_difficulty(bool showCadetHints_, bool showCadetWP_) {
            auto ret = host::functions.invoke_raw_unary(__sqf::unary__forcecadetdifficulty__array__ret__array, {showCadetHints_, showCadetWP_});
            return std::pair<bool, bool>{ret[0], ret[1]};
        }

        rv_dlc_asset_info get_asset_dlc_info(const object &asset_) {
            return rv_dlc_asset_info(host::functions.invoke_raw_unary(__sqf::unary__getassetdlcinfo__object_string__ret__array, asset_));
        }
        rv_dlc_asset_info get_asset_dlc_info(sqf_string_const_ref model_) {
            return rv_dlc_asset_info(host::functions.invoke_raw_unary(__sqf::unary__getassetdlcinfo__object_string__ret__array, model_));
        }
        rv_dlc_asset_info get_asset_dlc_info(sqf_string_const_ref classname_, const config &config_) {
            return rv_dlc_asset_info(host::functions.invoke_raw_unary(__sqf::unary__getassetdlcinfo__array__ret__array, {classname_, config_}));
        }

        std::pair<float, float> get_dlc_assets_usage_by_name(sqf_string_const_ref asset_) {
            auto ret = host::functions.invoke_raw_unary(__sqf::unary__getdlcassetsusagebyname__string__ret__array, asset_);
            return std::pair<float, float>{ret[0], ret[1]};
        }

        bool is_final(const code &code_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isfinal__code_string__ret__bool, code_);
        }

        sqf_return_string hash_value(const game_value &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__hashvalue__object_side__ret__string, value_);
        }

        bool is_mission_profile_namespace_loaded() {
            return host::functions.invoke_raw_nular(__sqf::nular__ismissionprofilenamespaceloaded__ret__bool);
        }

        bool is_saving() {
            return host::functions.invoke_raw_nular(__sqf::nular__issaving__ret__bool);
        }
    }  // namespace sqf
}  // namespace intercept
