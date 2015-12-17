/*!
@file
@author Nou (korewananda@gmail.com)

@brief Memory searcher and patching functionality to the RV engine.

This is the main patching suit for Intercept. It contains all the functionality
to search for and patch the RV engine. It also does the main memory analysis to
find and catalog the SQF function pointers and store them.

https://github.com/NouberNou/intercept
*/
#pragma once
#include "shared.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"
#include "shared\types.hpp"
#include <unordered_set>

using namespace intercept::types;
/*!
@namespace intercept
@brief The main namespace for all Intercept functionality.

All functionality of Intercept is included in this namespace and broken up into
sub-namespaces. Namespaces that are prefixed with `__` are considered private
and their classes/functions are considered internal and to not be used by anyone
using the API.
*/
namespace intercept {
    //! Nular function map.
    typedef std::unordered_map<std::string, std::vector<nular_entry>> nular_map;
    //! Unary function map.
    typedef std::unordered_map<std::string, std::vector<unary_entry>> unary_map;
    //! Binary functon map.
    typedef std::unordered_map<std::string, std::vector<binary_entry>> binary_map;

    /*!
    @brief The loader class, memory searcher and patching functionality to the RV engine.

    This is the main patching suit for Intercept. It contains all the functionality
    to search for and patch the RV engine. It also does the main memory analysis to
    find and catalog the SQF function pointers and store them.
    */
    class loader
        : public singleton<loader>
    {
    public:
        loader();
        ~loader();

        /*!
        @brief Walks the game state maps of SQF functions and finds their info.

        This walks the internal game state objects maps of SQF functions and then
        gets their comref information, arguement types, and the pointer to the
        actual function and stores them.
        */
        void do_function_walk(uintptr_t state_addr_);
        
        /*!
        @brief Returns a unary SQF function from the loaders library of found SQF functions.
        
        Returns a unary SQF function from the loaders library of found SQF functions.

        @param [in] function_name_ The name of the function, all in lowercase.
        @param [out] function_ A reference variable to the unary function.
        
        @return true if function is found, false if function is not found.

        @todo Throw exception if overloads are found so that unexpected results
        are not encountered.

        @code
        unary_function can_fire;
        bool found = get_function("canfire", can_fire);
        @endcode
        */
        bool get_function(std::string function_name_, unary_function &function_);

        /*!
        @brief Returns a unary SQF function from the loaders library of found 
        SQF functions with argument signature.
        
        Returns a unary SQF function from the loaders library of found SQF functions
        but also takes a argument type in case there are overloaded versions of 
        this SQF command available.

        @param [in] function_name_ The name of the function, all in lowercase.
        @param [out] function_ A reference variable to the unary function.
        @param [in] arg_signature_ The type of variable in SQF that the right 
        argument is. Must be in all caps, "ARRAY", "SCALAR", "BOOL", "OBJECT", etc.

        @return `true` if function is found, `false` if function is not found.

        @code
        unary_function random_function1;
        bool found1 = get_function("random", random_function1, "SCALAR");
        unary_function random_function2;
        bool found2 = get_function("random", random_function2, "ARRAY");
        @endcode
        */
        bool get_function(std::string function_name_, unary_function & function_, std::string arg_signature_);

        /*!
        @brief Returns a binary SQF function from the loaders library of found SQF functions.

        Returns a binary SQF function from the loaders library of found SQF functions.

        @param [in] function_name_ The name of the function, all in lowercase.
        @param [out] function_ A reference variable to the binary function.

        @return `true` if function is found, `false` if function is not found.

        @todo Throw exception if overloads are found so that unexpected results
        are not encountered.

        @code
        binary_function set_pos;
        bool found = get_function("setpos", set_pos);
        @endcode
        */
        bool get_function(std::string function_name_, binary_function &function_);

        /*!
        @brief Returns a binary SQF function from the loaders library of found 
        SQF functions with argument signature.

        Returns a binary SQF function from the loaders library of found SQF functions
        but also takes a argument type in case there are overloaded versions of
        this SQF command available.

        @param [in] function_name_ The name of the function, all in lowercase.
        @param [out] function_ A reference variable to the binary function.
        @param [in] arg1_signature_ The type of variable in SQF that the left
        argument is. Must be in all caps, "ARRAY", "SCALAR", "BOOL", "OBJECT", 
        etc.
        @param [in] arg2_signature_ The type of variable in SQF that the right
        argument is. Must be in all caps, "ARRAY", "SCALAR", "BOOL", "OBJECT", 
        etc.

        @return `true` if function is found, `false` if function is not found.

        @code
        binary_function remove_menu_item1;
        bool found1 = get_function("removemenuitem", remove_menu_item1, "CONTROL", "SCALAR");
        binary_function remove_menu_item2;
        bool found2 = get_function("removemenuitem", remove_menu_item2, "CONTROL", "STRING");
        @endcode
        */
        bool get_function(std::string function_name_, binary_function &function_, std::string arg1_signature_, std::string arg2_signature_);

        /*!
        @brief Returns a nular SQF function from the loaders library of found SQF functions.

        Returns a nular SQF function from the loaders library of found SQF functions.
        There is no version of this function that takes a argument signature because
        there are no possible arguements for these functions and hence no possible
        overloading.

        @param [in] function_name_ The name of the function, all in lowercase.
        @param [out] function_ A reference variable to the binary function.

        @return `true` if function is found, `false` if function is not found.

        @code
        nular_function player;
        bool found = get_function("player", player);
        @endcode
        */
        bool get_function(std::string function_name_, nular_function &function_);

        /*!@{
        @brief Hook a function.

        Hooks a function so that when it is executed in SQF the hooked function
        will execute in its place instead.

        @warning Warning, this will only hook the first function (and in the future 
        raise an exception if there is an overload of this function).

        @param [in] function_name_ The name of the function to hook. 
        @param [in] hook_ A void pointer to the function to call instead.
        @param [out] trampoline_ A reference to the trampoline that stores the 
        original function call.

        @return `true` if the hook succeded, `false` if the hook failed.
        */
        bool hook_function(std::string function_name_, void *hook_, unary_function &trampoline_);
        bool hook_function(std::string function_name_, void *hook_, binary_function &trampoline_);
        bool hook_function(std::string function_name_, void *hook_, nular_function &trampoline_);
        //!@}
        
        /*!@{
        @brief Unhook a unary function.

        Unhooks an already hooked functon. You must pass in the name, original 
        hooked function (the `hook_` parameter that was passed in) and the trampoline
        that was assigned by the hook function.

        @param [in] function_name_ The name of the function to unhook.
        @param [in] hook_ A void pointer to the function that is being called in
        place of the original.
        @param [out] trampoline_ The trampoline that was returned via reference
        in the original hook.
        */
        bool unhook_function(std::string function_name_, void *hook_, unary_function &trampoline_);
        bool unhook_function(std::string function_name_, void *hook_, binary_function &trampoline_);
        bool unhook_function(std::string function_name_, void *hook_, nular_function &trampoline_);
        //!@}


        /*!@{
        @brief Return the associated function maps.
        */
        const unary_map & unary() const;
        const binary_map & binary() const;
        const nular_map & nular() const;
        //!@}

    protected:
        /*!
        @name Function Maps
        */
        //!@{
        unary_map _unary_operators;
        binary_map _binary_operators;
        nular_map _nular_operators;
        //!@}

        /*!
        @name Initial Hook Functionality
        */
        //!@{
        static int __cdecl _initial_patch(char *a_, int b_, int c_);
        static unary_function _initial_trampoline;
        //!@}

        /*!
        @brief Stores the hooked functions.
        */
        std::unordered_set<uint32_t> _hooked_functions;

        bool _attached;
        bool _patched;
    };
}