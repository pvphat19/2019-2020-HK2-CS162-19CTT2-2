#ifndef _FUNCTION_H_
#define _FUNCTION_H_

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
struct Student {

	int id;
	string password;
	string fullname;
	Date dob;
	string cla; //class
	int status; //0:inactive; 1:active;
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
//loadData
bool loadStudent(int&, Student*&, string);
void loadClass(int&, Class*&);
void loadStaff(int&, Staff*&);
void loadLecturer(int&, Lecturer*&);
void deleteStudentList(Student*&);
void deleteClassList(Class*&);
void deleteStaffList(Staff*&);
void deleteLecturerList(Lecturer*&);

//rewriteTextFile
void printDate(ofstream&, int);
void rewriteStudent(int, Student*, string);
void rewriteClass(int, Class*);
void rewriteStaff(int, Staff*);
void rewriteLecturer(int, Lecturer*);

//consoleEdit
void resizeConsole(int width, int height);	// Ham thay doi kich co cua khung cmd 
void textColor(int x);	// Ham to mau chu
void goToXY(int x, int y);	// Ham dich chuyen con tro den toa do x, y
void fixConsoleWindow(); // Ham co dinh console
/* system("cls")	// Ham xoa man hinh
// system("pause")	// Ham pause cho den khi nhan 1 phim bat ki	*/

//staffClass
void viewClass(Class*&);
void viewStudentsInClass(Class* pClass, string name);
//ModificationClass
void removeStudents(int numStudent, Student*& pStudent);
void ChangeStudentsInfo(int numStudent, Student*& pStudent);
void ChangeStudentsClass(int numStudent, Student*& pStudent);
#endif // !_FUNCTION_H_

