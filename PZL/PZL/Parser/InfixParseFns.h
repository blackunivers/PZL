#pragma once

#include "Parser/Parser.h"
#include "Parser/AST/AST.h"
#include "Parser/AST/Expression.h"

namespace PZL
{

	inline InfixParseFns DefineInfixFns()
	{
		InfixParseFns fns;
		fns[TokenType::PLUS] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::MINUS] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::DIVISION] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::MULTIPLICATION] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::EQUALS_TO] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::NOT_EQUALS] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::LESS_THAN] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::GREATER_THAN] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::LPAREN] = (InfixParseFn)ParseCall;

		return fns;
	}

	inline AST::Infix* ParseInfixExpression(Parser* This, AST::Expression* Left)
	{
		AST::Infix* Infix = new AST::Infix(This->CurrentToken, Left, This->CurrentToken->Value);

		Precedence P = This->CurrentPrecedence();

		This->Advance();

		Infix->Right = This->ParseExpression(P, TokenType::ILLEGAL);

		return Infix;
	}

	inline AST::Expression* ParseCall(Parser* This, AST::Expression* Fn)
	{
		AST::Call* call = new AST::Call(This->CurrentToken, Fn);
		call->Arguments = This->ParseCallArguments();

		return call;
	}

}