#ifndef TRACK_H
#define TRACK_H

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <vector>

class tardis; class user; class odbevent;
typedef std::vector<QLazyWeakPointer<tardis> > tardises;
typedef ::tardises tardises_type;
typedef ::user user_type;
typedef ::odbevent odbevent_type;

#pragma db object
class track
{
public:
    const QLazySharedPointer<odbevent_type>& odbevent() const { return event_id; }
    void odbevent(QLazySharedPointer<odbevent_type> odbevent) { event_id = odbevent; }
	const QLazySharedPointer<user_type>& user() const { return user_id; }
	void user(QLazySharedPointer<user_type> user) { user_id = user; }
	const tardises_type& tardises() const { return tardises_; }
	tardises_type& tardises() { return tardises_; }

	track() {}
    track(QLazySharedPointer<odbevent_type>, QLazySharedPointer<user_type>);
    int getID();
private:
	friend class odb::access;
#pragma db id auto
	unsigned int track_id;
#pragma db value_not_null inverse(track_id)
	tardises_type tardises_;
#pragma db not_null
    QLazySharedPointer<odbevent_type> event_id;
#pragma db not_null
	QLazySharedPointer<user_type> user_id;
};

#ifdef ODB_COMPILER
#include "tardis.h"
#include "user.h"
#include "event.h"
#endif

#endif // TRACK_H
