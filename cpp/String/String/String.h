#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <iostream>
#include <string.h>
using namespace std;

class String
{
public:
	String(){ p = NULL; }    //Ĭ�Ϲ��캯��
	String(char *str);       //�������캯��
	String(const String& s); //���ƹ��캯��
	~String();               //��������

	int  Size()const{ return p ? strlen(p) : 0; }
	bool Empty()const{ return (p == 0 || strlen(p) == 0); }

	const String& operator=(const String& s); //��ֵ������

	//���ڴ�����±������[]������ԭ������
	char operator[](int n);

	//���������
	friend String operator+(const String& l, const String& r);
	friend bool operator> (const String& l, const String& r);
	friend bool operator==(const String& l, const String& r);
	friend istream& operator>>(istream& sin, String& r);
	friend ostream& operator<<(ostream& sout, const String& r);

private:
	char *p; //�ַ���ָ�룬����ָ��String�洢���ַ���
};

String operator+(const String& l, const String& r);

bool operator> (const String& l, const String& r);
bool operator==(const String& l, const String& r);
bool operator!=(const String& l, const String& r);
bool operator< (const String& l, const String& r);
bool operator>=(const String& l, const String& r);
bool operator<=(const String& l, const String& r);


istream& operator>>(istream& sin, String& r);
ostream& operator<<(ostream& sout, const String& r);

#endif
