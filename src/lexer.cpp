#include "lexer.h"

#include "token.h"

#include <iostream>

bool IsDigit(char c) { return c >= '0' && c <= '9'; }

int Lexer::_ReadNumber(std::string expression, int &pos)
{
    int val = 0;

    while (pos < expression.size())
    {
        char c = expression.at(pos);

        if (IsDigit(c))
        {
            pos++;
            val = val * 10 + (c - '0');
        }
        else
        {
            pos--;
            return val;
        }
    }

    return val;
}

std::vector<Token> Lexer::Run(std::string expression)
{
    std::vector<Token> res;
    int                pos = 0;

    while (pos < expression.size())
    {
        char  c = expression.at(pos);
        Token tok;

        if (IsDigit(c))
        {
            int val = _ReadNumber(expression, pos);

            tok = Token(TokenType::Number, val);

            bool valid = (res.empty() ||
                          res.back().IsOperator() ||
                          res.back().IsType(TokenType::Variable) ||
                          res.back().IsType(TokenType::ParOpen) ||
                          res.back().IsType(TokenType::ParClose));

            if (!valid)
                throw std::exception();
            else if (!res.empty() && (res.back().IsType(TokenType::Variable) ||
                                      res.back().IsType(TokenType::ParClose)))
            {
                res.push_back(Token(TokenType::OpeProd));
            }
        }
        else if (c == 'x')
        {
            tok = Token(TokenType::Variable);

            bool valid = (res.empty() ||
                          res.back().IsOperator() ||
                          res.back().IsType(TokenType::ParOpen) ||
                          res.back().IsType(TokenType::Number));

            if (!valid)
                throw std::exception();
            else if (!res.empty() && res.back().IsType(TokenType::Number))
                res.push_back(Token(TokenType::OpeProd));
        }
        else if (c == '+')
        {
            bool isUnary = (res.empty() ||
                            res.back().IsUnaryOperator() ||
                            res.back().IsType(TokenType::ParOpen));

            if (isUnary)
                tok = Token(TokenType::OpePlus);
            else
                tok = Token(TokenType::OpeSum);
        }
        else if (c == '-')
        {
            bool isUnary = (res.empty() ||
                            res.back().IsUnaryOperator() ||
                            res.back().IsType(TokenType::ParOpen));

            if (isUnary)
                tok = Token(TokenType::OpeMinus);
            else
                tok = Token(TokenType::OpeDiff);
        }
        else if (c == '*')
        {
            tok = Token(TokenType::OpeProd);

            bool valid =
                (!res.empty() && (res.back().IsType(TokenType::Number) ||
                                  res.back().IsType(TokenType::Variable) ||
                                  res.back().IsType(TokenType::ParClose)));

            if (!valid)
                throw std::exception();
        }
        else if (c == '/')
        {
            tok = Token(TokenType::OpeQuot);

            bool valid =
                (!res.empty() && (res.back().IsType(TokenType::Number) ||
                                  res.back().IsType(TokenType::Variable) ||
                                  res.back().IsType(TokenType::ParClose)));

            if (!valid)
                throw std::exception();
        }
        else if (c == '^')
        {
            tok = Token(TokenType::OpePow);

            bool valid = (!res.empty() &&
                          (res.back().IsType(TokenType::Number) ||
                           res.back().IsType(TokenType::Variable) ||
                           res.back().IsType(TokenType::ParClose)));

            if (!valid)
                throw std::exception();
        }
        else if (c == '(')
        {
            tok = Token(TokenType::ParOpen);

            bool valid = (res.empty() ||
                          res.back().IsOperator() ||
                          res.back().IsType(TokenType::Number) ||
                          res.back().IsType(TokenType::Variable) ||
                          res.back().IsType(TokenType::ParOpen) ||
                          res.back().IsType(TokenType::ParClose));

            if (!valid)
                throw std::exception();
            else if (!res.empty() &&
                     (res.back().IsType(TokenType::Number) ||
                      res.back().IsType(TokenType::Variable) ||
                      res.back().IsType(TokenType::ParClose)))
                res.push_back(Token(TokenType::OpeProd));
        }
        else if (c == ')')
        {
            tok = Token(TokenType::ParClose);

            bool valid = (res.empty() || res.back().IsType(TokenType::Number) ||
                          res.back().IsType(TokenType::Variable) ||
                          res.back().IsType(TokenType::ParClose));

            if (!valid)
                throw std::exception();
        }
        else if (c != ' ' && c != '\t' && c != '\r' && c != '\n')
            throw std::exception();

        if (!tok.IsType(TokenType::None))
            res.push_back(tok);

        pos++;
    }

    return res;
}
