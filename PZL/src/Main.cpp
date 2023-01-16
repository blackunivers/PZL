#include "PCH.h"
#include "PZL/PZL.h"

#include <__msvc_int128.hpp>

int main(int argc, char** argv)
{
	PZL::Init();
	using namespace PZL;
	PZL::IO::File* SourceFile = PZL::IO::ReadFile(argv[1]);

	PZL::Parser* Parser;
	if (SourceFile->IsValid)
		Parser = new PZL::Parser(SourceFile->Data);
	else
		exit(-1);

	auto Program = Parser->ParseProgram();

	auto Eval = new Evaluator();
	auto Val = Eval->EvaluateProgram(Program);
	Eval->ShowErrorAndExit(Val);
	
	delete Program;
	delete Parser;
	delete SourceFile;

	auto Result = Eval->ExecuteFunction("Main");
	Eval->ShowErrorAndExit(Result);
	Type::UInt8* ReturnValue = (Type::UInt8*)Result;
	std::cout << "Exit with value " <<  int(ReturnValue->Data) << ".\n";
	if(Eval->CurrentContext[2] != Evaluator::Context::ReturnStatementID)
		delete Result;

	delete Eval;
	return 0; 
}