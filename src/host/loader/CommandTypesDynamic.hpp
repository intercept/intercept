#pragma once

#define CT_NOALLOC

namespace __CTBase {
#define CT_VERSION 0
#include "CommandTypes.hpp"
#undef CT_VERSION
}

namespace __CT214 {
#define CT_VERSION 1
#include "CommandTypes.hpp"
#undef CT_VERSION
}

#undef CT_NOALLOC

// loader.cpp
extern bool CT_Is214;

namespace intercept {
    namespace __internal {

        class gsFuncBase {
            uint64_t dummyBuffer[16] {};
        public:
            void copyPH(const gsFuncBase* other) noexcept {
                if (CT_Is214)
                    reinterpret_cast<__CT214::intercept::__internal::gsFuncBase*>(this)->copyPH(reinterpret_cast<const __CT214::intercept::__internal::gsFuncBase*>(other));
                else
                    reinterpret_cast<__CTBase::intercept::__internal::gsFuncBase*>(this)->copyPH(reinterpret_cast<const __CTBase::intercept::__internal::gsFuncBase*>(other));
            }
        };
        class gsFunction : public gsFuncBase {
        public:
            uint64_t dummySpace[32] {};  // This is memory allocated on stack, where we fill data into before we copy/move it into table

            using TBase = __CTBase::intercept::__internal::gsFunction;
            using T214 = __CT214::intercept::__internal::gsFunction;

            r_string get_name2() const {  //#TODO after 2.14 release, move these into the base definitions without dynamic dispatch
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_name2;
                else
                    return reinterpret_cast<const TBase*>(this)->_name2;
            }

            unary_operator* get_operator() const {
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_operator;
                else
                    return reinterpret_cast<const TBase*>(this)->_operator;
            }

            void set_operator(unary_operator* newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_operator = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_operator = newOP;
            }

            void set_name(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_name = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_name = newOP;
            }

            void set_name2(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_name2 = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_name2 = newOP;
            }

#ifndef __linux__
            r_string get_description() const {
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_description;
                else
                    return reinterpret_cast<const TBase*>(this)->_description;
            }

            void set_description(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<__CT214::intercept::__internal::gsOperator*>(this)->_description = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_description = newOP;
            }

            void set_category(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_category = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_category = newOP;
            }

#endif
        };
        class gsOperator : public gsFuncBase {
            uint64_t dummySpace[32]{};  // This is memory allocated on stack, where we fill data into before we copy/move it into table

        public:
            using TBase = __CTBase::intercept::__internal::gsOperator;
            using T214 = __CT214::intercept::__internal::gsOperator;

            r_string get_name2() const {  //#TODO after 2.14 release, move these into the base definitions without dynamic dispatch
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_name2;
                else
                    return reinterpret_cast<const TBase*>(this)->_name2;
            }

            binary_operator* get_operator() const {
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_operator;
                else
                    return reinterpret_cast<const TBase*>(this)->_operator;
            }

            void set_operator(binary_operator* newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_operator = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_operator = newOP;
            }

            void set_name(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_name = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_name = newOP;
            }

            void set_name2(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_name2 = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_name2 = newOP;
            }

#ifndef __linux__
            r_string get_description() const {
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_description;
                else
                    return reinterpret_cast<const TBase*>(this)->_description;
            }

            void set_description(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_description = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_description = newOP;
            }

            void set_category(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_category = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_category = newOP;
            }
#endif
        };
        class gsNular : public gsFuncBase {
        public:
            uint64_t dummySpace[32]{};  // This is memory allocated on stack, where we fill data into before we copy/move it into table

            using TBase = __CTBase::intercept::__internal::gsNular;
            using T214 = __CT214::intercept::__internal::gsNular;

            r_string get_name2() const { //#TODO after 2.14 release, move these into the base definitions without dynamic dispatch
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_name2;
                else
                    return reinterpret_cast<const TBase*>(this)->_name2;
            }

            nular_operator* get_operator() const {
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_operator;
                else
                    return reinterpret_cast<const TBase*>(this)->_operator;
            }

            void set_operator(nular_operator* newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_operator = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_operator = newOP;
            }

            void set_name(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_name = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_name = newOP;
            }

            void set_name2(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_name2 = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_name2 = newOP;
            }

#ifndef __linux__
            r_string get_description() const {
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_description;
                else
                    return reinterpret_cast<const TBase*>(this)->_description;
            }

            void set_description(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_description = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_description = newOP;
            }

            void set_category(r_string newOP) {
                if (CT_Is214)
                    reinterpret_cast<T214*>(this)->_category = newOP;
                else
                    reinterpret_cast<TBase*>(this)->_category = newOP;
            }
#endif

            std::string_view get_map_key() const noexcept {
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_name2;
                else
                    return reinterpret_cast<const TBase*>(this)->_name2;
            }

