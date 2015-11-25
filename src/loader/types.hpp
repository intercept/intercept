#pragma once
#include "shared.hpp"


namespace intercept {
    namespace rv_types {
        typedef int(__cdecl *nular_function)(char *, int);
        typedef int(__cdecl *unary_function)(char *, int, int);
        typedef int(__cdecl *binary_function)(char *, int, int, int);

        struct unary_operator {
            uint32_t        v_table;
            uint32_t        ref_count;
            unary_function  *procedure_addr;
            uint32_t        return_type;
            uint32_t        arg_type;
        };

        struct unary_entry {
            char *name;
            unary_operator *op;
        };

        struct binary_operator {
            uint32_t        v_table;
            uint32_t        ref_count;
            unary_function  *procedure_addr;
            uint32_t        return_type;
            uint32_t        arg1_type;
            uint32_t        arg2_type;
        };

        struct binary_entry {
            char *name;
            binary_operator *op;
        };

        struct nular_operator {
            uint32_t        v_table;
            uint32_t        ref_count;
            nular_function  *procedure_addr;
            uint32_t        return_type;
        };

        struct nular_entry {
            char *name;
            nular_operator *op;
        };


    }
}