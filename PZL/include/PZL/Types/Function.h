#pragma once

#include "Types/Object.h"

namespace PZL::AST
{

	struct VarStatement;
	struct Block;
}

namespace PZL::Evaluator
{

	struct Environment;
}

namespace PZL::Type
{

	struct Function : public Object
	{
	public:
		Function(std::vector<AST::VarStatement*> Parameters, AST::Block* Body, Evaluator::Environment* Env);
		~Function();

		virtual const char* ToString() const override;
	public:
		std::vector<AST::VarStatement*> Parameters;
		AST::Block* Body;
		Evaluator::Environment* Env;
	};
}