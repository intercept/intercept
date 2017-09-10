#pragma once
#include "shared.hpp"
#include "shared/client_types.hpp"
namespace intercept::cert {



    class signing {
    public:
        signing(std::wstring_view file_path_, types::r_string ca_cert_);
        bool verify();
        ~signing();
    private:
        std::wstring_view file_path;
        types::r_string ca_cert;
        bool verified = false;
        static void debug_certs_in_store(void* store);
    };
}


