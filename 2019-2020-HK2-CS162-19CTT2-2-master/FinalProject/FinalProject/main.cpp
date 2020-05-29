#include "function.h"

int main()
{
	resizeConsole(1000, 700);
	fixConsoleWindow();

	int numSemester;
	Semester* pSemester = nullptr;
	loadSemester(numSemester, pSemester);
	deleteSemesterList(pSemester);
	login();
	return 0;
}

