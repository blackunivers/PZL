#pragma once

namespace PZL
{
	// Represents object types.
	enum class ObjectType
	{
		Int,
		Bool,
		Char,
		Null,
	};

	// Represents an object.
	template<typename TTS = const char*>
	struct Object
	{
		// Object Type
		ObjectType OType;

		// Returns the object as a string.
		virtual TTS ToString() const = 0;
	};
}