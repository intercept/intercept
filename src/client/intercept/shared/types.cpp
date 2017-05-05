#include "shared\types.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"
#include <assert.h>
#include <future>
#include <sstream> //Debugging

#define INTERNAL_TAG 0x0000dede

#if INTERCEPT_HOST_DLL
#include "loader.hpp"
#define GET_ENGINE_ALLOCATOR intercept::loader::get().get_allocator();
#else
#define GET_ENGINE_ALLOCATOR client::host::functions.get_engine_allocator()
#endif

namespace intercept {
    namespace __internal {
        
        class mem_leak_watcher {
        public:
            mem_leak_watcher() {
                static auto fut = std::async(std::launch::async,[&]() {
                    while (game_data_number::pool_alloc_base == nullptr) std::this_thread::sleep_for(std::chrono::seconds(5));
                    while (true) {
                        _mut.lock();
                        auto it = _allocs.begin();
                        auto _now = std::chrono::system_clock::now() - std::chrono::seconds(5);
                        while (it != _allocs.end() && it->second > _now) {
                            static auto numberdef = game_data_number::type_def;
                            if (*reinterpret_cast<uintptr_t*>(static_cast<refcount*>(it->first)) != numberdef) {//Was already deleted
                                _allocs.erase(it);
                                it = _allocs.begin();
                                if (it == _allocs.end()) break;
                            }
                             ++it;
                        };


                         if (it != _allocs.end()) {
                             std::stringstream stream;
                             stream << "memLeak " << "SCALAR " << std::hex << it->first << "\n";
                             OutputDebugStringA(stream.str().c_str());
                             _allocs.erase(it);
                         }
                        _mut.unlock();
                        std::this_thread::sleep_for(std::chrono::milliseconds(5));
                        std::stringstream stream;
                        stream << "ScalarPool " << game_data_number::pool_alloc_base->allocated_count << "\n";
                        OutputDebugStringA(stream.str().c_str());
                        
                    }
                });
            }
            void add_alloc(game_data_number* _al) {
                _mut.lock();
                _allocs.insert({ _al,std::chrono::system_clock::now() });
                _mut.unlock();
            }

            std::map<game_data_number*, std::chrono::system_clock::time_point> _allocs;
            std::mutex _mut;
        };


    }


    namespace types {
        uintptr_t game_data_string::type_def;
        uintptr_t game_data_string::data_type_def;
        rv_pool_allocator* game_data_string::pool_alloc_base;
        thread_local game_data_pool<game_data_string> game_data_string::_data_pool;

        uintptr_t game_data_number::type_def;
        uintptr_t game_data_number::data_type_def;
        rv_pool_allocator* game_data_number::pool_alloc_base;
        thread_local game_data_pool<game_data_number> game_data_number::_data_pool;

        uintptr_t game_data_array::type_def;
        uintptr_t game_data_array::data_type_def;
        rv_pool_allocator* game_data_array::pool_alloc_base;
        thread_local game_data_pool<game_data_array> game_data_array::_data_pool;
        thread_local game_data_array_pool<game_value> game_data_array::_array_pool;

        uintptr_t game_data_bool::type_def;
        uintptr_t game_data_bool::data_type_def;
        rv_pool_allocator* game_data_bool::pool_alloc_base;
        thread_local game_data_pool<game_data_bool> game_data_bool::_data_pool;

        uintptr_t game_data_code::type_def;
        uintptr_t game_data_code::data_type_def;

        uintptr_t game_data_group::type_def;
        uintptr_t game_data_group::data_type_def;

        uintptr_t game_data_config::type_def;
        uintptr_t game_data_config::data_type_def;

        uintptr_t game_data_control::type_def;
        uintptr_t game_data_control::data_type_def;

        uintptr_t game_data_display::type_def;
        uintptr_t game_data_display::data_type_def;

        uintptr_t game_data_location::type_def;
        uintptr_t game_data_location::data_type_def;

        uintptr_t game_data_script::type_def;
        uintptr_t game_data_script::data_type_def;

        uintptr_t game_data_side::type_def;
        uintptr_t game_data_side::data_type_def;

        uintptr_t game_data_rv_text::type_def;
        uintptr_t game_data_rv_text::data_type_def;

        uintptr_t game_data_team::type_def;
        uintptr_t game_data_team::data_type_def;

        uintptr_t game_data_rv_namespace::type_def;
        uintptr_t game_data_rv_namespace::data_type_def;

        uintptr_t game_data_object::type_def;
        uintptr_t game_data_object::data_type_def;



        uintptr_t game_value::__vptr_def;



