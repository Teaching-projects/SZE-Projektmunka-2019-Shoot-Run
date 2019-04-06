#ifndef IMAGE_H
#define IMAGE_H

#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <odb/tr1/lazy-ptr.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <string>
#include <QtCore/QDateTime>

class user; class event;
typedef ::event event_type;
typedef ::user user_type;

#pragma db object
class image
{
public:

	const QLazySharedPointer<event_type>& event() const { return event_id; }
	void event(QLazySharedPointer<event_type> event) { event_id = event; }

	const QLazySharedPointer<user_type>& user() const { return user_id; }
	void user(QLazySharedPointer<user_type> user) { user_id = user; }

	image() {}
	image(std::string, QLazySharedPointer<event_type>, QLazySharedPointer<user_type>, QDateTime, double, double);
private:
    friend class odb::access;
#pragma db id auto
    unsigned int image_id;
	std::string  PATH;
#pragma db not_null
	QLazySharedPointer<event_type> event_id;
#pragma db not_null
	QLazySharedPointer<user_type> user_id;
#pragma db type("DATETIME")
	QDateTime	 image_date;
    bool         image_accepted=0;
    double       image_longitude;
	double       image_latitude;
};

#ifdef ODB_COMPILER
#include "user.h"
#include "event.h"
#endif
#endif // IMAGE_H
