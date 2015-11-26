#include "invoker.hpp"
#include "controller.hpp"

namespace intercept {
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

        }
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
        int player = invoke_raw("player");
        int pos = invoke_raw("getpos", player);
        pos = *(uint32_t *)(pos + 4);
        pos = *(uint32_t *)(pos + 12);
        float x = *(float *)((*(uint32_t *)(pos + 0 + 4)) + 12);
        float y = *(float *)((*(uint32_t *)(pos + 8 + 4)) + 12);
        float z = *(float *)((*(uint32_t *)(pos + 16 + 4)) + 12);
        LOG(DEBUG) << "Player Pos: [" << x << "," << y << "," << z << "]";
        return true;
    }

    int invoker::invoke_raw(std::string function_name_)
    {
        nular_function function;
        if (loader::get().get_function(function_name_, function)) {
            return function(_sqf_this, _sqf_game_state);
        }
        return 0;
    }

    int invoker::invoke_raw(std::string function_name_, int right)
    {
        unary_function function;
        if (loader::get().get_function(function_name_, function)) {
            return function(_sqf_this, _sqf_game_state, right);
        }
        return 0;
    }

    int invoker::invoke_raw(std::string function_name_, int left, int right)
    {
        binary_function function;
        if (loader::get().get_function(function_name_, function)) {
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