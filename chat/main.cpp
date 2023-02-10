#include "chatEngine.h"
using namespace std;


int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char choice = 'null';
	while (choice != 'q')
	{
		SetConsoleTextAttribute(hConsole, 11);
		cout << "Добро пожаловать в чат!" << endl;
		cout << "Введите [s] - для входа; [r] - регистрации; [q] - выхода" << endl;
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
		cout << "============================================\n";
	}
	
	return 0;
}