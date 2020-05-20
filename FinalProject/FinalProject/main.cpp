#include "function.h"

int main()
{
	resizeConsole(1200, 720);
	fixConsoleWindow();
	int numStudent, numClass, numStaff, numLecturer;
	Student* pStudent = nullptr;
	Class* pClass = nullptr;
	Staff* pStaff = nullptr;
	Lecturer* pLecturer = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	loadClass(numClass, pClass);
	loadStaff(numStaff, pStaff);
	loadLecturer(numLecturer, pLecturer);
	viewClass();
	viewStudentsInClass();
	deleteStudentList(pStudent);
	deleteClassList(pClass);
	deleteStaffList(pStaff);
	deleteLecturerList(pLecturer);
	return 0;
}