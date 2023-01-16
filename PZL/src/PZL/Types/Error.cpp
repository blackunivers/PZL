#include "PCH.h"
#include "PZL/Types/Error.h"

namespace PZL
{

	Error::Error(const char* What, ErrorType ErrType) : What(What), ErrType(ErrType)
	{
		Type = ObjectType::Error;
	}

	Error::~Error()
	{
	}

}