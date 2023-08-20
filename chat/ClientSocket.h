#pragma once

#include <string>
#include <winsock2.h>
#include "CVarsSystem.h"

class CSocket
{
public:
	CSocket(CVarSystem* pVars);
	~CSocket();


public:
	void SMessage(std::string& message);
	std::string RMessage();

	void ConnectedHello();

public:
	WSADATA wsaData;
	SOCKET clientSocket;


	bool ConnectedSocket = false;
	bool HelloServer = false;

	int id = 0;
	std::string nickname;
	std::string login;
	std::string password;
};