#ifndef TARDIS_H
#define TARDIS_H
#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <string>
#include<iostream>//torold
using std::tr1::shared_ptr;

#pragma db object
class tardis
{
private:
    friend class odb::access;
#pragma db id auto type("MEDIUMINT(8)")
    unsigned int tardis_id;
#pragma db type("MEDIUMINT(8)")
    unsigned int track_id;
#pragma db type("DOUBLE")
	double       tardis_longitude;
#pragma db type("DOUBLE")
	double       tardis_latitude;
#pragma db type("varchar(50)")//átír addig semmi értelme
    std::string time;
public:
    tardis(){}
    tardis(unsigned int,double,double,std::string);
	void ki() { std::cout << track_id; }//torols
};

#endif // TARDIS_H