        rv_string::rv_string() : length(0), ref_count_internal(0)
        {
        }

        std::string rv_string::string() {
            return std::string((char *)&char_string);
        }

        value_types op_value_entry::type() {
            if (single_type != NULL) {
                return{ single_type->type_name->string() };
            }
            else {
                return{
                    compound_type->types->first->type_name->string(),
                    compound_type->types->second->type_name->string()
                };
            }
        }

        std::string op_value_entry::type_str() {
            if (single_type != NULL) {
                return single_type->type_name->string();
            }
            else {
                return
                    compound_type->types->first->type_name->string() + "_" +
                    compound_type->types->second->type_name->string();
            }
        }

        game_data_number::game_data_number() {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            number = 0.0f;
        }

        game_data_number::game_data_number(float val_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            number = val_;
        }

        game_data_number::game_data_number(const game_data_number & copy_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            number = copy_.number;
        }

        game_data_number::game_data_number(game_data_number && move_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            number = move_.number;
        }

        game_data_number & game_data_number::operator=(const game_data_number & copy_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            number = copy_.number;
            return *this;
        }

        game_data_number & game_data_number::operator=(game_data_number && move_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            number = move_.number;
            return *this;
        }

        inline void * game_data_number::operator new(std::size_t)
        {
            return pool_alloc_base->allocate(1);
        }

        inline void game_data_number::operator delete(void * ptr_, std::size_t)
        {
            return pool_alloc_base->deallocate(ptr_);
        }

        game_data_bool::game_data_bool() {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            val = false;
        }

        game_data_bool::game_data_bool(bool val_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            val = val_;
        }

        game_data_bool::game_data_bool(const game_data_bool & copy_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            val = copy_.val;
        }

        game_data_bool::game_data_bool(game_data_bool && move_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            val = move_.val;
        }

        game_data_bool & game_data_bool::operator=(const game_data_bool & copy_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            val = copy_.val;
            return *this;
        }

        game_data_bool & game_data_bool::operator=(game_data_bool && move_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            val = move_.val;
            return *this;
        }

        inline void * game_data_bool::operator new(std::size_t)
        {
            return pool_alloc_base->allocate(1);
        }

        inline void game_data_bool::operator delete(void * ptr_, std::size_t)
        {
            return pool_alloc_base->deallocate(ptr_);
        }

        game_data_string::game_data_string() {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
        }

        game_data_string::game_data_string(const std::string &str_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            raw_string = r_string(str_.c_str(),str_.length());
           /* raw_string = allocate_string(str_.length() + 1);
            memcpy(&raw_string->char_string, str_.c_str(), str_.length() + 1);
            raw_string->length = str_.length() + 1;
            

            */

        }

        game_data_string::game_data_string(const game_data_string & copy_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            raw_string = copy_.raw_string;
        }

        game_data_string::game_data_string(game_data_string && move_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            raw_string = move_.raw_string;
            move_.raw_string = nullptr;
        }

        game_data_string & game_data_string::operator=(const game_data_string & copy_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            raw_string = copy_.raw_string;
            return *this;
        }

        game_data_string & game_data_string::operator=(game_data_string && move_)
        {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            _refcount = move_._refcount;
            raw_string = move_.raw_string;
            move_.raw_string = nullptr;
            return *this;
        }

        void game_data_string::free() {
            //#TODO dealloc?
        }

        game_data_string::~game_data_string()
        {
            free();
        }

        void * game_data_string::operator new(std::size_t)
        {
            return pool_alloc_base->allocate(1);
        }

        void game_data_string::operator delete(void * ptr_, std::size_t)
        {
            return pool_alloc_base->deallocate(ptr_);
        }

        game_data_array::game_data_array() {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            length = 0;
            max_size = 0;
            data = nullptr;
        }

        game_data_array::game_data_array(size_t size_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            data = rv_allocator<game_value>::createArray(size_); //_array_pool.acquire(size_);
            length = size_;
            max_size = size_;
        }

        game_data_array::game_data_array(const std::initializer_list<game_value> &init_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            data = rv_allocator<game_value>::createArray(init_.size()); //_array_pool.acquire(init_.size());
            length = init_.size();
            max_size = init_.size();
            size_t i = 0;
            for (auto& it : init_)
                data[i++] = it;
        }

        game_data_array::game_data_array(const std::vector<game_value> &init_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            data = rv_allocator<game_value>::createArray(init_.size()); //_array_pool.acquire(init_.size());
            length = init_.size();
            max_size = init_.size();
            size_t i = 0;
            for (auto& it : init_)
                data[i++] = it;
        }

