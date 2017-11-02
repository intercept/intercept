#pragma once
#include "shared.hpp"
#include "shared/client_types.hpp"
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
}


