#pragma once

#include "Types/Object.h"

namespace PZL::Evaluator
{

	struct Environment
	{
	public:
		Environment()
		{

		}

		~Environment()
		{
			for (auto&[Key, Var] : StorageVar)
				delete Var;
			for (auto&[Key, Func] : StorageFunctions)
				delete Func;
		}

	public:
		std::unordered_map<std::string, Object*> StorageVar;
		std::unordered_map<const char*, Object*> StorageFunctions;
	};
}