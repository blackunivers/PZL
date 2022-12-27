#pragma once

#include "Types/Base.h"

namespace PZL
{

	enum class TokenType
	{
		ID,

		// Symbols
		EQUALS,
		PLUS,
		MINUS,
		MULTIPLICATION,
		DIVISION,
		LPAREN,
		RPAREN,
		LBRACE,
		RBRACE,
		COLON,
		SEMICOLON,
		COMMA,
		DOT,

		// Logic operators
		EQUALS_TO,
		NOT,
		NOT_EQUALS,
		LESS_THAN,
		GREATER_THAN,

		//Values
		INT,

		//Primitive types
		TYPE_INT,

		//KeyWords
		FUNCTION,
		RETURN,

		// Others
		END_OF_FILE,
		ILLEGAL,
	};
	
	const char* TokenTypeToString(TokenType Type);
	TokenType LookUpTokenType(const char* ID);

	// Class mainly used to represent a token.
	struct Token
	{
		TokenType Type;
		char* Value;

		Token(TokenType Type, char Value)
		{
			this->Type = Type;
			this->Value = (char*)calloc(2, sizeof(char));
			this->Value[0] = Value;
			this->Value[1] = '\0';
		}

		Token(TokenType Type, const char* Value)
		{
			this->Type = Type;
			this->Value = (char*)Value;
		}

		// Returns its current value as a string.
		inline const char* ToString()
		{
			std::stringstream ss;
			ss << "Type: " << TokenTypeToString(Type) << ", Value: " << Value;

			std::string Str = ss.str();
			char* NStr = (char*)calloc(Str.length(), sizeof(char));
			strcpy(NStr, Str.c_str());

			return NStr;
		}
	};


	// Class mainly used for lexing.
	class Lexer
	{
	public:
		Lexer(const char* Source);
		~Lexer();

		// Returns a pointer to a token corresponding to the passed string. 
		Token* NextToken();

	private:
		void _SkipWhiteSpace();
		void _Advance();
		char _PeekCharacter();

		Token* _AdvanceWith(TokenType Type); 
		Token* _AdvanceWithTwo(TokenType Type);
		Token* _AdvanceWithID();
		Token* _AdvanceWithDigit();

	private:
		const char* _Source;
		Type::Size _Len;
		Type::Size _Index;
		Type::Char _Current;
	};
}