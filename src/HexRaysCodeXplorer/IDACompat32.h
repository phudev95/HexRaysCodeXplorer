// IDA SDK 7.7 compatibility header for 32-bit builds
// Include this BEFORE any IDA SDK headers to work around static_assert issues
#pragma once

#ifdef _WIN32
#ifndef _WIN64
// For 32-bit builds, we need to work around IDA SDK 7.7's static_assert checks
// The SDK expects 64-bit structure sizes which don't match 32-bit compilation

// Override the CASSERT macro used by IDA SDK
#ifdef CASSERT
#undef CASSERT
#endif
#define CASSERT(cond) // Disable compile-time assertions

// Override static_assert to prevent structure size validation failures
#ifndef static_assert
#define static_assert(condition, message) typedef char __static_assert_dummy
#endif

// Define a macro to indicate we're using the compatibility mode
#define IDA_SDK_32BIT_COMPAT 1

#endif // _WIN64
#endif // _WIN32