#include "../src/token.h"

#include <criterion/criterion.h>

Test(Token_A_Init, Simple)
{
    Token tok(TokenType::OpeMinus);

    cr_assert(tok.IsType(TokenType::OpeMinus));
    cr_assert(!(tok.IsType(TokenType::OpeProd)));
}

Test(Token_A_Init, Precedence)
{
    Token tok(TokenType::OpeProd);

    cr_assert(tok.IsType(TokenType::OpeProd));
    cr_assert(tok.GetPrecedence() == 2);
}

Test(Token_B_NumberInit, Simple)
{
    int val = 42;

    Token tok(TokenType::Number, val);

    cr_assert(tok.IsType(TokenType::Number));
    cr_assert(tok.GetTokenValue() == val);
}
