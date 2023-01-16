#pragma once

#include "PZL/Types/Base.h"

namespace PZL
{
	enum class TokenType;
	struct Token;

	// Class mainly used for lexing.
	class Lexer
	{
	public:
		Lexer(const char* Source);
		~Lexer();

		// Returns a pointer to a token corresponding to the passed string. 
		Token* NextToken();

	public:
		void SkipWhiteSpace();
		void Advance();
		char PeekCharacter();

		Token* AdvanceWith(TokenType Type); 
		Token* AdvanceWithTwo(TokenType Type);
		Token* AdvanceWithID();
		Token* AdvanceWithDigit();
		Token* AdvanceWithFloat(const char* Left);

	public:
		const char* Source;
		size_t Len;
		size_t Index;
		Type::Size Line = 1;
		char Current;
	};
}