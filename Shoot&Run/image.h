#ifndef IMAGE_H
#define IMAGE_H
#include "coord.h"
#include "date.h"
#include "exif.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include<cstring>
class image
{
private:
    //unsigned int id;
    datetime date_;
    Coord coord;
    //unsigned int photographer_id;
    //bool accepted=0;
    string path;

public:
    image(string path):path(path),date_(0,0,0,0,0,0),coord(0.0,0.0){
        this->load();
    }
    image(string path,unsigned int y,unsigned int m,unsigned int d,unsigned int h,unsigned int min,unsigned int s,double lon, double lat):path(path),date_(y,m,d,h,min,s),coord(lat,lon){
        //this->load();
    }

    void addDate(unsigned int year,unsigned int month,unsigned int day,unsigned int hour,unsigned int minute ,unsigned int second){
        this->date_.setYear(year);
        this->date_.setMonth(month);
        this->date_.setDay(day);
        this->date_.setHour(hour);
        this->date_.setMinute(minute);
        this->date_.setSecond(second);
    }
    void load(){
        char *cstr = new char[this->path.length() + 1];
        strcpy(cstr, this->path.c_str());
        FILE *fp = fopen(cstr, "rb");

        fseek(fp, 0, SEEK_END);
        unsigned long fsize = ftell(fp);
        rewind(fp);
        unsigned char *buf = new unsigned char[fsize];
        if (fread(buf, 1, fsize, fp) != fsize) {
          printf("Can't read file.\n");
          delete[] buf;
        }
        fclose(fp);
        // Parse EXIF
        easyexif::EXIFInfo result;
        int code = result.parseFrom(buf, fsize);
        delete[] buf;
        if (code) {
          printf("Error parsing EXIF: code %d\n", code);
        }
        coord.setLongitude(result.GeoLocation.Longitude);
        coord.setLatitude(result.GeoLocation.Latitude);
        string stdido=result.DateTime.c_str();
        unsigned int year=stoul(stdido.substr(0,4));
        unsigned int month=stoul(stdido.substr(5,2));
        unsigned int day=stoul(stdido.substr(8,2));
        unsigned int hour=stoul(stdido.substr(11,2));
        unsigned int minute=stoul(stdido.substr(14,2));
        unsigned int second=stoul(stdido.substr(17,2));
        this->addDate(year,month,day,hour,minute,second);
    }
    void print(){
        //this->coord.print();
        cout<<"Kep keszitesenek a datuma: ";
        this->date_.print();
    }

    Coord getCoord() const
    {
        return coord;
    }
    datetime getDate() const;
    string getPath() const;
    bool operator > (const image& other) {
      return this->getDate().durationinseconds()>other.getDate().durationinseconds();
    }
    bool operator < (const image& other) {
      return this->getDate().durationinseconds()<other.getDate().durationinseconds();
    }
};



#endif // IMAGE_H


