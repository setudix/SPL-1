#include "../include/Time.h"
#include <cstdio>

Time::Time(std::string str)
{
	sscanf(str.c_str(), "%d %*c %d %*c %d %d %*c %d %*s",
		   &year, &month, &day, &hour, &min);
}

void Time::displayTime()
{
	printf("%d-%d-%d  %d:%d\n", year, month,
		   day, hour, min);
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
