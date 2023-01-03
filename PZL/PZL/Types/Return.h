#pragma once

#include "Types/Object.h"

namespace PZL::Type
{

	struct Return : public Object
	{
	public:
		Return(Object* Value);
		~Return();

		inline virtual const char* ToString() const override;
	public:
		Object* Value;
	};
}