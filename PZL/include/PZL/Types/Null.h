#pragma once

#include "PZL/Types/Object.h"

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

	};
}