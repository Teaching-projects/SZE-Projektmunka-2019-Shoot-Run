#include "image.h"

image::image(std::string PATH, QLazySharedPointer<event_type> event_id, QLazySharedPointer<user_type> user_id, QDateTime image_date, double image_longitude, double image_latitude):
	PATH(PATH), event_id(event_id), user_id(user_id), image_date(image_date), image_longitude(image_longitude), image_latitude(image_latitude){}

double image::getLatitude(){return image_latitude;}
double image::getLongitude(){return image_longitude;}
QDateTime image::getDate(){return image_date;}
std::string image::getPATH(){return PATH;}
void image::Accept(){image_accepted = true;}
