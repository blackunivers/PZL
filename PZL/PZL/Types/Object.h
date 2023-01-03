#pragma once

namespace PZL
{
	// Represents object types.
	enum class ObjectType
	{
		Int32 = 1,

		Bool,
		Null,

		Error = -1,
		Return = 4,
		Function,
	};

	// Represents an object.
	struct Object
	{
	public:
		Object() {};
		virtual ~Object() {}

		// Returns the object as a string.
		virtual const char* ToString() const = 0;
	public:
		// Object Type
		ObjectType Type;
	public:
	
		static inline const char* ObjectTypeToString(ObjectType Type)
		{
			switch (Type)
			{
			case ObjectType::Int32:
				return "Int32";
			case ObjectType::Bool:
				return "Bool";
			}

			return "Unknown";
		}
	};

}