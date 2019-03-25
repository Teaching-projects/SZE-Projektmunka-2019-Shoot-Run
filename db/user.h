#ifndef USER_H
#define USER_H
#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <odb/tr1/lazy-ptr.hxx>
#include <string>
#include <vector>

class image;class track;
typedef std::vector<odb::tr1::lazy_weak_ptr<image> > images;
typedef ::images images_type;
typedef std::vector<odb::tr1::lazy_weak_ptr<track> > tracks;
typedef ::tracks tracks_type;

#pragma db object
class user
{
public:
	//images
	const images_type& images() const { return images_; }
	images_type& images() { return images_; }	
	//tracks
	const tracks_type& tracks() const { return tracks_; }
	tracks_type& tracks() { return tracks_; }

	user() {}
	user(std::string, std::string, std::string, std::string, std::string);
private:
    friend class odb::access;
#pragma db id auto
    unsigned int user_id;
	std::string  user_name, password, first_name, last_name, email;
#pragma db value_not_null inverse(user_image_) //image
	images_type images_;
#pragma db value_not_null inverse(user_track_) //track
	tracks_type tracks_;
};
#ifdef ODB_COMPILER
#include "track.h"
#include "image.h"
#endif

#endif // USER_H
