#pragma once
#include <stdio.h>
#include <set>
#include <mutex>
#include <thread>
#include <atomic>
#include "vector.hpp"
#include "pool.hpp"

namespace intercept {
    namespace types {
        typedef uintptr_t(__cdecl *nular_function)(char *, uintptr_t);
        typedef uintptr_t(__cdecl *unary_function)(char *, uintptr_t, uintptr_t);
        typedef uintptr_t(__cdecl *binary_function)(char *, uintptr_t, uintptr_t, uintptr_t);

        typedef std::set<std::string> value_types;
        typedef uintptr_t value_type;

        class rv_string {
        public:
            rv_string();
            rv_string(const rv_string &) = delete;
            rv_string(rv_string &&) = delete;
            rv_string & operator=(const rv_string &) = delete;
            rv_string & operator=(rv_string &&) = delete;

            uint32_t ref_count_internal;
            uint32_t length;
            char char_string; //#TODO add .natvis to display full string in Visual Studio dbg
            std::string string();
        };

        struct value_entry {
            rv_string *type_name;
        };

        struct compound_value_pair {
            value_entry *first;
            value_entry *second;
        };

        struct compound_value_entry {
            uintptr_t           v_table;
            compound_value_pair *types;
        };

        class op_value_entry {
        public:
            uintptr_t               v_table;
            value_entry             *single_type;
            compound_value_entry    *compound_type;
            value_types type();
            std::string type_str();
        };

        struct unary_operator {
            uintptr_t        v_table;
            uint32_t         ref_count;
            unary_function   *procedure_addr;
            op_value_entry   return_type;
            op_value_entry   arg_type;
        };

        struct unary_entry {
            const char *name;
            uintptr_t procedure_ptr_addr;
            unary_operator *op;
        };

        struct binary_operator {
            uintptr_t        v_table;
            uint32_t         ref_count;
            unary_function   *procedure_addr;
            op_value_entry   return_type;
            op_value_entry   arg1_type;
            op_value_entry   arg2_type;
        };

        struct binary_entry {
            const char *name;
            uintptr_t procedure_ptr_addr;
            binary_operator *op;
        };

        struct nular_operator {
            uintptr_t        v_table;
            uint32_t         ref_count;
            nular_function   *procedure_addr;
            op_value_entry   return_type;
        };

        struct nular_entry {
            const char *name;
            uintptr_t procedure_ptr_addr;
            nular_operator *op;
        };
        /*
        typedef union ref_count {
        public:
            ref_count() { current_count = 0; __initial_count = 0; }
            int32_t rv_ref_count;
            struct {
            public:
                uint16_t current_count;
                uint16_t __initial_count;
            };

            void set_initial(uint16_t val_, bool is_intercept_) {
                assert(val_ <= SHRT_MAX);
                __initial_count = val_;
                if (is_intercept_) {
                    __initial_count |= 1 << 15;
                }
            }

            uint16_t get_initial() {
                if ((__initial_count >> 15) & 1)
                    return __initial_count & ~(1 << 15);
                return __initial_count;
            }

            bool is_intercept() {
                return (__initial_count >> 15) & 1;
            }
        } ref_count_type;
        */

        class ref_count {
        public:
            ref_count() { _count = 0; };

            ref_count(int16_t initial_, int16_t actual_, bool is_intercept_) {
                _count = (((int32_t)initial_) << 16) | ((int32_t)actual_);
                if (is_intercept_)
                    _count |= 1 << 31;
            }

            void operator = (int16_t val_) {
                _count = (((int32_t)_initial()) << 16) | ((int32_t)val_);
            }

            uint16_t operator + (const int32_t val_) {
                return _actual() + val_;
            }

            uint16_t operator - (const int32_t val_) {
                return _actual() - val_;
            }

            void operator ++ (const int32_t val_) {
                _count = (((int32_t)_initial()) << 16) | ((int32_t)_actual() + 1);
            }

            void operator -- (const int32_t val_) {
                _count = (((int32_t)_initial()) << 16) | ((int32_t)_actual() - 1);
            }

            operator int16_t() {
                return _actual();
            }

            void set_initial(int16_t val_, bool is_intercept_) {
                _count = (((int32_t)val_) << 16) | (int32_t)_actual();
                if (is_intercept_)
                    _count |= 1 << 31;
            }

            int16_t get_initial() {
                return ((int16_t)(_count >> 16)) & ~(1 << 15);
            }

            bool is_intercept() {
                return (_count >> 31) & 1;
            }

