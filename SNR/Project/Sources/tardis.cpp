#include "tardis.h"

tardis::tardis(QSharedPointer<track_type> track_id, double tardis_longitude,
	double tardis_latitude, QDateTime tardis_date)
	:tardis_longitude(tardis_longitude),tardis_latitude(tardis_latitude), tardis_date(tardis_date)
{
	this->track_id = track_id;
}

double tardis::getLongitude(){return tardis_longitude;}
double tardis::getLatitude(){return tardis_latitude;}
QDateTime tardis::getDate(){return tardis_date;}

