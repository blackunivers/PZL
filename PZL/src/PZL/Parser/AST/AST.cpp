#include "PCH.h"
#include "PZL/Parser/AST/AST.h"

#include "PZL/Lexer/Token.h"

namespace PZL::AST
{

	Statement::Statement(Type::Size Line)
	{
		this->Line = Line;
	}

	Statement::~Statement()
	{
	}

	Expression::Expression(Type::Size Line)
	{
		this->Line = Line;
	}

	Expression::~Expression()
	{
	}

	Program::Program(std::vector<Statement*> Statements)
	{
		this->Statements = Statements;
	}

	Program::~Program()
	{
		for (auto statement : Statements)
			delete statement;
	}

	const ASTNodeType Program::Type() const
	{
		return ASTNodeType::Program;
	}

}