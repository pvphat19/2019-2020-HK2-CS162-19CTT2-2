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
void loadStudent(Student*&, string);
void loadClass(Class*&);
void deleteStudentList(Student*&);
void deleteClassList(Class*&);
#endif // !_FUNCTION_H_

