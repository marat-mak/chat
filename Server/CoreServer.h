#pragma once

#include <iostream>
#include "I_SQL_Driver.h"
#include "CVarSystem.h"
#include "Client.h"
#include <vector>

#define ERROR_SYSTEM(_MESSAGE) \
        std::cerr << "\n\n\n[Error] " << _MESSAGE << std::endl; \
		exit(EXIT_FAILURE);


class CoreServer
{
public:
	CoreServer();
	~CoreServer();



	int getCountUserDB();

public:
	void Init();
	CVarSystem *pCVar;
	Isql_Core* pSqlSystem;
	std::vector<Client*> pClientOnline;


};

