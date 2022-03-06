#include "ast.h"

AST::AST(Token key, AST *left, AST *right)
    : _key{key}, _left{left}, _right{right}
{
}
