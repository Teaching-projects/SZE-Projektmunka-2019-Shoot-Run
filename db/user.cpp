#include "user.h"

user::user(std::string user_name, std::string password,
           std::string first_name, std::string last_name,
           std::string email)
    :user_name(user_name),password(password),
      first_name(first_name),last_name(last_name),
      email(email){}
