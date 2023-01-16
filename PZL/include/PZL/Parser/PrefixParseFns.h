#pragma once

#include "PZL/Parser/Parser.h"
#include "PZL/Parser/Precedence.h"
#include "PZL/Lexer/Token.h"
#include "PZL/Parser/AST/AST.h"
#include "PZL/Parser/AST/Statement.h"
#include "PZL/Parser/AST/Expression.h"

namespace PZL
{

	inline PrefixParseFns DefinePrefixFns()
	{
		PrefixParseFns Fns;
		Fns[TokenType::FUNCTION] = (PrefixParseFn)Parser::ParseFunction;
		Fns[TokenType::ID] = (PrefixParseFn)Parser::ParseIdentifier;
		Fns[TokenType::INT32] = (PrefixParseFn)Parser::ParseInteger;
		Fns[TokenType::FLOAT32] = (PrefixParseFn)Parser::ParseFloat;
		Fns[TokenType::IF] = (PrefixParseFn)Parser::ParseIf;
		Fns[TokenType::LPAREN] = (PrefixParseFn)Parser::ParseGroupedExpression;
		Fns[TokenType::MINUS] = (PrefixParseFn)Parser::ParsePrefixExpression;
		Fns[TokenType::NOT] = (PrefixParseFn)Parser::ParsePrefixExpression;
		Fns[TokenType::FALSE] = (PrefixParseFn)Parser::ParseBoolean;
		Fns[TokenType::TRUE] = (PrefixParseFn)Parser::ParseBoolean;
		return Fns;
	}

	inline AST::Expression* Parser::ParseFunction(Parser* This, TokenType)
	{
		AST::Function* Function = new AST::Function(This->CurrentToken->Line);
		delete This->CurrentToken;

		if (!This->ExpectedToken(TokenType::ID)) {}

		Function->FunctionName = new AST::Identifier(This->CurrentToken->Line, This->CurrentToken->Value);
		delete This->CurrentToken;

		if (!This->ExpectedToken(TokenType::LPAREN)) {}
		delete This->CurrentToken;

		Function->Parameters = This->ParseFunctionParameters();

		if (!This->ExpectedToken(TokenType::COLON)) {}
		delete This->CurrentToken;

		This->Advance();

		for (auto VarType : This->VarTypes)
		{
			if (This->CurrentToken->Type == VarType)
			{
				Function->FunctionType = This->CurrentToken->Type;
				delete This->CurrentToken;
				break;
			}
		}

		if (Function->FunctionType == TokenType::ILLEGAL)
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

		if (!This->ExpectedToken(TokenType::LBRACE)) {}

		Function->Body = This->ParseBlock();
		Function->IsDefined = true;

		return Function;
	}

	inline AST::Expression* Parser::ParseIdentifier(Parser* This, TokenType)
	{
		auto ID = new AST::Identifier(This->CurrentToken->Line, This->CurrentToken->Value);
		delete This->CurrentToken;
		return ID;
	}

