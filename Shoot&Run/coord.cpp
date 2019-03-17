#include "coord.h"

double Coord::getLatitude() const
{
    return latitude;
}

void Coord::setLatitude(double value)
{
    latitude = value;
}

double Coord::getLongitude() const
{
    return longitude;
}

void Coord::setLongitude(double value)
{
    longitude = value;
}

Coord::Coord(double longitude, double latitude):longitude(longitude),latitude(latitude)
{

}
void Coord::print(){
    cout<<setprecision(8)<<getLatitude()<<"\t"<<getLongitude()<<endl;
}
