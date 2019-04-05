#include "tardis.h"

tardis::tardis(QSharedPointer<track_type> track_, double tardis_longitude,
	double tardis_latitude, QDateTime tardis_date)
	:tardis_longitude(tardis_longitude),
	tardis_latitude(tardis_latitude), tardis_date(tardis_date){
	this->track_tardis_ = track_tardis_;
}
