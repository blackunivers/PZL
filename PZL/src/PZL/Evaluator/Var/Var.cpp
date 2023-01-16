#include "PCH.h"
#include "PZL/Evaluator/Var/Var.h"

namespace PZL
{
	
	Var::Var(const char* ID, Object* Value, ObjectType VarType) : ID(ID), Value(Value), VarType(VarType)
	{
	}

	Var::~Var()
	{
		delete Value;
	}

}