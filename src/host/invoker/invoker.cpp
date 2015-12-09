#include "invoker.hpp"
#include "controller.hpp"
#include "extensions.hpp"

namespace intercept {

    bool invoker_accessisble = false;
    int total_memory_count = 0;

    void threaded_invoke_demo() {
        while (true) {
           
            Sleep(10);
        }
    }

    nular_function invoker::_state_hook_trampoline = NULL;
    unary_function invoker::_register_hook_trampoline = NULL;

    invoker::invoker() : _attached(false), _patched(false), _delete_index(0)
    {
        
    }

    invoker::~invoker() 
    {

    }

    void invoker::attach_controller()
    {
        if (!_attached) {
            _attached = true;
            controller::get().add("init_invoker", std::bind(&intercept::invoker::init_invoker, this, std::placeholders::_1, std::placeholders::_2));
            controller::get().add("test_invoker", std::bind(&intercept::invoker::test_invoker, this, std::placeholders::_1, std::placeholders::_2));
            controller::get().add("invoker_demo", std::bind(&intercept::invoker::invoker_demo, this, std::placeholders::_1, std::placeholders::_2));
            controller::get().add("do_invoke_period", std::bind(&intercept::invoker::do_invoke_period, this, std::placeholders::_1, std::placeholders::_2));
            controller::get().add("invoker_begin_register", std::bind(&intercept::invoker::invoker_begin_register, this, std::placeholders::_1, std::placeholders::_2));
            controller::get().add("invoker_register", std::bind(&intercept::invoker::invoker_register, this, std::placeholders::_1, std::placeholders::_2));
            controller::get().add("invoker_end_register", std::bind(&intercept::invoker::invoker_end_register, this, std::placeholders::_1, std::placeholders::_2));
        }
    }

    void invoker::allow_access() {
        std::unique_lock<std::mutex> invoke_lock(_invoke_mutex, std::defer_lock);
        {
            std::lock_guard<std::mutex> lock(_state_mutex);
            invoke_lock.lock();
            invoker_accessisble = true;
        }
        
        _invoke_condition.notify_all();
    }

    void invoker::deny_access() {
        std::lock_guard<std::mutex> lock(_state_mutex);
        std::lock_guard<std::mutex> invoke_lock(_invoke_mutex);
        invoker_accessisble = false;
    }

    bool invoker::invoker_begin_register(const arguments & args_, std::string & result_)
    {
        if (loader::get().hook_function("str", _register_hook, _register_hook_trampoline)) {
            LOG(INFO) << "Registration function hooked.";
        }
        else {
            LOG(ERROR) << "Registration function failed to hook.";
        }
        return true;
    }

    bool invoker::invoker_register(const arguments & args_, std::string & result_)
    {
        _registration_type = args_.as_string(0);
        return true;
    }

    bool invoker::invoker_end_register(const arguments & args_, std::string & result_)
    {
        if (loader::get().unhook_function("str", _register_hook, _register_hook_trampoline)) {
            LOG(INFO) << "Registration function unhooked.";
        }
        else {
            LOG(INFO) << "Registration function failed to unhook.";
        }
        return true;
    }

    bool invoker::do_invoke_period(const arguments & args_, std::string & result_)
    {
        auto to_free = _free_queue.begin();
        while (to_free != _free_queue.end()) {
            if (release_value(&*to_free, true)) {
                _free_queue.erase(to_free++);
            }
            else {
                ++to_free;
            }
        }
        allow_access();
        long timeout = clock() + 3;
        while (clock() < timeout) continue;
        // do the per-frame handler here.
        for (auto module : extensions::get().modules()) {
            if (module.second.functions.on_frame) {
                module.second.functions.on_frame();
            }
        }
        deny_access();
        return true;
    }

    bool invoker::init_invoker(const arguments & args_, std::string & result_)
    {
        _delete_size_zero = game_value(0.0f);
        _delete_size_max = game_value(100.0f);

        // @TODO These values need to get cleaned up, but when the release_value() is
        // called this early it crashes the game with some weird race. Need to look at.
        game_value delete_ptr_name = "INVOKER_DELETE_ARRAY";
        game_value mission_namespace = invoke_raw("missionnamespace");
        invoker::get()._delete_array_ptr = invoke_raw("getvariable", &mission_namespace, "NAMESPACE", &delete_ptr_name, "STRING");
        return true;
    }

    bool invoker::test_invoker(const arguments & args_, std::string & result_)
    {
        result_ = "-1";
        game_value res = invoke_raw("profilenamesteam");
        result_ = res;
        return true;
    }

