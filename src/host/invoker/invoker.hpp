#pragma once
#include "shared.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"
#include "loader.hpp"
#include "shared\types.hpp"
#include <mutex>
#include <condition_variable>
#include <queue>


using namespace intercept::types;

namespace intercept {
    typedef uintptr_t value_type;
    class invoker
        : public singleton<invoker>
    {
    public:
        invoker();
        ~invoker();

        void attach_controller();
        void allow_access();
        void deny_access();

        bool invoker_begin_register(const arguments & args_, std::string & result_);
        bool invoker_register(const arguments & args_, std::string & result_);
        bool invoker_end_register(const arguments & args_, std::string & result_);

        bool do_invoke_period(const arguments & args_, std::string & result_);
        bool init_invoker(const arguments & args_, std::string & result_);
        bool test_invoker(const arguments & args_, std::string & result_);
        bool invoker_demo(const arguments & args_, std::string & result_);

        void invoke_lock_test();

        
        
        rv_game_value invoke_raw(nular_function function_);
        rv_game_value invoke_raw(std::string function_name_);
        
        rv_game_value invoke_raw(unary_function function_, game_value * right_);
        rv_game_value invoke_raw(std::string function_name_, game_value *right_);
        rv_game_value invoke_raw(std::string function_name_, game_value *right_, std::string right_type_);
        
        rv_game_value invoke_raw(binary_function function_, game_value * left_, game_value * right_);
        rv_game_value invoke_raw(std::string function_name_, game_value *left_, game_value *right_);
        rv_game_value invoke_raw(std::string function_name_, game_value *left_, std::string left_type_, game_value *right_, std::string right_type_);

        const value_type get_type(game_value *value_);

        const std::string get_type_str(game_value *value_);

        bool release_value(game_value * value_);
        bool release_value(game_value * value_, bool immediate_);

        void collect_string(rv_string *str_);


        std::unordered_map<value_type, std::string> type_map;
        std::unordered_map<std::string, std::pair<value_type, value_type>> type_structures;
        uintptr_t game_value_vptr;
    protected:
        std::thread _collection_thread;
        void _string_collector();

        static int __cdecl _state_hook(char *sqf_this_, uintptr_t sqf_game_state_);
        static nular_function _state_hook_trampoline;

        static int __cdecl _register_hook(char *sqf_this_, uintptr_t sqf_game_state_, uintptr_t right_arg_);
        static unary_function _register_hook_trampoline;

        std::string _registration_type;

        game_value _delete_array_ptr;
        game_value _delete_size_zero;
        game_value _delete_size_max;
        uint32_t _delete_index;


        bool _patched;
        bool _attached;
        char *_sqf_this;
        uintptr_t _sqf_game_state;
        
        std::list<rv_string *> _string_collection;

        std::mutex _invoke_mutex;
        std::mutex _state_mutex;
        std::mutex _delete_mutex;
        std::mutex _string_collection_mutex;
        std::condition_variable _invoke_condition;
        
        std::vector<std::thread> _demo_threads;
    };
}