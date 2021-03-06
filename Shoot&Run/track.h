#ifndef TRACK_H
#define TRACK_H

#include "coord.h"
#include <vector>
#include <string>
#include "date.h"

class Track
{
private:
    string name;
    unsigned int id;
    vector<Coord*> coordinates;
    vector<datetime*> dates;
public:
    Track(string name);
    //vector<datetime*> dates;
    //vector<Coord*> coordinates;
    void addCoord(double longitude, double latitude);
    void addDate(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second);
    void kiir();
    string getName() const;
    vector<Coord *> getCoordinates() const;
    vector<datetime *> getDates() const;
};

#endif // TRACK_H
