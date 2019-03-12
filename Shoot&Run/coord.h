#ifndef COORD_H
#define COORD_H
#include <iostream>

using namespace std;

class Coord
{
private:
    double longitude;
    double latitude;
public:
    Coord(double longitude, double latitude);
    double getLatitude() const;
    void setLatitude(double value);
    double getLongitude() const;
    void setLongitude(double value);
    void print();
};

#endif // COORD_H
