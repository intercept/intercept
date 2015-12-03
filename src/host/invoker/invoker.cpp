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
        //bool patched = loader::get().hook_function("cadetmode", _state_hook, _state_hook_trampoline);
        _delete_size_zero = create_type<invoker_type::scalar>();
        _delete_size_max = create_type<invoker_type::scalar>();
        ((game_data_number *)_delete_size_zero.data)->number = 0.0f;
        ((game_data_number *)_delete_size_max.data)->number = 100.0f;
        game_value delete_ptr_name = create_type<invoker_type::string>();
        ((game_data_string *)delete_ptr_name.data)->set_string("INVOKER_DELETE_ARRAY");
        game_value mission_namespace = invoke_raw("missionnamespace");
        invoker::get()._delete_array_ptr = invoke_raw("getvariable", &mission_namespace, "NAMESPACE", &delete_ptr_name, "STRING");
        //release_value(&delete_ptr_name);
        //release_value(&mission_namespace);
        /*
        if (patched) {
            LOG(INFO) << "Invoker has attached itself.";
            _patched = true;
            result_ = "1";
        }
        else {
            LOG(ERROR) << "Invoker has FAILED to attach itself.";
            result_ = "-1";
        }
        */
        return true;
    }

    bool invoker::test_invoker(const arguments & args_, std::string & result_)
    {
        result_ = "-1";
        game_value res = invoke_raw("profilenamesteam");
        if (res.data != NULL) {
            game_data_string *profile_name = (game_data_string *)res.data;
            result_ = profile_name->get_string();
        }
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
        uintptr_t return_address = function_(_sqf_this, _sqf_game_state);
        game_value return_value;
        return_value.__vptr = *(uintptr_t *)return_address;
        return_value.data = (game_data *)*(uintptr_t *)(return_address + 4);
        return return_value;
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
        uintptr_t return_address = function_(_sqf_this, _sqf_game_state, (uintptr_t)right_);
        game_value return_value;
        return_value.__vptr = *(uintptr_t *)return_address;
        return_value.data = (game_data *)*(uintptr_t *)(return_address + 4);
        return return_value;
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
        uintptr_t return_address = function_(_sqf_this, _sqf_game_state, (uintptr_t)left_, (uintptr_t)right_);
        game_value return_value;
        return_value.__vptr = *(uintptr_t *)return_address;
        return_value.data = (game_data *)*(uintptr_t *)(return_address + 4);
        return return_value;
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
        return type_map[value_->data->type];
    }

    bool invoker::release_value(game_value *value) {
        return release_value(value, false);
    }

    bool invoker::release_value(game_value *value_, bool immediate_) {
        if (value_->data->ref_count_internal != 0x0000dede) {
            std::lock_guard<std::mutex> delete_lock(_delete_mutex);
            value_->data->ref_count_internal = 1; // this may or may not be needed and might actually be detrimental
            game_data_array *value_array = (game_data_array *)_delete_array_ptr.data;
            value_array->data[_delete_index++] = *value_;
            value_array->length = _delete_index;
            if (_delete_index >= 100 || immediate_) {
                _delete_index = 0;
                LOG(DEBUG) << "Flushing Memory...";
                invoke_raw("resize", &_delete_array_ptr, &_delete_size_zero);
                invoke_raw("resize", &_delete_array_ptr, &_delete_size_max);
            }
            return true;
        }
        else {
            if (immediate_) {
                if (get_type_str(value_) == "STRING") {
                    if (((game_data_string *)value_->data)->raw_string->ref_count_internal <= 1) {
                        delete (game_data_string *)value_->data;
                        return true;
                    }
                }
                else {
                    delete value_->data;
                    return true;
                }
            }
            else {
                _free_queue.push_back(*value_);
            }
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

        invoker::get().game_value_vptr = *(uintptr_t *)right_arg_;

        std::pair<value_type, value_type> structure;
        structure.first = *(uintptr_t *)(*(uintptr_t *)(right_arg_ + 4));
        structure.second = *(uintptr_t *)((*(uintptr_t *)(right_arg_ + 4)) + 8);

        if (step == "delete_ptr") {
            invoker::get()._delete_array_ptr = (game_value)*(game_value *)right_arg_;
            LOG(INFO) << "Assigned Delete Ptr";
            invoker::get().type_map[structure.first] = "ARRAY";
            invoker::get().type_structures["ARRAY"] = structure;
        }
        else if (step == "numeric_type") {
            invoker::get().type_map[structure.first] = "SCALAR";
            invoker::get().type_structures["SCALAR"] = structure;
        }
        else if (step == "string_type") {
            invoker::get().type_map[structure.first] = "STRING";
            invoker::get().type_structures["STRING"] = structure;
        }
        else if (step == "code_type") {
            invoker::get().type_map[structure.first] = "CODE";
            invoker::get().type_structures["CODE"] = structure;
        }
        else if (step == "object_type") {
            invoker::get().type_map[structure.first] = "OBJECT";
            invoker::get().type_structures["OBJECT"] = structure;
        }
        else if (step == "group_type") {
            invoker::get().type_map[structure.first] = "GROUP";
            invoker::get().type_structures["GROUP"] = structure;
        }
        else if (step == "config_type") {
            invoker::get().type_map[structure.first] = "CONFIG";
            invoker::get().type_structures["CONFIG"] = structure;
        }
        else if (step == "control_type") {
            invoker::get().type_map[structure.first] = "CONTROL";
            invoker::get().type_structures["CONTROL"] = structure;
        }
        else if (step == "display_type") {
            invoker::get().type_map[structure.first] = "DISPLAY";
            invoker::get().type_structures["DISPLAY"] = structure;
        }
        else if (step == "location_type") {
            invoker::get().type_map[structure.first] = "LOCATION";
            invoker::get().type_structures["LOCATION"] = structure;
        }
        else if (step == "script_type") {
            invoker::get().type_map[structure.first] = "SCRIPT";
            invoker::get().type_structures["SCRIPT"] = structure;
        }
        else if (step == "side_type") {
            invoker::get().type_map[structure.first] = "SIDE";
            invoker::get().type_structures["SIDE"] = structure;
        }
        else if (step == "text_type") {
            invoker::get().type_map[structure.first] = "TEXT";
            invoker::get().type_structures["TEXT"] = structure;
        }
        else if (step == "team_type") {
            invoker::get().type_map[structure.first] = "TEAM_MEMBER";
            invoker::get().type_structures["TEAM_MEMBER"] = structure;
        }
        else if (step == "namespace_type") {
            invoker::get().type_map[structure.first] = "NAMESPACE";
            invoker::get().type_structures["NAMESPACE"] = structure;
        }

        return _register_hook_trampoline(sqf_this_, sqf_game_state_, right_arg_);
    }

}