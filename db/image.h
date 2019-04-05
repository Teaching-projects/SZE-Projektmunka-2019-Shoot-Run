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
private:
    friend class odb::access;
#pragma db id auto
    unsigned int image_id;
	std::string  PATH;
#pragma db not_null //event_id
	QLazySharedPointer<event_type> event_image_;
#pragma db not_null //user_id
	QLazySharedPointer<user_type> user_image_;
#pragma db type("DATETIME(6)")
	QDateTime	 image_date;
    bool         image_accepted;
    double       image_longitude;
	double       image_latitude;
public:
	//event
	const QLazySharedPointer<event_type>& event() const { return event_image_; }
	void event(QLazySharedPointer<event_type> event) { event_image_ = event; }
	//user
	const QLazySharedPointer<user_type>& user() const { return user_image_; }
	void user(QLazySharedPointer<user_type> user) { user_image_ = user; }

    image(){}
    image(std::string, QLazySharedPointer<event_type>, QLazySharedPointer<user_type>, QDateTime,double,double);
};

#ifdef ODB_COMPILER
#include "user.h"
#include "event.h"
#endif
#endif // IMAGE_H
