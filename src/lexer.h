#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#include <vector>

class Lexer
{
    private:
        static int _ReadNumber(std::string expression, int &pos);
    public:
        static std::vector<Token> Run(std::string expression);
};

#endif    // LEXER_H
