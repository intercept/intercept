#include "invoker.hpp"
#include "controller.hpp"

namespace intercept {

    bool invoker_accessisble = false;

    void threaded_invoke_demo() {
        while (true) {
            int player = invoker::get().invoke_raw("player");
            /*
            int pos = invoker::get().invoke_raw("getpos", player);
            pos = *(uint32_t *)(pos + 4);
            pos = *(uint32_t *)(pos + 12);
            float x = *(float *)((*(uint32_t *)(pos + 0 + 4)) + 12);
            float y = *(float *)((*(uint32_t *)(pos + 8 + 4)) + 12);
            float z = *(float *)((*(uint32_t *)(pos + 16 + 4)) + 12);
            LOG(DEBUG) << "Thread ID " << std::this_thread::get_id() << " Player Pos: [" << x << "," << y << "," << z << "]";
            */
            Sleep(10);
        }
    }

    nular_function invoker::_state_hook_trampoline = NULL;

    invoker::invoker() : _attached(false), _patched(false)
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
            controller::get().add("open_invoke_period", std::bind(&intercept::invoker::open_invoke_period, this, std::placeholders::_1, std::placeholders::_2));
            controller::get().add("close_invoke_period", std::bind(&intercept::invoker::close_invoke_period, this, std::placeholders::_1, std::placeholders::_2));

        }
    }

    bool invoker::open_invoke_period(const arguments & args_, std::string & result_) {
        allow_access();
        return true;
    }

    bool invoker::close_invoke_period(const arguments & args_, std::string & result_) {
        deny_access();
        return false;
    }

    void invoker::allow_access() {
        {
            std::lock_guard<std::mutex> lock(_state_mutex);
            invoker_accessisble = true;
        }
        _invoke_condition.notify_all();
    }

    void invoker::deny_access() {
        std::lock_guard<std::mutex> lock(_state_mutex);
        invoker_accessisble = false;
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
        int res = invoke_raw("profilenamesteam");
        if (res) {
            res = res + 4;
            res = *(uint32_t *)res;
            res = res + 12;
            res = *(uint32_t *)res;
            res = res + 8;
            result_ = std::string((char *)res);
        }
        return true;
    }

    bool invoker::invoker_demo(const arguments & args_, std::string & result_)
    {
        result_ = "1";
        _demo_threads.push_back(std::thread(threaded_invoke_demo));
        return true;
    }

    const int invoker::invoke_raw(std::string function_name_)
    {
        nular_function function;
        if (loader::get().get_function(function_name_, function)) {
            std::unique_lock<std::mutex> lock(_state_mutex);
            _invoke_condition.wait(lock, [] {return invoker_accessisble;});
            std::lock_guard<std::mutex> invoke_lock(_invoke_mutex);
            int return_val = function(_sqf_this, _sqf_game_state);
            return return_val;
        }
        return 0;
    }

    const int invoker::invoke_raw(std::string function_name_, int right)
    {
        unary_function function;
        if (loader::get().get_function(function_name_, function)) {
            std::unique_lock<std::mutex> lock(_state_mutex);
            _invoke_condition.wait(lock, [] {return invoker_accessisble;});
            std::lock_guard<std::mutex> invoke_lock(_invoke_mutex);
            return function(_sqf_this, _sqf_game_state, right);
        }
        return 0;
    }

    const int invoker::invoke_raw(std::string function_name_, int left, int right)
    {
        binary_function function;
        if (loader::get().get_function(function_name_, function)) {
            std::unique_lock<std::mutex> lock(_state_mutex);
            _invoke_condition.wait(lock, [] {return invoker_accessisble;});
            std::lock_guard<std::mutex> invoke_lock(_invoke_mutex);
            return function(_sqf_this, _sqf_game_state, left, right);
        }
        return 0;
    }
    int invoker::_state_hook(char * sqf_this_, int sqf_game_state_)
    {
        invoker::get()._sqf_this = sqf_this_;
        invoker::get()._sqf_game_state = sqf_game_state_;
        return _state_hook_trampoline(sqf_this_, sqf_game_state_);
    }
}