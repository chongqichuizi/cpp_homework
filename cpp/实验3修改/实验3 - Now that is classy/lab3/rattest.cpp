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
		
		Rational Sum = r + s;
		Rational Product = r * s;

		cout << r << " + " << s << " = " << Sum << endl;
		cout << r << " * " << s << " = " << Product << endl << endl;
	}

	return 0;
}
