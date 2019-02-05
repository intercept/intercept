#include "pointers.hpp"

#ifndef INTERCEPT_NO_SQF
namespace intercept {
    namespace client {
#include "sqf_pointers_definitions.hpp"
        binary_function __sqf::binary__configaccessor__config__string__ret__config;
        void __sqf::__initialize()
        {
#include "sqf_assignments.hpp"
            __sqf::binary__configaccessor__config__string__ret__config = host::functions.get_binary_function_typed(">>"sv, "CONFIG"sv, "STRING"sv);
        }
    }

    
}
#endif
