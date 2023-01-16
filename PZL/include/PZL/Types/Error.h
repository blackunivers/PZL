#pragma once

#include "PZL/Types/Object.h"

namespace PZL
{

	enum class ErrorType
	{
		NotImplementedYet,
		SUCCESS,
		UndefinedReference,
		StatementExpected,
		ErrorType,
	};

	struct Error : public Object
	{
	public:
		Error(const char* What, ErrorType ErrType);
		~Error();

	public:
		const char* What;

		ErrorType ErrType;
	};

}

namespace PZL::ERROR
{

	inline const Error NotImplementedYet = { "Not implemented yet." , ErrorType::NotImplementedYet};
	inline const Error SUCCESS = { "Success." , ErrorType::SUCCESS };
	inline const Error UndefinedReference = { "Undefined reference to '%s'." ,ErrorType::UndefinedReference};
	inline const Error StatementExpected = { "A statement was expected.", ErrorType::StatementExpected };
	inline const Error ErrorType = { "'%s' cant't convert to '%s'.", ErrorType::ErrorType };
}