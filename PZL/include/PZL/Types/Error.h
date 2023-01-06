#pragma once

#include "Types/Object.h"

namespace PZL::Type
{

	struct Error : public Object
	{
	public:
		Error(const char* What);
		~Error();

		virtual const char* ToString() const override;
	public:
		const char* What;
	};
}