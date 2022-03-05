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
    long long time_in_seconds;

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
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMin() const;
    int getSec() const;
    void displayTime();
    long long getTimeInSeconds() const;
};

Time operator+(Time &a, Time &b);
Time operator-(Time &a, Time &b);
bool operator==(const Time &a, const Time &b);
bool operator<(const Time &a, const Time &b);

#endif