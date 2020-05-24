#include "function.h"
//chua test ham nao het

bool checkDuplicateAcademicYear(string AcademicYear, Semester* pSemester)
{
	Semester* cur = pSemester;
	bool t = false;
	while (cur != nullptr)
	{
		if (AcademicYear == cur->academicYear)
		{
			t = true;
			break;
		}
		cur = cur->pNext;
	}
	return t;
}
bool checkDuplicateSemester(string AcademicYear, string Semestername, Semester* pSemester)
{
	Semester* cur = pSemester;
	bool t = false;
	while (cur != nullptr)
	{
		if (AcademicYear == cur->academicYear && Semestername==cur->semester)
		{
			t = true;
			break;
		}
		cur = cur->pNext;
	}
	return t;
}
void createSemester(string AcademicYear, string Semestername, int& numSemester, Semester* &pSemester)
{
	//tao folder cho tung Semester
	string Foldername = "Semester\\" + AcademicYear+"-"+Semestername;
	char* Foldernamereal;
	int s = Foldername.size();
	Foldernamereal = new char[s + 1];
	for (int i = 0; i < s; ++i)
		Foldernamereal[i] = Foldername[i];
	Foldernamereal[s] = '\0';
	_mkdir(Foldernamereal);
	delete[]Foldernamereal;
	//tao file txt
	Foldername = Foldername + "\\" + AcademicYear + '-' + Semestername + ".txt";
	ofstream out;
	out.open(Foldername);
	out.close();
	//cap nhat pSemester
	if (pSemester == nullptr)
	{
		numSemester = 1;
		pSemester = new Semester;
		pSemester->pNext = nullptr;
		pSemester->academicYear = AcademicYear;
		pSemester->semester = Semestername;
		pSemester->pSchedule = nullptr;
		pSemester->numSchedule = 0;
	}
	else
	{
		numSemester++;
		Semester* cur = pSemester;
		while (cur->pNext != nullptr)
		{
			cur = cur->pNext;
		}
		cur->pNext = new Semester;
		cur = cur->pNext;
		cur->pNext = nullptr;
		cur->academicYear = AcademicYear;
		cur->semester = Semestername;
		cur->pSchedule = nullptr;
		cur->numSchedule = 0;
	}
}
void deleteSemester(string AcademicYear, string Semestername, int& numSemester, Semester* &pSemester)//chua delete directory
{
	//delete directory
	
	//update pSemester
	if (pSemester->academicYear == AcademicYear && pSemester->semester == Semestername)
	{
		Semester* tmp = pSemester;
		pSemester = pSemester->pNext;
		delete tmp;
		numSemester--;
	}
	else
	{
		Semester* prev = pSemester;
		Semester* cur = pSemester->pNext;
		while (cur != nullptr)
		{
			if (cur->academicYear == AcademicYear && cur->semester == Semestername)
			{
				prev->pNext = cur->pNext;
				delete cur;
				numSemester--;
				break;
			}
			else
			{
				prev = cur;
				cur = cur->pNext;
			}
		}
	}
	rewriteSemester(numSemester, pSemester);
}

void createAcademicYear(int& numSemester, Semester*& pSemester)
{
	cout << "Please enter the academic year: ";
	string AcademicYear;
	getline(cin, AcademicYear, '\n');
	while (checkDuplicateAcademicYear(AcademicYear, pSemester))
	{
		cout << "The academic year has been exited. Please enter another academic year: ";
		getline(cin, AcademicYear, '\n');
	}
	cout << "Please enter the number of semester: ";
	int n;
	cin >> n;
	while (n < 1)
	{
		cout << "Please enter a positive number: ";
		cin >> n;
	}
	cin.ignore();
	for (int i = 1; i <= n; ++i)
	{
		cout << "Enter name of " << i << "-th semester: ";
		string Semestername;
		getline(cin, Semestername, '\n');
		while (checkDuplicateSemester(AcademicYear, Semestername, pSemester))
		{
			cout << "The semester has been existed. Enter another name: ";
			getline(cin, Semestername, '\n');
		}
		createSemester(AcademicYear, Semestername, numSemester,pSemester);
	}
	rewriteSemester(numSemester, pSemester);
	cout << "The academic year has been created." << endl;
}

