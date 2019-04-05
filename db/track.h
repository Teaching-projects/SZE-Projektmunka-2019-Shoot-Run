#ifndef TRACK_H
#define TRACK_H

#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <odb/tr1/lazy-ptr.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <vector>

class tardis; class user; class event;
typedef std::vector<QLazyWeakPointer<tardis> > tardises;
typedef ::tardises tardises_type;
typedef ::user user_type;
typedef ::event event_type;

#pragma db object
class track
{
private:
friend class odb::access;

#pragma db id auto
	unsigned int track_id;
#pragma db value_not_null inverse(track_tardis_) //tardis
	tardises_type tardises_;
#pragma db not_null //event
	QLazySharedPointer<event_type> event_track_;
#pragma db not_null //user
	QLazySharedPointer<user_type> user_track_;
public:
	//event
	const QLazySharedPointer<event_type>& event() const { return event_track_; }
	void event(QLazySharedPointer<event_type> event) { event_track_ = event; }
	//user
	const QLazySharedPointer<user_type>& user() const { return user_track_; }
	void user(QLazySharedPointer<user_type> user) { user_track_ = user; }
	//tardis vector
	const tardises_type& tardises() const { return tardises_; }
	tardises_type& tardises() { return tardises_; }
	track() {}
	track(QLazySharedPointer<event_type>, QLazySharedPointer<user_type>);
};

#ifdef ODB_COMPILER
#include "tardis.h"
#include "user.h"
#include "event.h"
#endif

#endif // TRACK_H
