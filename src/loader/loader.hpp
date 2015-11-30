#pragma once
#include "shared.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"
#include "types.hpp"
#include <unordered_set>

using namespace intercept::rv_types;

namespace intercept {
    class loader
        : public singleton<loader>
    {
    public:
        loader();
        ~loader();

        void attach_controller();

        
       

        bool get_function(std::string function_name_, unary_function &function_);
        bool get_function(std::string function_name_, unary_function & function_, std::string arg_signature_);

        bool get_function(std::string function_name_, binary_function &function_);
        bool get_function(std::string function_name_, binary_function &function_, std::string arg1_signature_, std::string arg2_signature_);

        bool get_function(std::string function_name_, nular_function &function_);

        bool hook_function(std::string function_name_, void *hook_, unary_function &trampoline_);
        bool hook_function(std::string function_name_, void *hook_, binary_function &trampoline_);
        bool hook_function(std::string function_name_, void *hook_, nular_function &trampoline_);

        bool unhook_function(std::string function_name_, void *hook_, unary_function &trampoline_);
        bool unhook_function(std::string function_name_, void *hook_, binary_function &trampoline_);
        bool unhook_function(std::string function_name_, void *hook_, nular_function &trampoline_);


        /*
        Controller Functions
        */
        bool init_patch(const arguments &_args, std::string & result);
        bool remove_patch(const arguments &_args, std::string & result);

        

    protected:
        
        void _find_locs(HANDLE process, std::string const pattern, std::vector<unsigned char *> &output);
        void _find_locs_ptr(HANDLE process, char *find, std::vector<unsigned char *> &output);
        bool _find_initial_function(std::pair<std::string, uintptr_t> &func_map);

        bool _hook(void *hook_, void **trampoline_, void * original_function_);
        bool _unhook(void *hook_, void **trampoline_, void * original_function_);

        
        static int __cdecl _initial_patch(char *a, int b, int c);
        static unary_function _initial_trampoline;
        void _do_function_walk(uintptr_t state_addr_);

        

        bool _attached;
        bool _patched;

        std::unordered_set<uint32_t> _hooked_functions;

        std::unordered_map<std::string, std::vector<unary_entry>> _unary_operators;
        std::unordered_map<std::string, std::vector<binary_entry>> _binary_operators;
        std::unordered_map<std::string, std::vector<nular_entry>> _nular_operators;
    };
}