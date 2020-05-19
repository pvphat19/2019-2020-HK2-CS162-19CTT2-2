#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <string>
using namespace std;

struct Date {
	int day;
	int month;
	int year;
};
struct Time {
	int hour;
	int minute;
};
struct Grade {
	double bonus;
	double midterm;
	double final;
	double total;
};
struct Student {
	int id;
	string password;
	string fullname;
	Date dob;
	string cla; //class
	int status; //0:inactive; 1:active;
	Grade grade;
	bool attend[10];
	Student* pNext;
};
struct Class {
	string name;
	int numStudent;
	Student* pStudent;
	Class* pNext;
};
struct Staff {
	string username;
	string password;
	string fullname;
	int gender; //0:male; 1:female;
	Staff* pNext;
};
struct Lecturer {
	string username;
	string password;
	string fullname;
	string degree;
	int gender; //0:male; 1:female;
	Lecturer* pNext;
};
struct Course {
	string courseID;
	string courseName;
	string cla;
	Lecturer lecturer;
	string day;
	string room;
	Date dateStart;
	Date dateEnd;
	Time timeStart;
	Time timeEnd;
	int numStudent;
	Student* pStudent;
	Course* pNext;
};
struct Schedule {
	string cla; //class
	int numCourse;
	Course* pCourse;
	Schedule* pNext;
};
struct Semester {
	string academicYear;	//2018-2019
	string semester;	//HK2
	int numSchedule;
	Schedule* pSchedule;
	Semester* pNext;
};
//loadData
void loadStudent(int&, Student*&, string name);
void loadClass(int&, Class*&);
void loadStaff(int&, Staff*&);
void loadLecturer(int&, Lecturer*&);
void loadSemester(int&, Semester*&);
void loadSchedule(int&, Schedule*&, string dir, string name);
void loadCourse(Course*, string dir, string name);
void loadCourseList(int&, Course*&, string dir, string name);

//deleteData
void deleteStudentList(Student*&);
void deleteClassList(Class*&);
void deleteStaffList(Staff*&);
void deleteLecturerList(Lecturer*&);
void deleteSemesterList(Semester*&);
void deleteScheduleList(Schedule*&);
void deleteCourseList(Course*&);

//rewriteTextFile
void rewriteStudent(int, Student*, string);
void rewriteClass(int, Class*);
void rewriteStaff(int, Staff*);
void rewriteLecturer(int, Lecturer*);
void rewriteSemester(int, Semester*);
void rewriteScheduleList(int, Schedule*, string filename);
void rewriteCourseList(int, Course* pCourse, string filename);
void rewriteCourse(Course* curCourse, string filename);

//consoleEdit
void resizeConsole(int width, int height);	// Ham thay doi kich co cua khung cmd 
void textColor(int x);	// Ham to mau chu
void goToXY(int x, int y);	// Ham dich chuyen con tro den toa do x, y
void fixConsoleWindow(); // Ham co dinh console
/* system("cls")	// Ham xoa man hinh
// system("pause")	// Ham pause cho den khi nhan 1 phim bat ki	*/

//checkUser
bool isStaff(string username, string password, Staff*& curStaff);

//systemMenu
void printHCMUS(int x, int y);
void staffMenu(Staff*& curStaff);
void login();

//viewData
void viewClass();
void viewStudentsInClass();

//ModificationClass
void removeStudents();
void ChangeStudentsInfo();
void ChangeStudentsClass();

//manually add and import class
void manually_add_student_to_class();
void import_class();
#endif // !_FUNCTION_H_

