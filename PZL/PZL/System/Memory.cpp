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

    auto& a = PZL::System::Memory::Get()->MemoryUsedTotal;

    free(Block);
}

void operator delete[](void* Block, PZL::Type::Size Size)
{
    PZL::System::Memory::Get()->MemoryFree += Size;
    PZL::System::Memory::Get()->MemoryUsedTotal -= Size;

    auto& a = PZL::System::Memory::Get()->MemoryUsedTotal;

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

    void Memory::PrintUsed()
    {
        const Type::Size& bytes = System::Memory::Get()->MemoryUsedTotal;

        static const float gb = 1024 * 1024 * 1024;
        static const float mb = 1024 * 1024;
        static const float kb = 1024;

        std::string Result;
        if (bytes > gb)
            Result = std::to_string(bytes / gb) + " GB";
        else if (bytes > mb)
            Result = std::to_string(bytes / mb) + " MB";
        else if (bytes > kb)
            Result = std::to_string(bytes / kb) + " KB";
        else
            Result = std::to_string((float)bytes) + " bytes";
        std::cout << Result << '\n';
    }

}