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
    void displayTimeWithDate();
    void setTime(long long temp);
    void setTime(std::string);
    void setYear(int year);
    void setMonth(int month);
    void setHour(int hour);
    void setDay(int day);
    void setMin(int min);
    void setSec(int sec);
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMin();
    int getSec();
    void displayTime();
    long long getTimeInSeconds();
};

Time operator+(Time &a, Time &b);
Time operator-(Time &a, Time &b);

#endif