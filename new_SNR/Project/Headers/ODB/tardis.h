#ifndef TARDIS_H
#define TARDIS_H

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <string>
#include <QDateTime>

class track;
typedef ::track track_type;

#pragma db object
class tardis
{
public:
	const QSharedPointer<track_type>& track() const { return track_id; }
	void track(QSharedPointer<track_type> track) { track_id = track; }

	tardis() {}
	tardis(QSharedPointer<track_type>, double, double, QDateTime);
	double getLongitude();
	double getLatitude();
	QDateTime getDate();
private:
	friend class odb::access;
#pragma db id auto
    unsigned int tardis_id;
#pragma db not_null
	QSharedPointer<track_type> track_id;
	double       tardis_longitude;
	double       tardis_latitude;
#pragma db type("DATETIME")
	QDateTime	 tardis_date;
};

#ifdef ODB_COMPILER
#include "track.h"
#endif

#endif // TARDIS_H
