#include "function.h"

int main()
{
	resizeConsole(1200, 720);
	fixConsoleWindow();
	Student* pStudent = nullptr;
	Class* pClass = nullptr;
	Staff* pStaff = nullptr;
	Lecturer* pLecturer = nullptr;
	loadStudent(pStudent, "Student");
	loadClass(pClass);
	loadStaff(pStaff);
	loadLecturer(pLecturer);
	deleteStudentList(pStudent);
	deleteClassList(pClass);
	deleteStaffList(pStaff);
	deleteLecturerList(pLecturer);
	return 0;
}