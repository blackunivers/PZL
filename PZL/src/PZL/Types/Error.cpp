#include "PCH.h"
#include "Error.h"

namespace PZL::Type
{

    Error::Error(const char* What)
    {
        Type = ObjectType::Error;
        this->What = What;
    }

    Error::~Error()
    {
    }

    const char* Error::ToString() const
    {
        return What;
    }
}
