#pragma once

#include "PZL/Types/Object.h"

namespace PZL::Type
{

	// Represents both signed and unsigned numbers.
	template<typename T, ObjectType ObjType>
	struct BasicInt : public Object
	{
	public:
		using TypeInt = T;
	public:
		BasicInt() : Data(0)
		{
			Type = ObjType;
		}

		BasicInt(const T& Value) : Data(Value)
		{
			Type = ObjType;
		}

		BasicInt(T&& Value) : Data(Value)
		{
			Type = ObjType;
		}

		explicit BasicInt(BasicInt<T, ObjType>* B) : Data((T)B->Data)
		{
			Type = ObjType;
		}

		template<typename T, ObjectType ObjType>
		explicit BasicInt(BasicInt<T, ObjType>* B) : Data((T)B->Data)
		{
			Type = ObjType;
		}

		virtual Object* operator+(Object* B) override { return new BasicInt<T, ObjType>(this->Data + ((BasicInt<T, ObjType>*)B)->Data); }
		virtual Object* operator-(Object* B) override { return new BasicInt<T, ObjType>(this->Data - ((BasicInt<T, ObjType>*)B)->Data); }
		virtual Object* operator*(Object* B) override { return new BasicInt<T, ObjType>(this->Data * ((BasicInt<T, ObjType>*)B)->Data); }
		virtual Object* operator/(Object* B) override { return new BasicInt<T, ObjType>(this->Data / ((BasicInt<T, ObjType>*)B)->Data); }
		virtual bool operator==(Object* B) override { return new BasicInt<T, ObjType>(this->Data == ((BasicInt<T, ObjType>*)B)->Data); }
		virtual bool operator!=(Object* B) override { return new BasicInt<T, ObjType>(this->Data != ((BasicInt<T, ObjType>*)B)->Data); }

		inline operator T& () { return Data; }

	public:
		T Data;
	};

	// basic integer types.
	using Int8 = BasicInt<signed char, ObjectType::Int8>;
	using UInt8 = BasicInt<unsigned char, ObjectType::UInt8>;
	using Int16 = BasicInt<signed short, ObjectType::Int16>;
	using UInt16 = BasicInt<unsigned short, ObjectType::UInt16>;
	using Int32 = BasicInt<signed int, ObjectType::Int32>;
	using UInt32 = BasicInt<signed int, ObjectType::UInt32>;
	using Int64 = BasicInt<signed long long, ObjectType::Int64>;
	using UInt64 = BasicInt<unsigned long long, ObjectType::UInt64>;

}