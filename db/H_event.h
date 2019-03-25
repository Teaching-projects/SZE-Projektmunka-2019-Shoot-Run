#ifndef H_EVENT_H
#define H_EVENT_H

#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <odb/tr1/lazy-ptr.hxx>
#include <memory>
#include <string>
#include <vector>
#include <stdio.h>
#include <time.h>

class image; class track; class user;
typedef ::track track_type;
#pragma db object
class H_event
{
private:
	friend class odb::access;
#pragma db id auto
	unsigned int event_id;
	std::string  event_name;
	std::string  submit_date;
	unsigned int submitter_id;
	bool         event_accepted;
#pragma db not_null
	odb::tr1::lazy_shared_ptr<track_type> track_event_;
public:
	const odb::tr1::lazy_shared_ptr<track_type>& track() const { return track_event_; }
	void position(odb::tr1::lazy_shared_ptr<track_type> track) { track_event_ = track; }
	H_event(std::string, unsigned int);
	H_event() {}
};

#ifdef ODB_COMPILER
#include "track.h"
#include "image.h"
#endif
#endif // h_EVENT_H
