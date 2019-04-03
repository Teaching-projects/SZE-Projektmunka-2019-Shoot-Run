#ifndef DATE_H
#define DATE_H
#include <iostream>

//#pragma db object
class date
{
protected:
    unsigned int year;
    unsigned int month;
    unsigned int day;
public:
    //date(unsigned int year, unsigned int month, unsigned int day);
    date(unsigned int year, unsigned int month, unsigned int day):year(year),month(month),day(day){}

    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;
    void setYear(unsigned int value);
    void setMonth(unsigned int value);
    void setDay(unsigned int value);
};
//#pragma db object
class datetime : public date
{
private:
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
public:
    datetime(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second)
        :date(year,month,day), hour(hour), minute(minute), second(second){}
    void print(){
        std::cout<<getYear()<<"-"<<getMonth()<<"-"<<getDay()<<" "<<getHour()<<"."<<getMinute()<<"."<<getSecond()<<std::endl;
    }

        unsigned int getHour() const;
        unsigned int getMinute() const;
        unsigned int getSecond() const;
        unsigned int durationinseconds() const;
        void setHour(unsigned int value);
        void setMinute(unsigned int value);
        void setSecond(unsigned int value);
        bool operator == ( const datetime &other){
            return (year==other.year and month==other.month and day==other.day and hour==other.hour and minute==other.minute and second==other.second);
        }
        bool operator > (const datetime& other) {
          return this->durationinseconds() > other.durationinseconds();
        }
        bool operator < (const datetime& other) {
          return this->durationinseconds() < other.durationinseconds();
        }
};



#endif // DATE_H
