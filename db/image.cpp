#include "image.h"


image::image(unsigned int event_id, std::string PATH,
     unsigned int photographer_id,
     std::string datetime, double image_longitude,
	 double image_latitude)
	:event_id(event_id),PATH(PATH),
     photographer_id(photographer_id),
     datetime(datetime), image_longitude(image_longitude),
	image_latitude(image_latitude){}
