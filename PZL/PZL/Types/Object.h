#pragma once

namespace PZL
{
	// Represents object types
	enum class ObjectType
	{
		Int,
		Bool,
		Null,
	};

	// Represents an object
	struct Object
	{
		// Object Type
		ObjectType Type;

		// Returns the object as a string
		virtual const char* ToString() const = 0;
	};
}