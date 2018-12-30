#pragma once
#include "shared.hpp"
#include "shared/client_types.hpp"

#ifndef __linux__
#include "Windows.h"
#include <future>
#include <intrin.h>
#endif

namespace intercept::cert {

    class signing {
    public:
        signing() {}
        ~signing() {}
        enum class security_class {
            not_signed,
            self_signed,
            core
        };
        std::pair<intercept::cert::signing::security_class, std::optional<std::string>> verifyCert(std::wstring_view file_path, types::r_string ca_cert);
    private:
        static void debug_certs_in_store(void* store);
    };

#ifndef __linux__
#include "Windows.h"
#include <future>
#include <intrin.h>


#define CERT_ENTER \
    HMODULE hmod;                                                                                                                               \
    if (auto pcToHeader = GetProcAddress(GetModuleHandleA("ntdll"), "RtlPcToFileHeader"); pcToHeader) {                                         \
        if (reinterpret_cast<void*(NTAPI *)(_In_ PVOID PcValue, _Out_ PVOID * BaseOfImage)>(pcToHeader)(_ReturnAddress(), (void**)&hmod)) {     \
            intercept::cert::current_security_class = intercept::extensions::get().get_module_security_class(reinterpret_cast<uintptr_t>(hmod));\
        }}
#define CERT_EXIT intercept::cert::current_security_class = intercept::cert::signing::security_class::not_signed;

    extern thread_local signing::security_class current_security_class;

#else

#define CERT_ENTER
#define CERT_EXIT

    static const signing::security_class current_security_class = signing::security_class::core;
#endif


}


