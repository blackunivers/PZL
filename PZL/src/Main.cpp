#include "PCH.h"
#include "PZL.h"

int main(int argc, char** argv)
{
	PZL::Init();
	using namespace PZL::Type;
	using namespace PZL;
	IO::File* SourceFile = PZL::IO::ReadFile(argv[1]);
	
	PZL::Parser* Parser = new PZL::Parser(SourceFile->Data);

	auto Program = Parser->ParseProgram();

	if (Parser->Errors.size() > 0)
	{
		for (auto error : Parser->Errors)
			std::cout << error << '\n';
		return -1;
	}

	std::cout << Program->ToString();

	delete Program;
	delete Parser;
	delete SourceFile;

	PZL::Exit();
	PZL::System::Memory::Get()->PrintUsed();
	return 0;
}