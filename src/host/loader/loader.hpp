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
#include "common.hpp"
#include "singleton.hpp"
#include "logging.hpp"
#include "arguments.hpp"
#include "shared/types.hpp"
#include <unordered_set>

using namespace intercept::types;

namespace intercept {
    //! Nular function map.
    typedef std::unordered_map<r_string, std::vector<nular_entry>> nular_map;
    //! Unary function map.
    typedef std::unordered_map<r_string, std::vector<unary_entry>> unary_map;
    //! Binary functon map.
    typedef std::unordered_map<r_string, std::vector<binary_entry>> binary_map;

    struct sqf_register_functions {
        sqf_register_functions() : _types(static_cast<size_t>(types::game_data_type::end)) {}
        uintptr_t _gameState{};
        uintptr_t _operator_construct{};
        uintptr_t _operator_insert{};
        uintptr_t _unary_construct{};
        uintptr_t _unary_insert{};
        uintptr_t _type_vtable{};
        uintptr_t _compoundtype_vtable{};
        std::vector<const script_type_info *> _types;
    };

    /*!
    @brief The loader class, memory searcher and patching functionality to the RV engine.

    This is the main patching suit for Intercept. It contains all the functionality
    to search for and patch the RV engine. It also does the main memory analysis to
    find and catalog the SQF function pointers and store them.
    */
    class loader
        : public singleton<loader> {
    public:
        loader();

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
        bool get_function(std::string_view function_name_, unary_function &function_);

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
        bool get_function(std::string_view function_name_, unary_function & function_, std::string_view arg_signature_);

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
        bool get_function(std::string_view function_name_, binary_function &function_);

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
        bool get_function(std::string_view function_name_, binary_function &function_, std::string_view arg1_signature_, std::string_view arg2_signature_);

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
        bool get_function(std::string_view function_name_, nular_function &function_);

        /*!@{
        @brief Return the associated function maps.
        */
        const unary_map & unary() const;
        const binary_map & binary() const;
        const nular_map & nular() const;
        //!@}

        /*!
        @brief Returns the pointer to the engines allocator functions.
        */
        const types::__internal::allocatorInfo* get_allocator() const;

        /*!
        @brief Returns function Pointers needed to register SQF Functions
        */
        const sqf_register_functions& get_register_sqf_info() const;

        ///Finds game_state on the Stack
        static uintptr_t find_game_state(uintptr_t stack_base);

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
        @brief Stores the hooked functions.
        */
        std::unordered_set<uint32_t> _hooked_functions;

        /*!
        @brief Stores the data about the engines allocators.
        */
        types::__internal::allocatorInfo _allocator {};

        /*!
        @brief Stores the data about the Functions needed to register SQF Functions.
        */
        sqf_register_functions _sqf_register_funcs;

        game_state* game_state_ptr {nullptr};
        uintptr_t evaluate_script_function {0};
        uintptr_t varset_function {0};

        bool _attached {false};
        bool _patched{false};
    };
}
