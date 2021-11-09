#include <stddef.h>
#pragma once
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
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
