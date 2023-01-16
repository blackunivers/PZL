#include "PCH.h"
#include "PZL/Evaluator/Evaluator.h"

#define PZL_EVALUATOR_OPERATION_FLOAT(F, R, L, RT, LT, O) { RT a = Object::As<RT>(R); LT b = Object::As<LT>(L); return new F(a->Data O b->Data); }
#define PZL_EVALUATOR_OPERATION_INT(R, L, RT, LT, O) { RT a = Object::As<RT>(R); LT b = Object::As<LT>(L); return (a->operator##O(b)); }
#define PZL_EVALUATOR_OPERATION_BOOL(V, R, L, RT, LT, O) { RT a = Object::As<RT>(R); LT b = Object::As<LT>(L); return new Type::Bool(a->operator##O(b)); }


namespace PZL
{

	Object* Evaluator::EvaluateIntegerOperation(Object* Right, const char* Operator, Object* Left)
	{
		if (std::strcmp(Operator, "+") == 0)
		{
			if (Object::IsSigned(Right->Type) && Object::IsSigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::Int64*, Type::Int64*, +);
			if (Object::IsSigned(Right->Type) && Object::IsUnsigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::Int64*, Type::UInt64*, +);
			if (Object::IsUnsigned(Right->Type) && Object::IsSigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::UInt64*, Type::Int64*, +);
			if (Object::IsUnsigned(Right->Type) && Object::IsUnsigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::UInt64*, Type::UInt64*, +);
		}
		if (std::strcmp(Operator, "-") == 0)
		{
			if (Object::IsSigned(Right->Type) && Object::IsSigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::Int64*, Type::Int64*, -);
			if (Object::IsSigned(Right->Type) && Object::IsUnsigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::Int64*, Type::UInt64*, -);
			if (Object::IsUnsigned(Right->Type) && Object::IsSigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::UInt64*, Type::Int64*, -);
			if (Object::IsUnsigned(Right->Type) && Object::IsUnsigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::UInt64*, Type::UInt64*, -);
		}
		if (std::strcmp(Operator, "*") == 0)
		{
			if (Object::IsSigned(Right->Type) && Object::IsSigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::Int64*, Type::Int64*, *);
			if (Object::IsSigned(Right->Type) && Object::IsUnsigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::Int64*, Type::UInt64*, *);
			if (Object::IsUnsigned(Right->Type) && Object::IsSigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::UInt64*, Type::Int64*, *);
			if (Object::IsUnsigned(Right->Type) && Object::IsUnsigned(Left->Type))
				PZL_EVALUATOR_OPERATION_INT(Right, Left, Type::UInt64*, Type::UInt64*, *);
		}
		if (std::strcmp(Operator, "/") == 0)
			PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float64*, Type::Float64*, /);
		if (std::strcmp(Operator, "==") == 0)
		{
			if (Object::IsSigned(Right->Type) && Object::IsSigned(Left->Type))
				PZL_EVALUATOR_OPERATION_BOOL(Type::Bool, Right, Left, Type::Bool*, Type::Bool*, == );
			if (Object::IsSigned(Right->Type) && Object::IsUnsigned(Left->Type))
				PZL_EVALUATOR_OPERATION_BOOL(Type::Bool, Right, Left, Type::Bool*, Type::Bool*, == );
			if (Object::IsUnsigned(Right->Type) && Object::IsSigned(Left->Type))
				PZL_EVALUATOR_OPERATION_BOOL(Type::Bool, Right, Left, Type::Bool*, Type::Bool*, == );
			if (Object::IsUnsigned(Right->Type) && Object::IsUnsigned(Left->Type))
				PZL_EVALUATOR_OPERATION_BOOL(Type::Bool, Right, Left, Type::Bool*, Type::Bool*, == );
		}
		if (std::strcmp(Operator, "!=") == 0)
		{
			if (Object::IsSigned(Right->Type) && Object::IsSigned(Left->Type))
				PZL_EVALUATOR_OPERATION_BOOL(Type::Bool, Right, Left, Type::Bool*, Type::Bool*, != );
			if (Object::IsSigned(Right->Type) && Object::IsUnsigned(Left->Type))
				PZL_EVALUATOR_OPERATION_BOOL(Type::Bool, Right, Left, Type::Bool*, Type::Bool*, != );
			if (Object::IsUnsigned(Right->Type) && Object::IsSigned(Left->Type))
				PZL_EVALUATOR_OPERATION_BOOL(Type::Bool, Right, Left, Type::Bool*, Type::Bool*, != );
			if (Object::IsUnsigned(Right->Type) && Object::IsUnsigned(Left->Type))
				PZL_EVALUATOR_OPERATION_BOOL(Type::Bool, Right, Left, Type::Bool*, Type::Bool*, != );
		}

		return new Type::Null;
	}

	Object* Evaluator::EvaluateFloatOperation(Object* Right, const char* Operator, Object* Left)
	{
		if (std::strcmp(Operator, "+") == 0)
		{
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float32*, Type::Float32*, +);
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float32*, Type::Float64*, +);
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float64*, Type::Float32*, +);
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float64*, Type::Float64*, +);
		}
		if (std::strcmp(Operator, "-") == 0)
		{
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float32*, Type::Float32*, -);
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float32*, Type::Float64*, -);
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float64*, Type::Float32*, -);
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float64*, Type::Float64*, -);
		}
		if (std::strcmp(Operator, "*") == 0)
		{
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float32*, Type::Float32*, *);
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float32*, Type::Float64*, *);
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float64*, Type::Float32*, *);
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float64*, Type::Float64*, *);
		}
		if (std::strcmp(Operator, "/") == 0)
		{
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float32, Right, Left, Type::Float32*, Type::Float32*, / );
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float32*, Type::Float64*, / );
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float64*, Type::Float32*, / );
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Float64, Right, Left, Type::Float64*, Type::Float64*, / );
		}
		if (std::strcmp(Operator, "==") == 0)
		{
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Bool, Right, Left, Type::Float32*, Type::Float32*, ==);
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Bool, Right, Left, Type::Float32*, Type::Float64*, ==);
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Bool, Right, Left, Type::Float64*, Type::Float32*, ==);
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Bool, Right, Left, Type::Float64*, Type::Float64*, ==);
		}
		if (std::strcmp(Operator, "!=") == 0)
		{
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Bool, Right, Left, Type::Float32*, Type::Float32*, != );
			if (Right->Type == ObjectType::Float32 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Bool, Right, Left, Type::Float32*, Type::Float64*, != );
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float32)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Bool, Right, Left, Type::Float64*, Type::Float32*, != );
			if (Right->Type == ObjectType::Float64 && Left->Type == ObjectType::Float64)
				PZL_EVALUATOR_OPERATION_FLOAT(Type::Bool, Right, Left, Type::Float64*, Type::Float64*, != );
		}

		return new Type::Null;
	}

}