#pragma once
#include <string>
#include <list>

struct Message;

class Client
{
public:
	Client(std::string &autchData);
	~Client();



public:
	std::string login;
	std::string username;
	std::string password;
	int id = 0;

	std::list<Message> *ListMessage;



};

