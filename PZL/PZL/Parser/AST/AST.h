#pragma once

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
		Integer,
		Boolean,
		Prefix,
		Infix,

		VarStatement,
		ExpressionStatement,
	};

	struct ASTNode
	{
		virtual const char* ToString() const = 0;
		virtual const ASTNodeType Type() const = 0;
	};

	struct Statement : public ASTNode
	{
	public:
		Statement(Token* TK);
		virtual ~Statement();
	public:
		Token* TK;
	};

	struct Expression : public ASTNode
	{
	public:
		Expression(Token* TK);
		virtual ~Expression();
	public:
		Token* TK;
	};

	struct Program : public ASTNode
	{
	public:
		Program(std::vector<Statement*> Statements);
		~Program();

		virtual const char* ToString() const override;
		virtual const ASTNodeType Type() const override;
	public:
		std::vector<Statement*> Statements;
	};

}