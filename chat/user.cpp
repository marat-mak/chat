#include "user.h"


User::User(std::string name, std::string login, std::string password) : _name(name), _login(login), _password(password)
{
}
void User::show()                                              
{
    std::cout << _name << " " << _login << " " << _password << std::endl;
}
std::string User::getName()
{
    return _name;
}
std::string User::getLogin()
{
    return _login;
}
std::string User::getPassword()
{
    return _password;
}
std::ostream& operator<<(std::ostream& output, const User& u)
{
    output << u._name << " " << u._login << " " << u._password;
    return output;
}

