#include "PCH.h"
#include "Bool.h"

namespace PZL::Type
{

	Bool::Bool() : Data(false)
	{
		Type = ObjectType::Bool;
	}

	Bool::Bool(const bool& Value) : Data(Value)
	{
		Type = ObjectType::Bool;
		this->Data = Value;
	}

	Bool::Bool(bool&& Value) : Data(Value)
	{
		Type = ObjectType::Bool;
		this->Data = Value;
	}

	const char* Bool::ToString() const
	{
		return Data ? "true" : "false";
	}

}