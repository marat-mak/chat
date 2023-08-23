// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "CoreServer.h"
#include <filesystem>

#pragma comment(lib, "mariadbcpp.lib")

int main(int argc, char* argv[])
{
    std::locale::global(std::locale("en_US.utf8"));

    std::cout << "Server Start\n";
    new CoreServer();


}