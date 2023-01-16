#pragma once

#include "PZL/Parser/AST/AST.h"
#include "PZL/Types/Base.h"

namespace PZL
{

	struct Environment;

	class Function
	{
	public:
		Function(ObjectType ReturnType, Type::Bool IsDefined, const char* FunctionName, std::vector<AST::Statement*> Body);
		virtual ~Function();

		ObjectType ReturnType;
		Type::Bool IsDefined;
		const char* FunctionName;
		std::vector<AST::Statement*> Body;
		std::unordered_map<std::string, Object*> LocalVariables;
	};

}