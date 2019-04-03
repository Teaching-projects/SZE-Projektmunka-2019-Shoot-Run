#include <QXmlStreamReader>
#include <QDebug>
#include <QString>
#include <QFile>
#include <iostream>
#include <iomanip>
#include "event.h"
#include <algorithm>

int main()
{
    event esemeny("Marathon",2018,9,26);
    QString ido;
    std::string stdido;
    Track t("Kocsis");
    Track t2("Attila");
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
                t.addCoord(inputStream.attributes().value("lon").toDouble(),inputStream.attributes().value("lat").toDouble());
            }
            if (name=="time"){
                ido=inputStream.readElementText();
                stdido=ido.toStdString();
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
    QFile file2("track2.gpx");
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File open error:" << file.errorString();
        return 1;
    }
    QXmlStreamReader inputStreamm(&file2);
    while (!inputStreamm.atEnd() && !inputStreamm.hasError())
    {
        inputStreamm.readNext();
        if (inputStreamm.isStartElement()) {
            QString name = inputStreamm.name().toString();
            if (name == "wpt"){
                t2.addCoord(inputStreamm.attributes().value("lon").toDouble(),inputStreamm.attributes().value("lat").toDouble());
            }
            if (name=="time"){
                ido=inputStreamm.readElementText();
                stdido=ido.toStdString();
                unsigned int year=stoul(stdido.substr(0,4));
                unsigned int month=stoul(stdido.substr(5,2));
                unsigned int day=stoul(stdido.substr(8,2));
                unsigned int hour=stoul(stdido.substr(11,2));
                unsigned int minute=stoul(stdido.substr(14,2));
                unsigned int second=stoul(stdido.substr(17,2));
                t2.addDate(year,month,day,hour,minute,second);
            }
        }
    }
    image egy("kep1",2016,2,16,14,0,33,49.21126,11.4627);
    image ketto("kep2",2016,2,16,14,0,36,49.2143,11.4612);
    image harom("kep3",2016,2,16,14,0,30,49.2144,11.4613);
    std::string path;
    std::cin>>path;
    image a(path);
    a.getCoord().print();
    esemeny.imageAdd(a);
    esemeny.imageAdd(egy);
    esemeny.imageAdd(ketto);
    esemeny.imageAdd(harom);
    cout<<endl<<endl;
    esemeny.sortt();
    esemeny.trackAdd(t);
    esemeny.trackAdd(t2);
    //a.print();
    cout<<endl;
    for(unsigned int i=0, j=0; i<t.getDates().size()&&j<esemeny.getImages().size();){
        if(esemeny.getImages()[j]->getDate().durationinseconds()<t.getDates()[i]->durationinseconds())
            j++;
        else if(esemeny.getImages()[j]->getDate().durationinseconds()>t.getDates()[i]->durationinseconds())
            i++;
        else if((t.getDates()[i]->durationinseconds()>esemeny.getImages()[j]->getDate().durationinseconds()-7)&&(t.getDates()[i]->durationinseconds()<esemeny.getImages()[j]->getDate().durationinseconds()+7)){
            if(t.getCoordinates()[i]->distance(esemeny.getImages()[j]->getCoord())<50){
                cout<<t.getName()<<" rajt van "<<esemeny.getImages()[j]->getPath()<<" kepen "<<t.getCoordinates()[i]->distance(esemeny.getImages()[j]->getCoord())<<" m"<<endl;
                t.getDates()[i]->print();
                j++;
            }
        }
    }
    return 0;
}
