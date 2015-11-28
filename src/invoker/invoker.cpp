#include "invoker.hpp"
#include "controller.hpp"

namespace intercept {

    bool invoker_accessisble = false;

    void threaded_invoke_demo() {
        while (true) {
            game_value player = invoker::get().invoke_raw("player");
            invoker::get().release_value(&player);
            /*
            game_value pos_val = invoker::get().invoke_raw("getpos", &player);
            game_data_array *pos = (game_data_array *)pos_val.data;



            float x = ((game_data_number *)pos->data[0].data)->number;
            float y = ((game_data_number *)pos->data[1].data)->number;
            float z = ((game_data_number *)pos->data[2].data)->number;
            

            LOG(DEBUG) << "Thread ID " << std::this_thread::get_id() << " Player Pos: [" << x << "," << y << "," << z << "]";
            */
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
            _delete_size = create_type<invoker_type::number>();
        }
        else {
            LOG(INFO) << "Registration function failed to unhook.";
        }
        return true;
    }

    bool invoker::do_invoke_period(const arguments & args_, std::string & result_)
    {
        allow_access();
        long timeout = clock() + 3;
        while (clock() < timeout) continue;
        deny_access();
        return true;
    }

    bool invoker::init_invoker(const arguments & args_, std::string & result_)
    {
        bool patched = loader::get().hook_function("cadetmode", _state_hook, _state_hook_trampoline);
        if (patched) {
            LOG(INFO) << "Invoker has attached itself.";
            _patched = true;
            result_ = "1";
        }
        else {
            LOG(ERROR) << "Invoker has FAILED to attach itself.";
            result_ = "-1";
        }
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

    const game_value invoker::invoke_raw(std::string function_name_)
    {
        nular_function function;
        if (loader::get().get_function(function_name_, function)) {
            std::unique_lock<std::mutex> lock(_state_mutex);
            _invoke_condition.wait(lock, [] {return invoker_accessisble;});
            std::lock_guard<std::mutex> invoke_lock(_invoke_mutex);
            uintptr_t return_address = function(_sqf_this, _sqf_game_state);
            game_value return_value;
            return_value.__vptr = *(uintptr_t *)return_address;
            return_value.data = (game_data *)*(uintptr_t *)(return_address + 4);

            return return_value;
        }
        return game_value();
    }

    const game_value invoker::invoke_raw(std::string function_name_, game_value *right)
    {
        unary_function function;
        if (loader::get().get_function(function_name_, function)) {
            std::unique_lock<std::mutex> lock(_state_mutex);
            _invoke_condition.wait(lock, [] {return invoker_accessisble;});
            std::lock_guard<std::mutex> invoke_lock(_invoke_mutex);
            uintptr_t return_address = function(_sqf_this, _sqf_game_state, (uintptr_t)right);
            game_value return_value;
            return_value.__vptr = *(uintptr_t *)return_address;
            return_value.data = (game_data *)*(uintptr_t *)(return_address + 4);
            return return_value;
        }
        return game_value();
    }

    const game_value invoker::invoke_raw(std::string function_name_, game_value *left, game_value *right)
    {
        binary_function function;
        if (loader::get().get_function(function_name_, function)) {
            std::unique_lock<std::mutex> lock(_state_mutex);
            _invoke_condition.wait(lock, [] {return invoker_accessisble;});
            std::lock_guard<std::mutex> invoke_lock(_invoke_mutex);
            uintptr_t return_address = function(_sqf_this, _sqf_game_state, (uintptr_t)left, (uintptr_t)right);
            game_value return_value;
            return_value.__vptr = *(uintptr_t *)return_address;
            return_value.data = (game_data *)*(uintptr_t *)(return_address + 4);
            return return_value;
        }
        return game_value();
    }

    const value_type invoker::get_type(game_value value_)
    {
        return value_type();
    }

    void invoker::release_value(game_value *value) {
        release_value(value, false);
    }

    void invoker::release_value(game_value *value, bool immediate_) {
        game_data_array *value_array = (game_data_array *)_delete_array_ptr.data;
        value_array->data[_delete_index++] = *value;
        if (_delete_index >= 100 || immediate_) {
            _delete_index = 0;
            LOG(DEBUG) << "Flushing Memory...";
            ((game_data_number *)_delete_size.data)->number = 0.0f;
            invoke_raw("resize", &_delete_array_ptr, &_delete_size);
            ((game_data_number *)_delete_size.data)->number = 100.0f;
            invoke_raw("resize", &_delete_array_ptr, &_delete_size);
        }
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
            invoker::get().type_map[structure.first] = "NUMBER";
            invoker::get().type_structures["NUMBER"] = structure;
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
        return _register_hook_trampoline(sqf_this_, sqf_game_state_, right_arg_);
    }

}