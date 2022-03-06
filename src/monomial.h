#ifndef MONOMIAL_H
#define MONOMIAL_H

#define null 0

#include <stdexcept>
#include <string>

class Monomial
{
    private:
        int coef;
        int degree;
    public:

        Monomial(int coef, int degree = 0);

        bool IsZero();
        int GetCoef();
        int GetDegree();

        static bool HasSameDegree(Monomial m1, Monomial m2)
        {
            return m1.GetDegree() == m2.GetDegree();
        }

        std::string ToString();

        bool operator==(Monomial m2)
        {
            return this->GetDegree() == m2.GetDegree() &&
                this->GetCoef() == m2.GetCoef();
        }

        bool operator!=(Monomial m2)
        {
            return !(*this == m2);
        }

        Monomial operator-()
        {
            return Monomial(-coef, degree);
        }

        Monomial operator+(Monomial m2)
        {
            if (IsZero())
                return m2;

            if (m2.IsZero())
                return *this;

            if (!HasSameDegree(*this, m2))
                throw std::exception();

            return Monomial(coef + m2.GetCoef(), degree);
        }

        Monomial operator-(Monomial m2)
        {
            return *this + -m2;
        }

        Monomial operator*(Monomial m2)
        {
            return Monomial(coef * m2.GetCoef(), degree + m2.GetDegree());
        }

        Monomial operator/(Monomial m2)
        {
            if (m2.IsZero())
                throw std::exception();

            return Monomial(coef / m2.GetCoef(), degree - m2.GetDegree());
        }
};

#endif    // MONOMIAL_H
