#pragma once
#include <stdio.h>
#include <set>
#include <array>
#include <mutex>
#include <thread>
#include <atomic>
//#include <utility>
#include "vector.hpp"
//#include "pool.hpp"
#include "shared.hpp"
#include <string_view>
#include <string.h>
#include <algorithm>
#include <memory>

//GNUC somehow can't do it if it's inside shared.hpp.
#ifdef __GNUC__
#define CDECL __attribute__ ((__cdecl__))
#endif
using namespace std::literals::string_view_literals;

[[deprecated("use sv instead")]] constexpr std::string_view operator ""_sv(char const* str, std::size_t len) noexcept {
    return { str, len };
};

namespace intercept {
    class sqf_functions;
    class registered_sqf_function_impl;
    class invoker;
    namespace types {
        class game_value;
        class game_data_array;
        class internal_object;
        class game_data;
    #ifdef __linux__
        //using nular_function = game_value*(__attribute__((__stdcall__))*) (game_value *);
        using nular_function = game_value(*) (uintptr_t state);
        using unary_function = game_value(*) (uintptr_t state, uintptr_t);
        using binary_function = game_value(*) (uintptr_t state, uintptr_t, uintptr_t);
    #else
        using nular_function = game_value*(CDECL *) (game_value *, uintptr_t);
        using unary_function = game_value*(CDECL *) (game_value *, uintptr_t, uintptr_t);
        using binary_function = game_value*(CDECL *) (game_value *, uintptr_t, uintptr_t, uintptr_t);
    #endif

        typedef std::set<std::string> value_types;
        typedef uintptr_t value_type;
        namespace __internal {
            void set_game_value_vtable(uintptr_t vtable);
            template <typename T, typename U>
            std::size_t pairhash(const T& first, const U& second) {
                size_t _hash = std::hash<T>()(first);
                _hash ^= std::hash<U>()(second) + 0x9e3779b9 + (_hash << 6) + (_hash >> 2);
                return _hash;
            }
            class I_debug_value {  //ArmaDebugEngine is very helpful... (No advertising.. I swear!)
            public:
                I_debug_value() {}
                virtual ~I_debug_value() {}
                // IDebugValue
                virtual int IAddRef() = 0;
                virtual int IRelease() = 0;
            };
        }

    #pragma region Allocator


        namespace __internal {
            void* rv_allocator_allocate_generic(size_t _size);
            void rv_allocator_deallocate_generic(void* _Ptr);
            void* rv_allocator_reallocate_generic(void* _Ptr, size_t _size);
        }

        template<class Type>
        class rv_allocator : std::allocator<Type> {
        public:
            static void deallocate(Type* _Ptr, size_t = 0) {
                return __internal::rv_allocator_deallocate_generic(_Ptr);
            }
            //This only allocates the memory! This will not be initialized to 0 and the allocated object will not have it's constructor called!
            //use the create* Methods instead
            static Type* allocate(size_t _count) {
                return reinterpret_cast<Type*>(__internal::rv_allocator_allocate_generic(sizeof(Type)*_count));
            }

            //Allocates and Initializes one Object
            template<class... _Types>
            static Type* createSingle(_Types&&... _Args) {
                auto ptr = allocate(1);
                ::new (ptr) Type(std::forward<_Types>(_Args)...);
                //Have to do a little more unfancy stuff for people that want to overload the new operator
                return ptr;
            }

            //Allocates and initializes array of Elements using the default constructor.
            static Type* createArray(size_t _count) {
                if (_count == 1) return createSingle();

                auto ptr = allocate(_count);

                for (size_t i = 0; i < _count; ++i) {
                    ::new (ptr + i) Type();
                }

                return ptr;
            }

            static Type* createUninitializedArray(size_t _count) {
                if (_count == 1) return createSingle();

                auto ptr = allocate(_count);

                return ptr;
            }

            static Type* reallocate(Type* _Ptr, size_t _count) {
                return reinterpret_cast<Type*>(__internal::rv_allocator_reallocate_generic(_Ptr, sizeof(Type)*_count));
            }
        };

        class rv_pool_allocator {
            char pad_0x0000[0x24]; //0x0000
        public:
            const char* _allocName;

            int _1;
            int _2;
            int _3;
            int _4;
            int allocated_count;

            void* allocate(size_t count);
            void deallocate(void* data);

        };
    #pragma endregion


    #pragma region Refcounting

        class refcount_base {
        public:
            constexpr refcount_base() : _refcount(0) {}
            refcount_base(const refcount_base &src) { _refcount = 0; }
            void operator = (const refcount_base &src) const {}

            constexpr int add_ref() const {
                return ++_refcount;
            }
            int dec_ref() const {
                return --_refcount;
            }
            int ref_count() const {
                return _refcount;
            }
            mutable int _refcount;
        };

        //refcount has to be the first element in a class. Use refcount_vtable instead if refcount is preceded by a vtable
        class refcount : public refcount_base {
        public:
            virtual ~refcount() {}
            int release() const {
                int rcount = dec_ref();
                if (rcount == 0) {
                    //this->~refcount();
                    lastRefDeleted();
                    //rv_allocator<refcount>::deallocate(const_cast<refcount *>(this), 0);
                }
                return rcount;
            }
            void destruct() const {
                delete const_cast<refcount *>(this);
            }
            virtual void lastRefDeleted() const { destruct(); }
            virtual int __dummy_refcount_func() const { return 0; }
        };
        class game_value_static;
        template<class Type>
        class ref {
            friend class game_value_static; //Overrides _ref to nullptr in destructor when Arma is exiting
            static_assert(std::is_base_of<refcount_base, Type>::value, "Type must inherit refcount_base");
            Type* _ref;
        public:
            ref() : _ref(nullptr) {}
            ~ref() { free(); }

            //Construct from Pointer
            ref(Type* other) {
                if (other) other->add_ref();
                _ref = other;
            }
            //Copy from pointer
            const ref &operator = (Type *source) {
                Type *old = _ref;
                if (source) source->add_ref();
                _ref = source;
                if (old) old->release();//decrement reference and delete object if refcount == 0
                return *this;
            }

            //Construct from reference
            ref(const ref &sRef) {
                Type *source = sRef._ref;
                if (source) source->add_ref();
                _ref = source;
            }
            //Copy from reference.
            const ref &operator = (const ref &other) {
                Type *source = other._ref;
                Type *old = _ref;
                if (source) source->add_ref();
                _ref = source;
                if (old) old->release();//decrement reference and delete object if refcount == 0
                return *this;
            }

            bool isNull() const { return _ref == nullptr; }
            void free() {
                if (!_ref) return;
                _ref->release();
                _ref = nullptr;
            }
            //This returns a pointer to the underlying object. Use with caution!
            Type *getRef() const { return _ref; }
            Type *operator -> () const { return _ref; }
            operator Type *() const { return _ref; }
            bool operator != (const ref<Type>& other_) { return _ref != other_._ref; }
            size_t ref_count() const { return _ref ? _ref->ref_count() : 0; }
        };

    #pragma endregion

        /*
        This is a placeholder so i can use refcount but still have an accessible vtable pointer
        */
        class __vtable {
        public:
            uintptr_t _vtable{ 0 };
        };

        class _refcount_vtable_dummy : public __vtable, public refcount_base {};

    #pragma region Containers
        template<class Type, class Allocator = rv_allocator<char>> //Has to be allocator of type char
        class compact_array : public refcount_base {
            static_assert(std::is_literal_type<Type>::value, "Type must be a literal type");
        public:

            size_t size() const { return _size; }
            Type *data() { return &_data; }
            const Type *data() const { return &_data; }
            const Type * cbegin() const { return &_data; }
            const Type * cend() const { return (&_data) + _size; }

            //We delete ourselves! After release no one should have a pointer to us anymore!
            int release() const {
                int ret = dec_ref();
                if (!ret) del();
                return ret;
            }

            static compact_array* create(size_t number_of_elements_) {
                size_t size = sizeof(compact_array) + sizeof(Type)*(number_of_elements_ - 1);//-1 because we already have one element in compact_array
                compact_array* buffer = reinterpret_cast<compact_array*>(Allocator::allocate(size));
                new (buffer) compact_array(number_of_elements_);
                return buffer;
            }
            static compact_array* create(const compact_array &other) {
                size_t size = other.size();
                compact_array* buffer = reinterpret_cast<compact_array*>(Allocator::allocate(size));
                new (buffer) compact_array(size);
                std::copy(other.data(), other.data() + other.size(), buffer->data());
                return buffer;
            }
            void del() const {
                this->~compact_array();
                const void* _thisptr = this;
                void* _thisptr2 = const_cast<void*>(_thisptr);
                Allocator::deallocate(reinterpret_cast<char*>(_thisptr2), _size - 1 + sizeof(compact_array));
            }

