#ifndef EVENT_H
#define EVENT_H

#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <odb/tr1/lazy-ptr.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <memory>
#include <string>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QDateTime>

class track; class user; class image;
typedef ::user user_type;
typedef std::vector<QLazyWeakPointer <track> > tracks;
typedef ::tracks tracks_type;
typedef std::vector<QLazyWeakPointer<image> > images;
typedef ::images images_type;

#pragma db object
class event
{
public:

	const tracks_type& tracks() const { return tracks_; }
	tracks_type& tracks() { return tracks_; }

	const images_type& images() const { return images_; }
	images_type& images() { return images_; }

	const QLazySharedPointer<user_type>& user() const { return submitter_id; }
	void user(QLazySharedPointer<user_type> user) { submitter_id = user; }

	event() {}
	event(std::string event_name):event_name(event_name){submit_date = QDateTime::currentDateTime();}
private:
	friend class odb::access;
#pragma db id auto
	unsigned int event_id;
	std::string  event_name;
#pragma db type("DATETIME")
	QDateTime    submit_date;
	bool		 event_accepted=0;
#pragma db value_not_null inverse(track_id)
	tracks_type  tracks_;
#pragma db value_not_null inverse(image_id)
	images_type  images_;
#pragma db not_null
	QLazySharedPointer<user_type> submitter_id;
};

#ifdef ODB_COMPILER
#include "track.h"
#include "image.h"
#include "user.h"
#endif

#endif // EVENT_H
