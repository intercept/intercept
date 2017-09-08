#include "signing.hpp"
#ifndef __linux__
#include <wincrypt.h>
#include <wintrust.h>
#include <windows.h>
#pragma comment(lib, "crypt32.lib")

//https://stackoverflow.com/questions/7241453/read-and-validate-certificate-from-executable
/*
https://stackoverflow.com/questions/84847/how-do-i-create-a-self-signed-certificate-for-code-signing-on-windows
CA:
makecert -r -pe -n "CN=InterceptSignTest CA" -ss CA -sr CurrentUser -a sha256 -cy authority -sky signature -sv InterceptSignTest.pvk InterceptSignTestCA.cer
CodesignCert:
makecert -pe -n "CN=InterceptSignTest SPC" -a sha256 -cy end  -sky signature -ic InterceptSignTestCA.cer -iv InterceptSignTest.pvk -sv InterceptSignTestCodeSignCert.pvk InterceptSignTestCodeSignCert.cer
PFX:
pvk2pfx -pvk InterceptSignTestCodeSignCert.pvk -spc InterceptSignTestCodeSignCert.cer -pfx InterceptSignTestCodeSignCert.pfx

sign binary:
signtool sign /v /f InterceptSignTestCodeSignCert.pfx  /t http://timestamp.comodoca.com/authenticode SignatureCheck.exe


*/

//Only debug
#include <cryptuiapi.h>
#pragma comment (lib, "cryptui.lib")

using namespace intercept::types;
typedef struct {
    LPWSTR lpszProgramName;
    LPWSTR lpszPublisherLink;
    LPWSTR lpszMoreInfoLink;
} SPROG_PUBLISHERINFO, *PSPROG_PUBLISHERINFO;


intercept::cert::signing::signing(std::wstring_view file_path_, types::r_string ca_cert_) : file_path(file_path_), ca_cert(ca_cert_) {}

