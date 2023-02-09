#include "chatEngine.h"
using namespace std;


int main()
{	
	char choice = 'null';
	while (choice != 'q')
	{
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
			reg();
			/*try { reg(); }
			catch (const char* ex)
			{
				cout << ex << endl;
			}*/
			break;
		case 'q':
			break;
		}
		cout << "============================================\n";
	}
	
	return 0;
}