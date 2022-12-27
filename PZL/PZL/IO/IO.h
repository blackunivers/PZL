#pragma once

#include "Types/Size.h"
#include "Types/Bool.h"

namespace PZL::IO
{

	struct File
	{
		const char* Data;
		const Type::Size Len;
		const Type::Bool IsValid;
	};

	File* ReadFile(const char* Path);
}