#include "rational.h"

//Subtract(): subtract r from current Rational and return result
Rational Rational::Subtract(const Rational &r) const {
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	return Rational(a*d - b * c, b*d);
	// complete function body
}
Rational Rational::Divide(const Rational &r) const {
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	return Rational(a*d, b*c);
	// complete function body
}
int Rational::Compare(const Rational & r) const
{
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	if (b*d > 0)
	{
		if (a*d - b * c > 0)
			return 1;
		if (a*d - b * c == 0)
			return 0;
		if (a*d - b * c < 0)
			return -1;
	}
	else
	{
		if (a*d - b * c > 0)
			return -1;
		if (a*d - b * c == 0)
			return 0;
		if (a*d - b * c < 0)
			return 1;
	}
	
}
//operator -: overload subtraction for rationals
Rational operator-(const Rational &l, const Rational &r)
{
	return l.Subtract(r);
}

//operator /: overload division for rationals
Rational operator/(const Rational &l, const Rational &r) 
{
	return l.Divide(r);
}

bool operator==(const Rational & l, const Rational & r)
{
	if(l.Compare(r)==0)
	return true;
	else return false;
}

bool operator<(const Rational & l, const Rational & r)
{
	if (l.Compare(r) < 0)
		return true;
	else return false;
}

bool operator>(const Rational & l, const Rational & r)
{
	if (l.Compare(r) > 0)
		return true;
	else return false;
}