            size_t _size;
            Type _data;
        private:
            explicit compact_array(size_t size_) {
                _size = size_;
            }
        };


        //template<std::size_t N>
        //class r_string_const : public refcount_base { // constexpr string
        //private:
        //    const size_t _size;
        //    const char _data[];
        //public:
        //    constexpr r_string_const(const char a[N]) : _size(N - 1), _data({a[0] ... a[N]}) { add_ref(); }
        //};

        class r_string {
        protected:
        public:
            r_string() {}
            r_string(std::string_view str) {
                if (str.length()) _ref = create(str.data(), str.length());
            }
            //template <size_t N>
            //constexpr r_string(const r_string_const<N>& c) {
            //    _ref = reinterpret_cast<compact_array<char>*>(&c);
            //}
            explicit r_string(compact_array<char>* dat) : _ref(dat) {}
            r_string(r_string&& _move) noexcept {
                _ref = _move._ref;
                _move._ref = nullptr;
            }
            r_string(const r_string& _copy) {
                _ref = _copy._ref;
            }

            r_string& operator = (r_string&& _move) noexcept {
                if (this == &_move)
                    return *this;
                _ref = _move._ref;
                _move._ref = nullptr;
                return *this;
            }

            r_string& operator = (const r_string& _copy) {
                _ref = _copy._ref;
                return *this;
            }
            r_string& operator = (std::string_view _copy) {
                _ref = create(_copy.data(), _copy.length());
                return *this;
            }
            const char* data() const {
                if (_ref) return _ref->data();
                static char empty[]{ 0 };
                return empty;
            }
            const char* c_str() const { return data(); }
            //This will copy the underlying container if we cannot safely modify this r_string
            void make_mutable() {
                if (_ref && _ref->ref_count() > 1) {//If there is only one reference we can safely modify the string
                    _ref = create(_ref->data());
                }
            }

            explicit operator const char *() const { return data(); }
            operator std::string_view() const { return std::string_view(data()); }
            //explicit operator std::string() const { return std::string(data()); } //non explicit will break string_view operator because std::string operator because it becomes ambiguous
            //This calls strlen so O(N)
            size_t length() const {
                if (!_ref) return 0;
                return strlen(_ref->data());
            }

            size_t capacity() const {
                if (!_ref) return 0;
                return _ref->size();
            }

            //== is case insensitive just like scripting
            bool operator == (const char *other) const {
                if (!data())  return (!other || !*other); //empty?
            #ifdef __GNUC__
                return std::equal(_ref->cbegin(), _ref->cend(),
                    other, [](unsigned char l, unsigned char r) {return l == r || tolower(l) == tolower(r); });
            #else
                return _strcmpi(data(), other) == 0;
            #endif
            }

            //!= is case insensitive just like scripting
            bool operator != (const char *other) const {
                return !(*this == other);
            }

            bool operator < (const r_string& other) const {
                if (!data()) return false; //empty?
                return strcmp(data(), other.data()) < 0;
            }

            bool operator == (const r_string& other) const {
                if (!data()) return (!other.data() || !*other.data()); //empty?
                if (data() == other.data()) return true;
            #ifdef __GNUC__
                return std::equal(_ref->cbegin(), _ref->cend(),
                    other.data(), [](unsigned char l, unsigned char r) {return l == r || tolower(l) == tolower(r); });
            #else
                return _strcmpi(data(), other.data()) == 0;
            #endif
            }

            bool operator == (const std::string& other) const {
                if (!data()) return other.empty(); //empty?
                if (other.length() > _ref->size()) return false; //There is more data than we can even have
            #ifdef __GNUC__
                return std::equal(_ref->cbegin(), _ref->cend(),
                    other.data(), [](unsigned char l, unsigned char r) {return l == r || tolower(l) == tolower(r); });
            #else
                return _strcmpi(data(), other.data()) == 0;
            #endif
            }

            bool operator == (const std::string_view& other) const {
                if (!data()) return other.empty(); //empty?
                if (other.length() > _ref->size()) return false; //There is more data than we can even have
#ifdef __GNUC__
                return std::equal(_ref->cbegin(), _ref->cend(),
                    other.data(), [](unsigned char l, unsigned char r) {return l == r || tolower(l) == tolower(r); });
#else
                return _strcmpi(data(), other.data()) == 0;
#endif
            }

            bool operator != (const r_string& other) const {
                return !(*this == other);
            }

            friend std::ostream& operator << (std::ostream& _os, const r_string& _s) {
                _os << _s.data();
                return _os;
            }

            friend std::istream& operator >> (std::istream& _in, r_string& _t){
                char inp;
                std::string tmp;
                while (_in.get(inp)) {
                    if (inp == 0) break;
                    tmp.push_back(inp);
                }
                _t._ref = create(tmp.data(), tmp.length());
                return _in;
            }

            bool compare_case_sensitive(const char *other) const {
            #ifdef __GNUC__
                return !std::equal(_ref->cbegin(), _ref->cend(),
                    other, [](unsigned char l, unsigned char r) {return l == r; });
            #else
                return _stricmp(data(), other) == 0;
            #endif
            }

            size_t find(char ch, size_t start = 0) const {
                if (length() == 0) return -1;
                const char *pos = strchr(_ref->data() + start, ch);
                if (pos == nullptr) return -1;
                return pos - _ref->data();
            }

            size_t find(const char *sub, int nStart = 0) const {
                if (_ref == nullptr || length() == 0) return -1;
                const char *pos = strstr(_ref->data() + nStart, sub);
                if (pos == nullptr) return -1;
                return pos - _ref->data();
            }
            void clear() {
                _ref = nullptr;
            }
            size_t hash() const {
                return std::hash<std::string_view>()(std::string_view(data(), _ref ? _ref->size() : 0u));
            }

        private:
            ref<compact_array<char>> _ref;

            static compact_array<char> *create(const char *str, size_t len) {
                if (len == 0 || *str == 0) return nullptr;
                compact_array<char> *string = compact_array<char>::create(len + 1);
            #if __GNUC__
                std::copy_n(str, len, string->data());
            #else
                strncpy_s(string->data(), string->size(), str, len);//#TODO better use memcpy? does strncpy_s check for null chars? we don't want that
            #endif
                string->data()[len] = 0;
                return string;
            }

            static compact_array<char> *create(size_t len) {
                if (len == 0) return nullptr;
                compact_array<char> *string = compact_array<char>::create(len + 1);
                string->data()[0] = 0;
                return string;
            }

            static compact_array<char> *create(const char *str) {
                if (*str == 0) return nullptr;
                return create(str, strlen(str));
            }
        };

        //constexpr r_string tests
        //#define r_string_literal(str) \
        //    ([]() -> const r_string_const<sizeof(str)- 1>& { \
        //        static const r_string_const<sizeof(str)- 1> literal{ str }; \
        //        return literal; \
        //    }())

        //constexpr const r_string& operator ""_rs(const char* __str, size_t len) {
        //    return r_string_literal(__str);
        //};

        //Contributed by ArmaDebugEngine
        class rv_arraytype {};

        template<class Type>
        class rv_array : public rv_arraytype {
        protected:
            Type *_data;
            int _n;
        public:
            class const_iterator;

            class iterator : public std::iterator<std::random_access_iterator_tag, Type> {
                friend class const_iterator;
                Type* p_;
            public:
                iterator() : p_(nullptr) {}
                explicit iterator(Type* p) : p_(p) {}
                iterator(const iterator& other) : p_(other.p_) {}
                const iterator& operator=(const iterator& other) { p_ = other.p_; return other; }

                iterator& operator++() { ++p_; return *this; } // prefix++
                iterator  operator++(int) { iterator tmp(*this); ++(*this); return tmp; } // postfix++
                iterator& operator--() { --p_; return *this; } // prefix--
                iterator  operator--(int) { iterator tmp(*this); --(*this); return tmp; } // postfix--

