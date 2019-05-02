#ifndef EVENT_H
#define EVENT_H

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <string>
#include <vector>
#include <QDateTime>

class track; class user; class image;
typedef user user_type;
typedef std::vector<QLazyWeakPointer <track> > tracks;
typedef tracks tracks_type;
typedef std::vector<QLazyWeakPointer<image> > images;
typedef images images_type;

#pragma db object
class odbevent
{
public:
	const tracks_type& tracks() const { return tracks_; }
	tracks_type& tracks() { return tracks_; }
	const images_type& images() const { return images_; }
	images_type& images() { return images_; }
	const QLazySharedPointer<user_type>& user() const { return submitter_id; }
	void user(QLazySharedPointer<user_type> user) { submitter_id = user; }

    odbevent() {}
    odbevent(std::string event_name, QDateTime event_date):event_name(event_name),event_date(event_date){submit_date = QDateTime::currentDateTime();}
    void Accept();
    QString getName();
    QDateTime getDate();
    int getId();
    bool isAccepted();

private:
	friend class odb::access;
#pragma db id auto
	unsigned int event_id;
	std::string  event_name;
#pragma db type("DATETIME")
	QDateTime    submit_date;
	QDateTime	 event_date;
	bool		 event_accepted=0;
#pragma db value_null inverse(track_id)
	tracks_type  tracks_;
#pragma db value_null inverse(image_id)
	images_type  images_;
#pragma db not_null
	QLazySharedPointer<user_type> submitter_id;
};

#pragma db view object(odbevent) object(image) \
    query ((?) + "GROUP BY" + image::event_id)
struct image_per_event{
    #pragma db column(image::image_accepted)
    bool accepted;
    #pragma db column(image::event_id)
    unsigned int event_id;
    #pragma db column("count(" + image::event_id + ")")
    std::size_t count;
};

#ifdef ODB_COMPILER
#include "track.h"
#include "image.h"
#include "user.h"
#endif

#endif // EVENT_H
