#include "PCH.h"
#include "Return.h"

namespace PZL::Type
{

	Return::Return(Object* Value)
	{
		Type = ObjectType::Return;
		this->Value = Value;
	}

	Return::~Return()
	{
		if(Value != nullptr)
			delete Value;
	}

	inline const char* Return::ToString() const
	{
		return Value->ToString();
	}

}