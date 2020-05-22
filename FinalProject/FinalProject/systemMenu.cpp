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
bool convertStringToInt(string str, int& x)
{
	int n = str.length();
	x = 0;
	for (int i = 0; i < n; i++)
		if (isdigit(str[i]))
			x = x * 10 + int(str[i]) - int('0');
		else
			return false;
	return true;
}
void staffClassMenu()
{
	int choice;
	while (true)
	{
		system("cls");
		int x = 10, y = 5;
		goToXY(x, y++); cout << "1. Import students of a class from a csv file." << endl;
		goToXY(x, y++); cout << "2. Manually add a new student to a class." << endl;
		goToXY(x, y++); cout << "3. Change a student's info." << endl;
		goToXY(x, y++); cout << "4. Remove a student." << endl;
		goToXY(x, y++); cout << "5. Move a student to another class." << endl;
		goToXY(x, y++); cout << "6. View list of classes." << endl;
		goToXY(x, y++); cout << "7. View list of students in a class." << endl;
		goToXY(x, y++); cout << "0. Return" << endl; y++;
		goToXY(x, y++); cout << "Please enter your choice: "; 
		cin >> choice;	cin.get();
		if (choice == 0)	break;
		switch (choice)
		{
		case 1:
		{
			import_class();
			break;
		}
		case 2:
		{
			manually_add_student_to_class();
			break;
		}
		case 3:
		{
			ChangeStudentsInfo();
			break;
		}
		case 4:
		{
			removeStudents();
			break;
		}
		case 5:
		{
			ChangeStudentsClass();
			break;
		}
		case 6:
		{
			viewClass();
			break;
		}
		case 7:
		{
			viewStudentsInClass();
			break;
		}
		default:
			textColor(4);
			goToXY(x, y + 5); cout << "Invalid choice! Please try again." << endl;
			goToXY(x, y + 6); system("pause");
			textColor(15);
			break;
		}
	}
}
void staffMenu(Staff*& curStaff, int& numSemester, Semester*& pSemester)
{
	int choice;
	while (true)
	{
		system("cls");
		int x = 10, y = 5;
		goToXY(x, y++); cout << "Welcome " << msMr(curStaff->gender) << curStaff->fullname << '!' << endl; y++;
		goToXY(x, y++); cout << "1. View profile" << endl;
		goToXY(x, y++); cout << "   Task: " << endl;
		goToXY(x, y++); cout << "2. Class" << endl;
		goToXY(x, y++); cout << "3. Course" << endl;
		goToXY(x, y++); cout << "4. Scoreboard" << endl;
		goToXY(x, y++); cout << "5. Attendance list" << endl;
		goToXY(x, y++); cout << "0. Logout" << endl; y++;
		goToXY(x, y++); cout << "Please enter your choice: "; 
		cin >> choice;	cin.get();
		if (choice == 0)	break;
		switch (choice)
		{
		case 1:
		{
			viewCurStaffInfo(curStaff);
			break;
		}
		case 2:
		{
			staffClassMenu();
			break;
		}
		default:
			textColor(4);
			goToXY(x, y + 5); cout << "Invalid choice! Please try again." << endl;
			goToXY(x, y + 6); system("pause");
			textColor(15);
			break;
		}
	}
}
void login(int& numSemester, Semester*& pSemester)
{
	while (true)
	{
		system("cls");
		printHCMUS(29, 12);
		int x = 50, y = 22;
		string username = "";
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
			staffMenu(curStaff, numSemester, pSemester);
			delete curStaff;
		}
		else
		{
			textColor(4);
			goToXY(x, y + 9); cout << "Invalid login! Please try again.";
			goToXY(x, y + 10); system("pause");
			textColor(15);
		}
	}
}