bool intercept::cert::signing::verify() {
    if (verified) return verified;
    HCERTSTORE hStore = nullptr;
    HCRYPTMSG hMsg = nullptr;
    DWORD dwEncoding, dwContentType, dwFormatType;
    DWORD dwSignerInfo;
    CERT_INFO CertInfo;
    //file_path = file_path.substr(4);
    BOOL fResult = CryptQueryObject(CERT_QUERY_OBJECT_FILE,
        file_path.data(),
        CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
        CERT_QUERY_FORMAT_FLAG_BINARY,
        0,
        &dwEncoding,
        &dwContentType,
        &dwFormatType,
        &hStore,
        &hMsg,
        nullptr);
    if (!fResult) return false;

    // Get signer information size.
    fResult = CryptMsgGetParam(hMsg,
        CMSG_SIGNER_INFO_PARAM,
        0,
        nullptr,
        &dwSignerInfo);
    if (!fResult) {
        if (hMsg) CryptMsgClose(hMsg);
        if (hStore) CertCloseStore(hStore, 0);
        return false;
    }

    // Allocate memory for signer information.
    PCMSG_SIGNER_INFO pSignerInfo = static_cast<PCMSG_SIGNER_INFO>(LocalAlloc(LPTR, dwSignerInfo));
    if (!pSignerInfo) {
        if (hStore) CertCloseStore(hStore, 0);
        return false;
    }

    // Get Signer Information.
    fResult = CryptMsgGetParam(hMsg,
        CMSG_SIGNER_INFO_PARAM,
        0,
        static_cast<PVOID>(pSignerInfo),
        &dwSignerInfo);
    if (hMsg) CryptMsgClose(hMsg);
    if (!fResult) {
        if (hStore) CertCloseStore(hStore, 0);
        if (pSignerInfo) LocalFree(pSignerInfo);
        return false;
    }

    // Search for the signer certificate in the temporary 
    // certificate store.
    CertInfo.Issuer = pSignerInfo->Issuer;
    CertInfo.SerialNumber = pSignerInfo->SerialNumber;

    //create in-memory CertStore to hold our CA
    HCERTSTORE hMemoryStore = CertOpenStore(CERT_STORE_PROV_MEMORY, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, NULL, 0, nullptr);
    if (!hMemoryStore) {
        if (hStore) CertCloseStore(hStore, 0);
        if (pSignerInfo) LocalFree(pSignerInfo);
        return false;
    }

    unsigned char           derPubKey[2048];
    DWORD         derPubKeyLen = 2048;
    if (!CryptStringToBinaryA(ca_cert.data(), 0, CRYPT_STRING_BASE64HEADER, derPubKey, &derPubKeyLen, nullptr, nullptr)) {
        if (hStore) CertCloseStore(hStore, 0);
        if (pSignerInfo) LocalFree(pSignerInfo);
        return false;
    }


    PCCERT_CONTEXT ct = CertCreateCertificateContext(PKCS_7_ASN_ENCODING | X509_ASN_ENCODING,
        derPubKey,
        derPubKeyLen);

    //auto lastError = GetLastError();
    //CRYPT_E_EXISTS
    //E_INVALIDARG

    auto ret3 = CertAddCertificateContextToStore(
        hMemoryStore,
        ct,
        CERT_STORE_ADD_ALWAYS,
        nullptr
    );
    //#TODO error check ret3
    debug_certs_in_store(hMemoryStore);
    debug_certs_in_store(hStore);


    PCCERT_CONTEXT pCertContext = CertFindCertificateInStore(hStore,
        X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
        0,
        CERT_FIND_SUBJECT_CERT,
        static_cast<PVOID>(&CertInfo),
        nullptr);
    if (!pCertContext) {
        if (hStore) CertCloseStore(hStore, 0);
        if (pSignerInfo) LocalFree(pSignerInfo);
        return false;
    }

    PCCERT_CHAIN_CONTEXT chainContext;
    CERT_ENHKEY_USAGE        EnhkeyUsage;
    CERT_USAGE_MATCH         CertUsage;
    CERT_CHAIN_PARA          ChainPara;

    EnhkeyUsage.cUsageIdentifier = 0;
    EnhkeyUsage.rgpszUsageIdentifier = nullptr;
    CertUsage.dwType = USAGE_MATCH_TYPE_AND;
    CertUsage.Usage = EnhkeyUsage;
    ChainPara.cbSize = sizeof(CERT_CHAIN_PARA);
    ChainPara.RequestedUsage = CertUsage;

    CERT_CHAIN_ENGINE_CONFIG ChainConfig;
    ChainConfig.cbSize = sizeof(CERT_CHAIN_ENGINE_CONFIG);
    ChainConfig.hRestrictedRoot = nullptr;
    ChainConfig.hRestrictedTrust = nullptr;
    ChainConfig.hRestrictedOther = nullptr;
    ChainConfig.cAdditionalStore = 0;
    ChainConfig.rghAdditionalStore = nullptr;
    ChainConfig.dwFlags = CERT_CHAIN_CACHE_END_CERT;
    ChainConfig.dwUrlRetrievalTimeout = 0;
    ChainConfig.MaximumCachedCertificates = 0;
    ChainConfig.CycleDetectionModulus = 0;
    ChainConfig.hExclusiveRoot = hMemoryStore;
    ChainConfig.hExclusiveTrustedPeople = hMemoryStore;
    HCERTCHAINENGINE         hChainEngine;
    auto ret4 = CertCreateCertificateChainEngine(
        &ChainConfig,
        &hChainEngine);
    //auto err = GetLastError();
    if (!ret4) {
        if (pSignerInfo) LocalFree(pSignerInfo);
        if (hStore) CertCloseStore(hStore, 0);
        if (pSignerInfo) LocalFree(pSignerInfo);
        if (pCertContext) CertFreeCertificateContext(pCertContext);
        return false;
    }


    auto ret = CertGetCertificateChain(
        hChainEngine,
        pCertContext,
        NULL,
        hMemoryStore,
        &ChainPara,
        0,
        NULL,
        &chainContext
    );
    //chainContext.TrustStatus.dwErrorStatus should be 0x20 for CERT_TRUST_IS_UNTRUSTED_ROOT which is correct




    AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA  policy2 = { sizeof(policy2) };
    policy2.dwRegPolicySettings = 0;
    policy2.pSignerInfo = pSignerInfo;

    AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS  status2 = { sizeof(status2) };

    CERT_CHAIN_POLICY_PARA policy = { sizeof(policy) };
    policy.pvExtraPolicyPara = &policy2;

    CERT_CHAIN_POLICY_STATUS status = { sizeof(status) };
    status.pvExtraPolicyStatus = &status2;


    BOOL verified = CertVerifyCertificateChainPolicy(CERT_CHAIN_POLICY_BASE,//CERT_CHAIN_POLICY_AUTHENTICODE,
        chainContext,
        &policy,
        &status);

    if (hStore) CertCloseStore(hStore, 0);
    if (pSignerInfo) LocalFree(pSignerInfo);
    if (pCertContext) CertFreeCertificateContext(pCertContext);

    return verified && status.dwError == 0x0;



}


intercept::cert::signing::~signing() {}

void intercept::cert::signing::debug_certs_in_store(HCERTSTORE store) {
    PCCERT_CONTEXT pCertContextx = nullptr;
    while (pCertContextx = CertEnumCertificatesInStore(store, pCertContextx)) {
        CryptUIDlgViewContext(CERT_STORE_CERTIFICATE_CONTEXT, pCertContextx, nullptr, nullptr, 0, nullptr);
    }
}
#endif
