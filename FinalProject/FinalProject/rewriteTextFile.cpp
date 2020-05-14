#include "function.h"

void printDate(ofstream& out, int x)
{
	if (x < 10)
		out << 0 << x;
	else
		out << x;
}
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
		out << cur->dob.year << ' '; 
		printDate(out, cur->dob.month);
		out << ' ';
		printDate(out, cur->dob.day);
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