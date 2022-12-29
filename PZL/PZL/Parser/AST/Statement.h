#pragma once

#include "Parser/AST/AST.h"

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
		VarStatement(Token* TK, TokenType Type, Identifier* ID = nullptr, Expression* Value = nullptr);
		~VarStatement();

		virtual const char* ToString() const override;
		virtual const ASTNodeType Type() const override;
	public:
		TokenType VarType;
		Identifier* ID;
		Expression* Value;
	};

	struct ExpressionStatement : public Statement
	{
	public:
		ExpressionStatement(Token* TK, Expression* Value = nullptr);
		~ExpressionStatement();

		virtual const char* ToString() const override;
		virtual const ASTNodeType Type() const override;
	public:
		Expression* Value;
	};
}