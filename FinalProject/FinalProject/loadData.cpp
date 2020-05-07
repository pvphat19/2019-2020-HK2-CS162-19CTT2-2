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
				in >> cur->id; in.get();
				getline(in, cur->password);
				getline(in, cur->fullname);
				in >> cur->dob.year >> cur->dob.month >> cur->dob.day;
				in >> cur->cla;
				in >> cur->status;
				cur->pNext = nullptr;
			}
			else
			{
				cur->pNext = new Student;
				cur = cur->pNext;
				in >> cur->id; in.get();
				getline(in, cur->password);
				getline(in, cur->fullname);
				in >> cur->dob.year >> cur->dob.month >> cur->dob.day;
				in >> cur->cla;
				in >> cur->status;
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