#include "String.h"

//�������캯��
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

//���ƹ��캯��
String::String(const String& s) {
	if (!s.Empty())
	{
		p = new char[s.Size() + 1];
		strcpy(p, s.p);
	}
	else
		p = NULL;
}

//��������
String::~String() {
	if (p)
		delete[] p;
}

//��ֵ������
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

//����+�����
//
//��Ҫʹ�ñ�׼�����⺯��strcpy��strcat�����¸�д�����������
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

//��ȡ����
istream& operator>>(istream& sin, String& r)
{
	char c[256];
	sin.getline(c, 256);
	r = String(c);
	return sin;
}

//�������
ostream& operator<<(ostream& sout, const String& r)
{
	sout << r.p;
	return sout;
}

//���ع�ϵ�����
bool operator>(const String& l, const String& r) {
	return (strcmp(l.p, r.p) > 0);
}
bool operator==(const String& l, const String& r){
	return (strcmp(l.p, r.p) == 0);
}

//����4����ϵ�����������> ��==����
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

