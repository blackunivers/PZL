#include "PCH.h"
#include "Lexer.h"

#include "Lexer/Token.h"

namespace PZL
{

    Lexer::Lexer(const char* Source)
    {
        this->Source = Source;
        Current = this->Source[0];
        Len = strlen(Source);
    }

    Lexer::~Lexer()
    {
    }

    Token* Lexer::NextToken()
    {
        Token* TK;

        SkipWhiteSpace();

        switch (Current)
        {
        case '=':
            if (PeekCharacter() == '=')
                TK = AdvanceWithTwo(TokenType::EQUALS_TO);
            else
                TK = AdvanceWith(TokenType::EQUALS);
            break;
        case '+':
            TK = AdvanceWith(TokenType::PLUS);
            break;
        case '-':
            TK = AdvanceWith(TokenType::MINUS);
            break;
        case '*':
            TK = AdvanceWith(TokenType::MULTIPLICATION);
            break;
        case '/':
            TK = AdvanceWith(TokenType::DIVISION);
            break;
        case '(':
            TK = AdvanceWith(TokenType::LPAREN);
            break;
        case ')':
            TK = AdvanceWith(TokenType::RPAREN);
            break;
        case '{':
            TK = AdvanceWith(TokenType::LBRACE);
            break;
        case '}':
            TK = AdvanceWith(TokenType::RBRACE);
            break;
        case ',':
            TK = AdvanceWith(TokenType::COMMA);
            break;
        case '.':
            TK = AdvanceWith(TokenType::DOT);
            break;
        case ':':
            TK = AdvanceWith(TokenType::COLON);
            break;
        case ';':
            TK = AdvanceWith(TokenType::SEMICOLON);
            break;
        case '!':
            if (PeekCharacter() == '=')
                TK = AdvanceWithTwo(TokenType::NOT_EQUALS);
            else
                TK = AdvanceWith(TokenType::NOT);
            break;
        case '>':
            TK = AdvanceWith(TokenType::GREATER_THAN);
            break;
        case '<':
            TK = AdvanceWith(TokenType::LESS_THAN);
            break;
        case '\0':
            TK = AdvanceWith(TokenType::END_OF_FILE);
            break;
        default:

            if (std::isalpha(Current) || Current == '_')
                return AdvanceWithID();
            else if (std::isdigit(Current))
                return AdvanceWithDigit();


            TK = new Token(TokenType::ILLEGAL, Current, Line);
            break;
        }

        return TK;
    }

    void Lexer::SkipWhiteSpace()
    {
        while (Current == ' ' || Current == '\t' || Current == '\n' || Current == '\r')
        {
            if (Current == '\n')
                Line++;
            Advance();
        }
    }

    void Lexer::Advance()
    {
        Index++;
        if (Index > Len)
            Current = '\0';
        else
            Current = Source[Index];
    }

    char Lexer::PeekCharacter()
    {
        if ((Index + 1) > Len)
            return ' ';
        return Source[Index + 1];
    }

    Token* Lexer::AdvanceWith(TokenType Type)
    {
        char Value = Current;
        Advance();

        return new Token(Type, Value, Line);
    }

    Token* Lexer::AdvanceWithTwo(TokenType Type)
    {
        char* Value = (char*)calloc(3, sizeof(char));
        Value[0] = Current;
        Advance();
        Value[1] = Current;
        Advance();
        Value[2] = '\0';

        return new Token(Type, Value, Line);
    }

    Token* Lexer::AdvanceWithID()
    {
        char* Value = (char*)calloc(2, sizeof(char));
        Value[0] = Current;
        Value[1] = '\0';
        Advance();

        while (std::isalnum(Current) || Current == '_')
        {
            Value = (char*)realloc(Value, (strlen(Value) + 2) * sizeof(char));
            char* Tmp = (char*)calloc(2, sizeof(char));
            Tmp[0] = Current;
            Tmp[1] = '\0';
            strcat(Value, Tmp);
            
            Advance();

            free(Tmp);
        }

        TokenType Type = Token::LookUpTokenType(Value);

        return new Token(Type, Value, Line);
    }

    Token* Lexer::AdvanceWithDigit()
    {
        char* Value = (char*)calloc(2, sizeof(char));
        Value[0] = Current;
        Value[1] = '\0';
        Advance();

        while (std::isdigit(Current))
        {
            Value = (char*)realloc(Value, (strlen(Value) + 2) * sizeof(char));
            char* Tmp = (char*)calloc(2, sizeof(char));
            Tmp[0] = Current;
            Tmp[1] = '\0';
            strcat(Value, Tmp);

            Advance();

            free(Tmp);
        }

        return new Token(TokenType::INT, Value, Line);
    }

}