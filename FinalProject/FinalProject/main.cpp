#include "function.h"

int main()
{
	resizeConsole(1000, 700);
	fixConsoleWindow();
	int numSemester = 0;
	Semester* pSemester = nullptr;
	loadSemester(numSemester, pSemester);

	viewCourseAttendance(pSemester);
	//login(numSemester, pSemester);
	//manually_add_student_to_class();
	//rewriteScheduleList(pSemester->numSchedule, pSemester->pSchedule, "Semester\\2018-2019-HK2\\2018-2019-HK2.txt");
	//rewriteCourseList(pSemester->pSchedule->numCourse, pSemester->pSchedule->pCourse, "Semester\\2018-2019-HK2\\19APCS1\\19APCS1.txt");
	//rewriteCourse(pSemester->pSchedule->pCourse, "Semester\\2018-2019-HK2\\19APCS1\\CS162.txt");
	//viewStudentsInClass();
	deleteSemesterList(pSemester);
	return 0;
}