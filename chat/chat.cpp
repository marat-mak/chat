#include "chat.h"
#include <fstream>
#include <filesystem>
#include "ClientSocket.h"
#include <map>
#include "MessageManager.h"
#include "Base64.h"

#include <vector>
#include <string>
#include <sstream>
#include <codecvt>


std::string currentUser;
std::vector<User> users;
std::vector<Message> mes;
 
std::string name;
std::string login;
std::string password;

std::string to;
std::string sms;

CSocket* pClientsLocal = nullptr;

void reg(CSocket* pClient)
{
    /*std::fstream user_file("users.list", std::ios::out | std::ios::app);

    auto permissions = std::filesystem::perms::group_all |
std::filesystem::perms::others_all;

    std::filesystem::permissions("users.list", permissions,
std::filesystem::perm_options::remove);*/
    name = "";
    login = "";
    password = "";


    printf("\x1b[36m");
    std::cout << "Enter username:" << std::endl;
    std::cin >> name;
    std::cout << "Enter login:" << std::endl;
    std::cin >> login;
    std::cin.ignore();
    std::cout << "Enter password (min 6 characters): " << std::endl;
    int ch = 0;
    while (true)
    {
        ch = _getch();
        if (ch == ENTER)
        {
            if (password.length() <= 5)
            {
    		printf("\x1b[31m");
                std::cout << std::endl;
                std::cout << "the password is too short" << std::endl << std::endl;
                std::cout << "please try again" << std::endl << std::endl;
                std::cout << "press ESC to cancel" << std::endl << std::endl;
                std::cout << "Enter password (min 6 characters): " << std::endl;
                password.clear();
                continue;
            }
            else
            {

                std::string message = "page=register;login=" + login + ";password=" + password + ";userName=" + name + ";";
                pClient->SMessage(message);

                std::string result = pClient->RMessage();

                std::map<std::string, std::string> read_result = MessageManager::parseKeyValueString(result);
                if (read_result["status"] != "ok")
                {
                    std::string print_message = base64_decode(read_result["message"]);
                    std::cout << print_message << std::endl;
                    reg(pClient);
                    break;
                }
                else
                {
                    std::cout << "Register Success\n";
                    break;
                }

                /*users.emplace_back(name, login, password);
                user_file << "name:" << name << "\n";
                user_file << "login:" << login << "\n";
                user_file << "pass:" << password << "\n";
		user_file.close();
	       	std::cout << "\nUser " << name << " registered" << std::endl;
                password.clear();*/

                
            }
        }

        if (ch == 8)
        {
            std::cout << (char)8 << ' ' << char(8);

            if (!password.empty())
            {
                password.erase(password.length() - 1);
            }
        }
        else
        {
            std::cout << '*';
            password += (char)ch;
        }
        if (ch == 27)
        {
            break;
        }
    }
    
}

bool signUp(CSocket* pClient)
{
    std::string name;
    std::string login;
    std::string password;

    printf("\x1b[35m");
    std::cout << "Enter login:" << std::endl;
    std::cin >> login;
    std::cin.ignore();
    std::cout << "Enter password: ";
    int ch = 0;
    std::cout << std::endl;
    while (true)
    {
        ch = _getch();
        if (ch == ENTER)
        {
            /*for (int i = 0; i < users.size(); ++i)
            {
                if (users[i].getLogin() == login && users[i].getPassword() == password)
                {
		    printf("\033c");
                    std::cout << "Login correct! Hello " << users[i].getName() << std::endl;
                    currentUser = users[i].getName();
                    return true;
                    break;
                }
            }*/

            std::string message = "page=autch;login=" + login + ";password=" + password + ";";
            pClient->SMessage(message);

            std::string rec = pClient->RMessage();
            std::map<std::string, std::string> pMessageManager = MessageManager::parseKeyValueString(rec);

            if (pMessageManager["page"] == "autch")
            {
                std::string status = pMessageManager["status"];

                if (status == "ok")
                {
                    std::string login = pMessageManager["login"];
                    std::string pass = pMessageManager["password"];
                    std::string name = pMessageManager["username"];
                    int id = atoi(pMessageManager["id"].c_str() );
                    std::cout << "Login correct! Hello " << name << std::endl;
                    pClient->login = login;
                    pClient->password = pass;
                    pClient->nickname = name;
                    pClient->id = id;


                    currentUser = login;
                    pClientsLocal = pClient;
                    return true;

                }
                else
                {

                    std::cout << std::endl;
                    throw "incorrect login or password";
                }

            }




        }

        if (ch == 8)
        {
            std::cout << (char)8 << ' ' << char(8);
            if (!password.empty())
                password.erase(password.length() - 1);
        }
        else
        {
            std::cout << '*';
            password += (char)ch;
        }

    }
}

