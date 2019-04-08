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

unsigned char coreCACert[] = { 
0x30, 0x82, 0x05, 0x94, 0x30, 0x82, 0x03, 0x7C, 0xA0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x09, 0x00,0xDF, 0xE4, 0xAA, 0xD1, 0xDD, 0x14, 0xD7, 0x1C, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86,
0xF7, 0x0D, 0x01, 0x01, 0x0B, 0x05, 0x00, 0x30, 0x57, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55,0x04, 0x06, 0x13, 0x02, 0x44, 0x45, 0x31, 0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x08, 0x0C,
0x07, 0x47, 0x65, 0x72, 0x6D, 0x61, 0x6E, 0x79, 0x31, 0x12, 0x30, 0x10, 0x06, 0x03, 0x55, 0x04,0x0A, 0x0C, 0x09, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x63, 0x65, 0x70, 0x74, 0x31, 0x0B, 0x30, 0x09,
0x06, 0x03, 0x55, 0x04, 0x0B, 0x0C, 0x02, 0x43, 0x41, 0x31, 0x15, 0x30, 0x13, 0x06, 0x03, 0x55,0x04, 0x03, 0x0C, 0x0C, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x63, 0x65, 0x70, 0x74, 0x20, 0x43, 0x41,
0x30, 0x1E, 0x17, 0x0D, 0x31, 0x37, 0x31, 0x31, 0x30, 0x32, 0x31, 0x31, 0x33, 0x36, 0x32, 0x38,0x5A, 0x17, 0x0D, 0x33, 0x37, 0x31, 0x30, 0x32, 0x38, 0x31, 0x31, 0x33, 0x36, 0x32, 0x38, 0x5A,
0x30, 0x57, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x44, 0x45, 0x31,0x10, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x04, 0x08, 0x0C, 0x07, 0x47, 0x65, 0x72, 0x6D, 0x61, 0x6E,
0x79, 0x31, 0x12, 0x30, 0x10, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x0C, 0x09, 0x49, 0x6E, 0x74, 0x65,0x72, 0x63, 0x65, 0x70, 0x74, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x0C, 0x02,
0x43, 0x41, 0x31, 0x15, 0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0C, 0x0C, 0x49, 0x6E, 0x74,0x65, 0x72, 0x63, 0x65, 0x70, 0x74, 0x20, 0x43, 0x41, 0x30, 0x82, 0x02, 0x22, 0x30, 0x0D, 0x06,
0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x02, 0x0F,0x00, 0x30, 0x82, 0x02, 0x0A, 0x02, 0x82, 0x02, 0x01, 0x00, 0xC7, 0x34, 0x2F, 0x3D, 0x40, 0x30,
0x73, 0x52, 0x06, 0x14, 0x2B, 0xC1, 0x51, 0x84, 0x7D, 0x22, 0xAB, 0x81, 0xD4, 0x34, 0x3B, 0x79,0xF4, 0xE1, 0xC4, 0xBE, 0xA0, 0x6A, 0xCC, 0xC5, 0xDC, 0xB6, 0x5D, 0x54, 0x50, 0x50, 0xCF, 0x45,
0xA3, 0x52, 0x6A, 0x8F, 0xFD, 0x9C, 0x7E, 0x52, 0xAA, 0xCF, 0x0B, 0xF9, 0x8C, 0x31, 0x2A, 0x54,0x7B, 0xB4, 0x8B, 0x15, 0x0A, 0x7A, 0xBA, 0x45, 0x0C, 0x21, 0x7D, 0xA8, 0x68, 0xD2, 0xF2, 0xEE,
0xF8, 0x21, 0xCE, 0x14, 0x4B, 0x97, 0xA5, 0x64, 0x6D, 0xCD, 0x3A, 0x78, 0xB4, 0x15, 0x7A, 0x8E,0x15, 0xCC, 0x2C, 0x3A, 0x1C, 0x8B, 0x98, 0x80, 0xB6, 0xD7, 0x38, 0x32, 0x22, 0xE0, 0x40, 0xDE,
0xBA, 0x91, 0x91, 0x34, 0x43, 0xF2, 0x1B, 0xC9, 0xC2, 0xAD, 0xC5, 0xA2, 0xD4, 0xF3, 0xF6, 0x1A,0x0C, 0x79, 0xB5, 0x2B, 0x12, 0xC4, 0xEB, 0x8F, 0x84, 0xE7, 0xC1, 0x77, 0x4D, 0xCA, 0x6C, 0xAB,
0x77, 0xEB, 0x85, 0xD6, 0xCA, 0xA4, 0x4D, 0x8A, 0x82, 0xB1, 0x66, 0xAE, 0x24, 0xDA, 0x4B, 0xDA,0x33, 0xE0, 0x48, 0x75, 0xC3, 0x0C, 0x35, 0xF4, 0xFA, 0x42, 0x7D, 0x24, 0xF8, 0xCB, 0xFD, 0xE4,
0xBF, 0xF6, 0xAB, 0xF6, 0x72, 0x92, 0x86, 0xA8, 0xCA, 0x3C, 0x85, 0x24, 0x90, 0x3E, 0x1C, 0xEC,0x7B, 0x77, 0x3C, 0x4B, 0xF4, 0x37, 0x49, 0x40, 0xDF, 0x4C, 0x13, 0xC0, 0x53, 0x9F, 0x4E, 0x06,
0xAC, 0x8E, 0xF4, 0x5E, 0x57, 0x09, 0xFF, 0x20, 0x69, 0xEB, 0x10, 0x85, 0xB5, 0xD6, 0x95, 0x01,0xBE, 0xFD, 0x72, 0x93, 0x4B, 0x83, 0x70, 0x8D, 0xFB, 0x11, 0x6D, 0x4A, 0x9F, 0xD8, 0x2B, 0x2C,
0x5A, 0x67, 0x2D, 0x3E, 0x14, 0xC0, 0xF6, 0x2E, 0x63, 0xC1, 0x08, 0x9E, 0x95, 0x4D, 0x20, 0x71,0x1F, 0xC0, 0xFD, 0x52, 0x5C, 0x84, 0x12, 0x7F, 0x7F, 0x65, 0x62, 0xFE, 0xA5, 0xC5, 0x93, 0xF7,
0x36, 0xF5, 0xCB, 0x1B, 0xB2, 0x32, 0xF5, 0xE6, 0x56, 0x8A, 0xED, 0x32, 0x1F, 0xF6, 0xFD, 0x78,0xD2, 0x9E, 0xEB, 0x23, 0x6A, 0x57, 0x77, 0x6D, 0x48, 0x54, 0xD8, 0x25, 0xE2, 0x20, 0x1C, 0xB5,
0xC7, 0x18, 0xCD, 0x74, 0xCB, 0x6C, 0x20, 0x24, 0x7C, 0xC5, 0x6B, 0x55, 0x93, 0x8B, 0x62, 0x0C,0x11, 0x91, 0xB0, 0x27, 0xB7, 0x05, 0xDA, 0x1D, 0x46, 0x9B, 0x82, 0x75, 0x13, 0x84, 0x55, 0x0F,
0xCE, 0xF6, 0x45, 0xB5, 0x6A, 0x6E, 0x39, 0xC4, 0x7A, 0x1F, 0x58, 0x95, 0x37, 0xC3, 0x28, 0x0F,0x8A, 0xF1, 0xFE, 0xD7, 0x74, 0xFD, 0x71, 0x83, 0x9F, 0x5F, 0x58, 0xED, 0x20, 0x6F, 0x29, 0x7F,
0x1F, 0x12, 0x21, 0x76, 0xC2, 0x5D, 0x79, 0x9B, 0xB7, 0xA3, 0x82, 0xD6, 0x96, 0x1F, 0xC1, 0xC2,0xE8, 0x90, 0x43, 0x6D, 0x67, 0x00, 0xC8, 0x41, 0xB9, 0x76, 0x45, 0xD8, 0x0C, 0x5F, 0x9F, 0x5D,
0x37, 0xF2, 0xFB, 0x62, 0x56, 0x02, 0xBE, 0x68, 0xF5, 0x43, 0xC8, 0xBC, 0xB2, 0xFC, 0x9B, 0xE9,0xA4, 0x60, 0x54, 0xD2, 0x1D, 0x4C, 0xD7, 0x4F, 0xBB, 0xCA, 0x1A, 0x2E, 0x4D, 0xE5, 0xAD, 0x76,
0x57, 0xFB, 0x74, 0x1E, 0xBE, 0x6B, 0x8E, 0xBE, 0x90, 0xD6, 0x92, 0x93, 0x69, 0x7E, 0x43, 0x62,0x19, 0xE2, 0xF6, 0x10, 0xF7, 0x6C, 0x79, 0x89, 0x00, 0x08, 0x17, 0x69, 0xA0, 0x19, 0xAD, 0xC6,
0x52, 0x8C, 0x6E, 0xFE, 0x4D, 0x60, 0xEF, 0xFB, 0x95, 0x08, 0x4A, 0x96, 0xF5, 0xFE, 0x82, 0xF9,0x74, 0x1F, 0x01, 0x92, 0x90, 0x11, 0xFF, 0x23, 0x6E, 0xE9, 0xC7, 0x03, 0x3E, 0x0D, 0x31, 0x01,
0x7C, 0x49, 0x55, 0x35, 0x5F, 0x6D, 0x10, 0xBD, 0x50, 0x65, 0x7F, 0x88, 0x6A, 0x21, 0x84, 0xC5,0x90, 0x4C, 0x29, 0x6A, 0x05, 0x67, 0x17, 0x58, 0x96, 0x1D, 0x02, 0x03, 0x01, 0x00, 0x01, 0xA3,
0x63, 0x30, 0x61, 0x30, 0x1D, 0x06, 0x03, 0x55, 0x1D, 0x0E, 0x04, 0x16, 0x04, 0x14, 0xA4, 0xD6,0x8A, 0x2B, 0x70, 0xF8, 0x6B, 0x10, 0x56, 0xA6, 0x16, 0x29, 0x03, 0x5A, 0x97, 0xE2, 0xD0, 0x6E,
0x59, 0x63, 0x30, 0x1F, 0x06, 0x03, 0x55, 0x1D, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0xA4,0xD6, 0x8A, 0x2B, 0x70, 0xF8, 0x6B, 0x10, 0x56, 0xA6, 0x16, 0x29, 0x03, 0x5A, 0x97, 0xE2, 0xD0,
0x6E, 0x59, 0x63, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x1D, 0x13, 0x01, 0x01, 0xFF, 0x04, 0x05, 0x30,0x03, 0x01, 0x01, 0xFF, 0x30, 0x0E, 0x06, 0x03, 0x55, 0x1D, 0x0F, 0x01, 0x01, 0xFF, 0x04, 0x04,
0x03, 0x02, 0x01, 0x86, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01,0x0B, 0x05, 0x00, 0x03, 0x82, 0x02, 0x01, 0x00, 0xBA, 0x48, 0xE8, 0x58, 0x0B, 0x94, 0xFA, 0x6E,
0x5D, 0xD2, 0xFA, 0x02, 0x37, 0x1B, 0x3E, 0xD1, 0x91, 0x2D, 0x2E, 0xAE, 0xED, 0x49, 0x35, 0xAF,0x6A, 0x75, 0x26, 0xB8, 0xB4, 0xFD, 0xE3, 0xDF, 0x94, 0x63, 0xC2, 0x1C, 0x26, 0x9C, 0xCD, 0xE9,
0xB5, 0x76, 0x74, 0x87, 0x2D, 0xE7, 0x7F, 0x1F, 0x5E, 0xED, 0x57, 0xC3, 0xBB, 0x70, 0xFD, 0xAB,0xBC, 0x37, 0x43, 0x62, 0x92, 0x6C, 0xE6, 0x1B, 0x84, 0x2C, 0x84, 0x43, 0x95, 0x4A, 0xCF, 0xDB,
0x4F, 0x36, 0xFE, 0xCB, 0x64, 0x8F, 0x69, 0xD1, 0xA1, 0xAE, 0xB0, 0xCB, 0x61, 0x33, 0xDA, 0xDE,0xAF, 0x69, 0x36, 0x86, 0x58, 0xFD, 0x70, 0xFA, 0x47, 0xBC, 0x2C, 0x34, 0xCF, 0xE6, 0x60, 0x5A,
0xBA, 0x1A, 0xE1, 0xA3, 0xB8, 0x98, 0xBF, 0x08, 0x3B, 0x2F, 0xC0, 0x4A, 0x9E, 0x7A, 0xC6, 0x45,0x29, 0xE8, 0x88, 0x2E, 0xB6, 0x1E, 0xD2, 0x80, 0x51, 0x86, 0x63, 0x69, 0x08, 0xDA, 0xA9, 0x8C,
0xD6, 0xEE, 0xE6, 0xBA, 0x6C, 0x49, 0xCF, 0x94, 0xC0, 0x60, 0x60, 0x44, 0x3C, 0x76, 0xCC, 0x0C,0x7F, 0x73, 0x65, 0x84, 0xD5, 0xCC, 0x97, 0xD2, 0xCC, 0xFF, 0x6E, 0x45, 0xAB, 0x1B, 0x33, 0xC3,
0x58, 0x3F, 0x15, 0x6D, 0xF8, 0x24, 0x91, 0x76, 0x37, 0xF9, 0xCE, 0x1D, 0x6E, 0xB3, 0x94, 0xAA,0x74, 0xF3, 0x20, 0xE4, 0x9C, 0x9E, 0x57, 0xDD, 0x05, 0x63, 0x5C, 0x34, 0xC7, 0xEA, 0x07, 0x84,
0x62, 0xA2, 0x27, 0xFE, 0x2F, 0xF1, 0xAB, 0x50, 0x4B, 0x51, 0x8B, 0x83, 0x6C, 0x18, 0x56, 0xD0,0xD9, 0x1D, 0x5C, 0xEA, 0x06, 0xD4, 0x5C, 0x29, 0x90, 0x88, 0x60, 0x92, 0xDD, 0x27, 0x2C, 0xA9,
0x82, 0xD2, 0xC9, 0x07, 0xFA, 0xF4, 0x33, 0x9E, 0x1C, 0x10, 0xA6, 0x0F, 0x22, 0x53, 0x9A, 0x69,0xE9, 0xB1, 0x9B, 0xAC, 0x30, 0x22, 0xED, 0xE5, 0x93, 0xCD, 0x81, 0x2F, 0xE2, 0xA7, 0x5C, 0xF4,
0x23, 0xA4, 0xE3, 0x63, 0x7A, 0x92, 0x23, 0x05, 0xCC, 0x55, 0x6E, 0x92, 0xAC, 0x81, 0x16, 0xB5,0x96, 0x40, 0x75, 0xF1, 0x00, 0xB0, 0x71, 0x4C, 0xD8, 0x03, 0x9E, 0x8E, 0xFC, 0x24, 0xB6, 0x6A,
0x8A, 0xC0, 0xE0, 0x3F, 0x4E, 0xB4, 0x08, 0x7F, 0xB5, 0x67, 0xF1, 0x96, 0xC0, 0x03, 0xA8, 0xBE,0xFA, 0xA3, 0x65, 0x13, 0xFA, 0x00, 0x5E, 0x1C, 0x40, 0xA0, 0xBF, 0xBB, 0x74, 0x89, 0xEE, 0x89,
0x6E, 0x43, 0x53, 0x63, 0xC0, 0x07, 0xF1, 0x98, 0x0E, 0xA2, 0x58, 0xCF, 0x61, 0x2A, 0xBE, 0xB7,0x15, 0x33, 0xEF, 0xB1, 0xF9, 0x8E, 0xDF, 0x08, 0xE0, 0xFF, 0xEF, 0x2B, 0x09, 0xF2, 0x9E, 0x99,
0xDB, 0x45, 0x5B, 0x7C, 0xE0, 0x0D, 0xFB, 0x67, 0x4F, 0xE7, 0x63, 0xC7, 0x1B, 0x87, 0xAE, 0x22,0x07, 0x2F, 0x7E, 0x1A, 0x28, 0xDD, 0x52, 0x90, 0x0D, 0x00, 0xCB, 0x51, 0x77, 0x43, 0xFA, 0x58,
0x24, 0x0B, 0x83, 0x60, 0x73, 0x74, 0xDE, 0xF0, 0xCC, 0x97, 0xB6, 0xF2, 0x96, 0xE0, 0x69, 0x19,0xB6, 0x3F, 0xD8, 0x08, 0xE6, 0x34, 0x7B, 0x4F, 0xB0, 0x72, 0xF0, 0xE8, 0xA1, 0xFA, 0xAE, 0xF2,
0xC8, 0xAB, 0xF4, 0x61, 0xCA, 0x27, 0xCB, 0x98, 0x9D, 0x03, 0x23, 0x10, 0xFE, 0x2E, 0x61, 0xB6,0xE8, 0x5C, 0x48, 0xA6, 0x62, 0x90, 0x76, 0x3C, 0x6B, 0x13, 0x77, 0xEB, 0x91, 0xD9, 0x5F, 0xB8,
0x0C, 0xB3, 0x8F, 0xE2, 0x96, 0x40, 0xDA, 0x1E, 0x45, 0x30, 0xB8, 0xAE, 0x66, 0x04, 0xBB, 0xB1,0x52, 0xD9, 0x9C, 0x20, 0xD4, 0xF1, 0x0F, 0xAF, 0x37, 0xDD, 0x10, 0x56, 0x34, 0x09, 0x49, 0xCF,
0x9D, 0x4B, 0x3A, 0x0C, 0xF7, 0xCB, 0xB2, 0xA5, 0x0A, 0xEE, 0x26, 0x03, 0x1A, 0x10, 0x02, 0xCC,0xAE, 0x40, 0x25, 0xE1, 0x01, 0xA7, 0x63, 0xB0 };


