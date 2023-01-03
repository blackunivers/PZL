#include "PCH.h"
#include "Evaluator.h"

#include "Parser/AST/Expression.h"
#include "Parser/AST/Statement.h"
#include "Lexer/Token.h"
#include "Types/Object.h"
#include "Types/Global.h"
#include "Evaluator/Environment.h"

namespace PZL::Evaluator
{

    Object* Evaluate(AST::ASTNode* Node, Environment* Env)
    {
        AST::ASTNodeType NodeType = Node->Type();

        if (NodeType == AST::ASTNodeType::Program)
        {
            AST::Program* Program = (AST::Program*)Node;

            return EvaluateProgram(Program, Env);
        }
        else if (NodeType == AST::ASTNodeType::ExpressionStatement)
        {
            AST::ExpressionStatement* ES = (AST::ExpressionStatement*)Node;
            Line = ES->TK->Line;
            if (ES->Value != nullptr)
                return Evaluate(ES->Value, Env);
        }
        else if (NodeType == AST::ASTNodeType::Integer32)
        {
            AST::Integer32* Int32 = (AST::Integer32*)Node;
            Line = Int32->TK->Line;
            return new Type::Int32(Int32->Value);
        }
        else if (NodeType == AST::ASTNodeType::Boolean)
        {
            AST::Boolean* Bool = (AST::Boolean*)Node;
            Line = Bool->TK->Line;
            return new Type::Bool(Bool->Value);
        }
        else if (NodeType == AST::ASTNodeType::Prefix)
        {
            AST::Prefix* Prefix = (AST::Prefix*)Node;
            Line = Prefix->TK->Line;
            Object* Right = Evaluate(Prefix->Right, Env);

            Object* Result = EvaluatePrefixExpression(Prefix->Operator, Right);
            if (TypeEvaluation == Context::Var)
                if (Prefix->Right->Type() != AST::ASTNodeType::Identifier)
                    delete Right;
            else if (TypeEvaluation == Context::Expression)
                delete Right;

            TypeEvaluation = Context::Expression;
            return Result;
        }
        else if (NodeType == AST::ASTNodeType::Infix)
        {
            AST::Infix* Infix = (AST::Infix*)Node;
            Line = Infix->TK->Line;
            Object* Left = Evaluate(Infix->Left, Env);
            Object* Right = Evaluate(Infix->Right, Env);

            Object* Result =  EvaluateInfixExpression(Infix->Operator, Left, Right);

           
            if(Infix->Left->Type() != AST::ASTNodeType::Identifier)
                delete Left;
            if (Infix->Right->Type() != AST::ASTNodeType::Identifier)
                delete Right;
            
            TypeEvaluation = Context::Expression;
            return Result;
        }
        else if (NodeType == AST::ASTNodeType::Block)
        {
            AST::Block* Block = (AST::Block*)Node;
            Line = Block->TK->Line;
            return EvaluateBlockStatements(Block, Env);
        }
        else if (NodeType == AST::ASTNodeType::If)
        {
            AST::If* If = (AST::If*)Node;
            Line = If->TK->Line;
            return EvaluateIfExpression(If, Env);
        }
        else if (NodeType == AST::ASTNodeType::ReturnStatement)
        {
            AST::ReturnStatement* RS = (AST::ReturnStatement*)Node;
            Line = RS->TK->Line;
            Object* Result = nullptr;

            if (RS->Value != nullptr)
                Result = Evaluate(RS->Value, Env);

            if (Result->Type != ObjectType::Null)
                return new Type::Return(Result);
        }
        else if (NodeType == AST::ASTNodeType::VarStatement)
        {
            AST::VarStatement* Var = (AST::VarStatement*)Node;
            Line = Var->TK->Line;
            Object* Value = nullptr;
            auto it = Env->StorageVar.find(Var->ID->ID);

            if (it != Env->StorageVar.end())
            {
                TypeEvaluation = Context::Var;
                return it->second;
            }
            else
            {
                TypeEvaluation = Context::Var;
                if (Var->Value != nullptr)
                    Value = Evaluate(Var->Value, Env);

                if (Var->ID != nullptr && Value->Type != ObjectType::Null)
                {
                    if(Var->VarType == TokenType::TYPE_INT)
                    {
                        Object* Int32 = new Type::Int32(((Type::Int32*)Value)->Data);
                        delete Value;
                        Env->StorageVar[Var->ID->ID] = Int32;
                    }
                    if (Var->VarType == TokenType::TYPE_BOOL)
                    {
                        Object* Bool = new Type::Bool(((Type::Bool*)Value)->Data);
                        delete Value;
                        Env->StorageVar[Var->ID->ID] = Bool;
                    }
                }
            }
        }
        else if (NodeType == AST::ASTNodeType::Identifier)
        {
            AST::Identifier* ID = (AST::Identifier*)Node;
            Line = ID->TK->Line;
            TypeEvaluation = Context::Var;
            return EvaluateIdentifier(ID, Env);
        }
        else if (NodeType == AST::ASTNodeType::Function)
        {
            AST::Function* Function = (AST::Function*)Node;
            return new Type::Function(Function->Parameters, Function->Body, Env);
        }

        return new Type::Null();
    }