void updateAcademicYear(int& numSemester, Semester*& pSemester)
{
	string academicYear;
	cout << "Please enter the academic year: ";
	getline(cin, academicYear, '\n');
	while (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		cout << "The academic year is not available. Please enter another academic year: ";
		getline(cin, academicYear, '\n');
	}
	cout << "You choose academic year " << academicYear << endl;
	cout << "The academic year has had the semester(s) below: " << endl;
	Semester* cur = pSemester;
	int dem=0;
	while (cur != nullptr)
	{
		if (cur->academicYear == academicYear)
		{
			dem++;
			cout<<dem<<". " << cur->semester << endl;
		}
		cur = cur->pNext;
	}
	if (dem == 0) cout << "The academic year had no semester." << endl;
	int choice;
	while (true)
	{
		cout << "We have 3 options: " << endl;
		cout << "1. Add a new semester." << endl;
		cout << "2. Delete an existing semester." << endl;
		cout << "0. Exit." << endl;
		cout << "Your choice: ";
		cin >> choice;
		while (choice < 0 || choice >2)
		{
			cout << "Please enter from 0 to 2: ";
			cin >> choice;
		}
		if (choice == 0)
			break;
		else if (choice == 1)
		{
			//tao folder semester va cap nhat pSemester
			cout << "Add a new semester." << endl;
			cout << "Please enter the name of semester: ";
			string Semestername;
			getline(cin, Semestername, '\n');
			bool t = checkDuplicateSemester(academicYear, Semestername, pSemester);
			while (t)
			{
				cout << "The name of semester has existed." << endl;
				cout << "Do you want to " << endl;
				cout << "0. End adding semester." << endl;
				cout << "1. Add another semester." << endl;
				int choice2;
				cout << "Your choice: ";
				cin >> choice2;
				while (choice2 != 0 && choice2 != 1)
				{
					cout << "Please enter 0 or 1: ";
					cin >> choice2;
				}
				if (choice2 == 0)
					break;
				else
				{
					getline(cin, Semestername, '\n');
				}
			}
			if (t == true);
			else createSemester(academicYear,Semestername, numSemester, pSemester);
		}
		else
		{
			if (dem == 0)
				cout << "There are no semester to delete." << endl;
			else {
				cout << "The academic year has had semester(s) below: " << endl;
				cur = pSemester;
				int dem = 0;
				while (cur != nullptr)
				{
					if (cur->academicYear == academicYear)
					{
						dem++;
						cout << dem << ". " << cur->semester << endl;
					}
					cur = cur->pNext;
				}
				cout << "Please enter the name of semester you want to delete: " << endl;
				string deleteSemestername;
				getline(cin, deleteSemestername, '\n');
				while (!checkDuplicateSemester(academicYear, deleteSemestername, pSemester))
				{
					cout << "You have enter a wrong name. Please enter again: ";
					getline(cin, deleteSemestername, '\n');
				}
				deleteSemester(academicYear, deleteSemestername, numSemester, pSemester);
			}
		}
	}
	rewriteSemester(numSemester, pSemester);
}
void deleteAcademicYear(int& numSemester, Semester*& pSemester)//chua xoa duoc folder
{
	loadSemester(numSemester, pSemester);
	string academicYear;
	cout << "Please enter the academic year: ";
	getline(cin, academicYear, '\n');
	while (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		cout << "The academic year is not available. Please enter another academic year: ";
		getline(cin, academicYear, '\n');
	}
	cout << "You choose academic year " << academicYear << endl;
	cout << "Do you want to delete this academic year? Enter 1 for yes, 0 for no: ";
	int choice;
	cin >> choice;
	while (choice != 0 && choice != 1)
	{
		cout << "Please enter 0 or 1: ";
		cin >> choice;
	}
	if (choice == 0);
	else
	{
		//xoa directory

		//cap nhat pSemester
	}
	rewriteSemester(numSemester, pSemester);
}
void viewAcademicYear(string academicYear, int numSemester, Semester* pSemester)
{

}
void viewallSemester(int numSemester, Semester* pSemester) {

}

