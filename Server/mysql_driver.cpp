#include "mysql_driver.h"

#include <iostream>
#include <chrono>
#include <ctime>


mysql_driver::mysql_driver()
{
	std::cout << "[Mysql] System start init\n";
	this->Init();
}

mysql_driver::~mysql_driver()
{
}

void mysql_driver::Init()
{
	std::cout << "[Mysql] init\n";
	this->con = nullptr;
	this->driver = nullptr;




}

bool mysql_driver::IsRun()
{
	return statusConnectDB;
}

void mysql_driver::ConnectDB(const char* ip, const char* user, const char* pass, const char* dbName)
{
}

bool mysql_driver::SetDBName(const char* dbName)
{
	return false;
}

void mysql_driver::Disconnect()
{
}

#include <Windows.h>
void mysql_driver::ConnectDB(MySQL_user& MysqlContext)
{


    driver = sql::mariadb::get_driver_instance();
    std::string connecting_Str = "tcp://" + MysqlContext.ip + ":3306/" + MysqlContext.dbName;
    con = driver->connect(connecting_Str.c_str(), MysqlContext.user.c_str(), MysqlContext.pass.c_str());

    statusConnectDB = true;

    std::cout << "[Mysql] Connected to DB\n";




}

int mysql_driver::getCountUsers()
{
    int count = 0;

    try {
        std::shared_ptr<sql::Statement> stmt(con->createStatement());
        std::shared_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT COUNT(*) AS count FROM users"));

        if (res->next()) {
            count = res->getInt("count");
        }

        // Освобождение ресурсов
        res.reset();
        stmt.reset();
    }
    catch (sql::SQLException& e) {
        std::cout << "SQLException: " << e.what() << std::endl;
    }

    return count;
}

bool mysql_driver::AutchUser(std::string login, std::string pass, std::string& result)
{
    bool fresult = false;

    std::shared_ptr<sql::PreparedStatement> selectStatement(
        con->prepareStatement("SELECT * FROM users WHERE login = ? AND password = ? ;")
    );

    // Установка параметров
    selectStatement->setString(1, login.c_str());
    selectStatement->setString(2, pass.c_str());


    sql::ResultSet* resultSet = selectStatement->executeQuery();

    if (resultSet->next()) {
        std::string id = resultSet->getString("id").c_str();
        std::string username = resultSet->getString("username").c_str();
        std::string login = resultSet->getString("login").c_str();
        std::string password = resultSet->getString("password").c_str();
        
        result = "id=" + id + ";username=" + username + ";login=" + login + ";password=" + password + ";";
        fresult = true;
    }

    delete resultSet;

    return fresult;
}

int mysql_driver::RegisterUser(std::string login, std::string username, std::string pass)
{
    std::shared_ptr<sql::PreparedStatement> selectStatement(
        con->prepareStatement("INSERT INTO `users`(`username`, `login`, `password`) VALUES (? , ? , ?);")
    );

    selectStatement->setString(1, username.c_str());
    selectStatement->setString(2, login.c_str());
    selectStatement->setString(3, pass.c_str());
    selectStatement->executeUpdate(); // Выполняем вставку

    return 0;

}

int mysql_driver::UserList(std::string &result)
{

    int count = 0;
    std::shared_ptr<sql::PreparedStatement> selectStatement(
        con->prepareStatement("SELECT username FROM `users` WHERE 1;")
    );

    sql::ResultSet* resultSet = selectStatement->executeQuery();
    while (resultSet->next()) {
        std::string username = resultSet->getString("username").c_str();
        result += username + ";";

        count++;
    }

    return count;
}

std::string  mysql_driver::ReadMessageALL(int id)
{
    std::string result;

    std::shared_ptr<sql::PreparedStatement> selectStatement(
        con->prepareStatement("SELECT * FROM `chat` WHERE client_to = 0 OR client_to = ? ORDER BY time ASC;")
    );
    selectStatement->setInt(1, id);


    sql::ResultSet* resultSet = selectStatement->executeQuery();

    while (resultSet->next()) {
        resultSet->getString("nickname_from").c_str();
        int id_to = atoi(resultSet->getString("client_to").c_str());
        std::string client_from = resultSet->getString("nickname_from").c_str();
        std::string message = resultSet->getString("message").c_str();

        std::cout << client_from + " = " + message + ";";


        if(id_to == 0)
            result += "[AllMessage];" + client_from + ";" + message + ";";
        else
            result += "[PrivateMessage];" + client_from + "; " + message + ";";
    }

    return result;
}

bool mysql_driver::CheckUserName(std::string username)
{
    bool result = false;


    std::shared_ptr<sql::PreparedStatement> selectStatement(
        con->prepareStatement("SELECT * FROM `users` WHERE `username` = ? LIMIT 1;")
    );
    selectStatement->setString(1, username.c_str());
    sql::ResultSet* resultSet = selectStatement->executeQuery();
    if (resultSet->next()) {
        result = true;
    }


    return result;
}

bool mysql_driver::CheckLogin(std::string login)
{
    int id = 0;

    std::shared_ptr<sql::PreparedStatement> selectStatement(
        con->prepareStatement("SELECT * FROM `users` WHERE `login` = ? LIMIT 1;")
    );

    selectStatement->setString(1, login.c_str());

    sql::ResultSet* resultSet = selectStatement->executeQuery();
    if (resultSet->next()) {
        id = atoi(resultSet->getString("id").c_str());
    }

    return id;
}

int mysql_driver::GetUserID(std::string username)
{
    int id = 0;

    std::shared_ptr<sql::PreparedStatement> selectStatement(
        con->prepareStatement("SELECT * FROM `users` WHERE `username` = ? LIMIT 1;")
    );

    selectStatement->setString(1, username.c_str());

    sql::ResultSet* resultSet = selectStatement->executeQuery();
    if (resultSet->next()) {
        id = atoi(resultSet->getString("id").c_str());
    }

    return id;
}

bool mysql_driver::WriteMessage(std::string client_from, std::string nickname_from,
    std::string client_to, std::string nickname_to, std::string message)
{
    std::shared_ptr<sql::PreparedStatement> insertStatement(
        con->prepareStatement("INSERT INTO `chat`(`client_from`, `nickname_from`, `client_to`, `nickname_to`, `message`, `time`) VALUES (?,?,?,?,?,?)")
    );

    insertStatement->setString(1, client_from.c_str() );
    insertStatement->setString(2, nickname_from.c_str());
    insertStatement->setString(3, client_to.c_str());
    insertStatement->setString(4, nickname_to.c_str());
    insertStatement->setString(5, message.c_str());

    // Get the current time and date
    auto now = std::chrono::system_clock::now();
    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);

    // Convert the timestamp to a string in the format "YYYY-MM-DD HH:MM:SS"
    char timeBuffer[20];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&timestamp));
    std::string currentTime(timeBuffer);

    insertStatement->setString(6, currentTime.c_str() );

    try {
        insertStatement->executeUpdate();
    }
    catch (const sql::SQLException& e) {
        std::cerr << "Error executing INSERT query: " << e.what() << std::endl;
        return false;
    }

    if (insertStatement->getUpdateCount() > 0) {
        return true;
    }
    else {
        return false;
    }
}