                void     operator+=(const std::size_t& n) { p_ += n; }
                void     operator+=(const iterator& other) { p_ += other.p_; }
                iterator operator+ (const std::size_t& n) const { iterator tmp(*this); tmp += n; return tmp; }
                iterator operator+ (const iterator& other) const { iterator tmp(*this); tmp += other; return tmp; }

                void        operator-=(const std::size_t& n) { p_ -= n; }
                void        operator-=(const iterator& other) { p_ -= other.p_; }
                iterator    operator- (const std::size_t& n) const { iterator tmp(*this); tmp -= n; return tmp; }
                std::size_t operator- (const iterator& other) const { return p_ - other.p_; }

                bool operator< (const iterator& other) const { return (p_ - other.p_) < 0; }
                bool operator<=(const iterator& other) const { return (p_ - other.p_) <= 0; }
                bool operator> (const iterator& other) const { return (p_ - other.p_) > 0; }
                bool operator>=(const iterator& other) const { return (p_ - other.p_) >= 0; }
                bool operator==(const iterator& other) const { return  p_ == other.p_; }
                bool operator!=(const iterator& other) const { return  p_ != other.p_; }

                Type& operator*() const { return *p_; }
                Type* operator->() { return  p_; }
                explicit operator Type*() { return p_; }
            };
            class const_iterator : public std::iterator<std::random_access_iterator_tag, Type> {
                const Type* p_;
            public:
                const_iterator() : p_(nullptr) {}
                explicit const_iterator(const Type* p) : p_(p) {}
                const_iterator(const typename rv_array<Type>::iterator& other) : p_(other.p_) {}
                const_iterator(const const_iterator& other) : p_(other.p_) {}
                const const_iterator& operator=(const const_iterator& other) { p_ = other.p_; return other; }
                const const_iterator& operator=(const typename rv_array<Type>::iterator& other) { p_ = other.p_; return other; }

                const_iterator& operator++() { ++p_; return *this; } // prefix++
                const_iterator  operator++(int) { const_iterator tmp(*this); ++(*this); return tmp; } // postfix++
                const_iterator& operator--() { --p_; return *this; } // prefix--
                const_iterator  operator--(int) { const_iterator tmp(*this); --(*this); return tmp; } // postfix--

                void           operator+=(const std::size_t& n) { p_ += n; }
                void           operator+=(const const_iterator& other) { p_ += other.p_; }
                const_iterator operator+ (const std::size_t& n)        const { const_iterator tmp(*this); tmp += n; return tmp; }
                const_iterator operator+ (const const_iterator& other) const { const_iterator tmp(*this); tmp += other; return tmp; }

                void           operator-=(const std::size_t& n) { p_ -= n; }
                void           operator-=(const const_iterator& other) { p_ -= other.p_; }
                const_iterator operator- (const std::size_t& n)        const { const_iterator tmp(*this); tmp -= n; return tmp; }
                std::size_t    operator- (const const_iterator& other) const { return p_ - other.p_; }

                bool operator< (const const_iterator& other) const { return (p_ - other.p_) < 0; }
                bool operator<=(const const_iterator& other) const { return (p_ - other.p_) <= 0; }
                bool operator> (const const_iterator& other) const { return (p_ - other.p_) > 0; }
                bool operator>=(const const_iterator& other) const { return (p_ - other.p_) >= 0; }
                bool operator==(const const_iterator& other) const { return  p_ == other.p_; }
                bool operator!=(const const_iterator& other) const { return  p_ != other.p_; }

                const Type& operator*()  const { return *p_; }
                const Type* operator->() const { return  p_; }
                explicit operator const Type*() const { return p_; }
            };


            rv_array() :_data(nullptr), _n(0) {};
            rv_array(rv_array<Type>&& move_) noexcept :_data(move_._data), _n(move_._n) { move_._data = nullptr; move_._n = 0; };
            Type &get(size_t i) {
                return _data[i];
            }
            const Type &get(size_t i) const {
                return _data[i];
            }
            Type &operator [] (size_t i) { return get(i); }
            const Type &operator [] (size_t i) const { return get(i); }
            Type *data() { return _data; }
            size_t count() const { return static_cast<size_t>(_n); }

            iterator begin() { if (!_data) return iterator(); return iterator(&get(0)); }
            iterator end() { if (!_data) return iterator(); return iterator(&get(_n)); }

            const_iterator cbegin() const { return const_iterator(&get(0)); }
            const_iterator cend() const { return const_iterator(&get(_n)); }

            const_iterator begin() const { return const_iterator(&get(0)); }
            const_iterator end() const { return const_iterator(&get(_n)); }

            const Type &front() const { return get(0); }
            const Type &back() const { return get(_n - 1); }

            Type &front() { return get(0); }
            Type &back() { return get(_n - 1); }

            bool is_empty() const { return _n == 0; }

            template <class Func>
            void for_each(const Func &f) const {
                for (size_t i = 0; i < count(); i++) {
                    f(get(i));
                }
            }

            template <class Func>
            void for_each_backwards(const Func &f) const { //This returns if Func returns true
                for (size_t i = count() - 1; i >= 0; i--) {
                    if (f(get(i))) return;
                }
            }

            template <class Func>
            void for_each(const Func &f) {
                for (size_t i = 0; i < count(); i++) {
                    f(get(i));
                }
            }
            size_t hash() const {
                size_t _hash{ 0 };
                for (const auto& it : *this) {
                    _hash ^= std::hash<Type>()(it) + 0x9e3779b9 + (_hash << 6) + (_hash >> 2);
                }
                return _hash;
            }
            template<typename FindType>
            iterator find(const FindType& find_) {
                return std::find(begin(), end(), find_);
            }
        };

        template<class Type, size_t growthFactor = 32>
        class auto_array : public rv_array<Type> {
            typedef rv_array<Type> base;
        protected:
            int _maxItems;
            Type *try_realloc(Type *old, size_t n) {
                Type *ret = rv_allocator<Type>::reallocate(old, n);
                return ret;
            }

            void reallocate(size_t size) {

                if (_maxItems == size) return;

                if (base::_n > static_cast<int>(size)) {
                    resize(size);
                    return;//resize calls reallocate and reallocates... Ugly.. I know
                }
                Type *newData = nullptr;
                if (base::_data && size > 0 && ((newData = try_realloc(base::_data, size)))) {
                    //if (size > _maxItems)//Don't null out new stuff if there is no new stuff
                    //    std::fill(reinterpret_cast<uint32_t*>(&newData[_maxItems]), reinterpret_cast<uint32_t*>(&newData[size]), 0);
                    _maxItems = static_cast<int>(size);
                    base::_data = newData;
                    return;
                }
                newData = rv_allocator<Type>::createUninitializedArray(size);
                //memset(newData, 0, size * sizeof(Type));
                if (base::_data) {
                #ifdef __GNUC__
                    memmove(newData, base::_data, base::_n * sizeof(Type));
                #else
                    //std::uninitialized_move(begin(), end(), newData); //This might be cleaner. But still causes a move construct call where memmove just moves bytes.
                    memmove_s(newData, size * sizeof(Type), base::_data, base::_n * sizeof(Type));
                #endif
                    rv_allocator<Type>::deallocate(base::_data);
                }
                base::_data = newData;
                _maxItems = static_cast<int>(size);

            }

            void grow(size_t n) {
            #undef max
                reallocate(_maxItems + std::max(n, growthFactor));
            }
        public:
            using base::end;
            using base::begin;
            using base::cend;
            using base::cbegin;
            using iterator = typename base::iterator;
            using const_iterator = typename base::const_iterator;
            auto_array() : rv_array<Type>(), _maxItems(0) {};
            auto_array(const std::initializer_list<Type> &init_) : rv_array<Type>(), _maxItems(0) {
                insert(end(), init_.begin(), init_.end());
            }
            template<class _InIt>
            auto_array(_InIt _first, _InIt _last) : rv_array<Type>(), _maxItems(0) {
                insert(end(), _first, _last);
            }
            auto_array(const auto_array<Type> &copy_) : rv_array<Type>(), _maxItems(0) {
                insert(end(), copy_.begin(), copy_.end());
            }
            auto_array(auto_array<Type> &&move_) noexcept : rv_array<Type>(std::move(move_)), _maxItems(move_._maxItems) {
                move_._maxItems = 0;
            }
            ~auto_array() {
                if (base::_data == nullptr) return;
                resize(0);
            }
            void shrink_to_fit() {
                resize(base::_n);
            }
            auto_array& operator = (auto_array &&move_) noexcept {
                base::_n = move_._n;
                _maxItems = move_._maxItems;
                base::_data = move_._data;
                move_._data = nullptr;
                move_._n = 0;
                move_._maxItems = 0;
                return *this;
            }

