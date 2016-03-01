#include "shared\types.hpp"
#include "client\client.hpp"
#include "shared\client_types.hpp"
#include <assert.h>

#define INTERNAL_TAG 0x0000dede

namespace intercept {
    namespace types {
        uintptr_t game_data_string::type_def;
        uintptr_t game_data_string::data_type_def;
        thread_local game_data_pool<game_data_string> game_data_string::_data_pool;

        uintptr_t game_data_number::type_def;
        uintptr_t game_data_number::data_type_def;
        thread_local game_data_pool<game_data_number> game_data_number::_data_pool;

        uintptr_t game_data_array::type_def;
        uintptr_t game_data_array::data_type_def;
        thread_local game_data_pool<game_data_array> game_data_array::_data_pool;
        thread_local game_data_array_pool<game_value> game_data_array::_array_pool;

        uintptr_t game_data_bool::type_def;
        uintptr_t game_data_bool::data_type_def;
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



        uintptr_t rv_game_value::__vptr_def;



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
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            number = 0.0f;
        }

        game_data_number::game_data_number(float val_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            number = val_;
        }

        game_data_number::game_data_number(const game_data_number & copy_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            number = copy_.number;
        }

        game_data_number::game_data_number(game_data_number && move_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = move_.ref_count_internal;
            number = move_.number;
        }

        game_data_number & game_data_number::operator=(const game_data_number & copy_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            number = copy_.number;
            return *this;
        }

        game_data_number & game_data_number::operator=(game_data_number && move_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = move_.ref_count_internal;
            number = move_.number;
            return *this;
        }

        inline void * game_data_number::operator new(std::size_t sz_)
        {
            return _data_pool.acquire();
        }

        inline void game_data_number::operator delete(void * ptr_, std::size_t sz_)
        {
            _data_pool.release((game_data_number *)ptr_);
        }

        game_data_bool::game_data_bool() {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            val = false;
        }

        game_data_bool::game_data_bool(bool val_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            val = val_;
        }

        game_data_bool::game_data_bool(const game_data_bool & copy_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            val = copy_.val;
        }

        game_data_bool::game_data_bool(game_data_bool && move_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = move_.ref_count_internal;
            val = move_.val;
        }

        game_data_bool & game_data_bool::operator=(const game_data_bool & copy_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            val = copy_.val;
            return *this;
        }

        game_data_bool & game_data_bool::operator=(game_data_bool && move_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = move_.ref_count_internal;
            val = move_.val;
            return *this;
        }

        inline void * game_data_bool::operator new(std::size_t sz_)
        {
            return _data_pool.acquire();
        }

        inline void game_data_bool::operator delete(void * ptr_, std::size_t sz_)
        {
            _data_pool.release((game_data_bool *)ptr_);
        }

        game_data_string::game_data_string() {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            raw_string = allocate_string(128);
            raw_string->length = 128;
            raw_string->ref_count_internal = 1;
        }

        game_data_string::game_data_string(const std::string &str_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            raw_string = allocate_string(str_.length() + 1);
            memcpy(&raw_string->char_string, str_.c_str(), str_.length() + 1);
            raw_string->length = str_.length() + 1;
            raw_string->ref_count_internal = 1;
        }

        game_data_string::game_data_string(const game_data_string & copy_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            raw_string = allocate_string(copy_.raw_string->length);
            memcpy(&raw_string->char_string, &copy_.raw_string->char_string, copy_.raw_string->length);
            raw_string->length = copy_.raw_string->length;
            raw_string->ref_count_internal = 1;
        }

        game_data_string::game_data_string(game_data_string && move_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = move_.ref_count_internal;
            free_string(raw_string);
            raw_string = move_.raw_string;
            move_.raw_string = nullptr;
        }

        game_data_string & game_data_string::operator=(const game_data_string & copy_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal.set_initial(1, true);
            raw_string = allocate_string(copy_.raw_string->length);
            memcpy(&raw_string->char_string, &copy_.raw_string->char_string, copy_.raw_string->length);
            raw_string->length = copy_.raw_string->length;
            raw_string->ref_count_internal = 1;
            return *this;
        }

