#include <QXmlStreamReader>
#include <QDebug>
#include <QString>
#include <QFile>
#include <iostream>
#include <iomanip>
#include "track.h"
#include "image.h"

int main()
{
    QString ido;
    std::string stdido;
    Track t("Ricsi");
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
    std::string path;
    std::cin>>path;
    image a(path);

    unsigned int j=0;
    for(auto i:t.getDates()){
        if((i->durationinseconds()>a.getDate().durationinseconds()-7) && (i->durationinseconds()<a.getDate().durationinseconds()+7)){
            if(t.getCoordinates()[j]->tav(a.getCoord())<50){
                cout<<t.getName()<<" rajt van "<<a.getPath()<<" kepen"<<endl;
                t.getCoordinates()[j]->print();
                i->print();
            }
        }
    j++;
    }

    return 0;
}
