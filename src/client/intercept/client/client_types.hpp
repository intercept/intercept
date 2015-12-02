#pragma once
#include "shared.hpp"
#include "shared\types.hpp"
#include <memory>

namespace intercept {
    namespace client {
        namespace types {
            class object_ptr {
            public:
                object_ptr();
                object_ptr(rv_types::game_value rv_obj_);
                ~object_ptr();
                rv_types::game_value rv_obj;
            };

            typedef std::shared_ptr<object_ptr> object;
        }
    }
}