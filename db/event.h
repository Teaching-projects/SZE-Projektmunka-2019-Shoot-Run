#ifndef EVENT_H
#define EVENT_H

#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <odb/tr1/lazy-ptr.hxx>
#include <memory>
#include <string>
#include <vector>
#include <stdio.h>
#include <time.h>

//under construct
/*std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}*/

class track; class user; class image;
typedef std::vector<odb::tr1::lazy_weak_ptr<track> > tracks;
typedef ::tracks tracks_type;
typedef std::vector<odb::tr1::lazy_weak_ptr<image> > images;
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
	event(std::string event_name) : event_name(event_name) { submit_date = "123123"; }//currentDateTime();}
private:
	friend class odb::access;
#pragma db id auto
	unsigned int event_id;
	std::string  event_name;
	std::string  submit_date;
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