//Only debug
#include <cryptuiapi.h>
#pragma comment (lib, "cryptui.lib")

using namespace intercept::types;
typedef struct {
    LPWSTR lpszProgramName;
    LPWSTR lpszPublisherLink;
    LPWSTR lpszMoreInfoLink;
} SPROG_PUBLISHERINFO, *PSPROG_PUBLISHERINFO;

template <class T, auto D>
class ManagedObject {
public:
    T obj = nullptr;

    ManagedObject() = default;
    ManagedObject(T s) : obj(s) {}

    ~ManagedObject() {
        if (!obj) return;

        //Special case for CertCloseStore
        if constexpr (std::is_invocable_v<decltype(D), T, DWORD>)
            D(obj, 0);
        else
            D(obj);
    }

    T operator->() { return obj; }
    T* operator&() { return &obj; }
    T& operator*() { return *obj; }
    operator T() { return obj; }

    ManagedObject& operator=(T* s) {
        obj = s;
        return *this;
    }
};

thread_local intercept::cert::signing::security_class intercept::cert::current_security_class = intercept::cert::signing::security_class::not_signed;

std::pair<intercept::cert::signing::security_class, std::optional<std::string>> intercept::cert::signing::verifyCert(std::wstring_view file_path, types::r_string ca_cert) {
    ManagedObject<HCERTSTORE, CertCloseStore> hStore;
    ManagedObject<HCRYPTMSG, CryptMsgClose> hMsg;
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
    if (!fResult) return {security_class::not_signed, fmt::format("CryptQueryObject failed: {}", GetLastError())};

    // Get signer information size.
    fResult = CryptMsgGetParam(hMsg,
        CMSG_SIGNER_INFO_PARAM,
        0,
        nullptr,
        &dwSignerInfo);
    if (!fResult) {
        auto errmsg = fmt::format("CryptMsgGetParam failed: {}", GetLastError());
        return {security_class::not_signed, errmsg};
    }

    // Allocate memory for signer information.
    ManagedObject<PCMSG_SIGNER_INFO, LocalFree> pSignerInfo = static_cast<PCMSG_SIGNER_INFO>(LocalAlloc(LPTR, dwSignerInfo));
    if (!pSignerInfo) {
        return {security_class::not_signed, "LocalAlloc for signerInfo failed"};
    }

    // Get Signer Information.
    fResult = CryptMsgGetParam(hMsg,
        CMSG_SIGNER_INFO_PARAM,
        0,
        static_cast<PVOID>(pSignerInfo),
        &dwSignerInfo);

    if (!fResult) {
        auto errmsg = fmt::format("CryptMsgGetParam failed: {}", GetLastError());
        return {security_class::not_signed, "LocalAlloc for signerInfo failed"};
    }

    // Search for the signer certificate in the temporary
    // certificate store.
    CertInfo.Issuer = pSignerInfo->Issuer;
    CertInfo.SerialNumber = pSignerInfo->SerialNumber;

    //create in-memory CertStore to hold our CA
    ManagedObject<HCERTSTORE, CertCloseStore> hMemoryStore = CertOpenStore(CERT_STORE_PROV_MEMORY, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, NULL, 0, nullptr);
    if (!hMemoryStore) {
        auto errmsg = fmt::format("CertOpenStore failed: {}", GetLastError());
        return {security_class::not_signed, errmsg};
    }

    std::vector<unsigned char> data;
    data.resize(ca_cert.length()*2); //should be enough to store the decoded string
    DWORD derPubKeyLen = 2048;
    //This can fail if the key is invalid. But it can be invalid and still be signed with core key
    if (ca_cert.length() != 0 && CryptStringToBinaryA(ca_cert.data(), 0, CRYPT_STRING_BASE64HEADER, data.data(), &derPubKeyLen, nullptr, nullptr)) {
        ManagedObject<PCCERT_CONTEXT, CertFreeCertificateContext> ct = CertCreateCertificateContext(PKCS_7_ASN_ENCODING | X509_ASN_ENCODING,
            data.data(),
            derPubKeyLen);

        //auto lastError = GetLastError();
        //CRYPT_E_EXISTS
        //E_INVALIDARG

        //Don't care if this errors. The key cert won't land in the store and chain building will fail.
        CertAddCertificateContextToStore(
            hMemoryStore,
            ct,
            CERT_STORE_ADD_ALWAYS,
            nullptr
        );
    }

    //Add the core cert
    ManagedObject<PCCERT_CONTEXT, CertFreeCertificateContext> ct = CertCreateCertificateContext(PKCS_7_ASN_ENCODING | X509_ASN_ENCODING,
        coreCACert,
        sizeof(coreCACert));

    CertAddCertificateContextToStore(
        hMemoryStore,
        ct,
        CERT_STORE_ADD_ALWAYS,
        nullptr
    );

    debug_certs_in_store(hMemoryStore);
    debug_certs_in_store(hStore);

    ManagedObject<PCCERT_CONTEXT, CertFreeCertificateContext> pCertContext = CertFindCertificateInStore(hStore,
        X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
        0,
        CERT_FIND_SUBJECT_CERT,
        static_cast<PVOID>(&CertInfo),
        nullptr);

    if (!pCertContext) {
        auto errmsg = fmt::format("CertFindCertificateInStore failed: {}", GetLastError());
        return {security_class::not_signed, errmsg};
    }

    ManagedObject<PCCERT_CHAIN_CONTEXT, CertFreeCertificateChain> chainContext;
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
    //- sizeof(DWORD) removes WIN8 only flag(dwExclusiveFlags) and makes this win7 compatible
    ChainConfig.cbSize = sizeof(CERT_CHAIN_ENGINE_CONFIG) - sizeof(DWORD);
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
    const auto ret4 = CertCreateCertificateChainEngine(
        &ChainConfig,
        &hChainEngine);
    //auto err = GetLastError();
    if (!ret4) {
        auto errmsg = fmt::format("CertCreateCertificateChainEngine failed: {}", GetLastError());
        return {security_class::not_signed, errmsg};
    }

    const auto ret = CertGetCertificateChain(
        hChainEngine,
        pCertContext,
        nullptr,
        hStore, //Has to be here so we can find intermediaries that are included in the plugins cert
        &ChainPara,
        CERT_CHAIN_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT,
        nullptr,
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


    const BOOL verified = CertVerifyCertificateChainPolicy(CERT_CHAIN_POLICY_BASE,//CERT_CHAIN_POLICY_AUTHENTICODE,
        chainContext,
        &policy,
        &status);

    if (!chainContext) return {security_class::not_signed, "CertVerifyCertificateChainPolicy failed to create chainContext"};
    if (!verified) return {security_class::not_signed, "CertVerifyCertificateChainPolicy failed to verify"};

    bool coreSigned = false;

    //If chain has more than a single element, grab the root cert and compare to our core CA
    if (chainContext->cChain >= 1 && chainContext->rgpChain[chainContext->cChain - 1]->cElement > 1) {
        auto CAContext = chainContext->rgpChain[chainContext->cChain - 1]->rgpElement[chainContext->rgpChain[chainContext->cChain - 1]->cElement - 1]->pCertContext;
        if (CAContext && ct && ct->cbCertEncoded == CAContext->cbCertEncoded) {
            //Check if the CA of this plugin matches the core CA
            coreSigned = std::memcmp(CAContext->pbCertEncoded, ct->pbCertEncoded, ct->cbCertEncoded) == 0;
        }
    }
    std::pair<security_class, std::optional<std::string>> returnCode = {security_class::not_signed, std::nullopt};

    switch (status.dwError) {
        case 0x0: {
            returnCode.first = coreSigned ? security_class::core : security_class::self_signed;
        } break;
        case CRYPT_E_NO_REVOCATION_CHECK: {                                                                    //No revocation list for cert
            if (chainContext->rgpChain[chainContext->cChain - 1]->cElement > 1                                 //have found parent cert
                && chainContext->rgpChain[chainContext->cChain - 1]->rgpElement[1]->pRevocationInfo            //has revocation info
                && chainContext->rgpChain[chainContext->cChain - 1]->rgpElement[1]->pRevocationInfo->pCrlInfo  //has CRL!
            ) {
                //parent has CRL but you don't!
                //#TODO warn
            }
            returnCode.first = coreSigned ? security_class::core : security_class::self_signed;
        } break;
        case CERT_E_REVOCATION_FAILURE:
        case CRYPT_E_REVOCATION_OFFLINE:
            returnCode.first = coreSigned ? security_class::core : security_class::self_signed;
            break;
        case CRYPT_E_REVOKED: //cert actively revoked
            returnCode.first = security_class::not_signed;
            returnCode.second = "Certificate Revoked";
            break;
        case CERT_E_CHAINING: //Couldn't build chain
            returnCode.first = security_class::not_signed;
            returnCode.second = "Couldn't build chain";
            break;
    }

    return returnCode;
}

/*
#include "Windows.h"
#include <future>
typedef void*(NTAPI *rtl)(_In_ PVOID PcValue,
_Out_ PVOID * BaseOfImage);
extern "C" __declspec(dllexport) void myFunc() {

HMODULE hmod;

//RtlPcToFileHeader
if (auto pcToHeader = GetProcAddress(GetModuleHandle(L"ntdll"), "RtlPcToFileHeader"); pcToHeader)  {
if (reinterpret_cast<rtl>(pcToHeader)(_ReturnAddress(), (void**)&hmod)) {
char sz[MAX_PATH];
if (GetModuleFileNameA(hmod, sz, MAX_PATH)) {
OutputDebugStringA(sz);
}
}
}



}

 */

void intercept::cert::signing::debug_certs_in_store([[maybe_unused]] HCERTSTORE store) {
#ifdef __DEBUG
    PCCERT_CONTEXT pCertContextx = nullptr;
    while (pCertContextx = CertEnumCertificatesInStore(store, pCertContextx)) {
        CryptUIDlgViewContext(CERT_STORE_CERTIFICATE_CONTEXT, pCertContextx, nullptr, nullptr, 0, nullptr);
    }
#endif
}

#else

std::pair<intercept::cert::signing::security_class, std::optional<std::string>> intercept::cert::signing::verifyCert(std::wstring_view, types::r_string) {
    return {security_class::core, std::nullopt};
}
void intercept::cert::signing::debug_certs_in_store(void*) {}
#endif