void userMenu()
{
    printf("\x1b[33m");
    std::cout << "Press [r] - read message; [w] - write message; [s] - show users; [any] - exit to main menu" << std::endl;
    int ch = 0;
    ch = _getch();
    std::cout << std::endl;
    if (ch == 114)
    {
        readMessage();
    }
    if (ch == 119)
    {
        try { writeMessage(); }
        catch (const char* ex)
        {
            std::cout << ex << std::endl;
            userMenu();
        }
    }
    if (ch == 115)
    {
        showUsers();
    }
    else
    {
        return;
    }
}

std::string decodeUtf8(const std::string& input) {
    int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, nullptr, 0);
    if (wideStrLen == 0) {
        return "";
    }

    std::wstring wideStr(wideStrLen, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, &wideStr[0], wideStrLen);

    int requiredLen = WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (requiredLen == 0) {
        return "";
    }

    std::string result(requiredLen, '\0');
    WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, &result[0], requiredLen, nullptr, nullptr);

    return result;
}

void readMessage()
{
    std::cout << "=============================================" << std::endl;

    std::string message = "page=sendUsersMessageAll;user_id=" + std::to_string(pClientsLocal->id) + ";";
    pClientsLocal->SMessage(message);

    std::string resultBase64 = pClientsLocal->RMessage();
    std::map<std::string, std::string> result = MessageManager::parseKeyValueString(resultBase64);
    std::string results = base64_decode(result["all_message"]);

    struct ListMessage { std::string type_message;  std::string nickname; std::string message; };
    std::list<ListMessage> AllMessage;

    std::istringstream iss(results);
    std::string token;

    std::vector<std::string> elements;

    while (std::getline(iss, token, ';')) {
        if (!token.empty()) {
            elements.push_back(token);
        }
    }

    std::vector<std::vector<std::string>> vresult;
    // Разделение на массив из двух элементов по три подэлемента
    for (size_t i = 0; i < elements.size(); i += 3) {
        std::vector<std::string> sub_array;
        for (size_t j = 0; j < 3 && i + j < elements.size(); ++j) {
            sub_array.push_back(elements[i + j]);
        }
        vresult.push_back(sub_array);
    }


    // Вывод результата
    for (const auto& sub_array : vresult) {


        ListMessage message;
        message.nickname = sub_array[1];
        message.nickname.erase(std::remove(message.nickname.begin(), message.nickname.end(), ' '), message.nickname.end());;
        
        message.message = decodeUtf8(sub_array[2]);

        message.type_message = sub_array[0];
        AllMessage.push_back(message);
    }

    setlocale(LC_ALL, "Russian");

    for (const ListMessage& msg : AllMessage) {

        if (msg.nickname == pClientsLocal->nickname)
            std::cout << msg.type_message << " " << "You: -> " << msg.message << std::endl;
        else
            std::cout << msg.type_message << " " << msg.nickname << ": " << msg.message << std::endl;
    }

    std::cout << "=============================================" << std::endl;
    userMenu();
}

