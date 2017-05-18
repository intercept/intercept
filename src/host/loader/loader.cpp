﻿#include "loader.hpp"
#include "controller.hpp"
#include <thread>
#include <future>
#include <Psapi.h>
#pragma comment (lib, "Psapi.lib")//GetModuleInformation
#pragma comment (lib, "version.lib") //GetFileVersionInfoSize
template class intercept::types::rv_allocator<intercept::__internal::gsFunction>;
template class intercept::types::rv_allocator<intercept::__internal::gsOperator>;
template class intercept::types::rv_allocator<intercept::__internal::gsNular>;
template class intercept::types::rv_allocator<intercept::__internal::game_functions>;
template class intercept::types::rv_allocator<intercept::__internal::game_operators>;

namespace intercept {
    loader::loader() : _attached(false), _patched(false) {}

    loader::~loader() {

    }

    bool loader::get_function(std::string function_name_, unary_function & function_, std::string arg_signature_) {
        auto it = _unary_operators.find(function_name_);
        if (it != _unary_operators.end()) {
            for (auto op : it->second) {
                if (op.op->arg_type.type().count(arg_signature_)) {
                    function_ = reinterpret_cast<unary_function>(op.op->procedure_addr);
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    bool loader::get_function(std::string function_name_, unary_function & function_) {
        auto it = _unary_operators.find(function_name_);
        if (it != _unary_operators.end()) {
            function_ = reinterpret_cast<unary_function>(it->second[0].op->procedure_addr);
            return true;
        }
        return false;
    }

    bool loader::get_function(std::string function_name_, binary_function & function_) {
        auto it = _binary_operators.find(function_name_);
        if (it != _binary_operators.end()) {
            function_ = reinterpret_cast<binary_function>(it->second[0].op->procedure_addr);
            return true;
        }
        return false;
    }

    bool loader::get_function(std::string function_name_, binary_function & function_, std::string arg1_signature_, std::string arg2_signature_) {
        auto it = _binary_operators.find(function_name_);
        if (it != _binary_operators.end()) {
            for (auto op : it->second) {
                if (op.op->arg1_type.type().count(arg1_signature_) && op.op->arg2_type.type().count(arg2_signature_)) {
                    function_ = reinterpret_cast<binary_function>(op.op->procedure_addr);
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    bool loader::get_function(std::string function_name_, nular_function & function_) {
        auto it = _nular_operators.find(function_name_);
        if (it != _nular_operators.end()) {
            function_ = reinterpret_cast<nular_function>(it->second[0].op->procedure_addr);
            return true;
        }
        return false;
    }

    bool loader::hook_function(std::string function_name_, void * hook_, unary_function & trampoline_) {
        LOG(DEBUG) << "Attempting to hook unary function " << function_name_;
        auto op = _unary_operators.find(function_name_);
        if (op != _unary_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            trampoline_ = *reinterpret_cast<unary_function *>(op_ptr);
            memcpy(reinterpret_cast<void *>(op_ptr), &hook_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    bool loader::hook_function(std::string function_name_, void * hook_, binary_function & trampoline_) {
        LOG(DEBUG) << "Attempting to hook binary function " << function_name_;
        auto op = _binary_operators.find(function_name_);
        if (op != _binary_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            trampoline_ = *reinterpret_cast<binary_function *>(op_ptr);
            memcpy(reinterpret_cast<void *>(op_ptr), &hook_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    bool loader::hook_function(std::string function_name_, void * hook_, nular_function & trampoline_) {
        LOG(DEBUG) << "Attempting to hook nular function " << function_name_;
        auto op = _nular_operators.find(function_name_);
        if (op != _nular_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            trampoline_ = *reinterpret_cast<nular_function *>(op_ptr);
            memcpy(reinterpret_cast<void *>(op_ptr), &hook_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    bool loader::unhook_function(std::string function_name_, void * hook_, unary_function & trampoline_) {
        LOG(DEBUG) << "Attempting to unhook unary function " << function_name_;
        if (&trampoline_ == nullptr)
            return false;
        auto op = _unary_operators.find(function_name_);
        if (op != _unary_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            memcpy(reinterpret_cast<void *>(op_ptr), &trampoline_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    bool loader::unhook_function(std::string function_name_, void * hook_, binary_function & trampoline_) {
        LOG(DEBUG) << "Attempting to unhook binary function " << function_name_;
        if (&trampoline_ == nullptr)
            return false;
        auto op = _binary_operators.find(function_name_);
        if (op != _binary_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            memcpy(reinterpret_cast<void *>(op_ptr), &trampoline_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    bool loader::unhook_function(std::string function_name_, void * hook_, nular_function & trampoline_) {
        LOG(DEBUG) << "Attempting to unhook nular function " << function_name_;
        if (&trampoline_ == nullptr)
            return false;
        auto op = _nular_operators.find(function_name_);
        if (op != _nular_operators.end()) {
            uintptr_t op_ptr = op->second[0].procedure_ptr_addr;
            memcpy(reinterpret_cast<void *>(op_ptr), &trampoline_, sizeof(uintptr_t));
            return true;
        }
        return false;
    }

    void loader::do_function_walk(uintptr_t state_addr_) {
        uintptr_t types_array = state_addr_;
        auto game_state = reinterpret_cast<__internal::game_state*>(state_addr_);


        MODULEINFO modInfo = { nullptr };
        HMODULE hModule = GetModuleHandleA(nullptr);
        GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));

        auto findInMemory = [&modInfo](char* pattern, size_t patternLength) ->uintptr_t {
            uintptr_t base = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
            uintptr_t size = static_cast<uintptr_t>(modInfo.SizeOfImage);
            for (DWORD i = 0; i < size - patternLength; i++) {
                bool found = true;
                for (DWORD j = 0; j < patternLength; j++) {
                    found &= pattern[j] == *reinterpret_cast<char*>(base + i + j);
                    if (!found)
                        break;
                }
                if (found)
                    return base + i;
            }
            return 0;
        };

        auto findInMemoryPattern = [&modInfo](const char* pattern, const char* mask, uintptr_t offset = 0) {
            uintptr_t base = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
            uintptr_t size = static_cast<uintptr_t>(modInfo.SizeOfImage);

            uintptr_t patternLength = static_cast<DWORD>(strlen(mask));

            for (uintptr_t i = 0; i < size - patternLength; i++) {
                bool found = true;
                for (uintptr_t j = 0; j < patternLength; j++) {
                    found &= mask[j] == '?' || pattern[j] == *reinterpret_cast<char*>(base + i + j);
                    if (!found)
                        break;
                }
                if (found)
                    return base + i + offset;
            }
            return 0x0u;
        };

        auto getRTTIName = [](uintptr_t vtable) -> const char* {
            uintptr_t typeBase = *reinterpret_cast<uintptr_t*>(vtable - 4);
            uintptr_t type = *reinterpret_cast<uintptr_t*>(typeBase + 0xC);
            return reinterpret_cast<char*>(type + 9);
        };

        //Shamelessly copied from Dedmen's Hack :3
        CHAR fileName[_MAX_PATH];
        DWORD size = GetModuleFileName(nullptr, fileName, _MAX_PATH);
        fileName[size] = NULL;
        DWORD handle = 0;
        size = GetFileVersionInfoSize(fileName, &handle);
        BYTE* versionInfo = new BYTE[size];
        if (!GetFileVersionInfo(fileName, handle, size, versionInfo)) {
            delete[] versionInfo;
        }
        UINT    			len = 0;
        VS_FIXEDFILEINFO*   vsfi = nullptr;
        VerQueryValue(versionInfo, "\\", reinterpret_cast<void**>(&vsfi), &len);
        short version = HIWORD(vsfi->dwFileVersionLS);//131
        short version1 = LOWORD(vsfi->dwFileVersionLS);//646
        short version2 = HIWORD(vsfi->dwFileVersionMS);// 1
        short version3 = LOWORD(vsfi->dwFileVersionMS);// 48
        delete[] versionInfo;




        //Start them async before doing the other stuff so they are done when we are done parsing the script functions

        auto future_stringOffset = std::async([&]() {return findInMemory("tbb4malloc_bi", 13); });
        //auto future_unary_construct =std::async([&]() {return findInMemoryPattern("\x51\x8b\x44\x24\x00\x53\x55\x56\x33\xf6\x89\x74\x24\x00\x57\x8b\xf9\x8d\x5e\x00\x85\xc0\x74\x00\x50\xe8\x00\x00\x00\x00\x8b\xf0\x83\xc4\x00\x85\xf6\x74\x00\x8b\xc3\xf0\x0f\xc1\x06\x89\x74\x24\x00\x85\xf6\x74\x00\x8b\xc3\xf0\x0f\xc1\x06", "xxxx?xxxxxxxx?xxxxx?xxx?xx????xxxx?xxx?xxxxxxxxx?xxx?xxxxxx"); });

        //auto future_operator_construct = std::async([&]() {return findInMemoryPattern("\x51\x8b\x44\x24\x00\x53\x55\x56\x33\xf6\x89\x74\x24\x00\x57\x8b\xf9\x8d\x5e\x00\x85\xc0\x74\x00\x50\xe8\x00\x00\x00\x00\x8b\xf0\x83\xc4\x00\x85\xf6\x74\x00\x8b\xc3\xf0\x0f\xc1\x06\x89\x74\x24\x00\x85\xf6\x74\x00\x8b\xc3\xf0\x0f\xc1\x06\x6a\x00\x8d\x4f\x00\x89\x37\xe8\x00\x00\x00\x00\x83\xcd\x00\x85\xf6\x74\x00\x8b\xc5\xf0\x0f\xc1\x06\x48\x75\x00\x8b\x0d\x00\x00\x00\x00\x56\x8b\x01\xff\x50\x00\xc7\x44\x24\x00\x00\x00\x00\x00\x8b\x0f\x8b\x44\x24\x00\x89\x47\x00\x85\xc9\x74\x00\x8b\xc3\xf0\x0f\xc1\x01\x8b\x44\x24\x00\x89\x4f\x00\x89\x47\x00\x8b\x44\x24\x00\xc7\x47\x00\x00\x00\x00\x00\xc7\x47\x00\x00\x00\x00\x00\x85\xc0\x74\x00\x50\xe8\x00\x00\x00\x00\x8b\x57\x00\x83\xc4\x00\x85\xc0\x74\x00\x8b\xcb\xf0\x0f\xc1\x08", "xxxx?xxxxxxxx?xxxxx?xxx?xx????xxxx?xxx?xxxxxxxxx?xxx?xxxxxxx?xx?xxx????xx?xxx?xxxxxxxx?xx????xxxxx?xxx?????xxxxx?xx?xxx?xxxxxxxxx?xx?xx?xxx?xx?????xx?????xxx?xx????xx?xx?xxx?xxxxxx"); });
         
        //make sure insert patterns are long enough. they have to include the offset after the target of the first jmp instruction
        //auto future_operator_insert = std::async([&]() {return findInMemoryPattern("\x81\xec\x00\x00\x00\x00\x53\x56\x8b\xb4\x24\x00\x00\x00\x00\x8b\xd9\x57\x56\x8d\x4c\x24\x00\xe8\x00\x00\x00\x00\x8b\x46\x00\x85\xc0\x74\x00\x83\xc0\x00\xeb\x00\xb8\x00\x00\x00\x00\x83\xc3\x18", "xx????xxxxx????xxxxxxx?x????xx?xxx?xx?x?x????xxx"); });
        //auto future_unary_insert = std::async([&]() {return findInMemoryPattern("\x81\xec\x00\x00\x00\x00\x53\x56\x8b\xb4\x24\x00\x00\x00\x00\x8b\xd9\x57\x56\x8d\x4c\x24\x00\xe8\x00\x00\x00\x00\x8b\x46\x00\x85\xc0\x74\x00\x83\xc0\x00\xeb\x00\xb8\x00\x00\x00\x00\x83\xc3\x0C", "xx????xxxxx????xxxxxxx?x????xx?xxx?xx?x?x????xxx"); });

        //#TODO these patternfinds can be replaced by taking the alloc function out of any Types createFunction. and the dealloc function is right next to it asm wise
        auto future_poolFuncAlloc = std::async([&]() {return findInMemoryPattern("\x56\x8B\xF1\xFF\x46\x38\x8B\x46\x04\x3B\xC6\x74\x09\x85\xC0\x74\x05\x83\xC0\xF0\x75\x26\x8B\x4E\x10\x8D\x46\x0C\x3B\xC8\x74\x0B\x85\xC9\x74\x07\x8D\x41\xF0\x85\xC0\x75\x11", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); });
        auto future_poolFuncDealloc = std::async([&]() {return findInMemoryPattern("\x8B\x44\x24\x04\x85\xC0\x74\x09\x89\x44\x24\x04\xE9", "xxxxxxxxxxxxx"); });




        /*
        Unary Hashmap

        This is a hashmap using a key->bucket system, so an array of arrays keyed by a hash.
        We don't give a fuck about that though, we just want to iterate through all of the
        buckets and in turn each item in the bucket, because they are our operator entries.
        */
        for (auto& it : game_state->_scriptFunctions) {
            for (auto& entry : it) {
                unary_entry new_entry;
                new_entry.op = entry._operator;
                new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
                new_entry.name = entry._name.data();
                LOG(INFO) << "Found unary operator: " <<
                    new_entry.op->return_type.type_str() << " " <<
                    new_entry.name <<
                    "(" << new_entry.op->arg_type.type_str() << ")" <<
                    " @ " << new_entry.op->procedure_addr;
                std::string name = std::string(new_entry.name);
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                _unary_operators[name].push_back(new_entry);
            }
        }

        /*
        Binary Hashmap
        */
        for (auto& it : game_state->_scriptOperators) {
            for (auto& entry : it) {
                binary_entry new_entry;
                new_entry.op = entry._operator;
                new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
                new_entry.name = entry._name.data();
                LOG(INFO) << "Found binary operator: " <<
                    new_entry.op->return_type.type_str() << " " <<
                    "(" << new_entry.op->arg1_type.type_str() << ")" <<
                    new_entry.name <<
                    "(" << new_entry.op->arg2_type.type_str() << ")" <<
                    " @ " << new_entry.op->procedure_addr;
                std::string name = std::string(new_entry.name);
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                _binary_operators[name].push_back(new_entry);
            }
        }

        //Second part of finding the allocator. Done here so the second memorySearch is done when we are done parsing the Nulars
        uintptr_t stringOffset = future_stringOffset.get();
        auto future_allocatorVtablePtr = std::async([&]() {return (findInMemory(reinterpret_cast<char*>(&stringOffset), 4) - 4); });

        /*
        Nular Hashmap
        */
        for (auto& entry : game_state->_scriptNulars) {
            nular_entry new_entry;
            new_entry.op = entry._operator;
            new_entry.procedure_ptr_addr = reinterpret_cast<uintptr_t>(&entry._operator->procedure_addr);
            new_entry.name = entry._name.data();
            LOG(INFO) << "Found nular operator: " << new_entry.op->return_type.type_str() << " "
                << new_entry.name << " @ " << new_entry.op->procedure_addr;
            std::string name = std::string(new_entry.name);
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            _nular_operators[name].push_back(new_entry);
        }

        auto typeToEnum = [](const r_string& name) {     //I know this is ugly. Feel free to make it better
            if (name == "SCALAR") return types::__internal::GameDataType::SCALAR;
            if (name == "BOOL") return types::__internal::GameDataType::BOOL;
            if (name == "ARRAY") return types::__internal::GameDataType::ARRAY;
            if (name == "STRING") return types::__internal::GameDataType::STRING;
            if (name == "NOTHING") return types::__internal::GameDataType::NOTHING;
            if (name == "ANY") return types::__internal::GameDataType::ANY;
            if (name == "NAMESPACE") return types::__internal::GameDataType::NAMESPACE;
            if (name == "NaN") return types::__internal::GameDataType::NaN;
            if (name == "CODE") return types::__internal::GameDataType::CODE;
            if (name == "OBJECT") return types::__internal::GameDataType::OBJECT;
            if (name == "SIDE") return types::__internal::GameDataType::SIDE;
            if (name == "GROUP") return types::__internal::GameDataType::GROUP;
            if (name == "TEXT") return types::__internal::GameDataType::TEXT;
            if (name == "SCRIPT") return types::__internal::GameDataType::SCRIPT;
            if (name == "TARGET") return types::__internal::GameDataType::TARGET;
            if (name == "CONFIG") return types::__internal::GameDataType::CONFIG;
            if (name == "DISPLAY") return types::__internal::GameDataType::DISPLAY;
            if (name == "CONTROL") return types::__internal::GameDataType::CONTROL;
            if (name == "NetObject") return types::__internal::GameDataType::NetObject;
            if (name == "SUBGROUP") return types::__internal::GameDataType::SUBGROUP;
            if (name == "TEAM_MEMBER") return types::__internal::GameDataType::TEAM_MEMBER;
            if (name == "TASK") return types::__internal::GameDataType::TASK;
            if (name == "DIARY_RECORD") return types::__internal::GameDataType::DIARY_RECORD;
            if (name == "LOCATION") return types::__internal::GameDataType::LOCATION;
            return types::__internal::GameDataType::end;
        };

        //Game Types
        for (auto& entry : game_state->_scriptTypes) {
            if (!entry->_createFunction) continue; //Some types don't have create functions. Example: VECTOR.
            auto p1 = reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(entry->_createFunction) + 0x3);
            uintptr_t poolAlloc = *reinterpret_cast<uintptr_t*>(p1);
            LOG(INFO) << "Found Type operator: " << entry->_name << " create@ " << entry->_createFunction << " pool@ " << poolAlloc;
            OutputDebugStringA(entry->_name.data());
            OutputDebugStringA("\n");

            auto type = typeToEnum(entry->_name);
            if (poolAlloc && type != types::__internal::GameDataType::end) {
                _allocator._poolAllocs[static_cast<size_t>(type)] = reinterpret_cast<rv_pool_allocator*>(poolAlloc);
                _sqf_register_funcs._types[static_cast<size_t>(type)] = const_cast<__internal::gsTypeInfo*>(entry);
            }
        }


        _sqf_register_funcs._type_vtable = _binary_operators["arrayintersect"].front().op->arg1_type.v_table;
        //_sqf_register_funcs._types[static_cast<size_t>(types::__internal::GameDataType::ARRAY)] = reinterpret_cast<uintptr_t>(&_binary_operators["arrayintersect"].front().op->arg1_type);
        //_sqf_register_funcs._types[static_cast<size_t>(types::__internal::GameDataType::OBJECT)] = reinterpret_cast<uintptr_t>(&_binary_operators["doorphase"].front().op->arg1_type);
        //_sqf_register_funcs._types[static_cast<size_t>(types::__internal::GameDataType::STRING)] = reinterpret_cast<uintptr_t>(&_binary_operators["doorphase"].front().op->arg2_type);
        //_sqf_register_funcs._types[static_cast<size_t>(types::__internal::GameDataType::SCALAR)] = reinterpret_cast<uintptr_t>(&_binary_operators["doorphase"].front().op->return_type);
        //_sqf_register_funcs._types[static_cast<size_t>(types::__internal::GameDataType::BOOL)] = reinterpret_cast<uintptr_t>(&_unary_operators["isplayer"].front().op->return_type);
        //_sqf_register_funcs._types[static_cast<size_t>(types::__internal::GameDataType::ANY)] = reinterpret_cast<uintptr_t>(&_unary_operators["diag_log"].front().op->arg_type);

        //_sqf_register_funcs._operator_construct = future_operator_construct.get();
        //_sqf_register_funcs._operator_insert = future_operator_insert.get();
        //_sqf_register_funcs._unary_construct = future_unary_construct.get();
        //_sqf_register_funcs._unary_insert = future_unary_insert.get();
        _sqf_register_funcs._gameState = state_addr_;

        uintptr_t allocatorVtablePtr = future_allocatorVtablePtr.get();
        const char* test = getRTTIName(*reinterpret_cast<uintptr_t*>(allocatorVtablePtr));
        assert(strcmp(test, "?AVMemTableFunctions@@") == 0);
        _allocator.genericAllocBase = allocatorVtablePtr;
        _allocator.poolFuncAlloc = future_poolFuncAlloc.get();
        _allocator.poolFuncDealloc = future_poolFuncDealloc.get();
    }

    const unary_map & loader::unary() const {
        return _unary_operators;
    }

    const binary_map & loader::binary() const {
        return _binary_operators;
    }

    const nular_map & loader::nular() const {
        return _nular_operators;
    }

    const types::__internal::allocatorInfo* loader::get_allocator() const {
        return &_allocator;
    }

    const intercept::sqf_register_functions& loader::get_register_sqf_info() const {
        return _sqf_register_funcs;
    }

}