#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <direct.h>
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
	int attend[10];
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
void deleteStudent(Student* prev, Student*& cur, Student*& pHead);
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

//systemMenu
bool convertStringToInt(string, int&);
void login();

//viewData
bool inputCourse(int& x, int& y, Semester* pSemester, Course*& curCourse, string& directory);
void viewCurLecturerInfo(Lecturer* curLecturer);
void viewCurStaffInfo(Staff* curStaff);
void viewCurStudentInfo(Student* curStudent);
void viewCourseAttendance(Semester*);
void viewCourseScoreboard(Semester*);
void viewLecturer();
void viewClass();
void viewStudentsInClass();
void viewStudentInCourse(Semester*& pSemester);
void viewCourse(Semester*& pSemester);

//ModificationClass
void removeStudents();
void ChangeStudentsInfo();
void ChangeStudentsClass();

//manually add and import class
void manually_add_student_to_class();
void import_class();

//CourseMod
void editCourse(int numSemester, Semester* pSemester);
void removeCourse(int numSemester, Semester* pSemester);
void removeStudentfromCourse(int numSemester, Semester* pSemester);

//modifyFunction
bool convertStringToInt(string str, int& x);
void inputDate(int& result, int& result2, int& result3);
bool cmpDate(Date& date1, Date& date2);
void nextWeek(Date& date, int n);
void sortStudentList(Student*& pStudent);
void nextWeek(Date& date, int n);
bool isLunarYear(int year);
void printDate(int x);

//academic
void createSemester(string AcademicYear, string Semestername, int& numSemester, Semester*& pSemester);
void createAcademicYear(int& numSemester, Semester*& pSemester);
void importCourse(int& numSemester, Semester*& pSemester);
void manuallyAddCourse(int& numSemester, Semester*& pSemester);
void importScoreboard(int& numSemester, Semester*& pSemester);
void exportAttendanceList(Semester* pSemester);

#endif // !_FUNCTION_H_

