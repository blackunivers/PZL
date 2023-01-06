#pragma once

#include "Parser/Parser.h"
#include "Parser/Precedence.h"
#include "Lexer/Token.h"
#include "Parser/AST/AST.h"
#include "Parser/AST/Statement.h"
#include "Parser/AST/Expression.h"

namespace PZL
{

	inline PrefixParseFns DefinePrefixFns()
	{
		PrefixParseFns Fns;
		Fns[TokenType::FUNCTION] = (PrefixParseFn)ParseFunction;
		Fns[TokenType::ID] = (PrefixParseFn)ParseIdentifier;
		Fns[TokenType::INT] = (PrefixParseFn)ParseInteger;
		Fns[TokenType::IF] = (PrefixParseFn)ParseIf;
		Fns[TokenType::LPAREN] = (PrefixParseFn)ParseGroupedExpression;
		Fns[TokenType::MINUS] = (PrefixParseFn)ParsePrefixExpression;
		Fns[TokenType::NOT] = (PrefixParseFn)ParsePrefixExpression;
		Fns[TokenType::FALSE] = (PrefixParseFn)ParseBoolean;
		Fns[TokenType::TRUE] = (PrefixParseFn)ParseBoolean;
		return Fns;
	}

	inline AST::Expression* ParseFunction(Parser* This, TokenType)
	{
		AST::Function* Function = new AST::Function(This->CurrentToken);

		if (!This->ExpectedToken(TokenType::ID))
			return nullptr;

		Function->FunctionName = new AST::Identifier(This->CurrentToken, This->CurrentToken->Value);

		if (!This->ExpectedToken(TokenType::LPAREN))
			return nullptr;
		delete This->CurrentToken;

		Function->Parameters = This->ParseFunctionParameters();

		if (!This->ExpectedToken(TokenType::COLON))
			return nullptr;
		delete This->CurrentToken;

		This->Advance();

		for (auto VarType : This->VarTypes)
		{
			if (This->CurrentToken->Type == VarType)
			{
				Function->FunctionType = This->CurrentToken;
				break;
			}
		}

		if (Function->FunctionType == NULL)
		{
			std::cout << "Error at Line " << This->CurrentToken->Line << ": \n\tA kind of return was expected.";
			exit(-1);
		}

		if (This->NextToken->Type == TokenType::SEMICOLON)
		{
			delete This->NextToken;
			This->Advance();

			return Function;
		}

		if (!This->ExpectedToken(TokenType::LBRACE))
			return nullptr;

		Function->Body = This->ParseBlock();
		Function->IsDefined = true;

		return Function;
	}

	inline AST::Expression* ParseIdentifier(Parser* This, TokenType)
	{
		return new AST::Identifier(This->CurrentToken, This->CurrentToken->Value);
	}

	inline AST::Expression* ParseInteger(Parser* This, TokenType Type)
	{
		if (Type == TokenType::TYPE_BOOL && This->NextToken->Type == TokenType::SEMICOLON)
		{
			AST::Boolean* Bool = new AST::Boolean(This->CurrentToken);
			Bool->Value = atoi(This->CurrentToken->Value) ? true : false;
			return Bool;
		}

		AST::Integer32* Int32 = new AST::Integer32(This->CurrentToken);
		Int32->Value = atoi(This->CurrentToken->Value);
		return Int32;
	}

	inline AST::Expression* ParseIf(Parser* This, TokenType)
	{
		AST::If* IF = new AST::If(This->CurrentToken);

		if (!This->ExpectedToken(TokenType::LPAREN))
			return nullptr;
		delete This->CurrentToken;

		This->Advance();

		IF->Condition = This->ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL);

		if (!This->ExpectedToken(TokenType::RPAREN))
			return nullptr;
		delete This->CurrentToken;

		if (!This->ExpectedToken(TokenType::LBRACE))
			return nullptr;

		IF->IfBlock = This->ParseBlock();

		if (This->NextToken->Type == TokenType::ELSE)
		{
			delete This->NextToken;
			This->Advance();

			if (!This->ExpectedToken(TokenType::LBRACE))
				return nullptr;

			IF->ElseBlock = This->ParseBlock();
		}

		return IF;
	}

	inline AST::Expression* ParseGroupedExpression(Parser* This, TokenType)
	{
		delete This->CurrentToken;
		This->Advance();

		AST::Expression* Expression = This->ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL);

		if (!This->ExpectedToken(TokenType::RPAREN))
			return nullptr;
		delete This->CurrentToken;

		return Expression;
	}

	inline AST::Prefix* ParsePrefixExpression(Parser* This, TokenType)
	{
		AST::Prefix* prefix_expression = new AST::Prefix(This->CurrentToken, This->CurrentToken->Value);

		This->Advance();

		prefix_expression->Right = This->ParseExpression(Precedence::PREFIX, TokenType::ILLEGAL);

		return prefix_expression;
	}

	inline AST::Expression* ParseBoolean(Parser* This, TokenType Type)
	{
		AST::Boolean* Bool = new AST::Boolean(This->CurrentToken);

		Bool->Value = (This->CurrentToken->Type == TokenType::FALSE ? false : true);

		return Bool;
	}

}