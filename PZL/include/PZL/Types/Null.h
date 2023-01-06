#pragma once

#include "Types/Object.h"

namespace PZL::Type
{

	struct Null : public Object
	{
		Null()
		{
			Type = ObjectType::Null;
		}

		~Null()
		{

		}

		inline virtual const char* ToString() const override { return "Null"; }
	};
}