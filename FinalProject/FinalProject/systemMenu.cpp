#include "function.h"

void printHCMUS(int x, int y)
{
	textColor(13);
	goToXY(x, y);
	cout << " oo      oo       oooooooo    oooo     oooo    oo      oo     oooooo"; y++; goToXY(x, y);
	cout << " oo      oo      oo           oo oo   oo oo    oo      oo    oo     "; y++; goToXY(x, y);
	cout << " oo      oo     oo            oo  oo oo  oo    oo      oo    oo     "; y++; goToXY(x, y);
	cout << " oooooooooo    oo             oo   ooo   oo    oo      oo     ooooo "; y++; goToXY(x, y);
	cout << " oo      oo     oo            oo         oo    oo      oo         oo"; y++; goToXY(x, y);
	cout << " oo      oo      oo           oo         oo    oo      oo         oo"; y++; goToXY(x, y);
	cout << " oo      oo       oooooooo    oo         oo    oooooooooo    oooooo "; y++; goToXY(x, y);
}
string msMr(int gender)
{
	if (gender)
		return "Ms.";
	else
		return "Mr.";
}
void staffMenu(Staff*& curStaff)
{
	int choice;
	while (true)
	{
		system("cls");
		int x = 10, y = 4;
		goToXY(x, y++); cout << "Welcome " << msMr(curStaff->gender) << curStaff->fullname << '!' << endl;
		goToXY(x, y++); cout << "1. Remove a student" << endl;
		goToXY(x, y++); cout << "2. Change a student's info" << endl;
		goToXY(x, y++); cout << "3. Move a student to another class" << endl;
		goToXY(x, y++); cout << "0. Logout" << endl;
		goToXY(x, y++); cout << "Please enter your choice: "; cin >> choice;
		if (choice == 0)
		{
			cin.get();
			break;
		}
		switch (choice)
		{
		case 1:
		{
			removeStudents();
			break;
		}
		case 2:
		{
			ChangeStudentsInfo();
			break;
		}
		case 3:
		{
			ChangeStudentsClass();
			break;
		}
		default:
			cout << "Incorrect" << endl;
			cout << endl;
			break;
		}
	}
}
void login()
{
	while (true)
	{
		system("cls");
		printHCMUS(40, 10);
		int x = 56, y = 20;
		string username = "ntmphuc";
		string password = "";
		goToXY(x, y); cout << "Username: ";
		goToXY(x, y + 1); cout << "Password: ";
		textColor(15);
		goToXY(x + 10, y); getline(cin, username); 
		goToXY(x + 10, y + 1);
		char ch = _getch();
		while (ch != 13) {
			if (ch == '\b')
			{
				cout << "\b \b";
				password.pop_back();
			}
			else
			{
				password.push_back(ch);
				cout << '*';
			}
			ch = _getch();
		}
		Staff* curStaff = nullptr;
		if (isStaff(username, password, curStaff))
		{
			staffMenu(curStaff);
			delete curStaff;
		}
		else
		{
			goToXY(x, y + 9);
			textColor(4);
			cout << "Invalid login, please try again.";
			goToXY(x, y + 10);
			system("pause");
			textColor(15);
		}
	}
}