#include "CServer.h"

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include "Client.h"
#include <map>
#include "MessageManager.h"
#include "CoreServer.h"
#include "Base64.h"

#pragma comment(lib, "ws2_32.lib")

CoreServer* pCoreLocal = nullptr;

void SMessage(SOCKET ClientSocket, std::string message)
{
    if (send(ClientSocket, message.c_str(), message.size(), 0) == SOCKET_ERROR) {
        std::cerr << "Failed to send message." << std::endl;
    }
    else {
        std::cout << "Message sent: " << message << std::endl;
    }
}

void HandleClient(SOCKET clientSocket) {
    // Здесь вы можете обрабатывать запросы от клиента
    // Пример чтения данных от клиента и отправки ответа:

    char buffer[1024];
    int bytesReceived;

    Client* pClient = nullptr;

    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {

        std::string message(buffer, bytesReceived);

        std::cout << "[Client] ReadMessage " << message << std::endl;

        std::map<std::string, std::string> Message = MessageManager::parseKeyValueString(buffer);
        std::string page = Message["page"];

        if (page.empty())
            continue;

        if (page == "Hello")
        {

            std::string username = Message["name_user"];
            std::cout << "new Client is connected;user name = " << username << "\n";
            std::string message = "page=connected;status=ok";
            SMessage(clientSocket, message);

        }

        if (page == "autch")
        {
            //page=autch;login=Kasper;password=Las[ersds;

            std::string login = Message["login"];
            std::string password = Message["password"];

            std::string resultSQL;
            if (!pCoreLocal->pSqlSystem->AutchUser(login, password, resultSQL))
            {
                std::string message = "page=autch;status=failed;";
                SMessage(clientSocket, message);
            }
            else
            {
                pClient = new Client(resultSQL);
                pCoreLocal->pClientOnline.push_back(pClient);
                std::string message = "page=autch;status=ok;" + resultSQL;
                SMessage(clientSocket, message);

                
                pClient->id = atoi(MessageManager::parseKeyValueString(message)["id"].c_str());
                pClient->username = MessageManager::parseKeyValueString(message)["username"];
                pClient->login = MessageManager::parseKeyValueString(message)["login"];


            }
        }


        if (page == "usersAll")
        {
            std::string result;
            pCoreLocal->pSqlSystem->UserList(result);

            std::string base64result = base64_encode(result.c_str());

            std::string message = "result=" + base64result + ";";
            SMessage(clientSocket, message);

        }

        if (page == "register")
        {
            std::string login = Message["login"];
            std::string password = Message["password"];
            std::string username = Message["userName"];

            if (pCoreLocal->pSqlSystem->CheckLogin(login))
            {
                std::string base64_message = base64_encode("There is already a user with this login!");
                std::string message = "status=fail;message=" + base64_message + ";";
                SMessage(clientSocket, message);
                continue;
            }

            if (pCoreLocal->pSqlSystem->CheckUserName(username))
            {
                std::string base64_message = base64_encode("There is already a user with this username!");
                std::string message = "status=fail;message=" + base64_message + ";";
                SMessage(clientSocket, message);
                continue;
            }

            pCoreLocal->pSqlSystem->RegisterUser(login, username, password);
            std::string base64_message = base64_encode("Register Success!");
            std::string message = "status=ok;message=" + base64_message + ";";
            SMessage(clientSocket, message);
            continue;
        }


        if (page == "sendUserMessage")
        {

        }

        if (page == "readUserMessage")
        {
            std::string to_message = Message["to_message"];
            std::string message = Message["message"];

            if (to_message == "all")
            {
                if (!pCoreLocal->pSqlSystem->WriteMessage(std::to_string(pClient->id), pClient->username, "0", "", message))
                {
                    std::string messageBase64 = base64_encode("Failed to send a message!");

                    std::string Message = "page=readUserMessage;status=fail;message=" + messageBase64 + ";";
                    SMessage(clientSocket, Message);
                }
                else
                {
                    std::string Message = "page=readUserMessage;status=ok;";
                    SMessage(clientSocket, Message);
                }

            }
            else
            {
                int client_to = pCoreLocal->pSqlSystem->GetUserID(to_message);

                if (client_to == 0)
                {

                    std::string messageBase64 = base64_encode("user not found!");

                    std::string Message = "page=readUserMessage;status=fail;message=" + messageBase64 + ";";
                    SMessage(clientSocket, Message);

                    continue;
                }

                if (!pCoreLocal->pSqlSystem->WriteMessage(std::to_string(pClient->id), pClient->username, std::to_string(client_to), to_message, message))
                {
                    std::string messageBase64 = base64_encode("Failed to send a message!");
                    std::string Message = "page=readUserMessage;status=fail;message=" + messageBase64 + ";";
                    SMessage(clientSocket, Message);
                }
                else
                {
                    std::string Message = "page=readUserMessage;status=ok;";
                    SMessage(clientSocket, Message);
                }
            }










        }

        if (page == "sendUsersMessageAll")
        {

            std::string message = pCoreLocal->pSqlSystem->ReadMessageALL(atoi(Message["user_id"].c_str()));
            std::string base64result = base64_encode(message);

            std::string send = "all_message=" + base64result + ";";
            SMessage(clientSocket, send);


        }

        if (page == "readUsersAll")
        {

        }




        //send(clientSocket, buffer, bytesReceived, 0);
    }

    closesocket(clientSocket);
}

void CServer::StartListing(int port, CoreServer* pCore)
{
    pCoreLocal = pCore;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port); // Порт сервера

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Binding failed." << std::endl;
        closesocket(serverSocket);
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listening failed." << std::endl;
        closesocket(serverSocket);
    }

    std::cout << "Server listening on port " << port << " ... " << std::endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Client connection failed." << std::endl;
            continue;
        }

        // Создаем отдельный поток для обработки клиента
        std::thread(HandleClient, clientSocket).detach();
    }

    closesocket(serverSocket);
    WSACleanup();

}
