#include "Time.h"
Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}
Date Date::operator++()
{
	int n;
	if (_month = 2)
		n = 28;
	if (_month = 1, 3, 5, 7, 8, 10, 12)
		n = 31;
	if (_month = 4, 6, 9, 11)
		n = 30;

	if (++_day > n)
	{
		_day = 1;
		++_month;
	}

	if (_month > 12)
	{
		_month = 1;
		++_year;
	}

	return *this;
}

Date Date::operator--()
{
	int n;
	if (_month = 2)
		n = 28;
	if (_month = 1, 3, 5, 7, 8, 10, 12)
		n = 31;
	if (_month = 4, 6, 9, 11)
		n = 30;

	if (--_day < 1)
	{
		_day = n;
		--_month;
	}

	if (_month < 1)
	{
		_month = 12;
		--_year;
	}

	return *this;
}

string Date::GetDate()const
{
	char c[32];
	sprintf_s(c, 32, "%02d-%02d-%02d", _year, _month, _day);
	return string(c);
}