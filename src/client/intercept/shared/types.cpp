#include "types.hpp"

namespace intercept {
    namespace rv_types {

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

        game_value::game_value() : __vptr(NULL), data(NULL) {
        
        };
    }
}