            auto_array& operator = (const auto_array &copy_) {
                if (copy_._n) {
                    insert(base::end(), copy_.begin(), copy_.end());
                }
                std::vector<int> x = { 1,2,3 };
                return *this;
            }

            void resize(size_t n) {
                if (static_cast<int>(n) < base::_n) {
                    for (int i = static_cast<int>(n); i < base::_n; i++) {
                        (*this)[i].~Type();
                    }
                    base::_n = static_cast<int>(n);
                }
                if (n == 0 && base::_data) {
                    rv_allocator<Type>::deallocate(rv_array<Type>::_data);
                    rv_array<Type>::_data = nullptr;
                    return;
                }
                reallocate(n);
            }
            void reserve(size_t res) {
                if (_maxItems < static_cast<int>(res)) {
                    grow(res - _maxItems);
                }
            }
            template<class... _Valty>
            iterator emplace(iterator _where, _Valty&&... _Val) {
                if (_where < base::begin() || _where > base::end()) throw std::runtime_error("Invalid Iterator"); //WTF?!
                const size_t insertOffset = _where - base::begin();
                auto previousEnd = base::_n;
                if (_maxItems < base::_n + 1) {
                    grow(1);
                }
                auto& item = (*this)[base::_n];
                ::new (&item) Type(std::forward<_Valty>(_Val)...);
                ++base::_n;

                std::rotate(base::begin() + insertOffset, base::begin() + previousEnd, base::end());

                return base::begin() + insertOffset;
            }
            template<class... _Valty>
            iterator emplace_back(_Valty&&... _Val) {
                if (_maxItems < base::_n + 1) {
                    grow(1);
                }
                auto& item = (*this)[base::_n];
                ::new (&item) Type(std::forward<_Valty>(_Val)...);
                ++base::_n;
                return iterator(&item);
            }
            iterator push_back(const Type& _Val) {
                return emplace_back(_Val);
            }
            iterator push_back(Type&& _Val) {
                return emplace_back(std::move(_Val));
            }

            //void erase(int index) {
            //    if (index > base::_n) return;
            //    auto item = (*this)[index];
            //    item.~Type();
            //    memmove_s(&(*this)[index], (base::_n - index) * sizeof(Type), &(*this)[index + 1], (base::_n - index - 1) * sizeof(Type));
            //}
            void erase(const_iterator element) {
                if (element < base::begin() || element > base::end()) throw std::runtime_error("Invalid Iterator");
                size_t index = std::distance(base::cbegin(), element);
                if (static_cast<int>(index) > base::_n) return;
                auto item = (*this)[index];
                item.~Type();
            #ifdef __GNUC__
                memmove(&(*this)[index], &(*this)[index + 1], (base::_n - index - 1) * sizeof(Type));
            #else
                memmove_s(&(*this)[index], (base::_n - index) * sizeof(Type), &(*this)[index + 1], (base::_n - index - 1) * sizeof(Type));
            #endif
                --base::_n;
            }
            //This is sooo not threadsafe!
            template<class _InIt>
            iterator insert(iterator _where, _InIt _first, _InIt _last) {
                if (_first == _last) return _where; //Boogie!
                if (_where < base::begin() || _where > base::end()) throw std::runtime_error("Invalid Iterator"); //WTF?!
                size_t insertOffset = std::distance(base::begin(), _where);
                size_t previousEnd = static_cast<size_t>(base::_n);
                size_t oldSize = base::count();
                size_t insertedSize = std::distance(_first, _last);
                reserve(oldSize + insertedSize);

                auto index = base::_n;
                for (; _first != _last; ++_first) {
                    //emplace_back(*_first);
                    //custom inlined version of emplace_back. No capacity checks and only incrementing _n once.
                    auto& item = (*this)[index];
                    ::new (&item) Type(std::forward<decltype(*_first)>(*_first));
                    ++index;
                }
                base::_n = index;

                std::rotate(base::begin() + insertOffset, base::begin() + previousEnd, base::end());
                return base::begin() + insertOffset;
            }
            void clear() {
                if (base::_data)
                    rv_allocator<Type>::deallocate(rv_array<Type>::_data);
                base::_n = 0;
                _maxItems = 0;
            }

            bool operator==(rv_array<Type> other) {
                if (other._n != base::_n || ((base::_data == nullptr || other._data == nullptr) && base::_data != other._data))
                    return false;
                auto index = 0;
                for (auto& it : other) {
                    if ((*this[index]) != it)
                        return false;
                    ++index;
                }
                return true;
            }
        };


        static inline unsigned int rv_map_hash_string_case_sensitive(const char *key, int hashValue = 0) {
            while (*key) {
                hashValue = hashValue * 33 + static_cast<unsigned char>(*key++);
            }
            return hashValue;
        }
        static inline unsigned int rv_map_hash_string_case_insensitive(const char *key, int hashValue = 0) {
            while (*key) {
                hashValue = hashValue * 33 + static_cast<unsigned char>(tolower(*key++));
            }
            return hashValue;
        }

        struct map_string_to_class_trait {
            static unsigned int hash_key(const char * key) {
                return rv_map_hash_string_case_sensitive(key);
            }
            static bool compare_keys(const char * k1, const char * k2) {
                return strcmp(k1, k2) == 0;
            }
        };

        struct map_string_to_class_trait_caseinsensitive : public map_string_to_class_trait {
            static unsigned int hash_key(const char * key) {
                return rv_map_hash_string_case_insensitive(key);
            }

            static bool compare_keys(const char * k1, const char * k2) {
            #ifdef __GNUC__
                return std::equal(k1, k1 + strlen(k1),
                    k2, [](unsigned char l, unsigned char r) {return l == r || tolower(l) == tolower(r); });
            #else
                return _strcmpi(k1, k2) == 0;
            #endif
            }
        };

        template <class Type, class Container, class Traits = map_string_to_class_trait>
        class map_string_to_class {
        protected:
            Container* _table;
            int _tableCount{ 0 };
            int _count{ 0 };
            static Type _null_entry;
        public:

            class iterator {
                size_t _table;
                size_t _item;
                const map_string_to_class<Type, Container, Traits> *_map;
                size_t number_of_tables() {
                    return _map->_table ? static_cast<size_t>(_map->_tableCount) : 0u;
                }
                void get_next() {
                    while (_table < number_of_tables() && _item >= _map->_table[_table].count()) {
                        _table++;
                        _item = 0;
                    }
                }
            public:
                iterator(const map_string_to_class<Type, Container, Traits> &base) {
                    _table = 0; _item = 0; _map = &base;
                    get_next();
                }
                iterator(const map_string_to_class<Type, Container, Traits> &base, bool) { //Creates end Iterator
                    _item = 0; _map = &base;
                    _table = number_of_tables();
                }
                iterator& operator++ () {
                    if (_table >= number_of_tables()) return *this;
                    ++_item;
                    get_next();
                    return *this;
                }
                iterator operator++(int) {
                    iterator _tmp = *this;
                    ++*this;
                    return (_tmp);
                }
                bool operator==(const iterator& _other) {
                    return _table == _other._table && _item == _other._item;
                }
                bool operator!=(const iterator& _other) {
                    return _table != _other._table || _item != _other._item;
                }
                const Type &operator * () const {
                    return _map->_table[_table][_item];
                }
                const Type *operator-> () const {
                    return &_map->_table[_table][_item];
                }
                Type &operator * () {
                    return _map->_table[_table][_item];
                }
                Type *operator-> () {
                    return &_map->_table[_table][_item];
                }
            };
            iterator begin() {
                return iterator(*this);
            }
            iterator end() {
                return iterator(*this, true);
            }
            const iterator begin() const {
                return iterator(*this);
            }
            const iterator end() const {
                return iterator(*this, true);
            }

            map_string_to_class() {}

            template <class Func>
            void for_each(Func func) const {
                if (!_table || !_count) return;
                for (int i = 0; i < _tableCount; i++) {
                    const Container &container = _table[i];
                    for (int j = 0; j < container.count(); j++) {
                        func(container[j]);
                    }
                }
            }

