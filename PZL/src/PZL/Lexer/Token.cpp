#include "PCH.h"
#include "Token.h"

namespace PZL
{

    const char* Token::TokenTypeToString(TokenType Type)
    {
        switch (Type)
        {
        case TokenType::ID:
            return "ID";

        case TokenType::EQUALS:
            return "Equals";
        case TokenType::PLUS:
            return "Plus";
        case TokenType::MINUS:
            return "Minus";
        case TokenType::MULTIPLICATION:
            return "Multiplication";
        case TokenType::DIVISION:
            return "Division";
        case TokenType::LPAREN:
            return "LParen";
        case TokenType::RPAREN:
            return "RParen";
        case TokenType::LBRACE:
            return "LBrace";
        case TokenType::RBRACE:
            return "RBrace";
        case TokenType::COLON:
            return "Colon";
        case TokenType::SEMICOLON:
            return "Semicolon";
        case TokenType::COMMA:
            return "Comma";
        case TokenType::DOT:
            return "Dot";

        case TokenType::EQUALS_TO:
            return "EqualsTo";
        case TokenType::NOT:
            return "Not";
        case TokenType::NOT_EQUALS:
            return "NotEquals";
        case TokenType::LESS_THAN:
            return "LessThan";
        case TokenType::GREATER_THAN:
            return "GreaterThan";

        case TokenType::IF:
            return "If";
        case TokenType::ELIF:
            return "Elif";
        case TokenType::ELSE:
            return "Else";

        case TokenType::INT:
            return "Int";
        case TokenType::FALSE:
            return "False";
        case TokenType::TRUE:
            return "True";

        case TokenType::TYPE_VOID:
            return "TypeVoid";
        case TokenType::TYPE_INT:
            return "TypeInt";
        case TokenType::TYPE_BOOL:
            return "TypeBool";

        case TokenType::FUNCTION:
            return "Function";
        case TokenType::RETURN:
            return "Return";

        case TokenType::END_OF_FILE:
            return "EndOfFile";
        }

        return "ILLEGAL";
    }

    static int DefineKeyWords()
    {
        Token::KeyWords["void"] = TokenType::TYPE_VOID;
        Token::KeyWords["int"] = TokenType::TYPE_INT;
        Token::KeyWords["bool"] = TokenType::TYPE_BOOL;
        
        Token::KeyWords["if"] = TokenType::IF;
        Token::KeyWords["elif"] = TokenType::ELIF;
        Token::KeyWords["else"] = TokenType::ELSE;

        Token::KeyWords["false"] = TokenType::FALSE;
        Token::KeyWords["true"] = TokenType::TRUE;

        Token::KeyWords["func"] = TokenType::FUNCTION;
        Token::KeyWords["return"] = TokenType::RETURN;

        return 0;
    }

    TokenType Token::LookUpTokenType(const char* ID)
    {
        static int Unused = DefineKeyWords();

        for (auto& [Key, Word] : Token::KeyWords)
        {
            if (std::strcmp(Key, ID) == 0)
                return Word;
        }

        return TokenType::ID;
    }
}