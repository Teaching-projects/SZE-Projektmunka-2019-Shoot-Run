#ifndef TARDIS_H
#define TARDIS_H

#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <odb/tr1/lazy-ptr.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <string>
#include <iostream>
#include <QtCore/QDateTime>

class track;
typedef ::track track_type;

#pragma db object //pointer(QSharedPointer)
class tardis
{
private:
 friend class odb::access;
#pragma db id auto
    unsigned int tardis_id;
#pragma db not_null //track
	QSharedPointer<track_type> track_tardis_;
	double       tardis_longitude;
	double       tardis_latitude;
#pragma db type("DATETIME(6)")
	QDateTime	 tardis_date;
public:
	//track
	const QSharedPointer<track_type>& track() const { return track_tardis_; }
	void track(QSharedPointer<track_type> track) { track_tardis_ = track; }

    tardis(){}
    tardis(QSharedPointer<track_type>,double,double, QDateTime);
};

#ifdef ODB_COMPILER
#include "track.h"
#endif

#endif // TARDIS_H
