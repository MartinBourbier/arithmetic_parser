#include "polynomial.h"

bool Polynomial::IsZero() { return monomials.size() == 0; }

int Polynomial::GetDegree()
{
    Monomial lead = GetLead();
    return (lead == null) ? -1 : lead.GetDegree();
}

Polynomial::Polynomial() {}

Polynomial::Polynomial(Monomial m)
{
    if (!m.IsZero())
        monomials.push_back(m);
}

void Polynomial::AddMonomial(Monomial m)
{
    monomials.push_back(m);
}

Polynomial Polynomial::operator-()
{
    Polynomial res;

    for(Monomial m : monomials)
    {
        res.monomials.push_back(-m);
    }

    return res;
}

Polynomial Polynomial::operator+(Polynomial p)
{
    Polynomial res;

    int i = 0;
    int j = 0;

    int n = GetMonomials().size();
    int m = p.GetMonomials().size();

    while (i < n && j < m)
    {
        Monomial m1 = GetMonomials().at(i);
        Monomial m2 = p.GetMonomials().at(j);

        if (m1.GetDegree() == m2.GetDegree())
        {
            Monomial m3 = m1 + m2;

            if (!m3.IsZero())
                res.AddMonomial(m3);

            i++;
            j++;
        }
        else if (m1.GetDegree() < m2.GetDegree())
        {
            res.AddMonomial(m1);
            i++;
        }
        else
        {
            res.AddMonomial(m2);
            j++;
        }
    }

    while (i < GetMonomials().size())
        res.AddMonomial(GetMonomials().at(i++));

    while (j < p.GetMonomials().size())
        res.AddMonomial(p.GetMonomials().at(j++));

    return res;
}

Polynomial Polynomial::operator-(Polynomial p) { return *this + -p; }

Polynomial Polynomial::operator*(Polynomial p)
{
    Polynomial res;

    int n = GetMonomials().size();
    int m = p.GetMonomials().size();

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            res = res + Polynomial(GetMonomials().at(i) * p.GetMonomials().at(j));
        }
    }

    return res;
}

Polynomial Polynomial::operator/(Polynomial p)
{
    if (p.IsZero())
        throw std::exception();

    int i = p.GetMonomials().size();

    Polynomial q;
    Polynomial r = *this;

    while (!r.IsZero() && r.GetDegree() >= p.GetDegree() && i >= 0)
    {
        Polynomial t(r.GetLead() / p.GetLead());

        if (t.IsZero())
            return q;

        q = q + t;
        r = r - t * p;
        i--;
    }

    return q;
}

Polynomial Polynomial::operator^(Polynomial p)
{
    if (p.IsZero())
        return Polynomial(Monomial(1));

    Monomial lead = p.GetLead();

    if (lead.GetDegree() != 0)
        throw std::exception();

    int n = lead.GetCoef();

    if (n < 0)
        throw std::exception();

    Polynomial res = *this;

    for (int i = 1; i < n; ++i)
        res = res * *this;

    return res;
}

Monomial Polynomial::GetLead()
{
    if (IsZero())
        return null;

    return GetMonomials().at(GetMonomials().size() - 1);
}

std::vector<Monomial> Polynomial::GetMonomials() { return monomials; }

std::string Polynomial::ToString()
{
    if (IsZero())
        return "0";

    std::string res = "";

    for (int i = GetMonomials().size() - 1; i > 0; --i)
    {
        res += GetMonomials().at(i).ToString();
        res += " + ";
    }

    return res + GetMonomials().at(0).ToString();
}
