#include "image.h"

image::image(std::string PATH, QLazySharedPointer<event_type> event_id, QLazySharedPointer<user_type> user_id, QDateTime image_date, double image_longitude, double image_latitude):
	PATH(PATH), event_id(event_id), user_id(user_id), image_date(image_date), image_longitude(image_longitude), image_latitude(image_latitude){}
