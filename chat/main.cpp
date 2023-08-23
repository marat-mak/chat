#include "chat.h"
#include "ClientSocket.h"
#include "CVarsSystem.h"

int main()
{
	//loadUsers();
	//loadMessages();

	CVarSystem* pVars = new CVarSystem();


	

	std::cout << "Connect to the server " << pVars->getValue("client_connect_ip") << ":" << pVars->getValue("client_connect_port") << std::endl;

	CSocket* pSocket = new CSocket(pVars);
	if (!pSocket->ConnectedSocket)
	{
		printf("\x1b[31m");
		std::cout << "failed to connect to the server\n";

		std::cout << "Press Enter to exit...";
		std::cin.get(); // ќжидание ввода Enter

		return 0;
	}

	pSocket->ConnectedHello();
	if (!pSocket->HelloServer)
	{
		printf("\x1b[31m");
		std::cout << "failed to identity client\n";

		std::cout << "Press Enter to exit...";
		std::cin.get(); // ќжидание ввода Enter

		return 0;
	}


	int choice = 0;
	while (true)
	{
		printf("\x1b[36m");
		std::cout << "Welcome to chat" << std::endl;
		std::cout << "Press [s] - sign up; [r] - registry new user; [q] - quit" << std::endl;
		choice = _getch();
		std::cout << std::endl;
		if (choice == 115)
		{
			try
			{				
				if (signUp(pSocket))
				{
					userMenu();
				}
			}
			catch (const char* ex)
			{
				std::cout << ex << std::endl;
			}		
		}
		if (choice == 114)
		{
			try { reg(pSocket); }
			catch (const char* ex)
			{
				std::cout << ex << std::endl;
			}
		}
		if (choice == 113)
		{
			break;
		}		
		std::cout << "\n============================================\n";
	}	
	return 0;
}
