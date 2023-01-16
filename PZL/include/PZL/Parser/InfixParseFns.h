#pragma once

#include "PZL/Parser/Parser.h"
#include "PZL/Parser/AST/AST.h"
#include "PZL/Parser/AST/Expression.h"

namespace PZL
{

	inline InfixParseFns DefineInfixFns()
	{
		InfixParseFns fns;
		fns[TokenType::PLUS] = (InfixParseFn)Parser::ParseInfixExpression;
		fns[TokenType::MINUS] = (InfixParseFn)Parser::ParseInfixExpression;
		fns[TokenType::DIVISION] = (InfixParseFn)Parser::ParseInfixExpression;
		fns[TokenType::MULTIPLICATION] = (InfixParseFn)Parser::ParseInfixExpression;
		fns[TokenType::EQUALS_TO] = (InfixParseFn)Parser::ParseInfixExpression;
		fns[TokenType::NOT_EQUALS] = (InfixParseFn)Parser::ParseInfixExpression;
		fns[TokenType::LESS_THAN] = (InfixParseFn)Parser::ParseInfixExpression;
		fns[TokenType::GREATER_THAN] = (InfixParseFn)Parser::ParseInfixExpression;
		fns[TokenType::LPAREN] = (InfixParseFn)Parser::ParseCall;

		return fns;
	}

	inline AST::Infix* Parser::ParseInfixExpression(Parser* This, AST::Expression* Right)
	{
		AST::Infix* Infix = new AST::Infix(This->CurrentToken->Line, nullptr, This->CurrentToken->Value, Right);
		delete This->CurrentToken;

		Precedence P = This->CurrentPrecedence();

		This->Advance();

		Infix->Left = This->ParseExpression(P, TokenType::ILLEGAL);

		return Infix;
	}

	inline AST::Expression* Parser::ParseCall(Parser* This, AST::Expression* Fn)
	{
		AST::Call* call = new AST::Call(This->CurrentToken->Line, Fn);
		delete This->CurrentToken;
		call->Arguments = This->ParseCallArguments();

		return call;
	}

}