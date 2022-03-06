#include "evaluator.h"

Polynomial Evaluator::Evaluate(AST* ast)
{
    Polynomial res;

    switch (ast->_key.GetTokenType())
    {
        case TokenType::OpeSum:
            res = Evaluate(ast->_left) + Evaluate(ast->_right);
            break;
        case TokenType::OpeDiff:
            res = Evaluate(ast->_left) - Evaluate(ast->_right);
            break;
        case TokenType::OpeProd:
            res = Evaluate(ast->_left) * Evaluate(ast->_right);
            break;
        case TokenType::OpeQuot:
            res = Evaluate(ast->_left) / Evaluate(ast->_right);
            break;
        case TokenType::OpePow:
            res = Evaluate(ast->_left) ^ Evaluate(ast->_right);
            break;
        case TokenType::OpePlus:
            res = Evaluate(ast->_right);
            break;
        case TokenType::OpeMinus:
            res = -Evaluate(ast->_right);
            break;
        case TokenType::Number:
            res = Polynomial(Monomial(ast->_key.GetTokenValue()));
            break;
        case TokenType::Variable:
            res = Polynomial(Monomial(1, 1));
            break;
        default:
            break;
    }

    return res;
}
