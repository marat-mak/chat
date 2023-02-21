#include "chatEngine.h"
using namespace std;


int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int choice = 0;
	while (true)
	{
		SetConsoleTextAttribute(hConsole, 11);
		cout << "Welcome to chat" << endl;
		cout << "Press [s] - sign up; [r] - registry new user; [q] - quit" << endl;
		choice = _getche();
		cout << endl;
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
				cout << ex << endl;
			}		
		}
		if (choice == 114)
		{
			try { reg(); }
			catch (const char* ex)
			{
				cout << ex << endl;
			}
		}
		if (choice == 113)
		{
			break;
		}		
		cout << "\n============================================\n";
	}	
	return 0;
}