        game_data_string & game_data_string::operator=(game_data_string && move_)
        {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = move_.ref_count_internal;
            free_string(raw_string);
            raw_string = move_.raw_string;
            move_.raw_string = nullptr;
            return *this;
        }

        void game_data_string::free() {
            if (raw_string)
                free_string(raw_string);
        }

        game_data_string::~game_data_string()
        {
            free();
        }

        void * game_data_string::operator new(std::size_t sz_)
        {
            return _data_pool.acquire();
        }

        void game_data_string::operator delete(void * ptr_, std::size_t sz_)
        {
            _data_pool.release((game_data_string *)ptr_);
        }

        game_data_array::game_data_array() {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            length = 0;
            max_size = 0;
            data = nullptr;
        }

        game_data_array::game_data_array(size_t size_) {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            data = _array_pool.acquire(size_);
            length = size_;
            max_size = size_;
        }

        game_data_array::game_data_array(const std::vector<game_value> &init_) {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            data = _array_pool.acquire(init_.size());
            length = init_.size();
            max_size = init_.size();
            size_t i = 0;
            for (auto it = init_.begin(); it != init_.end(); ++it) {
                data[i++] = *it;
            }
        }

        game_data_array::game_data_array(const game_data_array & copy_) {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            length = copy_.length;
            max_size = copy_.max_size;
            data = _array_pool.acquire(length);
            for (size_t i = 0; i < length; ++i)
                data[i] = copy_.data[i];
        }

        game_data_array::game_data_array(game_data_array && move_) {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            if (data)
                _array_pool.release(data);
            data = move_.data;
            length = move_.length;
            max_size = move_.max_size;
            move_.data = nullptr;
        }

        game_data_array & game_data_array::operator = (const game_data_array &copy_) {
            type = type_def;
            data_type = data_type_def;
            ref_count_internal = 1;
            ref_count_internal.set_initial(1, true);
            length = copy_.length;
            data = _array_pool.acquire(length);
            for (size_t i = 0; i < length; ++i)
                data[i] = copy_.data[i];
            return *this;
        }

        game_data_array & game_data_array::operator = (game_data_array &&move_) {
            if (this == &move_)
                return *this;
            if (data)
                _array_pool.release(data);
            data = move_.data;
            length = move_.length;
            max_size = move_.max_size;
            move_.data = nullptr;
            return *this;
        }
        
        void game_data_array::free() {
            if (data)
                _array_pool.release(data);
        }

        game_data_array::~game_data_array() {
            free();
        }

        void * game_data_array::operator new(std::size_t sz_)
        {
            return _data_pool.acquire();
        }

        void game_data_array::operator delete(void * ptr_, std::size_t sz_)
        {
            _data_pool.release((game_data_array *)ptr_);
        }

        game_value::game_value() {
            rv_data.data = nullptr;
        }

        void game_value::copy(const game_value & copy_) {
            rv_data.__vptr = copy_.rv_data.__vptr;
            if (copy_.rv_data.data) {
                rv_data.data = copy_.rv_data.data;
                rv_data.data->ref_count_internal++;
            }
        }

        game_value::game_value(const game_value & copy_) {
            copy(copy_);
        }

        game_value::game_value(game_value && move_) {
            rv_data.__vptr = move_.rv_data.__vptr;
            rv_data.data = move_.rv_data.data;
            move_.rv_data.data = nullptr;
        }

        game_value::game_value(const rv_game_value &internal_)
        {
            rv_data.__vptr = internal_.__vptr;
            rv_data.data = (game_data *)internal_.data;
            if(rv_data.data)
                rv_data.data->ref_count_internal++;
        }

        game_value::game_value(float val_)
        {
            rv_data.data = new game_data_number(val_);
        }

        game_value::game_value(bool val_)
        {
            rv_data.data = new game_data_bool(val_);
        }

        game_value::game_value(const std::string &val_)
        {
            rv_data.data = new game_data_string(val_);
        }

        game_value::game_value(const char *val_)
        {
            rv_data.data = new game_data_string(val_);
        }

        game_value::game_value(const std::vector<game_value> &list_)
        {
            rv_data.data = new game_data_array(list_);
        }

        game_value::game_value(const vector3 & vec_)
        {
            rv_data.data = new game_data_array({ vec_.x, vec_.y, vec_.z });
        }

