#pragma once

#include "PZL/Types/Size.h"
#include "PZL/Types/Bool.h"

namespace PZL::IO
{

	// Represents a text file.
	struct File
	{
		char* Data;
		const Type::Size Len;
		Type::Bool IsValid;
	};
	
	// Gets the contents of a file and returns a file pointer.
	File* ReadFile(const char* Path);
}