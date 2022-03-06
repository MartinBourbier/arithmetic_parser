#include "../src/monomial.h"

#include <criterion/criterion.h>
#include <iostream>

Test(Monomial_A_Constructor, NothingSpecial_NoThrow)
{
    Monomial m1(1, 2);
    cr_expect(true);
}

Test(Monomial_A_Constructor, DegreeZero_NoThrow)
{
    Monomial m1(1, 0);
    cr_expect(true);
}

Test(Monomial_A_Constructor, Zero_Default_NoThrow)
{
    Monomial m1(0);
    cr_expect(true);
}

Test(Monomial_A_Constructor, Zero_PositiveDegree_NoThrow)
{
    Monomial m1(0, 10);
    cr_expect(true);
}

Test(Monomial_A_Constructor, Zero_NegativeDegree_NoThrow)
{
    Monomial m1(0, -10);
    cr_expect(true);
}

Test(Monomial_A_Constructor, NegativeCoef_MustThrow_MinusFour)
{
    cr_expect_throw(Monomial(1, -4), std::exception);
}

Test(Monomial_A_Constructorm, NegativeCoef_MustThrow_MinusOne)
{
    cr_expect_throw(Monomial(7, -1), std::exception);
}

Test(Monomial_B_Equality, BasicEqual)
{
    Monomial m1(1, 2);
    Monomial m2(1, 2);

    cr_expect(m1 == m2);
    cr_expect(!(m1 != m2));
}

Test(Monomial_B_Equality, BasicNotEqual)
{
    Monomial m1(1, 2);
    Monomial m2(3, 10);

    cr_expect(m1 != m2);
    cr_expect(!(m1 == m2));
}

Test(Monomial_B_Equality, SameCoefNotEqual)
{
    Monomial m1(1, 2);
    Monomial m2(1, 10);

    cr_expect(m1 != m2);
    cr_expect(!(m1 == m2));
}

Test(Monomial_B_Equality, SameDegreeNotEqual)
{
    Monomial m1(1, 2);
    Monomial m2(3, 2);

    cr_expect(m1 != m2);
    cr_expect(!(m1 == m2));
}

Test(Monomial_C_Add, SameDegree)
{
    Monomial m1(1, 2);
    Monomial m2(4, 2);

    Monomial expected(5, 2);
    cr_expect(m1 + m2 == expected);
}

Test(Monomial_C_Add, SameDegree_NegativeCoef)
{
    Monomial m1(1, 2);
    Monomial m2(-4, 2);

    Monomial expected(-3, 2);
    cr_expect(m1 + m2 == expected);
}

void TestAddMonomial(Monomial m1, Monomial m2)
{
    Monomial m = m1 + m2;
}

Test(Monomial_C_Add, DifferentDegree_Basic)
{
    Monomial m1(1, 2);
    Monomial m2(2, 1);

    cr_expect_throw(TestAddMonomial(m1, m2), std::exception);
}

Test(Monomial_C_Add, DifferentDegree_Zero_CoefNotZero)
{
    Monomial m1(1, 2);
    Monomial m2(3, 0);

    cr_expect_throw(TestAddMonomial(m1, m2), std::exception);
}

Test(Monomial_C_Add, SameDegree_Zero_CoefZero)
{
    Monomial m1(1, 2);
    Monomial m2(0, 10);

    Monomial expected(1, 2);
    cr_expect(m1 + m2 == expected);
}

Test(Monomial_C_Add, SameDegree_Zero_CoefZero_Reversed)
{
    Monomial m1(1, 2);
    Monomial m2(0 ,10);

    Monomial expected(1, 2);
    cr_expect(m2 + m1 == expected);
}

Test(Monomial_D_UnaryMinus, Simple)
{
    Monomial m1(1, 2);

    Monomial expected(-1, 2);
    cr_expect(-m1 == expected);
}

Test(Monomial_D_UnaryMinus, Simple_DegreeZero)
{
    Monomial m1(14, 0);

    Monomial expected(-14, 0);
    cr_expect(-m1 == expected);
}

Test(Monomial_D_UnaryMinus, Simple_CoefZero)
{
    Monomial m1(0, 3);

    Monomial expected(0, 3);
    cr_expect(-m1 == expected);
}

Test(Monomial_D_UnaryMinus, Simple_Nagative)
{
    Monomial m1(-2, 3);

    Monomial expected(2, 3);
    cr_expect(-m1 == expected);
}

Test(Monomial_E_BinaryMinus, SameDegree)
{
    Monomial m1(1, 2);
    Monomial m2(4, 2);

    Monomial expected(-3, 2);
    cr_expect(m1 - m2 == expected);
}

Test(Monomial_E_BinaryMinus, SameDegree_NegativeCoef)
{
    Monomial m1(1, 2);
    Monomial m2(-4, 2);

    Monomial expected(5, 2);
    cr_expect(m1 - m2 == expected);
}

