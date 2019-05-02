#include "image.h"
#include <QFile>
image::image(std::string PATH, QLazySharedPointer<odbevent_type> event_id,
             QLazySharedPointer<user_type> user_id, QDateTime image_date,
             double image_longitude, double image_latitude):
    PATH(PATH), event_id(event_id), user_id(user_id), image_date(image_date),
    image_longitude(image_longitude), image_latitude(image_latitude)
{
    loadfrompath();
}

double image::getLatitude(){
    return image_latitude;
}
double image::getLongitude(){
    return image_longitude;
}
QDateTime image::getDate(){
    return image_date;
}
std::string image::getPATH(){
    return PATH;
}
void image::Accept(){
    this->image_accepted = true;
}

void image::loadfrompath(){
    QFile file(QString::fromStdString(this->getPATH()));
    if (!file.open(QIODevice::ReadOnly)) return;
    this->blob = file.readAll();
}

QByteArray image::getBlob(){
    return this->blob;
}

bool image::isAccepted(){
    return image_accepted;
}
