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
int cmpTime(Time time1, Time time2)
{
	if (time1.hour > time2.hour)
		return 1;
	if (time1.hour < time2.hour)
		return -1;
	if (time1.minute > time2.minute)
		return 1;
	if (time1.minute > time2.minute)
		return -1;
	return 0;
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
		goToXY(x, y + 0); cout << "Current password   :";
		goToXY(x, y + 1); cout << "Enter new password :";
		goToXY(x, y + 2); cout << "Retype new password:";
		textColor(12);
		goToXY(x + 21, y + 0); cout << "                                                       ";
		goToXY(x + 21, y + 0); getPassword(curPass);
		if (curPass == password)
		{
			while (true)
			{
				textColor(12);
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
					textColor(14);
					return;
				}
				else
				{
					int choice;
					textColor(4);
					goToXY(x, y + 4); cout << "These passwords do not match! Do you want to try again (Yes(1) / No(0))?";
					goToXY(x, y + 5); cout << "Enter your choice: "; 
					string tmp;
					do {
						clearLine(x + 19, y + 5);
						goToXY(x + 19, y + 5); getline(cin, tmp); 
					} while (!convertStringToInt(tmp, choice));
					textColor(14);
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
			goToXY(x, y+5); cout << "Enter your choice: "; 
			string tmp;
			do {
				clearLine(x + 19, y + 5);
				goToXY(x + 19, y + 5); getline(cin, tmp);
			} while (!convertStringToInt(tmp, choice));
			textColor(14);
			if (!choice)
				break;
		}
	}
}
void rewriteClassStudentInfo(Student* curStudent)
{
	int numStudent;
	Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, curStudent->cla);
	Student* cur = pStudent;
	while (cur)
	{
		if (cur->id == curStudent->id)
			break;
		cur = cur->pNext;
	}
	if (cur)
		cur->password = curStudent->password;
	rewriteStudent(numStudent, pStudent, curStudent->cla);
	deleteStudentList(pStudent);
}
void getCurrentTime(Date& curDate, Time& curTime)
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%d %m %Y %H %M %S", timeinfo);
	string str(buffer);
	convertStringToInt(str.substr(0, 2), curDate.day);
	convertStringToInt(str.substr(3, 2), curDate.month);
	convertStringToInt(str.substr(6, 4), curDate.year);
	convertStringToInt(str.substr(11, 2), curTime.hour);
	convertStringToInt(str.substr(14, 2), curTime.minute);
}
void checkIn(Student* curStudent, Semester* pSemester)
{
	system("cls");
	int x = 10, y = 5;
	Date curDate;
	Time curTime;
	getCurrentTime(curDate, curTime);
	Semester* curSemester = pSemester;
	while (curSemester)
	{
		Schedule* curSchedule = curSemester->pSchedule;
		while (curSchedule)
		{
			Course* curCourse = curSchedule->pCourse;
			while (curCourse)
			{
				Student* curStudentCourse = curCourse->pStudent;
				while (curStudentCourse)
				{
					if (curStudentCourse->id == curStudent->id)
						break;
					curStudentCourse = curStudentCourse->pNext;
				}
				if (curStudentCourse)
				{
					int i = 0;
					Date date = curCourse->dateStart;
					while (cmpDate(date, curCourse->dateEnd) <= 0)
					{
						if (cmpDate(date, curDate) == 0)
							if ((cmpTime(curCourse->timeStart, curTime) <= 0) && (cmpTime(curTime, curCourse->timeEnd) <= 0))
							{
								curStudentCourse->attend[i] = 1;
								textColor(2);
								goToXY(x, y++); cout << "Check in succesfully! " << curCourse->courseID << " - " << curCourse->courseName;
								goToXY(x, y++); system("pause");
								textColor(14);
								rewriteCourse(curCourse, "Semester\\" + curSemester->academicYear + "-" + curSemester->semester + "\\" + curSchedule->cla + "\\" + curCourse->courseID + ".txt");
								return;
							}
						i++;
						nextWeek(date);
					}
				}
				curCourse = curCourse->pNext;
			}
			curSchedule = curSchedule->pNext;
		}
		curSemester = curSemester->pNext;
	}
	textColor(4);
	goToXY(x, y++); cout << "Check in failed! There are no available courses at the moment." << endl;
	goToXY(x, y++); system("pause");
	textColor(14);
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
	string tmp;
	while (true)
	{
		system("cls");
		int x = 10, y = 5;
		goToXY(x, y++); cout << "1. Import students of a class from a csv file" << endl;
		goToXY(x, y++); cout << "2. Manually add a new student to a class" << endl;
		goToXY(x, y++); cout << "3. Change a student's info" << endl;
		goToXY(x, y++); cout << "4. Remove a student" << endl;
		goToXY(x, y++); cout << "5. Move a student to another class" << endl;
		goToXY(x, y++); cout << "6. View list of classes" << endl;
		goToXY(x, y++); cout << "7. View list of students in a class" << endl;
		goToXY(x, y++); cout << "0. Return" << endl; y++;
		goToXY(x, y++); cout << "Please enter your choice: "; 
		getline(cin, tmp);
		if (!convertStringToInt(tmp, choice))
			choice = -1;
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
			editStudent();
			break;
		}
		case 4:
		{
			removestudent();
			break; //done
		}
		case 5:
		{
			changeStudentClass();
			break; //done
		}
		case 6:
		{
			viewClass();
			break; //done
		}
		case 7:
		{
			viewStudentsInClass();
			break; //done
		}
		default:
			textColor(4);
			goToXY(x, y + 5); cout << "Invalid choice! Please try again." << endl;
			goToXY(x, y + 6); system("pause");
			textColor(14);
			break;
		}
	}
}
void staffCourseMenu(int& numSemester, Semester*& pSemester)
{
	int choice;
	string tmp;
	while (true)
	{
		system("cls");
		int x = 10, y = 5;
		goToXY(x, y++); cout << "1. Create / update / delete academic years and semesters" << endl;
		goToXY(x, y++); cout << "2. Import courses from a csv file" << endl;
		goToXY(x, y++); cout << "3. Manually add a new course" << endl;
		goToXY(x, y++); cout << "4. Edit an existing course" << endl; 
		goToXY(x, y++); cout << "5. Remove a course" << endl;
		goToXY(x, y++); cout << "6. Remove a specific student from a course" << endl;
		goToXY(x, y++); cout << "7. Add a specific student to a course" << endl;
		goToXY(x, y++); cout << "8. View list of courses in a semester" << endl;
		goToXY(x, y++); cout << "9. View list of students of a course" << endl;
		goToXY(x, y++); cout << "10. View list of lecturers" << endl;
		goToXY(x, y++); cout << "11. View list of semesters" << endl;
		goToXY(x, y++); cout << "0. Return" << endl; y++;
		goToXY(x, y++); cout << "Please enter your choice: ";
		getline(cin, tmp);
		if (!convertStringToInt(tmp, choice))
			choice = -1;
		if (choice == 0)	break;
		switch (choice)
		{
		case 1:
		{
			updateAcademicYear(numSemester, pSemester);
			break; //done
		}
		case 2:
		{
			importCourse(numSemester, pSemester);
			break; //done
		}
		case 3:
		{
			manuallyAddCourse(numSemester, pSemester);
			break; //done
		}
		case 4:
		{
			editCourse(numSemester, pSemester);
			break; //done
		}
		case 5:
		{
			removeCourse(numSemester, pSemester);
			break; //done
		}
		case 6:
		{
			removeStudentfromCourse(numSemester, pSemester);
			break; //done
		}
		case 7:
		{
			addStudentIntoCourse(pSemester);
			break; //done
		}
		case 8:
		{
			viewCourse(pSemester);
			break; //done
		}
		case 9:
		{
			viewStudentInCourse(pSemester);
			break; //done
		}
		case 10:
		{
			viewLecturer();
			break; //done
		}
		case 11:
		{
			viewallSemester();
			break; //done
		}
		default:
			textColor(4);
			goToXY(x, y + 5); cout << "Invalid choice! Please try again." << endl;
			goToXY(x, y + 6); system("pause");
			textColor(14);
			break;
		}
	}
}
void staffASMenu(Semester* pSemester)
{
	int choice;
	string tmp;
	while (true)
	{
		system("cls");
		int x = 10, y = 5;
		goToXY(x, y++); cout << "1. View attendance list of a course" << endl;
		goToXY(x, y++); cout << "2. View the scoreboard of a course" << endl;
		goToXY(x, y++); cout << "3. Export an attendance list to a csv file" << endl;
		goToXY(x, y++); cout << "4. Export a scoreboard to a csv file" << endl;
		goToXY(x, y++); cout << "0. Return" << endl; y++;
		goToXY(x, y++); cout << "Please enter your choice: ";
		getline(cin, tmp);
		if (!convertStringToInt(tmp, choice))
			choice = -1;
		if (choice == 0)	break;
		switch (choice)
		{
		case 1:
		{
			viewCourseAttendance(pSemester);
			break; //done
		}
		case 2:
		{
			viewCourseScoreboard(pSemester);
			break; //done
		}
		case 3:
		{
			exportAttendanceList(pSemester);
			break; //done
		}
		case 4:
		{
			exportScoreboard(pSemester);
			break; //done
		}
		default:
			textColor(4);
			goToXY(x, y + 5); cout << "Invalid choice! Please try again." << endl;
			goToXY(x, y + 6); system("pause");
			textColor(14);
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
	string tmp;
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
		getline(cin, tmp);
		if (!convertStringToInt(tmp, choice))
			choice = -1;
		if (choice == 0)	break;
		switch (choice)
		{
		case 1:
		{
			viewCurStaffInfo(curStaff);	
			break; //done
		}
		case 2:
		{
			staffClassMenu();
			break;
		}
		case 3:
		{
			staffCourseMenu(numSemester, pSemester);
			break; 
		}
		case 4:
		{
			staffASMenu(pSemester);
			break; //done
		}
		case 5:
		{
			changePassword(curStaff->password);
			rewriteStaff(numStaff, pStaff);
			break;	//done
		}
		default:
			textColor(4);
			goToXY(x, y + 5); cout << "Invalid choice! Please try again." << endl;
			goToXY(x, y + 6); system("pause");
			textColor(14);
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
	string tmp;
	while (true)
	{
		system("cls");
		int x = 10, y = 5;
		goToXY(x, y++); cout << "Welcome " << msMr(curLecturer->gender) << curLecturer->fullname << '!' << endl; y++;
		goToXY(x, y++); cout << "1. View profile" << endl;
		goToXY(x, y++); cout << "   Task: " << endl;
		goToXY(x, y++); cout << "   2. View list of courses in a semester" << endl;
		goToXY(x, y++); cout << "   3. View list of students of a course" << endl;
		goToXY(x, y++); cout << "   4. View attendance list of a course" << endl;
		goToXY(x, y++); cout << "   5. View a scoreboard of a course" << endl;
		goToXY(x, y++); cout << "   6. Edit an attendance" << endl;
		goToXY(x, y++); cout << "   7. Edit grade of a student" << endl;
		goToXY(x, y++); cout << "   8. Import scoreboard of a course from a csv file" << endl;
		goToXY(x, y++); cout << "9. Change password" << endl;
		goToXY(x, y++); cout << "0. Logout" << endl; y++;
		goToXY(x, y++); cout << "Please enter your choice: ";
		getline(cin, tmp);
		if (!convertStringToInt(tmp, choice))
			choice = -1;
		if (choice == 0)	break;
		switch (choice)
		{
		case 1:
		{
			viewCurLecturerInfo(curLecturer);
			break; //done
		}
		case 2:
		{
			viewCourse(pSemester);
			break; //done
		}
		case 3:
		{
			viewStudentInCourse(pSemester);
			break; //done
		}
		case 4:
		{
			viewCourseAttendance(pSemester);
			break; //done
		}
		case 5:
		{
			viewCourseScoreboard(pSemester);
			break; //done
		}
		case 6:
		{
			editAttendance(numSemester, pSemester);
			break; //done
		}
		case 7:
		{
			editScore(numSemester, pSemester);
			break; //done
		}
		case 8:
		{
			importScoreboard(numSemester, pSemester);
			break;
		}
		case 9:
		{
			changePassword(curLecturer->password);
			rewriteLecturer(numLecturer, pLecturer);
			break; //done
		}
		default:
			textColor(4);
			goToXY(x, y + 5); cout << "Invalid choice! Please try again." << endl;
			goToXY(x, y + 6); system("pause");
			textColor(14);
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
	string tmp;
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
		goToXY(x, y++); cout << "   5. View scores" << endl;
		goToXY(x, y++); cout << "6. Change password" << endl;
		goToXY(x, y++); cout << "0. Logout" << endl; y++;
		goToXY(x, y++); cout << "Please enter your choice: ";
		getline(cin, tmp);
		if (!convertStringToInt(tmp, choice))
			choice = -1;
		if (choice == 0)	break;
		switch (choice)
		{
		case 1:
		{
			viewCurStudentInfo(curStudent);
			break; //done
		}
		case 2:
		{
			checkIn(curStudent, pSemester);
			break; //done
		}
		case 3:
		{
			viewCheckInResult(curStudent, pSemester);
			break; //done
		}
		case 4:
		{
			viewSchedule(curStudent, pSemester);
			break; //done
		}
		case 5:
		{
			student_view_score(curStudent, pSemester);
			break; //done
		}
		case 6:
		{
			changePassword(curStudent->password);
			rewriteStudent(numStudent, pStudent, "Student");
			rewriteClassStudentInfo(curStudent);
			break; //done
		}
		default:
			textColor(4);
			goToXY(x, y + 5); cout << "Invalid choice! Please try again." << endl;
			goToXY(x, y + 6); system("pause");
			textColor(14);
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
		textColor(9);
		printHCMUS(29, 12);
		int x = 50, y = 22;
		string username = "";
		string password = "";
		goToXY(x, y); cout << "Username: ";
		goToXY(x, y + 1); cout << "Password: ";

		textColor(12);
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