            template <class Func>
            void for_each_backwards(Func func) const {
                if (!_table || !_count) return;
                for (int i = _tableCount - 1; i >= 0; i--) {
                    const Container &container = _table[i];
                    for (int j = container.count() - 1; j >= 0; j--) {
                        func(container[j]);
                    }
                }
            }

            const Type &get(const char* key) const {
                if (!_table || !_count) return _null_entry;
                int hashedKey = hash_key(key);
                for (int i = 0; i < _table[hashedKey].count(); i++) {
                    const Type &item = _table[hashedKey][i];
                    if (Traits::compare_keys(item.get_map_key(), key))
                        return item;
                }
                return _null_entry;
            }

            Container* get_table_for_key(const char* key) {
                if (!_table || !_count) return nullptr;
                int hashedKey = hash_key(key);
                return &_table[hashedKey];
            }

            Type &get(const char* key) {
                if (!_table || !_count) return _null_entry;
                int hashedKey = hash_key(key);
                for (size_t i = 0; i < _table[hashedKey].count(); i++) {
                    Type &item = _table[hashedKey][i];
                    if (Traits::compare_keys(item.get_map_key(), key))
                        return item;
                }
                return _null_entry;
            }

            static bool is_null(const Type &value) { return &value == &_null_entry; }

            bool has_key(const char* key) const {
                return !is_null(get(key));
            }

        public:
            int count() const { return _count; }
        protected:
            int hash_key(const char* key) const {
                return Traits::hash_key(key) % _tableCount;
            }
        };

        template<class Type, class Container, class Traits>
        Type map_string_to_class<Type, Container, Traits>::_null_entry;


    #pragma endregion

    #pragma region Serialization
        enum class serialization_return {
            /*
            int __cdecl sub_108BC00(int a1) {
            switch ( a1 ) {
            case 0:
            result = (int)"No error";
            break;
            case 1:
            case 7:
            result = (int)"No such file";
            break;
            case 2:
            result = (int)"Bad file (CRC, ...)";
            break;
            case 3:
            result = (int)"Bad file structure";
            break;
            case 4:
            result = (int)"Unsupported format";
            break;
            case 5:
            result = (int)"Version is too new";
            break;
            case 6:
            result = (int)"Version is too old";
            break;
            case 8:
            result = (int)"Access denied";
            break;
            case 9:
            result = (int)"Disk error";
            break;
            case 10:
            result = (int)"No entry";
            break;
            default:
            sub_10E9550("LSError");
            case 12:
            result = (int)"Unknown error";
            break;
            }
            return result;
            }
            */
            no_error,
            no_such_file,
            bad_file,
            bad_file_structure,
            unsupported_format,
            version_too_new,
            version_too_old,
            no_such_file2,
            access_denied,
            disk_error,
            no_entry,
            unknown_error = 12
        };

        class param_archive_array_entry {
        public:
            virtual ~param_archive_array_entry() {}

            virtual operator float() const { return 0; }
            virtual operator int() const { return 0; }
            virtual operator const r_string() const { return r_string(); } //There are two r_string thingies apparently.
            virtual operator r_string() const { return r_string(); }
            virtual operator bool() const { return false; }
        };

        class param_archive_entry {
        public:
            virtual ~param_archive_entry() {}

            //Generic stuff for all types
            virtual int entry_count() const { return 0; } //Number of entries. count for array and number of class entries otherwise
            virtual param_archive_entry *get_entry_by_index(int index_) const { return nullptr; } //Don't know what that's used for.
            virtual r_string current_entry_name() { return r_string(); } //Dunno exactly what this is. on GameData serialize it returns "data"
            virtual param_archive_entry *get_entry_by_name(const r_string &name) const { return nullptr; }

            //Normal Entry. Contains a single value of a single type
            virtual operator float() const { return 0; }
            virtual operator int() const { return 0; }
            virtual operator int64_t() const { return 0; }
        private:
            //https://stackoverflow.com/questions/19356232/why-is-explicit-not-compatible-with-virtual
            //https://connect.microsoft.com/VisualStudio/feedback/details/805301/explicit-cannot-be-used-with-virtual
            virtual
            #ifndef _MSC_VER
            explicit
            #endif
            operator const r_string() const { return r_string(); }
        public:
            virtual operator r_string() const { return r_string(); }
            virtual operator bool() const { return false; }
            virtual r_string _placeholder1(uint32_t) const { return r_string(); }

            //Array entry
            virtual void reserve(int count_) {}//Yes.. This is indeed a signed integer for something that should be unsigned...
            virtual void add_array_entry(float value_) {}
            virtual void add_array_entry(int value_) {}
            virtual void add_array_entry(int64_t value_) {}
            virtual void add_array_entry(const r_string & value_) {}
            virtual int count() const { return 0; }
            virtual param_archive_array_entry *operator [] (int index_) const { return new param_archive_array_entry(); }

            //Class entry (contains named values)
            virtual param_archive_entry *add_entry_array(const r_string &name_) { return new param_archive_entry; }
            virtual param_archive_entry *add_entry_class(const r_string &name_, bool unknown_ = false) { return new param_archive_entry; }
            virtual void add_entry(const r_string &name_, const r_string &value_) {}
            virtual void add_entry(const r_string &name_, float value_) {}
            virtual void add_entry(const r_string &name_, int value_) {}
            virtual void add_entry(const r_string &name_, int64_t value_) {}

            virtual void compress() {}
            virtual void _placeholder(const r_string &name_) {}
        };
        class serialize_class;
        class param_archive {
        public:
            virtual ~param_archive() { if (_p1) delete _p1; }
            //#TODO add SRef class
            param_archive_entry* _p1{ new param_archive_entry() }; //pointer to classEntry. vtable something
            int _version{ 1 }; //version
            char _p3{ 0 }; //be careful with alignment seems to always be 0 for exporting.
            auto_array<uintptr_t> _parameters; //parameters? on serializing gameData only element is pointer to gameState
            bool _isExporting{ true }; //writing data vs loading data
            serialization_return serialize(r_string name, serialize_class& value, int min_version);
            serialization_return serialize(r_string name, r_string& value, int min_version);
            serialization_return serialize(r_string name, bool& value, int min_version);
            serialization_return serialize(r_string name, bool& value, int min_version, bool default_value);
            template <class Type>
            serialization_return serialize(r_string name, ref<Type> &value, int min_version) {
                if (_version < min_version) return serialization_return::version_too_new;
                if (_isExporting || _p3 == 2) {
                    if (!value) return serialization_return::no_error;

                    param_archive sub_archive;
                    sub_archive._version = _version;
                    sub_archive._p3 = _p3;
                    sub_archive._parameters = _parameters;
                    sub_archive._isExporting = _isExporting;
                    delete sub_archive._p1;
                    if (_isExporting) {
                        sub_archive._p1 = _p1->add_entry_class(name, false);
                    } else {
                        sub_archive._p1 = _p1->get_entry_by_name(name);
                    }

                    if (!sub_archive._p1) {
                        return serialization_return::no_entry;
                    }

                    auto ret = value->serialize(sub_archive);
                    if (_isExporting) {
                        sub_archive._p1->compress();
                        delete sub_archive._p1;
                        sub_archive._p1 = nullptr;
                    }
                } else {

                    param_archive sub_archive;
                    sub_archive._version = _version;
                    sub_archive._p3 = _p3;
                    sub_archive._parameters = _parameters;
                    sub_archive._isExporting = _isExporting;
                    delete sub_archive._p1;
                    if (_isExporting) {
                        sub_archive._p1 = _p1->add_entry_class(name, false);
                    } else {
                        sub_archive._p1 = _p1->get_entry_by_name(name);
                    }

                    if (!sub_archive._p1) {
                        return serialization_return::no_entry;
                    }
                    auto val = Type::createFromSerialized(sub_archive);
                    if (val) val->serialize(sub_archive);
                    if (_isExporting) {
                        sub_archive._p1->compress();
                        delete sub_archive._p1;
                        sub_archive._p1 = nullptr;
                    }
                }
                return serialization_return::no_error;
            }

        };

        class serialize_class {//That's from gameValue RTTI. I'd name it serializable_class but I think keeping it close to engine name is better.
        public:
            virtual ~serialize_class() = default;
            virtual bool _dummy(void*) { return false; }//Probably canSerialize?
            virtual serialization_return serialize(param_archive &) { return serialization_return::unknown_error; }
            virtual void _dummy2(void*) {}
        };

