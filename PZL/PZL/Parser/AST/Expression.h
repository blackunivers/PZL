#pragma once

#include "Parser/AST/AST.h"
#include "Types/Bool.h"
#include "Types/Int.h"
#include "Lexer/Token.h"

namespace PZL::AST
{
	struct VarStatement;
	struct Block;

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

	struct Function : public Expression
	{
	public:
		Function(Token* TK, Token* FunctionType = nullptr, Identifier* FunctionName = nullptr, std::vector<VarStatement*> Parameters = {}, Block* Body = nullptr);
		~Function();

		virtual const char* ToString() const override;
		virtual const ASTNodeType Type() const override;
	public:
		Token* FunctionType;
		Identifier* FunctionName;
		std::vector<VarStatement*> Parameters;
		Block* Body;
		Type::Bool IsDefined;
	};

	struct Call : public Expression
	{
	public:
		Call(Token* TK, Expression* Fn, std::vector<Expression*> Arguments = {});
		~Call();

		virtual const char* ToString() const override;
		virtual const ASTNodeType Type() const override;
	public:
		Expression* Fn;
		std::vector<Expression*> Arguments;
	};

}