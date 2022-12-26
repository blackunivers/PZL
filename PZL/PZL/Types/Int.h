#pragma once

#include "Types/Object.h"

#define PZL_INT_OPERATOR_OVERLOADING(Op, Type) inline BasicInt<T>& operator ##Op(Type A) { this->_Data ##Op A; return *this; }
#define PZL_INT_OPERATOR_OVERLOADING_NO_RIGHT(Op) inline BasicInt<T>& operator ##Op() { this->_Data ##Op; return *this; }

namespace PZL::Type
{

	// Represents both signed and unsigned numbers
	template<typename T>
	struct BasicInt : public Object<const char*>
	{
	public:
		using value_type = T;
	public:

		BasicInt() : _Data(0)
		{
		}

		BasicInt(const T& Value) : _Data(Value)
		{
		}

		BasicInt(T&& Value) : _Data(Value)
		{
		}

		// Returns its current value as a string
		virtual const char* ToString() const override
		{
			std::string Str = std::to_string(_Data);
			char* NStr = (char*)calloc(Str.length(), sizeof(char));
			strcpy(NStr, Str.c_str());
			return NStr;
		}

		inline BasicInt<T> operator+(BasicInt<T>& A)
		{
			BasicInt<T> B(this->_Data + A._Data);
			return B;
		}

		inline BasicInt<T> operator+(int32_t A)
		{
			BasicInt<T> B(this->_Data + A);
			return B;
		}

		inline BasicInt<T> operator+(uint32_t A)
		{
			BasicInt<T> B(this->_Data + A);
			return B;
		}

		inline BasicInt<T> operator+(int64_t A)
		{
			BasicInt<T> B(this->_Data + A);
			return B;
		}

		inline BasicInt<T> operator+(uint64_t A)
		{
			BasicInt<T> B(this->_Data + A);
			return B;
		}

		inline BasicInt<T>& operator+=(BasicInt<T>& A)
		{
			this->_Data += A._Data;
			return *this;
		}

		PZL_INT_OPERATOR_OVERLOADING(-=, uint8_t);
		PZL_INT_OPERATOR_OVERLOADING(-=, int8_t);
		PZL_INT_OPERATOR_OVERLOADING(-=, int32_t);
		PZL_INT_OPERATOR_OVERLOADING(-=, uint32_t);
		PZL_INT_OPERATOR_OVERLOADING(-=, int64_t);
		PZL_INT_OPERATOR_OVERLOADING(-=, uint64_t);

		PZL_INT_OPERATOR_OVERLOADING(+=, uint8_t);
		PZL_INT_OPERATOR_OVERLOADING(+=, int8_t);
		PZL_INT_OPERATOR_OVERLOADING(+=, int32_t);
		PZL_INT_OPERATOR_OVERLOADING(+=, uint32_t);
		PZL_INT_OPERATOR_OVERLOADING(+=, int64_t);
		PZL_INT_OPERATOR_OVERLOADING(+=, uint64_t);


		PZL_INT_OPERATOR_OVERLOADING_NO_RIGHT(++);

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