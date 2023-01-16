#include "PCH.h"
#include "PZL/Evaluator/Evaluator.h"

#include "PZL/Parser/AST/Expression.h"
#include "PZL/Parser/AST/Statement.h"
#include "PZL/Lexer/Token.h"
#include "PZL/Types/Global.h"
#include "PZL/Types/Error.h"
#include "PZL/Evaluator/Environment.h"

namespace PZL
{

	template<typename... TArg>
	Error* CreateError(ErrorType ErrType, const char* Message, TArg&&... ARGS)
	{
		char* Buffer = (char*)calloc(strlen(Message), sizeof(char));
		sprintf(Buffer, Message, std::forward<TArg>(ARGS)...);

		return new Error(Buffer, ErrType);
	}

	Evaluator::Evaluator()
	{
		GlobalEnvironment = new Environment;

		GlobalEnvironment->StorageVar["VERSION"] = new Var("VERSION", new Type::UInt16(1000), ObjectType::UInt16);
	}

	Evaluator::~Evaluator()
	{
		delete GlobalEnvironment;
	}

	Object* Evaluator::EvaluateProgram(AST::Program* Program)
	{
		for (auto Statement : Program->Statements)
		{
			CurrentContext[0] = Context::PreEvaluation;
			auto Result = EvaluateStatement(Statement);

			if (CurrentContext[1] == Context::ReturnStatement)
			{
				delete Result;
				return new Error(ERROR::StatementExpected.What, ErrorType::StatementExpected);
			}
			else if (Result->Type != ObjectType::Error && Result->Type != ObjectType::Null)
			{
				delete Result;
				return new Error(ERROR::StatementExpected.What, ErrorType::StatementExpected);
			}

			ShowErrorAndExit(Result);
		}

		CurrentContext = { Context::PreEvaluation, Context::OperationExpression, Context::OperationExpression };
		return new Type::Null;
	}

	Object* Evaluator::EvaluateStatement(AST::Statement* Statement)
	{
		switch (Statement->Type())
		{
		case AST::ASTNodeType::ExpressionStatement:
			{
				AST::ExpressionStatement* ES = (AST::ExpressionStatement*)Statement;
				CurrentLine = ES->Line;
				return EvaluateExpression(ES->Value);
			}
		case AST::ASTNodeType::ReturnStatement:
			{
				AST::ReturnStatement* RS = (AST::ReturnStatement*)Statement;
				CurrentLine = RS->Line;
				CurrentContext[1] = Context::ReturnStatement;
				if (RS->Value->Type() == AST::ASTNodeType::Identifier)
					CurrentContext[2] = Context::ReturnStatementID;
				return EvaluateExpression(RS->Value);
			}
		case AST::ASTNodeType::VarStatement:
			{
				AST::VarStatement* VS = (AST::VarStatement*)Statement;
				CurrentLine = VS->Line;
				CurrentContext[1] = Context::VariableStatement;

				auto it = GlobalEnvironment->StorageVar.find(VS->ID->ID);
				if (it != GlobalEnvironment->StorageVar.end())
				{
					std::cout << "Error at line " << CurrentLine << ":\n\t" << "New definition for '" << Object::ObjectTypeToString(Object::TokenTypeToObjectType(VS->VarType)) << ' ' << VS->ID->ID << "'.";
					exit(-1);
				}
				else
				{
					GlobalEnvironment->StorageVar[VS->ID->ID] = new Var(VS->ID->ID, nullptr, Object::TokenTypeToObjectType(VS->VarType));
					Object* Value = EvaluateExpression(VS->Value);
					if (Value->Type == Object::TokenTypeToObjectType(VS->VarType))
						GetVarByName(VS->ID->ID)->Value = Value;
					else
					{
						switch (Object::TokenTypeToObjectType(VS->VarType))
						{
						case ObjectType::Int8:
							GetVarByName(VS->ID->ID)->Value = new Type::Int8((char)((Type::Int64*)Value)->Data);
							break;
						case ObjectType::UInt8:
							GetVarByName(VS->ID->ID)->Value = new Type::UInt8((unsigned char)((Type::UInt64*)Value)->Data);
							break;
						case ObjectType::Int16:
							GetVarByName(VS->ID->ID)->Value = new Type::Int16((short)((Type::Int64*)Value)->Data);
							break;
						case ObjectType::UInt16:
							GetVarByName(VS->ID->ID)->Value = new Type::UInt16((unsigned short)((Type::UInt64*)Value)->Data);
							break;
						case ObjectType::Int32:
							GetVarByName(VS->ID->ID)->Value = new Type::Int32((int)((Type::UInt64*)Value)->Data);
							break;
						case ObjectType::UInt32:
							GetVarByName(VS->ID->ID)->Value = new Type::UInt32((unsigned int)((Type::Int64*)Value)->Data);
							break;
						case ObjectType::Int64:
							GetVarByName(VS->ID->ID)->Value = new Type::Int64((long long)((Type::Int64*)Value)->Data);
							break;
						case ObjectType::UInt64:
							GetVarByName(VS->ID->ID)->Value = new Type::UInt64((long long)((Type::UInt64*)Value)->Data);
							break;
						case ObjectType::Float32:
							if (Value->Type == ObjectType::Float32)
								GetVarByName(VS->ID->ID)->Value = new Type::Float64(((Type::Float32*)Value)->Data);
							else if (Value->Type == ObjectType::Float64)
								GetVarByName(VS->ID->ID)->Value = new Type::Float64(((Type::Float64*)Value)->Data);
							break;
						case ObjectType::Float64:
							if (Value->Type == ObjectType::Float32)
								GetVarByName(VS->ID->ID)->Value = new Type::Float64(((Type::Float32*)Value)->Data);
							else if (Value->Type == ObjectType::Float64)
								GetVarByName(VS->ID->ID)->Value = new Type::Float64(((Type::Float64*)Value)->Data);
							break;
						case ObjectType::Bool:
							GetVarByName(VS->ID->ID)->Value = new Type::Bool(((Type::Bool*)Value)->Data);
							break;
						}
						delete Value;
					}
					CurrentContext[1] = Context::OperationExpression;
				}
			}
		}

		return new Type::Null;
	}

