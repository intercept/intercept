#pragma once
#include "../shared.hpp"
#include "client.hpp"
#include "shared/functions.hpp"
#include "shared/client_types.hpp"

constexpr std::string_view operator ""_sv(char const* str, std::size_t len) noexcept {
    return { str, len };
};

using namespace intercept::types;
using namespace intercept::client;

namespace intercept {
    namespace client {

        class __sqf {
        public:
            static void __initialize();
#include "sqf_pointers_declaration.hpp"
            static binary_function binary__configaccessor__config__string__ret__config;
        };

        
    }
}