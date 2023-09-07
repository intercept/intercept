//#pragma once

// Used to swap between implementations for backwards/forwards compat
#ifndef CT_VERSION
#define CT_VERSION 0
#endif


namespace intercept {
    namespace __internal {
        class gsFuncBase {
        public:
            r_string _name;
            void copyPH(const gsFuncBase* other) noexcept {
                securityStuff = other->securityStuff;
                //std::copy(std::begin(other->securityStuff), std::end(other->securityStuff), std::begin(securityStuff));
            }

        private:
#if CT_VERSION == 0

            std::array<size_t,
#if _WIN64 || __X86_64__
                       10
#elif defined(_LINUX64)
                       7
#elif defined(__linux__)
                       8  //#TODO drop linux32 support
#else
                       11
#endif
                       >
                securityStuff{};  //Will scale with x64

#elif CT_VERSION == 1


            std::array<size_t,
#if _WIN64 || __X86_64__
                       9 // Win64
#elif defined(_LINUX64)
                       9 // Linux64
#elif defined(__linux__)
                       8 // Linux32 //#UNTESTED! //#TODO drop linux32 support
#else
                       18 // Win32
#endif
                       >
                securityStuff{};  //Will scale with x64


#endif


        };
        class gsFunction : public gsFuncBase {
#if CT_VERSION == 0
            void* placeholder12{nullptr};  //0x30  //jni function
#endif
        public:
            r_string _name2;               //0x34 this is (tolower name)
            unary_operator* _operator;     //0x38
#ifndef __linux__
            r_string _rightType;           //0x3c RString to something
            r_string _description;         //0x38
            r_string _example;
            r_string _example2;
            r_string placeholder_11;
            r_string placeholder_12;
            r_string _category{"intercept"sv};  //0x48
#endif
                //const rv_string* placeholder13;
        };
        class gsOperator : public gsFuncBase {
#if CT_VERSION == 0
            void* placeholder12{nullptr};       //0x30  JNI function
#endif
        public:
            r_string _name2;                    //0x34 this is (tolower name)
            int32_t placeholder_10{4};          //0x38 Small int 0-5  priority
            binary_operator* _operator;         //0x3c
#ifndef __linux__
            r_string _leftType;                 //0x40 Description of left hand side parameter
            r_string _rightType;                //0x44 Description of right hand side parameter
            r_string _description;              //0x48
            r_string _example;                  //0x4c
            r_string placeholder_11;            //0x60
            r_string _version;                  //0x64 some version number
            r_string placeholder_12;            //0x68
            r_string _category{"intercept"sv};  //0x6c
#endif
        };
        class gsNular : public gsFuncBase {
        public:
            r_string _name2;            //0x30 this is (tolower name)
            nular_operator* _operator;  //0x34
#ifndef __linux__
            r_string _description;      //0x38
            r_string _example;
            r_string _example2;
            r_string _version;             //0x44 some version number
            r_string placeholder_10;
            r_string _category;            //0x4d
#endif
#if CT_VERSION == 0
            void* placeholder11{nullptr};  //0x50 JNI probably
#endif
            std::string_view get_map_key() const noexcept { return _name2; }
        };

        class game_functions : public auto_array<gsFunction>, public gsFuncBase {
        public:
            game_functions(r_string name) : _name(std::move(name)) {}
            r_string _name;
            game_functions() noexcept {

            }
            ~game_functions() noexcept {

            }
            std::string_view get_map_key() const noexcept { return _name; }
        };

        class game_operators : public auto_array<gsOperator>, public gsFuncBase {
        public:
            game_operators(r_string name) : _name(std::move(name)) {}
            r_string _name;
            int32_t placeholder10{4};  //0x2C Small int 0-5  priority
            game_operators() noexcept {}
            std::string_view get_map_key() const noexcept { return _name; }
        };
    }  // namespace __internal

#ifndef CT_NOALLOC
    namespace types {
        template class rv_allocator<intercept::__internal::gsFunction>;
        template class rv_allocator<intercept::__internal::gsOperator>;
        template class rv_allocator<intercept::__internal::gsNular>;
        template class rv_allocator<intercept::__internal::game_functions>;
        template class rv_allocator<intercept::__internal::game_operators>;
    }  // namespace types
#endif
}  // namespace intercept
