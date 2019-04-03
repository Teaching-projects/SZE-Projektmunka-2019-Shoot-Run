#include "user.h"

user::user(std::string user_name, std::string password,
           std::string first_name, std::string last_name,
           std::string email,std::string registration_date)
    :user_name(user_name),password(password),
      first_name(first_name),last_name(last_name),
      email(email), registration_date(registration_date){}

std::string user::getRegistretionDate()
{
	return registration_date;
}
