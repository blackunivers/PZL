#pragma once

#include "Types/Base.h"

#include "System/Error.h"
#include "System/Memory.h"

#include "IO/IO.h"

#include "Lexer/Lexer.h"
#include "Lexer/Token.h"

#include "Parser/Parser.h"
#include "Parser/AST/AST.h"
#include "Parser/AST/Expression.h"
#include "Parser/AST/Statement.h"
#include "Parser/PrefixParseFns.h"
#include "Parser/InfixParseFns.h"

#include "Evaluator/Evaluator.h"
#include "Evaluator/Environment.h"

namespace PZL
{

	inline void Init()
	{
	}

	inline void Exit()
	{
		PZL::Token::KeyWords.clear();
	}
}