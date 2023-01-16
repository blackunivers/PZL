#pragma once

#include "PZL/Parser/AST/AST.h"
#include "PZL/Types/Bool.h"
#include "PZL/Types/Int.h"
#include "PZL/Lexer/Token.h"

namespace PZL::AST
{
	struct VarStatement;
	struct Block;

	struct Identifier : public Expression
	{
	public:
		Identifier(Type::Size Line, const char* ID);
		~Identifier();

		virtual const ASTNodeType Type() const override;
	public:
		const char* ID;
	};

	template<typename TypeNumber, ASTNodeType NodeType>
	struct BasicNumberExpression : public Expression
	{
	public:
		BasicNumberExpression(Type::Size Line, TypeNumber Value = 0) : Expression(Line) { this->Value = Value; }
		~BasicNumberExpression() {}

		inline virtual const ASTNodeType Type() const override { return NodeType; };
	public:
		TypeNumber Value;
	};

	using Integer8 = BasicNumberExpression<Type::Int8, ASTNodeType::Integer8>;
	using UnsignedInteger8 = BasicNumberExpression<Type::UInt8, ASTNodeType::UnsignedInteger8>;
	using Integer16 = BasicNumberExpression<Type::Int16, ASTNodeType::Integer16>;
	using UnsignedInteger16 = BasicNumberExpression<Type::UInt16, ASTNodeType::UnsignedInteger16>;
	using Integer32 = BasicNumberExpression<Type::Int32, ASTNodeType::Integer32>;
	using UnsignedInteger32 = BasicNumberExpression<Type::UInt32, ASTNodeType::UnsignedInteger32>;
	using Integer64 = BasicNumberExpression<Type::Int64, ASTNodeType::Integer64>;
	using UnsignedInteger64 = BasicNumberExpression<Type::UInt64, ASTNodeType::UnsignedInteger64>;

	using Float32 = BasicNumberExpression<Type::Float32, ASTNodeType::Float32>;
	using Float64 = BasicNumberExpression<Type::Float64, ASTNodeType::Float64>;

	struct Boolean : public Expression
	{
	public:
		Boolean(Type::Size Line, Type::Bool value = false);
		~Boolean();

		virtual const ASTNodeType Type() const override;
	public:
		Type::Bool Value;
	};

	struct Prefix : public Expression
	{
	public:
		Prefix(Type::Size Line, const char* Operator, Expression* Right = nullptr);
		~Prefix();

		virtual const ASTNodeType Type() const override;
	public:
		const char* Operator;
		Expression* Right;
	};

	struct Infix : public Expression
	{
	public:
		Infix(Type::Size Line, Expression* Left, const char* Operator, Expression* Right = nullptr);
		~Infix();

		virtual const ASTNodeType Type() const override;
	public:
		const char* Operator;
		Expression* Left;
		Expression* Right;
	};

	struct Function : public Expression
	{
	public:
		Function(Type::Size Line, TokenType FunctionType = TokenType::NONE, Identifier* FunctionName = nullptr, std::vector<VarStatement*> Parameters = {}, Block* Body = nullptr);
		~Function();

		virtual const ASTNodeType Type() const override;
	public:
		TokenType FunctionType;
		Identifier* FunctionName;
		std::vector<VarStatement*> Parameters;
		Block* Body;
		Type::Bool IsDefined;
	};

	struct Call : public Expression
	{
	public:
		Call(Type::Size Line, Expression* Fn, std::vector<Expression*> Arguments = {});
		~Call();

		virtual const ASTNodeType Type() const override;
	public:
		Expression* Fn;
		std::vector<Expression*> Arguments;
	};

	struct If : public Expression
	{
	public:
		If(Type::Size Line, Expression* Condition = nullptr, Block* IfBlock = nullptr, Block* ElseBlock = nullptr);
		~If();

		virtual const ASTNodeType Type() const override;
	public:
		Expression* Condition;
		Block* IfBlock;
		Block* ElseBlock;
	};

}