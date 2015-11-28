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

        
        

        const game_value invoke_raw(std::string function_name_);
        const game_value invoke_raw(std::string function_name_, game_value *right);
        const game_value invoke_raw(std::string function_name_, game_value *left, game_value *right);

        const value_type get_type(game_value value_);

        void release_value(game_value * value);
        void release_value(game_value * value, bool immediate_);

        template<typename Type>
        game_value create_type() {
            Type val_factory;
            return val_factory.factory();
        }

        std::unordered_map<value_type, std::string> type_map;
        std::unordered_map<std::string, std::pair<value_type, value_type>> type_structures;
        uintptr_t game_value_vptr;
    protected:
        static int __cdecl _state_hook(char *sqf_this_, uintptr_t sqf_game_state_);
        static nular_function _state_hook_trampoline;

        static int __cdecl _register_hook(char *sqf_this_, uintptr_t sqf_game_state_, uintptr_t right_arg_);
        static unary_function _register_hook_trampoline;

        std::string _registration_type;

        game_value _delete_array_ptr;
        game_value _delete_size;
        uint32_t _delete_index;


        bool _patched;
        bool _attached;
        char *_sqf_this;
        uintptr_t _sqf_game_state;
        
        std::mutex _invoke_mutex;
        std::mutex _state_mutex;
        std::condition_variable _invoke_condition;
        
        std::vector<std::thread> _demo_threads;
    };
    namespace invoker_type {
        class invoker_factory_base {
        public:
            virtual game_value factory() = 0;
        };

        class number : public invoker_factory_base {
        public:
            game_value factory() {
                game_value new_number;
                new_number.__vptr = invoker::get().game_value_vptr;
                new_number.data = new game_data_number();
                new_number.data->type = invoker::get().type_structures["NUMBER"].first;
                new_number.data->data_type = invoker::get().type_structures["NUMBER"].second;
                ((game_data_number *)new_number.data)->number = 0.0f;

                return new_number;
            }
        };
    }
}