#include "function.h"

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
	Class* cur = pClass;
	loadClass(numClass, pClass);

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
	int numSemester;

	string year, term;


	// User enters selection
	cout << "Please enter the academic year you need (Example:2018-2019): ";
	cin >> year;
	cout << "Please enter the semester you need (Example: HK2): ";
	cin >> term;

	Semester* cur = pSemester;
	while (cur != nullptr) {
		if (year == cur->academicYear && term == cur->semester) {
			cout << "Here is the course list of each class" << endl;
			while (cur->pSchedule != nullptr) {
				int i = 1;
				cout << i << ". " << cur->pSchedule->cla << ": " << endl;
				cout << "   - " << cur->pSchedule->pCourse->courseName << " - " << cur->pSchedule->pCourse->courseID << endl;
				cur->pSchedule = cur->pSchedule->pNext;
			}
			break;
		}
		cur = cur->pNext;
	}
	deleteSemesterList(pSemester);
}