bool checkExistingClass(string classname) {
	int numClass=0;
	Class* pClass=nullptr;
	loadClass(numClass, pClass);
	Class* cur = pClass;
	bool t = false;
	while (cur != nullptr)
	{
		if (cur->name == classname)
		{
			t = true;
			break;
		}
		cur = cur->pNext;
	}
	deleteClassList(pClass);
	return t;
}
bool checkExistingLecturer(string lecturerName)
{
	int numLecturer;
	Lecturer* pLecturer = nullptr;
	loadLecturer(numLecturer, pLecturer);
	Lecturer* cur = pLecturer;
	while (cur != nullptr)
	{
		if (cur->fullname == lecturerName)
		{
			deleteLecturerList(pLecturer);
			return true;
		}
		cur = cur->pNext;
	}
	deleteLecturerList(pLecturer);
	return false;
}
bool checkExistingClassInSemester(string classname, string academicYear, string Semestername, Semester *pSemester)
{
	Semester* cur = pSemester;
	while (cur != nullptr && (cur->academicYear != academicYear || cur->semester != Semestername))
	{
		cur = cur->pNext;
	}
	Schedule* tmp = cur->pSchedule;
	while (tmp != nullptr)
	{
		if (tmp->cla == classname)
			return true;
		tmp = tmp->pNext;
	}
	return false;
}
void createClassInSemester(string classname, string academicYear, string Semestername, Semester *&pSemester)//chua viet lai vao file
{
	if (!checkExistingClassInSemester(classname, academicYear, Semestername, pSemester))
	{
		//tao folder cho class
		string Foldername = "Semester\\" + academicYear + "-" + Semestername+"\\"+classname;
		char* Foldernamereal;
		int s = Foldername.size();
		Foldernamereal = new char[s + 1];
		for (int i = 0; i < s; ++i)
			Foldernamereal[i] = Foldername[i];
		Foldernamereal[s] = '\0';
		_mkdir(Foldernamereal);
		delete[]Foldernamereal;
		//tao file txt cho class
		Foldername = Foldername + "\\" +classname+ ".txt";
		ofstream out;
		out.open(Foldername);
		out.close();
		//cap nhat pSemester
		Semester* cur = pSemester;
		while (cur != nullptr && (cur->academicYear != academicYear || cur->semester != Semestername))
		{
			cur = cur->pNext;
		}
		Schedule* tmp = cur->pSchedule;
		cur->numSchedule++;
		if (cur->pSchedule == nullptr)
		{
			cur->pSchedule = new Schedule;
			tmp = cur->pSchedule;
			tmp->pNext = nullptr;
			tmp->cla = classname;
			tmp->numCourse = 0;
			tmp->pCourse = nullptr;
		}
		else
		{
			while (tmp->pNext != nullptr)
				tmp = tmp->pNext;
			tmp->pNext = new Schedule;
			tmp = tmp->pNext;
			tmp->pNext = nullptr;
			tmp->cla = classname;
			tmp->numCourse = 0;
			tmp->pCourse = nullptr;
		}
		//rewrite file hoc ki nay.txt
		Foldername = "Semester\\" + academicYear + "-" + Semestername + "\\" + academicYear + "-" + Semestername + ".txt";
		rewriteScheduleList(cur->numSchedule, cur->pSchedule, Foldername);
	}
}

