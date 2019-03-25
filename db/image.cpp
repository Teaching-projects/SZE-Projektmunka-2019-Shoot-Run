#include "image.h"

image::image(std::string PATH, odb::tr1::lazy_shared_ptr<event_type> event_image_, odb::tr1::lazy_shared_ptr<user_type> user_image_, std::string datetime, double image_longitude, double image_latitude):
	PATH(PATH), event_image_(event_image_), user_image_(user_image_), datetime(datetime), image_longitude(image_longitude), image_latitude(image_latitude){}
