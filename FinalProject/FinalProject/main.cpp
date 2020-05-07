#include "function.h"

int main()
{
	Student* pStudent = nullptr;
	Class* pClass = nullptr;
	loadStudent(pStudent, "Student.txt");
	loadClass(pClass);
	deleteStudentList(pStudent);
	deleteClassList(pClass);
	return 0;
}