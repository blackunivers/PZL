#include "PCH.h"
#include "PZL/Parser/AST/Expression.h"

#include "PZL/Lexer/Token.h"
#include "PZL/Parser/AST/Statement.h"

namespace PZL::AST
{

	Identifier::Identifier(Type::Size Line, const char* ID) : Expression(Line)
	{
		this->ID = ID;
	}

	Identifier::~Identifier()
	{
	}

	const ASTNodeType Identifier::Type() const
	{
		return ASTNodeType::Identifier;
	}

	Boolean::Boolean(Type::Size Line, Type::Bool value) : Expression(Line)
	{
		this->Value = Value;
	}

	Boolean::~Boolean()
	{
	}

	const ASTNodeType Boolean::Type() const
	{
		return ASTNodeType::Boolean;
	}

	Prefix::Prefix(Type::Size Line, const char* Operator, Expression* Right) : Expression(Line)
	{
		this->Operator = Operator;
		this->Right = Right;
	}

	Prefix::~Prefix()
	{
		delete Right;
	}

	const ASTNodeType Prefix::Type() const
	{
		return ASTNodeType::Prefix;
	}

	Infix::Infix(Type::Size Line, Expression* Left, const char* Operator, Expression* Right) : Expression(Line)
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

	const ASTNodeType Infix::Type() const
	{
		return ASTNodeType::Infix;
	}

	Function::Function(Type::Size Line, TokenType FunctionType, Identifier* FunctionName, std::vector<VarStatement*> Parameters, Block* Body) : Expression(Line)
	{
		this->FunctionType = FunctionType;
		this->FunctionName = FunctionName;
		this->Parameters = Parameters;
		this->Body = Body;
	}

	Function::~Function()
	{
		delete FunctionName;

		for (auto Param : Parameters)
			delete Param;

		delete Body;
	}

	const ASTNodeType Function::Type() const
	{
		return ASTNodeType::Function;
	}

	Call::Call(Type::Size Line, Expression* Fn, std::vector<Expression*> Arguments) : Expression(Line)
	{
		this->Fn = Fn;
		this->Arguments = Arguments;
	}

	Call::~Call()
	{
		delete Fn;
		for (auto Arg : Arguments)
			delete Arg;
	}

	const ASTNodeType Call::Type() const
	{
		return ASTNodeType::Call;
	}

	If::If(Type::Size Line, Expression* Condition, Block* IfBlock, Block* ElseBlock) : Expression(Line)
	{
		this->Condition = Condition;
		this->IfBlock = IfBlock;
		this->ElseBlock = ElseBlock;
	}

	If::~If()
	{
		delete Condition;
		delete IfBlock;
		delete ElseBlock;
	}

	const ASTNodeType If::Type() const
	{
		return ASTNodeType::If;
	}

}