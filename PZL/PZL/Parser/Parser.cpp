#include "PCH.h"
#include "Parser.h"

#include "Parser/AST/AST.h"
#include "Lexer/Token.h"
#include "Lexer/Lexer.h"
#include "Parser/AST/Statement.h"
#include "Parser/AST/Expression.h"
#include "Parser/Precedence.h"

namespace PZL
{

	Parser::Parser(const char* Source)
	{
		_Lexer = new Lexer(Source);
		_InitPrecedences();

		_PrefixParseFns = _RegisterPrefixFns();
		_InfixParseFns = _RegisterInfixFns();

		_DefineVarTypes();
	}

	Parser::~Parser()
	{
		delete _CurrentToken;
		delete _NextToken;
		Errors.clear();
		delete _Lexer;
	}

	AST::Program* Parser::ParseProgram()
	{
		AST::Program* Program = new AST::Program({});

		_Advance();
		_Advance();

		while (_CurrentToken->Type != TokenType::END_OF_FILE)
		{
			AST::Statement* statement = _ParseStatement();

			if (statement != nullptr)
				Program->Statements.emplace_back(statement);

			_Advance();
		}

		return Program;
	}

	void Parser::_DefineVarTypes()
	{
		VarTypes.emplace_back(TokenType::TYPE_VOID);
		VarTypes.emplace_back(TokenType::TYPE_INT);
		VarTypes.emplace_back(TokenType::TYPE_BOOL);
	}

	void Parser::_InitPrecedences()
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

	void Parser::_Advance()
	{
		_CurrentToken = _NextToken;
		_NextToken = _Lexer->NextToken();
	}

	Precedence Parser::_CurrentPrecedence()
	{
		auto it = Precedences.find(_CurrentToken->Type);

		if ((int)it->second)
		{
			return it->second;
		}

		return Precedence::LOWEST;
	}

	AST::Expression* Parser::_ParseExpression(Precedence P, TokenType Type)
	{
		PrefixParseFn ppf = _PrefixParseFns[_CurrentToken->Type];

		AST::Expression* left_expression = nullptr;
		if (ppf != nullptr)
			left_expression = ppf(this, Type);
		else
		{
			std::stringstream ss;
			ss << "No se encontro ninguna funcion para parsear " << _CurrentToken->Value;
			std::string Str = ss.str();

			char* NStr = (char*)calloc(Str.length(), sizeof(char));
			NStr[0] = '\0';
			strcpy(NStr, Str.c_str());

			Errors.emplace_back(NStr);
		}

		InfixParseFn ipf;

		while (_NextToken->Type != TokenType::SEMICOLON && P < _PeekPrecedence())
		{
			auto it = _InfixParseFns.find(_NextToken->Type);

			if (it != _InfixParseFns.end())
			{
				ipf = _InfixParseFns[_NextToken->Type];
				_Advance();

				left_expression = ipf(this, left_expression);
			}
			else
				return left_expression;
		}

		return left_expression;
	}

	AST::ExpressionStatement* Parser::_ParseExpressionStatement()
	{
		AST::ExpressionStatement* ES = new AST::ExpressionStatement(_CurrentToken);
		ES->Value = _ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL);

		if (_NextToken->Type == TokenType::SEMICOLON)
		{
			delete _NextToken;
			_Advance();
		}

