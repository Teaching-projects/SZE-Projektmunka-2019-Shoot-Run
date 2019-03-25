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
#pragma db id auto
    unsigned int image_id;
    unsigned int event_id;
    std::string  PATH;
    unsigned int photographer_id;
    std::string  datetime;
    bool         image_accepted;
    double       image_longitude;
	double       image_latitude;
public:
    image(){}
    image(unsigned int,std::string,unsigned int, std::string,double,double);

};

#endif // IMAGE_H
