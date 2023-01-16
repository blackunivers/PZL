#pragma once

#include "PZL/Types/Size.h"

namespace PZL
{

	struct Token;
}

namespace PZL::AST
{

	enum class ASTNodeType
	{
		Program,

		Identifier,

		Integer8,
		UnsignedInteger8,
		Integer16,
		UnsignedInteger16,
		Integer32,
		UnsignedInteger32,
		Integer64,
		UnsignedInteger64,

		Float32,
		Float64,

		Boolean,
		
		Prefix,
		Infix,
		
		Function,
		Call,
		
		If,

		VarStatement,
		ExpressionStatement,
		Block,
		ReturnStatement,
	};

	struct ASTNode
	{
		virtual const ASTNodeType Type() const = 0;
	};

	struct Statement : public ASTNode
	{
	public:
		Statement(Type::Size Line);
		virtual ~Statement();
	public:
		Type::Size Line;
	};

	struct Expression : public ASTNode
	{
	public:
		Expression(Type::Size Line);
		virtual ~Expression();
	public:
		Type::Size Line;
	};

	struct Program : public ASTNode
	{
	public:
		Program(std::vector<Statement*> Statements);
		~Program();

		virtual const ASTNodeType Type() const override;
	public:
		std::vector<Statement*> Statements;
	};

}