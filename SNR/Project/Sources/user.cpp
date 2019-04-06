#include "user.h"

user::user(std::string user_name, std::string password,std::string first_name, std::string last_name,
	std::string email, QDateTime registration_date)
	:user_name(user_name),password(password),
      first_name(first_name),last_name(last_name),
      email(email), registration_date(registration_date){}

QDateTime		 user::getRegistretionDate(){return registration_date;}


user user::guest_init()
{
	user guest_user;
	guest_user.user_name = guest;
	guest_user.type_ = guest;
	return guest_user;
}
