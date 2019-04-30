#include <iostream>
#include "String.h"
using namespace std;

int main()
{
	String str1, str2, str3, temp;
	cout << "please input three strings:"<<endl;
		cin >> str1 >> str2 >> str3;

	cout << "str1 + str2 = " << str1 + str2 << endl;

	if (str2 > str3){
		temp = str2; str2 = str3; str3 = temp;
	}

	if (str1 <= str2)
		cout << str1 << " " << str2 << " " << str3 << endl;
	else if (str1 <= str3)
		cout << str2 << " " << str1 << " " << str3 << endl;
	else
		cout << str2 << " " << str3 << " " << str1 << endl;

	//°´×Ö·ûÖð¸öÊä³östr3×Ö·û´®
	for (int i = 0; i < str3.Size(); ++i)
		cout << str3[i];

	cout << endl;
	return 0;
}
