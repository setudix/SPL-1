#include "../include/Time.h"
#include "../include/commands.h"
#include <cstdio>

Time::Time()
{
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	min = 0;
	sec = 0;
	time_in_seconds = 0;
}
Time::Time(std::string str)
{
	setTime(str);
}

void Time::displayTimeWithDate()
{
	printf("%d-%02d-%02d  %02d:%02d:%02d", year, month,
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
int Time::getYear() const
{
	return year;
}

int Time::getMonth() const
{
	return month;
}

int Time::getDay() const
{
	return day;
}

int Time::getHour() const
{
	return hour;
}

int Time::getMin() const
{
	return min;
}

int Time::getSec() const
{
	return sec;
}
long long Time::getTimeInSeconds() const
{
	return time_in_seconds;
}

void Time::displayTime()
{
	printf("%03dd %02d:%02d:%02d", day, hour, min, sec);
}
void Time::setTime(std::string str)
{
	// 2022-03-05 03:56:40
	sscanf(str.c_str(), "%d %*c %d %*c %d %d %*c %d %*c %d",
		   &year, &month, &day, &hour, &min, &sec);
	// this is does not account for months and years **yet**
	time_in_seconds = day * 86400 + hour * 3600 + min * 60 + sec;
}
void Time::setTime(long long temp)
{
	time_in_seconds = temp;

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
bool operator==(const Time &a, const Time &b)
{
	return a.getTimeInSeconds() == b.getTimeInSeconds();
}
bool operator<(const Time &a, const Time &b)
{
	return a.getTimeInSeconds() < b.getTimeInSeconds();
}

bool operator>(const Time &a, const Time &b)
{
	return a.getTimeInSeconds() > b.getTimeInSeconds();
}

bool operator<=(const Time &a, const Time &b)
{
	return a.getTimeInSeconds() <= b.getTimeInSeconds();
}

bool operator!=(const Time &a, const Time &b)
{
	return a.getTimeInSeconds() != b.getTimeInSeconds();
}
bool operator>=(const Time &a, const Time &b)
{
	return a.getTimeInSeconds() >= b.getTimeInSeconds();
}
Time Time::getCurrentTime()
{
	Time a(runCommand(Util::getCurrentTimeCommand(), "r"));
	return a;
}