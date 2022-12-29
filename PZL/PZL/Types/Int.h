#pragma once

#include "Types/Size.h"
#include "Types/Object.h"

namespace PZL::Type
{

	// Represents both signed and unsigned numbers.
	template<typename T>
	struct BasicInt : public Object<>
	{
	public:
		BasicInt() : Data(0)
		{
			OType = ObjectType::Int;
		}

		BasicInt(const T& Value) : Data(Value)
		{
			OType = ObjectType::Int;
		}

		BasicInt(T&& Value) : Data(Value)
		{
			OType = ObjectType::Int;
		}

		// Returns its current value as a string.
		virtual const char* ToString() const override
		{
			std::string Str = std::to_string(Data);
			char* NStr = (char*)calloc(Str.length(), sizeof(char));
			strcpy(NStr, Str.c_str());
			return NStr;
		}

		template<typename Type>
		inline BasicInt<T>& operator+=(Type A)
		{
			this->Data += A;
			return *this;
		}

		template<typename Type>
		inline BasicInt<T>& operator-=(Type A)
		{
			this->Data -= A;
			return *this;
		}

		template<typename Type>
		inline BasicInt<T>& operator*=(Type A)
		{
			this->Data *= A;
			return *this;
		}

		template<typename Type>
		inline BasicInt<T>& operator/=(Type A)
		{
			this->Data /= A;
			return *this;
		}

		template<typename Type>
		inline BasicInt<T>& operator%=(Type A)
		{
			this->Data %= A;
			return *this;
		}

		inline BasicInt<T>& operator++()
		{ 
			this->Data++;
			return *this;
		}

		inline BasicInt<T> operator++(int)
		{
			BasicInt<T> Tmp = *this;
			++* this;
			return Tmp;
		}

		inline bool operator>(const BasicInt<T>& A)
		{
			return Data > A.Data;
		}

		// Returns the current value as the type specified in the template.
		operator T&()
		{
			return Data;
		}
	public:
		T Data;
	private:
		friend bool operator>(const BasicInt<T>& A, Size B);
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

	template<typename T>
	inline bool operator>(const BasicInt<T>& A, Size B)
	{
		return A.Data > B;
	}
}