    Object* EvaluateProgram(const AST::Program* Program, Environment* Env)
    {
        Object* Result = new Type::Null();

        for (auto Statement : Program->Statements)
        {
            Line = Statement->TK->Line;
            if (TypeEvaluation == Context::Expression)
                delete Result;
            else if(TypeEvaluation == Context::Var)
                if (Result->Type == PZL::ObjectType::Null || Result->Type == PZL::ObjectType::Error)
                    delete Result;
            Result = Evaluate(Statement, Env);

            if (Result->Type == ObjectType::Return)
            {
                Type::Return* Return = (Type::Return*)Result;
                Object* Value = &(*(Return->Value));
                Return->Value = NULL;
                delete Return;
                return Value;
            }
            else if(Result->Type == ObjectType::Error)
                return Result;
        }
        return Result;
    }

    Object* EvaluateBangExpression(Object* Right)
    {
        if (Right->Type == ObjectType::Int32)
            return new Type::Int32((int)(!((Type::Int32*)Right)->Data));
        else if (((Type::Bool*)Right)->Data == Type::TRUE.Data)
            return new Type::Bool(false);
        else if (((Type::Bool*)Right)->Data == Type::FALSE.Data)
            return new Type::Bool(true);
        else
            return new Type::Bool(false);
    }
    
    Object* EvaluateBlockStatements(const AST::Block* Block, Environment* Env)
    {
        Object* Result = new Type::Null;

        for (auto Statement : Block->Statements)
        {
            Line = Statement->TK->Line;
            if (Result->Type == PZL::ObjectType::Null || Result->Type == PZL::ObjectType::Error)
                delete Result;
            Result = Evaluate(Statement, Env);

            if (Result->Type == ObjectType::Return)
            {
                Type::Return* Return = (Type::Return*)Result;
                return Return->Value;
            }
        }
        return Result;
    }

    Object* EvaluateIfExpression(AST::If* If, Environment* Env)
    {
        Object* Condition = Evaluate(If->Condition, Env);
        if (IsTruThy(Condition))
        {
            delete Condition;
            return Evaluate(If->IfBlock, Env);
        }
        else if (If->ElseBlock != nullptr)
        {
            delete Condition;
            return Evaluate(If->ElseBlock, Env);
        }
        delete Condition;
        return new Type::Null;
    }

    Object* EvaluateIdentifier(AST::Identifier* ID, Environment* Env)
    {
        auto Value = Env->StorageVar.find(ID->ID);

        if (Value != Env->StorageVar.end())
            return Env->StorageVar[ID->ID];

        return NewError(CreateErrorMessage(Type::ERROR_UNDEFINED_IDENTIFIER.What, ID->ID));
    }

    bool IsTruThy(Object* Obj)
    {
        if (Obj == NULL)
            return false;
        else if (((Type::Bool*)Obj)->Data == Type::TRUE.Data)
            return true;
        else if (((Type::Bool*)Obj)->Data == Type::FALSE.Data)
            return false;
        else
            return true;
    }

    Object* EvaluateInfixExpression(const char* Operator, Object* Left, Object* Right)
    {
        if (Left->Type == ObjectType::Int32 && Right->Type == ObjectType::Int32)
            return EvaluateIntegerInfixExpression(Operator, Left, Right);
        if (Left->Type == ObjectType::Bool && Right->Type == ObjectType::Int32)
            return EvaluateBooleanInfixExpression(Operator, Left, Right);
        if (Left->Type == ObjectType::Int32 && Right->Type == ObjectType::Bool)
            return EvaluateBooleanInfixExpression(Operator, Left, Right);
        if (Left->Type == ObjectType::Bool && Right->Type == ObjectType::Bool)
            return EvaluateBooleanInfixExpression(Operator, Left, Right);
        else if (std::strcmp(Operator, "==") == 0)
            return new Type::Bool(((Type::Bool*)Left)->Data == ((Type::Bool*)Right)->Data);
        else if (std::strcmp(Operator, "!=") == 0)
            return new Type::Bool(((Type::Bool*)Left)->Data != ((Type::Bool*)Right)->Data);
        else if (Left->Type != Right->Type)
            return NewError(CreateErrorMessage(Type::ERROR_UNKNOWN_OPERATION.What, Operator, Object::ObjectTypeToString(Left->Type), Operator, Object::ObjectTypeToString(Right->Type)));
        else
            return NewError(CreateErrorMessage(Type::ERROR_UNKNOWN_OPERATION.What, Operator, Object::ObjectTypeToString(Left->Type), Operator, Object::ObjectTypeToString(Right->Type)));
    }