void importCourse(int& numSemester, Semester*& pSemester)
{
	cout << "We have the following semester: " << endl;
	viewallSemester(numSemester, pSemester);
	cout << "Please enter the academic year: ";
	string academicYear;
	getline(cin, academicYear, '\n');
	while (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		cout << "The academic year is not existed. Please enter another academic year: ";
		getline(cin, academicYear, '\n');
	}
	viewAcademicYear(academicYear, numSemester, pSemester);
	cout << "Please enter the semester: ";
	string Semestername;
	getline(cin, Semestername, '\n');
	while (!checkDuplicateSemester(academicYear, Semestername, pSemester))
	{
		cout << "The semester is not existed. Please enter another semester: ";
		getline(cin, Semestername, '\n');
	}
	cout << "We already have class(es) below: " << endl;
	int numClass=0;
	Class* pClass=nullptr;
	loadClass(numClass, pClass);
	Class* cur = pClass;
	while (cur != nullptr)
	{
		cout << cur->name << endl;
		cur = cur->pNext;
	}
	deleteClassList(pClass);
	cout << "Please enter the class: ";
	string classname;
	getline(cin, classname, '\n');
	while (!checkExistingClass(classname))
	{
		cout << "The class is not available. Please enter another class: ";
		getline(cin, classname, '\n');
	}
	if (!checkExistingClassInSemester(classname,academicYear,Semestername, pSemester))
	{
		createClassInSemester(classname, academicYear, Semestername, pSemester);
	}
	Semester* curSemester = pSemester;
	while (curSemester != nullptr && (curSemester->academicYear != academicYear || curSemester->semester != Semestername))
		curSemester = curSemester->pNext;
	Schedule* curSchedule = curSemester->pSchedule;
	while (curSchedule != nullptr && (curSchedule->cla != classname))
		curSchedule = curSchedule->pNext;
	Course* pCourse = curSchedule->pCourse;
	cout << "Please enter the link of csv file." << endl;
	cout << "Notice that the order of csv file must be: No,Course ID,Course Name,Lecturer name,Lecturer Degree,Lecturer gender,Lecturer Account,Start Date,End Date,Day of Week,Start Hour,Start Minute,End Hour,End HourMinute,Room" << endl;
	string linkcsv;
	getline(cin, linkcsv, '\n');
	ifstream in;
	in.open(linkcsv);
	if (!in.is_open())
	{
		cout << "Can not open csv file. Please check the link." << endl;
		return;
	}
	in.ignore(1000, '\n');
	while (!in.eof())
	{
		in.ignore(100, ',');
		string courseID;
		getline(in, courseID, ',');
		if (in.eof()) break;
		Course* tmpCourse = pCourse;
		if (pCourse == nullptr)
		{
			pCourse = new Course;
			tmpCourse = pCourse;
		}
		else {
			while (tmpCourse != nullptr)
			{
				if (tmpCourse->courseID == courseID)
					break;
				tmpCourse = tmpCourse->pNext;
			}
			if (tmpCourse == nullptr)
			{
				tmpCourse = pCourse;
				while (tmpCourse->pNext != nullptr)
					tmpCourse = tmpCourse->pNext;
				tmpCourse->pNext = new Course;
				tmpCourse = tmpCourse->pNext;
			}
		}
		tmpCourse->pNext = nullptr;
		tmpCourse->courseID = courseID;
		getline(in,tmpCourse->courseName,',');
		string lecturerName;
		getline(in, lecturerName,',');
		//kt xem giao vien co trung k, k trung thi tao
		string lecturerDegree;
		getline(in, lecturerDegree, ',');
		string lecturerGender;
		getline(in, lecturerGender, ',');
		string lecturerAccount;
		getline(in, lecturerAccount,',');
		if (!checkExistingLecturer(lecturerName))
		{
			int numLecturer = 0;
			Lecturer* pLecturer = nullptr;
			loadLecturer(numLecturer, pLecturer);
			Lecturer* curLecturer = pLecturer;
			if (pLecturer == nullptr)
			{
				pLecturer = new Lecturer;
				curLecturer = pLecturer;
			}
			else
			{
				while (curLecturer->pNext != nullptr)
				{
					curLecturer = curLecturer->pNext;
				}
				curLecturer->pNext = new Lecturer;
				curLecturer = curLecturer->pNext;
			}
			curLecturer->fullname = lecturerName;
			curLecturer->degree = lecturerDegree;
			if (lecturerGender == "Male")
				curLecturer->gender = 0;
			else curLecturer->gender = 1;
			curLecturer->username = lecturerAccount;
			curLecturer->password = lecturerAccount;
			curLecturer->pNext = nullptr;
			numLecturer++;
			rewriteLecturer(numLecturer, pLecturer);
			deleteLecturerList(pLecturer);
		}
		string dateStart;
		getline(in, dateStart, ',');

		string endStart;
		getline(in, endStart, ',');
		string dayOfWeek;
		getline(in, dayOfWeek, ',');
		int startHour;
		cin >> startHour;
		in.ignore();
		int startMinute;
		cin >> startMinute;
		in.ignore();
		int endHour;
		cin >> endHour;
		in.ignore();
		int endMinute;
		cin >> endMinute;
		in.ignore();
		string room;
		getline(in, room, '\n');

	}
	//viet lai text file


	in.close();
}

