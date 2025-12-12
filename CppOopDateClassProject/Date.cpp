#include "Date.h"

Date::Date(int day, int month, int year)
{
	if (year < 0 || year > 9999)
		throw -1;
	if (month < 0 || month > 12)
		throw -1;
	if (day < 0)
		throw -1;
	if (month != 2 && day > monthDays[month])
		throw -1;
	if (month == 2 && day > (monthDays[month] + IsLeapYear(year)))
		throw -1;

	this->year = year;
	this->month = month;
	this->day = day;
}

Date::Date() : Date(1, 1, 0){}

bool Date::IsLeapYear(int year)
{
	return (!(year % 4) && year % 100 || !(year % 400));
}

int Date::Day() const
{
	return this->day; 
}

int Date::Month() const { return this->month; }

int Date::Year() const { return this->year; }

Date Date::AddDays(int days)
{
	int md;
	int m = this->month;
	int y{};

	if (days > 0)
	{
		md = monthDays[this->month] - this->day;

		while (days >= md)
		{
			days -= md;
			if (days == 0)
			{
				days = monthDays[m];
				break;
			}
			m++;
			if (m > 12)
			{
				m = 1;
				y++;
			}
			md = monthDays[m];
		}
		this->day = days;
		this->month = m;
		this->year += y;
	}
	else
	{
		md = this->day;
		days = -days;

		while (days >= md)
		{
			days -= md;
			m--;
			if(m < 1)
			{
				m = 12;
				y--;
			}
			if (days == 0)
			{
				days = 0;
				break;
			}
			md = monthDays[m];
		}
		this->day = monthDays[m] - days;
		this->month = m;
		this->year += y;
	}
	

	return *this;
}

int Date::CompareTo(Date other)
{
	if (this->year - other.year)
		return this->year - other.year;
	if (this->month - other.month)
		return this->month - other.month;
	
	return this->day - other.day;
}

int Date::YearDays()
{
	int days{};
	for (int m{ 1 }; m < this->month; m++)
	{
		days += this->monthDays[m];
		if (m == 2)
			days += IsLeapYear(this->year);
	}
		
	days += this->day;
	return days;
}

int Date::DateSpan(Date other)
{
	Date& minDate{ (this->CompareTo(other) < 0) ? *this : other };
	Date& maxDate{ (this->CompareTo(other) > 0) ? *this : other };

	int minDateDays{ minDate.YearDays() };
	int maxDateDays{ maxDate.YearDays() };

	for (int year{ minDate.year }; year < maxDate.year; year++)
		maxDateDays += TotalDays + IsLeapYear(year);

	int days{ maxDateDays - minDateDays };
	
	return (this == &minDate) ? days : -days;
}

Date Date::Now()
{
	SYSTEMTIME st;
	GetSystemTime(&st);

	return Date((int)st.wDay, (int)st.wMonth, (int)st.wYear);
}

std::ostream& operator<<(std::ostream& out, const Date& d)
{
	out << d.day << "." << d.month << "." << d.year;
	return out;
}
