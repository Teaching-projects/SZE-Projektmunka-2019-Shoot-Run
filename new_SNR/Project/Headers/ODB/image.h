#ifndef IMAGE_H
#define IMAGE_H

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <string>
#include <QDateTime>

class user; class odbevent;
typedef ::odbevent odbevent_type;
typedef ::user user_type;

#pragma db object
class image
{
public:
    const QLazySharedPointer<odbevent_type>& odbevent() const { return event_id; }
    void odbevent(QLazySharedPointer<odbevent_type> odbevent) { event_id = odbevent; }
	const QLazySharedPointer<user_type>& user() const { return user_id; }
	void user(QLazySharedPointer<user_type> user) { user_id = user; }

	image() {}
    image(std::string, QLazySharedPointer<odbevent_type>, QLazySharedPointer<user_type>, QDateTime, double, double);
	double getLatitude();
	double getLongitude();
	QDateTime getDate();
	std::string getPATH();
	void Accept();
    void loadfrompath();
    QByteArray getBlob();
    bool isAccepted();
private:
	friend class odb::access;
#pragma db id auto
    unsigned int image_id;
	std::string  PATH;
#pragma db not_null
    QLazySharedPointer<odbevent_type> event_id;
#pragma db not_null
	QLazySharedPointer<user_type> user_id;
#pragma db type("DATETIME")
	QDateTime	 image_date;
    bool         image_accepted=0;
    double       image_longitude;
	double       image_latitude;
#pragma db type("LONGBLOB")
    QByteArray blob;
};

#ifdef ODB_COMPILER
#include "user.h"
#include "event.h"
#endif

#endif // IMAGE_H
