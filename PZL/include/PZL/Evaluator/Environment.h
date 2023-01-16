#pragma once

#include "PZL/Types/Object.h"
#include "PZL/Evaluator/Function/Function.h"
#include "PZL/Evaluator/Var/Var.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace PZL
{

	struct Environment
	{
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

		std::unordered_map<std::string, Var*> StorageVar;
		std::unordered_map<std::string, Function*> StorageFunctions;
	};
}