#include "../src/polynomial.h"

#include <criterion/criterion.h>

bool PolyContains(Polynomial p, Monomial m)
{
    for (Monomial tmp : p.GetMonomials())
    {
        if (tmp == m)
            return true;
    }

    return false;
}

bool PolyEquals(Polynomial p1, Polynomial p2)
{
    for (Monomial m : p1.GetMonomials())
    {
        if (!PolyContains(p2, m))
            return false;
    }

    return p1.GetMonomials().size() == p2.GetMonomials().size();
}

Test(Polynomial_A_Constructor, Empty)
{
    Polynomial p;
    cr_assert(p.GetMonomials().size() == 0);
}

Test(Polynomial_A_Constructor, Constructor_WithZero)
{
    Polynomial p(Monomial(0));
    cr_assert(p.GetMonomials().size() == 0);
}

Test(Polynomial_A_Constructor, Constructor_WithDifferentThanZero)
{
    Polynomial p(Monomial(1));
    cr_assert(p.GetMonomials().size() == 1);
}

Test(Polynomial_A_Constructor, Constructor_WithDifferentThanZero_Bis)
{
    Polynomial p(Monomial(1, 3));
    cr_assert(p.GetMonomials().size() == 1);
}

Test(Polynomial_B_UnaryMinus, NumberOnly_Simple)
{
    Polynomial p(Monomial(4, 0));
    p = -p;

    Polynomial expected(Monomial(-4, 0));
    cr_assert(p.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, p));
}

Test(Polynomial_B_UnaryMinus, NumberOnly_Negative)
{
    Polynomial p(Monomial(-4, 0));
    p = -p;

    Polynomial expected(Monomial(4, 0));
    cr_assert(p.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, p));
}

Test(Polynomial_B_UnaryMinus, NumberOnly_Zero)
{
    Polynomial p(Monomial(0, 0));
    p = -p;

    Polynomial expected(Monomial(0, 0));
    cr_assert(p.GetMonomials().size() == 0);
    cr_assert(PolyEquals(expected, p));
}

Test(Polynomial_B_UnaryMinus, WithVariable_Simple)
{
    Polynomial p(Monomial(1, 1));
    p = -p;

    Polynomial expected(Monomial(-1, 1));
    cr_assert(p.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, p));
}

Test(Polynomial_B_UnaryMinus, WithVariable_DegreeTwo_Only)
{
    Polynomial p(Monomial(3, 2));
    p = -p;

    Polynomial expected(Monomial(-3, 2));
    cr_assert(p.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, p));
}

Test(Polynomial_B_UnaryMinus, WithVariable_DegreeTwo_Complete)
{
    Polynomial p(Monomial(12, 0));
    p = p + Polynomial(Monomial(-7, 1));
    p = p + Polynomial(Monomial(3, 2));

    p = -p;

    Polynomial expected(Monomial(-12, 0));
    expected = expected + Polynomial(Monomial(7, 1));
    expected = expected + Polynomial(Monomial(-3, 2));

    cr_assert(p.GetMonomials().size() == 3);
    cr_assert(PolyEquals(expected, p));
}