            static gsNular* convertingInsert(auto_array<gsNular>* const table, gsNular& inputVal) {  // Don't move these to base on 2.14
                using TCBase = __CTBase::intercept::__internal::gsNular;
                using TC214 = __CT214::intercept::__internal::gsNular;

                if (CT_Is214)
                    return reinterpret_cast<gsNular*>(
                        static_cast<TC214*>(
                            reinterpret_cast<auto_array<TC214>*>(table)->push_back(TC214(std::move(*reinterpret_cast<TC214*>(&inputVal))))
                        )
                    );
                else
                    return reinterpret_cast<gsNular*>(
                        static_cast<TCBase*>(
                            reinterpret_cast<auto_array<TCBase>*>(table)->push_back(TCBase(std::move(*reinterpret_cast<TCBase*>(&inputVal))))
                        )
                    );
            }

            static void SetupBackup(auto_array<gsNular>* table, std::map<uintptr_t, types::auto_array<char>>& keeper) {  // Don't move these to base on 2.14
                if (CT_Is214) {
                    const auto castTbl = reinterpret_cast<auto_array<T214>*>(table);

                    auto_array<T214> backup(castTbl->begin(), castTbl->end());
                    keeper.insert_or_assign(reinterpret_cast<uintptr_t>(castTbl->data()), std::move(*reinterpret_cast<auto_array<char>*>(castTbl)));
                    *castTbl = std::move(backup);
                } else {
                    const auto castTbl = reinterpret_cast<auto_array<TBase>*>(table);

                    auto_array<TBase> backup(castTbl->begin(), castTbl->end());
                    keeper.insert_or_assign(reinterpret_cast<uintptr_t>(castTbl->data()), std::move(*reinterpret_cast<auto_array<char>*>(castTbl)));
                    *castTbl = std::move(backup);
                }
            }
        };

        class game_functions : public auto_array<gsFunction>, public gsFuncBase {
        public:
            using TBase = __CTBase::intercept::__internal::game_functions;
            using T214 = __CT214::intercept::__internal::game_functions;

            static game_functions* tableInsert(auto_array<game_functions>* const table, r_string lowerName) {
                if (CT_Is214)
                    return reinterpret_cast<game_functions*>(
                        static_cast<T214*>(
                            reinterpret_cast<auto_array<T214>*>(table)->push_back(T214(std::move(lowerName)))));
                else
                    return reinterpret_cast<game_functions*>(
                        static_cast<TBase*>(
                            reinterpret_cast<auto_array<TBase>*>(table)->push_back(TBase(std::move(lowerName)))));
            }

            gsFunction* convertingInsert(gsFunction& inputVal) {  // Don't move these to base on 2.14
                using TCBase = __CTBase::intercept::__internal::gsFunction;
                using TC214 = __CT214::intercept::__internal::gsFunction;

                if (CT_Is214)
                    return reinterpret_cast<gsFunction*>(
                        static_cast<TC214*>(
                            reinterpret_cast<auto_array<TC214>*>(this)->push_back(TC214(std::move(*reinterpret_cast<TC214*>(&inputVal))))
                        )
                    );
                else
                    return reinterpret_cast<gsFunction*>(
                        static_cast<TCBase*>(
                            reinterpret_cast<auto_array<TCBase>*>(this)->push_back(TCBase(std::move(*reinterpret_cast<TCBase*>(&inputVal))))
                        )
                    );
            }

            static void SetupBackup(auto_array<game_functions>* table, std::map<uintptr_t, types::auto_array<char>>& keeper) {
                if (CT_Is214) {
                    const auto castTbl = reinterpret_cast<auto_array<T214>*>(table);

                    auto_array<T214> backup(castTbl->begin(), castTbl->end());
                    keeper.insert_or_assign(reinterpret_cast<uintptr_t>(castTbl->data()), std::move(*reinterpret_cast<auto_array<char>*>(castTbl)));
                    *castTbl = std::move(backup);
                } else {
                    const auto castTbl = reinterpret_cast<auto_array<TBase>*>(table);

                    auto_array<TBase> backup(castTbl->begin(), castTbl->end());
                    keeper.insert_or_assign(reinterpret_cast<uintptr_t>(castTbl->data()), std::move(*reinterpret_cast<auto_array<char>*>(castTbl)));
                    *castTbl = std::move(backup);
                }
            }

            std::string_view get_map_key() const noexcept {
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_name;
                else
                    return reinterpret_cast<const TBase*>(this)->_name;
            }
        };

        class game_operators : public auto_array<gsOperator>, public gsFuncBase {
        public:
            using TBase = __CTBase::intercept::__internal::game_operators;
            using T214 = __CT214::intercept::__internal::game_operators;

