#include "function.h"

void loadStudent(int& numStudent, Student*& pStudent, string name)
{
	ifstream in;
	string fileName = name + ".txt";
	in.open(fileName);
	if (in.is_open())
	{
		int n;
		Student* cur = nullptr;
		in >> n;
		numStudent = n;
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
				in >> cur->status;
				cur->pNext = nullptr;
			}
		}
	}
	else
	{
		numStudent = 0;
		pStudent = nullptr;
	}
	in.close();
}
void loadClass(int& numClass, Class*& pClass)
{
	ifstream in;
	in.open("Class.txt");
	if (in.is_open())
	{
		int n;
		Class* cur = nullptr;
		in >> n; in.get();
		numClass = n;
		for (int i = 0; i < n; i++)
		{
			if (pClass == nullptr)
			{
				pClass = new Class;
				cur = pClass;
				getline(in, cur->name);
				cur->pStudent = nullptr;
				loadStudent(cur->numStudent, cur->pStudent, cur->name);
				cur->pNext = nullptr;
			}
			else
			{
				cur->pNext = new Class;
				cur = cur->pNext;
				getline(in, cur->name);
				cur->pStudent = nullptr;
				loadStudent(cur->numStudent, cur->pStudent, cur->name);
				cur->pNext = nullptr;
			}
		}
	}
	else
	{
		numClass = 0;
		pClass = nullptr;
	}
	in.close();
}
void loadStaff(int& numStaff, Staff*& pStaff)
{
	ifstream in;
	in.open("Staff.txt");
	if (in.is_open())
	{
		int n;
		Staff* cur = nullptr;
		string emptyLine;
		if (in >> n)
		{
			numStaff = n;
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
	}
	else
	{
		numStaff = 0;
		pStaff = nullptr;
	}
	in.close();
}
void loadLecturer(int& numLecturer, Lecturer*& pLecturer)
{
	ifstream in;
	in.open("Lecturer.txt");
	if (in.is_open())
	{
		int n;
		Lecturer* cur = nullptr;
		string emptyLine;
		if (in >> n)
		{
			numLecturer = n;
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
	}
	else
	{
		numLecturer = 0;
		pLecturer = nullptr;
	}
	in.close();
}
void loadSemester(int& numSemester, Semester*& pSemester)
{
	ifstream in;
	string filename = "Semester\\Semester.txt";
	in.open(filename);
	if (in.is_open())
	{
		int n;
		in >> n; in.get();
		numSemester = n;
		Semester* cur = nullptr;
		string emptyLine;
		for (int i = 0; i < n; i++)
		{
			if (pSemester == nullptr)
			{
				pSemester = new Semester;
				cur = pSemester;
				getline(in, cur->academicYear);
				getline(in, cur->semester);
				cur->pSchedule = nullptr;
				string name = cur->academicYear + '-' + cur->semester;
				loadSchedule(cur->numSchedule, cur->pSchedule, "Semester\\" + name + "\\", name);
				getline(in, emptyLine);
				cur->pNext = nullptr;
			}
			else
			{
				cur->pNext = new Semester;
				cur = cur->pNext;
				getline(in, cur->academicYear);
				getline(in, cur->semester);
				cur->pSchedule = nullptr;
				string name = cur->academicYear + '-' + cur->semester;
				loadSchedule(cur->numSchedule, cur->pSchedule, "Semester\\" + name + "\\", name);
				getline(in, emptyLine);
				cur->pNext = nullptr;
			}
		}
	}
	else
	{
		numSemester = 0;
		pSemester = nullptr;
	}
	in.close();
}
void loadSchedule(int& numSchedule, Schedule*& pSchedule, string dir, string name)
{
	ifstream in;
	string filename = dir + name + ".txt";
	in.open(filename);
	if (in.is_open())
	{
		int n;
		in >> n; in.get();
		numSchedule = n;
		Schedule* cur = nullptr;
		for (int i = 0; i < n; i++)
		{
			if (pSchedule == nullptr)
			{
				pSchedule = new Schedule;
				cur = pSchedule;
				getline(in, cur->cla);
				cur->pCourse = nullptr;
				loadCourseList(cur->numCourse, cur->pCourse, dir + cur->cla + "\\", cur->cla);
				cur->pNext = nullptr;
			}
			else
			{
				cur->pNext = new Schedule;
				cur = cur->pNext;
				getline(in, cur->cla);
				cur->pCourse = nullptr;
				loadCourseList(cur->numCourse, cur->pCourse, dir + cur->cla + "\\", cur->cla);
				cur->pNext = nullptr;
			}
		}
	}
	else
	{
		numSchedule = 0;
		pSchedule = nullptr;
	}
	in.close();
}
void loadCourse(Course* curCourse, string dir, string name)
{
	ifstream in;
	string filename = dir + name + ".txt";
	in.open(filename);
	getline(in, curCourse->courseID);
	getline(in, curCourse->courseName);
	getline(in, curCourse->cla);
	getline(in, curCourse->lecturer.username);
	getline(in, curCourse->lecturer.fullname);
	getline(in, curCourse->lecturer.degree);
	in >> curCourse->lecturer.gender; in.get();
	getline(in, curCourse->day);
	getline(in, curCourse->room);
	in >> curCourse->dateStart.year >> curCourse->dateStart.month >> curCourse->dateStart.day;
	in >> curCourse->dateEnd.year >> curCourse->dateEnd.month >> curCourse->dateEnd.day;
	in >> curCourse->timeStart.hour >> curCourse->timeStart.minute >> curCourse->timeEnd.hour >> curCourse->timeEnd.minute;
	in >> curCourse->numStudent;
	Student* cur = nullptr;
	for (int i = 0; i < curCourse->numStudent; i++)
	{
		if (curCourse->pStudent == nullptr)
		{
			curCourse->pStudent = new Student;
			cur = curCourse->pStudent;
			in >> cur->id;
			in >> cur->grade.midterm >> cur->grade.final >> cur->grade.bonus >> cur->grade.total;
			for (int j = 0; j < 10; j++)
				in >> cur->attend[j];
			cur->pNext = nullptr;
		}
		else
		{
			cur->pNext = new Student;
			cur = cur->pNext;
			in >> cur->id;
			in >> cur->grade.midterm >> cur->grade.final >> cur->grade.bonus >> cur->grade.total;
			for (int j = 0; j < 10; j++)
				in >> cur->attend[j];
			cur->pNext = nullptr;
		}
	}
	in.close();
}
void loadCourseList(int& numCourse, Course*& pCourse, string dir, string name)
{
	ifstream in;
	string filename = dir + name + ".txt";
	in.open(filename);
	if (in.is_open())
	{
		int n;
		in >> n; in.get();
		numCourse = n;
		Course* cur = nullptr;
		string courseName;
		for (int i = 0; i < n; i++)
		{
			if (pCourse == nullptr)
			{
				pCourse = new Course;
				cur = pCourse;
				getline(in, courseName);
				cur->pStudent = nullptr;
				loadCourse(cur, dir, courseName);
				cur->pNext = nullptr;
			}
			else
			{
				cur->pNext = new Course;
				cur = cur->pNext;
				getline(in, courseName);
				cur->pStudent = nullptr;
				loadCourse(cur, dir, courseName);
				cur->pNext = nullptr;
			}
		}
	}
	else
	{
		numCourse = 0;
		pCourse = nullptr;
	}
	in.close();
}
