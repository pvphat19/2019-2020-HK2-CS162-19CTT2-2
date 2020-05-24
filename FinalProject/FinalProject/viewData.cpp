#include "function.h"

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