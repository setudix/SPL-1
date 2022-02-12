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

public:
    Time();
    Time(std::string);
    void displayTime();
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMin();
};
#endif