            static game_operators* tableInsert(auto_array<game_operators>* const table, r_string lowerName) {  // Don't move these to base on 2.14
                if (CT_Is214)
                    return reinterpret_cast<game_operators*>(
                        static_cast<T214*>(
                            reinterpret_cast<auto_array<T214>*>(table)->push_back(T214(std::move(lowerName)))
                        )
                    );
                else
                    return reinterpret_cast<game_operators*>(
                        static_cast<TBase*>(
                            reinterpret_cast<auto_array<TBase>*>(table)->push_back(TBase(std::move(lowerName)))
                        )
                    );
            }

            gsOperator* convertingInsert(gsOperator& inputVal) {  // Don't move these to base on 2.14
                using TCBase = __CTBase::intercept::__internal::gsOperator;
                using TC214 = __CT214::intercept::__internal::gsOperator;

                if (CT_Is214)
                    return reinterpret_cast<gsOperator*>(
                        static_cast<TC214*>(
                            reinterpret_cast<auto_array<TC214>*>(this)->push_back(TC214(std::move(*reinterpret_cast<TC214*>(&inputVal))))
                        )
                    );
                else
                    return reinterpret_cast<gsOperator*>(
                        static_cast<TCBase*>(
                            reinterpret_cast<auto_array<TCBase>*>(this)->push_back(TCBase(std::move(*reinterpret_cast<TCBase*>(&inputVal))))
                        )
                    );
            }

            static void SetupBackup(auto_array<game_operators>* table, std::map<uintptr_t, types::auto_array<char>>& keeper) {  // Don't move these to base on 2.14
                if (CT_Is214) {
                    const auto castTbl = reinterpret_cast<auto_array<T214>*>(table);

                    auto_array<T214> backup(castTbl->begin(), castTbl->end());
                    keeper.insert_or_assign(reinterpret_cast<uintptr_t>(castTbl->data()), std::move(*reinterpret_cast<auto_array<char>*>(castTbl)));
                    *castTbl = std::move(backup);
                } else {
                    const auto castTbl = reinterpret_cast<auto_array<TBase>*>(table);

                    auto_array<TBase> backup(castTbl->begin(), castTbl->end());
                    keeper.insert_or_assign(reinterpret_cast<uintptr_t>(castTbl->data()), std::move(*reinterpret_cast<auto_array<char>*>(castTbl)));
                    *castTbl = std::move(backup);
                }
            }

            std::string_view get_map_key() const noexcept {
                if (CT_Is214)
                    return reinterpret_cast<const T214*>(this)->_name;
                else
                    return reinterpret_cast<const TBase*>(this)->_name;
            }
        };

        struct FindHelpers {
            class game_state_access : public game_state {
            public:
                using game_state::_scriptFunctions;
                using game_state::_scriptNulars;
                using game_state::_scriptOperators;
            };

            static intercept::__internal::game_operators* findOperators(game_state* gsPtr, std::string name) {
                auto gs = static_cast<game_state_access*>(gsPtr);
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);

                using TMapBase = map_string_to_class<__CTBase::intercept::__internal::game_operators, auto_array<__CTBase::intercept::__internal::game_operators>>;
                using TMap214 = map_string_to_class<__CT214::intercept::__internal::game_operators, auto_array<__CT214::intercept::__internal::game_operators>>;

                if (CT_Is214) {
                    auto mapPtr = reinterpret_cast<TMap214*>(&gs->_scriptOperators);

                    auto& found = mapPtr->get(name);
                    if (mapPtr->is_null(found)) return nullptr;
                    return reinterpret_cast<game_operators*>(&found);
                } else {
                    auto mapPtr = reinterpret_cast<TMapBase*>(&gs->_scriptOperators);

                    auto& found = mapPtr->get(name);
                    if (mapPtr->is_null(found)) return nullptr;
                    return reinterpret_cast<game_operators *>(&found);
                }
            }

            static intercept::__internal::game_functions* findFunctions(game_state* gsPtr, std::string name) {
                auto gs = static_cast<game_state_access*>(gsPtr);
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);

                using TMapBase = map_string_to_class<__CTBase::intercept::__internal::game_functions, auto_array<__CTBase::intercept::__internal::game_functions>>;
                using TMap214 = map_string_to_class<__CT214::intercept::__internal::game_functions, auto_array<__CT214::intercept::__internal::game_functions>>;

                if (CT_Is214) {
                    auto mapPtr = reinterpret_cast<TMap214*>(&gs->_scriptFunctions);

                    auto& found = mapPtr->get(name);
                    if (mapPtr->is_null(found)) return nullptr;
                    return reinterpret_cast<game_functions*>(&found);
                } else {
                    auto mapPtr = reinterpret_cast<TMapBase*>(&gs->_scriptFunctions);

                    auto& found = mapPtr->get(name);
                    if (mapPtr->is_null(found)) return nullptr;
                    return reinterpret_cast<game_functions*>(&found);
                }
            }

