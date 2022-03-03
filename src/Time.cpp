#include "../include/Time.h"
#include <cstdio>

Time::Time()
{
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	min = 0;
	sec = 0;
}
Time::Time(std::string str)
{
	sscanf(str.c_str(), "%d %*c %d %*c %d %d %*c %d %*c %d %*s",
		   &year, &month, &day, &hour, &min, &sec);
}

void Time::displayTime()
{
	printf("%d-%02d-%02d  %02d:%02d:%02d\n", year, month,
		   day, hour, min, sec);
}
void Time::setYear(int year)
{
	this->year = year;
}
void Time::setMonth(int month)
{
	this->month = month;
}
void Time::setDay(int day)
{
	this->day = day;
}
void Time::setHour(int hour)
{
	this->hour = hour;
}
void Time::setMin(int min)
{
	this->min = min;
}
void Time::setSec(int sec)
{
	this->sec = sec;
}
int Time::getYear()
{
	return year;
}

int Time::getMonth()
{
	return month;
}

int Time::getDay()
{
	return day;
}

int Time::getHour()
{
	return hour;
}

int Time::getMin()
{
	return min;
}

int Time::getSec()
{
	return sec;
}
long long Time::getTimeInSeconds()
{
	// this is does not account for months and years **yet**
	return day * 86400 + hour * 3600 + min * 60 + sec;
}

void Time::setTime(long long temp)
{
	day = temp / 86400;
	temp %= 86400;
	hour = temp / 3600;
	temp %= 3600;
	min = temp / 60;
	temp %= 60;
	sec = temp;
}
Time operator+(Time &a, Time &b)
{
	long long temp = a.getTimeInSeconds() + b.getTimeInSeconds();

	Time c;
	c.setTime(temp);

	return c;
}

Time operator-(Time &a, Time &b)
{
	// Always returns positive value, as - will mainly be used as difference.
	long long temp = a.getTimeInSeconds() - b.getTimeInSeconds();
	temp = (temp < 0) ? -1 * temp : temp;

	Time c;
	c.setTime(temp);

	return c;
}