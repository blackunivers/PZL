#pragma once

#include "PZL/Parser/AST/AST.h"

namespace PZL
{

	enum class TokenType;
}


namespace PZL::AST
{

	struct Identifier;

	struct VarStatement : public Statement
	{
	public:
		VarStatement(Type::Size Line, TokenType Type, Identifier* ID = nullptr, Expression* Value = nullptr);
		~VarStatement();

		virtual const ASTNodeType Type() const override;
	public:
		TokenType VarType;
		Identifier* ID;
		Expression* Value;
	};

	struct ExpressionStatement : public Statement
	{
	public:
		ExpressionStatement(Type::Size Line, Expression* Value = nullptr);
		~ExpressionStatement();

		virtual const ASTNodeType Type() const override;
	public:
		Expression* Value;
	};

	struct Block : public Statement
	{
	public:
		Block(Type::Size Line, std::vector<Statement*> Statements = {});
		~Block();

		virtual const ASTNodeType Type() const override;
	public:
		std::vector<Statement*> Statements;
	};

	struct ReturnStatement : public Statement
	{
	public:
		ReturnStatement(Type::Size Line, Expression* Value = nullptr);
		~ReturnStatement();

		virtual const ASTNodeType Type() const override;
	public:
		Expression* Value;
	};

}