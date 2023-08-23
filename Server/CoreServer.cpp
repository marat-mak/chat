#include "CoreServer.h"
#include "mysql_driver.h"
#include "CServer.h"


CoreServer::CoreServer()
{
	std::cout << "[CoreServer] Start Init\n";

	this->pCVar = nullptr;
	try {
		this->Init();

	}
	catch (const std::exception& e) {
		std::cerr << "[Program] Error: " << e.what() << std::endl;
		exit(EXIT_FAILURE); // «авершение программы с кодом ошибки
	}
}

CoreServer::~CoreServer()
{
}

//получает сколько пользователей всего зарегестрированно на сервере
int CoreServer::getCountUserDB()
{
	return 0;
}

void CoreServer::Init()
{
	std::cout << "Start CVarSystem Init\n";
	this->pCVar = new CVarSystem();

	std::string test = pCVar->getValue("sql_connect");

	std::cout << "[Mysql] Initialization system sql\n";

	//MYSQL Connection session
	{
		pSqlSystem = (Isql_Core*)new mysql_driver();

		MySQL_user userDb;
		userDb.dbName = pCVar->getValue("sql_dbname");
		userDb.user = pCVar->getValue("sql_user");
		userDb.pass = pCVar->getValue("sql_password");
		userDb.ip = pCVar->getValue("sql_connect");
		std::cout << "Start connect to db: " << userDb.ip << std::endl;
		pSqlSystem->ConnectDB(userDb);
	}
	std::cout << "\n\n\n[Avrora] Registered in the system: " << pSqlSystem->getCountUsers() << std::endl;
	std::cout << "[Avrora] Start Listening system port: " << std::endl;

	int port = atoi(pCVar->getValue("listing_port").c_str());
	CServer::StartListing(port, this);


}
