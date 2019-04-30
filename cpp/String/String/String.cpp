#include "String.h"

//参数构造函数
String::String(char* c)
{
	if (c)
	{
		p = new char[strlen(c) + 1];
		strcpy(p, c);
	}
	else
		p = NULL;
}

//复制构造函数
String::String(const String& s) {
	if (!s.Empty())
	{
		p = new char[s.Size() + 1];
		strcpy(p, s.p);
	}
	else
		p = NULL;
}

//析构函数
String::~String() {
	if (p)
		delete[] p;
}

//赋值操作符
const String& String::operator=(const String& s)
{
	if (this != &s)
	{
		if (p)
			delete[] p;
		p = new char[s.Size() + 1];
		strcpy(p, s.p);
	}

	return *this;
}

char String::operator[](int n)
{
	
	 return *(p + n);
	
}

//重载+运算符
//
//不要使用标准函数库函数strcpy和strcat，重新改写运算符＋函数
//
String operator+(const String& l, const String& r)
{
	char* c = new char[l.Size() + r.Size() + 1];
	char* pt = c;
	//strcpy(c, l.p);
	for (int j = 0; j < l.Size(); j++) {

		c[j] = *(l.p+j);
	}
	//strcat(c, r.p);
	for (int i = 0; i < r.Size(); i++) {
		c[i + l.Size()] = *(r.p+i);
	}
	c[l.Size() + r.Size()] =	NULL;
	String s(c);
	delete[] c;

	return s;
}

//提取操作
istream& operator>>(istream& sin, String& r)
{
	char c[256];
	sin.getline(c, 256);
	r = String(c);
	return sin;
}

//插入操作
ostream& operator<<(ostream& sout, const String& r)
{
	sout << r.p;
	return sout;
}

//重载关系运算符
bool operator>(const String& l, const String& r) {
	return (strcmp(l.p, r.p) > 0);
}
bool operator==(const String& l, const String& r){
	return (strcmp(l.p, r.p) == 0);
}

//其它4个关系运算符可以由> 和==导出
bool operator!=(const String& l, const String& r){
	return !(l == r);
}
bool operator<(const String& l, const String& r){
	return !(l>r) && (l != r);
}
bool operator>=(const String& l, const String& r){
	return !(l<r);
}
bool operator<=(const String& l, const String& r){
	return !(l>r);
}

