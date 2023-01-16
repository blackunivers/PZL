#include "PCH.h"
#include "PZL/Types/Object.h"

#include "PZL/Lexer/Token.h"

namespace PZL
{

	ObjectType Object::TokenTypeToObjectType(TokenType Type)
	{
		switch (Type)
		{
		case PZL::TokenType::TYPE_INT8:
			return ObjectType::Int8;
		case PZL::TokenType::TYPE_UINT8:
			return ObjectType::UInt8;
		case PZL::TokenType::TYPE_INT16:
			return ObjectType::Int16;
		case PZL::TokenType::TYPE_UINT16:
			return ObjectType::UInt16;
		case PZL::TokenType::TYPE_INT32:
			return ObjectType::Int32;
		case PZL::TokenType::TYPE_UINT32:
			return ObjectType::UInt32;
		case PZL::TokenType::TYPE_INT64:
			return ObjectType::Int64;
		case PZL::TokenType::TYPE_UINT64:
			return ObjectType::UInt64;
		case PZL::TokenType::TYPE_FLOAT32:
			return ObjectType::Float32;
		case PZL::TokenType::TYPE_FLOAT64:
			return ObjectType::Float64;
		case PZL::TokenType::TYPE_BOOL:
			return ObjectType::Bool;
		}

		return ObjectType::Null;
	}

	const char* Object::ObjectTypeToString(ObjectType Type)
	{
		switch (Type)
		{
		case PZL::ObjectType::Int8:
			return "Int8";
		case PZL::ObjectType::UInt8:
			return "UInt8";
		case PZL::ObjectType::Int16:
			return "Int16";
		case PZL::ObjectType::UInt16:
			return "UInt16";
		case PZL::ObjectType::Int32:
			return "Int32";
		case PZL::ObjectType::UInt32:
			return "UInt32";
		case PZL::ObjectType::Int64:
			return "Int64";
		case PZL::ObjectType::UInt64:
			return "UInt64";
		case PZL::ObjectType::Bool:
			return "Bool";
		case PZL::ObjectType::Float32:
			return "Float32";
		case PZL::ObjectType::Float64:
			return "Float64";
		case PZL::ObjectType::Null:
			return "Null";
		case PZL::ObjectType::Error:
			return "Error";
		}

		return "Unknown";
	}

	bool Object::IsNumber(ObjectType Type)
	{
		switch (Type)
		{
		case PZL::ObjectType::Int8:
		case PZL::ObjectType::UInt8:
		case PZL::ObjectType::Int16:
		case PZL::ObjectType::UInt16:
		case PZL::ObjectType::Int32:
		case PZL::ObjectType::UInt32:
		case PZL::ObjectType::Int64:
		case PZL::ObjectType::UInt64:
		case PZL::ObjectType::Bool:
		case PZL::ObjectType::Float32:
		case PZL::ObjectType::Float64:
			return true;
		}

		return false;
	}

	bool Object::IsInteger(ObjectType Type)
	{
		switch (Type)
		{
		case PZL::ObjectType::Int8:
		case PZL::ObjectType::UInt8:
		case PZL::ObjectType::Int16:
		case PZL::ObjectType::UInt16:
		case PZL::ObjectType::Int32:
		case PZL::ObjectType::UInt32:
		case PZL::ObjectType::Int64:
		case PZL::ObjectType::UInt64:
		case PZL::ObjectType::Bool:
			return true;
		}

		return false;
	}

	bool Object::IsFloat(ObjectType Type)
	{
		switch (Type)
		{
		case PZL::ObjectType::Float32:
		case PZL::ObjectType::Float64:
			return true;
		}

		return false;
	}

	bool Object::IsSigned(ObjectType Type)
	{
		switch (Type)
		{
		case PZL::ObjectType::Int8:
		case PZL::ObjectType::Int16:
		case PZL::ObjectType::Int32:
		case PZL::ObjectType::Int64:
		case PZL::ObjectType::Float32:
		case PZL::ObjectType::Float64:
			return true;
		}
		
		return false;
	}

	bool Object::IsUnsigned(ObjectType Type)
	{
		switch (Type)
		{
		case PZL::ObjectType::UInt8:
		case PZL::ObjectType::UInt16:
		case PZL::ObjectType::UInt32:
		case PZL::ObjectType::UInt64:
			return true;
		}

		return false;
	}

}