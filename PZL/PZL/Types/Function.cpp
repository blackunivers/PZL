#include "PCH.h"
#include "Function.h"

#include "Parser/AST/Expression.h"
#include "Parser/AST/Statement.h"
#include "Evaluator/Environment.h"

namespace PZL::Type
{

	Function::Function(std::vector<AST::VarStatement*> Parameters, AST::Block* Body, Evaluator::Environment* Env)
	{
		this->Parameters = Parameters;
		this->Body = Body;
		this->Env = Env;
	}

	Function::~Function()
	{
		for (auto Param : Parameters)
			delete Param;
		delete Body;
		delete Env;
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
				if (Index < Parameters.size())
					strcat(Params, ", ");
				Index++;
			}
		}

		std::stringstream ss;
		ss << "func" << "(" << Params << ")";
		if (Body != nullptr)
			ss << Body->ToString();
		else
			ss << ';';

		std::string Str = ss.str();

		char* NStr = (char*)calloc(Str.length(), sizeof(char));
		strcpy(NStr, Str.c_str());

		return NStr;
	}
}