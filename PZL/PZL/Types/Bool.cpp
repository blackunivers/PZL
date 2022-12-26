#include "PCH.h"
#include "Bool.h"

namespace PZL::Type
{

	Bool::Bool() : _Data(false)
	{
	}

	Bool::Bool(const bool& Value) : _Data(Value)
	{
	}

	Bool::Bool(bool&& Value) : _Data(Value)
	{
	}

	const char* Bool::ToString() const
	{
		return _Data ? "true" : "false";
	}

	Bool::operator bool()
	{
		return _Data;
	}
}