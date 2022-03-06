#ifndef AST_H
#define AST_H

#include "token.h"

class AST
{
    public:
        Token _key;
        AST   *_left;
        AST   *_right;

        AST(Token key = Token(), AST *left = NULL, AST *right = NULL);
};

#endif    // AST_H
