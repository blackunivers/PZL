#pragma once

#include "PZL/Types/Object.h"

namespace PZL::Type
{

	template<typename T, ObjectType ObjType>
	struct BasicFloat : public Object
	{
	public:
		using TypeFloat = T;
	public:
		BasicFloat() : Data(0)
		{
			Type = ObjType;
		}

		BasicFloat(const T& Value) : Data(Value)
		{
			Type = ObjType;
		}

		BasicFloat(T&& Value) : Data(Value)
		{
			Type = ObjType;
		}

		explicit BasicFloat(BasicFloat<T, ObjType>* B) : Data((T)B->Data)
		{
			Type = B->Type;
		}

		virtual Object* operator+(Object* B) override { return new BasicFloat<T, ObjType>(this->Data + ((BasicInt<T, ObjType>*)B)->Data); }
		virtual Object* operator-(Object* B) override { return new BasicFloat<T, ObjType>(this->Data - ((BasicInt<T, ObjType>*)B)->Data); }
		virtual Object* operator*(Object* B) override { return new BasicFloat<T, ObjType>(this->Data * ((BasicInt<T, ObjType>*)B)->Data); }
		virtual Object* operator/(Object* B) override { return new BasicFloat<T, ObjType>(this->Data / ((BasicInt<T, ObjType>*)B)->Data); }
		virtual bool operator==(Object* B) override { return new BasicFloat<T, ObjType>(this->Data == ((BasicInt<T, ObjType>*)B)->Data); }
		virtual bool operator!=(Object* B) override { return new BasicFloat<T, ObjType>(this->Data != ((BasicInt<T, ObjType>*)B)->Data); }

	public:
		T Data;
	};

	using Float32 = BasicFloat<float, ObjectType::Float32>;
	using Float64 = BasicFloat<double, ObjectType::Float64>;
}