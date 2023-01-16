#pragma once

#include "PZL/Types/Object.h"

namespace PZL
{
	class Var
	{
	public:
		Var(const char* ID, Object* Value, ObjectType VarType);
		~Var();
	public:
		const char* ID;
		Object* Value;
		ObjectType VarType;
	};
}