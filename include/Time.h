#ifndef TIME_H
#define TIME_H
#include <string>
class Time
{
private:
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;

public:
    Time();
    Time(std::string);
    void displayTime();
    void setTime(long long tmep);
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMin();
    int getSec();
    long long getTimeInSeconds();
};

Time operator+(Time &a, Time &b);
Time operator-(Time &a, Time &b);

#endif