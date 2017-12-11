#pragma once
#include <cstdint>
#include <assert.h>

#pragma once

#ifdef __GNUC__
#define __forceinline __attribute__((always_inline))
#endif

namespace intercept {
    template<typename T>
    class singleton {
        // Cannot copy Singleton
        singleton(const singleton&) = delete;
        singleton(singleton&&) = delete;
        singleton& operator=(const singleton&) = delete;
        singleton& operator=(singleton&&) = delete;
    public:
        static __forceinline T & get() noexcept {
            return _singletonInstance;
            //if (_singletonInstance == nullptr) {
            //    assert(_initialized == false);
            //    _initialized = true;
            //    _singletonInstance = new T();
            //}
            //    
            //return *_singletonInstance;
        }
        static void release() {
            //delete _singletonInstance;
        }
    protected:
        // Can only create Singleton via get() function
        singleton() noexcept {}
        static T /***/_singletonInstance;
        static bool _initialized;
    };
    template<typename T>
    T/***/ singleton<T>::_singletonInstance/* = nullptr*/;
    template<typename T>
    bool singleton<T>::_initialized = false;
}
