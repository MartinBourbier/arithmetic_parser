#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

#include <stack>
#include <vector>

class Parser
{
    private:
        static std::stack<Token> _ToPolishNotation(std::vector<Token> tokens);
        static AST* _BuildAST(std::stack<Token> &tokens);
    public:
        static AST* BuildAST(std::vector<Token> tokens);
};

#endif    // PARSER_H
