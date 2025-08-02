#include "Compat.h"
#include <struct.hpp>
#include <name.hpp>

namespace Compat
{
	tid_t add_struc(uval_t idx, const char* name, bool is_union)
	{
		return ::add_struc(idx, name, is_union);
	}

	struc_error_t add_struc_member(tid_t sid, const char* fieldname, ea_t offset, flags_t flag,
								   const opinfo_t* mt, asize_t nbytes)
	{
		return static_cast<struc_error_t>(::add_struc_member(get_struc(sid), fieldname, offset, flag, mt, nbytes));
	}

	int get_member_flag(tid_t sid, asize_t offset)
	{
		struc_t* s = get_struc(sid);
		if (!s) return -1;
		member_t* m = get_member(s, offset);
		return m ? m->flag : -1;
	}

	tid_t get_member_id(tid_t sid, asize_t offset)
	{
		struc_t* s = get_struc(sid);
		if (!s) return BADADDR;
		member_t* m = get_member(s, offset);
		return m ? m->id : BADADDR;
	}

	qstring get_member_name(tid_t sid, asize_t offset)
	{
		qstring result;
		struc_t* s = get_struc(sid);
		if (!s) return result;
		member_t* m = get_member(s, offset);
		if (m) {
			get_member_name(&result, m->id);
		}
		return result;
	}

	asize_t get_member_size(tid_t sid, asize_t offset)
	{
		struc_t* s = get_struc(sid);
		if (!s) return 0;
		member_t* m = get_member(s, offset);
		return m ? get_member_size(m) : 0;
	}

	bool get_member_tinfo(tinfo_t* tif, tid_t sid, asize_t offset)
	{
		struc_t* s = get_struc(sid);
		if (!s) return false;
		member_t* m = get_member(s, offset);
		return m ? ::get_member_tinfo(tif, m) : false;
	}

	ea_t get_struc_first_offset(tid_t id)
	{
		struc_t* s = get_struc(id);
		return s ? get_struc_first_offset(s) : BADADDR;
	}

	tid_t get_struc_id(const char* name)
	{
		return ::get_struc_id(name);
	}

	qstring get_struc_name(tid_t id)
	{
		qstring result;
		get_struc_name(&result, id);
		return result;
	}

	ea_t get_struc_next_offset(tid_t id, ea_t offset)
	{
		struc_t* s = get_struc(id);
		return s ? get_struc_next_offset(s, offset) : BADADDR;
	}

	bool set_member_name(tid_t sid, ea_t offset, const char* name)
	{
		struc_t* s = get_struc(sid);
		if (!s) return false;
		member_t* m = get_member(s, offset);
		return m ? ::set_member_name(s, offset, name) : false;
	}

	bool set_member_tinfo(tid_t sid, uval_t memoff, const tinfo_t& tif, int flags)
	{
		struc_t* s = get_struc(sid);
		if (!s) return false;
		member_t* m = get_member(s, memoff);
		return m ? ::set_member_tinfo(s, m, memoff, tif, flags) : false;
	}

	bool set_struc_cmt(tid_t id, const char* cmt, bool repeatable)
	{
		return ::set_struc_cmt(id, cmt, repeatable);
	}
}
