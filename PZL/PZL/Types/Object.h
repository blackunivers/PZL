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
	template<typename TTS = const char*>
	struct Object
	{
		// Object Type
		ObjectType Type;

		// Returns the object as a string
		virtual TTS ToString() const = 0;
	};
}