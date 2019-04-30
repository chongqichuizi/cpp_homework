#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <iostream>
#include <string.h>
using namespace std;

class String
{
public:
	String(){ p = NULL; }    //默认构造函数
	String(char *str);       //参数构造函数
	String(const String& s); //复制构造函数
	~String();               //析构函数

	int  Size()const{ return p ? strlen(p) : 0; }
	bool Empty()const{ return (p == 0 || strlen(p) == 0); }

	const String& operator=(const String& s); //赋值操作符

	//请在此添加下标运算符[]函数的原型声明
	char operator[](int n);

	//其它运算符
	friend String operator+(const String& l, const String& r);
	friend bool operator> (const String& l, const String& r);
	friend bool operator==(const String& l, const String& r);
	friend istream& operator>>(istream& sin, String& r);
	friend ostream& operator<<(ostream& sout, const String& r);

private:
	char *p; //字符型指针，用于指向String存储的字符串
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
