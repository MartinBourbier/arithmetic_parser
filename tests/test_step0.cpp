#include "../src/reducto.h"

#include <criterion/criterion.h>
#include <stdexcept>

bool PolyContain(Polynomial p, Monomial m)
{
    for (Monomial tmp : p.GetMonomials())
    {
        if (tmp == m)
            return true;
    }

    return false;
}

bool PolyEqual(Polynomial p1, Polynomial p2)
{
    for (Monomial m : p1.GetMonomials())
    {
        if (!PolyContain(p2, m))
            return false;
    }

    return p1.GetMonomials().size() == p2.GetMonomials().size();
}

Test(Step_0_A_Empty, Nothing)
{
    cr_assert(true);
}

Test(Step_0_B_PositiveNumber, Basic_Digit)
{
    Polynomial p = Reducto::Parse("3");

    Polynomial expected;
    expected = expected + Polynomial(Monomial(3));

    cr_assert(PolyEqual(expected, p));
}

Test(Step_0_B_PositiveNumber, Basic_TripleDigit)
{
    Polynomial p = Reducto::Parse("123");

    Polynomial expected;
    expected = expected + Polynomial(Monomial(123));

    cr_assert(PolyEqual(expected, p));
}

Test(Step_0_B_PositiveNumber, Basic_WhiteSpace_Begin)
{
    Polynomial p = Reducto::Parse("   123");

    Polynomial expected;
    expected = expected + Polynomial(Monomial(123));

    cr_assert(PolyEqual(expected, p));
}

Test(Step_0_B_PositiveNumber, Basic_WhiteSpace_End)
{
    Polynomial p = Reducto::Parse("123   ");

    Polynomial expected;
    expected = expected + Polynomial(Monomial(123));

    cr_assert(PolyEqual(expected, p));
}

Test(Step_0_B_PositiveNumber, Basic_WhiteSpace_BeginEnd)
{
    Polynomial p = Reducto::Parse("   123   ");

    Polynomial expected;
    expected = expected + Polynomial(Monomial(123));

    cr_assert(PolyEqual(expected, p));
}

Test(Step_0_C_VariableOnly, Basic_Digit)
{
    Polynomial p = Reducto::Parse("x");

    Polynomial expected;
    expected = expected + Polynomial(Monomial(1, 1));
    cr_assert(PolyEqual(expected, p));
}

Test(Step_0_C_VariableOnly, Basic_WhiteSpace_BeginEnd)
{
    Polynomial p = Reducto::Parse("   x   ");

    Polynomial expected;
    expected = expected + Polynomial(Monomial(1, 1));
    cr_assert(PolyEqual(expected, p));
}
