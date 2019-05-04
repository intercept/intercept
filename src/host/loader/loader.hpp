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
        uintptr_t _file_banks{};
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
        types::__internal::allocatorInfo _allocator;

        /*!
        @brief Stores the data about the Functions needed to register SQF Functions.
        */
        sqf_register_functions _sqf_register_funcs;

        game_state* game_state_ptr;
        uintptr_t evaluate_script_function;
        uintptr_t varset_function;

        bool _attached;
        bool _patched;
    };

    namespace __internal {
        class gsFuncBase {
        public:
            r_string _name;
            void copyPH(const gsFuncBase* other) noexcept {
                securityStuff = other->securityStuff;
                //std::copy(std::begin(other->securityStuff), std::end(other->securityStuff), std::begin(securityStuff));
            }
        private:
            std::array<size_t,
            #if _WIN64 || __X86_64__
                10
            #else
            #ifdef __linux__
                8
            #else
                11
            #endif
            #endif
            > securityStuff {};  //Will scale with x64
            //size_t securityStuff[11];
        };
        class gsFunction : public gsFuncBase {
            void* placeholder12{ nullptr };//0x30  //jni function
        public:
            r_string _name2;//0x34 this is (tolower name)
            unary_operator * _operator;//0x38
        #ifndef __linux__
            r_string _rightType;//0x3c RString to something
            r_string _description;//0x38
            r_string _example;
            r_string _example2;
            r_string placeholder_11;
            r_string placeholder_12;
            r_string _category{ "intercept"sv }; //0x48
        #endif
                                        //const rv_string* placeholder13;
        };
        class gsOperator : public gsFuncBase {
            void* placeholder12{ nullptr };//0x30  JNI function
        public:
            r_string _name2;//0x34 this is (tolower name)
            int32_t placeholder_10{ 4 }; //0x38 Small int 0-5  priority
            binary_operator * _operator;//0x3c
        #ifndef __linux__
            r_string _leftType;//0x40 Description of left hand side parameter
            r_string _rightType;//0x44 Description of right hand side parameter
            r_string _description;//0x48
            r_string _example;//0x4c
            r_string placeholder_11;//0x60
            r_string _version;//0x64 some version number
            r_string placeholder_12;//0x68
            r_string _category{ "intercept"sv }; //0x6c
        #endif
        };
        class gsNular : public gsFuncBase {
        public:
            r_string _name2;//0x30 this is (tolower name)
            nular_operator * _operator;//0x34
        #ifndef __linux__
            r_string _description;//0x38
            r_string _example;
            r_string _example2;
            r_string _version;//0x44 some version number
            r_string placeholder_10;
            r_string _category; //0x4d
        #endif
            void* placeholder11{ nullptr };//0x50 JNI probably
            std::string_view get_map_key() const noexcept { return _name2; }
        };

        class game_functions : public auto_array<gsFunction>, public gsFuncBase {
        public:
            game_functions(r_string name) : _name(std::move(name)) {}
            r_string _name;
            game_functions() noexcept {}
            std::string_view get_map_key() const noexcept { return _name; }
        };

        class game_operators : public auto_array<gsOperator>, public gsFuncBase {
        public:
            game_operators(r_string name) : _name(std::move(name)) {}
            r_string _name;
            int32_t placeholder10{ 4 }; //0x2C Small int 0-5  priority
            game_operators() noexcept {}
            std::string_view get_map_key() const noexcept { return _name; }
        };
    }

    namespace types {
        template class rv_allocator<intercept::__internal::gsFunction>;
        template class rv_allocator<intercept::__internal::gsOperator>;
        template class rv_allocator<intercept::__internal::gsNular>;
        template class rv_allocator<intercept::__internal::game_functions>;
        template class rv_allocator<intercept::__internal::game_operators>;
    }
}