	Object* Evaluator::EvaluateExpression(AST::Expression* Expression)
	{
		switch (Expression->Type())
		{
		case AST::ASTNodeType::Function:
		{
			AST::Function* Func = (AST::Function*)Expression;
			CurrentLine = Func->Line;

			auto it = GlobalEnvironment->StorageFunctions.find(Func->FunctionName->ID);
			if (it != GlobalEnvironment->StorageFunctions.end())
			{
				if (it->second->IsDefined && Func->IsDefined)
				{
					std::cout << "Error at line " << CurrentLine << ":\n\t" << "The '" << Func->FunctionName->ID << "' type '" << Object::ObjectTypeToString(Object::TokenTypeToObjectType(Func->FunctionType)) << "' function is already defined.";
					exit(-1);
				}
				else if (!it->second->IsDefined && Func->IsDefined)
				{
					GetFunctionByName(Func->FunctionName->ID)->IsDefined = true;
					GetFunctionByName(Func->FunctionName->ID)->Body = Func->Body->Statements;
				}
			}
			else
			{
				GlobalEnvironment->StorageFunctions[Func->FunctionName->ID] = new Function(Object::TokenTypeToObjectType(Func->FunctionType), Func->IsDefined, Func->FunctionName->ID, std::move(Func->Body->Statements));
			}
		}
		break;
		case AST::ASTNodeType::Boolean:
			CurrentLine = ((AST::Boolean*)Expression)->Line;
			return new Type::Bool(((AST::Boolean*)Expression)->Value);
		case AST::ASTNodeType::Integer8:
			CurrentLine = ((AST::Integer8*)Expression)->Line;
			return new Type::Int8(((AST::Integer8*)Expression)->Value);
		case AST::ASTNodeType::UnsignedInteger8:
			CurrentLine = ((AST::UnsignedInteger8*)Expression)->Line;
			return new Type::UInt8(((AST::UnsignedInteger8*)Expression)->Value);
		case AST::ASTNodeType::Integer16:
			CurrentLine = ((AST::Integer16*)Expression)->Line;
			return new Type::Int16(((AST::Integer16*)Expression)->Value);
		case AST::ASTNodeType::UnsignedInteger16:
			CurrentLine = ((AST::UnsignedInteger16*)Expression)->Line;
			return new Type::UInt16(((AST::UnsignedInteger16*)Expression)->Value);
		case AST::ASTNodeType::Integer32:
			CurrentLine = ((AST::Integer32*)Expression)->Line;
			return new Type::Int32(((AST::Integer32*)Expression)->Value);
		case AST::ASTNodeType::UnsignedInteger32:
			CurrentLine = ((AST::UnsignedInteger32*)Expression)->Line;
			return new Type::UInt32(((AST::UnsignedInteger32*)Expression)->Value);
		case AST::ASTNodeType::Integer64:
			CurrentLine = ((AST::Integer64*)Expression)->Line;
			return new Type::Int64(((AST::Integer64*)Expression)->Value);
		case AST::ASTNodeType::UnsignedInteger64:
			CurrentLine = ((AST::UnsignedInteger64*)Expression)->Line;
			return new Type::UInt64(((AST::UnsignedInteger64*)Expression)->Value);
		case AST::ASTNodeType::Float32:
			CurrentLine = ((AST::Float32*)Expression)->Line;
			return new Type::Float32(((AST::Float32*)Expression)->Value);
		case AST::ASTNodeType::Float64:
			CurrentLine = ((AST::Float64*)Expression)->Line;
			return new Type::Float64(((AST::Float64*)Expression)->Value);
		case AST::ASTNodeType::Infix:
			{
				AST::Infix* Infix = (AST::Infix*)Expression;
				CurrentLine = Infix->Line;

				Object* Right = EvaluateExpression(Infix->Right);
				Object* Left = EvaluateExpression(Infix->Left);

				Object* Result = EvaluateInfix(Right, Infix->Operator, Left);

				
				if (Infix->Right->Type() != AST::ASTNodeType::Identifier)
					delete Right;
				if (Infix->Left->Type() != AST::ASTNodeType::Identifier)
					delete Left;

				return Result;
			}
		case AST::ASTNodeType::Identifier:
			{
				AST::Identifier* ID = (AST::Identifier*)Expression;
				CurrentLine = ID->Line;

				return EvaluateID(ID->ID);
			}
		}

		return new Type::Null;
	}

