#include "PCH.h"
#include "Machine.h"

namespace PZL::System
{

	Machine* Machine::s_Instance = nullptr;

	Machine::Machine()
	{
	}

	Machine::~Machine()
	{
	}

	Machine* Machine::Get()
	{
		if (s_Instance == nullptr)
			s_Instance = new Machine();
		return s_Instance;
	}

}