    #pragma endregion

        struct script_type_info {  //Donated from ArmaDebugEngine
            using createFunc = game_data* (*)(param_archive* ar);
        #ifdef __linux__
            script_type_info(r_string name, createFunc cf, r_string localizedName, r_string readableName) :
                _name(std::move(name)), _createFunction(cf), _localizedName(std::move(localizedName)), _readableName(std::move(readableName)), _javaFunc("none") {}
        #else
            script_type_info(r_string name, createFunc cf, r_string localizedName, r_string readableName, r_string description, r_string category, r_string typeName) :
                _name(std::move(name)), _createFunction(cf), _localizedName(std::move(localizedName)), _readableName(std::move(readableName)), _description(std::move(description)),
                _category(std::move(category)), _typeName(std::move(typeName)), _javaFunc("none") {}
        #endif
            r_string _name;           // SCALAR
            createFunc _createFunction{ nullptr };
            r_string _localizedName; //@STR_EVAL_TYPESCALAR
            r_string _readableName; //Number
        #ifndef __linux__
            r_string _description; //A real number.
            r_string _category; //Default
            r_string _typeName; //float/NativeObject
        #endif
            r_string _javaFunc; //Lcom/bistudio/JNIScripting/NativeObject;
        };

        struct compound_value_pair {
            script_type_info *first;
            script_type_info *second;
        };

        struct compound_script_type_info {
            uintptr_t           v_table;
            compound_value_pair *types;
        };

        class sqf_script_type : public serialize_class {
        public:
            static uintptr_t type_def; //#TODO should not be accessible
            sqf_script_type() { set_vtable(type_def); }
            sqf_script_type(const script_type_info* type) {
                single_type = type; set_vtable(type_def);
            }
            //#TODO use type_def instead
            sqf_script_type(uintptr_t vt, const script_type_info* st, compound_script_type_info* ct) :
                single_type(st), compound_type(ct) {
                set_vtable(vt);
            }
            void set_vtable(uintptr_t v) { *reinterpret_cast<uintptr_t*>(this) = v; }
            uintptr_t get_vtable() const { return *reinterpret_cast<const uintptr_t*>(this); }
            sqf_script_type(sqf_script_type&& other) noexcept :
            single_type(other.single_type), compound_type(other.compound_type) {
                set_vtable(other.get_vtable());
            }
            sqf_script_type(const sqf_script_type& other) :
                single_type(other.single_type), compound_type(other.compound_type) {
                set_vtable(other.get_vtable());
            }
            sqf_script_type& operator=(const sqf_script_type& other) {
                single_type = other.single_type;
                compound_type = other.compound_type;
                set_vtable(other.get_vtable());
                return *this;
            }
            const script_type_info*     single_type{ nullptr };
            compound_script_type_info*  compound_type{ nullptr };
            value_types type() const;
            std::string type_str() const;
            bool operator==(const sqf_script_type& other) const {
                return single_type == other.single_type && compound_type == other.compound_type;
            }
            bool operator!=(const sqf_script_type& other) const {
                return single_type != other.single_type || compound_type != other.compound_type;
            }
        };

        struct unary_operator : public _refcount_vtable_dummy {
            unary_function   *procedure_addr;
            sqf_script_type   return_type;
            sqf_script_type   arg_type;
        };

        struct unary_entry {
            const char *name;
            uintptr_t procedure_ptr_addr;
            unary_operator *op;
        };

        struct binary_operator : public _refcount_vtable_dummy {
            binary_function   *procedure_addr;
            sqf_script_type   return_type;
            sqf_script_type   arg1_type;
            sqf_script_type   arg2_type;
        };

        struct binary_entry {
            const char *name;
            uintptr_t procedure_ptr_addr;
            binary_operator *op;
        };

        struct nular_operator : public _refcount_vtable_dummy {
            nular_function   *procedure_addr;
            sqf_script_type   return_type;
        };

        struct nular_entry {
            const char *name;
            uintptr_t procedure_ptr_addr;
            nular_operator *op;
        };




        class game_data : public refcount, public __internal::I_debug_value {
            friend class game_value;
            friend class intercept::invoker;
        public:
            virtual const sqf_script_type & type() const {
            #ifdef _MSC_VER //Only on MSVC on Windows
                __debugbreak(); //If you landed here you did something wrong while implementing your custom type.
            #endif
                static sqf_script_type dummy; return dummy;
            }
            virtual ~game_data() {}
        protected:
            virtual bool get_as_bool() const { return false; }
            virtual float get_as_number() const { return 0.f; }
            virtual const r_string& get_as_string() const { static r_string dummy; dummy.clear(); return dummy; } ///Only usable on String and Code! Use to_string instead!
            virtual const auto_array<game_value>& get_as_const_array() const { static auto_array<game_value> dummy; dummy.clear(); return dummy; } //Why would you ever need this?
            virtual auto_array<game_value> &get_as_array() { static auto_array<game_value> dummy; dummy.clear(); return dummy; }
            virtual game_data *copy() const { return nullptr; }
            virtual void set_readonly(bool) {} //No clue what this does...
            virtual bool get_readonly() const { return false; }
            virtual bool get_final() const { return false; }
            virtual void set_final(bool) {}; //Only on GameDataCode AFAIK
        public: 
            virtual r_string to_string() const { return r_string(); }
            virtual bool equals(const game_data *) const { return false; };
            virtual const char *type_as_string() const { return "unknown"; }
            virtual bool is_nil() const { return false; }
        private:
            virtual void placeholder() const {};
            virtual bool can_serialize() { return false; }


            int IAddRef() override { return add_ref(); };
            int IRelease() override { return release(); };
        public:                               //#TODO make protected and give access to param_archive
            virtual serialization_return serialize(param_archive& ar) {
                if (ar._isExporting) {
                    sqf_script_type _type = type();
                    ar.serialize(r_string("type"sv), _type, 1);
                }

                return serialization_return::no_error;
            }
            static game_data* createFromSerialized(param_archive& ar);
        protected:
        #ifdef __linux__
        public:
        #endif
            uintptr_t get_vtable() const {
                return *reinterpret_cast<const uintptr_t*>(this);
            }
            uintptr_t get_secondary_vtable() const {
                return *reinterpret_cast<const uintptr_t*>(static_cast<const __internal::I_debug_value*>(this));
            }
        };

        class game_value_conversion_error : public std::runtime_error {
        public:
            explicit game_value_conversion_error(const std::string& _Message)
                : runtime_error(_Message) {}

            explicit game_value_conversion_error(const char* _Message)
                : runtime_error(_Message) {}
        };

        class game_value : public serialize_class {
            friend class intercept::invoker;
            friend void __internal::set_game_value_vtable(uintptr_t);
        protected:
            static uintptr_t __vptr_def; //Users should not be able to access this
        public:
            game_value();
            ~game_value();
            void copy(const game_value & copy_); //I don't see any use for this.
            game_value(const game_value &copy_);
            game_value(game_value &&move_) noexcept;



            //Conversions
            game_value(game_data* val_);
            game_value(float val_);
            game_value(int val_);
            game_value(bool val_);
            game_value(const std::string &val_);
            game_value(const r_string &val_);
            game_value(std::string_view val_);
            game_value(const char* str_) : game_value(std::string_view(str_)) {}
            game_value(const std::vector<game_value> &list_);
            game_value(const std::initializer_list<game_value> &list_);
            game_value(auto_array<game_value> &&array_);
            template<class Type>
            game_value(const auto_array<Type>& array_) : game_value(std::move(auto_array<game_value>(array_.begin(), array_.end()))) {
                static_assert(std::is_convertible<Type, game_value>::value);
            }
            template<class Type>
            game_value(const std::vector<Type>& array_) : game_value(std::move(auto_array<game_value>(array_.begin(), array_.end()))) {
                static_assert(std::is_convertible<Type, game_value>::value);
            }
            game_value(const vector3 &vec_);
            game_value(const vector2 &vec_);
            game_value(const internal_object &internal_);

            game_value & operator = (const game_value &copy_);
            game_value & operator = (game_value &&move_) noexcept;
            game_value & operator = (float val_);
            game_value & operator = (bool val_);
            game_value & operator = (const std::string &val_);
            game_value & operator = (const r_string &val_);
            game_value & operator = (std::string_view val_);
            game_value & operator = (const char* str_) {
                return this->operator =(std::string_view(str_));
            }
            game_value & operator = (const std::vector<game_value> &list_);
            game_value & operator = (const vector3 &vec_);
            game_value & operator = (const vector2 &vec_);
            game_value & operator = (const internal_object &internal_);