	Object* Evaluator::EvaluateInfix(Object* Right, const char* Operator, Object* Left)
	{
		if (Object::IsInteger(Right->Type) && Object::IsInteger(Left->Type))
			return EvaluateIntegerOperation(Right, Operator, Left);
		if (Object::IsFloat(Right->Type) && Object::IsFloat(Left->Type))
			return EvaluateFloatOperation(Right, Operator, Left);

		return new Type::Null;
	}

	Object* Evaluator::EvaluateID(const char* ID)
	{
		auto it = GlobalEnvironment->StorageVar.find(ID);
		if (it != GlobalEnvironment->StorageVar.end())
		{
			return it->second->Value;
		}

		return CreateError(ErrorType::UndefinedReference, ERROR::UndefinedReference.What, ID);
	}

	Object* Evaluator::EvaluateBlock(std::vector<AST::Statement*> Statements)
	{
		for (auto Statement : Statements)
		{
			auto Value = EvaluateStatement(Statement);
			ShowErrorAndExit(Value);

			if (CurrentContext[1] == Context::ReturnStatement && CurrentContext[0] == Context::FunctionExpression)
				return Value;
			else if (CurrentContext[1] == Context::ReturnStatement)
				return CreateError(ErrorType::StatementExpected, ERROR::UndefinedReference.What);
		}

		return new Type::Null;
	}

	Object* Evaluator::ExecuteFunction(const char* FunctionName)
	{
		auto it = GlobalEnvironment->StorageFunctions.find(FunctionName);

		if (it != GlobalEnvironment->StorageFunctions.end())
		{
			CurrentContext[0] = Context::FunctionExpression;
			Object* ReturnValue = EvaluateBlock(GetFunctionByName(FunctionName)->Body);
			if (ReturnValue->Type == GetFunctionByName(FunctionName)->ReturnType)
				return ReturnValue;
			else
				if (Object::IsNumber(ReturnValue->Type) && Object::IsNumber(GetFunctionByName(FunctionName)->ReturnType))
					return ReturnValue;
				else
					return CreateError(ErrorType::ErrorType, ERROR::ErrorType.What, Object::ObjectTypeToString(ReturnValue->Type), Object::ObjectTypeToString(GetFunctionByName(FunctionName)->ReturnType));
		}

		return CreateError(ErrorType::UndefinedReference,ERROR::UndefinedReference.What, FunctionName);
	}

	void Evaluator::ShowErrorAndExit(Object* E)
	{
		if (E->Type == ObjectType::Error && ((Error*)E)->ErrType != ErrorType::SUCCESS)
		{
			std::cout << "Error at line " << CurrentLine << ":\n\t" << ((Error*)E)->What;
			exit(-1);
		}

		if (E->Type == ObjectType::Null)
		{
			delete E;
			E = NULL;
		}
	}

	Var* Evaluator::GetVarByName(const char* ID)
	{
		return GlobalEnvironment->StorageVar[ID];
	}

	Function* Evaluator::GetFunctionByName(const char* ID)
	{
		return GlobalEnvironment->StorageFunctions[ID];
	}

}
