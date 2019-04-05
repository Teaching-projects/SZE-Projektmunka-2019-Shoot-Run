#include "image.h"

image::image(std::string PATH, QLazySharedPointer<event_type> event_image_, QLazySharedPointer<user_type> user_image_, QDateTime image_date, double image_longitude, double image_latitude):
	PATH(PATH), event_image_(event_image_), user_image_(user_image_), image_date(image_date), image_longitude(image_longitude), image_latitude(image_latitude){}
