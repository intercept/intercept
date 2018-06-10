#pragma once

// This is a warning normally for returning references to local/stack allocated variables
// It is so dangerous though that we need to force it as a warning because it can break
// everything.
#pragma warning( error : 4172 )

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <memory>
#include <cmath>
#include <cstdint>
#include <streambuf>
#include <istream>
#include <variant>
#include <optional>

#ifdef _DEBUG
#define ZERO_OUTPUT()    { memset(output, 0x00, outputSize); }
#define EXTENSION_RETURN() {output[outputSize-1] = 0x00; } return;
#else
#define ZERO_OUTPUT()
#define EXTENSION_RETURN() return;
#endif

#ifdef _DEBUG
#define INTERCEPT_ASSERT assert()
#else
#define INTERCEPT_ASSERT intercept::runtime_assert()
#endif

#ifdef __GNUC__
#define CDECL __attribute__ ((__cdecl__))
#else
#undef CDECL
#define CDECL __cdecl
#endif

#ifdef __GNUC__
#define DLLEXPORT __attribute__((visibility("default")))
#else
#define DLLEXPORT __declspec(dllexport)
#endif
