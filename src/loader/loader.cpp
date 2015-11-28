#include "loader.hpp"
#include "controller.hpp"
#include "detours.h"
#include <Windows.h>




namespace intercept {
    unary_function loader::_initial_trampoline;

    loader::loader() : _attached(false), _patched(false) {
    }

    loader::~loader() {

    }

    void loader::attach_controller() {
        if (!_attached) {
            _attached = true;
            controller::get().add("init_patch", std::bind(&intercept::loader::init_patch, this, std::placeholders::_1, std::placeholders::_2));
            controller::get().add("remove_patch", std::bind(&intercept::loader::remove_patch, this, std::placeholders::_1, std::placeholders::_2));
        }
    }

    int __cdecl loader::_initial_patch(char * a_, int b_, int c_)
    {
        loader::get()._do_function_walk(b_);
        return _initial_trampoline(a_, b_, c_);
    }

    bool loader::init_patch(const arguments &args_, std::string & result_) {
        uint32_t version = args_.as_uint32(0);
        result_ = "1";
        if (!_patched) {
            bool do_search = false;
            bool found = false;
            DWORD offset;
            std::string command_name;

            HANDLE handle = GetModuleHandle(0);
            void *base_address = (void*)handle;

            {
                std::ifstream cache_read("interceptcache", std::ios::binary);
                if (cache_read.is_open()) {
                    uint32_t cached_version, command_length;
                    cache_read.read((char *)&cached_version, sizeof(uint32_t));
                    cache_read.read((char *)&command_length, sizeof(uint32_t));
                    LOG(DEBUG) << "Command str len: " << command_length;
                    command_name.resize(command_length, ' ');
                    cache_read.read(&command_name[0], command_length);
                    cache_read.read((char *)&offset, sizeof(uintptr_t));
                    if(cached_version == version) {
                        LOG(INFO) << "Cached offset for build #" << cached_version << " patch function: " << command_name << " @ " << (unary_function)offset;
                        found = true;
                    }
                    else {
                        LOG(INFO) << "Cached build #" << cached_version << " != " << version << ", researching patch offset.";
                        do_search = true;
                    }
                }
                else {
                    do_search = true;
                }
            }
            if (do_search) {
                std::pair<std::string, uintptr_t> func_map;
                found = _find_initial_function(func_map);
                if (found) {
                    
                    std::ofstream cache_write("interceptcache", std::ios::binary);
                    offset = func_map.second - (DWORD)base_address;
                    LOG(INFO) << "Found offset for patch function: " << func_map.first << " @ " << (unary_function)offset;
                    if (cache_write.is_open()) {
                        cache_write.write((char *)&version, sizeof(uint32_t));
                        uint32_t command_length = func_map.first.length();
                        cache_write.write((char *)&command_length, sizeof(uint32_t));
                        cache_write.write(func_map.first.c_str(), command_length);
                        cache_write.write((char *)&offset, sizeof(uintptr_t));
                        LOG(INFO) << "Cache offset written";
                        command_name = func_map.first;
                    }
                }
            }
            if(found) {
                _initial_trampoline = (unary_function)(offset + (DWORD)base_address);
                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());

                LONG errorCode = DetourAttach(&(PVOID &)_initial_trampoline, _initial_patch);
                DetourTransactionCommit();
                result_ = command_name;
                _patched = true;
            }
            else {
                result_ = "-1";
            }
        }
        