        game_data_array::game_data_array(const game_data_array & copy_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            length = copy_.length;
            max_size = copy_.max_size;
            data = rv_allocator<game_value>::createArray(length); //_array_pool.acquire(length);
            for (size_t i = 0; i < length; ++i)
                data[i] = copy_.data[i];
        }

        game_data_array::game_data_array(game_data_array && move_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            if (data)
                rv_allocator<game_value>::deallocate(data); //_array_pool.release(data);
            data = move_.data;
            length = move_.length;
            max_size = move_.max_size;
            move_.data = nullptr;
        }

        game_data_array & game_data_array::operator = (const game_data_array &copy_) {
            *reinterpret_cast<uintptr_t*>(this) = type_def;
            *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            length = copy_.length;
            data = rv_allocator<game_value>::createArray(length); //_array_pool.acquire(length);
            for (size_t i = 0; i < length; ++i)
                data[i] = copy_.data[i];
            return *this;
        }

        game_data_array & game_data_array::operator = (game_data_array &&move_) {
            if (this == &move_)
                return *this;
            if (data)
                rv_allocator<game_value>::deallocate(data); //_array_pool.release(data);
            data = move_.data;
            length = move_.length;
            max_size = move_.max_size;
            move_.data = nullptr;
            return *this;
        }

        void game_data_array::free() {
            //Should never be called. Because this call goes through the vtable and we will call Arma's function
            if (data) {
                for (auto it = 0u; it < length; ++it) {
                    data[it].~game_value();
                }
                rv_allocator<game_value>::deallocate(data); // _array_pool.release(data);
                data = nullptr;
            }
                
        }

        game_data_array::~game_data_array() {
            free();
        }

        void * game_data_array::operator new(std::size_t)
        {
            return pool_alloc_base->allocate(1);
        }

        void game_data_array::operator delete(void * ptr_, std::size_t)
        {
            return pool_alloc_base->deallocate(ptr_);
        }

        game_value::game_value() {
            set_vtable(__vptr_def);
            data = nullptr;
        }

        void game_value::copy(const game_value & copy_) {
            set_vtable(copy_.get_vtable());
            if (copy_.data) {
                data = copy_.data;
            }
        }

        game_value::game_value(const game_value & copy_) {
            copy(copy_);
        }

        game_value::game_value(game_value && move_) {
            set_vtable(move_.get_vtable());
            data = move_.data;
            move_.data = nullptr;
        }

        //game_value::game_value(const rv_game_value &internal_)
        //{
        //    __vptr = internal_.__vptr;
        //    data = internal_.data;
        //}

        game_value::game_value(float val_) {
            set_vtable(__vptr_def);
            data = new game_data_number(val_);
        }

        game_value::game_value(bool val_) {
            set_vtable(__vptr_def);
            data = new game_data_bool(val_);
        }

        game_value::game_value(const std::string &val_) {
            set_vtable(__vptr_def);
            data = new game_data_string(val_);
        }

        game_value::game_value(const char *val_) {
            set_vtable(__vptr_def);
            data = new game_data_string(val_);
        }

        game_value::game_value(const std::vector<game_value> &list_) {
            set_vtable(__vptr_def);
            data = new game_data_array(list_);
        }

        game_value::game_value(const std::initializer_list<game_value> &list_) {
            set_vtable(__vptr_def);
            data = new game_data_array(list_);
        }

        game_value::game_value(const vector3 & vec_) {
            set_vtable(__vptr_def);
            data = new game_data_array({ vec_.x, vec_.y, vec_.z });
        }

        game_value::game_value(const vector2 & vec_) {
            set_vtable(__vptr_def);
            data = new game_data_array({ vec_.x, vec_.y });
        }
        game_value::game_value(const internal_object &internal_) {
            set_vtable(__vptr_def); //object class has bugged vtable :u
            data = internal_.data;
        }
        game_value::~game_value() {
            data = nullptr;
            _free();
        }

        void game_value::_free()
        {
              //#TODO handle deallocation?

            /*
            // Ghetto superstar...
            if (data) {
                data->ref_count_internal--;
                if (data->ref_count_internal < data->ref_count_internal.get_initial()) {
                    if (data->ref_count_internal.is_intercept()) {
                        data->ref_count_internal.clear_initial(); // make sure we clear out the initial value, so it goes back to a pure 32 bit int.
                        if (data && data->_vtable == game_data_number::type_def)
                            delete (game_data_number *)data;

                        else if (data && data->_vtable == game_data_string::type_def)
                            delete (game_data_string *)data;

                        else if (data && data->_vtable == game_data_array::type_def)
                            delete (game_data_array *)data;

                        else if (data && data->_vtable == game_data_bool::type_def)
                            delete (game_data_bool *)data;

                        else if (data)
                            delete data;
                    }
                    else {
                        data->ref_count_internal.clear_initial(); // make sure we clear out the initial value, so it goes back to a pure 32 bit int.
                        client::host::functions.free_value(this);
                        data = nullptr;
                    }
                }
            }
            */



        }

