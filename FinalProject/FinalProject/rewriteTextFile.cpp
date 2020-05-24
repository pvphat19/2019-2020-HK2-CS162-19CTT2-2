#include "function.h"

void rewriteStudent(int numStudent, Student* pStudent, string name)
{
	ofstream out;
	string fileName = name + ".txt";
	out.open(fileName);
	Student* cur = pStudent;
	out << numStudent << endl;
	while (cur)
	{
		out << cur->id << endl;
		out << cur->password << endl;
		out << cur->fullname << endl;
		out << cur->dob.year << ' ' << cur->dob.month << ' ' << cur->dob.day;
		out << endl;
		out << cur->cla << endl;
		out << cur->status << endl;
		out << endl;
		cur = cur->pNext;
	}
	out.close();
}
void rewriteClass(int numClass, Class* pClass)
{
	ofstream out;
	out.open("Class.txt");
	Class* cur = pClass;
	out << numClass << endl;
	while (cur)
	{
		out << cur->name << endl;
		cur = cur->pNext;
	}
	out.close();
}
void rewriteStaff(int numStaff, Staff* pStaff)
{
	ofstream out;
	out.open("Staff.txt");
	Staff* cur = pStaff;
	out << numStaff << endl;
	while (cur)
	{
		out << cur->username << endl;
		out << cur->password << endl;
		out << cur->fullname << endl;
		out << cur->gender << endl;
		out << endl;
		cur = cur->pNext;
	}
	out.close();
}
void rewriteLecturer(int numLecturer, Lecturer* pLecturer)
{
	ofstream out;
	out.open("Lecturer.txt");
	Lecturer* cur = pLecturer;
	out << numLecturer << endl;
	while (cur)
	{
		out << cur->username << endl;
		out << cur->password << endl;
		out << cur->fullname << endl;
		out << cur->degree << endl;
		out << cur->gender << endl;
		out << endl;
		cur = cur->pNext;
	}
	out.close();
}
void rewriteSemester(int numSemester, Semester* pSemester)
{
	ofstream out;
	string filename = "Semester\\Semester.txt";
	out.open(filename);
	Semester* cur = pSemester;
	out << numSemester << endl;
	while (cur)
	{
		out << cur->academicYear << endl;
		out << cur->semester << endl;
		out << endl;
		cur = cur->pNext;
	}
	out.close();
}
void rewriteScheduleList(int numSchedule, Schedule* pSchedule, string filename)
{
	ofstream out;
	out.open(filename);
	Schedule* cur = pSchedule;
	out << numSchedule << endl;
	while (cur)
	{
		out << cur->cla << endl;
		cur = cur->pNext;
	}
	out.close();
}
void rewriteCourseList(int numCourse, Course* pCourse, string filename)
{
	ofstream out;
	out.open(filename);
	Course* cur = pCourse;
	out << numCourse << endl;
	while (cur)
	{
		out << cur->courseID << endl;
		cur = cur->pNext;
	}
	out.close();
}
void rewriteCourse(Course* curCourse, string filename)
{
	ofstream out;
	out.open(filename);
	out << curCourse->courseID << endl;
	out << curCourse->courseName << endl;
	out << curCourse->cla << endl;
	out << curCourse->lecturer.username << endl;
	out << curCourse->lecturer.fullname << endl;
	out << curCourse->lecturer.degree << endl;
	out << curCourse->lecturer.gender << endl;
	out << curCourse->day << endl;
	out << curCourse->room << endl;
	out << curCourse->dateStart.year << ' ' << curCourse->dateStart.month << ' ' << curCourse->dateStart.day << endl;
	out << curCourse->dateEnd.year << ' ' << curCourse->dateEnd.month << ' ' << curCourse->dateEnd.day << endl;
	out << curCourse->timeStart.hour << ' ' << curCourse->timeStart.minute << ' '
		<< curCourse->timeEnd.hour << ' ' << curCourse->timeEnd.minute << endl;
	out << curCourse->numStudent << endl;
	Student* cur = curCourse->pStudent;
	while (cur)
	{
		out << cur->id << endl;
		out << cur->grade.midterm << ' ' << cur->grade.final << ' ' << cur->grade.bonus << ' ' << cur->grade.total << endl;
		for (int j = 0; j < 10; j++)
			out << cur->attend[j] << ' ';
		out << endl;
		cur = cur->pNext;
	}
	out.close();
}