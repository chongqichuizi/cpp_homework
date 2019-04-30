// Demonstrate some member functions and
// auxiliary operators of the Rational ADT
#include <iostream>
#include <string>

using namespace std;

#include "rational.h"

int main() {
	Rational r;
	Rational s;

	for (int i = 1; i <= 4; ++i) 
	{
		cout << "Enter rational number (a/b): ";
		cin >> r;
		cout << "Enter rational number (a/b): ";
		cin >> s;

        if ( r == s ) {
      	   cout << r << " == " << s << " is true \n" << endl;
        }
        else {
       	   cout << r << " == " << s << " is false \n" << endl;
        }

        if ( r < s ) {
      	   cout << r << " < " << s << " is true \n" << endl;
        }
        else {
       	   cout << r << " < " << s << " is false \n" << endl;
        }

        if ( r > s ) {
      	   cout << r << " > " << s << " is true \n" << endl;
        }
        else {
           cout << r << " > " << s << " is false \n" << endl;
        }
	}

	return 0;
}


