#include "function.h"

void printHCMUS(int x, int y)
{
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
void clearLine(int x, int y)
{
	goToXY(x, y); cout << "                                                                                    ";
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
void getPassword(string& password)
{
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
}
void changePassword(string& password)
{
	string curPass, newPass1, newPass2;
	while (true)
	{
		system("cls");
		int x = 10, y = 5;
		curPass = ""; 
		textColor(12);
		goToXY(x, y + 0); cout << "Current password   :";
		goToXY(x, y + 1); cout << "Enter new password :";
		goToXY(x, y + 2); cout << "Retype new password:";
		textColor(8);
		goToXY(x + 21, y + 0); cout << "                                                       ";
		goToXY(x + 21, y + 0); getPassword(curPass);
		if (curPass == password)
		{
			while (true)
			{
				newPass1 = ""; newPass2 = "";
				clearLine(x + 21, y + 1);
				goToXY(x + 21, y + 1); getPassword(newPass1);
				clearLine(x + 21, y + 2);
				goToXY(x + 21, y + 2); getPassword(newPass2);
				if (newPass1 == newPass2)
				{
					password = newPass1;
					textColor(2);
					goToXY(x, y + 4); cout << "Your password has been successfully changed!";
					goToXY(x, y + 5); system("pause");
					textColor(8);
					return;
				}
				else
				{
					int choice;
					textColor(4);
					goToXY(x, y + 4); cout << "These passwords do not match! Do you want to try again (Yes(1) / No(0))?";
					goToXY(x, y + 5); cout << "Enter your choice: "; cin >> choice; cin.get();
					textColor(8);
					if (!choice)
						return;
					clearLine(x, y + 4);
					clearLine(x, y + 5);
				}
			}
		}
		else
		{
			int choice;
			textColor(4);
			goToXY(x, y+4); cout << "Incorrect password! Do you want to try again (Yes(1) / No(0))?";
			goToXY(x, y+5); cout << "Enter your choice: "; cin >> choice; cin.get();
			textColor(8);
			if (!choice)
				break;
		}
	}
}
bool isStaff(string username, string password, Staff* pStaff, Staff*& curStaff)
{
	curStaff = pStaff;
	while (curStaff)
	{
		if ((username == curStaff->username) && (password == curStaff->password))
			break;
		curStaff = curStaff->pNext;
	}
	if (curStaff)
		return true;
	else
		return false;
}
bool isLecturer(string username, string password, Lecturer* pLecturer, Lecturer*& curLecturer)
{
	curLecturer = pLecturer;
	while (curLecturer)
	{
		if ((username == curLecturer->username) && (password == curLecturer->password))
			break;
		curLecturer = curLecturer->pNext;
	}
	if (curLecturer)
		return true;
	else
		return false;
}
bool isStudent(string username, string password, Student* pStudent, Student*& curStudent)
{
	int id;
	curStudent = pStudent;
	bool ok = convertStringToInt(username, id);
	while (curStudent)
	{
		if ((id == curStudent->id) && (password == curStudent->password))
			break;
		curStudent = curStudent->pNext;
	}
	if (curStudent)
		return true;
	else
		return false;
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
bool staffMenu(string username, string password)
{
	int numStaff;
	Staff* pStaff = nullptr;
	Staff* curStaff = nullptr;
	loadStaff(numStaff, pStaff);
	if (!isStaff(username, password, pStaff, curStaff))
	{
		deleteStaffList(pStaff);
		return false;
	}
	int numSemester;
	Semester* pSemester = nullptr;
	loadSemester(numSemester, pSemester);
	int choice;
	while (true)
	{
		system("cls");
		int x = 10, y = 5;
		goToXY(x, y++); cout << "Welcome " << msMr(curStaff->gender) << curStaff->fullname << '!' << endl; y++;
		goToXY(x, y++); cout << "1. View profile" << endl;
		goToXY(x, y++); cout << "   Task: " << endl;
		goToXY(x, y++); cout << "   2. Class" << endl;
		goToXY(x, y++); cout << "   3. Course" << endl;
		goToXY(x, y++); cout << "   4. Attendance list and scoreboard" << endl;
		goToXY(x, y++); cout << "5. Change password" << endl;
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
		case 3:
		{
			staffClassMenu();
			break;
		}
		case 4:
		{
			staffClassMenu();
			break;
		}
		case 5:
		{
			changePassword(curStaff->password);
			rewriteStaff(numStaff, pStaff);
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
	deleteStaffList(pStaff);
	deleteSemesterList(pSemester);
	return true;
}
bool lecturerMenu(string username, string password)
{
	int numLecturer;
	Lecturer* pLecturer = nullptr;
	Lecturer* curLecturer = nullptr;
	loadLecturer(numLecturer, pLecturer);
	if (!isLecturer(username, password, pLecturer, curLecturer))
	{
		deleteLecturerList(pLecturer);
		return false;
	}
	int numSemester;
	Semester* pSemester = nullptr;
	loadSemester(numSemester, pSemester);
	int choice;
	while (true)
	{
		system("cls");
		int x = 10, y = 5;
		goToXY(x, y++); cout << "Welcome " << msMr(curLecturer->gender) << curLecturer->fullname << '!' << endl; y++;
		goToXY(x, y++); cout << "1. View profile" << endl;
		goToXY(x, y++); cout << "   Task: " << endl;
		goToXY(x, y++); cout << "   2. View list of courses in the current semester" << endl;
		goToXY(x, y++); cout << "   3. View list of students of a course" << endl;
		goToXY(x, y++); cout << "   4. View attendance list of a course" << endl;
		goToXY(x, y++); cout << "   5. View a scoreboard of a course" << endl;
		goToXY(x, y++); cout << "   6. Edit an attendance" << endl;
		goToXY(x, y++); cout << "   7. Edit grade of a student" << endl;
		goToXY(x, y++); cout << "   8. Import scoreboard of a course from a csv file" << endl;
		goToXY(x, y++); cout << "9. Change password" << endl;
		goToXY(x, y++); cout << "0. Logout" << endl; y++;
		goToXY(x, y++); cout << "Please enter your choice: ";
		cin >> choice;	cin.get();
		if (choice == 0)	break;
		switch (choice)
		{
		case 1:
		{
			viewCurLecturerInfo(curLecturer);
			break;
		}
		case 2:
		{
			
			break;
		}
		case 3:
		{
			//viewCurLecturerInfo(curLecturer);
			break;
		}
		case 4:
		{
			//viewCurLecturerInfo(curLecturer);
			break;
		}
		case 5:
		{
			//viewCurLecturerInfo(curLecturer);
			break;
		}
		case 6:
		{
			//viewCurLecturerInfo(curLecturer);
			break;
		}
		case 7:
		{
			//viewCurLecturerInfo(curLecturer);
			break;
		}
		case 8:
		{
			//viewCurLecturerInfo(curLecturer);
			break;
		}
		case 9:
		{
			changePassword(curLecturer->password);
			rewriteLecturer(numLecturer, pLecturer);
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
	deleteLecturerList(pLecturer);
	deleteSemesterList(pSemester);
	return true;
}
bool studentMenu(string username, string password)
{
	int numStudent;
	Student* pStudent = nullptr;
	Student* curStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	if (!isStudent(username, password, pStudent, curStudent))
	{
		deleteStudentList(pStudent);
		return false;
	}
	int numSemester;
	Semester* pSemester = nullptr;
	loadSemester(numSemester, pSemester);
	int choice;
	while (true)
	{
		system("cls");
		int x = 10, y = 5;
		goToXY(x, y++); cout << "Welcome " << curStudent->fullname << '!' << endl; y++;
		goToXY(x, y++); cout << "1. View profile" << endl;
		goToXY(x, y++); cout << "   Task: " << endl;
		goToXY(x, y++); cout << "   2. Check in" << endl;
		goToXY(x, y++); cout << "   3. View check-in result" << endl;
		goToXY(x, y++); cout << "   4. View schedules" << endl;
		goToXY(x, y++); cout << "   5. View his/her scores of a course" << endl;
		goToXY(x, y++); cout << "6. Change password" << endl;
		goToXY(x, y++); cout << "0. Logout" << endl; y++;
		goToXY(x, y++); cout << "Please enter your choice: ";
		cin >> choice;	cin.get();
		if (choice == 0)	break;
		switch (choice)
		{
		case 1:
		{
			viewCurStudentInfo(curStudent);
			break;
		}
		case 2:
		{
			//staffClassMenu();
			break;
		}
		case 3:
		{
			//staffClassMenu();
			break;
		}
		case 4:
		{
			//staffClassMenu();
			break;
		}
		case 5:
		{
			//staffClassMenu();
			break;
		}
		case 6:
		{
			changePassword(curStudent->password);
			//rewriteStudent(numStudent, pStudent, ");
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
	deleteStudentList(pStudent);
	deleteSemesterList(pSemester);
	return true;
}
void login()
{
	while (true)
	{
		system("cls");
		textColor(1);
		printHCMUS(29, 12);
		textColor(13);
		int x = 50, y = 22;
		string username = "";
		string password = "";
		goToXY(x, y); cout << "Username: ";
		goToXY(x, y + 1); cout << "Password: ";

		textColor(8);
		goToXY(x + 10, y); getline(cin, username);
		goToXY(x + 10, y + 1);
		getPassword(password);

		textColor(14);
		if ((!staffMenu(username, password))
			&&
			(!lecturerMenu(username, password))
			&&
			(!studentMenu(username, password)))
		{
			textColor(4);
			goToXY(x, y + 9); cout << "Invalid login! Please try again.";
			goToXY(x, y + 10); system("pause");
		}
	}
}






