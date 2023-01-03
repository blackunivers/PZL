#pragma once

#include "Parser/AST/AST.h"
#include "Types/Object.h"

namespace PZL::AST
{

    struct If;
    struct Block;
    struct Identifier;
}

namespace PZL::Type
{

    struct Error;
}

namespace PZL::Evaluator
{

    enum class Context
    {
        Expression = 1,
        Var,
    };

    inline int Line;
    inline Context TypeEvaluation = Context::Expression;

    struct Environment;

    Object* Evaluate(AST::ASTNode* Node, Environment* Env);

    Object* EvaluateProgram(const AST::Program* Program, Environment* Env);

    Object* EvaluateBangExpression(Object* Right);

    Object* EvaluateBlockStatements(const AST::Block* Block, Environment* Env);

    Object* EvaluateIfExpression(AST::If* If, Environment* Env);

    Object* EvaluateIdentifier(AST::Identifier* ID, Environment* Env);

    bool IsTruThy(Object* Obj);

    Object* EvaluateInfixExpression(const char* Operator, Object* Left, Object* Right);
    Object* EvaluateIntegerInfixExpression(const char* Operator, Object* Left, Object* Right);
    Object* EvaluateBooleanInfixExpression(const char* Operator, Object* Left, Object* Right);

    Object* EvaluateMinusOperatorExpression(Object* Right);

    Object* EvaluatePrefixExpression(const char* Operator, Object* Right);

    template<typename... TArgs>
    const char* CreateErrorMessage(const char* Message, TArgs&&... Args);

    Type::Error* NewError(const char* Message);

}