#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
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
void loadStudent(Student*&, string);
void loadClass(Class*&);
void loadStaff(Staff*&);
void loadLecturer(Lecturer*&);
void deleteStudentList(Student*&);
void deleteClassList(Class*&);
void deleteStaffList(Staff*&);
void deleteLecturerList(Lecturer*&);

//consoleEdit
void resizeConsole(int width, int height);	// Ham thay doi kich co cua khung cmd 
void textColor(int x);	// Ham to mau chu
void goToXY(int x, int y);	// Ham dich chuyen con tro den toa do x, y
void fixConsoleWindow(); // Ham co dinh console
/* system("cls")	// Ham xoa man hinh
// system("pause")	// Ham pause cho den khi nhan 1 phim bat ki	*/

//staffClass
void viewClass(Class*&);
void viewStudentsInClass(Student* pStudent, string name);
#endif // !_FUNCTION_H_

