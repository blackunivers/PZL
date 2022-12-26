#pragma once

namespace PZL
{

	enum class TokenType
	{
		ID,

		// Symbols
		LPAREN,
		RPAREN,
		LBRACE,
		RBRACE,
		COLON,
		SEMICOLON,

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

	class Lexer
	{
	public:

	private:

	};
}