#include "function.h"

void deleteStudent(Student* prev, Student*& cur, Student*& pHead)
{
	Student* tmp = cur;
	cur = cur->pNext;
	if (prev)
		prev->pNext = cur;
	else
		pHead = cur;
	delete tmp;
}
void deleteStudentList(Student*& pStudent)
{
	Student* tmp;
	while (pStudent)
	{
		tmp = pStudent;
		pStudent = pStudent->pNext;
		delete tmp;
	}
}
void deleteClassList(Class*& pClass)
{
	Class* tmp;
	while (pClass)
	{
		tmp = pClass;
		pClass = pClass->pNext;
		deleteStudentList(tmp->pStudent);
		delete tmp;
	}
}
void deleteStaffList(Staff*& pStaff)
{
	Staff* tmp;
	while (pStaff)
	{
		tmp = pStaff;
		pStaff = pStaff->pNext;
		delete tmp;
	}
}
void deleteLecturerList(Lecturer*& pLecturer)
{
	Lecturer* tmp;
	while (pLecturer)
	{
		tmp = pLecturer;
		pLecturer = pLecturer->pNext;
		delete tmp;
	}
}
void deleteSemesterList(Semester*& pSemester)
{
	Semester* tmp;
	while (pSemester)
	{
		tmp = pSemester;
		pSemester = pSemester->pNext;
		deleteScheduleList(tmp->pSchedule);
		delete tmp;
	}
}
void deleteScheduleList(Schedule*& pSchedule)
{
	Schedule* tmp;
	while (pSchedule)
	{
		tmp = pSchedule;
		pSchedule = pSchedule->pNext;
		deleteCourseList(tmp->pCourse);
		delete tmp;
	}
}
void deleteCourseList(Course*& pCourse)
{
	Course* tmp;
	while (pCourse)
	{
		tmp = pCourse;
		pCourse = pCourse->pNext;
		deleteStudentList(tmp->pStudent);
		delete tmp;
	}
}