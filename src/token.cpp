#include "token.h"

Token::Token(TokenType type, int val) : _type{type}, _val{val} {}

bool Token::IsOperator()
{
    return IsType(TokenType::OpeSum) || IsType(TokenType::OpeDiff) ||
        IsType(TokenType::OpeProd) || IsType(TokenType::OpeQuot) ||
        IsType(TokenType::OpePow) || IsType(TokenType::OpePlus) ||
        IsType(TokenType::OpeMinus);
}

bool Token::IsUnaryOperator()
{
    return IsType(TokenType::OpePlus) || IsType(TokenType::OpeMinus);
}

bool Token::IsLeftAssociative()
{
    return IsType(TokenType::OpeSum) || IsType(TokenType::OpeDiff) ||
        IsType(TokenType::OpeProd) || IsType(TokenType::OpeQuot);
}

int Token::GetPrecedence()
{
    switch (_type)
    {
        case TokenType::OpePlus:
        case TokenType::OpeMinus:
            return 4;

        case TokenType::OpePow:
            return 3;

        case TokenType::OpeProd:
        case TokenType::OpeQuot:
            return 2;

        case TokenType::OpeSum:
        case TokenType::OpeDiff:
            return 1;

        default:
            return 0;
    }
}

bool Token::HasGreaterPrecedence(Token other)
{
    return GetPrecedence() > other.GetPrecedence();
}

bool Token::HasEqualPrecedence(Token other)
{
    return GetPrecedence() == other.GetPrecedence();
}

TokenType Token::GetTokenType() { return _type; }

int Token::GetTokenValue() { return _val; }

void Token::SetTokenType(TokenType type) { _type = type; }

void Token::SetTokenValue(int val) { _val = val; }

bool Token::IsType(TokenType type) { return _type == type; }

std::string Token::ToString()
{
    switch (_type)
    {
        case TokenType::OpeSum:
            return "<binary +>";

        case TokenType::OpePlus:
            return "<unary +>";

        case TokenType::OpeDiff:
            return "<binary ->";

        case TokenType::OpeMinus:
            return "<unary ->";

        case TokenType::OpeProd:
            return "<*>";

        case TokenType::OpeQuot:
            return "</>";

        case TokenType::OpePow:
            return "<^>";

        case TokenType::ParOpen:
            return "(";

        case TokenType::ParClose:
            return ")";

        case TokenType::Variable:
            return "<variable>";

        case TokenType::Number:
            return "<number " + std::to_string(_val) + ">";

        default:
            return "<unknown>";
    }
}
