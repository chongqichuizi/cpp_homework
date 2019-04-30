//Time.h Time类的声明
#ifndef _TIME_INC_
#define _TIME_INC_

#include <string>
using namespace std;

class Time
{
public:
	Time() :hour(23), minute(59), sec(57){}
	void Reset();

	Time operator++();
	Time operator--();
	int same();
	string GetTime()const;

private:
	int hour;
	int minute;
	int sec;
};
class Date
{
public:
	Date():_year(2018), _month(4), _day(25){}
	Date(int year, int month, int day);

	Date operator++(); //日期增加1天
	Date operator--(); //日期减少1天

	string GetDate()const;

private:
	int _year;
	int _month;
	int _day;
};
#endif
