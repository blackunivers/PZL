#include "PCH.h"
#include "IO.h"

#include "System/Machine.h"

namespace PZL::IO
{

	File* ReadFile(const char* Path)
	{
		std::ifstream File(Path);

		if(!File.is_open())
		{
			return nullptr;
		}
		
		
		return nullptr;
	}
}