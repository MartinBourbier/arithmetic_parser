#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include "polynomial.h"

class Evaluator
{
    public:
        static Polynomial Evaluate(AST* ast);
};

#endif    // EVALUATOR_H
