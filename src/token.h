#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType
{
    None = 0,
    Number,      // [0-9]
    Variable,    // x
    OpePlus,     // + (unary)
    OpeMinus,    // - (unary)
    OpeSum,      // + (binary)
    OpeDiff,     // - (binary)
    OpeProd,     // *
    OpeQuot,     // /
    OpePow,      // ^
    ParOpen,     // (
    ParClose     // )
};

class Token
{
    private:
        TokenType _type;
        int       _val;

    public:
        Token(TokenType type = TokenType::None, int val = 0xdeadbeef);
        bool IsOperator();
        bool IsUnaryOperator();
        bool IsLeftAssociative();
        int GetPrecedence();
        bool HasGreaterPrecedence(Token other);
        bool HasEqualPrecedence(Token other);
        TokenType GetTokenType();
        int GetTokenValue();
        void SetTokenType(TokenType type);
        void SetTokenValue(int val);
        bool IsType(TokenType type);
        std::string ToString();
};

#endif    // TOKEN_H
