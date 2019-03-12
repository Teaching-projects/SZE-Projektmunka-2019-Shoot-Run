#include <QXmlStreamReader>
#include <QDebug>
#include <QString>
#include <QFile>
#include <iostream>
#include <iomanip>
#include "track.h"
#include "image.h"
#define earthRadiusKm 6371.0
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}
double rad2deg(double rad) {
  return (rad * 180 / M_PI);
}

double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v))*1000;
}

int main()
{
    QString ido;
    std::string stdido;
    Track t;
    QFile file("track.gpx");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File open error:" << file.errorString();
        return 1;
    }
    QXmlStreamReader inputStream(&file);
    while (!inputStream.atEnd() && !inputStream.hasError())
    {
        inputStream.readNext();
        if (inputStream.isStartElement()) {
            QString name = inputStream.name().toString();
            if (name == "wpt"){
                //qDebug() << "lon:" << inputStream.attributes().value("lon").toFloat() << "lat:" << inputStream.attributes().value("lat").toFloat();
                t.addCoord(inputStream.attributes().value("lon").toDouble(),inputStream.attributes().value("lat").toDouble());
            }
            if (name=="time"){
                ido=inputStream.readElementText();
                stdido=ido.toStdString();
                //
                unsigned int year=stoul(stdido.substr(0,4));
                unsigned int month=stoul(stdido.substr(5,2));
                unsigned int day=stoul(stdido.substr(8,2));
                unsigned int hour=stoul(stdido.substr(11,2));
                unsigned int minute=stoul(stdido.substr(14,2));
                unsigned int second=stoul(stdido.substr(17,2));
                t.addDate(year,month,day,hour,minute,second);
            }
        }
    }
    t.kiir();
    std::string path;
    std::cin>>path;
    image a(path);
    a.kiir();

    /*Coord koord1(50.2333,49.2333);
    Coord koord2(50.2334,49.2334);

    cout<<"ASDADSDSDS:  "<<distanceEarth(koord1.getLatitude(),koord1.getLongitude(),koord2.getLatitude(),koord2.getLongitude())<<endl;
    */
    unsigned int j=0;
    for(auto i:t.dates){
        j++;
        if(*i==a.date_){
            cout<<setprecision(8)<<t.coordinates[j-1]->getLongitude()<<" "<<setprecision(8)<<t.coordinates[j-1]->getLatitude()<<endl;
        }

    }

    return 0;
}
