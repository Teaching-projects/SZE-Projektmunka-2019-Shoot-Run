#ifndef COORD_H
#define COORD_H
#include <iomanip>
#include <iostream>
#include <math.h>
#include <cmath>
#define earthRadiusKm 6371.0

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
    double deg2rad(double deg) {
      return (deg * M_PI / 180);
    }
    double rad2deg(double rad) {
      return (rad * 180 / M_PI);
    }
    double tav(Coord other) {
      double lat1r, lon1r, lat2r, lon2r, u, v;
      lat1r = deg2rad(this->latitude);
      lon1r = deg2rad(this->longitude);
      lat2r = deg2rad(other.latitude);
      lon2r = deg2rad(other.longitude);
      u = sin((lat2r - lat1r)/2);
      v = sin((lon2r - lon1r)/2);
      return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v))*1000;
    }
};

#endif // COORD_H
