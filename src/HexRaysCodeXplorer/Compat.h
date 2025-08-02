// compatibility functions needed for IDA 9.0 support. mostly ported from IDAPython's idc module
#pragma once

// Include 32-bit compatibility fixes for IDA SDK 7.7
#include "IDACompat32.h"

#include <lines.hpp>
#include <kernwin.hpp>
#include <nalt.hpp>
#include <struct.hpp>
#include <typeinf.hpp>

// Define flags64_t for older IDA versions if not defined
#ifndef __EA64__
typedef flags_t flags64_t;
#else
// In IDA 7.7 and later, flags64_t should be available, but we'll use flags_t as fallback
#if !defined(flags64_t)
typedef flags_t flags64_t;
#endif
#endif

// Platform-specific type definitions for 32-bit vs 64-bit builds
#ifdef _WIN64
    // 64-bit build
    #define IDA_PLATFORM_SUFFIX "64"
    #define IDA_LIB_SUFFIX "_64"
#else
    // 32-bit build  
    #define IDA_PLATFORM_SUFFIX ""
    #define IDA_LIB_SUFFIX "_32"
#endif

namespace Compat
{
	tid_t add_struc(uval_t idx, const char* name, bool is_union = false);
	struc_error_t add_struc_member(tid_t sid, const char* fieldname, ea_t offset, flags_t flag,
								   const opinfo_t* mt, asize_t nbytes);
	int get_member_flag(tid_t sid, asize_t offset);
	tid_t get_member_id(tid_t sid, asize_t offset);
	qstring get_member_name(tid_t sid, asize_t offset);
	asize_t get_member_size(tid_t sid, asize_t offset);
	bool get_member_tinfo(tinfo_t* tif, tid_t sid, asize_t offset);
	ea_t get_struc_first_offset(tid_t id);
	tid_t get_struc_id(const char* name);
	qstring get_struc_name(tid_t id);
	ea_t get_struc_next_offset(tid_t id, ea_t offset);
	bool set_member_name(tid_t sid, ea_t offset, const char* name);
	bool set_member_tinfo(tid_t sid, uval_t memoff, const tinfo_t& tif, int flags);
	bool set_struc_cmt(tid_t id, const char* cmt, bool repeatable);

	/// \defgroup SET_MEMTI_ Set member tinfo flags
	/// Passed as 'flags' parameter to set_member_tinfo()
	//@{
	#define SET_MEMTI_MAY_DESTROY 0x0001 ///< may destroy other members
	#define SET_MEMTI_COMPATIBLE  0x0002 ///< new type must be compatible with the old
	#define SET_MEMTI_FUNCARG     0x0004 ///< mptr is function argument (cannot create arrays)
	#define SET_MEMTI_BYTIL       0x0008 ///< new type was created by the type subsystem
	#define SET_MEMTI_USERTI      0x0010 ///< user-specified type
	//@}
}
