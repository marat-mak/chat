#pragma once
#include <string>
#include <iostream>

class User
{
private:
	std::string _name;
	std::string _login;
	std::string _password;
public:
	User() = default;
	User(std::string name, std::string login, std::string password);
	~User() = default;
	void show();
	std::string getName();
	std::string getLogin();
	std::string getPassword();
	friend std::ostream& operator<<(std::ostream& output, const User& u);
};

