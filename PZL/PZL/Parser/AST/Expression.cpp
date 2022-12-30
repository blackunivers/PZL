#include "PCH.h"
#include "Expression.h"

#include "Lexer/Token.h"
#include "Parser/AST/Statement.h"

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
		this->Value = Value;
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

	Function::Function(Token* TK, Token* FunctionType, Identifier* FunctionName, std::vector<VarStatement*> Parameters, Block* Body) : Expression(TK)
	{
		this->FunctionType = FunctionType;
		this->FunctionName = FunctionName;
		this->Parameters = Parameters;
		this->Body = Body;
	}

	Function::~Function()
	{
		delete FunctionType;
		delete FunctionName;

		for (auto Param : Parameters)
			delete Param;

		delete Body;
	}

	const char* Function::ToString() const
	{
		char* Params = (char*)calloc(2, sizeof(char));
		if (Parameters.size() == 1)
			strcat(Params, Parameters[0]->ToString());
		else
		{
			for (auto Param : Parameters)
			{
				static Type::Size Index = 1;
				std::string Tmp = Param->ToString();
				Params = (char*)realloc(Params, (Tmp.length() + strlen(Params) + 3) * sizeof(char));
				strcat(Params, Tmp.c_str());
				if(Index < Parameters.size())
					strcat(Params, ", ");
				Index++;
			}
		}

		std::stringstream ss;
		ss << TK->Value << ' ' << FunctionName->ID << "(" << Params << ")" << " : " << FunctionType->Value;
		if (Body != nullptr)
			ss << Body->ToString();
		else
			ss << ';';

		std::string Str = ss.str();

		char* NStr = (char*)calloc(Str.length(), sizeof(char));
		strcpy(NStr, Str.c_str());

		free(Params);
		return NStr;
	}

	const ASTNodeType Function::Type() const
	{
		return ASTNodeType::Function;
	}

	Call::Call(Token* TK, Expression* Fn, std::vector<Expression*> Arguments) : Expression(TK)
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

	const char* Call::ToString() const
	{
		char* Args = (char*)calloc(2, sizeof(char));
		for (auto Arg : Arguments)
		{
			static Type::Size Index = 1;
			std::string Tmp = Arg->ToString();
			Args = (char*)realloc(Args, (Tmp.length() + strlen(Args) + 3) * sizeof(char));
			strcat(Args, Tmp.c_str());
			if (Index < Arguments.size())
				strcat(Args, ", ");
			Index++;
		}

		std::stringstream ss;
		ss << Fn->ToString() << "(" << Args << ");";
		std::string Str = ss.str();

		char* NStr = (char*)calloc(Str.length(), sizeof(char));
		strcpy(NStr, Str.c_str());
		
		return NStr;
	}

	const ASTNodeType Call::Type() const
	{
		return ASTNodeType::Call;
	}

}