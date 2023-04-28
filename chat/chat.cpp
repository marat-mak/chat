#include "chat.h"
#include "mygetch.h"
#include <fstream>
#include <filesystem>

std::string currentUser;
std::vector<User> users;
std::vector<Message> mes;
 
std::string name;
std::string login;
std::string password;

std::string to;
std::string sms;
 
void reg()
{
    std::fstream user_file("users.list", std::ios::out | std::ios::app);

    auto permissions = std::filesystem::perms::group_all |
std::filesystem::perms::others_all;

    std::filesystem::permissions("users.list", permissions,
std::filesystem::perm_options::remove);
  
       
    printf("\x1b[36m");
    std::cout << "Enter username:" << std::endl;
    std::cin >> name;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getName() == name) throw "name is busy";
    }
    std::cout << "Enter login:" << std::endl;
    std::cin >> login;
    std::cin.ignore();
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getLogin() == login) throw "login is busy";
    }
    std::cout << "Enter password (min 6 characters): " << std::endl;
    int ch = 0;
    while (true)
    {
        ch = mygetch();
        if (ch == 10)
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
                users.emplace_back(name, login, password);
                user_file << "name:" << name << "\n";
                user_file << "login:" << login << "\n";
                user_file << "pass:" << password << "\n";
		user_file.close();
	       	std::cout << "\nUser " << name << " registered" << std::endl;
                password.clear();
                break;
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

bool signUp()
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
        ch = mygetch();
        if (ch == 10)
        {
            for (int i = 0; i < users.size(); ++i)
            {
                if (users[i].getLogin() == login && users[i].getPassword() == password)
                {
		    printf("\033c");
                    std::cout << "Login correct! Hello " << users[i].getName() << std::endl;
                    currentUser = users[i].getName();
                    return true;
                    break;
                }
            }
            std::cout << std::endl;
            throw "incorrect login or password";

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
    ch = mygetch();
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

void readMessage()
{
    std::cout << "=============================================" << std::endl;
    for (int i = 0; i < mes.size(); i++)
    {
        if (mes[i].getTo() == currentUser || mes[i].getTo() == "all" || mes[i].getFrom() == currentUser)
        {
            if (mes[i].getFrom() == currentUser)  std::cout << "You: -> " << mes[i].getMessage() << std::endl;

            else std::cout << mes[i].getFrom() << ": " << mes[i].getMessage() << std::endl;
        }
    }
    std::cout << "=============================================" << std::endl;
    userMenu();
}

void writeMessage()
{
    std::fstream mes_file("messages.list", std::ios::out | std::ios::app);
    
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
    userMenu();
}

void showUsers()
{
    printf("\x1b[36m");
    std::cout << "=============================================" << std::endl;
    for (int i = 0; i < users.size(); i++)
    {
        std::cout << i + 1 << ". " << users[i].getName() << "\n";
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
