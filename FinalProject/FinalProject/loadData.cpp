#include "function.h"

void loadStudent(Student*& pStudent, string name)
{
	ifstream in;
	string fileName = name + ".txt";
	in.open(fileName);
	int n;
	Student* cur = nullptr;
	if (in >> n)
	{
		for (int i = 0; i < n; i++)
		{
			if (pStudent == nullptr)
			{
				pStudent = new Student;
				cur = pStudent;
				in >> cur->id; 
				in.ignore();
				getline(in, cur->password);
				getline(in, cur->fullname);
				in >> cur->dob.year >> cur->dob.month >> cur->dob.day;
				in.ignore();
				getline(in, cur->cla);
				in >> cur->status;
				cur->pNext = nullptr;
			}
			else
			{
				cur->pNext = new Student;
				cur = cur->pNext;
				in >> cur->id;
				in.ignore();
				getline(in, cur->password);
				getline(in, cur->fullname);
				in >> cur->dob.year >> cur->dob.month >> cur->dob.day;
				in.ignore();
				getline(in, cur->cla);
				cur->pNext = nullptr;
			}
		}
	}
	in.close();
}
void loadClass(Class*& pClass)
{
	ifstream in;
	in.open("Class.txt");
	int n;
	Class* cur = nullptr;
	in >> n; 
	in.get();
	for (int i = 0; i < n; i++)
	{
		if (pClass == nullptr)
		{
			pClass = new Class;
			cur = pClass;
			getline(in, cur->name);
			cur->pStudent = nullptr;
			loadStudent(cur->pStudent, cur->name);
			cur->pNext = nullptr;
		}
		else
		{
			cur->pNext = new Class;
			cur = cur->pNext;
			getline(in, cur->name);
			cur->pStudent = nullptr;
			loadStudent(cur->pStudent, cur->name);
			cur->pNext = nullptr;
		}
	}
	in.close();
}
void loadStaff(Staff*& pStaff)
{
	ifstream in;
	in.open("Staff.txt");
	int n;
	Staff* cur = nullptr;
	string emptyLine;
	if (in >> n)
	{
		for (int i = 0; i < n; i++)
		{
			if (pStaff == nullptr)
			{
				pStaff = new Staff;
				cur = pStaff;
				in.ignore();
				getline(in, cur->username);
				getline(in, cur->password);
				getline(in, cur->fullname);
				in >> cur->gender;
				cur->pNext = nullptr;
			}
			else
			{
				cur->pNext = new Staff;
				cur = cur->pNext;
				in.ignore();
				getline(in, emptyLine);
				getline(in, cur->username);
				getline(in, cur->password);
				getline(in, cur->fullname);
				in >> cur->gender;
				cur->pNext = nullptr;
			}
		}
	}
	in.close();
}
void loadLecturer(Lecturer*& pLecturer)
{
	ifstream in;
	in.open("Lecturer.txt");
	int n;
	Lecturer* cur = nullptr;
	string emptyLine;
	if (in >> n)
	{
		for (int i = 0; i < n; i++)
		{
			if (pLecturer == nullptr)
			{
				pLecturer = new Lecturer;
				cur = pLecturer;
				in.ignore();
				getline(in, cur->username);
				getline(in, cur->password);
				getline(in, cur->fullname);
				getline(in, cur->degree);
				in >> cur->gender;
				cur->pNext = nullptr;
			}
			else
			{
				cur->pNext = new Lecturer;
				cur = cur->pNext;
				in.ignore();
				getline(in, emptyLine);
				getline(in, cur->username);
				getline(in, cur->password);
				getline(in, cur->fullname);
				getline(in, cur->degree);
				in >> cur->gender;
				cur->pNext = nullptr;
			}
		}
	}
	in.close();
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