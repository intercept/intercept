#pragma once
#include "../shared.hpp"
#include "shared\functions.hpp"
#include <chrono>
#include <regex>

#define DLLEXPORT __declspec(dllexport)



using namespace std::literals;

namespace intercept {
    namespace client {








        class host {
        public:
            static client_functions functions;
        protected:
            class mem_watcher {
            public:
                mem_watcher();
                ~mem_watcher();
                void clean();
                void add_watch(game_value &data_);
            protected:
                void _add(game_value &data_);
                std::list<game_value> _watch_data;
            };


        public:
            static mem_watcher memory_watcher;
        };


        
        extern "C" {
            DLLEXPORT void __cdecl assign_functions(const struct intercept::client_functions funcs);
            DLLEXPORT void __cdecl handle_unload();
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