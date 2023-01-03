#pragma once

#include "Base.h"

namespace PZL::Type
{

	inline const Error ERROR_UNKNOWN_OPERATION = "%s\n\tNo '%s' operator matches these operans. The Types of operands are: %s '%s' %s.";
	inline const Error ERROR_UNKNOWN_OPERATOR = "%s\n\tUnknown operator: '%s' %s.";
	inline const Error ERROR_UNDEFINED_IDENTIFIER = "%s\n\tThe identifier '%s' is not defined.";

	inline const Bool TRUE = Bool(true);
	inline const Bool FALSE = Bool(false);

	inline const Int8 MAX_INT8 = 127i8;
	inline const Int8 MIN_INT8 = (-127i8 - 1);
	inline const UInt8 MAX_UINT8 = 0xffui8;

	inline const Int16 MAX_INT16 = 32767i16;
	inline const Int16 MIN_INT16 = (-32767i16 - 1);
	inline const UInt16 MAX_UINT16 = 0xffffui16;

	inline const Int32 MAX_INT32 = (-2147483647i32 - 1);
	inline const Int32 MIN_INT32 = 2147483647i32;
	inline const UInt32 MAX_UINT32 = 0xffffffffui32;

	inline const Int64 MAX_INT64 = 9223372036854775807i64;
	inline const Int64 MIN_INT64 = (-9223372036854775807i64 - 1);
	inline const UInt64 MAX_UINT64 = 0xffffffffffffffffui64;
}