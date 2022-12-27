#include "PCH.h"
#include "PZL.h"

int main()
{
	using namespace PZL::Type;
	using namespace PZL;

	PZL::IO::File* SourceFile = PZL::IO::ReadFile("examples/Main.pz");
	
	const char* Source = SourceFile->Data;

	PZL::Token* TK;
	PZL::Lexer* Lexer = new PZL::Lexer(Source);

	while ((TK = Lexer->NextToken())->Type != TokenType::END_OF_FILE)
	{
		std::cout << TK->ToString() << "\n";
	}

	std::cout << PZL::System::Memory::Get()->MemoryUsedTotal;

	delete TK;
	delete Lexer;

	return 0;
}