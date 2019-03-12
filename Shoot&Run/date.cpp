#include "date.h"



unsigned int date::getMonth() const
{
    return month;
}


unsigned int date::getDay() const
{
    return day;
}

void date::setYear(unsigned int value)
{
    year = value;
}

void date::setMonth(unsigned int value)
{
    month = value;
}

void date::setDay(unsigned int value)
{
    day = value;
}

unsigned int date::getYear() const
{
    return year;
}

unsigned int datetime::getMinute() const
{
    return minute;
}

unsigned int datetime::getSecond() const
{
    return second;
}

void datetime::setHour(unsigned int value)
{
    hour = value;
}

void datetime::setMinute(unsigned int value)
{
    minute = value;
}

void datetime::setSecond(unsigned int value)
{
    second = value;
}

unsigned int datetime::getHour() const
{
    return hour;
}
