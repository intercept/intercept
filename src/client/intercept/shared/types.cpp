#include "types.hpp"

namespace intercept {
    namespace rv_types {
        uintptr_t game_data_string::type_def;
        uintptr_t game_data_string::data_type_def;

        uintptr_t game_data_object::type_def;
        uintptr_t game_data_object::data_type_def;

        uintptr_t game_data_number::type_def;
        uintptr_t game_data_number::data_type_def;

        uintptr_t game_data_array::type_def;
        uintptr_t game_data_array::data_type_def;

        uintptr_t game_data_array_stack::type_def;
        uintptr_t game_data_array_stack::data_type_def;

        uintptr_t game_data_bool::type_def;
        uintptr_t game_data_bool::data_type_def;

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

        uintptr_t game_data_text::type_def;
        uintptr_t game_data_text::data_type_def;

        uintptr_t game_data_team::type_def;
        uintptr_t game_data_team::data_type_def;

        uintptr_t game_data_namespace::type_def;
        uintptr_t game_data_namespace::data_type_def;



        uintptr_t rv_game_value::__vptr_def;
        std::string rv_string::string() {
            return std::string((char *)&char_string);
        }

        value_type op_value_entry::type() {
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

        std::string game_data_string::get_string() {
            return std::string((char *)&raw_string->char_string);
        }

        bool game_data_string::set_string(std::string val_) {
            if (ref_count_internal == 0x0000dede) {
                if (val_.length() + 1 < 2048) {
                    memcpy(&raw_string->char_string, val_.c_str(), val_.length() + 1);
                    raw_string->length = val_.length() + 1;
                    return true;
                }
            }
            return false;
        }

        rv_game_value::rv_game_value() : __vptr(NULL), data(NULL) {
            __vptr = __vptr_def;
        };

        void game_data_array::allocate(size_t size_) {
            data = new rv_game_value[size_];
        }
    }
}


