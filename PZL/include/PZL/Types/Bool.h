#pragma once

#include "PZL/Types/Object.h"

namespace PZL::Type
{
	 // Represents Booleans.
	struct Bool : public Object
	{
	public:
		Bool() : Data(false)
		{
			Type = ObjectType::Bool;
		}

		Bool(const bool& Value) : Data(Value)
		{
			Type = ObjectType::Bool;
		}

		Bool(bool&& Value) : Data(Value)
		{
			Type = ObjectType::Bool;
		}

		virtual Object* operator+(Object* B) override { return new Bool(this->Data + ((Bool*)B)->Data); }
		virtual Object* operator-(Object* B) override { return new Bool(this->Data - ((Bool*)B)->Data); }
		virtual Object* operator*(Object* B) override { return new Bool(this->Data * ((Bool*)B)->Data); }
		virtual bool operator==(Object* B) override { return new Bool(this->Data == ((Bool*)B)->Data); }
		virtual bool operator!=(Object* B) override { return new Bool(this->Data != ((Bool*)B)->Data); }
		
		operator bool& () { return Data; }

	public:
		bool Data;
	};
}