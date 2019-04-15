#ifndef USER_H
#define USER_H

#include <iostream>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>
#include <string>
#include <vector>
#include <QtCore/QDateTime>

class image;class track;
typedef std::vector<QLazyWeakPointer<image> > images;
typedef images images_type;
typedef std::vector<QLazyWeakPointer<track> > tracks;
typedef tracks tracks_type;
enum type { admin, simple_user, guest};

#pragma db object
class user
{
public:
	const images_type& images() const { return images_; }
	images_type& images() { return images_; }
	const tracks_type& tracks() const { return tracks_; }
	tracks_type& tracks() { return tracks_; }

	user() {}
	user(std::string, std::string, std::string, std::string, std::string, QDateTime);
	QDateTime getRegistretionDate();
	user guest_init();
private:
    friend class odb::access;
#pragma db id auto
    unsigned int user_id;
	std::string  user_name, password, first_name, last_name, email;
	type type_= simple_user;
#pragma db type("DATETIME")
	QDateTime	registration_date;
#pragma db value_not_null inverse(image_id)
	images_type images_;
#pragma db value_not_null inverse(user_id)
	tracks_type tracks_;
};
#ifdef ODB_COMPILER
#include "track.h"
#include "image.h"
#endif

#endif // USER_H
