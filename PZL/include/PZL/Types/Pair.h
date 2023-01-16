#pragma once

#include <iostream>

namespace PZL::Type
{

	template<typename T1, typename T2>
	struct Pair : public Object
	{
	public:
		Pair(T1 First, T2 Second) : First(First), Second(Second)
		{
			Type = ObjectType::Pair;
		}

		~Pair()
		{
		}

	public:
		T1 First;
		T2 Second;
	};
}