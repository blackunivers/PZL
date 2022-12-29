#pragma once

#include "Parser/AST/AST.h"
#include "Types/Bool.h"
#include "Types/Int.h"

namespace PZL::AST
{

	struct Identifier : public Expression
	{
	public:
		Identifier(Token* TK, const char* ID);
		~Identifier();

		virtual const char* ToString() const override;
		virtual const ASTNodeType Type() const override;
	public:
		const char* ID;
	};

	struct Integer : public Expression
	{
	public:
		Integer(Token* TK, Type::Int32 value = 0);
		~Integer();

		virtual const char* ToString() const override;

		virtual const ASTNodeType Type() const override;
	public:
		Type::Int32 Value;
	};

	struct Boolean : public Expression
	{
	public:
		Boolean(Token* TK, Type::Bool value = false);
		~Boolean();

		virtual const char* ToString() const override;

		virtual const ASTNodeType Type() const override;
	public:
		Type::Bool Value;
	};

	struct Prefix : public Expression
	{
	public:
		Prefix(Token* TK, const char* Operator, Expression* Right = nullptr);
		~Prefix();

		virtual const char* ToString() const override;
		virtual const ASTNodeType Type() const override;
	public:
		const char* Operator;
		Expression* Right;
	};

	struct Infix : public Expression
	{
	public:
		Infix(Token* TK, Expression* Left, const char* Operator, Expression* Right = nullptr);
		~Infix();

		virtual const char* ToString() const override;
		virtual const ASTNodeType Type() const override;
	public:
		const char* Operator;
		Expression* Left;
		Expression* Right;
	};

}