void writeMessage()
{
    /*std::fstream mes_file("messages.list", std::ios::out | std::ios::app);
    
    auto permissions = std::filesystem::perms::group_all |
std::filesystem::perms::others_all;
    
    std::filesystem::permissions("messages.list", permissions,
std::filesystem::perm_options::remove);
    
   bool test = false;
    printf("\x1b[37m");
    std::cout << "to whom(write 'all' for all): ";
    std::cin >> to;
    std::cin.ignore();
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getName() == to || to == "all")
        {
            test = true;
            continue;
        }
    }
    if (test == false) throw "no user in base";
    std::cout << "enter message: ";
    getline(std::cin, sms);
    mes.emplace_back(currentUser, to, sms);
    mes_file << "from:" << currentUser << "\n";
    mes_file << "to:" << to << "\n";
    mes_file << "sms:" << sms << "\n";
    mes_file.close();
    userMenu();*/

    std::string to_message;
    std::string message;

    printf("\x1b[37m");
    std::cout << "to whom(write 'all' for all): ";
    std::cin >> to_message;
    std::cin.ignore();

    if (to_message == "all")
    {
        std::cout << "Send to All Users\n";
        std::cout << "enter message: ";
        getline(std::cin, message);
    }
    else
    {
        std::cout << "Send to " << to_message << std::endl;
        std::cout << "enter message: ";
        getline(std::cin, message);


    }


    std::cout << "Send " << to_message << " Message: " << message << std::endl;
    std::string Message = "page=readUserMessage;to_message=" + to_message + ";message=" + message + ";";
    pClientsLocal->SMessage(Message);

    std::string result = pClientsLocal->RMessage();

    if (MessageManager::parseKeyValueString(result)["status"] == "ok")
    {
        std::cout << "Message Sending\n";
    }
    else
    {
        std::string message = decodeUtf8(base64_decode(MessageManager::parseKeyValueString(result)["message"]));
        std::cout << message << std::endl;
        

    }

    userMenu();

}

void showUsers()
{
    printf("\x1b[36m");
    std::cout << "=============================================" << std::endl;


    std::string message = "page=usersAll;";
    pClientsLocal->SMessage(message);

    std::string result = pClientsLocal->RMessage();

    std::string userBase64 = MessageManager::parseKeyValueString(result)["result"];
    std::string users = base64_decode(userBase64);

    // Удаление последнего символа ';'
    if (!users.empty() && users.back() == ';') {
        users.pop_back();
    }

    std::vector<std::string> tokens;
    std::istringstream tokenStream(users);
    std::string token;

    while (std::getline(tokenStream, token, ';')) {
        tokens.push_back(token);
    }

    int count = 1;

    for (const std::string& token : tokens) {
        std::cout << count << ". " << token << std::endl;
        count++;
    }


    std::cout << "=============================================" << std::endl;
    userMenu();
}

void loadUsers() {
    std::fstream user_file("users.list", std::ios::in);
    if (user_file.is_open()) {
        const std::string delimiter = ":"; 
        std::string line;
        std::string type;
        std::string value;

        while (std::getline(user_file, line)) {
            size_t delimiterPosition = line.find(delimiter);
            if (delimiterPosition > 0) {
                type = line.substr(0, delimiterPosition);
                value = line.substr(delimiterPosition + 1);

                if (type == "name") {
                    name = value;
                }
                else if (type == "login") {
                    login = value;
                }
		else if (type == "pass") {
                    password = value;
                    users.emplace_back(name, login, password);
                    password.clear();

                }
            }
        }
    }
    user_file.close();
}

void loadMessages() {
    std::fstream mes_file("messages.list", std::ios::in);
    if (mes_file.is_open()) {
        const std::string delimiter = ":"; 
        std::string line;
        std::string type;
        std::string value;

        while (std::getline(mes_file, line)) {
            size_t delimiterPosition = line.find(delimiter);
            if (delimiterPosition > 0) {
                type = line.substr(0, delimiterPosition);
                value = line.substr(delimiterPosition + 1);

                if (type == "from") {
                    currentUser = value;
                }
                else if (type == "to") {
                    to = value;
                }
		else if (type == "sms") {
                    sms = value;
                    mes.emplace_back(currentUser, to, sms);
                }
            }
        }
    }
    mes_file.close();
}
