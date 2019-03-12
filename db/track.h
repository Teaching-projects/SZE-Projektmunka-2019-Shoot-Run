#ifndef TRACK_H
#define TRACK_H
#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <vector>
class event;
class user;
class tardis;


#pragma db object
class track
{
private:
    friend class odb::access;
#pragma db id auto type("MEDIUMINT(8)")
    unsigned int track_id;
#pragma db type("MEDIUMINT(8)")
    unsigned int event_id;
#pragma db type("MEDIUMINT(8)")
    unsigned int user_id;
public:
    track(){}
    track(unsigned int, unsigned int);
/*#pragma db not_null
	std::tr1::shared_ptr<event> event_;
#pragma db not_null
	std::tr1::shared_ptr<user> user_;
#pragma db value_not_null unordered
	std::vector<std::tr1::shared_ptr<tardis>> tardiss_;*/
};

#endif // TRACK_H
