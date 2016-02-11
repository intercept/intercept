#pragma once
#include "../shared.hpp"
#include "shared\functions.hpp"

#define DLLEXPORT __declspec(dllexport)

namespace intercept {
    namespace client {

        class host {
        public:
            static client_functions functions;
        };
        
        extern "C" {
            DLLEXPORT void __cdecl assign_functions(const struct intercept::client_functions funcs);
        }

        void __initialize();

        class invoker_lock {
        public:
            invoker_lock(bool delayed_ = false);
            invoker_lock(const invoker_lock &) = delete;
            invoker_lock(invoker_lock &&) = delete;
            invoker_lock & operator=(const invoker_lock &) = delete;
            invoker_lock & operator=(invoker_lock &&) = delete;
            ~invoker_lock();
            void lock();
        protected:
            bool _locked;
        };
    }


}