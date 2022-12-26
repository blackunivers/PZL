#include "PCH.h"
#include "Types/Int.h"

int main()
{
	PZL::Type::Int32 MyData = 300;

	std::cout << MyData.ToString();

	return 0;
}