            operator int() const;
            operator float() const;
            operator bool() const;
            operator std::string() const;
            operator r_string() const;
            operator vector3() const;
            operator vector2() const;

            /**
            * \brief tries to convert the game_value to an array if possible
            * \throws game_value_conversion_error {if game_value is not an array}
            */
            auto_array<game_value>& to_array();
            /**
             * \brief tries to convert the game_value to an array if possible
             * \throw game_value_conversion_error {if game_value is not an array}
             */
            const auto_array<game_value>& to_array() const;
            /**
            * \brief tries to convert the game_value to an array if possible and return the element at given index.
            * \throw game_value_conversion_error {if game_value is not an array}
            */
            game_value& operator [](size_t i_);
            /**
            * \brief tries to convert the game_value to an array if possible and return the element at given index.
            * \throw game_value_conversion_error {if game_value is not an array}
            */
            game_value operator [](size_t i_) const;

            uintptr_t type() const;//#TODO return GameDataType

            [[deprecated("Replaced by size, because that name is more clear")]] size_t length() const;
            size_t size() const;
            //#TODO implement is_null. GameDataObject's objectLink == nullptr. Same for GameDataGroup and others.
            //Returns true for uninitialized game_value's and Nil values returned from Arma
            bool is_nil() const;

            bool operator==(const game_value& other) const;
            bool operator!=(const game_value& other) const;


            size_t hash() const;
            //set's this game_value to null
            void clear() { data = nullptr; }


            serialization_return serialize(param_archive& ar) override;

            ref<game_data> data;
            [[deprecated]] static void* operator new(std::size_t sz_); //Should never be used
            static void operator delete(void* ptr_, std::size_t sz_);
        #ifndef __linux__
        protected:
        #endif
            uintptr_t get_vtable() const;
            void set_vtable(uintptr_t vt);

        };

        class game_value_static : public game_value {
        public:
            ~game_value_static();
            game_value_static(const game_value& copy) : game_value(copy) {}
            game_value_static(game_value&& move) : game_value(move) {}
            game_value_static operator=(const game_value& copy) { data = copy.data;return *this; }
            operator game_value() { return *this; }
        };

    #pragma region GameData Types

        class game_data_number : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            static rv_pool_allocator* pool_alloc_base;
            game_data_number();
            game_data_number(float val_);
            game_data_number(const game_data_number &copy_);
            game_data_number(game_data_number &&move_);
            game_data_number& operator = (const game_data_number &copy_);
            game_data_number& operator = (game_data_number &&move_);
            static void* operator new(std::size_t sz_);
            static void operator delete(void* ptr_, std::size_t sz_);
            float number;
            size_t hash() const {
                return __internal::pairhash(type_def, number);
            };
            //protected:
            //    static thread_local game_data_pool<game_data_number> _data_pool;
        };

