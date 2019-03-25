#ifndef TRACK_H
#define TRACK_H
#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <odb/tr1/lazy-ptr.hxx>
#include <vector>

class tardis; class user; class event;
typedef std::vector<odb::tr1::lazy_weak_ptr<tardis> > tardises;
typedef ::tardises tardises_type;
typedef ::user user_type;
typedef ::event event_type;


#pragma db object
class track
{
private:

//tardis_vector
const tardises_type& tardiss() const { return tardises_; }
tardises_type& tardiss() { return tardises_; }

	friend class odb::access;
#pragma db id auto
	unsigned int track_id;

#pragma db inverse(track_event_)
	odb::tr1::lazy_shared_ptr<event_type> event_track_;

#pragma db not_null
	odb::tr1::lazy_shared_ptr<user_type> user_track_;

#pragma db value_not_null inverse(track_tardis_)
	tardises_type tardises_;

public:
//event_id
const odb::tr1::lazy_weak_ptr<event_type>& event() const { return event_track_; }
void event(odb::tr1::lazy_weak_ptr<event_type> event) { event_track_ = event; }
//user_id
const odb::tr1::lazy_shared_ptr<user_type>& user() const { return user_track_; }
void user(odb::tr1::lazy_shared_ptr<user_type> user) { user_track_ = user; }

	track() {}
	track(odb::tr1::lazy_weak_ptr<event_type>, odb::tr1::lazy_shared_ptr<user_type>);


};

#ifdef ODB_COMPILER
#include "tardis.h"
#include "user.h"
#include "event.h"
#endif

#endif // TRACK_H
