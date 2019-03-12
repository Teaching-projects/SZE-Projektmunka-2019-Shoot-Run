#include "track.h"

Track::Track()
{

}
void Track::addDate(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second){
    dates.push_back(new datetime(year,month,day,hour,minute,second));
}
void Track::addCoord(double longitude, double latitude)
{
     coordinates.push_back(new Coord(longitude,latitude));
}

void Track::kiir()
{
    for(unsigned int i=0;i<coordinates.size();i++){
        cout<<coordinates[i]->getLongitude()<<" "<<coordinates[i]->getLatitude()<<" "<<std::endl;
        dates[i]->print();
    }
}