        uintptr_t game_value::get_vtable() const {
            return *reinterpret_cast<const uintptr_t*>(this);
        }

        void game_value::set_vtable(uintptr_t vt) {
            *reinterpret_cast<uintptr_t*>(this) = vt;
        }

        game_value & game_value::operator = (const game_value &copy_) {
            copy(copy_);
            return *this;
        }
        game_value & game_value::operator = (game_value &&move_) {
            if (this == &move_)
                return *this;
            set_vtable(move_.get_vtable());
            data = move_.data;
            move_.data = nullptr;
            return *this;
        }

        game_value & game_value::operator=(const float val_)
        {
            data = new game_data_number(val_);
            return *this;
        }

        game_value & game_value::operator=(bool val_)
        {
            data = new game_data_bool(val_);
            return *this;
        }

        game_value & game_value::operator=(const std::string &val_)
        {
            data = new game_data_string(val_);
            return *this;
        }

        game_value & game_value::operator=(const char * val_)
        {
            data = new game_data_string(val_);
            return *this;
        }

        game_value & game_value::operator=(const std::vector<game_value> &list_)
        {
            data = new game_data_array(list_);
            return *this;
        }

        game_value & game_value::operator=(const vector3 &vec_)
        {
            data = new game_data_array({ vec_.x, vec_.y, vec_.z });
            return *this;
        }

        game_value & game_value::operator=(const vector2 &vec_)
        {
            data = new game_data_array({ vec_.x, vec_.y });
            return *this;
        }

        game_value & game_value::operator=(const internal_object &internal_)
        {
            data = internal_.data;
            set_vtable(internal_.get_vtable());
            return *this;
        }

        //game_value & game_value::operator=(const rv_game_value &internal_)
        //{
        //    if (data)
        //        _free();
        //    data = internal_.data;
        //    __vptr = internal_.__vptr;
        //    return *this;
        //}

        game_value::operator int()
        {
            if (data && *reinterpret_cast<uintptr_t*>(data.getRef()) == game_data_number::type_def)
                return static_cast<int>(static_cast<game_data_number *>(data.getRef())->number);
            return 0;
        }

        game_value::operator float()
        {
            if (data && *reinterpret_cast<uintptr_t*>(data.getRef()) == game_data_number::type_def)
                return ((game_data_number *)data.getRef())->number;
            return 0.0f;
        }

        game_value::operator bool()
        {
            if (data && *reinterpret_cast<uintptr_t*>(data.getRef()) == game_data_bool::type_def)
                return ((game_data_bool *)data.getRef())->val;
            return false;
        }

        game_value::operator r_string ()
        {
            return ((game_data_string *)data.getRef())->raw_string;
        }

        game_value::operator vector3()
        {
            if (((game_data_array *)data.getRef())->length == 3)
                return vector3(
                    ((game_data_array *)data.getRef())->data[0],
                    ((game_data_array *)data.getRef())->data[1],
                    ((game_data_array *)data.getRef())->data[2]
                    );
            return vector3();
        }

        game_value::operator vector2()
        {
            if(((game_data_array *)data.getRef())->length == 2)
                return vector2(
                    ((game_data_array *)data.getRef())->data[0],
                    ((game_data_array *)data.getRef())->data[1]
                    );
            return vector2();
        }

        game_value::operator int() const
        {
            if (data && *reinterpret_cast<uintptr_t*>(data.getRef()) == game_data_number::type_def)
                return static_cast<int>(((game_data_number *)data.getRef())->number);
            return 0;
        }

        game_value::operator float() const
        {
            if (data && *reinterpret_cast<uintptr_t*>(data.getRef()) == game_data_number::type_def)
                return ((game_data_number *)data.getRef())->number;
            return 0.0f;
        }

        game_value::operator bool() const
        {
            if (data && *reinterpret_cast<uintptr_t*>(data.getRef()) == game_data_bool::type_def)
                return ((game_data_bool *)data.getRef())->val;
            return false;
        }

        game_value::operator r_string () const
        {
            return ((game_data_string *)data.getRef())->raw_string;
        }

        game_value::operator vector3() const
        {
            return vector3(
                ((game_data_array *)data.getRef())->data[0],
                ((game_data_array *)data.getRef())->data[1],
                ((game_data_array *)data.getRef())->data[2]
                );
        }

