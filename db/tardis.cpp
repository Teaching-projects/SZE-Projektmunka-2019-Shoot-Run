#include "tardis.h"


tardis::tardis(unsigned int track_id, double tardis_longitude,
	double tardis_latitude, std::string time)
	:track_id(track_id), tardis_longitude(tardis_longitude),
	tardis_latitude(tardis_latitude), time(time){}
