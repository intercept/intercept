#pragma once



#ifndef CMDSC_TYPE
#define CMDSC_TYPE Base
#endif


#define CONCAT_(a,b) a ## b
#define CONCAT(a, b) CONCAT_(a,b)

#define BASE_NAMESPACE CONCAT(__CT, CMDSC_TYPE)

void CONCAT(DoCommandScan, CMDSC_TYPE) (loader& ldrPtr, game_state* gameStatePtr) {
    class game_state_access : public game_state {
    public:
        using game_state::_scriptFunctions;
        using game_state::_scriptNulars;
        using game_state::_scriptOperators;
    };

    class loader_access : public loader {
    public:
        using loader::_unary_operators;
        using loader::_binary_operators;
        using loader::_nular_operators;
    };

    auto gameState = static_cast<game_state_access*>(gameStatePtr);
    auto ldr = static_cast<loader_access*>(&ldrPtr);

    /*
    Unary Hashmap

    This is a hashmap using a key->bucket system, so an array of arrays keyed by a hash.
    We don't give a fuck about that though, we just want to iterate through all of the
    buckets and in turn each item in the bucket, because they are our operator entries.
    */

    auto* funcAccess = (map_string_to_class<BASE_NAMESPACE::intercept::__internal::game_functions, auto_array<BASE_NAMESPACE::intercept::__internal::game_functions>>*)&gameState->_scriptFunctions;
    for (auto& it : *funcAccess) {
        for (auto& entry : it) {
            unary_entry new_entry;
            new_entry.op = entry._operator;
            new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
            new_entry.name = entry._name.data();
            LOG(INFO, "Found unary operator: {} {} ({}) @{:x}",
                new_entry.op->return_type.type_str(), new_entry.name,
                new_entry.op->get_arg_type().type_str(), reinterpret_cast<uintptr_t>(new_entry.op->procedure_addr));
            ldr->_unary_operators[entry._name2].push_back(new_entry);
        }
    }

    /*
    Binary Hashmap
    */
    auto* opAccess = (map_string_to_class<BASE_NAMESPACE::intercept::__internal::game_operators, auto_array<BASE_NAMESPACE::intercept::__internal::game_operators>>*)&gameState->_scriptOperators;
    for (auto& it : *opAccess) {
        for (auto& entry : it) {
            binary_entry new_entry;
            new_entry.op = entry._operator;
            new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
            new_entry.name = entry._name.data();
            LOG(INFO, "Found binary operator: {} ({}) {} ({}) @{:x}",
                new_entry.op->return_type.type_str(), new_entry.op->get_arg1_type().type_str(), new_entry.name,
                new_entry.op->get_arg2_type().type_str(), reinterpret_cast<uintptr_t>(new_entry.op->procedure_addr));
            ldr->_binary_operators[entry._name2].push_back(new_entry);
        }
    }

    /*
    Nular Hashmap
    */
    auto* nularAccess = (map_string_to_class<BASE_NAMESPACE::intercept::__internal::gsNular, auto_array<BASE_NAMESPACE::intercept::__internal::gsNular>>*)&gameState->_scriptNulars;
    for (auto& entry : *nularAccess) {
        nular_entry new_entry;
        new_entry.op = entry._operator;
        new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
        new_entry.name = entry._name.data();
        LOG(INFO, "Found nular operator: {} {} @{:x}", new_entry.op->return_type.type_str(), new_entry.name, reinterpret_cast<uintptr_t>(new_entry.op->procedure_addr));
        ldr->_nular_operators[entry._name2].push_back(new_entry);
    }
}
