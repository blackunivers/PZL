#pragma once

#include "Types/Object.h"

namespace PZL::Type
{
	 // Represents Booleans.
	struct Bool : public Object<>
	{
	public:
		Bool();
		Bool(const bool& Value);
		Bool(bool&& Value);

		// Returns its current value as a string.
		virtual const char* ToString() const override;

		// So that it can be used in logical operations.
		operator bool&();
	private:
		bool _Data;
	};
}