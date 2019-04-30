// Demonstrate some member functions and
// auxiliary operators of the Rational ADT
#include <iostream>
#include <string>
using namespace std;

#include "rational.h"

int main() 
{
	Rational r;
	Rational s;

	for (int i = 1; i <= 4; ++i) 
	{
		cout << "Enter rational number (a/b): ";
		cin >> r;
		cout << "Enter rational number (a/b): ";
		cin >> s;

		Rational Difference = r - s;
		Rational Division   = r / s;

		cout << r << " - " << s << " = " << Difference << endl;
		cout << r << " / " << s << " = " << Division   << endl << endl;
	}

	return 0;
}


