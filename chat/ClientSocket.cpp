#include "ClientSocket.h"
#include <iostream>
#include "CVarsSystem.h"

#pragma comment(lib, "ws2_32.lib")
#include "MessageManager.h"

CSocket::CSocket(CVarSystem* pVars)
{

    // Инициализация WinSock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize WinSock." << std::endl;
        return;
    }

    // Создание сокета
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return;
    }

    // Установка параметров сервера
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(atoi(pVars->getValue("client_connect_port").c_str()));  // Порт сервера
    serverAddress.sin_addr.s_addr = inet_addr(pVars->getValue("client_connect_ip").c_str());  // IP-адрес сервера

    // Подключение к серверу
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to the server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    ConnectedSocket = true;




}

CSocket::~CSocket()
{
    // Закрытие сокета и выход
    closesocket(clientSocket);
    WSACleanup();
}

void CSocket::SMessage(std::string& message)
{

    if (send(clientSocket, message.c_str(), strlen(message.c_str()), 0) == SOCKET_ERROR) {
        std::cerr << "Failed to send data." << std::endl;
    }
}

std::string CSocket::RMessage()
{
    int bytesReceived = 0;
    char buffer[1024];


    bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

    std::string receivedData(buffer, bytesReceived);  // Создаем std::string из буфера

    //std::cout << "[Client] ReadMessage: " << receivedData << std::endl;


    return receivedData;
    
}

void CSocket::ConnectedHello()
{
    char computerName[256];
    DWORD computerNameSize = sizeof(computerName);
    if (GetComputerNameA(computerName, &computerNameSize)) {
        std::cout << "Computer Name: " << computerName << std::endl;
    }
    else {
        std::cerr << "Failed to get computer name." << std::endl;
    }


    std::string message = "page=Hello;name_user=" + std::string(computerName) + ";";
    this->SMessage(message);

    std::string rec = this->RMessage();

    std::map<std::string, std::string> pMessageManager = MessageManager::parseKeyValueString(rec);
    std::string page = pMessageManager["page"];

    if (page == "connected")
    {
        if (pMessageManager["status"] == "ok")
        {
            HelloServer = true;
            return;
        }
    }
    else
        std::cout << "Server is not versionError\n";

}
