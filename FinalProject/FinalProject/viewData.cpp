#include "function.h"

string maleFemale(int gender)
{
	if (gender)
		return "female";
	else
		return "male";
}
void printDate(int x)
{
	if (x < 10)
		cout << 0 << x;
	else
		cout << x;
}
bool isLunarYear(int year)
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}
void nextWeek(Date& date)
{
	int nday;
	if ((4 == date.month) || (6 == date.month) || (9 == date.month) || (11 == date.month))
		nday = 30;
	else
		if (2 == date.month)
			if (isLunarYear(date.year))
				nday = 29;
			else
				nday = 28;
		else nday = 31;
	date.day += 7;
	if (date.day > nday)
	{
		date.day = date.day - nday;
		date.month++;
	}
	if (date.month > 12)
	{
		date.month = 1;
		date.year++;
	}
}
int cmpDate(Date& date1, Date& date2)
{
	if (date1.year > date2.year)
		return 1;
	if (date1.year < date2.year)
		return -1;
	if (date1.month > date2.month)
		return 1;
	if (date1.month < date2.month)
		return -1;
	if (date1.day > date2.day)
		return 1;
	if (date1.day < date2.day)
		return -1;
	return 0;
}
void sortStudentList(Student*& pStudent)
{
	for (Student* curI = pStudent; curI != nullptr; curI = curI->pNext)
		for (Student* curJ = curI->pNext; curJ != nullptr; curJ = curJ->pNext)
			if (curI->id > curJ->id)
			{
				swap(curI->id, curJ->id);
				swap(curI->grade, curJ->grade);
				for (int k = 0; k < 10; k++)
					swap(curI->attend[k], curJ->attend[k]);
			}
}
void viewCurStaffInfo(Staff* curStaff)
{
	system("cls");
	int x = 10, y = 5;
	goToXY(x, y++); cout << "Your Profile Information" << endl; y++;
	goToXY(x, y++); cout << "User name: " << curStaff->username << endl;
	goToXY(x, y++); cout << "Full name: " << curStaff->fullname << endl;
	goToXY(x, y++); cout << "Gender   : " << maleFemale(curStaff->gender) << endl; y++;
	goToXY(x, y++); system("pause");
}
void viewCurLecturerInfo(Lecturer* curLecturer)
{
	system("cls");
	int x = 10, y = 5;
	goToXY(x, y++); cout << "Your Profile Information" << endl; y++;
	goToXY(x, y++); cout << "User name: " << curLecturer->username << endl;
	goToXY(x, y++); cout << "Full name: " << curLecturer->fullname << endl;
	goToXY(x, y++); cout << "Degree   : " << curLecturer->degree << endl;
	goToXY(x, y++); cout << "Gender   : " << maleFemale(curLecturer->gender) << endl; y++;
	goToXY(x, y++); system("pause");
}
void viewCurStudentInfo(Student* curStudent)
{
	system("cls");
	int x = 10, y = 5;
	goToXY(x, y++); cout << "Your Profile Information" << endl; y++;
	goToXY(x, y++); cout << "ID number    : " << curStudent->id << endl;
	goToXY(x, y++); cout << "Full name    : " << curStudent->fullname << endl;
	goToXY(x, y++); cout << "Date of birth: " << curStudent->dob.day << '/' << curStudent->dob.month << '/' << curStudent->dob.year << endl;
	goToXY(x, y++); cout << "Class        : " << curStudent->cla << endl; y++;
	goToXY(x, y++); system("pause");
}
void viewLecturer()
{
	system("cls");
	int numLecturer;
	Lecturer* pLecturer = nullptr;
	loadLecturer(numLecturer, pLecturer);
	int x = 10, y = 5, count = 1;
	Lecturer* cur = pLecturer;
	goToXY(x, y++); cout << "Here is the list of lecturer:" << endl; y++;
	while (cur)
	{
		goToXY(x, y++); cout << count++ << ". " << cur->fullname << " - " << cur->username << endl;
		goToXY(x + 3, y++); cout << "Degree: " << cur->degree << endl;
		goToXY(x + 3, y++); cout << "Gender: " << maleFemale(cur->gender) << endl; y++;
		cur = cur->pNext;
	}
	deleteLecturerList(pLecturer);
	goToXY(x, y++); system("pause");
}
bool inputCourse(int& x, int&y, Semester* pSemester, Course*& curCourse, string& directory)
{
	string academicYear, semester, cla, courseId, dir = "Semester\\"; curCourse = nullptr;
	//Semester
	goToXY(x, y++); cout << "Enter academic year: "; getline(cin, academicYear);
	goToXY(x, y++); cout << "Enter semester name: "; getline(cin, semester);
	Semester* curSemester = pSemester;
	while (curSemester)
	{
		if ((curSemester->academicYear == academicYear) && (curSemester->semester == semester))
			break;
		curSemester = curSemester->pNext;
	}
	if (curSemester == nullptr)
	{
		y++;
		int choice;
		textColor(4);
		goToXY(x, y++); cout << "Invalid semester! Do you want to try again (Yes(1) / No(0))?";
		goToXY(x, y++); cout << "Enter your choice: "; cin >> choice; cin.get();
		textColor(15);
		return choice;
	}
	//Schedule
	dir = dir + academicYear + '-' + semester + "\\";
	Schedule* curSchedule; 
	while (true)
	{
		curSchedule = curSemester->pSchedule;
		clearLine(x, y);
		goToXY(x, y); cout << "Enter class name: "; getline(cin, cla);
		while (curSchedule)
		{
			if (curSchedule->cla == cla)
				break;
			curSchedule = curSchedule->pNext;
		}
		if (curSchedule == nullptr)
		{
			int choice;
			textColor(4);
			goToXY(x, y + 2); cout << "Invalid class! Do you want to try again (Yes(1) / No(0))?";
			goToXY(x, y + 3); cout << "Enter your choice: "; cin >> choice; cin.get();
			textColor(14);
			clearLine(x, y + 2);
			clearLine(x, y + 3);
			if (!choice)
				return false;
		}
		else
		{
			y++;
			break;
		}
	}
	//Course
	dir = dir + cla + "\\";
	while (true)
	{
		curCourse = curSchedule->pCourse;
		clearLine(x, y);
		goToXY(x, y); cout << "Enter course id: "; getline(cin, courseId);
		while (curCourse)
		{
			if (curCourse->courseID == courseId)
				break;
			curCourse = curCourse->pNext;
		}
		if (curCourse == nullptr)
		{
			int choice;
			textColor(4);
			goToXY(x, y + 2); cout << "Invalid course Id! Do you want to try again (Yes(1) / No(0))?";
			goToXY(x, y + 3); cout << "Enter your choice: "; cin >> choice; cin.get();
			textColor(14);
			clearLine(x, y + 2);
			clearLine(x, y + 3);
			if (!choice)
				return false;
		}
		else
		{
			y++;
			break;
		}
	}
	directory = dir;
	return true;
}
void viewCourseAttendance(Semester* pSemester)
{
	int x, y;
	string dir; 
	Course* curCourse;
	while (true)
	{
		system("cls");
		x = 10; y = 5;
		goToXY(x, y++); cout << "Choose the course you want to view the attendance list"; y++;	 
		bool check = inputCourse(x, y, pSemester, curCourse, dir);
		if (curCourse)	break;
		if (check)	viewCourseAttendance(pSemester);	
		return;
	}
	resizeConsole(1100, 700);
	int numStudent;
	Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	y++; goToXY(x+40, y++); cout << "Attendance list of the course" << endl; y++;
	int numDay = 10;
	Date date = curCourse->dateStart;
	for (int i = 0; i < 10; i++)
	{
		goToXY(x + 23 + i * 10, y);
		if (cmpDate(date, curCourse->dateEnd) == 1)
		{
			numDay = i;
			break;
		}
		printDate(date.day); cout << '/'; printDate(date.month); cout << '/'; printDate(date.year % 100);
		nextWeek(date);
	}
	sortStudentList(curCourse->pStudent);
	Student* prevStudent = nullptr;
	Student* curStudent = curCourse->pStudent;
	while (curStudent)
	{
		Student* cur = pStudent;
		while (cur)
		{
			if (cur->id == curStudent->id)
				break;
			cur = cur->pNext;
		}
		if (cur)
		{
			goToXY(x, ++y); cout << cur->id;
			goToXY(x, ++y); cout << cur->fullname;
			for (int i = 0; i < numDay; i++)
			{
				goToXY(x + 27 + i * 10, y);
				cout << curStudent->attend[i];
			}
			prevStudent = curStudent;
			curStudent = curStudent->pNext;
		}
		else
		{
			curCourse->numStudent--;
			deleteStudent(prevStudent, curStudent, curCourse->pStudent);
		}
	}
	y++;
	goToXY(x, ++y); system("pause");
	rewriteCourse(curCourse, dir + curCourse->courseID + ".txt");
	deleteStudentList(pStudent);
	resizeConsole(1000, 700);
}
void viewCourseScoreboard(Semester* pSemester)
{
	int x, y;
	string dir;
	Course* curCourse;
	while (true)
	{
		system("cls");
		x = 10; y = 5;
		goToXY(x, y++); cout << "Choose the course you want to view the scoreboard"; y++;
		bool check = inputCourse(x, y, pSemester, curCourse, dir);
		if (curCourse)	break;
		if (check)	viewCourseAttendance(pSemester);
		return;
	}

	int numStudent;
	Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	y++; goToXY(x + 30, y++); cout << "Scoreboard of the course" << endl; y++;
	goToXY(x + 25, y); cout << "Midterm";
	goToXY(x + 36, y); cout << "Final";
	goToXY(x + 46, y); cout << "Bonus";
	goToXY(x + 56, y); cout << "Total";
	sortStudentList(curCourse->pStudent);
	Student* prevStudent = nullptr;
	Student* curStudent = curCourse->pStudent;
	while (curStudent)
	{
		Student* cur = pStudent;
		while (cur)
		{
			if (cur->id == curStudent->id)
				break;
			cur = cur->pNext;
		}
		if (cur)
		{
			goToXY(x, ++y); cout << cur->id;
			goToXY(x, ++y); cout << cur->fullname;
			goToXY(x + 28, y); cout << curStudent->grade.midterm;
			goToXY(x + 38, y); cout << curStudent->grade.total;
			goToXY(x + 48, y); cout << curStudent->grade.final;
			goToXY(x + 58, y); cout << curStudent->grade.bonus;
			prevStudent = curStudent;
			curStudent = curStudent->pNext;
		}
		else
		{
			curCourse->numStudent--;
			deleteStudent(prevStudent, curStudent, curCourse->pStudent);
		}
	}
	y++;
	goToXY(x, ++y); system("pause");
	rewriteCourse(curCourse, dir + curCourse->courseID + ".txt");
	deleteStudentList(pStudent);
}
void viewClass() {
	system("cls");
	int x = 10, y = 5;
	int numClass;
	Class* pClass = nullptr;
	loadClass(numClass, pClass);
	if (pClass == nullptr) {
		cout << "There is no class in stored data" << endl;
	}
	else {
		Class* cur = pClass;
		int i = 1;
		y++; goToXY(x, y++); cout << "Here is the list of class:" << endl; y++;
		while (cur != nullptr) {
			goToXY(x + 10, y++); cout << i << ". " << cur->name << endl;
			cur = cur->pNext;
			++i;
		}
	}
	deleteClassList(pClass);
	y++; goToXY(x, y++); system("pause");
}
void viewStudentsInClass() {
	system("cls");
	int x = 10, y = 5;
	Class* pClass = nullptr;
	int numClass;
	loadClass(numClass, pClass);
	Class* cur = pClass;

	// View Selection
	y++; goToXY(x, y++); cout << "Choose the class you want to view students list: " << endl;  ++y;
	int i = 0;
	while (cur != nullptr) {
		goToXY(x + 5, y++); cout << i + 1 << ". " << cur->name << endl;
		cur = cur->pNext;
		++i;
	}

	cur = pClass;
	int count = 1;
	int choice;

	++y; goToXY(x + 3, y++); cout << "Your Choice is: "; ++y;
	cin >> choice;


	while (cur != nullptr) {
		if (count == choice) {
			if (cur->pStudent == nullptr)
			{
				goToXY(x + 3, y++); cout << "There are no students in this class at the moment." << endl;
				break;
			}
			else {
				system("cls");
				x = 10, y = 5;
				++y; goToXY(x + 6, ++y); cout << "Here is the student list in class " << cur->name << endl; ++y;
				while (cur->pStudent != nullptr) {
					goToXY(x + 10, y++); cout << cur->pStudent->fullname << " - " << cur->pStudent->id << endl;
					cur->pStudent = cur->pStudent->pNext;
				}
			}
			break;
		}
		else {
			++count;
			cur = cur->pNext;
		}
	}
	deleteClassList(pClass);
	y++; goToXY(x, y++); system("pause");
}
void viewCourse(Semester*& pSemester) {
	int x = 10, y = 5;
	string year, term;
	int i = 1;

	// User enters selection
	goToXY(x, y++); cout << "Please enter the academic year you need (Example: 2018-2019): ";
	cin >> year;
	goToXY(x, y++); cout << "Please enter the semester you need (Example: HK2): ";
	cin >> term;

	Semester* cur = pSemester;
	while (cur != nullptr) {
		if (year == cur->academicYear && term == cur->semester)
			break;
		cur = cur->pNext;
	}
	if (cur) {
		if (cur->pSchedule == nullptr) {
			++y; goToXY(x, y++); cout << "This semester is empty" << endl;
			return;
		}
		system("cls");
		x = 10, y = 5;
		goToXY(x + 6, y++); cout << "Here is the course list of each class" << endl;
		while (cur->pSchedule != nullptr) {
			++y; goToXY(x + 6, ++y); cout << i << ". " << cur->pSchedule->cla << ": " << endl;
			while (cur->pSchedule->pCourse != nullptr) {
				goToXY(x + 10, ++y); cout << "   - " << cur->pSchedule->pCourse->courseName << " - " << cur->pSchedule->pCourse->courseID << endl; // Print out course's name and course's id
				cur->pSchedule->pCourse = cur->pSchedule->pCourse->pNext; // move to next course
			}
			cur->pSchedule = cur->pSchedule->pNext; // move to next schedule
			++i;
		}
	}
	else {
		++y; goToXY(x, y++); cout << "There is no information about this semester in the system" << endl;
	}
	y = y + 3; goToXY(x, y++); system("pause");
}
void viewStudentInCourse(Semester*& pSemester) {
	int x = 10, y = 5;
	string dir;
	Course* curCourse;
	while (true)
	{
		system("cls");
		x = 10; y = 5;
		goToXY(x, y++); cout << "Choose the course you want to view the students"; y++;
		bool check = inputCourse(x, y, pSemester, curCourse, dir);
		if (curCourse)	break;
		if (check)	viewStudentInCourse(pSemester);
		return;
	}

	system("cls");
	x = 10, y = 5;
	int numStudent;
	Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	y++; goToXY(x + 30, y++); cout << "Students of the course " << curCourse->courseID; y++;
	sortStudentList(curCourse->pStudent);
	Student* prevStudent = nullptr;
	Student* curStudent = curCourse->pStudent;
	while (curStudent)
	{
		++y;
		Student* cur = pStudent;
		while (cur)
		{
			if (cur->id == curStudent->id)
				break;
			cur = cur->pNext;
		}
		if (cur)
		{
			goToXY(x, ++y); cout << "Student's name: " << cur->fullname;
			goToXY(x, ++y); cout << "Student's ID: " << cur->id;
			goToXY(x, ++y); cout << "Student's class: " << cur->cla;
			prevStudent = curStudent;
			curStudent = curStudent->pNext;
		}
		else
		{
			curCourse->numStudent--;
			deleteStudent(prevStudent, curStudent, curCourse->pStudent);
		}
	}
	deleteStudentList(pStudent);
	y = y + 3;; goToXY(x, y++); system("pause");
	rewriteCourse(curCourse, dir + curCourse->courseID + ".txt");
}
void viewCheckInResult(Student* curStudent, Semester* pSemester) 
{
	system("cls");
	resizeConsole(1200, 700);
	int x = 10, y = 5;
	goToXY(x, y++); cout << "Your check in:"; 
	x = 8;
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
					int numDay = 10;
					Date date = curCourse->dateStart;
					goToXY(x, ++y); cout << curCourse->courseID;
					for (int i = 0; i < 10; i++)
					{
						goToXY(x + 38 + i * 10, y);
						if (cmpDate(date, curCourse->dateEnd) == 1)
						{
							numDay = i;
							break;
						}
						printDate(date.day); cout << '/'; printDate(date.month); cout << '/'; printDate(date.year % 100);
						nextWeek(date);
					}
					goToXY(x, ++y); cout << curCourse->courseName;
					for (int i = 0; i < numDay; ++i) 
					{
						goToXY(x + 41 + i * 10, y);
						cout << curStudentCourse->attend[i];
					}
				}
				curCourse = curCourse->pNext;
			}
			curSchedule = curSchedule->pNext;
		}
		curSemester = curSemester->pNext;
	}
	y++;
	goToXY(x, ++y); system("pause");
	resizeConsole(1000, 700);
}
void viewSchedule(Student* curStudent, Semester* pSemester) {
	system("cls");
	int x = 10, y = 5;
	goToXY(x, y++); cout << "Here is your schedule:";
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
				Date curDate; 
				Time curTime;
				getCurrentTime(curDate, curTime);
				if ((curStudentCourse) && (cmpDate(curCourse->dateStart, curDate) <= 0) && (cmpDate(curDate, curCourse->dateEnd) <= 0))
				{
					y++;
					goToXY(x, y++); cout << curCourse->courseID << " - " << curCourse->courseName;
					goToXY(x, y++); cout << "Class     : " << curCourse->cla;
					goToXY(x, y++); cout << "Lecturer  : " << curCourse->lecturer.fullname;
					goToXY(x, y++); cout << "Day       : " << curCourse->day << endl;
					goToXY(x, y++); cout << "Time      : ";
					cout << curCourse->timeStart.hour << ':' << curCourse->timeStart.minute << " - "
						 << curCourse->timeEnd.hour << ':' << curCourse->timeEnd.minute << endl;
				}
				curCourse = curCourse->pNext;
			}
			curSchedule = curSchedule->pNext;
		}
		curSemester = curSemester->pNext;
	}
	goToXY(x, ++y); system("pause");
}
void student_view_score(Student* curStudent, Semester* pSemester) 
{
	system("cls");
	int x = 10, y = 5;
	goToXY(x, y++); cout << "Here is your schedule:"; y++;
	Semester* curSemester = pSemester;
	goToXY(x + 40, y); cout << "Midterm";
	goToXY(x + 51, y); cout << "Final";
	goToXY(x + 61, y); cout << "Bonus";
	goToXY(x + 71, y); cout << "Total";
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
					goToXY(x, ++y); cout << curCourse->courseID;
					goToXY(x, ++y); cout << curCourse->courseName;
					goToXY(x + 43, y); cout << curStudentCourse->grade.midterm;
					goToXY(x + 53, y); cout << curStudentCourse->grade.total;
					goToXY(x + 63, y); cout << curStudentCourse->grade.final;
					goToXY(x + 73, y); cout << curStudentCourse->grade.bonus;
				}
				curCourse = curCourse->pNext;
			}
			curSchedule = curSchedule->pNext;
		}
		curSemester = curSemester->pNext;
	}
	y++;
	goToXY(x, ++y); system("pause");
}