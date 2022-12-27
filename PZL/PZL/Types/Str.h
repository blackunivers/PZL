#pragma once

#include "Types/Size.h"
#include "Types/Int.h"

namespace PZL::Type
{
	// Represents characters.
	struct Char : public Object<>
	{
	public:
		Char();
		Char(const char& Value);
		Char(char&& Value);
		Char(UInt8 Value);

		// Returns its current value as a string.
		virtual const char* ToString() const override;

		char& operator=(const char& A)
		{
			_Data = A;
			return _Data;
		}

		char& operator=(char&& A)
		{
			_Data = A;
			return _Data;
		}

		// So that it can be used in operations with characters.
		operator char& ();
	private:
		char _Data;
	};
}