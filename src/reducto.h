#ifndef REDUCTO_H
#define REDUCTO_H

#include "evaluator.h"
#include "lexer.h"
#include "parser.h"

class Reducto
{
    public:
        static Polynomial Parse(std::string expression);
};

#endif // REDUCTO_H
