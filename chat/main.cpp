#include "chatEngine.h"
using namespace std;


int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char choice = 'null';
	while (choice != 'q')
	{
		SetConsoleTextAttribute(hConsole, 11);
		cout << "Welcome to chat" << endl;
		cout << "Press [s] - sign up; [r] - registry new user; [q] - quit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 's':
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
			break;
		case 'r':
			try { reg(); }
			catch (const char* ex)
			{
				cout << ex << endl;
			}
			break;
		case 'q':
			break;
		}
		cout << "\n============================================\n";
	}
	
	return 0;
}