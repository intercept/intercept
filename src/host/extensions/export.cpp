#include "export.hpp"
#include "invoker.hpp"


namespace intercept {
    namespace client_function_defs {
        rv_game_value invoke_raw_nular(nular_function function_) {
            return intercept::invoker::get().invoke_raw(function_);
        }

        rv_game_value invoke_raw_nular_nolock(nular_function function_)
        {
            //@TODO: Yea, there should be some sort of transparent indirection (as in it compiles out the function call) to the invoker,
            //but for right now there is not, so this will have to do.
            //stopwatch<> timer;
            uintptr_t ret_ptr = function_(invoker::sqf_this, invoker::sqf_game_state);
            //double time = timer.stop();
            //LOG(INFO) << "Raw nular call time: " << time << " microseconds.";
            rv_game_value ret;
            ret.__vptr = *(uintptr_t *)ret_ptr;
            ret.data = (game_data *)*(uintptr_t *)(ret_ptr + 4);
            if(ret.data)
                ret.data->ref_count_internal.set_initial((uint16_t)ret.data->ref_count_internal.current_count--, false);
            return ret;
        }

        rv_game_value invoke_raw_unary(unary_function function_, const game_value &right_arg_) {
            return intercept::invoker::get().invoke_raw(function_, &right_arg_);
        }

        rv_game_value invoke_raw_unary_nolock(unary_function function_, const game_value & right_arg_)
        {
            //@TODO: Yea, there should be some sort of transparent indirection (as in it compiles out the function call) to the invoker,
            //but for right now there is not, so this will have to do.
            //stopwatch<> timer;
            uintptr_t ret_ptr = function_(invoker::sqf_this, invoker::sqf_game_state, (uintptr_t)&right_arg_);
            //double time = timer.stop();
            //LOG(INFO) << "Raw unary call time: " << time << " microseconds.";
            rv_game_value ret;
            ret.__vptr = *(uintptr_t *)ret_ptr;
            ret.data = (game_data *)*(uintptr_t *)(ret_ptr + 4);
            if (ret.data)
                ret.data->ref_count_internal.set_initial((uint16_t)ret.data->ref_count_internal.current_count--, false);
            return ret;
        }

        rv_game_value invoke_raw_binary(binary_function function_, const game_value &left_arg_, const game_value &right_arg_) {
            return intercept::invoker::get().invoke_raw(function_, &left_arg_, &right_arg_);
        }

        rv_game_value invoke_raw_binary_nolock(binary_function function_, const game_value & left_arg_, const game_value & right_arg_)
        {
            //@TODO: Yea, there should be some sort of transparent indirection (as in it compiles out the function call) to the invoker,
            //but for right now there is not, so this will have to do.
            //stopwatch<> timer;
            uintptr_t ret_ptr = function_(invoker::sqf_this, invoker::sqf_game_state, (uintptr_t)&left_arg_, (uintptr_t)&right_arg_);
            //double time = timer.stop();
            //LOG(INFO) << "Raw binary call time: " << time << " microseconds.";
            rv_game_value ret;
            ret.__vptr = *(uintptr_t *)ret_ptr;
            ret.data = (game_data *)*(uintptr_t *)(ret_ptr + 4);
            if (ret.data)
                ret.data->ref_count_internal.set_initial((uint16_t)ret.data->ref_count_internal.current_count--, false);
            return ret;
        }

        void get_type_structure(const char *type_name_, uintptr_t &type_def_, uintptr_t &data_type_def_) {
            auto structure = invoker::get().type_structures[std::string(type_name_)];
            type_def_ = structure.first;
            data_type_def_ = structure.second;
        }

        rv_string * allocate_string(size_t size_) {
            return invoker::string_pool.acquire(size_);
        }

        void free_string(rv_string *value_) {
            invoker::string_pool.release(value_);
        }

        void free_value(game_value *value_) {
            intercept::invoker::get().release_value(value_);
        }

        nular_function get_nular_function(const char *function_name_) {
            nular_function function;
            if (intercept::loader::get().get_function(std::string(function_name_), function)) {
                return function;
            }
            return NULL;
        }

        unary_function get_unary_function(const char *function_name_) {
            unary_function function;
            if (intercept::loader::get().get_function(std::string(function_name_), function)) {
                return function;
            }
            return NULL;
        }

        unary_function get_unary_function_typed(const char *function_name_, const char *right_arg_type_) {
            unary_function function;
            if (intercept::loader::get().get_function(std::string(function_name_), function, std::string(right_arg_type_))) {
                return function;
            }
            return NULL;
        }

        binary_function get_binary_function(const char *function_name_) {
            binary_function function;
            if (intercept::loader::get().get_function(std::string(function_name_), function)) {
                return function;
            }
            return NULL;
        }

        binary_function get_binary_function_typed(const char *function_name_, const char *left_arg_type_, const char *right_arg_type_) {
            binary_function function;
            if (intercept::loader::get().get_function(std::string(function_name_), function, std::string(left_arg_type_), std::string(right_arg_type_))) {
                return function;
            }
            return NULL;
        }

        void invoker_lock()
        {
            invoker::get().lock();
        }

        void invoker_unlock()
        {
            invoker::get().unlock();
        }
    }
}