Test(Polynomial_C_Add, NumberOnly_Simple)
{
    Polynomial p1(Monomial(4));
    Polynomial p2(Monomial(7));
    Polynomial res = p1 + p2;

    Polynomial expected(Monomial(11));
    cr_assert(res.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_C_Add, NumberOnly_TrickyZero)
{
    Polynomial p1(Monomial(4));
    Polynomial p2(Monomial(-4));
    Polynomial res = p1 + p2;

    Polynomial expected(Monomial(0));
    cr_assert(res.GetMonomials().size() == 0);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_C_Add, Basic_SameDegree)
{
    Polynomial p1(Monomial(4, 2));
    Polynomial p2(Monomial(2, 2));
    Polynomial res = p1 + p2;

    Polynomial expected(Monomial(6, 2));
    cr_assert(res.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_C_Add, Basic_SameDegree_Zero)
{
    Polynomial p1(Monomial(4, 2));
    Polynomial p2(Monomial(-4, 2));
    Polynomial res = p1 + p2;

    Polynomial expected(Monomial(0));
    cr_assert(res.GetMonomials().size() == 0);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_C_Add, Basic_TwoDegree)
{
    Polynomial p(Monomial(4, 2));
    p = p + Polynomial(Monomial(7, 1));
    p = p + Polynomial(Monomial(-1, 1));
    p = p + Polynomial(Monomial(2, 2));

    Polynomial expected(Monomial(6, 2));
    expected = expected + Polynomial(Monomial(6, 1));

    cr_assert(expected.GetMonomials().size() == 2);
    cr_assert(PolyEquals(expected, p));
}

Test(Polynomial_C_Add, WithVariable_MixedOrder)
{
    Polynomial p1(Monomial(1, 2));
    p1 = p1 + Polynomial(Monomial(5, 1));
    p1 = p1 + Polynomial(Monomial(4));

    Polynomial p2(Monomial(-5, 1));
    p2 = p2 + Polynomial(Monomial(-2));
    p2 = p2 + Polynomial(Monomial(1, 2));

    Polynomial res = p1 + p2;

    Polynomial expected;
    expected = expected + Polynomial(Monomial(2, 2));
    expected = expected + Polynomial(Monomial(2));

    cr_assert(res.GetMonomials().size() == 2);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_D_BinaryMinus, NumberOnly_Simple)
{
    Polynomial p1(Monomial(4));
    Polynomial p2(Monomial(7));
    Polynomial res = p1 - p2;

    Polynomial expected(Monomial(-3));
    cr_assert(res.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_D_BinaryMinus, NumberOnly_NotZero)
{
    Polynomial p1(Monomial(4));
    Polynomial p2(Monomial(-4));
    Polynomial res = p1 - p2;

    Polynomial expected(Monomial(8));
    cr_assert(res.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_D_BinaryMinus, NumberOnly_Zero)
{
    Polynomial p1(Monomial(4));
    Polynomial p2(Monomial(4));
    Polynomial res = p1 - p2;

    Polynomial expected(Monomial(0));
    cr_assert(res.GetMonomials().size() == 0);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_D_BinaryMinus, Basic_SameDegree)
{
    Polynomial p1(Monomial(4, 2));
    Polynomial p2(Monomial(2, 2));
    Polynomial res = p1 - p2;

    Polynomial expected(Monomial(2, 2));
    cr_assert(res.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_D_BinaryMinus, Basic_SameDegree_Zero)
{
    Polynomial p1(Monomial(4, 2));
    Polynomial p2(Monomial(4, 2));
    Polynomial res = p1 - p2;

    Polynomial expected(Monomial(0));
    cr_assert(res.GetMonomials().size() == 0);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_D_BinaryMinus, Basic_TwoDegree)
{
    Polynomial p(Monomial(4, 2));
    p = p - Polynomial(Monomial(7, 1));
    p = p - Polynomial(Monomial(-1, 1));
    p = p - Polynomial(Monomial(2, 2));

    Polynomial expected(Monomial(2, 2));
    expected = expected + Polynomial(Monomial(-6, 1));

    cr_assert(p.GetMonomials().size() == 2);
    cr_assert(PolyEquals(expected, p));
}

Test(Polynomial_D_BinaryMinus, WithVariable_MixedOrder)
{
    Polynomial p1(Monomial(1, 2));
    p1 = p1 + Polynomial(Monomial(5, 1));
    p1 = p1 + Polynomial(Monomial(4, 0));

    Polynomial p2(Monomial(-5, 1));
    p2 = p2 + Polynomial(Monomial(-2, 0));
    p2 = p2 + Polynomial(Monomial(1, 2));

    Polynomial res = p1 - p2;

    Polynomial expected;
    expected = expected + Polynomial(Monomial(10, 1));
    expected = expected + Polynomial(Monomial(6, 0));

    cr_assert(res.GetMonomials().size() == 2);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_E_Mult, NumberOnly_Simple)
{
    Polynomial p1(Monomial(4));
    Polynomial p2(Monomial(7));

    Polynomial res = p1 * p2;

    Polynomial expected(Monomial(4 * 7));
    cr_assert(res.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_E_Mult, NumberOnly_Long)
{
    Polynomial p1(Monomial(4165));
    Polynomial p2(Monomial(748));

    Polynomial res = p1 * p2;

    Polynomial expected(Monomial(4165 * 748));
    cr_assert(res.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_E_Mult, NumberOnly_One)
{
    Polynomial p1(Monomial(214));
    Polynomial p2(Monomial(1));

    Polynomial res = p1 * p2;

    Polynomial expected(Monomial(214));
    cr_assert(res.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_E_Mult, NumberOnly_Zero_Left)
{
    Polynomial p1(Monomial(0));
    Polynomial p2(Monomial(7));

    Polynomial res = p1 * p2;

    Polynomial expected(Monomial(0));
    cr_assert(res.GetMonomials().size() == 0);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_E_Mult, NumberOnly_Zero_Right)
{
    Polynomial p1(Monomial(4));
    Polynomial p2(Monomial(0));

    Polynomial res = p1 * p2;

    Polynomial expected(Monomial(0));
    cr_assert(res.GetMonomials().size() == 0);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_E_Mult, NumberOnly_Zero_Both)
{
    Polynomial p1(Monomial(0));
    Polynomial p2(Monomial(0));

    Polynomial res = p1 * p2;

    Polynomial expected(Monomial(0));
    cr_assert(res.GetMonomials().size() == 0);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_E_Mult, WithVariable_Simple_7x)
{
    Polynomial p1(Monomial(1, 1));
    Polynomial p2(Monomial(7));

    Polynomial res = p1 * p2;

    Polynomial expected(Monomial(7, 1));
    cr_assert(res.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_E_Mult, WithVariable_Simple_xx)
{
    Polynomial p1(Monomial(1, 1));
    Polynomial p2(Monomial(1, 1));

    Polynomial res = p1 * p2;

    Polynomial expected(Monomial(1, 2));
    cr_assert(res.GetMonomials().size() == 1);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_E_Mult, WithVariable_Factoring_Simple)
{
    Polynomial p1(Monomial(2, 1));
    p1 = p1 + Polynomial(Monomial(3));

    Polynomial p2(Monomial(4));

    Polynomial res = p1 * p2;

    Polynomial expected(Monomial(12));
    expected = expected + Polynomial(Monomial(8, 1));

    cr_assert(res.GetMonomials().size() == 2);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_E_Mult, WithVariable_Factoring_Complete)
{
    Polynomial p1(Monomial(2, 1));
    p1 = p1 + Polynomial(Monomial(3));

    Polynomial p2(Monomial(-3));
    p2 = p2 + Polynomial(Monomial(-1, 1));
    p2 = p2 + Polynomial(Monomial(6, 2));

    Polynomial res = p1 * p2;

    Polynomial expected(Monomial(-9, 0));
    expected = expected + Polynomial(Monomial(-9, 1));
    expected = expected + Polynomial(Monomial(16, 2));
    expected = expected + Polynomial(Monomial(12, 3));

    cr_assert(res.GetMonomials().size() == 4);
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_F_Div, OnlyNumberDiv_Perfect)
{
    Polynomial p(Monomial(8));
    p = p / Polynomial(Monomial(2));

    Polynomial expected(Monomial(4));
    cr_assert(PolyEquals(expected, p));
}

Test(Polynomial_F_Div, OnlyNumberDiv_WithRemainder)
{
    Polynomial p(Monomial(46));
    p = p / Polynomial(Monomial(9));

    Polynomial expected(Monomial(5));
    cr_assert(PolyEquals(expected, p));
}

Test(Polynomial_F_Div, BiggerDegree_Simple)
{
    Polynomial p1(Monomial(7));
    p1 = p1 + Polynomial(Monomial(7, 1));
    p1 = p1 + Polynomial(Monomial(2, 2));

    Polynomial p2(Monomial(2));
    p2 = p2 + Polynomial(Monomial(1, 1));

    Polynomial res = p1 / p2;

    Polynomial expected(Monomial(3));
    expected = expected + Polynomial(Monomial(2, 1));

    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_F_Div, BiggerDegree_Wikipedia)
{
    Polynomial p1(Monomial(-4));
    p1 = p1 + Polynomial(Monomial(-2, 2));
    p1 = p1 + Polynomial(Monomial(1, 3));

    Polynomial p2(Monomial(-3));
    p2 = p2 + Polynomial(Monomial(1, 1));

    Polynomial res = p1 / p2;

    Polynomial expected(Monomial(3));
    expected = expected + Polynomial(Monomial(1, 1));
    expected = expected + Polynomial(Monomial(1, 2));

    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_F_Div, SameDegree_Simple)
{
    Polynomial p1(Monomial(7));
    p1 = p1 + Polynomial(Monomial(6, 2));

    Polynomial p2(Monomial(1));
    p2 = p2 + Polynomial(Monomial(2, 2));

    Polynomial res = p1 / p2;

    Polynomial expected(Monomial(3));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_F_Div, SameDegree_MathStackExchange)
{
    Polynomial p1(Monomial(2));
    p1 = p1 + Polynomial(Monomial(5, 1));
    p1 = p1 + Polynomial(Monomial(10, 2));
    p1 = p1 + Polynomial(Monomial(4, 3));

    Polynomial p2(Monomial(1));
    p2 = p2 + Polynomial(Monomial(3, 1));
    p2 = p2 + Polynomial(Monomial(3, 2));
    p2 = p2 + Polynomial(Monomial(2, 3));

    Polynomial res = p1 / p2;

    Polynomial expected(Monomial(2));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_F_Div, SmallerDegree_Simple)
{
    Polynomial p1(Monomial(2));

    Polynomial p2(Monomial(1));
    p2 = p2 + Polynomial(Monomial(3, 1));

    Polynomial res = p1 / p2;

    Polynomial expected(Monomial(0));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_F_Div, SmallerDegree_Hard)
{
    Polynomial p1(Monomial(2));
    p1 = p1 + Polynomial(Monomial(5, 1));
    p1 = p1 + Polynomial(Monomial(10, 2));

    Polynomial p2(Monomial(1));
    p2 = p2 + Polynomial(Monomial(3, 1));
    p2 = p2 + Polynomial(Monomial(3, 2));
    p2 = p2 + Polynomial(Monomial(2, 3));

    Polynomial res = p1 / p2;

    Polynomial expected(Monomial(0));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_G_Pow, NumberOnly_Simple)
{
    Polynomial p1(Monomial(2));
    Polynomial p2(Monomial(3));

    Polynomial res = p1 ^ p2;

    Polynomial expected(Monomial(8));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_G_Pow, NumberOnly_Negative_Even)
{
    Polynomial p1(Monomial(-2));
    Polynomial p2(Monomial(4));

    Polynomial res = p1 ^ p2;

    Polynomial expected(Monomial(16));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_G_Pow, NumberOnly_Negative_Odd)
{
    Polynomial p1(Monomial(-2));
    Polynomial p2(Monomial(3));

    Polynomial res = p1 ^ p2;

    Polynomial expected(Monomial(-8));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_G_Pow, NumberOnly_Zero)
{
    Polynomial p1(Monomial(2));
    Polynomial p2(Monomial(0));

    Polynomial res = p1 ^ p2;

    Polynomial expected(Monomial(1));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_G_Pow, NumberOnly_Zero_Zero)
{
    Polynomial p1(Monomial(0));
    Polynomial p2(Monomial(0));

    Polynomial res = p1 ^ p2;

    Polynomial expected(Monomial(1));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_G_Pow, NumberOnly_Zero_Negative)
{
    Polynomial p1(Monomial(-3));
    Polynomial p2(Monomial(0));

    Polynomial res = p1 ^ p2;

    Polynomial expected(Monomial(1));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_G_Pow, WithVariable_Simple)
{
    Polynomial p1(Monomial(2, 1));
    Polynomial p2(Monomial(3));

    Polynomial res = p1 ^ p2;

    Polynomial expected(Monomial(8, 3));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_G_Pow, WithVariable_Simple_HighDegree)
{
    Polynomial p1(Monomial(2, 4));
    Polynomial p2(Monomial(10));

    Polynomial res = p1 ^ p2;

    Polynomial expected(Monomial(1024, 40));
    cr_assert(PolyEquals(expected, res));
}

Test(Polynomial_G_Pow, WithVariable_Expr_Complete)
{
    Polynomial p1(Monomial(5));
    p1 = p1 + Polynomial(Monomial(2, 1));

    Polynomial p2(Monomial(3));

    Polynomial res = p1 ^ p2;

    Polynomial expected(Monomial(125));
    expected = expected + Polynomial(Monomial(150, 1));
    expected = expected + Polynomial(Monomial(60, 2));
    expected = expected + Polynomial(Monomial(8, 3));

    cr_assert(PolyEquals(expected, res));
}

void TestPowPolynomial(Polynomial p1, Polynomial p2)
{
    Polynomial p = p1 ^ p2;
}

Test(Polynomial_G_Pow, ErrorManagement_Negative)
{
    Polynomial p1(Monomial(3));
    Polynomial p2(Monomial(-1));

    cr_assert_throw(TestPowPolynomial(p1, p2), std::exception);
}

Test(Polynomial_G_Pow, ErrorManagement_Negative_Bis)
{
    Polynomial p1(Monomial(0));
    Polynomial p2(Monomial(-12));

    cr_assert_throw(TestPowPolynomial(p1, p2), std::exception);
}

Test(Polynomial_G_Pow, ErrorManagement_NonConst)
{
    Polynomial p1(Monomial(3));
    Polynomial p2(Monomial(1, 1));

    cr_assert_throw(TestPowPolynomial(p1, p2), std::exception);
}

Test(Polynomial_G_Pow, ErrorManagement_NonConst_Big)
{
    Polynomial p1(Monomial(3));

    Polynomial p2(Monomial(3));
    p2 = p2 + Polynomial(Monomial(1, 1));
    p2 = p2 + Polynomial(Monomial(-4, 2));

    cr_assert_throw(TestPowPolynomial(p1, p2), std::exception);
}
