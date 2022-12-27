#include "PCH.h"
#include "Str.h"

namespace PZL::Type
{
	Char::Char()
	{
		OType = ObjectType::Char;
	}

	Char::Char(const char& Value)
	{
		OType = ObjectType::Char;
		_Data = Value;
	}

	Char::Char(char&& Value)
	{
		OType = ObjectType::Char;
		_Data = Value;
	}

	Char::Char(UInt8 Value)
	{
		OType = ObjectType::Char;
		_Data = Value;
	}

	const char* Char::ToString() const
	{
		return &_Data;
	}

	Char::operator char& ()
	{
		return _Data;
	}

}