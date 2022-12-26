#pragma once

#include "Types/Base.h"

#define pznew		new
#define pzdel		delete

void* operator new(PZL::Type::Size Size);
void* operator new[](PZL::Type::Size Size);
void operator delete(void* Block, PZL::Type::Size Size);
void operator delete[](void* Block, PZL::Type::Size Size);

namespace PZL::System
{

	struct Memory
	{
	public:
		static Memory* Get();

	public:
		Type::UInt64 MemoryUsed = 0;
		Type::UInt64 MemoryUsedTotal = 0;
		Type::UInt64 MemoryAllocated = 0;
		Type::UInt64 MemoryFree = 0;
	private:
		static Memory* s_Instance;
	};
}