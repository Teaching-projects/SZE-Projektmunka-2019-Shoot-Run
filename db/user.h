#ifndef USER_H
#define USER_H
#include <odb/core.hxx>
#include <odb/tr1/memory.hxx>
#include <string>
#include <vector>

class event;
class image;
class track;

#pragma db object
class user
{
private:
    friend class odb::access;
#pragma db id auto type("MEDIUMINT(8)")
    unsigned int user_id;
#pragma db type("VARCHAR(20)")
    std::string  user_name;
#pragma db type("VARCHAR(30)")
    std::string  password;
#pragma db type("VARCHAR(50)")
    std::string  first_name;
#pragma db type("VARCHAR(50)")
    std::string  last_name;
#pragma db type("VARCHAR(100)")
    std::string  email;
public:
    user(){}
    user(std::string,std::string,std::string,std::string,std::string);
/*#pragma db value_not_null unordered
	std::vector<std::tr1::shared_ptr<image>> images_;
#pragma db value_not_null unordered
	std::vector<std::tr1::shared_ptr<track>> tracks_;
#pragma db value_not_null unordered
	std::vector<std::tr1::shared_ptr<event>> events_;*/
};

#endif // USER_H