    Object* EvaluateIntegerInfixExpression(const char* Operator, Object* Left, Object* Right)
    {
        Type::Int32* ValueLeft = (Type::Int32*)Left;
        Type::Int32* ValueRight = (Type::Int32*)Right;

        if (std::strcmp(Operator, "+") == 0)
            return new Type::Int32(ValueLeft->Data + ValueRight->Data);
        else if (std::strcmp(Operator, "==") == 0)
            return new Type::Bool(ValueLeft->Data == ValueRight->Data);
        else if (std::strcmp(Operator, "!=") == 0)
            return new Type::Bool(ValueLeft->Data != ValueRight->Data);
        else if (std::strcmp(Operator, "-") == 0)
            return new Type::Int32(ValueLeft->Data - ValueRight->Data);
        else if (std::strcmp(Operator, "*") == 0)
            return new Type::Int32(ValueLeft->Data * ValueRight->Data);
        else if (std::strcmp(Operator, "/") == 0)
            return new Type::Int32(ValueLeft->Data / ValueRight->Data);
        else if (std::strcmp(Operator, "<") == 0)
            return new Type::Bool(ValueLeft->Data < ValueRight->Data);
        else if(std::strcmp(Operator, ">") == 0)
            return new Type::Bool(ValueLeft->Data > ValueRight->Data);
        else
            return NewError(CreateErrorMessage(Type::ERROR_UNKNOWN_OPERATION.What, Operator, Object::ObjectTypeToString(Left->Type), Operator, Object::ObjectTypeToString(Right->Type)));
    }

    Object* EvaluateBooleanInfixExpression(const char* Operator, Object* Left, Object* Right)
    {
        Type::Bool* ValueLeft = (Type::Bool*)Left;
        Type::Bool* ValueRight = (Type::Bool*)Right;

        if (std::strcmp(Operator, "+") == 0)
            return new Type::Int32(ValueLeft->Data + ValueRight->Data);
        else if (std::strcmp(Operator, "-") == 0)
            return new Type::Int32(ValueLeft->Data - ValueRight->Data);
        else if (std::strcmp(Operator, "*") == 0)
            return new Type::Int32(ValueLeft->Data * ValueRight->Data);
        else if (std::strcmp(Operator, "==") == 0)
            return new Type::Bool(ValueLeft->Data == ValueRight->Data);
        else if (std::strcmp(Operator, "!=") == 0)
            return new Type::Bool(ValueLeft->Data != ValueRight->Data); 
        else
            return NewError(CreateErrorMessage(Type::ERROR_UNKNOWN_OPERATOR.What, Operator, Object::ObjectTypeToString(Right->Type)));
    }

    Object* EvaluateMinusOperatorExpression(Object* Right)
    {
        if (Right->Type == ObjectType::Int32)
        {
            Type::Int32* Int32 = (Type::Int32*)Right;
            return new Type::Int32(-Int32->Data);
        }
        else if (Right->Type == ObjectType::Bool)
        {
            Type::Bool* Bool = (Type::Bool*)Right;
            return new Type::Bool(Bool->Data ? false : true);
        }
        return NewError(CreateErrorMessage(Type::ERROR_UNKNOWN_OPERATOR.What, "-", Object::ObjectTypeToString(Right->Type)));
    }

    Object* EvaluatePrefixExpression(const char* Operator, Object* Right)
    {
        if (std::strcmp("!", Operator) == 0)
            return EvaluateBangExpression(Right);
        else if (std::strcmp("-", Operator) == 0)
            return EvaluateMinusOperatorExpression(Right);
        return NewError(CreateErrorMessage(Type::ERROR_UNKNOWN_OPERATOR.What, Operator, Object::ObjectTypeToString(Right->Type)));
    }

    template<typename... TArgs>
    const char* CreateErrorMessage(const char* Message, TArgs&&... Args)
    {
        const char* Used = "Error at line %i: ";
        char* Buffer = (char*)calloc(strlen(Used), sizeof(char));
        sprintf(Buffer, Used, Line);
        Buffer = (char*)realloc(Buffer, (strlen(Buffer) + strlen(Message)) * sizeof(char));
        sprintf(Buffer, Message, Buffer, std::forward<TArgs>(Args)...);
        return Buffer;
    }

    Type::Error* NewError(const char* Message)
    {
        return new Type::Error(Message);
    }

}