    bool invoker::invoker_demo(const arguments & args_, std::string & result_)
    {
        std::unique_lock<std::mutex> lock(_state_mutex);
        _invoke_condition.wait(lock, [] {return invoker_accessisble;});
        std::lock_guard<std::mutex> invoke_lock(_invoke_mutex);
        result_ = "1";
        _demo_threads.push_back(std::thread(threaded_invoke_demo));
        LOG(INFO) << "Started Demo Thread #" << _demo_threads.size();
        return true;
    }

    const game_value invoker::invoke_raw(nular_function function_)
    {
        std::unique_lock<std::mutex> lock(_state_mutex);
        _invoke_condition.wait(lock, [] {return invoker_accessisble;});
        std::lock_guard<std::mutex> invoke_lock(_invoke_mutex);
        return game_value(function_(_sqf_this, _sqf_game_state));
    }

    const game_value invoker::invoke_raw(std::string function_name_)
    {
        nular_function function;
        if (loader::get().get_function(function_name_, function)) {
            return invoke_raw(function);
        }
        return game_value();
    }

    const game_value invoker::invoke_raw(unary_function function_, game_value *right_)
    {
        std::unique_lock<std::mutex> lock(_state_mutex);
        _invoke_condition.wait(lock, [] {return invoker_accessisble;});
        std::lock_guard<std::mutex> invoke_lock(_invoke_mutex);
        return game_value(function_(_sqf_this, _sqf_game_state, (uintptr_t)right_));
    }

    const game_value invoker::invoke_raw(std::string function_name_, game_value * right_, std::string right_type_)
    {
        unary_function function;
        if (loader::get().get_function(function_name_, function, right_type_)) {
            return invoke_raw(function, right_);
        }
        return game_value();
    }

    const game_value invoker::invoke_raw(std::string function_name_, game_value *right_)
    {
        unary_function function;
        if (loader::get().get_function(function_name_, function)) {
            return invoke_raw(function, right_);
        }
        return game_value();
    }

    const game_value invoker::invoke_raw(binary_function function_, game_value *left_, game_value *right_)
    {
        std::unique_lock<std::mutex> lock(_state_mutex);
        _invoke_condition.wait(lock, [] {return invoker_accessisble;});
        std::lock_guard<std::mutex> invoke_lock(_invoke_mutex);
        return game_value(function_(_sqf_this, _sqf_game_state, (uintptr_t)left_, (uintptr_t)right_));
    }

    const game_value invoker::invoke_raw(std::string function_name_, game_value *left_, game_value *right_)
    {
        binary_function function;
        if (loader::get().get_function(function_name_, function)) {
            return invoke_raw(function, left_, right_);
        }
        return game_value();
    }

    const game_value invoker::invoke_raw(std::string function_name_, game_value * left_, std::string left_type_, game_value * right_, std::string right_type_)
    {
        binary_function function;
        if (loader::get().get_function(function_name_, function, left_type_, right_type_)) {
            return invoke_raw(function, left_, right_);
        }
        return game_value();
    }

    const value_type invoker::get_type(game_value *value_)
    {
        return value_type();
    }

    const std::string invoker::get_type_str(game_value *value_)
    {
        return type_map[value_->type()];
    }

    bool invoker::release_value(game_value *value) {
        return release_value(value, false);
    }

    bool invoker::release_value(game_value *value_, bool immediate_) {
        if (!value_->client_owned()) {
            std::lock_guard<std::mutex> delete_lock(_delete_mutex);
            _delete_array_ptr[_delete_index++] = *value_;
            if (_delete_index >= 100 || immediate_) {
                _delete_index = 0;
                LOG(DEBUG) << "Flushing Memory...";
                invoke_raw("resize", &_delete_array_ptr, &_delete_size_zero);
                invoke_raw("resize", &_delete_array_ptr, &_delete_size_max);
            }
            return true;
        }
        return false;
    }

    int invoker::_state_hook(char * sqf_this_, uintptr_t sqf_game_state_)
    {
        invoker::get()._sqf_this = sqf_this_;
        invoker::get()._sqf_game_state = sqf_game_state_;
        return _state_hook_trampoline(sqf_this_, sqf_game_state_);
    }

