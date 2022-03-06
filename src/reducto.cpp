#include "reducto.h"

Polynomial Reducto::Parse(std::string expression)
{
    if (expression.size() <= 0)
        throw std::exception();

    std::vector<Token> tokens = Lexer::Run(expression);
    AST *ast = Parser::BuildAST(tokens);
    Polynomial res = Evaluator::Evaluate(ast);

    return res;
}
