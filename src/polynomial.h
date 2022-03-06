#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "monomial.h"

#include <vector>

class Polynomial
{
    private:
        bool IsZero();
        int GetDegree();
        std::vector<Monomial> monomials;
    public:
        Polynomial();
        Polynomial(Monomial m);

        void AddMonomial(Monomial m);

        Polynomial operator-();
        Polynomial operator+(Polynomial p);
        Polynomial operator-(Polynomial p);
        Polynomial operator*(Polynomial p);
        Polynomial operator/(Polynomial p);
        Polynomial operator^(Polynomial p);

        Monomial GetLead();
        std::vector<Monomial> GetMonomials();
        std::string ToString();
};

#endif    // POLYNOMIAL_H
