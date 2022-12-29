#include "PCH.h"
#include "Statement.h"

#include "Lexer/Token.h"
#include "Parser/AST/Expression.h"

namespace PZL::AST
{

	VarStatement::VarStatement(Token* TK, TokenType Type, Identifier* ID, Expression* Value) : Statement(TK)
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

	const char* VarStatement::ToString() const
	{
		std::stringstream ss;
		ss << TK->Value << " " << ID->ID << " = " << Value->ToString() << ";";

		std::string Str = ss.str();
		char* NStr = (char*)calloc(Str.length(), sizeof(char));
		strcpy(NStr, Str.c_str());

		return NStr;
	}

	const ASTNodeType VarStatement::Type() const
	{
		return ASTNodeType::VarStatement;
	}

	ExpressionStatement::ExpressionStatement(Token* TK, Expression* Value) : Statement(TK)
	{
		this->Value = Value;
	}

	ExpressionStatement::~ExpressionStatement()
	{
	}

	const char* ExpressionStatement::ToString() const
	{
		return Value->ToString();
	}

	const ASTNodeType ExpressionStatement::Type() const
	{
		return ASTNodeType::ExpressionStatement;
	}

}