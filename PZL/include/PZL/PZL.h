#pragma once

#include "PZL/Types/Base.h"

#include "PZL/System/Memory.h"

#include "PZL/IO/IO.h"

#include "PZL/Lexer/Lexer.h"
#include "PZL/Lexer/Token.h"

#include "PZL/Parser/Parser.h"
#include "PZL/Parser/AST/AST.h"
#include "PZL/Parser/AST/Expression.h"
#include "PZL/Parser/AST/Statement.h"
#include "PZL/Parser/PrefixParseFns.h"
#include "PZL/Parser/InfixParseFns.h"

#include "PZL/Evaluator/Evaluator.h"
#include "PZL/Evaluator/Environment.h"
#include "PZL/Evaluator/Function/Function.h"

namespace PZL
{

	inline void Init()
	{
	}

	inline void Exit()
	{
	}
}