    int invoker::_register_hook(char *sqf_this_, uintptr_t sqf_game_state_, uintptr_t right_arg_)
    {
        LOG(INFO) << "Registration Hook Function Called: " << invoker::get()._registration_type;
        auto step = invoker::get()._registration_type;
        invoker::get()._sqf_game_state = sqf_game_state_;
        invoker::get()._sqf_this = sqf_this_;

        std::pair<value_type, value_type> gv_structure;
        invoker::get().game_value_vptr = *(uintptr_t *)right_arg_;
        rv_game_value::__vptr_def = *(uintptr_t *)right_arg_;
        gv_structure.first = rv_game_value::__vptr_def;
        gv_structure.second = rv_game_value::__vptr_def;
        invoker::get().type_structures["GV"] = gv_structure;

        std::pair<value_type, value_type> structure;
        structure.first = *(uintptr_t *)(*(uintptr_t *)(right_arg_ + 4));
        structure.second = *(uintptr_t *)((*(uintptr_t *)(right_arg_ + 4)) + 8);

        if (step == "delete_ptr") {
            invoker::get()._delete_array_ptr = (game_value)*(game_value *)right_arg_;
            LOG(INFO) << "Assigned Delete Ptr";
            invoker::get().type_map[structure.first] = "ARRAY";
            invoker::get().type_structures["ARRAY"] = structure;
            game_data_array::type_def = structure.first;
            game_data_array::data_type_def = structure.second;
            
        }
        else if (step == "numeric_type") {
            invoker::get().type_map[structure.first] = "SCALAR";
            invoker::get().type_structures["SCALAR"] = structure;
            game_data_number::type_def = structure.first;
            game_data_number::data_type_def = structure.second;
        }
        else if (step == "bool_type") {
            invoker::get().type_map[structure.first] = "BOOL";
            invoker::get().type_structures["BOOL"] = structure;
            game_data_bool::type_def = structure.first;
            game_data_bool::data_type_def = structure.second;
        }
        else if (step == "string_type") {
            invoker::get().type_map[structure.first] = "STRING";
            invoker::get().type_structures["STRING"] = structure;
            game_data_string::type_def = structure.first;
            game_data_string::data_type_def = structure.second;
        }

        /*
        else if (step == "code_type") {
            invoker::get().type_map[structure.first] = "CODE";
            invoker::get().type_structures["CODE"] = structure;
            game_data_code::type_def = structure.first;
            game_data_code::data_type_def = structure.second;
        }
        else if (step == "object_type") {
            invoker::get().type_map[structure.first] = "OBJECT";
            invoker::get().type_structures["OBJECT"] = structure;
            game_data_object::type_def = structure.first;
            game_data_object::data_type_def = structure.second;
        }
        else if (step == "group_type") {
            invoker::get().type_map[structure.first] = "GROUP";
            invoker::get().type_structures["GROUP"] = structure;
            game_data_group::type_def = structure.first;
            game_data_group::data_type_def = structure.second;
        }
        else if (step == "config_type") {
            invoker::get().type_map[structure.first] = "CONFIG";
            invoker::get().type_structures["CONFIG"] = structure;
            game_data_config::type_def = structure.first;
            game_data_config::data_type_def = structure.second;
        }
        else if (step == "control_type") {
            invoker::get().type_map[structure.first] = "CONTROL";
            invoker::get().type_structures["CONTROL"] = structure;
            game_data_control::type_def = structure.first;
            game_data_control::data_type_def = structure.second;
        }
        else if (step == "display_type") {
            invoker::get().type_map[structure.first] = "DISPLAY";
            invoker::get().type_structures["DISPLAY"] = structure;
            game_data_display::type_def = structure.first;
            game_data_display::data_type_def = structure.second;
        }
        else if (step == "location_type") {
            invoker::get().type_map[structure.first] = "LOCATION";
            invoker::get().type_structures["LOCATION"] = structure;
            game_data_location::type_def = structure.first;
            game_data_location::data_type_def = structure.second;
        }
        else if (step == "script_type") {
            invoker::get().type_map[structure.first] = "SCRIPT";
            invoker::get().type_structures["SCRIPT"] = structure;
            game_data_script::type_def = structure.first;
            game_data_script::data_type_def = structure.second;
        }
        else if (step == "side_type") {
            invoker::get().type_map[structure.first] = "SIDE";
            invoker::get().type_structures["SIDE"] = structure;
            game_data_side::type_def = structure.first;
            game_data_side::data_type_def = structure.second;
        }
        else if (step == "text_type") {
            invoker::get().type_map[structure.first] = "TEXT";
            invoker::get().type_structures["TEXT"] = structure;
            game_data_text::type_def = structure.first;
            game_data_text::data_type_def = structure.second;
        }
        else if (step == "team_type") {
            invoker::get().type_map[structure.first] = "TEAM_MEMBER";
            invoker::get().type_structures["TEAM_MEMBER"] = structure;
            game_data_team::type_def = structure.first;
            game_data_team::data_type_def = structure.second;
        }
        else if (step == "namespace_type") {
            invoker::get().type_map[structure.first] = "NAMESPACE";
            invoker::get().type_structures["NAMESPACE"] = structure;
            game_data_namespace::type_def = structure.first;
            game_data_namespace::data_type_def = structure.second;
        }
        */
        

        return _register_hook_trampoline(sqf_this_, sqf_game_state_, right_arg_);
    }

}