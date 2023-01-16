#include "PCH.h"
#include "PZL/Lexer/Token.h"

namespace PZL
{

    const char* Token::TokenTypeToString(TokenType Type)
    {
        switch (Type)
        {
        case TokenType::NONE:
            return "None";
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

        case TokenType::INT32:
            return "Int32";
        case TokenType::FALSE:
            return "False";
        case TokenType::TRUE:
            return "True";

        case TokenType::TYPE_VOID:
            return "TypeVoid";
        case TokenType::TYPE_INT8:
            return "TypeInt8";
        case TokenType::TYPE_UINT8:
            return "TypeUInt8";
        case TokenType::TYPE_INT16:
            return "TypeInt16";
        case TokenType::TYPE_UINT16:
            return "TypeUInt16";
        case TokenType::TYPE_INT32:
            return "TypeInt32";
        case TokenType::TYPE_UINT32:
            return "TypeUInt32";
        case TokenType::TYPE_INT64:
            return "TypeInt64";
        case TokenType::TYPE_UINT64:
            return "TypeUInt64";
        case TokenType::TYPE_FLOAT32:
            return "TypeFloat32";
        case TokenType::TYPE_FLOAT64:
            return "TypeFloat64";
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

        Token::KeyWords["i8"] = TokenType::TYPE_INT8;
        Token::KeyWords["u8"] = TokenType::TYPE_UINT8;
    
        Token::KeyWords["i16"] = TokenType::TYPE_INT16;
        Token::KeyWords["u16"] = TokenType::TYPE_UINT16;
    
        Token::KeyWords["i32"] = TokenType::TYPE_INT32;
        Token::KeyWords["u32"] = TokenType::TYPE_UINT32;

        Token::KeyWords["i64"] = TokenType::TYPE_INT64;
        Token::KeyWords["u64"] = TokenType::TYPE_UINT64;       
        Token::KeyWords["f32"] = TokenType::TYPE_FLOAT32;
        Token::KeyWords["f64"] = TokenType::TYPE_FLOAT64;

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