#pragma once

namespace PZL::AST
{
	struct ASTNode;
	struct Expression;
	struct Statement;

	struct Boolean;
	struct Prefix;
	struct Infix;

	struct VarStatement;
	struct ExpressionStatement;
	struct Block;
	struct ReturnStatement;

	struct Program;
}

namespace PZL
{

	enum class Precedence;
	
	enum class TokenType;
	struct Token;

	class Lexer;
	class Parser;

	using PrefixParseFn = AST::Expression*(*)(Parser*, TokenType);
	using InfixParseFn = AST::Expression*(*)(Parser*, AST::Expression* Expr);

	using PrefixParseFns = std::unordered_map<TokenType, PrefixParseFn>;
	using InfixParseFns = std::unordered_map<TokenType, InfixParseFn>;

	class Parser
	{
	public:
		Parser(const char* Source);
		~Parser();

		AST::Program* ParseProgram();

		void DefineVarTypes();
		void InitPrecedences();
		void Advance(); 

		Precedence CurrentPrecedence(); 
		Precedence PeekPrecedence();

		AST::Expression* ParseExpression(Precedence P, TokenType Type);
		
		AST::ExpressionStatement* ParseExpressionStatement();
		AST::ReturnStatement* ParseReturnStatement();
		AST::Statement* ParseStatement();
		AST::VarStatement* ParseVarStatement(TokenType VarType);
		
		bool ExpectedToken(TokenType Type);
		void ExpectedError(TokenType Type);
		
		std::vector<AST::Expression*> ParseCallArguments();
		std::vector<AST::VarStatement*> ParseFunctionParameters();
		AST::Block* ParseBlock();

		PrefixParseFns RegisterPrefixFns();
		InfixParseFns RegisterInfixFns();
	public:
		Lexer* Lex;

		PrefixParseFns PrefixFns;
		InfixParseFns InfixFns;

		Token* CurrentToken;
		Token* NextToken;

		std::vector<TokenType> VarTypes;
		std::unordered_map<TokenType, Precedence> Precedences;
	public:
		static AST::Expression* ParseInteger(Parser* This, TokenType Type);
		static AST::Expression* ParseFloat(Parser* This, TokenType Type);
		static AST::Expression* ParseBoolean(Parser* This, TokenType Type);
		static AST::Expression* ParseGroupedExpression(Parser* This, TokenType);
		static AST::Expression* ParseIdentifier(Parser* This, TokenType);
		static AST::Prefix* ParsePrefixExpression(Parser* This, TokenType);
		static AST::Expression* ParseFunction(Parser* This, TokenType);
		static AST::Expression* ParseIf(Parser* This, TokenType);
		static AST::Infix* ParseInfixExpression(Parser* This, AST::Expression* Left);
		static AST::Expression* ParseCall(Parser* This, AST::Expression* Fn);
	};

}