#pragma once

#include "PZL/Parser/AST/Expression.h"
#include "PZL/Types/Object.h"
#include "PZL/Types/Error.h"

namespace PZL
{

	struct Environment;
	struct Error;
	class Function;
	class Var;
}

namespace PZL
{

	class Evaluator
	{
	public:
		Evaluator();
		~Evaluator();

	public:
		Object* EvaluateProgram(AST::Program* Program);
		Object* EvaluateStatement(AST::Statement* Statement);
		Object* EvaluateExpression(AST::Expression* Expression);

		Object* EvaluateIntegerOperation(Object* Right, const char* Operator, Object* Left);
		Object* EvaluateFloatOperation(Object* Right, const char* Operator, Object* Left);

		Object* EvaluateInfix(Object* Right, const char* Operator, Object* Left);
		Object* EvaluateID(const char* ID);
		Object* EvaluateBlock(std::vector<AST::Statement*> Statements);

		Object* ExecuteFunction(const char* FunctionName);

		void ShowErrorAndExit(Object* E);

		Var* GetVarByName(const char* ID);
		Function* GetFunctionByName(const char* ID);

	public:
		Type::Size CurrentLine;

		enum class Context
		{
			PreEvaluation = 0,
			FunctionExpression,

			AssingExpression,
			OperationExpression,
			CallExpression,
			IfExpression,

			VariableStatement,
			ReturnStatement,

			ReturnStatementID,
		};
	   
		Type::StaticArray< Context, 3> CurrentContext = { Context::PreEvaluation, Context::OperationExpression};
		Environment* GlobalEnvironment;
	};

}