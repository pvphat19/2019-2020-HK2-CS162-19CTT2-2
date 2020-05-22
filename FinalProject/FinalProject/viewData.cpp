#include "function.h"

string maleFemale(int gender)
{
	if (gender)
		return "female";
	else
		return "male";
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

	cout << "Choice: ";
	cin >> choice;

	while (cur != nullptr) {
		if (count == choice) {
			cout << cur->pStudent->fullname << " - " << cur->pStudent->id << endl;
			cur->pStudent = cur->pStudent->pNext;
			if (cur->pStudent == nullptr) break;
		}
		else {
			++count;
			cur = cur->pNext;
		}
	}
	deleteClassList(pClass);
}