void manuallyAddCourse(int& numSemester, Semester*& pSemester)
{
	cout << "We have the following semester: " << endl;
	viewallSemester(numSemester, pSemester);
	cout << "Please enter the academic year: ";
	string academicYear;
	getline(cin, academicYear, '\n');
	while (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		cout << "The academic year is not existed. Please enter another academic year: ";
		getline(cin, academicYear, '\n');
	}
	viewAcademicYear(academicYear, numSemester, pSemester);
	cout << "Please enter the semester: ";
	string Semestername;
	getline(cin, Semestername, '\n');
	while (!checkDuplicateSemester(academicYear, Semestername, pSemester))
	{
		cout << "The semester is not existed. Please enter another semester: ";
		getline(cin, Semestername, '\n');
	}
	cout << "We already have class(es) below: " << endl;
	int numClass = 0;
	Class* pClass = nullptr;
	loadClass(numClass, pClass);
	Class* cur = pClass;
	while (cur != nullptr)
	{
		cout << cur->name << endl;
		cur = cur->pNext;
	}
	deleteClassList(pClass);
	cout << "Please enter the class: ";
	string classname;
	getline(cin, classname, '\n');
	while (!checkExistingClass(classname))
	{
		cout << "The class is not available. Please enter another class: ";
		getline(cin, classname, '\n');
	}
	if (!checkExistingClassInSemester(classname, academicYear, Semestername, pSemester))
	{
		createClassInSemester(classname, academicYear, Semestername, pSemester);
	}
	Semester* curSemester = pSemester;
	while (curSemester != nullptr && (curSemester->academicYear != academicYear || curSemester->semester != Semestername))
		curSemester = curSemester->pNext;
	Schedule* curSchedule = curSemester->pSchedule;
	while (curSchedule != nullptr && (curSchedule->cla != classname))
		curSchedule = curSchedule->pNext;
	Course* pCourse = curSchedule->pCourse;
	cout << "Please enter course ID: ";
	string courseID;
	getline(cin, courseID, '\n');
	Course* tmpCourse = pCourse;
	if (pCourse == nullptr)
	{
		pCourse = new Course;
		tmpCourse = pCourse;
	}
	else {
		while (tmpCourse != nullptr)
		{
			if (tmpCourse->courseID == courseID)
				break;
			tmpCourse = tmpCourse->pNext;
		}
		if (tmpCourse == nullptr)
		{
			tmpCourse = pCourse;
			while (tmpCourse->pNext != nullptr)
				tmpCourse = tmpCourse->pNext;
			tmpCourse = new Course;
		}
	}
	tmpCourse->pNext = nullptr;
	tmpCourse->courseID = courseID;
	cout << "Please enter course name: ";
	getline(cin, tmpCourse->courseName, '\n');
	cout << "Please enter lecturer name: ";
	string lecturerName;
	getline(cin, lecturerName, '\n');
	//kt xem giao vien co trung k, k trung thi tao
	string lecturerDegree;
	getline(cin, lecturerDegree, '\n');
	string lecturerGender;
	getline(cin, lecturerGender, '\n');
	string lecturerAccount;
	getline(cin, lecturerAccount, '\n');
	if (!checkExistingLecturer(lecturerName))
	{
		int numLecturer = 0;
		Lecturer* pLecturer = nullptr;
		loadLecturer(numLecturer, pLecturer);
		Lecturer* curLecturer = pLecturer;
		if (pLecturer == nullptr)
		{
			pLecturer = new Lecturer;
			curLecturer = pLecturer;
		}
		else
		{
			while (curLecturer->pNext != nullptr)
			{
				curLecturer = curLecturer->pNext;
			}
			curLecturer->pNext = new Lecturer;
			curLecturer = curLecturer->pNext;
		}
		curLecturer->fullname = lecturerName;
		curLecturer->degree = lecturerDegree;
		if (lecturerGender == "Male")
			curLecturer->gender = 0;
		else curLecturer->gender = 1;
		curLecturer->username = lecturerAccount;
		curLecturer->password = lecturerAccount;
		curLecturer->pNext = nullptr;
		numLecturer++;
		rewriteLecturer(numLecturer, pLecturer);
		deleteLecturerList(pLecturer);
	}
	string dateStart;
	getline(cin, dateStart, '\n');
	string endStart;
	getline(cin, endStart, '\n');
	string dayOfWeek;
	getline(cin, dayOfWeek, '\n');
	int startHour;
	cin >> startHour;
	int startMinute;
	cin >> startMinute;
	int endHour;
	cin >> endHour;
	int endMinute;
	cin >> endMinute;
	string room;
	getline(cin, room, '\n');
}