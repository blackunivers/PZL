#pragma once

#include "PCH.h"
#include "PZL/Types/Base.h"

namespace PZL
{

	enum class TokenType
	{
		NONE,
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

		// flow controllers
		IF,
		ELIF,
		ELSE,

		// Values
		INT32,
		FLOAT32,
		TRUE,
		FALSE,

		//Primitive types
		TYPE_VOID,
		TYPE_INT8,
		TYPE_UINT8,
		TYPE_INT16,
		TYPE_UINT16,
		TYPE_INT32,
		TYPE_UINT32,
		TYPE_INT64,
		TYPE_UINT64,
		TYPE_FLOAT32,
		TYPE_FLOAT64,
		TYPE_BOOL,

		//KeyWords
		FUNCTION,
		RETURN,

		// Others
		END_OF_FILE,
		ILLEGAL,
	};

	// Class mainly used to represent a token.
	struct Token
	{
	public:
		TokenType Type;
		char* Value;
		Type::Size Line;
	public:
		Token(TokenType Type, char Value, Type::Size Line)
		{
			this->Type = Type;
			this->Value = (char*)calloc(2, sizeof(char));
			this->Value[0] = Value;
			this->Value[1] = '\0';
			this->Line = Line;
		}

		Token(TokenType Type, const char* Value, Type::Size Line)
		{
			this->Type = Type;
			this->Value = (char*)Value;
			this->Line = Line;
		}

		~Token()
		{
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
	public:
		static inline std::unordered_map<const char*, TokenType> KeyWords = {};
	public:
		static const char* TokenTypeToString(TokenType Type);
		static TokenType LookUpTokenType(const char* ID);

	};
}