#ifndef TARDIS_H
#define TARDIS_H
#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <odb/tr1/lazy-ptr.hxx>
#include <string>
#include<iostream>
class track;
typedef ::track track_type;

#pragma db object
class tardis
{
private:
 friend class odb::access;
#pragma db id auto
    unsigned int tardis_id;
#pragma db not_null
	odb::tr1::lazy_shared_ptr<track_type> track_tardis_;
	double       tardis_longitude;
	double       tardis_latitude;
    std::string time;
public:
const odb::tr1::lazy_shared_ptr<track_type>& track() const { return track_tardis_; }
void track(odb::tr1::lazy_shared_ptr<track_type> track) { track_tardis_ = track; }

    tardis(){}
    tardis(odb::tr1::lazy_shared_ptr<track_type>,double,double,std::string);

};

#ifdef ODB_COMPILER
#include "track.h"
#endif

#endif // TARDIS_H
