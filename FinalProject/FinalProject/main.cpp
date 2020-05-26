#include "function.h"

int main()
{
	resizeConsole(1100, 700);
	fixConsoleWindow();

	int numSemester;
	Semester* pSemester = nullptr;
	loadSemester(numSemester, pSemester);
	//viewStudentInCourse(pSemester);
	viewCourseAttendance(pSemester);
	//viewCourseScoreboard(pSemester);
	//viewStudentInCourse(pSemester);
	//viewCourseAttendance(pSemester);
	//viewCourseScoreboard(pSemester);
	deleteSemesterList(pSemester);
	//login();
	//viewCourseAttendance(pSemester);
	//removeStudentfromCourse(numSemester, pSemester);
	
	return 0;
}