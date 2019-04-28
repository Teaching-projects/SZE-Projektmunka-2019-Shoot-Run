#include "user.h"

user::user(std::string user_name, std::string password,std::string first_name,
    std::string last_name,std::string email, QDateTime registration_date):
    user_name(user_name),password(password),first_name(first_name),
	last_name(last_name),email(email), registration_date(registration_date){}

QDateTime user::getRegistretionDate(){
    return registration_date;
}

bool user::isadmin(){
    if(type_ == 0)
        return true;
    return false;
}

int user::getID(){
    return user_id;
}