        class game_data_bool : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            static rv_pool_allocator* pool_alloc_base;
            game_data_bool();
            game_data_bool(bool val_);
            game_data_bool(const game_data_bool &copy_);
            game_data_bool(game_data_bool &&move_);
            game_data_bool& operator = (const game_data_bool &copy_);
            game_data_bool& operator = (game_data_bool &&move_);
            static void* operator new(std::size_t sz_);
            static void operator delete(void* ptr_, std::size_t sz_);
            bool val;
            size_t hash() const { return __internal::pairhash(type_def, val); };
            //protected:
            //    static thread_local game_data_pool<game_data_bool> _data_pool;
        };

        class game_data_array : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            static rv_pool_allocator* pool_alloc_base;
            game_data_array();
            game_data_array(size_t size_);
            game_data_array(const std::vector<game_value> &init_);
            game_data_array(const std::initializer_list<game_value> &init_);
            game_data_array(auto_array<game_value> &&init_);
            game_data_array(const game_data_array &copy_);
            game_data_array(game_data_array &&move_);
            game_data_array& operator = (const game_data_array &copy_);
            game_data_array& operator = (game_data_array &&move_);
            ~game_data_array();
            auto_array<game_value> data;
            auto length() { return data.count(); }
            size_t hash() const { return __internal::pairhash(type_def, data.hash()); };
            static void* operator new(std::size_t sz_);
            static void operator delete(void* ptr_, std::size_t sz_);
        };

        class game_data_string : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            static rv_pool_allocator* pool_alloc_base;
            game_data_string();
            game_data_string(const std::string &str_);
            game_data_string(const r_string &str_);
            game_data_string(const game_data_string &copy_);
            game_data_string(game_data_string &&move_);
            game_data_string& operator = (const game_data_string &copy_);
            game_data_string& operator = (game_data_string &&move_);
            ~game_data_string();
            r_string raw_string;
            size_t hash() const { return __internal::pairhash(type_def, raw_string); };
            static void* operator new(std::size_t sz_);
            static void operator delete(void* ptr_, std::size_t sz_);
            //protected:
            //    static thread_local game_data_pool<game_data_string> _data_pool;
        };

        class game_data_group : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_group() {
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, group); };
            void *group;
        };

        class game_data_config : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_config() {
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, config); };
            void *config;
        };

        class game_data_control : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_control() {
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, control); };
            void *control;
        };

        class game_data_display : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_display() {
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, display); };
            void *display;
        };

        class game_data_location : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_location() {
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, location); };
            void *location;
        };

        class game_data_script : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_script() {
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, script); }
            void *script;
        };

        class game_data_side : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_side() {
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, side); };
            void *side;
        };

        class game_data_rv_text : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_rv_text() {
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, rv_text); };
            void *rv_text;
        };

        class game_data_team : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_team() {
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, team); };
            void *team;
        };

        class game_data_rv_namespace : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_rv_namespace() {
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, rv_namespace); };
            void *rv_namespace;
        };

        class game_data_code : public game_data {
        public:
            static uintptr_t type_def;
            static uintptr_t data_type_def;
            game_data_code() {
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, code_string); };
            r_string code_string;
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
                *reinterpret_cast<uintptr_t*>(this) = type_def;
                *reinterpret_cast<uintptr_t*>(static_cast<I_debug_value*>(this)) = data_type_def;
            };
            size_t hash() const { return __internal::pairhash(type_def, reinterpret_cast<uintptr_t>(object ? object->object : object)); };
            struct visualState {
                //will be false if you called stuff on nullObj
                bool valid{ false };
                vector3 _aside;
                vector3 _up;
                vector3 _dir;

                vector3 _position;
                float _scale;
                float _maxScale;

                float _deltaT;
                vector3 _speed; // speed in world coordinates
                vector3 _modelSpeed; // speed in model coordinates (updated in Move())
                vector3 _acceleration;
            };
            struct visual_head_pos {
                bool valid{ false };
                vector3 _cameraPositionWorld;
                vector3 _aimingPositionWorld;
            };
        #ifndef __linux__
            //Not compatible yet. Not sure if every will be.
            visualState get_position_matrix() const {
                if (!object || !object->object) return visualState();
                uintptr_t vbase = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(object->object) + 0xA0);

                struct visState1 {
                    vector3 _aside;
                    vector3 _up;
                    vector3 _dir;

                    vector3 _position;
                    float _scale;
                    float _maxScale;
                };
                struct visState2 {
                    float _deltaT;
                    vector3 _speed;
                    vector3 _modelSpeed;
                    vector3 _acceleration;
                };

                visState1* s1 = reinterpret_cast<visState1*>(vbase + sizeof(uintptr_t));
                visState2* s2 = reinterpret_cast<visState2*>(vbase + 0x44);

                return visualState{
                    true,
                    s1->_aside,
                    s1->_up,
                    s1->_dir,
                    { s1->_position.x,s1->_position.z,s1->_position.y},
                    s1->_scale,
                    s1->_maxScale,
                    s2->_deltaT,
                    s2->_speed,
                    s2->_modelSpeed,
                    s2->_acceleration
                };
            }

            visual_head_pos get_head_pos() const {


                if (!object || !object->object) return visual_head_pos();
            #if _WIN64 || __X86_64__
                uintptr_t vbase = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(object->object) + 0xD0);
            #else
                uintptr_t vbase = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(object->object) + 0xA0);
            #endif
                class v1 {
                    virtual void doStuff() {}
                };
                class v2 : public v1 {
                    void doStuff() override {}
                };
                v2* v = reinterpret_cast<v2*>(vbase);
                auto& typex = typeid(*v);
            #ifdef __GNUC__
                auto test = typex.name();
            #else
                auto test = typex.raw_name();
            #endif

                auto hash = typex.hash_code();
                if (hash !=
                #if _WIN64 || __X86_64__
                    0xb57aedbe2fc8b61e
                #else
                    0x6d4f3e40
                #endif
                    && strcmp(test, ".?AVManVisualState@@") != 0) return  visual_head_pos();
                visual_head_pos* s3 = reinterpret_cast<visual_head_pos*>(vbase +
                #if _WIN64 || __X86_64__
                    0x168
                #else
                    0x114
                #endif
                    );
                return  visual_head_pos();
                return visual_head_pos{
                    true,
                    { s3->_cameraPositionWorld.x,s3->_cameraPositionWorld.z,s3->_cameraPositionWorld.y },
                    { s3->_aimingPositionWorld.x,s3->_aimingPositionWorld.z,s3->_aimingPositionWorld.y }
                };

            }
        #endif
            struct {
                uint32_t _x;
                void* object;
            } *object;
        };
        //#TODO add game_data_nothing
        enum class GameDataType {
            SCALAR,
            BOOL,
            ARRAY,
            STRING,
            NOTHING,
            ANY,
            NAMESPACE,
            NaN,
            CODE,
            OBJECT,
            SIDE,
            GROUP,
            TEXT,
            SCRIPT,
            TARGET,
            CONFIG,
            DISPLAY,
            CONTROL,
            NetObject,
            SUBGROUP,
            TEAM_MEMBER,
            TASK,
            DIARY_RECORD,
            LOCATION,
            end
        };

        namespace __internal {
            GameDataType game_datatype_from_string(const r_string& name);
            std::string to_string(GameDataType type);
            //Not public API!
            void add_game_datatype(r_string name, GameDataType type);

            struct allocatorInfo {
                uintptr_t genericAllocBase;
                uintptr_t poolFuncAlloc;
                uintptr_t poolFuncDealloc;
                std::array<rv_pool_allocator*, static_cast<size_t>(GameDataType::end)> _poolAllocs;
            };
        }


    #pragma endregion


    #if 0
        template<size_t Size = 1024, size_t Alloc_Length = 512>
        class game_data_string_pool {
        public:
            game_data_string_pool() : _running(false) {
                for (size_t i = 0; i < Size; ++i)
                    _buy_entry(Alloc_Length);
            }

            inline r_string acquire(size_t alloc_length_) {
                std::lock_guard<std::mutex> collector_lock(_string_collection_mutex);
                if (_pool_queue.size() == 0 || alloc_length_ > Alloc_Length)
                    _buy_entry(alloc_length_);
                r_string ret = _pool_queue.front();
                _pool_queue.pop();
                return ret;
            }

            inline void release(r_string _ptr) {
                /*
                std::lock_guard<std::mutex> collector_lock(_string_collection_mutex);
                if (_ptr->ref_count_internal <= 1) {
                    _ptr->ref_count_internal = 0;
                    _ptr->length = 0;
                    _ptr->char_string = 0x0;
                    _pool_queue.push(_ptr);
                } else {
                    if (!_running) {
                        _running = true;
                        _collection_thread = std::thread(&game_data_string_pool::_string_collector, this);
                    }
                    _string_collection.push_back(_ptr);
                }
                */
            }

            ~game_data_string_pool() {
                _running = false;
                _collection_thread.join();
            }
        protected:
            std::queue<r_string> _pool_queue;
            std::vector<r_string> _pool;
            std::mutex _string_collection_mutex;
            std::thread _collection_thread;
            std::atomic<bool> _running;

            inline void _buy_entry(size_t alloc_length_) {
                r_string str;
                _pool_queue.push(str);
                _pool.push_back(str);
            }

            /*!
            @brief A list of strings to monitor for deletion, used by the string collector.
            */
            std::list<r_string> _string_collection;

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
            void _string_collector() {
                /*
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
                            } else {
                                ++it;
                            }
                        }
                    }
                    sleep(250);
                }
                */
            }
        };
    #endif


    #pragma region RSQF
        class registered_sqf_function {
            friend class sqf_functions;
        public:
            registered_sqf_function() {};
            explicit registered_sqf_function(std::shared_ptr<registered_sqf_function_impl> func_);
            void clear() { _function = nullptr; }
        private:
            std::shared_ptr<registered_sqf_function_impl> _function;
        };

    #ifdef __linux__
        template <game_value(*T)(game_value, game_value)>
        static game_value  userFunctionWrapper(uintptr_t gs, uintptr_t left_arg_, uintptr_t right_arg_) {
            game_value* l = reinterpret_cast<game_value*>(left_arg_);
            game_value* r = reinterpret_cast<game_value*>(right_arg_);
            return game_value(T(*l, *r));
        }

        template <game_value(*T)(game_value)>
        static game_value userFunctionWrapper(uintptr_t gs, uintptr_t right_arg_) {
            game_value* r = reinterpret_cast<game_value*>(right_arg_);
            return game_value(T(*r));
        }

        template <game_value(*T)(const game_value&)>
        static game_value userFunctionWrapper_ref(uintptr_t gs, uintptr_t right_arg_) {
            game_value* r = reinterpret_cast<game_value*>(right_arg_);
            return game_value(T(*r));
        }

        template <game_value(*T)()>
        static game_value userFunctionWrapper(uintptr_t gs) {
            return game_value(T());
            //return sqf_this_;
        }
    #else
        template <game_value(*T)(game_value, game_value)>
        static game_value* userFunctionWrapper(game_value* sqf_this_, uintptr_t, uintptr_t left_arg_, uintptr_t right_arg_) {
            game_value* l = reinterpret_cast<game_value*>(left_arg_);
            game_value* r = reinterpret_cast<game_value*>(right_arg_);
            ::new (sqf_this_) game_value(T(*l, *r));
            return sqf_this_;
        }

        template <game_value(*T)(game_value)>
        static game_value* userFunctionWrapper(game_value* sqf_this_, uintptr_t, uintptr_t right_arg_) {
            game_value* r = reinterpret_cast<game_value*>(right_arg_);
            ::new (sqf_this_) game_value(T(*r));
            return sqf_this_;
        }

        template <game_value(*T)(const game_value&)>
        static game_value* userFunctionWrapper_ref(game_value* sqf_this_, uintptr_t, uintptr_t right_arg_) {
            game_value* r = reinterpret_cast<game_value*>(right_arg_);
            ::new (sqf_this_) game_value(T(*r));
            return sqf_this_;
        }

        template <game_value(*T)()>
        static game_value* userFunctionWrapper(game_value* sqf_this_, uintptr_t) {
            ::new (sqf_this_) game_value(T());
            return sqf_this_;
        }
    #endif
    #pragma endregion

        enum class register_plugin_interface_result {
            success,
            interface_already_registered,
            interface_name_occupied_by_other_module, //Use list_plugin_interfaces(name_) to find out who registered it 
            invalid_interface_class
        };


    }
    namespace __internal {
        //#TODO move to types::__internal and make less ugly
        class game_functions;
        class game_operators;
        class gsNular;
        class game_state {  //ArmaDebugEngine is thankful for being allowed to contribute this.
        public:
            types::auto_array<const types::script_type_info *> _scriptTypes;
            types::map_string_to_class<game_functions, types::auto_array<game_functions>> _scriptFunctions;
            types::map_string_to_class<game_operators, types::auto_array<game_operators>> _scriptOperators;
            types::map_string_to_class<gsNular, types::auto_array<gsNular>> _scriptNulars;
            types::game_data* create_gd_from_type(const types::sqf_script_type& type, types::param_archive* ar) const {
                for (auto& it : _scriptTypes) {
                    if (types::sqf_script_type(it) == type) {
                        if (it->_createFunction) return it->_createFunction(ar);
                        return nullptr;
                    }
                }
                return nullptr;
            }
        };
    }
}

namespace std {
    template <> struct hash<intercept::types::r_string> {
        size_t operator()(const intercept::types::r_string& x) const {
            return x.hash();
        }
    };
    template <> struct hash<intercept::types::game_value> {
        size_t operator()(const intercept::types::game_value& x) const {
            return x.hash();
        }
    };
}





