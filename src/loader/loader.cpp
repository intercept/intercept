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
        result_ = "1";
        if (!_patched) {
            std::pair<std::string, uint32_t> func_map;
            bool found = _find_initial_function(func_map);
            if (found) {
                HANDLE handle = GetModuleHandle(0); //or OpenProcess()
                void *baseAddress = (void*)handle;
                DWORD true_offset = func_map.second - (DWORD)baseAddress;
                LOG(INFO) << "True offset for patch function: " << func_map.first << " @ " << (unary_function)true_offset;
                DWORD offset = func_map.second;
                _initial_trampoline = (unary_function)offset;
                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());

                LONG errorCode = DetourAttach(&(PVOID &)_initial_trampoline, _initial_patch);
                DetourTransactionCommit();
                result_ = func_map.first;
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

    void loader::_do_function_walk(uint32_t state_addr_) {
        uint32_t unary_hash = state_addr_ + 16;
        uint32_t binary_hash = state_addr_ + 28;
        uint32_t nulars_hash = state_addr_ + 40;

        /*
        Unary Hashmap

        This is a hashmap using a key->bucket system, so an array of arrays keyed by a hash.
        We don't give a fuck about that though, we just want to iterate through all of the
        buckets and in turn each item in the bucket, because they are our operator entries.
        */
        uint32_t bucket_start = *(uint32_t *)unary_hash;
        uint32_t bucket_count = *(uint32_t *)(unary_hash + 4);


        for (uint32_t bucket_offset = 0; bucket_offset < bucket_count; ++bucket_offset) {

            uint32_t bucket = (bucket_start + (12 * bucket_offset));
            uint32_t bucket_length = *(uint32_t *)(bucket + 4);

            uint32_t entry_start = *(uint32_t *)bucket;

            for (uint32_t entry_offset = 0; entry_offset < bucket_length; ++entry_offset) {
                uint32_t entry = *(uint32_t *)(entry_start + (20 * entry_offset));
                unary_entry new_entry;
                new_entry.op = (unary_operator *)*(uint32_t *)(entry + 12);
                uint32_t name_entry = *(uint32_t *)entry;
                new_entry.name = (char *)(name_entry + 8);
                LOG(INFO) << "Found unary operator: " << new_entry.name << " @ " << new_entry.op->procedure_addr;
                _unary_operators[std::string(new_entry.name)] = new_entry;
            }
        }

        /*
        Binary Hashmap
        */
        bucket_start = *(uint32_t *)binary_hash;
        bucket_count = *(uint32_t *)(binary_hash + 4);


        for (uint32_t bucket_offset = 0; bucket_offset < bucket_count; ++bucket_offset) {

            uint32_t bucket = (bucket_start + (12 * bucket_offset));
            uint32_t bucket_length = *(uint32_t *)(bucket + 4);

            uint32_t entry_start = *(uint32_t *)bucket;

            for (uint32_t entry_offset = 0; entry_offset < bucket_length; ++entry_offset) {
                uint32_t entry = *(uint32_t *)(entry_start + (24 * entry_offset));
                binary_entry new_entry;
                new_entry.op = (binary_operator *)*(uint32_t *)(entry + 16);
                uint32_t name_entry = *(uint32_t *)entry;
                new_entry.name = (char *)(name_entry + 8);
                LOG(INFO) << "Found binary operator: " << new_entry.name << " @ " << new_entry.op->procedure_addr;
                _binary_operators[std::string(new_entry.name)] = new_entry;
            }
        }

        /*
        Nular Hashmap
        */
        bucket_start = *(uint32_t *)nulars_hash;
        bucket_count = *(uint32_t *)(nulars_hash + 4);


        for (uint32_t bucket_offset = 0; bucket_offset < bucket_count; ++bucket_offset) {

            uint32_t bucket = (bucket_start + (12 * bucket_offset));
            uint32_t bucket_length = *(uint32_t *)(bucket + 4);

            uint32_t entry_start = *(uint32_t *)bucket;

            for (uint32_t entry_offset = 0; entry_offset < bucket_length; ++entry_offset) {
                uint32_t entry = (entry_start + (40 * entry_offset));
                nular_entry new_entry;
                new_entry.op = (nular_operator *)*(uint32_t *)(entry + 8);
                uint32_t name_entry = *(uint32_t *)entry;
                new_entry.name = (char *)(name_entry + 8);
                LOG(INFO) << "Found nular operator: " << new_entry.name << " @ " << new_entry.op->procedure_addr;
                _nular_operators[std::string(new_entry.name)] = new_entry;
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

    bool loader::_find_initial_function(std::pair<std::string, uint32_t> &func_map) {
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
                    uint32_t rstring_ptr = (uint32_t)&(char_ptr[0]);
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
                        uint32_t rstring_parent_ptr = (uint32_t)&(rstring[0]);

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
                            uint32_t rstring_parent_container = (uint32_t)&(rstring_parent[0]);

                            // So lets get those enums and check and see if they are under 10 as a sanity check
                            uint32_t check1 = *(uint32_t *)(rstring_parent_container + 4);
                            uint32_t check2 = *(uint32_t *)(rstring_parent_container + 8);
                            if (check1 < 10 && check2 < 10) {
                                // Cool they are!
                                uint32_t rstring_check1 = *(uint32_t *)(rstring_parent_container + 12);
                                uint32_t rstring_check2 = *(uint32_t *)(rstring_parent_container + 16);

                                // Now lets check the length of those two strings at the end and see if they
                                // are 1) the same length as each other, and 2) the same length as the command
                                uint32_t length1 = *(uint8_t *)(rstring_check1 + 4);
                                uint32_t length2 = *(uint8_t *)(rstring_check2 + 4);
                                if (length1 == length2 && length1 == command.length() + 1) {
                                    uint32_t bucket_entry = *(uint32_t *)rstring_parent_container;
                                    uint32_t name_entry = *(uint32_t *)bucket_entry;
                                    char *name = (char *)(name_entry + 8);

                                    uint32_t op_entry = *(uint32_t *)(bucket_entry + 12);
                                    op_entry = *(uint32_t *)(op_entry + 8);
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