            void clear_initial() {
                _count = (((int32_t)0) << 16) | (int32_t)_actual();
            }
        protected:
            inline int16_t _actual() {
#undef max // fucking hell i hate these macros, need to turn them off...
                return ((int32_t)((std::numeric_limits<int16_t>::max()) & _count));
            }
            inline int16_t _initial() {
                return (int16_t)(_count >> 16);
            }
            int32_t _count;
        };

        class game_data {
        public:
            uintptr_t type;
            ref_count ref_count_internal;
            uintptr_t data_type;
        };

        class game_data_number : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_number();
            game_data_number(float val_);
            game_data_number(const game_data_number &copy_);
            game_data_number(game_data_number &&move_);
            game_data_number & game_data_number::operator = (const game_data_number &copy_);
            game_data_number & game_data_number::operator = (game_data_number &&move_);
            static void* operator new(std::size_t sz_);
            static void operator delete(void* ptr_, std::size_t sz_);
            float number;
        protected:
            static thread_local game_data_pool<game_data_number> _data_pool;
        };

        class game_data_bool : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_bool();
            game_data_bool(bool val_);
            game_data_bool(const game_data_bool &copy_);
            game_data_bool(game_data_bool &&move_);
            game_data_bool & game_data_bool::operator = (const game_data_bool &copy_);
            game_data_bool & game_data_bool::operator = (game_data_bool &&move_);
            static void* operator new(std::size_t sz_);
            static void operator delete(void* ptr_, std::size_t sz_);
            bool val;
        protected:
            static thread_local game_data_pool<game_data_bool> _data_pool;
        };

        class rv_game_value {
        public:
            static uintptr_t __vptr_def;
            rv_game_value() : __vptr(rv_game_value::__vptr_def), data(nullptr) {};
            uintptr_t __vptr;
            game_data *data;
            const void deallocate();
        };

        class game_data_array;
        class internal_object;

        class game_value {
        public:
            game_value();
            void copy(const game_value & copy_);
            game_value(const game_value &copy_);
            game_value(game_value &&move_);

            game_value(const rv_game_value &internal_);
            game_value(float val_);
            game_value(bool val_);
            game_value(const std::string &val_);
            game_value(const char *);
            game_value(const std::vector<game_value> &list_);
            game_value(const vector3 &vec_);
            game_value(const vector2 &vec_);
            game_value(const internal_object &internal_);

            ~game_value();

            game_value & operator = (const game_value &copy_);
            game_value & operator = (game_value &&move_);

            game_value & operator = (float val_);
            game_value & operator = (bool val_);
            game_value & operator = (const std::string &val_);
            game_value & operator = (const char *val_);
            game_value & operator = (const std::vector<game_value> &list_);
            game_value & operator = (const vector3 &vec_);
            game_value & operator = (const vector2 &vec_);
            game_value & operator = (const internal_object &internal_);
            game_value & operator = (const rv_game_value &internal_);


            operator int();
            operator float();
            operator bool();
            operator std::string();
            operator rv_string &();
            operator rv_game_value *();
            operator vector3();
            operator vector2();
            operator int() const;
            operator float() const;
            operator bool() const;
            operator std::string() const;
            operator rv_string &() const;
            operator vector3() const;
            operator vector2() const;

            game_value & operator [](int i_);
            game_value operator [](int i_) const;

            uintptr_t type() const;

            size_t length() const;

            bool is_null();

            bool client_owned() const;
            rv_game_value rv_data;
        protected:
            void _free();
            
        };

        class game_data_array : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_array();
            game_data_array(size_t size_);
            game_data_array(const std::vector<game_value> &init_);
            game_data_array(const game_data_array &copy_);
            game_data_array(game_data_array &&move_);
            game_data_array & game_data_array::operator = (const game_data_array &copy_);
            game_data_array & game_data_array::operator = (game_data_array &&move_);
            void free();
            ~game_data_array();
            game_value *data;
            uint32_t length;
            uint32_t max_size;
            static void* operator new(std::size_t sz_);
            static void operator delete(void* ptr_, std::size_t sz_);
        protected:
            static thread_local game_data_pool<game_data_array> _data_pool;
            static thread_local game_data_array_pool<game_value> _array_pool;
        };

        class game_data_string : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_string();
            game_data_string(const std::string &str_);
            game_data_string(const game_data_string &copy_);
            game_data_string(game_data_string &&move_);
            game_data_string & game_data_string::operator = (const game_data_string &copy_);
            game_data_string & game_data_string::operator = (game_data_string &&move_);
            void free();
            ~game_data_string();
            rv_string *raw_string;
            static void* operator new(std::size_t sz_);
            static void operator delete(void* ptr_, std::size_t sz_);
        protected:
            static thread_local game_data_pool<game_data_string> _data_pool;
        };

        rv_string *allocate_string(size_t size_);
        void free_string(rv_string *str_);

        class game_data_group : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_group() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            void *group;
        };

        class game_data_config : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_config() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            void *config;
        };

        class game_data_control : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_control() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            void *control;
        };

        class game_data_display : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_display() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            void *display;
        };

        class game_data_location : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_location() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            void *location;
        };

        class game_data_script : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_script() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            void *script;
        };

        class game_data_side : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_side() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            void *side;
        };

        class game_data_rv_text : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_rv_text() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            void *rv_text;
        };

        class game_data_team : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_team() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            void *team;
        };

        class game_data_rv_namespace : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_rv_namespace() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            void *rv_namespace;
        };

        class game_data_code : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_code() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            rv_string *code_string;
            uintptr_t instruction_array;
            uint32_t instruction_array_size;
            uint32_t instruction_array_max_size;
            bool is_final;
        };

        class game_data_object : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_object() {
                type = type_def;
                data_type = data_type_def;
                ref_count_internal = 1;
                ref_count_internal.set_initial(1, true);
            };
            void *object;
        };

        template<size_t Size = 1024, size_t Alloc_Length = 512>
        class game_data_string_pool {
        public:
            game_data_string_pool() : _running(false) {
                for (size_t i = 0; i < Size; ++i)
                    _buy_entry(Alloc_Length);
            }

            inline rv_string * acquire(size_t alloc_length_) {
                std::lock_guard<std::mutex> collector_lock(_string_collection_mutex);
                if (_pool_queue.size() == 0 || alloc_length_ > Alloc_Length)
                    _buy_entry(alloc_length_);
                rv_string * ret = _pool_queue.front();
                ret->ref_count_internal = 1;
                ret->length = alloc_length_;
                *((char *)&ret->char_string + alloc_length_) = 0x0;
                _pool_queue.pop();
                return ret;
            }

            inline void release(rv_string *_ptr) {
                std::lock_guard<std::mutex> collector_lock(_string_collection_mutex);
                if (_ptr->ref_count_internal <= 1) {
                    _ptr->ref_count_internal = 0;
                    _ptr->length = 0;
                    _ptr->char_string = 0x0;
                    _pool_queue.push(_ptr);
                }
                else {
                    if (!_running) {
                        _running = true;
                        _collection_thread = std::thread(&game_data_string_pool::_string_collector, this);
                    }
                    _string_collection.push_back(_ptr);
                }
            }

            ~game_data_string_pool() {
                for (auto entry : _pool)
                    delete[] (char *)entry;
                _running = false;
                _collection_thread.join();
            }
        protected:
            std::queue<rv_string *> _pool_queue;
            std::vector<rv_string *> _pool;
            std::mutex _string_collection_mutex;
            std::thread _collection_thread;
            std::atomic<bool> _running;

            inline void _buy_entry(size_t alloc_length_) {
                char *raw_data = new char[sizeof(uint32_t) + sizeof(uint32_t) + alloc_length_];
                ((rv_string *)raw_data)->length = alloc_length_;
                ((rv_string *)raw_data)->ref_count_internal = 1;
                _pool_queue.push((rv_string *)raw_data);
                _pool.push_back((rv_string *)raw_data);
            }

            /*!
            @brief A list of strings to monitor for deletion, used by the string collector.
            */
            std::list<rv_string *> _string_collection;

            /*!
            @brief Collects a string and adds it to a queue that waits for its internal
            ref counter to reach 1, at which point it can be safely released.

            Strings allocated by Intercept are allocated in the Intercept host memory
            because the engine may or may not use them right away. In some cases the
            string may be held in some sort of execution logic for a significant time.
            Since these strings are normal internal strings, the engine will adjust
            their ref counter to account for this, and we need to monitor the ref counter
            to make sure that we can safely release it.

            @param str_ A pointer to the string to release.
            */
            void _string_collector()
            {
                while (_running) {
                    {
                        std::lock_guard<std::mutex> collector_lock(_string_collection_mutex);
                        for (auto it = _string_collection.begin(); it != _string_collection.end();) {
                            if ((*it)->ref_count_internal <= 1) {
                                rv_string *ptr = *it;
                                ptr->ref_count_internal = 0;
                                ptr->length = 0;
                                ptr->char_string = 0x0;
                                _pool_queue.push(ptr);
                                _string_collection.erase(it++);
                            }
                            else {
                                ++it;
                            }
                        }
                    }
                    sleep(250);
                }
            }
        };
    }
}