		return ES;
	}

	AST::Expression* ParseGroupedExpression(Parser* This, TokenType)
	{
		delete This->_CurrentToken;

		This->_Advance();

		AST::Expression* Expr = This->_ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL);

		if (!This->_ExpectedToken(TokenType::RPAREN))
			return nullptr;
		delete This->_CurrentToken;

		return Expr;
	}

	AST::ReturnStatement* Parser::_ParseReturnStatement()
	{
		AST::ReturnStatement* RS = new AST::ReturnStatement(_CurrentToken);

		_Advance();

		RS->Value = _ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL);

		if (_NextToken->Type == TokenType::SEMICOLON)
		{
			delete _NextToken;
			_Advance();
		}

		return RS;
	}

	AST::Statement* Parser::_ParseStatement()
	{
		for(auto VarType : VarTypes)
			if(_CurrentToken->Type == VarType)
				return _ParseVarStatement(VarType);
		if (_CurrentToken->Type == TokenType::RETURN)
			return _ParseReturnStatement();
		else
			return _ParseExpressionStatement();
	}

	AST::VarStatement* Parser::_ParseVarStatement(TokenType VarType)
	{
		AST::VarStatement* Var = new AST::VarStatement(_CurrentToken, _CurrentToken->Type);

		if (!_ExpectedToken(TokenType::ID))
			return nullptr;

		Var->ID = new AST::Identifier(_CurrentToken, _CurrentToken->Value);

		if(_NextToken->Type == TokenType::SEMICOLON)
		{
			if (VarType == TokenType::TYPE_INT)
				Var->Value = new AST::Integer(_NextToken);
			else if (VarType == TokenType::TYPE_BOOL)
				Var->Value = new AST::Boolean(_NextToken);

			_Advance();

			return Var;
		}


		if (!_ExpectedToken(TokenType::EQUALS))
			return nullptr;
		delete _CurrentToken;

		_Advance();

		Var->Value = _ParseExpression(Precedence::LOWEST, Var->VarType);

		if (_NextToken->Type == TokenType::SEMICOLON)
		{
			delete _NextToken;
			_Advance();
		}

		return Var;
	}

	AST::Infix* ParseInfixExpression(Parser* This, AST::Expression* Left)
	{
		AST::Infix* Infix = new AST::Infix(This->_CurrentToken, Left, This->_CurrentToken->Value);

		Precedence P = This->_CurrentPrecedence();

		This->_Advance();

		Infix->Right = This->_ParseExpression(P, TokenType::ILLEGAL);

		return Infix;
	}

	AST::Expression* ParseFunction(Parser* This, TokenType)
	{
		AST::Function* Function = new AST::Function(This->_CurrentToken);

		if (!This->_ExpectedToken(TokenType::ID))
			return nullptr;

		Function->FunctionName = new AST::Identifier(This->_CurrentToken, This->_CurrentToken->Value);

		if (!This->_ExpectedToken(TokenType::LPAREN))
			return nullptr;
		delete This->_CurrentToken;

		Function->Parameters = This->_ParseFunctionParameters();

		if (!This->_ExpectedToken(TokenType::COLON))
			return nullptr;
		delete This->_CurrentToken;

		This->_Advance();

		for (auto VarType : This->VarTypes)
		{
			if (This->_CurrentToken->Type == VarType)
			{
				Function->FunctionType = This->_CurrentToken;
				break;
			}
			if (VarType == TokenType::TYPE_BOOL)
				return nullptr;
		}

		if (This->_NextToken->Type == TokenType::SEMICOLON)
		{
			delete This->_NextToken;
			This->_Advance();

			return Function;
		}

		if (!This->_ExpectedToken(TokenType::LBRACE))
			return nullptr;
		delete This->_CurrentToken;

		Function->Body = This->_ParseBlock();
		Function->IsDefined = true;

		return Function;
	}

	AST::Expression* ParseIdentifier(Parser* This, TokenType)
	{
		return new AST::Identifier(This->_CurrentToken, This->_CurrentToken->Value);
	}

	AST::Expression* ParseInteger(Parser* This, TokenType Type)
	{
		if (Type == TokenType::TYPE_BOOL && This->_NextToken->Type == TokenType::SEMICOLON)
		{
			AST::Boolean* Bool = new AST::Boolean(This->_CurrentToken);
			Bool->Value = atoi(This->_CurrentToken->Value) ? true : false;
			return Bool;
		}
		
		AST::Integer* Int = new AST::Integer(This->_CurrentToken);
		Int->Value = atoi(This->_CurrentToken->Value);
		return Int;
	}

	AST::Expression* ParseBoolean(Parser* This, TokenType Type)
	{
		AST::Boolean* Bool = new AST::Boolean(This->_CurrentToken);

		Bool->Value = (This->_CurrentToken->Type == TokenType::FALSE ? false : true);

		return Bool;
	}

	AST::Prefix* ParsePrefixExpression(Parser* This, TokenType)
	{
		AST::Prefix* prefix_expression = new AST::Prefix(This->_CurrentToken, (const char*)This->_CurrentToken->Value);

		This->_Advance();

		prefix_expression->Right = This->_ParseExpression(Precedence::PREFIX, TokenType::ILLEGAL);

		return prefix_expression;
	}

	bool Parser::_ExpectedToken(TokenType Type)
	{
		if (_NextToken->Type == Type)
		{
			_Advance();
			return true;
		}

		_ExpectedError(Type);
		return false;
	}

	AST::Expression* ParseCall(Parser* This, AST::Expression* Fn)
	{
		AST::Call* call = new AST::Call(This->_CurrentToken, Fn);
		call->Arguments = This->_ParseCallArguments();

		return call;
	}

	std::vector<AST::Expression*> Parser::_ParseCallArguments()
	{
		std::vector<AST::Expression*> args = {};

		if (_NextToken->Type == TokenType::RPAREN)
		{
			delete _NextToken;
			_Advance();
			return args;
		}

		_Advance();
		AST::Expression* Expr;
		if (Expr = _ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL))
			args.emplace_back(Expr);

		while (_NextToken->Type == TokenType::COMMA)
		{
			delete _NextToken;
			_Advance();
			_Advance();

			if (Expr = _ParseExpression(Precedence::LOWEST, TokenType::ILLEGAL))
				args.emplace_back(Expr);
		}

		if (!_ExpectedToken(TokenType::RPAREN))
			return {};
		delete _CurrentToken;

		return args;
	}

	void Parser::_ExpectedError(TokenType Type)
	{
		std::stringstream ss;
		ss << "The next token was expected to be " << TokenTypeToString(Type) << " but was obtained " << TokenTypeToString(_NextToken->Type) << ".";

		std::string Str = ss.str();
		char* NStr = (char*)calloc(Str.length(), sizeof(char));
		strcpy(NStr, Str.c_str());

		Errors.emplace_back(NStr);
	}

	std::vector<AST::VarStatement*> Parser::_ParseFunctionParameters()
	{
		std::vector<AST::VarStatement*> Params;

		if (_NextToken->Type == TokenType::RPAREN)
		{
			_Advance();
			delete _CurrentToken;
			return Params;
		}

		_Advance();

		TokenType FristArgumentType = _CurrentToken->Type;
		AST::VarStatement* FristArgument = new AST::VarStatement(_CurrentToken, _CurrentToken->Type);

		if (!_ExpectedToken(TokenType::ID))
			return {};

		FristArgument->ID = new AST::Identifier(_CurrentToken, _CurrentToken->Value);

		if (_NextToken->Type == TokenType::EQUALS)
		{
			delete _NextToken;
			_Advance();
			_Advance();

			FristArgument->Value = _ParseExpression(Precedence::LOWEST, FristArgumentType);
		}

		Params.emplace_back(FristArgument);

		while (_NextToken->Type == TokenType::COMMA)
		{
			delete _NextToken;
			_Advance();
			_Advance();

			TokenType ArgumentType = _CurrentToken->Type;
			AST::VarStatement* Argument = new AST::VarStatement(_CurrentToken, _CurrentToken->Type);

			if (!_ExpectedToken(TokenType::ID))
				return {};

			Argument->ID = new AST::Identifier(_CurrentToken, _CurrentToken->Value);

			if (_NextToken->Type == TokenType::EQUALS)
			{
				delete _NextToken;
				_Advance();
				_Advance();

				Argument->Value = _ParseExpression(Precedence::LOWEST, ArgumentType);
			}

			Params.emplace_back(Argument);
		}

		if (!_ExpectedToken(TokenType::RPAREN))
			return {};
		delete _CurrentToken;

		return Params;
	}

	AST::Block* Parser::_ParseBlock()
	{
		AST::Block* Block = new AST::Block(_CurrentToken);

		_Advance();
		while (_CurrentToken->Type != TokenType::RBRACE && _CurrentToken->Type != TokenType::END_OF_FILE)
		{
			AST::Statement* statement = _ParseStatement();

			if (statement != nullptr)
				Block->Statements.emplace_back(statement);

			_Advance();
		}

		return Block;
	}

	Precedence Parser::_PeekPrecedence()
	{
		return Precedences[_NextToken->Type];
	}

	PrefixParseFns DefinePrefixFns()
	{
		PrefixParseFns Fns;
		Fns[TokenType::FUNCTION] = (PrefixParseFn)ParseFunction;
		Fns[TokenType::ID] = (PrefixParseFn)ParseIdentifier;
		Fns[TokenType::INT] = (PrefixParseFn)ParseInteger;
		//fns[TokenType::C_IF] = (PrefixParseFn)_ParseIf;
		Fns[TokenType::LPAREN] = (PrefixParseFn)ParseGroupedExpression;
		Fns[TokenType::MINUS] = (PrefixParseFn)ParsePrefixExpression;
		Fns[TokenType::NOT] = (PrefixParseFn)ParsePrefixExpression;
		Fns[TokenType::FALSE] = (PrefixParseFn)ParseBoolean;
		Fns[TokenType::TRUE] = (PrefixParseFn)ParseBoolean;
		return Fns;
	}

	PrefixParseFns Parser::_RegisterPrefixFns()
	{
		static PrefixParseFns Fns = DefinePrefixFns();
		return Fns;
	}

	InfixParseFns DefineInfixFns()
	{
		InfixParseFns fns;
		fns[TokenType::PLUS] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::MINUS] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::DIVISION] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::MULTIPLICATION] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::EQUALS_TO] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::NOT_EQUALS] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::LESS_THAN] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::GREATER_THAN] = (InfixParseFn)ParseInfixExpression;
		fns[TokenType::LPAREN] = (InfixParseFn)ParseCall;

		return fns;
	}

	InfixParseFns Parser::_RegisterInfixFns()
	{
		static InfixParseFns Fns = DefineInfixFns();
		return Fns;
	}

}