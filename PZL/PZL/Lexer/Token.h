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
		TRUE,
		FALSE,

		//Primitive types
		TYPE_INT,
		TYPE_BOOL,

		//KeyWords
		FUNCTION,
		RETURN,

		// Others
		END_OF_FILE,
		ILLEGAL,
	};

	inline std::unordered_map<const char*, TokenType> KeyWords = {};
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

		~Token()
		{
			free(Value);
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
}