void TestSubMonomial(Monomial m1, Monomial m2)
{
    Monomial m = m1 - m2;
}

Test(Monomial_E_BinaryMinus, DifferentDegree_Basic)
{
    Monomial m1(1, 2);
    Monomial m2(2, 1);

    cr_expect_throw(TestSubMonomial(m1, m2), std::exception);
}

Test(Monomial_E_BinaryMinus, DifferentDegree_Zero_CoefNotZero)
{
    Monomial m1(1, 2);
    Monomial m2(3, 0);

    cr_expect_throw(TestSubMonomial(m1, m2), std::exception);
}

Test(Monomial_E_BinaryMinus, SameDegree_Zero_CoefZero)
{
    Monomial m1(1, 2);
    Monomial m2(0, 10);
    
    Monomial expected(1, 2);
    cr_expect(m1 - m2 == expected);
}

Test(Monomial_E_BinaryMinus, SameDegree_Zero_CoefZero_Reversed)
{
    Monomial m1(1, 2);
    Monomial m2(0, 10);

    Monomial expected(-1, 2);
    cr_expect(m2 - m1 == expected);
}

Test(Monomial_F_Mult, SameDegree)
{
    Monomial m1(7, 3);
    Monomial m2(4, 3);

    Monomial expected(28, 6);
    cr_expect(m1 * m2 == expected);
}

Test(Monomial_F_Mult, SameDegree_NegativeCoef)
{
    Monomial m1(7, 3);
    Monomial m2(-4, 3);

    Monomial expected(-28, 6);
    cr_expect(m1 * m2 == expected);
}

Test(Monomial_F_Mult, DifferentDegree)
{
    Monomial m1(7, 2);
    Monomial m2(4, 3);

    Monomial expected(28, 5);
    cr_expect(m1 * m2 == expected);
}

Test(Monomial_F_Mult, DifferentDegree_NegativeCoef)
{
    Monomial m1(7, 2);
    Monomial m2(-4, 3);

    Monomial expected(-28, 5);
    cr_expect(m1 * m2 == expected);
}

Test(Monomial_F_Mult, SameDegree_Zero_CoefZero)
{
    Monomial m1(1, 2);
    Monomial m2(0, 10);

    Monomial expected(0, 0);
    cr_expect(m1 * m2 == expected);
}

Test(Monomial_F_Mult, SameDegree_Zero_CoefZero_Reversed)
{
    Monomial m1(1, 2);
    Monomial m2(0, 10);

    Monomial expected(0, 0);
    cr_expect(m2 * m1 == expected);
}

Test(Monomial_F_Mult, SameDegree_Zero_Both)
{
    Monomial m1(0, 2);
    Monomial m2(0, 10);

    Monomial expected(0, 0);
    cr_expect(m1 * m2 == expected);
}

Test(Monomial_G_Div, Simple)
{
    Monomial m1(8, 2);
    Monomial m2(2, 0);

    Monomial expected(4, 2);
    cr_expect(m1 / m2 == expected);
}

Test(Monomial_G_Div, Simple_TrickDivision)
{
    Monomial m1(8, 2);
    Monomial m2(3, 0);

    Monomial expected(8 / 3, 2);
    cr_expect(m1 / m2 == expected);
}

Test(Monomial_G_Div, Simple_TrickDivision_Bis)
{
    Monomial m1(8, 2);
    Monomial m2(11, 0);

    Monomial expected(8 / 11, 2);
    cr_expect(m1 / m2 == expected);
}

Test(Monomial_G_Div, Simple_BothDegree)
{
    Monomial m1(8, 5);
    Monomial m2(4, 5);

    Monomial expected(2, 0);
    cr_expect(m1 / m2 == expected);
}

Test(Monomial_G_Div, Simple_BothDegree_Zero)
{
    Monomial m1(8, 0);
    Monomial m2(4, 0);

    Monomial expected(2, 0);
    cr_expect(m1 / m2 == expected);
}

void TestDivMonomial(Monomial m1, Monomial m2)
{
    Monomial m = m1 / m2;
}

Test(Monomial_G_Div, ZeroDivision_Left)
{
    Monomial m1(0, 2);
    Monomial m2(4, 1);

    Monomial expected(0);
    cr_expect(m1 / m2 == expected);
}

Test(Monomial_G_Div, ZeroDivision_Right)
{
    Monomial m1(4, 2);
    Monomial m2(0, 1);

    cr_expect_throw(TestDivMonomial(m1, m2), std::exception);
}

Test(Monomial_G_Div, ZeroDivision_Both)
{
    Monomial m1(0, 2);
    Monomial m2(0, 1);

    cr_expect_throw(TestDivMonomial(m1, m2), std::exception);
}
