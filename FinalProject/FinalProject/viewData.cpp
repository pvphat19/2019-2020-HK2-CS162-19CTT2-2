#include "function.h"

#include "function.h"

string maleFemale(int gender)
{
	if (gender)
		return "female";
	else
		return "male";
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
	goToXY(x, y++); cout << "Your Profile Information" << endl;
	goToXY(x, y++); cout << "User name: " << curStaff->username << endl;
	goToXY(x, y++); cout << "Full name: " << curStaff->fullname << endl;
	goToXY(x, y++); cout << "Gender: " << maleFemale(curStaff->gender) << endl;
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

bool inputCourse(int& x, int& y, Semester* pSemester, Course*& curCourse, string& directory)
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
		goToXY(x, y++); cout << "Choose the course you want to view the attendance list"; y++;	//Changes depend on the purpose  
		bool check = inputCourse(x, y, pSemester, curCourse, dir);
		if (curCourse)	break;
		if (check)	viewCourseAttendance(pSemester);	//Change to the name of the current function
		return;
	}
	goToXY(x, y++); cout << "Directory: " << dir << endl;	//Test purpose
	//function process part
	//For Ex: View attendance list	
	Student* curStudent = curCourse->pStudent;
	for (int i = 0; i < 10; i++)
	{
		goToXY(x + 25 + i * 8, y);
		cout << i + 1;
	}
	while (curStudent)
	{
		goToXY(x, ++y); cout << curStudent->id;
		goToXY(x, ++y);
		for (int i = 0; i < 10; i++)
		{
			goToXY(x + 25 + i * 8, y);
			cout << curStudent->attend[i];
		}
		curStudent = curStudent->pNext;
	}
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
				goToXY(x + 3, y++); cout << "There is no information in stored data." << endl;
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

bool inputCourse(int& x, int& y, Semester* pSemester, Course*& curCourse, string& directory)
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