        game_value::operator vector2() const
        {
            return vector2(
                ((game_data_array *)data.getRef())->data[0],
                ((game_data_array *)data.getRef())->data[1]
                );
        }

        game_value::operator std::string() const
        {
            if (data && *reinterpret_cast<uintptr_t*>(data.getRef()) == game_data_string::type_def)
                return std::string(((game_data_string *)data.getRef())->raw_string);
            return std::string();
        }

        game_value::operator std::string()
        {
            if (data && *reinterpret_cast<uintptr_t*>(data.getRef()) == game_data_string::type_def)//#TODO use GetType virtual func instead
                return std::string(((game_data_string *)data.getRef())->raw_string);
            return std::string();
        }

        game_value & game_value::operator [](int i_) {
            assert(data && *reinterpret_cast<uintptr_t*>(data.getRef()) == game_data_array::type_def && (uint32_t)i_ < ((game_data_array *)data.getRef())->length);
            return ((game_data_array *)data.getRef())->data[i_];
        }

        game_value game_value::operator [](int i_) const {
            assert(data && *reinterpret_cast<uintptr_t*>(data.getRef()) == game_data_array::type_def && (uint32_t)i_ < ((game_data_array *)data.getRef())->length);
            return ((game_data_array *)data.getRef())->data[i_];
        }

        uintptr_t game_value::type() const {
            if (data)
                return *reinterpret_cast<uintptr_t*>(data.getRef()); //#TODO use GetType virtual func instead
            return 0x0;
        }

        size_t game_value::length() const {
            if (type() == game_data_array::type_def)
                return ((game_data_array *)data.getRef())->length;
            return 0;
        }

        bool game_value::is_null()
        {
            return !(data);
        }

        bool game_value::client_owned() const {//#TODO what is this used for?
            // if (data && data->ref_count_internal.is_intercept())
            //     return true;
            return false;
        }

        void* game_value::operator new(std::size_t sz_) {
            return rv_allocator<game_value>::createArray(sz_);
        }

        void game_value::operator delete(void* ptr_, std::size_t) {
            rv_allocator<game_value>::deallocate(static_cast<game_value*>(ptr_));
        }

        rv_string * allocate_string(size_t size_) {
            return client::host::functions.allocate_string(size_);
        }

        void free_string(rv_string * str_) {
            client::host::functions.free_string(str_);
        }

        template<class Type>
        void rv_allocator<Type>::deallocate(Type* _Ptr, size_t) {
            //#TODO assert when _ptr is not 32/64bit aligned
            // deallocate object at _Ptr
            auto allocatorBase = GET_ENGINE_ALLOCATOR;
            MemTableFunctions* alloc = (MemTableFunctions*) allocatorBase->genericAllocBase;
            //std::stringstream stream;
            //stream << "deallocate " << "x * " << typeid(Type).name() << "@" << std::hex << (int)_Ptr << "\n";
            //OutputDebugStringA(stream.str().c_str());
            alloc->Delete(_Ptr);
        }

        template<class Type>
        Type* rv_allocator<Type>::allocate(size_t _count) {	// allocate array of _Count elements

            auto allocatorBase = GET_ENGINE_ALLOCATOR;
            //uintptr_t allocatorBase = GET_ENGINE_ALLOCATOR;    
            MemTableFunctions* alloc = (MemTableFunctions*) allocatorBase->genericAllocBase;
            Type* newData = reinterpret_cast<Type*>(alloc->New(sizeof(Type)*_count));
            //std::stringstream stream;
            //stream << "allocate " << _count << " * " << typeid(Type).name() << "@" << std::hex << (int) newData << "\n";
            //OutputDebugStringA(stream.str().c_str());
            return newData;
        }

        void* rv_pool_allocator::allocate(size_t count) {
            auto allocatorBase = GET_ENGINE_ALLOCATOR;
            typedef void*(__thiscall *allocFunc)(rv_pool_allocator*, size_t count);
            allocFunc alloc = reinterpret_cast<allocFunc>(allocatorBase->poolFuncAlloc);
            auto allocation = alloc(this, count);
            return allocation;
        }

        void rv_pool_allocator::deallocate(void* data) {
            auto allocatorBase = GET_ENGINE_ALLOCATOR;
            typedef void(__thiscall *deallocFunc)(rv_pool_allocator*, void* data);
            deallocFunc dealloc = reinterpret_cast<deallocFunc>(allocatorBase->poolFuncDealloc);
            return dealloc(this,data);
        }
}
}


