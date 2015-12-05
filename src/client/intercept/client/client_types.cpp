#include "client.hpp"
#include "client_types.hpp"
#include "shared\functions.hpp"

namespace intercept {
    namespace client {
        namespace types {
            internal_ptr::internal_ptr()
            {
            }

            internal_ptr::internal_ptr(rv_types::game_value value_) : value(value_)
            {
            }

            internal_ptr::~internal_ptr()
            {
                host::functions.free_value(&value);
            }
            object_ptr::~object_ptr()
            {
                host::functions.free_value(&value);
            }
            group_ptr::~group_ptr()
            {
                host::functions.free_value(&value);
            }
            code_ptr::~code_ptr()
            {
                host::functions.free_value(&value);
            }
            config_ptr::~config_ptr()
            {
                host::functions.free_value(&value);
            }
            control_ptr::~control_ptr()
            {
                host::functions.free_value(&value);
            }
            display_ptr::~display_ptr()
            {
                host::functions.free_value(&value);
            }
            location_ptr::~location_ptr()
            {
                host::functions.free_value(&value);
            }
            script_ptr::~script_ptr()
            {
                host::functions.free_value(&value);
            }
            side_ptr::~side_ptr()
            {
                host::functions.free_value(&value);
            }
            text_ptr::~text_ptr()
            {
                host::functions.free_value(&value);
            }
            team_member_ptr::~team_member_ptr()
            {
                host::functions.free_value(&value);
            }
            rv_namespace_ptr::~rv_namespace_ptr()
            {
                host::functions.free_value(&value);
            }
        }
    }
}