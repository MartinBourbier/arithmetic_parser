#include "monomial.h"

Monomial::Monomial(int _coef, int _degree)
{
    coef = _coef;
    degree = _degree;

    if (IsZero())
        degree = -1;
    else if (degree <= -1)
        throw std::exception();
}

bool Monomial::IsZero() { return coef == 0; }

int Monomial::GetCoef() { return coef; }

int Monomial::GetDegree() { return degree; }

std::string Monomial::ToString()
{
    if (degree == 0)
        return std::to_string(coef);

    if (degree == 1)
        return std::to_string(coef) + 'x';

    std::string coef_str = "";

    if (coef == -1)
        coef_str += '-';
    else if (coef != 1)
        coef_str += std::to_string(coef);

    return coef_str + "x^" + std::to_string(degree);
}
