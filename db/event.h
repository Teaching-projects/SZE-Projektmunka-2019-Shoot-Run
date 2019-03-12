#ifndef EVENT_H
#define EVENT_H

#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <memory>
#include <string>
#include <vector>

class image;
class track;
class user;

#pragma db object
class event
{
private:
    friend class odb::access;
#pragma db id auto type("MEDIUMINT(8)")
    unsigned int event_id;
#pragma db type("VARCHAR(100)")
    std::string  event_name;
#pragma db type("varchar(50)")//átír addig semmi értelme
    std::string  submit_date;
#pragma db type("MEDIUMINT(8)")
    unsigned int submitter_id;
#pragma db type("TINYINT(1)")
    bool         event_accepted;

public:
    event(){}
    event(std::string,unsigned int);
/*#pragma db value_not_null unordered
	std::vector<std::tr1::shared_ptr<image>> images_;
#pragma db value_not_null unordered
	std::vector<std::tr1::shared_ptr<track>> tracks_;
#pragma db not_null
	std::tr1::shared_ptr<user> user_;*/
};

#endif // EVENT_H
