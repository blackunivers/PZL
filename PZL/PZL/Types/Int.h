#pragma once

#include "Types/Object.h"

namespace PZL::Type
{

	// Represents both signed and unsigned numbers
	template<typename T>
	struct BasicInt : public Object<const char*>
	{
	public:
		BasicInt() : _Data(0)
		{
			OType = ObjectType::Int;
		}

		BasicInt(const T& Value) : _Data(Value)
		{
			OType = ObjectType::Int;
		}

		BasicInt(T&& Value) : _Data(Value)
		{
			OType = ObjectType::Int;
		}

		// Returns its current value as a string
		virtual const char* ToString() const override
		{
			std::string Str = std::to_string(_Data);
			char* NStr = (char*)calloc(Str.length(), sizeof(char));
			strcpy(NStr, Str.c_str());
			return NStr;
		}

		template<typename Type>
		BasicInt<T>& operator+=(Type A)
		{
			this->_Data += A;
			return *this;
		}

		template<typename Type>
		BasicInt<T>& operator-=(Type A)
		{
			this->_Data -= A;
			return *this;
		}

		template<typename Type>
		BasicInt<T>& operator*=(Type A)
		{
			this->_Data *= A;
			return *this;
		}

		template<typename Type>
		BasicInt<T>& operator/=(Type A)
		{
			this->_Data /= A;
			return *this;
		}

		template<typename Type>
		BasicInt<T>& operator%=(Type A)
		{
			this->_Data %= A;
			return *this;
		}

		inline BasicInt<T>& operator++()
		{ 
			this->_Data++;
			return *this;
		}

		inline BasicInt<T> operator++(int)
		{
			BasicInt<T> Tmp = *this;
			++* this;
			return Tmp;
		}

		// Returns the current value as the type specified in the template
		operator T()
		{
			return _Data;
		}
	private:
		T _Data;
	};

	// basic integer types
	using Int8 = BasicInt<signed char>;
	using UInt8 = BasicInt<unsigned char>;
	using Int16 = BasicInt<signed short>;
	using UInt16 = BasicInt<unsigned short>;
	using Int32 = BasicInt<signed int>;
	using UInt32 = BasicInt<signed int>;
	using Int64 = BasicInt<signed long long>;
	using UInt64 = BasicInt<unsigned long long>;
}