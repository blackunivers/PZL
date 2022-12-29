#pragma once

namespace PZL::AST
{
	struct ASTNode;
	struct Expression;
	struct Statement;

	struct Integer;
	struct Boolean;
	struct Prefix;
	struct Infix;

	struct VarStatement;
	struct ExpressionStatement;

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
	public:
		std::vector<const char*> Errors;
	private:
		void _DefineVarTypes();
		void _InitPrecedences();
		void _Advance();
		Precedence _CurrentPrecedence();
		AST::Expression* _ParseExpression(Precedence P, TokenType Type);
		AST::ExpressionStatement* _ParseExpressionStatement();
		AST::Statement* _ParseStatement();
		AST::VarStatement* _ParseVarStatement(TokenType VarType);
		bool _ExpectedToken(TokenType Type);
		void _ExpectedError(TokenType Type);
		Precedence _PeekPrecedence();
		PrefixParseFns _RegisterPrefixFns();
		InfixParseFns _RegisterInfixFns();
	private:
		Lexer* _Lexer;

		PrefixParseFns _PrefixParseFns;
		InfixParseFns _InfixParseFns;

		Token* _CurrentToken;
		Token* _NextToken;

		std::vector<TokenType> VarTypes;
		std::unordered_map<TokenType, Precedence> Precedences;
	private:
		friend AST::Expression* ParseInteger(Parser* This, TokenType Type);
		friend AST::Expression* ParseBoolean(Parser* This, TokenType Type);
		friend AST::Expression* ParseGroupedExpression(Parser* parser, TokenType);
		friend AST::Expression* ParseIdentifier(Parser* This, TokenType);
		friend AST::Prefix* ParsePrefixExpression(Parser* This, TokenType);
		friend AST::Infix* ParseInfixExpression(Parser* This, AST::Expression* Left);
	};
}