        game_value::game_value(const vector2 & vec_)
        {
            rv_data.data = new game_data_array({ vec_.x, vec_.y });
        }
        game_value::game_value(const internal_object &internal_)
        {

            rv_data = internal_.rv_data;
            rv_data.__vptr = internal_.rv_data.__vptr;
            if (rv_data.data)
                rv_data.data->ref_count_internal++;
        }
        game_value::~game_value() {
            _free();
        }

        void game_value::_free()
        {
            // Ghetto superstar...
            if (rv_data.data) {
                rv_data.data->ref_count_internal--;
                if (rv_data.data->ref_count_internal < rv_data.data->ref_count_internal.get_initial()) {
                    if (rv_data.data->ref_count_internal.is_intercept()) {
                        rv_data.data->ref_count_internal.clear_initial(); // make sure we clear out the initial value, so it goes back to a pure 32 bit int.
                        if (rv_data.data && rv_data.data->type == game_data_number::type_def)
                            delete (game_data_number *)rv_data.data;

                        else if (rv_data.data && rv_data.data->type == game_data_string::type_def)
                            delete (game_data_string *)rv_data.data;

                        else if (rv_data.data && rv_data.data->type == game_data_array::type_def)
                            delete (game_data_array *)rv_data.data;

                        else if (rv_data.data && rv_data.data->type == game_data_bool::type_def)
                            delete (game_data_bool *)rv_data.data;

                        else if (rv_data.data)
                            delete rv_data.data;
                    }
                    else {
                        rv_data.data->ref_count_internal.clear_initial(); // make sure we clear out the initial value, so it goes back to a pure 32 bit int.
                        client::host::functions.free_value(this);
                        rv_data.data = nullptr;
                    }
                }
            }
        }

        game_value & game_value::operator = (const game_value &copy_) {
            copy(copy_);
            return *this;
        }
        game_value & game_value::operator = (game_value &&move_) {
            if (this == &move_)
                return *this;
            if (rv_data.data) // this needs to be properly freed from where it came.
                _free();
            rv_data.__vptr = move_.rv_data.__vptr;
            rv_data.data = move_.rv_data.data;
            move_.rv_data.data = nullptr;
            return *this;
        }

        game_value & game_value::operator=(const float val_)
        {
            if (rv_data.data)
                _free();
            rv_data.data = new game_data_number(val_);
            return *this;
        }

        game_value & game_value::operator=(bool val_)
        {
            if (rv_data.data)
                _free();
            rv_data.data = new game_data_bool(val_);
            return *this;
        }

        game_value & game_value::operator=(const std::string &val_)
        {
            if (rv_data.data)
                _free();
            rv_data.data = new game_data_string(val_);
            return *this;
        }

        game_value & game_value::operator=(const char * val_)
        {
            if (rv_data.data)
                _free();
            rv_data.data = new game_data_string(val_);
            return *this;
        }

        game_value & game_value::operator=(const std::vector<game_value> &list_)
        {
            if (rv_data.data)
                _free();
            rv_data.data = new game_data_array(list_);
            return *this;
        }

        game_value & game_value::operator=(const vector3 &vec_)
        {
            if (rv_data.data)
                _free();
            rv_data.data = new game_data_array({ vec_.x, vec_.y, vec_.z });
            return *this;
        }

        game_value & game_value::operator=(const vector2 &vec_)
        {
            if (rv_data.data)
                _free();
            rv_data.data = new game_data_array({ vec_.x, vec_.y });
            return *this;
        }

        game_value & game_value::operator=(const internal_object &internal_)
        {
            if (rv_data.data)
                _free();
            rv_data.data = internal_.rv_data.data;
            rv_data.__vptr = internal_.rv_data.__vptr;
            if(rv_data.data)
                rv_data.data->ref_count_internal++;
            return *this;
        }

        game_value & game_value::operator=(const rv_game_value &internal_)
        {
            if (rv_data.data)
                _free();
            rv_data.data = internal_.data;
            rv_data.__vptr = internal_.__vptr;
            if (rv_data.data)
                rv_data.data->ref_count_internal++;
            return *this;
        }

        game_value::operator int()
        {
            if (rv_data.data && rv_data.data->type == game_data_number::type_def)
                return static_cast<int>(((game_data_number *)rv_data.data)->number);
            return 0;
        }

