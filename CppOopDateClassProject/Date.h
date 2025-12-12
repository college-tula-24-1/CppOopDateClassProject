#pragma once
#include <iostream>
#include <Windows.h>

class Date
{
	int day;
	int month;
	int year;

	int monthDays[13]{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	const int TotalDays{ 365 };
public:
	
	Date(int day, int month, int year);
	Date();
	
	bool IsLeapYear(int year);

	int Day() const;
	int Month() const;
	int Year() const;

	Date AddDays(int days);

	int CompareTo(Date other);

	int YearDays();
	int DateSpan(Date other);

	static Date Now();

	friend std::ostream& operator<<(std::ostream& out, const Date& d);
};