	inline AST::Expression* Parser::ParseFloat(Parser* This, TokenType Type)
	{
		switch (Type)
		{
		case TokenType::TYPE_BOOL:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Boolean* Bool = new AST::Boolean(This->CurrentToken->Line);
				Bool->Value = atof(This->CurrentToken->Value) ? true : false;
				delete This->CurrentToken;
				return Bool;
			}
			break;
		case TokenType::TYPE_FLOAT64:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Float64* Float64 = new AST::Float64(This->CurrentToken->Line);
				Float64->Value = atof(This->CurrentToken->Value) ? true : false;
				delete This->CurrentToken;
				return Float64;
			}
			break;
		case TokenType::TYPE_INT8:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Integer8* Int = new AST::Integer8(This->CurrentToken->Line);
				Int->Value = (char)atof(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Int;
			}
			break;
		case TokenType::TYPE_UINT8:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::UnsignedInteger8* Int = new AST::UnsignedInteger8(This->CurrentToken->Line);
				Int->Value = (unsigned char)atof(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Int;
			}
			break;
		case TokenType::TYPE_INT16:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Integer16* Int = new AST::Integer16(This->CurrentToken->Line);
				Int->Value = (short)atof(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Int;
			}
			break;
		case TokenType::TYPE_UINT16:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::UnsignedInteger16* Int = new AST::UnsignedInteger16(This->CurrentToken->Line);
				Int->Value = (unsigned short)atof(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Int;
			}
			break;
		case TokenType::TYPE_INT32:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Integer32* Int = new AST::Integer32(This->CurrentToken->Line);
				Int->Value = (int)atof(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Int;
			}
			break;
		case TokenType::TYPE_UINT32:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::UnsignedInteger32* Int = new AST::UnsignedInteger32(This->CurrentToken->Line);
				Int->Value = (unsigned int)atof(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Int;
			}
			break;
		case TokenType::TYPE_INT64:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Integer64* Int = new AST::Integer64(This->CurrentToken->Line);
				Int->Value = (long long)atof(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Int;
			}
			break;
		case TokenType::TYPE_UINT64:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::UnsignedInteger64* Int = new AST::UnsignedInteger64(This->CurrentToken->Line);
				Int->Value = (unsigned long long)atof(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Int;
			}
			break;
		}

		AST::Float32* Float32 = new AST::Float32(This->CurrentToken->Line);
		Float32->Value = (float)atof(This->CurrentToken->Value);
		delete This->CurrentToken;
		return Float32;
	}

	inline AST::Expression* Parser::ParseInteger(Parser* This, TokenType Type)
	{
		switch (Type)
		{
		case PZL::TokenType::TYPE_INT8:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Integer8* Integer = new AST::Integer8(This->CurrentToken->Line);
				Integer->Value = (char)atoi(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Integer;
			}
			break;
		case PZL::TokenType::TYPE_UINT8:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::UnsignedInteger8* Integer = new AST::UnsignedInteger8(This->CurrentToken->Line);
				Integer->Value = (unsigned char)atoi(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Integer;
			}
			break;
		case PZL::TokenType::TYPE_INT16:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Integer16* Integer = new AST::Integer16(This->CurrentToken->Line);
				Integer->Value = (short)atoi(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Integer;
			}
			break;
		case PZL::TokenType::TYPE_UINT16:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::UnsignedInteger16* Integer = new AST::UnsignedInteger16(This->CurrentToken->Line);
				Integer->Value = (unsigned short)atoi(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Integer;
			}
			break;
		case PZL::TokenType::TYPE_INT32:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Integer32* Integer = new AST::Integer32(This->CurrentToken->Line);
				Integer->Value = (int)atoi(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Integer;
			}
			break;
		case PZL::TokenType::TYPE_UINT32:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::UnsignedInteger32* Integer = new AST::UnsignedInteger32(This->CurrentToken->Line);
				Integer->Value = (unsigned int)atoi(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Integer;
			}
			break;
		case PZL::TokenType::TYPE_INT64:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Integer64* Integer = new AST::Integer64(This->CurrentToken->Line);
				Integer->Value = (long long)atoll(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Integer;
			}
			break;
		case PZL::TokenType::TYPE_UINT64:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::UnsignedInteger64* Integer = new AST::UnsignedInteger64(This->CurrentToken->Line);
				Integer->Value = (unsigned long long)atoll(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Integer;
			}
			break;
		case PZL::TokenType::TYPE_FLOAT32:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Float64* Float = new AST::Float64(This->CurrentToken->Line);
				Float->Value = (float)atoi(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Float;
			}
			break;
		case PZL::TokenType::TYPE_FLOAT64:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Float64* Float = new AST::Float64(This->CurrentToken->Line);
				Float->Value = (double)atoi(This->CurrentToken->Value);
				delete This->CurrentToken;
				return Float;
			}
			break;
		case PZL::TokenType::TYPE_BOOL:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Boolean* Bool = new AST::Boolean(This->CurrentToken->Line);
				Bool->Value = atof(This->CurrentToken->Value) ? true : false;
				delete This->CurrentToken;
				return Bool;
			}
			break;
		}
		
		AST::Integer32* Int32 = new AST::Integer32(This->CurrentToken->Line);
		Int32->Value = atoi(This->CurrentToken->Value);
		delete This->CurrentToken;
		return Int32;
	}

	inline AST::Expression* Parser::ParseIf(Parser* This, TokenType)
	{
		AST::If* IF = new AST::If(This->CurrentToken->Line);
		delete This->CurrentToken;

		if (!This->ExpectedToken(TokenType::LPAREN)) {}
		delete This->CurrentToken;

		This->Advance();

		IF->Condition = This->ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL);

		if (!This->ExpectedToken(TokenType::RPAREN)) {}
		delete This->CurrentToken;

		if (!This->ExpectedToken(TokenType::LBRACE)) {}
		delete This->CurrentToken;

		IF->IfBlock = This->ParseBlock();

		if (This->NextToken->Type == TokenType::ELSE)
		{
			delete This->NextToken;
			This->Advance();

			if (!This->ExpectedToken(TokenType::LBRACE)) {}
			delete This->CurrentToken;

			IF->ElseBlock = This->ParseBlock();
		}

		return IF;
	}

	inline AST::Expression* Parser::ParseGroupedExpression(Parser* This, TokenType)
	{
		delete This->CurrentToken;
		This->Advance();

		AST::Expression* Expression = This->ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL);

		if (!This->ExpectedToken(TokenType::RPAREN)) {}
		delete This->CurrentToken;

		return Expression;
	}

	inline AST::Prefix* Parser::ParsePrefixExpression(Parser* This, TokenType)
	{
		AST::Prefix* prefix_expression = new AST::Prefix(This->CurrentToken->Line, This->CurrentToken->Value);
		delete This->CurrentToken;

		This->Advance();

		prefix_expression->Right = This->ParseExpression(Precedence::PREFIX, TokenType::ILLEGAL);

		return prefix_expression;
	}

	inline AST::Expression* Parser::ParseBoolean(Parser* This, TokenType Type)
	{
		switch (Type)
		{
		case PZL::TokenType::TYPE_INT8:
		case PZL::TokenType::TYPE_UINT8:
		case PZL::TokenType::TYPE_INT16:
		case PZL::TokenType::TYPE_UINT16:
		case PZL::TokenType::TYPE_INT32:
		case PZL::TokenType::TYPE_UINT32:
		case PZL::TokenType::TYPE_INT64:
		case PZL::TokenType::TYPE_UINT64:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Integer32* Int = new AST::Integer32(This->CurrentToken->Line);
				Int->Value = (This->CurrentToken->Type == TokenType::FALSE ? 0 : 1);
				delete This->CurrentToken;
				return Int;
			}
			break;
		case PZL::TokenType::TYPE_FLOAT32:
		case PZL::TokenType::TYPE_FLOAT64:
			if (This->NextToken->Type == TokenType::SEMICOLON)
			{
				AST::Float32* Float = new AST::Float32(This->CurrentToken->Line);
				Float->Value = (This->CurrentToken->Type == TokenType::FALSE ? 0.f : 1.f);
				delete This->CurrentToken;
				return Float;
			}
			break;
		}

		AST::Boolean* Bool = new AST::Boolean(This->CurrentToken->Line);
		Bool->Value = (This->CurrentToken->Type == TokenType::FALSE ? false : true);
		delete This->CurrentToken;
		return Bool;
	}

}