        game_value::operator float()
        {
            if (rv_data.data && rv_data.data->type == game_data_number::type_def)
                return ((game_data_number *)rv_data.data)->number;
            return 0.0f;
        }

        game_value::operator bool()
        {
            if (rv_data.data && rv_data.data->type == game_data_bool::type_def)
                return ((game_data_bool *)rv_data.data)->val;
            return false;
        }

        game_value::operator rv_string &()
        {
            return *((game_data_string *)rv_data.data)->raw_string;
        }

        game_value::operator rv_game_value *()
        {
            return &rv_data;
        }

        game_value::operator vector3()
        {
            if (((game_data_array *)rv_data.data)->length == 3)
                return vector3(
                    ((game_data_array *)rv_data.data)->data[0],
                    ((game_data_array *)rv_data.data)->data[1],
                    ((game_data_array *)rv_data.data)->data[2]
                    );
            return vector3();
        }

        game_value::operator vector2()
        {
            if(((game_data_array *)rv_data.data)->length == 2)
                return vector2(
                    ((game_data_array *)rv_data.data)->data[0],
                    ((game_data_array *)rv_data.data)->data[1]
                    );
            return vector2();
        }

        game_value::operator int() const
        {
            if (rv_data.data && rv_data.data->type == game_data_number::type_def)
                return static_cast<int>(((game_data_number *)rv_data.data)->number);
            return 0;
        }

        game_value::operator float() const
        {
            if (rv_data.data && rv_data.data->type == game_data_number::type_def)
                return ((game_data_number *)rv_data.data)->number;
            return 0.0f;
        }

        game_value::operator bool() const
        {
            if (rv_data.data && rv_data.data->type == game_data_bool::type_def)
                return ((game_data_bool *)rv_data.data)->val;
            return false;
        }

        game_value::operator rv_string &() const
        {
            return *((game_data_string *)rv_data.data)->raw_string;
        }

        game_value::operator vector3() const
        {
            return vector3(
                ((game_data_array *)rv_data.data)->data[0],
                ((game_data_array *)rv_data.data)->data[1],
                ((game_data_array *)rv_data.data)->data[2]
                );
        }

        game_value::operator vector2() const
        {
            return vector2(
                ((game_data_array *)rv_data.data)->data[0],
                ((game_data_array *)rv_data.data)->data[1]
                );
        }

        game_value::operator std::string() const
        {
            if (rv_data.data && rv_data.data->type == game_data_string::type_def)
                return std::string(&((game_data_string *)rv_data.data)->raw_string->char_string);
            return std::string();
        }

        game_value::operator std::string()
        {
            if (rv_data.data && rv_data.data->type == game_data_string::type_def)
                return std::string(&((game_data_string *)rv_data.data)->raw_string->char_string);
            return std::string();
        }

        game_value & game_value::operator [](int i_) {
            assert(rv_data.data && rv_data.data->type == game_data_array::type_def && (uint32_t)i_ < ((game_data_array *)rv_data.data)->length);
            return ((game_data_array *)rv_data.data)->data[i_];
        }

        game_value game_value::operator [](int i_) const {
            assert(rv_data.data && rv_data.data->type == game_data_array::type_def && (uint32_t)i_ < ((game_data_array *)rv_data.data)->length);
            return ((game_data_array *)rv_data.data)->data[i_];
        }

        uintptr_t game_value::type() const {
            if (rv_data.data)
                return rv_data.data->type;
            return 0x0;
        }

        size_t game_value::length() const {
            if (type() == game_data_array::type_def)
                return ((game_data_array *)rv_data.data)->length;
            return 0;
        }

        bool game_value::is_null()
        {
            if (rv_data.data)
                return true;
            return false;
        }

        bool game_value::client_owned() const {
            if (rv_data.data && rv_data.data->ref_count_internal.is_intercept())
                return true;
            return false;
        }



        rv_string * allocate_string(size_t size_) {
            return client::host::functions.allocate_string(size_);
        }

        void free_string(rv_string * str_) {
            client::host::functions.free_string(str_);
        }

        const void rv_game_value::deallocate()
        {
            data = nullptr;
        }

}
}


