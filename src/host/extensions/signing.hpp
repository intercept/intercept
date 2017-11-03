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
        signing();
        enum class security_class {
            not_signed,
            self_signed,
            core
        };
        security_class verifyCert(std::wstring_view file_path, types::r_string ca_cert);
        ~signing();
    private:
        static void debug_certs_in_store(void* store);
    };

    extern thread_local signing::security_class current_security_class;
#ifndef __linux__
#include "Windows.h"
#include <future>
#include <intrin.h>


#define CERT_ENTER \
    HMODULE hmod;                                                                                                                               \
    if (auto pcToHeader = GetProcAddress(GetModuleHandleA("ntdll"), "RtlPcToFileHeader"); pcToHeader) {                                         \
        if (reinterpret_cast<void*(NTAPI *)(_In_ PVOID PcValue, _Out_ PVOID * BaseOfImage)>(pcToHeader)(_ReturnAddress(), (void**)&hmod)) {     \
            auto& seclist = intercept::extensions::get()._module_security_classes;                                                              \
            auto found = seclist.find(reinterpret_cast<uintptr_t>(hmod));                                                                       \
            if (found != seclist.end())                                                                                                         \
                intercept::cert::current_security_class = found->second;                                                                        \
        }}
#define CERT_EXIT intercept::cert::current_security_class = intercept::cert::signing::security_class::not_signed;

#else

#define CERT_ENTER
#define CERT_EXIT

#endif


}


