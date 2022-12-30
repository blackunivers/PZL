#include "PCH.h"
#include "Token.h"

namespace PZL
{

    const char* TokenTypeToString(TokenType Type)
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
        KeyWords["void"] = TokenType::TYPE_VOID;
        KeyWords["int"] = TokenType::TYPE_INT;
        KeyWords["bool"] = TokenType::TYPE_BOOL;
        KeyWords["false"] = TokenType::FALSE;
        KeyWords["true"] = TokenType::TRUE;
        KeyWords["func"] = TokenType::FUNCTION;
        KeyWords["return"] = TokenType::RETURN;

        return 0;
    }

    TokenType LookUpTokenType(const char* ID)
    {
        static int Unused = DefineKeyWords();

        for (auto& [Key, Word] : KeyWords)
        {
            if (std::strcmp(Key, ID) == 0)
                return Word;
        }

        return TokenType::ID;
    }
}