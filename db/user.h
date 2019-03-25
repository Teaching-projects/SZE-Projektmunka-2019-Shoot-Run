#ifndef USER_H
#define USER_H
#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <odb/tr1/lazy-ptr.hxx>
#include <string>
#include <vector>

class event;class image;class track;class tardis;
typedef std::vector<odb::tr1::lazy_weak_ptr<track> > tracks;

#pragma db object
class user
{
public:
	typedef ::tracks tracks_type;
	const tracks_type& tracks() const { return tracks_; }
	tracks_type& tardiss() { return tracks_; }
	user() {}
	user(std::string, std::string, std::string, std::string, std::string);

private:
    friend class odb::access;
#pragma db id auto
    unsigned int user_id;
    std::string  user_name;
    std::string  password;
    std::string  first_name;
    std::string  last_name;
    std::string  email;
#pragma db value_not_null inverse(user_track_)
	tracks_type tracks_;

};
#ifdef ODB_COMPILER
#include "track.h"
#include "image.h"
#endif

#endif // USER_H
