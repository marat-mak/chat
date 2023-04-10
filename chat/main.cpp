#include "chatEngine.h"
//using namespace std;


int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int choice = 0;
	while (true)
	{
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << "Welcome to chat" << std::endl;
		std::cout << "Press [s] - sign up; [r] - registry new user; [q] - quit" << std::endl;
		choice = _getche();
		std::cout << std::endl;
		if (choice == 115)
		{
			try
			{
				signUp();
				if (signUp)
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
