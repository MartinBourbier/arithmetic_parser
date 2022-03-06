#include "parser.h"

#include <iostream>

Token pop_front(std::vector<Token> &vector)
{
    if (vector.size() == 0)
        return Token();

    Token tok = vector.at(0);
    vector.erase(vector.begin());

    return tok;
}

bool try_peek(std::stack<Token> stack, Token &token)
{
    if (stack.empty())
        return false;

    token = stack.top();
    return true;
}

bool try_pop(std::stack<Token> &stack, Token &token)
{
    if (stack.empty())
        return false;

    token = stack.top();
    stack.pop();
    return true;
}

std::stack<Token> Parser::_ToPolishNotation(std::vector<Token> tokens)
{
    std::stack<Token> res;
    std::stack<Token> op;

    Token curr = pop_front(tokens);

    while (!curr.IsType(TokenType::None))
    {
        if (curr.IsOperator())
        {
            Token top;
            while (try_peek(op, top) && (top.HasGreaterPrecedence(curr) ||
                        (top.HasEqualPrecedence(curr) && curr.IsLeftAssociative()))
                    && !top.IsType(TokenType::ParOpen))
            {
                res.push(op.top());
                op.pop();
            }

            op.push(curr);
        }
        else if (curr.IsType(TokenType::ParOpen))
            op.push(curr);
        else if (curr.IsType(TokenType::ParClose))
        {
            bool found = false;
            Token top;

            while (!found && try_pop(op, top))
            {
                if (top.IsType(TokenType::ParOpen))
                    found = true;
                else
                    res.push(top);
            }

            if (!found)
                throw std::exception();
        }
        else
            res.push(curr);

        curr = pop_front(tokens);
    }

    while (op.size() > 0)
    {
        Token token = op.top();
        op.pop();

        if (token.IsType(TokenType::ParOpen) || token.IsType(TokenType::ParClose))
            throw std::exception();

        res.push(token);
    }

    return res;
}

AST* Parser::_BuildAST(std::stack<Token> &tokens)
{
    if (tokens.size() <= 0)
        return NULL;

    AST *res = new AST();

    Token token = tokens.top();
    tokens.pop();
    res->_key = token;

    if (token.IsOperator())
    {
        if (tokens.size() <= 0)
            throw std::exception();

        res->_right = _BuildAST(tokens);

        if (!token.IsUnaryOperator())
        {
            if (tokens.size() <= 0)
                throw std::exception();

            res->_left = _BuildAST(tokens);
        }
    }

    return res;
}

void print_stack(std::stack<Token> stack)
{
    while (!stack.empty())
    {
        Token tok = stack.top();
        std::cout << tok.ToString() << '\n';
        stack.pop();
    }
}

AST* Parser::BuildAST(std::vector<Token> tokens)
{
    std::stack<Token> token_stack = _ToPolishNotation(tokens);

    if (token_stack.size() <= 0)
        throw std::exception();

    return _BuildAST(token_stack);
}
