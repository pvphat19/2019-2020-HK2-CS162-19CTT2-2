#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <iostream>
#include <fstream>
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
void loadStudent(Student*&, string);
void loadClass(Class*&);
void loadStaff(Staff*&);
void loadLecturer(Lecturer*&);
void deleteStudentList(Student*&);
void deleteClassList(Class*&);
void deleteStaffList(Staff*&);
void deleteLecturerList(Lecturer*&);
void viewClass(Class*&);
#endif // !_FUNCTION_H_

