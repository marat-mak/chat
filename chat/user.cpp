#include "user.h"


User::User(string name, string login, string password) : _name(name), _login(login), _password(password)
{
}
void User::show()
{
    cout << _login << " " << _password << endl;
}
string User::getName()
{
    return _name;
}
string User::getLogin()
{
    return _login;
}
string User::getPassword()
{
    return _password;
}
ostream& operator<<(ostream& output, const User& u)
{
    output << u._login << " " << u._password;
    return output;
}