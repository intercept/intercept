#pragma once
#include "shared.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"
#include "loader.hpp"
#include "types.hpp"
#include <mutex>
#include <condition_variable>
#include <queue>


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

        
        
        const rv_game_value invoke_raw(nular_function function_);
        const rv_game_value invoke_raw(std::string function_name_);
        
        const rv_game_value invoke_raw(unary_function function_, rv_game_value * right_);
        const rv_game_value invoke_raw(std::string function_name_, rv_game_value *right_);
        const rv_game_value invoke_raw(std::string function_name_, rv_game_value *right_, std::string right_type_);
        
        const rv_game_value invoke_raw(binary_function function_, rv_game_value * left_, rv_game_value * right_);
        const rv_game_value invoke_raw(std::string function_name_, rv_game_value *left_, rv_game_value *right_);
        const rv_game_value invoke_raw(std::string function_name_, rv_game_value *left_, std::string left_type_, rv_game_value *right_, std::string right_type_);

        const value_type get_type(rv_game_value *value_);

        const std::string get_type_str(rv_game_value *value_);

        bool release_value(rv_game_value * value_);
        bool release_value(rv_game_value * value_, bool immediate_);

        template<typename Type>
        rv_game_value create_type() {
            Type val_factory;
            rv_game_value new_val = val_factory.factory();
            new_val.data->ref_count_internal = 0x0000dede;
            return new_val;
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

        rv_game_value _delete_array_ptr;
        rv_game_value _delete_size_zero;
        rv_game_value _delete_size_max;
        uint32_t _delete_index;


        bool _patched;
        bool _attached;
        char *_sqf_this;
        uintptr_t _sqf_game_state;
        
        std::mutex _invoke_mutex;
        std::mutex _state_mutex;
        std::mutex _delete_mutex;
        std::condition_variable _invoke_condition;

        std::list<rv_game_value> _free_queue;
        
        std::vector<std::thread> _demo_threads;
    };
    namespace invoker_type {
        class invoker_factory_base {
        public:
            virtual rv_game_value factory() = 0;
        };

        class scalar : public invoker_factory_base {
        public:
            rv_game_value factory() {
                rv_game_value new_number;
                new_number.__vptr = invoker::get().game_value_vptr;
                new_number.data = new game_data_number();
                new_number.data->type = invoker::get().type_structures["SCALAR"].first;
                new_number.data->data_type = invoker::get().type_structures["SCALAR"].second;
                ((game_data_number *)new_number.data)->number = 0.0f;

                return new_number;
            }
        };

        class string : public invoker_factory_base {
        public:
            rv_string * make_compact() {
                char *raw_data = new char[sizeof(uint32_t) + sizeof(uint32_t) + 2048];
                ((rv_string *)raw_data)->length = 2048;
                ((rv_string *)raw_data)->ref_count_internal = 1;
                return (rv_string *)raw_data;
            }
            rv_game_value factory() {
                rv_game_value new_string;
                new_string.__vptr = invoker::get().game_value_vptr;
                new_string.data = new game_data_string();
                new_string.data->type = invoker::get().type_structures["STRING"].first;
                new_string.data->data_type = invoker::get().type_structures["STRING"].second;
                ((game_data_string *)new_string.data)->raw_string = make_compact();
                return new_string;
            }
        };

        class array : public invoker_factory_base {
        public:
            rv_game_value factory() {
                rv_game_value new_array;
                new_array.__vptr = invoker::get().game_value_vptr;
                new_array.data = new game_data_array();
                new_array.data->type = invoker::get().type_structures["ARRAY"].first;
                new_array.data->data_type = invoker::get().type_structures["ARRAY"].second;
                return new_array;
            }
        };
    }
}