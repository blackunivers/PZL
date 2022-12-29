#include "PCH.h"
#include "Lexer.h"

#include "Lexer/Token.h"

namespace PZL
{

    Lexer::Lexer(const char* Source)
    {
        _Source = Source;
        _Current = Source[0];
        _Len = strlen(Source);
    }

    Lexer::~Lexer()
    {
    }

    Token* Lexer::NextToken()
    {
        Token* TK;

        _SkipWhiteSpace();

        switch (_Current)
        {
        case '=':
            if (_PeekCharacter() == '=')
                TK = _AdvanceWithTwo(TokenType::EQUALS_TO);
            else
                TK = _AdvanceWith(TokenType::EQUALS);
            break;
        case '+':
            TK = _AdvanceWith(TokenType::PLUS);
            break;
        case '-':
            TK = _AdvanceWith(TokenType::MINUS);
            break;
        case '*':
            TK = _AdvanceWith(TokenType::MULTIPLICATION);
            break;
        case '/':
            TK = _AdvanceWith(TokenType::DIVISION);
            break;
        case '(':
            TK = _AdvanceWith(TokenType::LPAREN);
            break;
        case ')':
            TK = _AdvanceWith(TokenType::RPAREN);
            break;
        case '{':
            TK = _AdvanceWith(TokenType::LBRACE);
            break;
        case '}':
            TK = _AdvanceWith(TokenType::RBRACE);
            break;
        case ',':
            TK = _AdvanceWith(TokenType::COMMA);
            break;
        case '.':
            TK = _AdvanceWith(TokenType::DOT);
            break;
        case ':':
            TK = _AdvanceWith(TokenType::COLON);
            break;
        case ';':
            TK = _AdvanceWith(TokenType::SEMICOLON);
            break;
        case '!':
            if (_PeekCharacter() == '=')
                TK = _AdvanceWithTwo(TokenType::NOT_EQUALS);
            else
                TK = _AdvanceWith(TokenType::NOT);
            break;
        case '>':
            TK = _AdvanceWith(TokenType::GREATER_THAN);
            break;
        case '<':
            TK = _AdvanceWith(TokenType::LESS_THAN);
            break;
        case '\0':
            TK = _AdvanceWith(TokenType::END_OF_FILE);
            break;
        default:

            if (std::isalpha(_Current) || _Current == '_')
                return _AdvanceWithID();
            else if (std::isdigit(_Current))
                return _AdvanceWithDigit();


            TK = new Token(TokenType::ILLEGAL, _Current);
            break;
        }

        return TK;
    }

    void Lexer::_SkipWhiteSpace()
    {
        while (_Current == ' ' || _Current == '\t' || _Current == '\n' || _Current == '\r')
            _Advance();
    }

    void Lexer::_Advance()
    {
        _Index++;
        if (_Index > _Len)
            _Current = '\0';
        else
            _Current = _Source[_Index];
    }

    char Lexer::_PeekCharacter()
    {
        if ((_Index + 1) > _Len)
            return ' ';
        return _Source[_Index + 1];
    }

    Token* Lexer::_AdvanceWith(TokenType Type)
    {
        char Value = _Current;
        _Advance();

        return new Token(Type, Value);
    }

    Token* Lexer::_AdvanceWithTwo(TokenType Type)
    {
        char* Value = (char*)calloc(3, sizeof(char));
        Value[0] = _Current;
        _Advance();
        Value[1] = _Current;
        _Advance();
        Value[2] = '\0';

        return new Token(Type, Value);
    }

    Token* Lexer::_AdvanceWithID()
    {
        char* Value = (char*)calloc(2, sizeof(char));
        Value[0] = _Current;
        Value[1] = '\0';
        _Advance();

        while (std::isalnum(_Current) || _Current == '_')
        {
            Value = (char*)realloc(Value, (strlen(Value) + 2) * sizeof(char));
            char* Tmp = (char*)calloc(2, sizeof(char));
            Tmp[0] = _Current;
            Tmp[1] = '\0';
            strcat(Value, Tmp);
            
            _Advance();

            free(Tmp);
        }

        TokenType Type = LookUpTokenType(Value);

        return new Token(Type, Value);
    }

    Token* Lexer::_AdvanceWithDigit()
    {
        char* Value = (char*)calloc(2, sizeof(char));
        Value[0] = _Current;
        Value[1] = '\0';
        _Advance();

        while (std::isdigit(_Current))
        {
            Value = (char*)realloc(Value, (strlen(Value) + 2) * sizeof(char));
            char* Tmp = (char*)calloc(2, sizeof(char));
            Tmp[0] = _Current;
            Tmp[1] = '\0';
            strcat(Value, Tmp);

            _Advance();

            free(Tmp);
        }

        return new Token(TokenType::INT, Value);
    }

}