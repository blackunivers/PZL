#pragma once

#include "Types/Size.h"
#include "Types/Object.h"

namespace PZL::Type
{

	// Represents both signed and unsigned numbers.
	template<typename T>
	struct BasicInt : public Object
	{
	public:
		BasicInt() : Data(0)
		{
			Type = ObjectType::Int32;
		}

		BasicInt(const T& Value) : Data(Value)
		{
			Type = ObjectType::Int32;
		}

		BasicInt(T&& Value) : Data(Value)
		{
			Type = ObjectType::Int32;
		}

		// Returns its current value as a string.
		virtual const char* ToString() const override
		{
			std::string Str = std::to_string(Data);
			char* NStr = (char*)calloc(Str.length(), sizeof(char));
			strcpy(NStr, Str.c_str());
			return NStr;
		}
	public:
		T Data;
	};

	// basic integer types.
	using Int8 = BasicInt<signed char>;
	using UInt8 = BasicInt<unsigned char>;
	using Int16 = BasicInt<signed short>;
	using UInt16 = BasicInt<unsigned short>;
	using Int32 = BasicInt<signed int>;
	using UInt32 = BasicInt<signed int>;
	using Int64 = BasicInt<signed long long>;
	using UInt64 = BasicInt<unsigned long long>;

}