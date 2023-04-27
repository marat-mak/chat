#include "chat.h"
#include "mygetch.h"

int main()
{
	loadUsers();
	loadMessages();
	int choice = 0;
	while (true)
	{
		printf("\x1b[36m");
		std::cout << "Welcome to chat" << std::endl;
		std::cout << "Press [s] - sign up; [r] - registry new user; [q] - quit" << std::endl;
		choice = mygetch();
		std::cout << std::endl;
		if (choice == 115)
		{
			try
			{				
				if (signUp())
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
			try { reg(); }
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
