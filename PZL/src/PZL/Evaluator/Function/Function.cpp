#include "PCH.h"
#include "PZL/Evaluator/Function/Function.h"

#include "PZL/Evaluator/Environment.h"

namespace PZL
{

	Function::Function(ObjectType ReturnType, Type::Bool IsDefined, const char* FunctionName, std::vector<AST::Statement*> Body) : ReturnType(ReturnType), IsDefined(IsDefined), FunctionName(FunctionName), Body(Body)
	{
	}

	Function::~Function()
	{
		for (auto Statement : Body)
			delete Statement;
		for (auto &[Key, Var] : LocalVariables)
			delete Var;
	}

}