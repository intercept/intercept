#pragma once
#include "shared.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"
#include "loader.hpp"
#include "types.hpp"
#include <mutex>
#include <condition_variable>


using namespace intercept::rv_types;

namespace intercept {
    class invoker
        : public singleton<invoker>
    {
    public:
        invoker();
        ~invoker();

        void attach_controller();
        void allow_access();
        void deny_access();
        bool do_invoke_period(const arguments & args_, std::string & result_);
        bool init_invoker(const arguments & args_, std::string & result_);
        bool test_invoker(const arguments & args_, std::string & result_);
        bool invoker_demo(const arguments & args_, std::string & result_);

        

        const int invoke_raw(std::string function_name_);
        const int invoke_raw(std::string function_name_, int right);
        const int invoke_raw(std::string function_name_, int left, int right);
        
    protected:
        static int __cdecl _state_hook(char *sqf_this_, int sqf_game_state_);
        static nular_function _state_hook_trampoline;

        bool _patched;
        bool _attached;
        char *_sqf_this;
        int _sqf_game_state;
        std::mutex _invoke_mutex;
        std::mutex _state_mutex;
        std::condition_variable _invoke_condition;
        
        std::vector<std::thread> _demo_threads;
    };
}