        return true;
    }

    bool loader::remove_patch(const arguments &args_, std::string & result_) {
        result_ = "1";
        if(_patched) {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());

            LONG errorCode = DetourDetach(&(PVOID &)_initial_trampoline, _initial_patch);
            DetourTransactionCommit();
        }

        return true;
    }

    bool loader::get_function(std::string function_name_, unary_function & function_)
    {
        auto it = _unary_operators.find(function_name_);
        if (it != _unary_operators.end()) {
            function_ = (unary_function)it->second.op->procedure_addr;
            return true;
        }
        return false;
    }

    bool loader::get_function(std::string function_name_, binary_function & function_)
    {
        auto it = _binary_operators.find(function_name_);
        if (it != _binary_operators.end()) {
            function_ = (binary_function)it->second.op->procedure_addr;
            return true;
        }
        return false;
    }

    bool loader::get_function(std::string function_name_, nular_function & function_)
    {
        auto it = _nular_operators.find(function_name_);
        if (it != _nular_operators.end()) {
            function_ = (nular_function)it->second.op->procedure_addr;
            return true;
        }
        return false;
    }

    bool loader::hook_function(std::string function_name_, void * hook_, unary_function & trampoline_)
    {
        LOG(DEBUG) << "Attempting to hook unary function " << function_name_;
        if (get_function(function_name_, trampoline_)) {
            return _hook(hook_, &(void *&)trampoline_, trampoline_);
        }
        return false;
    }

    bool loader::hook_function(std::string function_name_, void * hook_, binary_function & trampoline_)
    {
        LOG(DEBUG) << "Attempting to hook binary function " << function_name_;
        if (get_function(function_name_, trampoline_)) {
            return _hook(hook_, &(void *&)trampoline_, trampoline_);
        }
        return false;
    }

    bool loader::hook_function(std::string function_name_, void * hook_, nular_function & trampoline_)
    {
        LOG(DEBUG) << "Attempting to hook nular function " << function_name_;
        if (get_function(function_name_, trampoline_)) {
            return _hook(hook_, &(void *&)trampoline_, trampoline_);
        }
        return false;
    }

    bool loader::unhook_function(std::string function_name_, void * hook_, unary_function & trampoline_)
    {
        LOG(DEBUG) << "Attempting to unhook unary function " << function_name_;
        unary_function original_function;
        if (get_function(function_name_, original_function)) {
            return _unhook(hook_, &(void *&)trampoline_, original_function);
        }
    }

    bool loader::unhook_function(std::string function_name_, void * hook_, binary_function & trampoline_)
    {
        LOG(DEBUG) << "Attempting to unhook binary function " << function_name_;
        binary_function original_function;
        if (get_function(function_name_, original_function)) {
            return _unhook(hook_, &(void *&)trampoline_, original_function);
        }
    }

    bool loader::unhook_function(std::string function_name_, void * hook_, nular_function & trampoline_)
    {
        LOG(DEBUG) << "Attempting to unhook nular function " << function_name_;
        nular_function original_function;
        if (get_function(function_name_, original_function)) {
            return _unhook(hook_, &(void *&)trampoline_, original_function);
        }
        return false;
    }

    bool loader::_hook(void * hook_, void ** trampoline_, void * original_function_)
    {
        if (_hooked_functions.find((uintptr_t)original_function_) == _hooked_functions.end()) {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            long error_code = DetourAttach(trampoline_, hook_);
            DetourTransactionCommit();
            if (error_code) {
                LOG(ERROR) << "Hooking function failed! Error code: " << error_code;
                return false;
            }
            _hooked_functions.insert((uintptr_t)original_function_);
            LOG(DEBUG) << "Hook success!";
            return true;
        }
        return false;
    }

    bool loader::_unhook(void * hook_, void ** trampoline_, void * original_function_)
    {
        if (_hooked_functions.find((uintptr_t)original_function_) != _hooked_functions.end()) {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            long error_code = DetourDetach(trampoline_, hook_);
            DetourTransactionCommit();
            if (error_code) {
                LOG(ERROR) << "Unhooking function failed! Error code: " << error_code;
                return false;
            }
            _hooked_functions.erase((uintptr_t)original_function_);
            LOG(DEBUG) << "Unhook success!";
            return true;
        }
        return false;
    }

    void loader::_do_function_walk(uintptr_t state_addr_) {
        uintptr_t unary_hash = state_addr_ + 16;
        uintptr_t binary_hash = state_addr_ + 28;
        uintptr_t nulars_hash = state_addr_ + 40;

        /*
        Unary Hashmap

        This is a hashmap using a key->bucket system, so an array of arrays keyed by a hash.
        We don't give a fuck about that though, we just want to iterate through all of the
        buckets and in turn each item in the bucket, because they are our operator entries.
        */
        uintptr_t bucket_start = *(uintptr_t *)unary_hash;
        uint32_t bucket_count = *(uint32_t *)(unary_hash + 4);


        for (uint32_t bucket_offset = 0; bucket_offset < bucket_count; ++bucket_offset) {

            uintptr_t bucket = (bucket_start + (12 * bucket_offset));
            uint32_t bucket_length = *(uintptr_t *)(bucket + 4);

            uintptr_t entry_start = *(uintptr_t *)bucket;

            for (uint32_t entry_offset = 0; entry_offset < bucket_length; ++entry_offset) {
                uintptr_t entry = *(uintptr_t *)(entry_start + (20 * entry_offset));
                unary_entry new_entry;
                new_entry.op = (unary_operator *)*(uintptr_t *)(entry + 12);
                uintptr_t name_entry = *(uintptr_t *)entry;
                new_entry.name = (char *)(name_entry + 8);
                LOG(INFO) << "Found unary operator: " << new_entry.name << " @ " << new_entry.op->procedure_addr;
                std::string name = std::string(new_entry.name);
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                _unary_operators[name] = new_entry;
            }
        }

        /*
        Binary Hashmap
        */
        bucket_start = *(uintptr_t *)binary_hash;
        bucket_count = *(uint32_t *)(binary_hash + 4);


        for (uint32_t bucket_offset = 0; bucket_offset < bucket_count; ++bucket_offset) {

            uintptr_t bucket = (bucket_start + (12 * bucket_offset));
            uint32_t bucket_length = *(uint32_t *)(bucket + 4);

            uintptr_t entry_start = *(uintptr_t *)bucket;

            for (uint32_t entry_offset = 0; entry_offset < bucket_length; ++entry_offset) {
                uintptr_t entry = *(uintptr_t *)(entry_start + (24 * entry_offset));
                binary_entry new_entry;
                new_entry.op = (binary_operator *)*(uintptr_t *)(entry + 16);
                uintptr_t name_entry = *(uintptr_t *)entry;
                new_entry.name = (char *)(name_entry + 8);
                LOG(INFO) << "Found binary operator: " << new_entry.name << " @ " << new_entry.op->procedure_addr;
                std::string name = std::string(new_entry.name);
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                _binary_operators[name] = new_entry;
            }
        }

        /*
        Nular Hashmap
        */
        bucket_start = *(uintptr_t *)nulars_hash;
        bucket_count = *(uint32_t *)(nulars_hash + 4);


        for (uint32_t bucket_offset = 0; bucket_offset < bucket_count; ++bucket_offset) {

            uintptr_t bucket = (bucket_start + (12 * bucket_offset));
            uint32_t bucket_length = *(uintptr_t *)(bucket + 4);

            uintptr_t entry_start = *(uintptr_t *)bucket;

            for (uint32_t entry_offset = 0; entry_offset < bucket_length; ++entry_offset) {
                uintptr_t entry = (entry_start + (40 * entry_offset));
                nular_entry new_entry;
                new_entry.op = (nular_operator *)*(uintptr_t *)(entry + 8);
                uintptr_t name_entry = *(uintptr_t *)entry;
                new_entry.name = (char *)(name_entry + 8);
                LOG(INFO) << "Found nular operator: " << new_entry.name << " @ " << new_entry.op->procedure_addr;
                std::string name = std::string(new_entry.name);
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                _nular_operators[name] = new_entry;
            }
        }
    }

    void loader::_find_locs(HANDLE process, std::string const pattern, std::vector<unsigned char *> &output) {

        unsigned char *p = NULL;
        MEMORY_BASIC_INFORMATION info;
        for (p = NULL;
        VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info);
            p += info.RegionSize)
        {
            std::vector<char> buffer;
            std::vector<char>::iterator pos;

            if (info.State == MEM_COMMIT &&
                (info.Type == MEM_MAPPED || info.Type == MEM_PRIVATE))
            {
                DWORD bytes_read;
                buffer.resize(info.RegionSize);
                ReadProcessMemory(process, p, &buffer[0], info.RegionSize, &bytes_read);
                buffer.resize(bytes_read);
                for (pos = buffer.begin();
                buffer.end() != (pos = std::search(pos, buffer.end(), pattern.begin(), pattern.end()));
                    ++pos)
                {
                    output.push_back(p + (pos - buffer.begin()));
                }
            }
        }
    }

    void loader::_find_locs_ptr(HANDLE process, char *find, std::vector<unsigned char *> &output) {

        unsigned char *p = NULL;
        MEMORY_BASIC_INFORMATION info;

        std::vector<char> pattern;
        pattern.resize(4);
        pattern[0] = find[0];
        pattern[1] = find[1];
        pattern[2] = find[2];
        pattern[3] = find[3];


        for (p = NULL;
        VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info);
            p += info.RegionSize)
        {
            std::vector<char> buffer;
            std::vector<char>::iterator pos;

            if (info.State == MEM_COMMIT &&
                (info.Type == MEM_MAPPED || info.Type == MEM_PRIVATE))
            {
                DWORD bytes_read;
                buffer.resize(info.RegionSize);
                ReadProcessMemory(process, p, &buffer[0], info.RegionSize, &bytes_read);
                buffer.resize(bytes_read);
                for (pos = buffer.begin();
                buffer.end() != (pos = std::search(pos, buffer.end(), pattern.begin(), pattern.end()));
                    ++pos)
                {
                    output.push_back(p + (pos - buffer.begin()));
                }
            }
        }
    }

    bool loader::_find_initial_function(std::pair<std::string, uintptr_t> &func_map) {
        HANDLE process = GetCurrentProcess();

        SYSTEM_INFO si;
        GetSystemInfo(&si);

        std::vector<std::string> sqf_commands;
        //sqf_commands.push_back("toArray");
        sqf_commands.push_back("ceil");
        sqf_commands.push_back("floor");
        LOG(INFO) << "Starting initial hook search...";
        for (auto command : sqf_commands) {
            LOG(INFO) << "Looking for command: " << command;
            std::vector<unsigned char *> ptr_results;
            // Find the string locations... Specific string search function.
            _find_locs(process, command, ptr_results);
            for (auto char_ptr : ptr_results) {
                // simple check to see if this is an RString instance
                // try and get the length at -4 and check it against 
                // incoming command.
                uint32_t length = (uint32_t)*(char_ptr - 4);
                if (length == command.length() + 1) {
                    // ok this is an RString (most likely) so lets
                    // set the pointer to the actual start of the object
                    // which is at -8
                    uintptr_t rstring_ptr = (uintptr_t)&(char_ptr[0]);
                    rstring_ptr -= 8;
                    // RString is an odd beast, it caches the allocated char array for
                    // some reason, probably because of Eastern Europe and their crappy
                    // computers with no ram (also this was written in like 1999 so wtf).
                    // Because of this you can get multiple objects with the same data...
                    // ... anyway I digress...

                    // cool now lets search for all references to this memory address!
                    std::vector<unsigned char *> rstring_ptr_results;// = GetAddressOfData(GetCurrentProcessId(), (uint8_t *)&rstring_ptr, 4);
                    _find_locs_ptr(process, (char *)&rstring_ptr, rstring_ptr_results);
                    for (auto rstring : rstring_ptr_results) {
                        // these are the objects that contain a reference to this RString.
                        uintptr_t rstring_parent_ptr = (uintptr_t)&(rstring[0]);

                        // Our goal here is to find our place first inside an array of operator entries,
                        // then try and find that array in a hash map bucket, and then with that bucket,
                        // find the start of the hashmap. Once we do that we can iterate through the bucket
                        // arrays and easily get SQF operator addresses.

                        // So lets search for all objects that contain a reference to this parent object.
                        std::vector<unsigned char *> rstring_parent_results;// = GetAddressOfData(GetCurrentProcessId(), (uint8_t *)&rstring_parent_ptr, 4);
                        _find_locs_ptr(process, (char *)&rstring_parent_ptr, rstring_parent_results);
                        for (auto rstring_parent : rstring_parent_results) {
                            // Ok this is the check to see if we have an operator object
                            // It looks something like this in memory for a unary one:
                            // 0x0072BCB8  0070ce20   Îp.   // this is our object from above!
                            // 0x0072BCBC  00000001  ....   // this is some sort of enum value, not sure
                            // 0x0072BCC0  00000001  ....   // this is also an enum value, these should never go above 10
                            // 0x0072BCC4  0070a0a0    p.   // rstring_check1 (ill explain later)
                            // 0x0072BCC8  0070a0a0    p.   // rstring_check2 (trust me)

                            // So the end of each array entry has two strings, these strings are command names.
                            // They might be different, in this case they are the same, and sometimes they are
                            // in different cases (I believe this is a comref thing, internal and pretty, gotta
                            // dig around a bit more to figure that out).

                            // our entry
                            uintptr_t rstring_parent_container = (uintptr_t)&(rstring_parent[0]);

                            // So lets get those enums and check and see if they are under 10 as a sanity check
                            uint32_t check1 = *(uint32_t *)(rstring_parent_container + 4);
                            uint32_t check2 = *(uint32_t *)(rstring_parent_container + 8);
                            if (check1 < 10 && check2 < 10) {
                                // Cool they are!
                                uintptr_t rstring_check1 = *(uintptr_t *)(rstring_parent_container + 12);
                                uintptr_t rstring_check2 = *(uintptr_t *)(rstring_parent_container + 16);

                                // Now lets check the length of those two strings at the end and see if they
                                // are 1) the same length as each other, and 2) the same length as the command
                                uint32_t length1 = *(uint32_t *)(rstring_check1 + 4);
                                uint32_t length2 = *(uint32_t *)(rstring_check2 + 4);
                                if (length1 == length2 && length1 == command.length() + 1) {
                                    uintptr_t bucket_entry = *(uintptr_t *)rstring_parent_container;
                                    uintptr_t name_entry = *(uintptr_t *)bucket_entry;
                                    char *name = (char *)(name_entry + 8);

                                    uintptr_t op_entry = *(uintptr_t *)(bucket_entry + 12);
                                    op_entry = *(uintptr_t *)(op_entry + 8);
                                    LOG(INFO) << "Found Initial Function Hook: " << name << " @ " << (unary_function)op_entry;
                                    func_map.first = name;
                                    func_map.second = op_entry;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    

   
}