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
    //datetime date_;
    Coord coord;
    //unsigned int photographer_id;
    //bool accepted=0;
    string path;

public:
    datetime date_;
    image(string path):path(path),date_(0,0,0,0,0,0),coord(0.0,0.0){
        this->load();
    }

    void addDate(unsigned int year,unsigned int month,unsigned int day,unsigned int hour,unsigned int minute ,unsigned int second){
        this->date_.setYear(year);
        this->date_.setMonth(month);
        this->date_.setDay(day);
        this->date_.setHour(hour);
        this->date_.setMinute(minute);
        this->date_.setSecond(second);
    }
    //cout<<path;
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
    void kiir(){
        this->coord.print();
        this->date_.print();
    }

    };



#endif // IMAGE_H
