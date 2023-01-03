#include "PCH.h"
#include "Parser.h"

#include "Lexer/Token.h"
#include "Lexer/Lexer.h"
#include "Parser/Precedence.h"
#include "Parser/PrefixParseFns.h"
#include "Parser/InfixParseFns.h"

namespace PZL
{

	Parser::Parser(const char* Source)
	{
		Lex = new Lexer(Source);
		InitPrecedences();

		PrefixFns = RegisterPrefixFns();
		InfixFns = RegisterInfixFns();

		Advance();
		Advance();

		DefineVarTypes();
	}

	Parser::~Parser()
	{
		delete Lex;
		PrefixFns.clear();
		InfixFns.clear();
		VarTypes.clear();
		Precedences.clear();
		
		if(CurrentToken != nullptr)
			delete CurrentToken;
		if (NextToken != nullptr)
			delete NextToken;
	}

	AST::Program* Parser::ParseProgram()
	{
		AST::Program* Program = new AST::Program({});

		while (CurrentToken->Type != TokenType::END_OF_FILE)
		{
			AST::Statement* statement = ParseStatement();

			if (statement != nullptr)
				Program->Statements.emplace_back(statement);

			Advance();
		}

		return Program;
	}

	void Parser::DefineVarTypes()
	{
		VarTypes.emplace_back(TokenType::TYPE_VOID);
		VarTypes.emplace_back(TokenType::TYPE_INT);
		VarTypes.emplace_back(TokenType::TYPE_BOOL);
	}

	void Parser::InitPrecedences()
	{
		Precedences[TokenType::EQUALS_TO] = Precedence::EQUALS_TO;
		Precedences[TokenType::NOT_EQUALS] = Precedence::EQUALS_TO;
		Precedences[TokenType::LESS_THAN] = Precedence::LESSGREATER;
		Precedences[TokenType::GREATER_THAN] = Precedence::LESSGREATER;
		Precedences[TokenType::PLUS] = Precedence::SUM;
		Precedences[TokenType::MINUS] = Precedence::SUM;
		Precedences[TokenType::DIVISION] = Precedence::PRODUCT;
		Precedences[TokenType::MULTIPLICATION] = Precedence::PRODUCT;
		Precedences[TokenType::LPAREN] = Precedence::CALL;
	}

	void Parser::Advance()
	{
		CurrentToken = NextToken;
		NextToken = Lex->NextToken();
	}

	Precedence Parser::CurrentPrecedence()
	{
		auto it = Precedences.find(CurrentToken->Type);

		if ((int)it->second)
		{
			return it->second;
		}

		return Precedence::LOWEST;
	}

	AST::Expression* Parser::ParseExpression(Precedence P, TokenType Type)
	{
		PrefixParseFn ppf = PrefixFns[CurrentToken->Type];

		AST::Expression* left_expression = nullptr;
		if (ppf != nullptr)
			left_expression = ppf(this, Type);
		else
		{
			if (CurrentToken->Type == TokenType::ILLEGAL)
				std::cout << "Error at Line " << CurrentToken->Line << ": \n\tAn expression was expected";
			
			exit(-1);
		}

		InfixParseFn ipf;

		while (NextToken->Type != TokenType::SEMICOLON && P < PeekPrecedence())
		{
			auto it = InfixFns.find(NextToken->Type);

			if (it != InfixFns.end())
			{
				ipf = InfixFns[NextToken->Type];
				Advance();

				left_expression = ipf(this, left_expression);
			}
			else
				return left_expression;
		}

		return left_expression;
	}

	AST::ExpressionStatement* Parser::ParseExpressionStatement()
	{
		AST::ExpressionStatement* ES = new AST::ExpressionStatement(new Token(CurrentToken->Type, CurrentToken->Value, CurrentToken->Line));
		ES->Value = ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL);

		if (NextToken->Type == TokenType::SEMICOLON)
		{
			delete NextToken;
			Advance();
		}

