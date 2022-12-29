#pragma once


namespace PZL
{

	enum class Precedence
	{
		LOWEST = 1,
		EQUALS_TO,
		LESSGREATER,
		SUM,
		PRODUCT,
		PREFIX,
		CALL,
	};
}