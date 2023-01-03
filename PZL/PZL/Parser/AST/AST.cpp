#include "PCH.h"
#include "AST.h"

#include "Lexer/Token.h"

namespace PZL::AST
{

	Statement::Statement(Token* TK)
	{
		this->TK = TK;
	}

	Statement::~Statement()
	{
		delete TK;
	}

	Expression::Expression(Token* TK)
	{
			this->TK = TK;
	}

	Expression::~Expression()
	{
		delete TK;
	}

	Program::Program(std::vector<Statement*> Statements)
	{
		this->Statements = Statements;
	}

	Program::~Program()
	{
		for (auto statement : Statements)
			delete statement;
	}

	const char* Program::ToString() const
	{
		std::vector<const char*> out;
		for (auto statement : Statements)
		{
			if (statement != nullptr)
				out.emplace_back(statement->ToString());
		}

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

	const ASTNodeType Program::Type() const
	{
		return ASTNodeType::Program;
	}

}