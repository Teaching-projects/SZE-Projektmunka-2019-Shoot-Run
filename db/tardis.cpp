#include "tardis.h"

tardis::tardis(odb::tr1::lazy_shared_ptr<track_type> track_, double tardis_longitude,
	double tardis_latitude, std::string time)
	:track_tardis_(track_tardis_), tardis_longitude(tardis_longitude),
	tardis_latitude(tardis_latitude), time(time){}
