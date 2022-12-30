#include "PCH.h"
#include "Statement.h"

#include "Lexer/Token.h"
#include "Parser/AST/Expression.h"
#include "System/Error.h"

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
		ss << TK->Value << " " << ID->ID;
		if (Value != nullptr)
			ss << " = " << Value->ToString();

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
		if (Value)
			return Value->ToString();
		else
			return "Undefined value for ExpressionStatement";
	}

	const ASTNodeType ExpressionStatement::Type() const
	{
		return ASTNodeType::ExpressionStatement;
	}

	Block::Block(Token* TK, std::vector<Statement*> Statements) : Statement(TK)
	{
		this->Statements = Statements;
	}

	Block::~Block()
	{
		for (auto statement : Statements)
			delete statement;
	}

	inline const char* Block::ToString() const
	{
		std::vector<const char*> out;
		out.emplace_back("\n{");
		for (auto statement : Statements)
		{
			if (statement != nullptr)
			{
				std::string Str = "\t";
				Str.append(statement->ToString());

				char* NStr = (char*)calloc(Str.length(), sizeof(char));
				strcpy(NStr, Str.c_str());

				out.emplace_back(NStr);
			}
		}
		out.emplace_back("}");

		std::stringstream ss;
		for (auto str : out)
		{
			ss << str << '\n';
		}

		std::string Str = ss.str();
		char* NStr = (char*)calloc(Str.length(), sizeof(char));
		strcpy(NStr, Str.c_str());

		return NStr;
	}

	const ASTNodeType Block::Type() const
	{
		return ASTNodeType::Block;
	}

	ReturnStatement::ReturnStatement(Token* TK, Expression* Value) : Statement(TK)
	{
		this->Value = Value;
	}

	ReturnStatement::~ReturnStatement()
	{
		delete Value;
	}

	const char* ReturnStatement::ToString() const
	{
		std::stringstream ss;
		ss << TK->Value << " " << Value->ToString() << ";";
		std::string Str = ss.str();

		char* NStr = (char*)calloc(Str.length(), sizeof(char));
		strcpy(NStr, Str.c_str());

		return NStr;
	}

	const ASTNodeType ReturnStatement::Type() const
	{
		return ASTNodeType::ReturnStatement;
	}

}