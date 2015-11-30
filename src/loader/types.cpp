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
                    compound_type->types->first->type_name->string() + "," +
                    compound_type->types->second->type_name->string();
            }
        }

        std::string game_data_string::get_string() {
            return std::string((char *)&string->char_string);
        }

        game_value::game_value() : __vptr(NULL), data(NULL) {
        
        };
    }
}