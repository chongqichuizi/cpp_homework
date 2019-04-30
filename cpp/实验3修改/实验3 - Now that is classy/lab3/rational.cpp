#include <iostream>
#include <string>
using namespace std;

#include "rational.h"
#include "gcd.h"
#include<math.h>
// (numer, denom) constructor
Rational::Rational(int numer, int denom)
{
	
	SetNumerator(numer);
	SetDenominator(denom);
	
}

// get the numerator
int Rational::Numerator() const 
{
	return NumeratorValue;
}

// get the denominator
int Rational::Denominator() const 
{
	return DenominatorValue;
}

// set the numerator
void Rational::SetNumerator(int numer)
{
	NumeratorValue = numer;
}

// set the denominator
void Rational::SetDenominator(int denom) 
{
	if (denom != 0)
		DenominatorValue = denom;
	else {
		cerr << "Illegal denominator: " << denom
		<< " using 1" << endl;
		DenominatorValue = 1;
	}
}

// adding Rationals
Rational Rational::Add(const Rational &r) const 
{
	
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	
	Rational Add(a*d + b*c, b*d);
	Add.Reduce();
	return Add;
}

// multiplying Rationals
Rational Rational::Multiply(const Rational &r) const 
{
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	Rational Mul(a*c, b*d);
	Mul.Reduce();
	return Mul;
}


// inserting a Rational
void Rational::Insert(ostream &sout) const 
{
	
	sout << Numerator() << '/' << Denominator();
	return;
}

// extracting a Rational
void Rational::Extract(istream &sin) 
{
	int  numer;
	int  denom;
	char slash;
	
	sin >> numer >> slash >> denom;
	
	SetNumerator(numer);
	SetDenominator(denom);
	
	return;
}

// adding Rationals
Rational operator+(const Rational &l, const Rational &r) 
{
	return l.Add(r);
}

// multiplying Rationals
Rational operator*(const Rational &l, const Rational &r)
{
	return l.Multiply(r);
}

// inserting a Rational
ostream& operator<<(ostream &sout, const Rational &r) 
{
	
	r.Insert(sout);
	return sout;
}

// extracting a Rational
istream& operator>>(istream &sin, Rational &r) 
{
	r.Extract(sin);
	return sin;
}
void Rational::Reduce() 
{
	int a = Numerator();
	int b = Denominator();
	if (a >= 0 && b > 0) {
		NumeratorValue = a / gcd(a, b);
		DenominatorValue = b / gcd(a, b);
	}
	if (a < 0 && b>0)
	{
		NumeratorValue = a / gcd(-a, b);
		DenominatorValue = b / gcd(-a, b);
	}
	if (a >= 0 && b < 0) {
		NumeratorValue = a / gcd(a, -b);
		DenominatorValue = b / gcd(a, -b);
	}
	else {
		NumeratorValue = a / gcd(-a, -b);
		DenominatorValue = b / gcd(-a, -b);
	}

}

