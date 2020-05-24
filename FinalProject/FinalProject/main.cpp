#include "function.h"

int main()
{
	resizeConsole(1200, 720);
	fixConsoleWindow();
	int numSemester = 0;
	Semester* pSemester = nullptr;
	loadSemester(numSemester, pSemester);
	removeStudentfromCourse(numSemester, pSemester);
	//login();
	//rewriteScheduleList(pSemester->numSchedule, pSemester->pSchedule, "Semester\\2018-2019-HK2\\2018-2019-HK2.txt");
	//rewriteCourseList(pSemester->pSchedule->numCourse, pSemester->pSchedule->pCourse, "Semester\\2018-2019-HK2\\19APCS1\\19APCS1.txt");
	//rewriteCourse(pSemester->pSchedule->pCourse, "Semester\\2018-2019-HK2\\19APCS1\\CS162.txt");

	deleteSemesterList(pSemester);
	return 0;
}