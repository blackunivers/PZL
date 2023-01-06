#include "PCH.h"
#include "PZL/PZL.h"

int main(int argc, char** argv)
{
	PZL::Init();
	using namespace PZL::Type;
#if 1
	PZL::IO::File* SourceFile = PZL::IO::ReadFile(argv[1]);
	
	PZL::Parser* Parser = new PZL::Parser(SourceFile->Data);
	PZL::System::Memory::Get()->PrintUsed();
	auto Program = Parser->ParseProgram();
	PZL::System::Memory::Get()->PrintUsed();

	/*auto Env = new PZL::Evaluator::Environment;
	auto Result = PZL::Evaluator::Evaluate(Program, Env);
	std::cout << Result->ToString() << '\n';
	if (PZL::Evaluator::TypeEvaluation == PZL::Evaluator::Context::Var)
		if (Result->Type == PZL::ObjectType::Null || Result->Type == PZL::ObjectType::Error)
			delete Result;
	else if (PZL::Evaluator::TypeEvaluation == PZL::Evaluator::Context::Expression)
		delete Result;
	PZL::System::Memory::Get()->PrintUsed();
	delete Env;
	PZL::System::Memory::Get()->PrintUsed();*/

	delete Program;
	PZL::System::Memory::Get()->PrintUsed();
	delete Parser;
	PZL::System::Memory::Get()->PrintUsed();
	delete SourceFile;
	PZL::System::Memory::Get()->PrintUsed();
#else
	{
		std::string Src;
		std::cout << "> ";
		std::getline(std::cin, Src);
		std::cout << "OnInput: ";
		PZL::System::Memory::Get()->PrintUsed();
		auto Env = new PZL::Evaluator::Environment();

		while (Src != "exit()")
		{
			PZL::Parser* Parser = new PZL::Parser(Src.c_str());
			std::cout << "OnPostCreateLexerAndParser: ";
			PZL::System::Memory::Get()->PrintUsed();
			auto Program = Parser->ParseProgram();
			std::cout << "OnPostCreateProgram: ";
			PZL::System::Memory::Get()->PrintUsed();

			auto Result = PZL::Evaluator::Evaluate(Program, Env);
			std::cout << "OnPostCreateResult: ";
			PZL::System::Memory::Get()->PrintUsed();
			std::cout << Result->ToString() << '\n';
			PZL::System::Memory::Get()->PrintUsed();
			if (PZL::Evaluator::TypeEvaluation == PZL::Evaluator::Context::Var)
			{
				if (Result->Type == PZL::ObjectType::Null || Result->Type == PZL::ObjectType::Error)
				{
					delete Result;
					std::cout << "OnPostDestroyResult: ";
					PZL::System::Memory::Get()->PrintUsed();
				}
			}
			else if (PZL::Evaluator::TypeEvaluation == PZL::Evaluator::Context::Expression)
			{
				delete Result;
				std::cout << "OnPostDestroyResult: ";
				PZL::System::Memory::Get()->PrintUsed();
			}


			delete Program;
			std::cout << "OnPostDestoryProgram: ";
			PZL::System::Memory::Get()->PrintUsed();
			delete Parser;
			std::cout << "OnPostDestroyLexerAndParser: ";
			PZL::System::Memory::Get()->PrintUsed();

			Src.clear();

			std::cout << "> ";
			std::getline(std::cin, Src);
			std::cout << "OnInput: ";
			PZL::System::Memory::Get()->PrintUsed();

		}

		delete Env;
		std::cout << "OnPostDestroyEnv: ";
		PZL::System::Memory::Get()->PrintUsed();
	}
#endif
	PZL::Exit();
	std::cout << "OnExit: ";
	PZL::System::Memory::Get()->PrintUsed();
	return 0;
}