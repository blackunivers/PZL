#pragma once

namespace PZL
{

	enum class TokenType;

	// Represents object types.
	enum class ObjectType
	{
		Null = -1,
		Error = -2,

		Int8 = 1,
		UInt8,
		Int16,
		UInt16,
		Int32,
		UInt32,
		Int64,
		UInt64,
		Float32,
		Float64,
		Bool,


		Pair,
		StaticArray,
	};

	// Represents an object.
	struct Object
	{
	public:
		Object() {};
		virtual ~Object() {}
	public:
		// Object Type
		ObjectType Type;
	public:
		virtual Object* operator+(Object*) { return 0; }
		virtual Object* operator-(Object*) { return 0; }
		virtual Object* operator*(Object*) { return 0; }
		virtual Object* operator/(Object*) { return 0; };
		virtual bool operator==(Object*) { return 0; }
		virtual bool operator!=(Object*) { return 0; }
	public:
		static ObjectType TokenTypeToObjectType(TokenType Type);

		static const char* ObjectTypeToString(ObjectType Type);

		template<typename To>
		static To As(Object* Input);

		static bool IsNumber(ObjectType Type);
		static bool IsInteger(ObjectType Type);
		static bool IsFloat(ObjectType Type);
		static bool IsSigned(ObjectType Type);
		static bool IsUnsigned(ObjectType Type);

	};

	template<typename To>
	inline To Object::As(Object* Input) 
	{ 
		return ((To)Input); 
	}

}