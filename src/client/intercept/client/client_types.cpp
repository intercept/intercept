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

            config config_ptr::operator>>(std::string& value_) {
                auto binary = (binary_function)host::functions.get_binary_function_typed(">>", "CONFIG", "STRING");
                game_value ret_value = host::functions.invoke_raw_binary(binary, *this, game_value_string(value_));
                return std::make_shared<config_ptr>(ret_value);
            }

            config config_ptr::operator>>(const char* value_) {
                return operator>>(std::string(value_));
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
            task_ptr::~task_ptr()
            {
                host::functions.free_value(&value);
            }
        }
    }
}