		return ES;
	}

	AST::ReturnStatement* Parser::ParseReturnStatement()
	{
		AST::ReturnStatement* RS = new AST::ReturnStatement(CurrentToken);

		Advance();

		RS->Value = ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL);

		if (NextToken->Type == TokenType::SEMICOLON)
		{
			delete NextToken;
			Advance();
		}

		return RS;
	}

	AST::Statement* Parser::ParseStatement()
	{
		for(auto VarType : VarTypes)
			if(CurrentToken->Type == VarType)
				return ParseVarStatement(VarType);
		if (CurrentToken->Type == TokenType::RETURN)
			return ParseReturnStatement();
		else
			return ParseExpressionStatement();
	}

	AST::VarStatement* Parser::ParseVarStatement(TokenType VarType)
	{
		AST::VarStatement* Var = new AST::VarStatement(CurrentToken, CurrentToken->Type);

		if (!ExpectedToken(TokenType::ID))
			return nullptr;

		Var->ID = new AST::Identifier(CurrentToken, CurrentToken->Value);

		if(NextToken->Type == TokenType::SEMICOLON)
		{
			if (VarType == TokenType::TYPE_INT)
				Var->Value = new AST::Integer32(NextToken);
			else if (VarType == TokenType::TYPE_BOOL)
				Var->Value = new AST::Boolean(NextToken);

			Advance();

			return Var;
		}


		if (!ExpectedToken(TokenType::EQUALS))
			return nullptr;
		delete CurrentToken;

		Advance();

		Var->Value = ParseExpression(Precedence::LOWEST, Var->VarType);

		if (NextToken->Type == TokenType::SEMICOLON)
		{
			delete NextToken;
			Advance();
		}

		return Var;
	}

	bool Parser::ExpectedToken(TokenType Type)
	{
		if (NextToken->Type == Type)
		{
			Advance();
			return true;
		}

		ExpectedError(Type);
		return false;
	}

	std::vector<AST::Expression*> Parser::ParseCallArguments()
	{
		std::vector<AST::Expression*> args = {};

		if (NextToken->Type == TokenType::RPAREN)
		{
			delete NextToken;
			Advance();
			return args;
		}

		delete CurrentToken;
		Advance();
		AST::Expression* Expr;
		if (Expr = ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL))
			args.emplace_back(Expr);

		while (NextToken->Type == TokenType::COMMA)
		{
			delete NextToken;
			Advance();
			Advance();

			if (Expr = ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL))
				args.emplace_back(Expr);
		}

		if (!ExpectedToken(TokenType::RPAREN))
			return {};
		delete CurrentToken;

		return args;
	}

	void Parser::ExpectedError(TokenType Type)
	{
		std::stringstream ss;

		std::cout << "Error at line " << NextToken->Line << ": " << "\n\tThe next token was expected to be " << Token::TokenTypeToString(Type) << " but was obtained " << Token::TokenTypeToString(NextToken->Type) << '.';
		exit(-1);
	}

	std::vector<AST::VarStatement*> Parser::ParseFunctionParameters()
	{
		std::vector<AST::VarStatement*> Params;

		if (NextToken->Type == TokenType::RPAREN)
		{
			Advance();
			delete CurrentToken;
			return Params;
		}

		Advance();

		TokenType FristArgumentType = CurrentToken->Type;
		AST::VarStatement* FristArgument = new AST::VarStatement(CurrentToken, CurrentToken->Type);

		if (!ExpectedToken(TokenType::ID))
			return {};

		FristArgument->ID = new AST::Identifier(CurrentToken, CurrentToken->Value);

		if (NextToken->Type == TokenType::EQUALS)
		{
			delete NextToken;
			Advance();
			Advance();

			FristArgument->Value = ParseExpression(Precedence::LOWEST, FristArgumentType);
		}

		Params.emplace_back(FristArgument);

		while (NextToken->Type == TokenType::COMMA)
		{
			delete NextToken;
			Advance();
			Advance();

			TokenType ArgumentType = CurrentToken->Type;
			AST::VarStatement* Argument = new AST::VarStatement(CurrentToken, CurrentToken->Type);

			if (!ExpectedToken(TokenType::ID))
				return {};

			Argument->ID = new AST::Identifier(CurrentToken, CurrentToken->Value);

			if (NextToken->Type == TokenType::EQUALS)
			{
				delete NextToken;
				Advance();
				Advance();

				Argument->Value = ParseExpression(Precedence::LOWEST, ArgumentType);
			}

			Params.emplace_back(Argument);
		}

		if (!ExpectedToken(TokenType::RPAREN))
			return {};
		delete CurrentToken;

		return Params;
	}

	AST::Block* Parser::ParseBlock()
	{
		AST::Block* Block = new AST::Block(CurrentToken);

		Advance();
		while (CurrentToken->Type != TokenType::RBRACE && CurrentToken->Type != TokenType::END_OF_FILE)
		{
			AST::Statement* statement = ParseStatement();

			if (statement != nullptr)
				Block->Statements.emplace_back(statement);

			Advance();
		}
		delete CurrentToken;
		if(NextToken->Type == TokenType::RBRACE)
		{
			Advance();
			delete CurrentToken;
		}

		return Block;
	}

	Precedence Parser::PeekPrecedence()
	{
		return Precedences[NextToken->Type];
	}

	PrefixParseFns Parser::RegisterPrefixFns()
	{
		static PrefixParseFns Fns = DefinePrefixFns();
		return Fns;
	}

	InfixParseFns Parser::RegisterInfixFns()
	{
		static InfixParseFns Fns = DefineInfixFns();
		return Fns;
	}

}