#include "Client.h"
#include <iostream>
#include "MessageManager.h"
#include <map>

Client::Client(std::string &autchdata)
{
	std::cout << "[Client] Start Initialization\n";
	std::map<std::string, std::string> str = MessageManager::parseKeyValueString(autchdata);

	this->login = str["login"];
	this->password = str["password"];
	this->username = str["username"];

	std::cout << "Client auth username " << this->username << std::endl;

}

Client::~Client()
{
}
