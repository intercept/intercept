#include <stddef.h>
#pragma once
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#ifdef __cplusplus
// From: https://stackoverflow.com/questions/496034/most-efficient-replacement-for-isbadreadptr
// Check memory address access
static const DWORD dwForbiddenArea = PAGE_GUARD | PAGE_NOACCESS;
static const DWORD dwReadRights = PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
static const DWORD dwWriteRights = PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;

template<DWORD dwAccessRights>
bool CheckAccess(const void* pAddress, size_t nSize)
{
    if (!pAddress || !nSize)
    {
        return false;
    }

    MEMORY_BASIC_INFORMATION sMBI;
    bool bRet = false;

    UINT_PTR pCurrentAddress = UINT_PTR(pAddress);
    UINT_PTR pEndAdress = pCurrentAddress + (nSize - 1);

    do
    {
        ZeroMemory(&sMBI, sizeof(sMBI));
        VirtualQuery(LPCVOID(pCurrentAddress), &sMBI, sizeof(sMBI));

        bRet = (sMBI.State & MEM_COMMIT) // memory allocated and
            && !(sMBI.Protect & dwForbiddenArea) // access to page allowed and
            && (sMBI.Protect & dwAccessRights); // the required rights

        pCurrentAddress = (UINT_PTR(sMBI.BaseAddress) + sMBI.RegionSize);
    } while (bRet && pCurrentAddress <= pEndAdress);

    return bRet;
}

#define IsBadWritePtr(p,n) (!CheckAccess<dwWriteRights>(p,n))
#define IsBadReadPtr(p,n) (!CheckAccess<dwReadRights>(p,n))
#define IsBadStringPtrW(p,n) (!CheckAccess<dwReadRights>(p,n*2))
#endif /* defined(__cplusplus) */
#else
#define __CUSTOM_ISBADREADPTR
#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif /* defined(__cplusplus) */
    bool IsBadReadPtr(const void *p, size_t size);
#ifdef __cplusplus
}
#endif /* defined(__cplusplus) */
#endif /* windows */

#ifdef __cplusplus
template<typename T>
inline bool IsBadReadPtrTyped(const T *p) {
    return IsBadReadPtr((void *)p, sizeof(T));
}
#endif /* defined(__cplusplus) */
