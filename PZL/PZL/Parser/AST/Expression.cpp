#include "PCH.h"
#include "Expression.h"

#include "Lexer/Token.h"

namespace PZL::AST
{

	Identifier::Identifier(Token* TK, const char* ID) : Expression(TK)
	{
		this->ID = ID;
	}

	Identifier::~Identifier()
	{
	}

	const char* Identifier::ToString() const
	{
		return ID;
	}

	const ASTNodeType Identifier::Type() const
	{
		return ASTNodeType::Identifier;
	}

	Integer::Integer(Token* TK, Type::Int32 value) : Expression(TK)
	{
		this->Value = Value;
	}

	Integer::~Integer()
	{
	}

	const char* Integer::ToString() const
	{
		std::string Str = std::to_string(Value.Data);
		char* NStr = (char*)calloc(Str.length(), sizeof(char));
		strcpy(NStr, Str.c_str());

		return NStr;
	}

	const ASTNodeType Integer::Type() const
	{
		return ASTNodeType::Integer;
	}

	Boolean::Boolean(Token* TK, Type::Bool value) : Expression(TK)
	{
	}

	Boolean::~Boolean()
	{
	}

	const char* Boolean::ToString() const
	{
		return Value.ToString();
	}

	const ASTNodeType Boolean::Type() const
	{
		return ASTNodeType::Boolean;
	}

	Prefix::Prefix(Token* TK, const char* Operator, Expression* Right) : Expression(TK)
	{
		this->Operator = Operator;
		this->Right = Right;
	}

	Prefix::~Prefix()
	{
		delete Right;
	}

	const char* Prefix::ToString() const
	{
		std::stringstream ss;
		ss << "(" << Operator << Right->ToString() << ")";
		std::string Str = ss.str();

		char* NStr = (char*)calloc(Str.length(), sizeof(char));
		strcpy(NStr, Str.c_str());

		return NStr;
	}

	const ASTNodeType Prefix::Type() const
	{
		return ASTNodeType::Prefix;
	}

	Infix::Infix(Token* TK, Expression* Left, const char* Operator, Expression* Right) : Expression(TK)
	{
		this->Left = Left;
		this->Operator = Operator;
		this->Right = Right;
	}

	Infix::~Infix()
	{
		delete Left;
		delete Right;
	}

	const char* Infix::ToString() const
	{
		std::stringstream ss;
		ss << "(" << Left->ToString() << " " << Operator << " " << Right->ToString() << ")";
		std::string Str = ss.str();

		char* NStr = (char*)calloc(Str.length(), sizeof(char));
		strcpy(NStr, Str.c_str());

		return NStr;
	}

	const ASTNodeType Infix::Type() const
	{
		return ASTNodeType::Infix;
	}

}