            static intercept::__internal::gsNular* findNular(game_state* gsPtr, std::string name) {
                auto gs = static_cast<game_state_access*>(gsPtr);
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);

                using TMapBase = map_string_to_class<__CTBase::intercept::__internal::gsNular, auto_array<__CTBase::intercept::__internal::gsNular>>;
                using TMap214 = map_string_to_class<__CT214::intercept::__internal::gsNular, auto_array<__CT214::intercept::__internal::gsNular>>;

                if (CT_Is214) {
                    auto mapPtr = reinterpret_cast<TMap214*>(&gs->_scriptNulars);

                    auto& found = mapPtr->get(name);
                    if (mapPtr->is_null(found)) return nullptr;
                    return reinterpret_cast<gsNular*>(&found);
                } else {
                    auto mapPtr = reinterpret_cast<TMapBase*>(&gs->_scriptNulars);

                    auto& found = mapPtr->get(name);
                    if (mapPtr->is_null(found)) return nullptr;
                    return reinterpret_cast<gsNular*>(&found);
                }
            }

            static intercept::__internal::gsFunction* findUnary(game_state* gsPtr, std::string name, game_data_type argument_type) {
                auto gs = static_cast<game_state_access*>(gsPtr);
                //gs->_scriptFunctions.get_table_for_key(name.c_str())->for_each([](const game_functions& it) {
                //    OutputDebugStringA(it._name.c_str());
                //    OutputDebugStringA("\n");
                //});
                auto funcs = findFunctions(gs, name);
                if (!funcs) return nullptr;
                const auto argTypeString = types::__internal::to_string(argument_type);


                using TMapBase = map_string_to_class<__CTBase::intercept::__internal::game_functions, auto_array<__CTBase::intercept::__internal::game_functions>>;
                using TMap214 = map_string_to_class<__CT214::intercept::__internal::game_functions, auto_array<__CT214::intercept::__internal::game_functions>>;

                if (CT_Is214) {
                    auto funcsConv = reinterpret_cast<__CT214::intercept::__internal::game_functions*>(funcs);

                    for (auto& it : *funcsConv) {
                        auto types = it._operator->get_arg_type().type();
                        if (types.find(argTypeString) != types.end()) {
                            return reinterpret_cast<gsFunction*>(&it);
                        }
                    }
                } else {
                    auto funcsConv = reinterpret_cast<__CTBase::intercept::__internal::game_functions*>(funcs);

                    for (auto& it : *funcsConv) {
                        auto types = it._operator->get_arg_type().type();
                        if (types.find(argTypeString) != types.end()) {
                            return reinterpret_cast<gsFunction*>(&it);
                        }
                    }
                }

                return nullptr;
            }

            static intercept::__internal::gsOperator* findBinary(game_state* gsPtr, std::string name, types::game_data_type left_argument_type, types::game_data_type right_argument_type) {
                auto gs = static_cast<game_state_access*>(gsPtr);
                //gs->_scriptOperators.get_table_for_key(name.c_str())->for_each([](const game_operators& it) {
                //    OutputDebugStringA(it._name.c_str());
                //    OutputDebugStringA("\n");
                //});

                auto operators = findOperators(gs, name);
                if (!operators) return nullptr;

                                const auto left_argTypeString = types::__internal::to_string(left_argument_type);
                const auto right_argTypeString = types::__internal::to_string(right_argument_type);

                using TMapBase = map_string_to_class<__CTBase::intercept::__internal::game_operators, auto_array<__CTBase::intercept::__internal::game_operators>>;
                using TMap214 = map_string_to_class<__CT214::intercept::__internal::game_operators, auto_array<__CT214::intercept::__internal::game_operators>>;


                if (CT_Is214) {
                    auto opsConv = reinterpret_cast<__CT214::intercept::__internal::game_operators*>(operators);

                    for (auto& it : *opsConv) {
                        auto left_types = it._operator->get_arg1_type().type();
                        if (left_types.find(left_argTypeString) != left_types.end()) {
                            auto right_types = it._operator->get_arg2_type().type();
                            if (right_types.find(right_argTypeString) != right_types.end()) {
                                return reinterpret_cast<gsOperator*>(&it);
                            }
                        }
                    }
                } else {
                    auto opsConv = reinterpret_cast<__CTBase::intercept::__internal::game_operators*>(operators);

                    for (auto& it : *opsConv) {
                        auto left_types = it._operator->get_arg1_type().type();
                        if (left_types.find(left_argTypeString) != left_types.end()) {
                            auto right_types = it._operator->get_arg2_type().type();
                            if (right_types.find(right_argTypeString) != right_types.end()) {
                                return reinterpret_cast<gsOperator*>(&it);
                            }
                        }
                    }
                }

                return nullptr;
            }


        };

    } // namespace __internal
}  // namespace intercept





