#include "PCH.h"
#include "Memory.h"

void* operator new(PZL::Type::Size Size)
{
    PZL::System::Memory::Get()->MemoryUsedTotal += Size;
    PZL::System::Memory::Get()->MemoryUsed += Size;
    PZL::System::Memory::Get()->MemoryAllocated++;

    return malloc(Size);
}

void* operator new[](PZL::Type::Size Size)
{
    PZL::System::Memory::Get()->MemoryUsedTotal += Size;
    PZL::System::Memory::Get()->MemoryUsed += Size;
    PZL::System::Memory::Get()->MemoryAllocated++;

    return malloc(Size);
}

void operator delete(void* Block, PZL::Type::Size Size)
{
    PZL::System::Memory::Get()->MemoryFree += Size;
    PZL::System::Memory::Get()->MemoryUsedTotal -= Size;

    free(Block);
}

void operator delete[](void* Block, PZL::Type::Size Size)
{
    PZL::System::Memory::Get()->MemoryFree += Size;
    PZL::System::Memory::Get()->MemoryUsedTotal -= Size;

    free(Block);
}

namespace PZL::System
{

    Memory* Memory::s_Instance = nullptr;

    Memory* Memory::Get()
    {
        if (s_Instance == nullptr)
        {
            s_Instance = (Memory*)malloc(sizeof(Memory));
            s_Instance = new(s_Instance) Memory();
        }
        return s_Instance;
    }
}