#pragma once


namespace PZL::System
{

	class Machine
	{
	public:
		Machine();
		~Machine();

		static Machine* Get();
	public:
		std::vector<const char*> Errors;
	private:
		static Machine* s_Instance;
	};
}