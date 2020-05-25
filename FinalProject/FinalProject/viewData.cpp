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
void nextWeek(Date& date, int n)
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
	if (n != 0)
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
bool cmpDate(Date& date1, Date& date2)
{
	if (date1.year > date2.year)
		return true;
	if (date1.year < date2.year)
		return false;
	if (date1.month > date2.month)
		return true;
	if (date1.month < date2.month)
		return false;
	if (date1.day > date2.day)
		return true;
	if (date1.day < date2.day)
		return false;
	return false;
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
	goToXY(x, y++); cout << "Enter class name: "; getline(cin, cla);
	Schedule* curSchedule = curSemester->pSchedule;
	while (curSchedule)
	{
		if (curSchedule->cla == cla)
			break;
		curSchedule = curSchedule->pNext;
	}
	if (curSchedule == nullptr)
	{
		y++;
		int choice;
		textColor(4);
		goToXY(x, y++); cout << "Invalid class! Do you want to try again (Yes(1) / No(0))?";
		goToXY(x, y++); cout << "Enter your choice: "; cin >> choice; cin.get();
		textColor(15);
		return choice;
	}
	//Course
	dir = dir + cla + "\\";
	goToXY(x, y++); cout << "Enter course Id: "; getline(cin, courseId);
	curCourse = curSchedule->pCourse;
	while (curCourse)
	{
		if (curCourse->courseID == courseId)
			break;
		curCourse = curCourse->pNext;
	}
	if (curCourse == nullptr)
	{
		y++;
		int choice;
		textColor(4);
		goToXY(x, y++); cout << "Invalid course Id! Do you want to try again (Yes(1) / No(0))?";
		goToXY(x, y++); cout << "Enter your choice: "; cin >> choice; cin.get();
		textColor(15);
		return choice;
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

	int numStudent;
	Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	resizeConsole(1100, 700);
	y++; goToXY(x+40, y++); cout << "Attendance list of the course" << endl; y++;
	int numDay = 10;
	Date date = curCourse->dateStart;
	for (int i = 0; i < 10; i++)
	{
		goToXY(x + 23 + i * 10, y);
		nextWeek(date, i);
		if (cmpDate(date, curCourse->dateEnd))
		{
			numDay = i;
			break;
		}
		printDate(date.day); cout << '/'; printDate(date.month); cout << '/'; printDate(date.year % 100);
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
	goToXY(x, y++); system("pause");
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
	goToXY(x + 35, y); cout << "Final";
	goToXY(x + 45, y); cout << "Bonus";
	goToXY(x + 55, y); cout << "Total";
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
			goToXY(x + 25, y); cout << curStudent->grade.midterm;
			goToXY(x + 35, y); cout << curStudent->grade.total;
			goToXY(x + 45, y); cout << curStudent->grade.final;
			goToXY(x + 55, y); cout << curStudent->grade.bonus;
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
	goToXY(x, y++); system("pause");
	rewriteCourse(curCourse, dir + curCourse->courseID + ".txt");
	deleteStudentList(pStudent);
}
void viewClass() {
	system("cls");
	int numClass;
	Class* pClass = nullptr;
	loadClass(numClass, pClass);
	if (pClass == nullptr) {
		cout << "There is no class in stored data" << endl;
	}
	else {
		Class* cur = pClass;
		int i = 1;
		cout << "Here is the list of class:" << endl;
		while (cur != nullptr) {
			cout << i << ". " << cur->name << endl;
			cur = cur->pNext;
			++i;
		}
	}
	deleteClassList(pClass);
}
void viewStudentsInClass() {
	Class* pClass = nullptr;
	int numClass;
	loadClass(numClass, pClass);
	Class* cur = pClass;

	// View Selection
	cout << "Choose the class you want to view students list: " << endl;
	int i = 0;
	while (cur != nullptr) {
		cout << i + 1 << ". " << cur->name << endl;
		cur = cur->pNext;
		++i;
	}

	cur = pClass;
	int count = 1;
	int choice;

	cout << "Your Choice is: ";
	cin >> choice;

	while (cur != nullptr) {
		if (count == choice) {
			if (cur->pStudent == nullptr)
			{
				cout << "There is no information in stored data." << endl;
				break;
			}
			while (cur->pStudent != nullptr) {
				cout << cur->pStudent->fullname << " - " << cur->pStudent->id << endl;
				cur->pStudent = cur->pStudent->pNext;
			}
			break;
		}
		else {
			++count;
			cur = cur->pNext;
		}
	}
	deleteClassList(pClass);
}
void viewCourse(Semester*& pSemester) {
	string year, term;

	// User enters selection
	cout << "Please enter the academic year you need (Example: 2018-2019): ";
	cin >> year;
	cout << "Please enter the semester you need (Example: HK2): ";
	cin >> term;

	Semester* cur = pSemester;
	while (cur != nullptr) {
		if (year == cur->academicYear && term == cur->semester) {
			if (cur->pSchedule == nullptr) {
				cout << "There is no information in stored data." << endl;
				break;
			}
			cout << "Here is the course list of each class" << endl;
			while (cur->pSchedule != nullptr) {
				int i = 1;
				cout << i << ". " << cur->pSchedule->cla << ": " << endl;
				while (cur->pSchedule->pCourse != nullptr) {
					cout << "   - " << cur->pSchedule->pCourse->courseName << " - " << cur->pSchedule->pCourse->courseID << endl; // Print out course's name and course's id
					cur->pSchedule->pCourse = cur->pSchedule->pCourse->pNext; // move to next course
				}
				cur->pSchedule = cur->pSchedule->pNext; // move to next schedule
				++i;
			}
			break;
		}
		cur = cur->pNext;
	}
}
void viewStudentInCourse(Semester*& pSemester) {
	Semester* curSemester = pSemester;
	Schedule* curSchedule = pSemester->pSchedule;
	string year, term;

	// Users choose academic year and semester
	cout << "Please enter the academic year you need (Example: 2018-2019): ";
	cin >> year;
	cout << "Please enter the semester you need (Example: HK2): ";
	cin >> term;

	// Users choose a semester
	while (curSemester != nullptr) {

		// If the user's input matches the node
		if (year == curSemester->academicYear && term == curSemester->semester) {

			//User chooses a schedule
			cout << "Please choose the class in which is the course you need" << endl;
			cout << "Here is the list of class:" << endl;
			while (curSchedule != nullptr) {
				int i = 1;
				cout << i << ". " << curSchedule->cla << endl; // Print out list of class
				curSchedule = curSchedule->pNext; // move to next schedule
				++i;
			}

			curSchedule = pSemester->pSchedule; // Set the curSemester->pSchedule to head of the schedule list
			int iSchedule = 1;
			int classChoice;

			cout << "Your choice is: "; // User's input
			cin >> classChoice;

			Course* curCourse = pSemester->pSchedule->pCourse;
			while (curSchedule != nullptr) {

				// if the schedule node matches the user's choice
				if (iSchedule == classChoice) {

					// If there is no course in data
					if (curCourse == nullptr) {
						cout << "There is no information in stored data." << endl;
						break;
					}

					// else
					else {
						// Users choose a course
						cout << "Please choose the course in which you need to view information of students" << endl;
						cout << "Here is the list of courses:" << endl;
						while (curCourse != nullptr) {
							// Print out the list of courses
							int i = 1;
							cout << i << ". " << curCourse->courseName << " - " << curCourse->courseID << endl;
							curCourse = curCourse->pNext;
						}

						curCourse = pSemester->pSchedule->pCourse; // Set the curSemester->pSchedule->pCourse to head of the course list
						int iCourse = 1;
						int courseChoice;

						cout << "Your choice is: ";
						cin >> courseChoice;

						int numStudent;
						Student* pStudent = nullptr;
						loadStudent(numStudent, pStudent, "Student");

						Student* curStudent = pSemester->pSchedule->pCourse->pStudent;
						while (curCourse != nullptr) {

							// If the course node matches the user's input
							if (iCourse == courseChoice) {
								int count = 1;
								Student* cur = pStudent;

								// Evaluate the first student on the list
								while (curStudent == pSemester->pSchedule->pCourse->pStudent) {
									while (cur != nullptr) {
										if (cur->id == curStudent->id) {
											cout << cur->fullname << endl;
											cout << cur->id << endl;
											cout << cur->cla << endl;
											curStudent = curStudent->pNext;
											break;
										}
										else {
											++count;
											cur = cur->pNext;
										}
									}
									if (count == numStudent) {
										cout << "There is no information about student with ID " << curStudent->id << " in stored data" << endl;
										Student* temp = curStudent;
										curStudent = curStudent->pNext;
										delete temp;
									}
								}

								// Evaluate from 2nd student on the list
								Student* prevStudent = pSemester->pSchedule->pCourse->pStudent;
								while (curStudent != nullptr) {
									cur = pStudent;
									while (cur != nullptr) {
										if (cur->id == curStudent->id) {
											cout << cur->fullname << endl;
											cout << cur->id << endl;
											cout << cur->cla << endl;
											curStudent = curStudent->pNext;
											prevStudent = prevStudent->pNext;
											break;
										}
										else {
											++count;
											cur = cur->pNext;
										}
									}
									if (count == numStudent) {
										cout << "There is no information about student with ID " << curStudent->id << " in stored data" << endl;
										Student* temp = curStudent;
										curStudent = curStudent->pNext;
										prevStudent->pNext = curStudent;
										delete temp;
									}
								}
							}

							//else
							++iCourse;
							curCourse = curCourse->pNext;
						}
						break;
					}
				}

				// else
				++iSchedule;
				curSchedule = curSchedule->pNext;
			}
			break;
		}

		// else
		curSemester = curSemester->pNext;
	}
}