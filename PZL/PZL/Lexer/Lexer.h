#pragma once

#include "Types/Base.h"

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