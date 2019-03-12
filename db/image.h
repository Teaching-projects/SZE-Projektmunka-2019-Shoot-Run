#ifndef IMAGE_H
#define IMAGE_H
#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <string>

class user;
class event;


#pragma db object
class image
{
private:
    friend class odb::access;
#pragma db id auto type("MEDIUMINT(8)")
    unsigned int image_id;
#pragma db type("MEDIUMINT(8)")
    unsigned int event_id;
#pragma db type("VARCHAR(100)")
    std::string  PATH;
#pragma db type("MEDIUMINT(8)")
    unsigned int photographer_id;
#pragma db type("varchar(50)")//átír addig semmi értelme
    std::string  datetime;
#pragma db type("TINYINT(1)")
    bool         image_accepted;
#pragma db type("DOUBLE")
    double       image_longitude;
#pragma db type("DOUBLE")
	double       image_latitude;
public:
    image(){}
    image(unsigned int,std::string,unsigned int, std::string,double,double);
/*#pragma db not_null
	std::tr1::shared_ptr<user> user_;
#pragma db not_null
	std::tr1::shared_ptr<event> event_;*/
};

#endif // IMAGE_H
