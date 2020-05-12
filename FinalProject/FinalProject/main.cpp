#include "function.h"

int main()
{
	Student* pStudent = nullptr;
	Class* pClass = nullptr;
	Staff* pStaff = nullptr;
	Lecturer* pLecturer = nullptr;
	loadStudent(pStudent, "Student");
	loadClass(pClass);
	viewClass(pClass);
	loadStaff(pStaff);
	loadLecturer(pLecturer);
	deleteStudentList(pStudent);
	deleteClassList(pClass);
	deleteStaffList(pStaff);
	deleteLecturerList(pLecturer);
	return 0;
}