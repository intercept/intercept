#include "invoker.hpp"
#include "controller.hpp"
#include "extensions.hpp"
#include "shared\client_types.hpp"

namespace intercept {
    game_data_string_pool<> invoker::string_pool;

    /*!
    @brief Flag for when the invoker is able to access the RV Engine
    */
    bool invoker_accessible = false;
    bool invoker_accessible_all = false;

    void threaded_invoke_demo() {
        while (true) {
            const types::object player = invoker::get().invoke_raw("player");
            game_value tick_time = invoker::get().invoke_raw("diag_ticktime");

            game_value oops(player);

            std::vector<game_value> test = { player };
            game_value args = game_value({
                "Testers: %1 %2",
                player,
                tick_time
            });
            game_value message = invoker::get().invoke_raw("format", &args, "ARRAY");
            invoker::get().invoke_raw("sidechat", &player, "OBJECT", &message, "STRING");

            Sleep(10);
        }
    }

    unary_function invoker::_register_hook_trampoline = NULL;
    uintptr_t invoker::sqf_game_state = NULL;
    char * invoker::sqf_this = NULL;

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
            controller::get().add("rv_event", std::bind(&intercept::invoker::rv_event, this, std::placeholders::_1, std::placeholders::_2));
            eventhandlers::get().initialize();
        }
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
        {
            _invoker_unlock period_lock(this, true);
            long timeout = clock() + 3;
            while (clock() < timeout) continue;
        }
        {
            _invoker_unlock on_frame_lock(this);
            // do the per-frame handler here.
            for (auto module : extensions::get().modules()) {
                if (module.second.functions.on_frame) {
                    module.second.functions.on_frame();
                }
            }
        }
        {
            std::lock_guard<std::mutex> delete_lock(_delete_mutex);
            if (_to_delete.size() > 100) {
                for (uint32_t index = 0; index < 100; ++index) {
                    ((rv_game_value *)_delete_array_ptr[index])->__vptr = rv_game_value::__vptr_def;
                    ((rv_game_value *)_delete_array_ptr[index])->data = _to_delete.front();
                    _to_delete.pop();
                }
                _invoker_unlock delete_invoke_lock(this);
                invoke_delete();
            }
        }
        return true;
    }

    bool invoker::rv_event(const arguments & args_, std::string & result_)
    {
        std::string event_name = args_.as_string(0);
        uint32_t var_index = 0;
        if (args_.size() > 1)
            var_index = args_.as_uint32(1);
        LOG(DEBUG) << "EH " << event_name << " START";
        auto handler = _eventhandlers.find(event_name);
        if (handler != _eventhandlers.end()) {
            bool all = false;
            // If we are stopping a mission it is assumed that threads will be
            // stopped and joined here. Deadlocks can occur if we do not open up
            // the invoker to all threads.
            if (event_name == "mission_stopped")
                all = true;
            _invoker_unlock eh_lock(this, all);
            //game_value params = invoke_raw_nolock(_get_variable_func, &_mission_namespace, &var_name);
            handler->second(event_name, _eh_params[var_index]);
            LOG(DEBUG) << "EH " << event_name << " END";
            return true;
        }
        return false;
    }

    bool invoker::init_invoker(const arguments & args_, std::string & result_)
    {
        game_value delete_ptr_name = "INVOKER_DELETE_ARRAY";
        _eh_params_name = "intercept_params_var";
        _invoker_unlock init_lock(this);
        _mission_namespace = invoke_raw("missionnamespace");
        loader::get().get_function("getvariable", _get_variable_func, "NAMESPACE", "STRING");
        _delete_array_ptr = invoke_raw_nolock(_get_variable_func, &_mission_namespace, &delete_ptr_name);
        _eh_params = invoke_raw_nolock(_get_variable_func, &_mission_namespace, &_eh_params_name);
        _delete_size_zero = game_value(0.0f);
        _delete_size_max = game_value(1000.0f);
        return true;
    }

    bool invoker::test_invoker(const arguments & args_, std::string & result_)
    {
        _invoker_unlock test_lock(this);
        result_ = "-1";
        game_value res = invoke_raw("profilenamesteam");
        result_ = res;
        return true;
    }

    /*
    DO NOT EXECUTE THIS VIA A BLOCKING CALL EXTENSION!
    */
    bool invoker::invoker_demo(const arguments & args_, std::string & result_)
    {
        result_ = "1";
        _demo_threads.push_back(std::thread(threaded_invoke_demo));
        LOG(INFO) << "Started Demo Thread #" << _demo_threads.size();
        return true;
    }

    rv_game_value invoker::invoke_raw(nular_function function_)
    {
        std::unique_lock<std::mutex> lock(_state_mutex);
        _invoke_condition.wait(lock, [] {return invoker_accessible;});
        std::lock_guard<std::recursive_mutex> invoke_lock(_invoke_mutex);
        uintptr_t ret_ptr = function_(_sqf_this, _sqf_game_state);
        rv_game_value ret;
        ret.__vptr = *(uintptr_t *)ret_ptr;
        ret.data = (game_data *)*(uintptr_t *)(ret_ptr + 4);
        return ret;
    }

    rv_game_value invoker::invoke_raw_nolock(nular_function function_)
    {
        uintptr_t ret_ptr = function_(_sqf_this, _sqf_game_state);
        rv_game_value ret;
        ret.__vptr = *(uintptr_t *)ret_ptr;
        ret.data = (game_data *)*(uintptr_t *)(ret_ptr + 4);
        return ret;
    }

    void invoker::invoke_delete()
    {
        binary_function function;
        if (loader::get().get_function("resize", function)) {
            std::unique_lock<std::mutex> lock(_state_mutex);
            _invoke_condition.wait(lock, [] {return invoker_accessible;});
            std::lock_guard<std::recursive_mutex> invoke_lock(_invoke_mutex);
            LOG(DEBUG) << "FLUSHING MEMORY";
            function(_sqf_this, _sqf_game_state, (uintptr_t)&_delete_array_ptr, (uintptr_t)&_delete_size_zero);
            function(_sqf_this, _sqf_game_state, (uintptr_t)&_delete_array_ptr, (uintptr_t)&_delete_size_max);
        }
    }

    rv_game_value invoker::invoke_raw(std::string function_name_)
    {
        nular_function function;
        if (loader::get().get_function(function_name_, function)) {
            return invoke_raw(function);
        }
        return rv_game_value();
    }

    rv_game_value invoker::invoke_raw(unary_function function_, const game_value *right_)
    {
        std::unique_lock<std::mutex> lock(_state_mutex);
        _invoke_condition.wait(lock, [] {return invoker_accessible;});
        std::lock_guard<std::recursive_mutex> invoke_lock(_invoke_mutex);
        uintptr_t ret_ptr = function_(_sqf_this, _sqf_game_state, (uintptr_t)right_);
        rv_game_value ret;
        ret.__vptr = *(uintptr_t *)ret_ptr;
        ret.data = (game_data *)*(uintptr_t *)(ret_ptr + 4);
        return ret;
    }

    rv_game_value invoker::invoke_raw_nolock(unary_function function_, const game_value *right_)
    {
        uintptr_t ret_ptr = function_(_sqf_this, _sqf_game_state, (uintptr_t)right_);
        rv_game_value ret;
        ret.__vptr = *(uintptr_t *)ret_ptr;
        ret.data = (game_data *)*(uintptr_t *)(ret_ptr + 4);
        return ret;
    }

    rv_game_value invoker::invoke_raw(std::string function_name_, const game_value * right_, std::string right_type_)
    {
        unary_function function;
        if (loader::get().get_function(function_name_, function, right_type_)) {
            return invoke_raw(function, right_);
        }
        return rv_game_value();
    }

    rv_game_value invoker::invoke_raw(std::string function_name_, const game_value *right_)
    {
        unary_function function;
        if (loader::get().get_function(function_name_, function)) {
            return invoke_raw(function, right_);
        }
        return rv_game_value();
    }

    rv_game_value invoker::invoke_raw(binary_function function_, const game_value *left_, const game_value *right_)
    {
        std::unique_lock<std::mutex> lock(_state_mutex);
        _invoke_condition.wait(lock, [] {return invoker_accessible;});
        std::lock_guard<std::recursive_mutex> invoke_lock(_invoke_mutex);
        uintptr_t ret_ptr = function_(_sqf_this, _sqf_game_state, (uintptr_t)left_, (uintptr_t)right_);
        rv_game_value ret;
        ret.__vptr = *(uintptr_t *)ret_ptr;
        ret.data = (game_data *)*(uintptr_t *)(ret_ptr + 4);
        return ret;
    }

    rv_game_value invoker::invoke_raw_nolock(binary_function function_, const game_value *left_, const game_value *right_)
    {
        uintptr_t ret_ptr = function_(_sqf_this, _sqf_game_state, (uintptr_t)left_, (uintptr_t)right_);
        rv_game_value ret;
        ret.__vptr = *(uintptr_t *)ret_ptr;
        ret.data = (game_data *)*(uintptr_t *)(ret_ptr + 4);
        return ret;
    }

    rv_game_value invoker::invoke_raw(std::string function_name_, const game_value *left_, const game_value *right_)
    {
        binary_function function;
        if (loader::get().get_function(function_name_, function)) {
            return invoke_raw(function, left_, right_);
        }
        return rv_game_value();
    }

    rv_game_value invoker::invoke_raw(std::string function_name_, const game_value * left_, std::string left_type_, const game_value * right_, std::string right_type_)
    {
        binary_function function;
        if (loader::get().get_function(function_name_, function, left_type_, right_type_)) {
            return invoke_raw(function, left_, right_);
        }
        return rv_game_value();
    }

    value_type invoker::get_type(const game_value *value_) const
    {
        return value_->type();
    }

    const std::string invoker::get_type_str(const game_value *value_) const
    {
        auto type = value_->type();
        return type_map.at(type);
    }

    bool invoker::release_value(game_value *value_, bool immediate_) {
        if (!value_->client_owned()) {
            std::lock_guard<std::mutex> delete_lock(_delete_mutex);
            _to_delete.push(value_->rv_data.data);
            /*
            // We do not need a deep copy here, so we cast to the internal data type, and just copy the ptr.
            // The game_value destructor should set this pointer to null after, so it is effectively deleted
            // in the context of the passed objects lifespan, but the memory remains until we free it in the
            // RV engine itself later.
            //LOG(DEBUG) << "Adding delete...";
            ((rv_game_value *)_delete_array_ptr[_delete_index])->data = ((rv_game_value *)value_)->data;
            ((rv_game_value *)_delete_array_ptr[_delete_index])->__vptr = ((rv_game_value *)value_)->__vptr;
            //LOG(DEBUG) << "Ptr: " << ((rv_game_value *)value_)->data->type << " <-> " << ((rv_game_value *)_delete_array_ptr[_delete_index])->data->type;
            _delete_index++;
            if (_delete_index >= 1000 || immediate_) {
                //LOG(DEBUG) << "Flushing Memory...";
                invoke_delete();
                _delete_index = 0;
            }
            */
            return true;
        }
        return false;
    }


    int invoker::_register_hook(char *sqf_this_, uintptr_t sqf_game_state_, uintptr_t right_arg_)
    {
        LOG(INFO) << "Registration Hook Function Called: " << invoker::get()._registration_type;
        auto step = invoker::get()._registration_type;
        invoker::get()._sqf_game_state = sqf_game_state_;
        sqf_game_state = sqf_game_state_;
        invoker::get()._sqf_this = sqf_this_;
        sqf_this = sqf_this_;

        std::pair<value_type, value_type> gv_structure;

        rv_game_value::__vptr_def = *(uintptr_t *)right_arg_;
        gv_structure.first = rv_game_value::__vptr_def;
        gv_structure.second = rv_game_value::__vptr_def;
        invoker::get().type_structures["GV"] = gv_structure;

        std::pair<value_type, value_type> structure;
        structure.first = *(uintptr_t *)(*(uintptr_t *)(right_arg_ + 4));
        structure.second = *(uintptr_t *)((*(uintptr_t *)(right_arg_ + 4)) + 8);
        if (step == "delete_ptr") {
            LOG(INFO) << "Assigned Delete Ptr";
            invoker::get().type_map[structure.first] = "ARRAY";
            invoker::get().type_structures["ARRAY"] = structure;
            game_data_array::type_def = structure.first;
            game_data_array::data_type_def = structure.second;
            //invoker::get()._delete_array_ptr = game_value(right_arg_);
            
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
            game_data_rv_text::type_def = structure.first;
            game_data_rv_text::data_type_def = structure.second;
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
            game_data_rv_namespace::type_def = structure.first;
            game_data_rv_namespace::data_type_def = structure.second;
        }
        

        return _register_hook_trampoline(sqf_this_, sqf_game_state_, right_arg_);
    }

    bool invoker::add_eventhandler(const std::string & name_, std::function<void(const std::string&, game_value&)> func_) {
        if (_eventhandlers.find(name_) != _eventhandlers.end()) {
            // @TODO: Exceptions
            return false;
        }
        _eventhandlers[name_] = func_;

        return true;
    }

    void invoker::lock() {
        std::unique_lock<std::mutex> lock(_state_mutex);
        _invoke_condition.wait(lock, [] {return invoker_accessible_all;});
        _invoke_mutex.lock();
        LOG(DEBUG) << "Client Thread ACQUIRE EXCLUSIVE";
    }

    void invoker::unlock() {
        _invoke_mutex.unlock();
        LOG(DEBUG) << "Client Thread RELEASE EXCLUSIVE";
    }

    invoker::_invoker_unlock::_invoker_unlock(invoker * instance_, bool all_threads_, bool delayed_) : _all(all_threads_), _instance(instance_), _unlocked(false) {
        if (!delayed_) {
            unlock();
        }
    }

    invoker::_invoker_unlock::~_invoker_unlock() {
        if (_unlocked) {
            std::lock_guard<std::mutex> lock(_instance->_state_mutex);
            if (_all) {
                std::lock_guard<std::recursive_mutex> invoke_lock(_instance->_invoke_mutex);
                invoker_accessible = false;
                invoker_accessible_all = false;
                LOG(DEBUG) << "LOCKED ALL";
            }
            else {
                invoker_accessible = false;
                LOG(DEBUG) << "LOCKED";
            }
            
        }
    }

    void invoker::_invoker_unlock::unlock() {
        if (!_unlocked) {
            if (_all) {
                LOG(DEBUG) << "UNLOCKING ALL";
                std::unique_lock<std::recursive_mutex> invoke_lock(_instance->_invoke_mutex, std::defer_lock);
                {
                    std::lock_guard<std::mutex> lock(_instance->_state_mutex);
                    invoke_lock.lock();
                    invoker_accessible = true;
                    invoker_accessible_all = true;
                }
                _instance->_invoke_condition.notify_all();
            }
            else {
                LOG(DEBUG) << "UNLOCKING";
                std::lock_guard<std::mutex> lock(_instance->_state_mutex);
                invoker_accessible = true;
            }
            _unlocked = true;
        }
    }
}