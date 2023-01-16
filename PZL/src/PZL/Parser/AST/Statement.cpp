#include "PCH.h"
#include "PZL/Parser/AST/Statement.h"

#include "PZL/Lexer/Token.h"
#include "PZL/Parser/AST/Expression.h"

namespace PZL::AST
{

	VarStatement::VarStatement(Type::Size Line, TokenType Type, Identifier* ID, Expression* Value) : Statement(Line)
	{
		this->VarType = Type;
		this->ID = ID;
		this->Value = Value;
	}

	VarStatement::~VarStatement()
	{
		delete ID;
		delete Value;
	}

	const ASTNodeType VarStatement::Type() const
	{
		return ASTNodeType::VarStatement;
	}

	ExpressionStatement::ExpressionStatement(Type::Size Line, Expression* Value) : Statement(Line)
	{
		this->Value = Value;
	}

	ExpressionStatement::~ExpressionStatement()
	{
		delete Value;
	}

	const ASTNodeType ExpressionStatement::Type() const
	{
		return ASTNodeType::ExpressionStatement;
	}

	Block::Block(Type::Size Line, std::vector<Statement*> Statements) : Statement(Line)
	{
		this->Statements = Statements;
	}

	Block::~Block()
	{
		for (auto statement : Statements)
			delete statement;
	}

	const ASTNodeType Block::Type() const
	{
		return ASTNodeType::Block;
	}

	ReturnStatement::ReturnStatement(Type::Size Line, Expression* Value) : Statement(Line)
	{
		this->Value = Value;
	}

	ReturnStatement::~ReturnStatement()
	{
		delete Value;
	}

	const ASTNodeType ReturnStatement::Type() const
	{
		return ASTNodeType::ReturnStatement;
	}

}