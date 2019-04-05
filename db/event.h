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
typedef std::vector<QLazyWeakPointer <track> > tracks;
typedef ::tracks tracks_type;
typedef std::vector<QLazyWeakPointer<image> > images;
typedef ::images images_type;

#pragma db object
class event
{
public:
	//tracks
	const tracks_type& tracks() const { return tracks_; }
	tracks_type& tracks() { return tracks_; }
	//images
	const images_type& images() const { return images_; }
	images_type& images() { return images_; }

	event() {}
	event(std::string event_name):event_name(event_name){
		submit_date = QDateTime::currentDateTime();}
private:
	friend class odb::access;
#pragma db id auto
	unsigned int event_id;
	std::string  event_name;
#pragma db type("DATETIME(6)")
	QDateTime  submit_date;
	unsigned int submitter_id;//placeholder
	bool         event_accepted;
#pragma db value_not_null inverse(event_track_)
	tracks_type tracks_;
#pragma db value_not_null inverse(event_image_)
	images_type images_;
};

#ifdef ODB_COMPILER
#include "track.h"
#include "image.h"
#include "user.h"
#endif

#endif // EVENT_H
