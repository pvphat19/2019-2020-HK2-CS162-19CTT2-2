#include "function.h"
//chua test ham nao het

bool checkDuplicateAcademicYear(string AcademicYear, Semester* pSemester)//ok
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
bool checkDuplicateSemester(string AcademicYear, string Semestername, Semester* pSemester)//ok
{
	Semester* cur = pSemester;
	bool t = false;
	while (cur != nullptr)
	{
		if (AcademicYear == cur->academicYear && Semestername == cur->semester)
		{
			t = true;
			break;
		}
		cur = cur->pNext;
	}
	return t;
}
void convertStringChar(string source, char*& destination)//ok
{
	destination = new char[source.size() + 1];
	for (int i = 0; i < source.size(); ++i)
		destination[i] = source[i];
	destination[source.size()] = '\0';
}
void deleteDirectory(string dir)//chi xoa thu muc rong, xoa file dung remove()
{
	char* directory;
	convertStringChar(dir, directory);
	_rmdir(directory);
	delete[]directory;
}
void createSemester(string AcademicYear, string Semestername, int& numSemester, Semester*& pSemester)
{
	//tao folder cho tung Semester
	string Foldername = "Semester\\" + AcademicYear + "-" + Semestername;
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
	out << 0 << endl;
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
	rewriteSemester(numSemester, pSemester);
}
void deleteFirstSchedule(string academicYear, string Semestername, int& numSemester, Semester*& pSemester)
{
	Semester* curSemester = pSemester;
	while (curSemester && (curSemester->academicYear != academicYear || curSemester->semester != Semestername))
		curSemester = curSemester->pNext;
	if (curSemester == nullptr) return;
	Schedule* pSchedule = curSemester->pSchedule;
	if (pSchedule == nullptr) return;
	while (pSchedule->pCourse != nullptr)
	{
		string dir = "Semester\\" + academicYear + "-" + Semestername + "\\" + pSchedule->cla + "\\" + pSchedule->pCourse->courseID + ".txt";
		char* directory;
		convertStringChar(dir, directory);
		remove(directory);
		Course* tmp = pSchedule->pCourse;
		Student* tmpStudent = tmp->pStudent;
		while (tmpStudent)
		{
			Student* temp = tmpStudent;
			tmpStudent = tmpStudent->pNext;
			delete temp;
		}
		pSchedule->pCourse = pSchedule->pCourse->pNext;
		delete tmp;
	}
	string dir = "Semester\\" + academicYear + "-" + Semestername + "\\" + pSchedule->cla + "\\" + pSchedule->cla + ".txt";
	char* directory;
	convertStringChar(dir, directory);
	remove(directory);
	dir = "Semester\\" + academicYear + "-" + Semestername + "\\" + pSchedule->cla;
	deleteDirectory(dir);
	Schedule* tmp = pSchedule;
	curSemester->pSchedule = curSemester->pSchedule->pNext;
	delete tmp;
	curSemester->numSchedule--;
	dir = "Semester\\" + academicYear + "-" + Semestername + "\\" + academicYear + "-" + Semestername + ".txt";
	rewriteScheduleList(curSemester->numSchedule, curSemester->pSchedule, dir);
}
void deleteSemester(string AcademicYear, string Semestername, int& numSemester, Semester*& pSemester)
{
	//delete directory va nhung cai p trong no
	Semester* curSemester = pSemester;
	while (curSemester != nullptr && (curSemester->academicYear != AcademicYear || curSemester->semester != Semestername))
		curSemester = curSemester->pNext;
	if (curSemester == nullptr)
	{
		return;
	}
	while (curSemester->pSchedule != nullptr)
	{
		deleteFirstSchedule(AcademicYear, Semestername, numSemester, pSemester);
	}
	string dir = "Semester\\" + AcademicYear + "-" + Semestername + "\\" + AcademicYear + "-" + Semestername + ".txt";
	char* directory;
	convertStringChar(dir, directory);
	remove(directory);
	dir = "Semester\\" + AcademicYear + "-" + Semestername;
	deleteDirectory(dir);
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
void createAcademicYear(int& x, int& y, string academicYear, int& numSemester, Semester*& pSemester)
{
	goToXY(x, y++); cout << "Please enter the number of semester: ";
	int tmpx = x, tmpy = y - 1;
	int n;
	string tmp;
	getline(cin, tmp);
	bool check = convertStringToInt(tmp, n);
	while (!check || n < 1)
	{
		goToXY(tmpx, tmpy); cout << "                                                                                ";
		goToXY(tmpx, tmpy); cout << "Please enter a positive number: ";
		getline(cin, tmp);
		check = convertStringToInt(tmp, n);
	}
	for (int i = 1; i <= n; ++i)
	{
		goToXY(x, y++); cout << "Enter name of " << i << "-th semester: ";
		string Semestername;
		getline(cin, Semestername, '\n');
		while (checkDuplicateSemester(academicYear, Semestername, pSemester))
		{
			goToXY(x, y++); cout << "The semester name has been used. Enter another name: ";
			getline(cin, Semestername, '\n');
		}
		createSemester(academicYear, Semestername, numSemester, pSemester);
	}
	rewriteSemester(numSemester, pSemester);
}
void updateAcademicYear(int& numSemester, Semester*& pSemester)//con xoa semester
{
	system("cls");
	int x = 10, y = 5;
	goToXY(x, y++); cout << "Update academic year.";
	string academicYear;
	goToXY(x, y++); cout << "Please enter the academic year: ";
	getline(cin, academicYear, '\n');
	if (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		goToXY(x, y++); cout << "This academic year is a new academic year. Do you want to create the academic year: ";
		goToXY(x, y++); cout << "Enter 1(yes) or 0(no): ";
		int choice;
		string yourchoice;
		getline(cin, yourchoice);
		bool check = convertStringToInt(yourchoice, choice);
		while (!check || (choice != 0 && choice != 1))
		{
			goToXY(x, y - 1); cout << "                                                                               ";
			goToXY(x, y - 1); cout << "Enter 1(yes) or 0(no): ";
			getline(cin, yourchoice);
			check = convertStringToInt(yourchoice, choice);
		}
		if (choice == 0)
		{
			textColor(14);
			goToXY(x, y);
			system("pause");
			return;
		}
		else {
			createAcademicYear(x, y, academicYear, numSemester, pSemester);
			textColor(2);
			goToXY(x, y++); cout << "The academic year has been created successfully!";
			textColor(14);
		}
	}
	else {
		goToXY(x, y++); cout << "You choose academic year " << academicYear;
		Semester* cur = pSemester;
		int count = 0;
		while (cur != nullptr)
		{
			if (cur->academicYear == academicYear)
			{
				count++;
			}
			cur = cur->pNext;
		}
		if (count > 0) {
			goToXY(x, y++); cout << "This academic year has the semester(s) below: ";
			cur = pSemester;
			int dem = 0;
			x += 3; y++;
			while (cur != nullptr)
			{
				if (cur->academicYear == academicYear)
				{
					dem++;
					goToXY(x, y++); cout << dem << ". " << cur->semester;
				}
				cur = cur->pNext;
			}
			x -= 3; y++;
		}
		else {
			goToXY(x, y++); cout << "The academic year has no semester.";
			y++;
		}
		goToXY(x, y++); cout << "We have 3 options: ";
		goToXY(x, y++); cout << "0. Exit.";
		goToXY(x, y++); cout << "1. Add a new semester.";
		goToXY(x, y++); cout << "2. Delete an existing semester.";
		goToXY(x, y++); cout << "Your choice: ";
		string yourChoice;
		int choice;
		getline(cin, yourChoice);
		bool check = convertStringToInt(yourChoice, choice);
		while (!check || (choice < 0 || choice >2))
		{
			goToXY(x, y - 1); cout << "                                                                 ";
			goToXY(x, y - 1); cout << "Please enter your choice (0, 1 or 2): ";
			getline(cin, yourChoice);
			check = convertStringToInt(yourChoice, choice);
		}
		if (choice == 0);
		else if (choice == 1)
		{
			//tao folder semester va cap nhat pSemester
			goToXY(x, y++); cout << "Please enter the name of semester you want to add: ";
			string Semestername;
			getline(cin, Semestername, '\n');
			bool t = checkDuplicateSemester(academicYear, Semestername, pSemester);
			while (t)
			{
				goToXY(x, y++); cout << "The name of semester has existed.";
				goToXY(x, y++); cout << "Do you want to ";
				goToXY(x, y++); cout << "0. End adding semester.";
				goToXY(x, y++); cout << "1. Enter another semester name.";
				int choice2;
				goToXY(x, y++); cout << "Your choice: ";
				string yourchoice;
				getline(cin, yourchoice);
				bool check = convertStringToInt(yourchoice, choice2);
				while (!check || (choice2 != 0 && choice2 != 1))
				{
					goToXY(x, y - 1); cout << "                                                                       ";
					goToXY(x, y - 1); cout << "Please enter your choice (0 or 1): ";
					getline(cin, yourchoice);
					check = convertStringToInt(yourchoice, choice2);
				}
				if (choice2 == 0)
					break;
				else
				{
					goToXY(x, y++); cout << "Please enter the semester name again: ";
					getline(cin, Semestername, '\n');
				}
				t = checkDuplicateSemester(academicYear, Semestername, pSemester);
			}
			if (t == true);
			else
			{
				count++;
				createSemester(academicYear, Semestername, numSemester, pSemester);
				textColor(2);
				goToXY(x, y++); cout << "The semester has successfully added!" << endl;
				textColor(14);
			}
		}
		else
		{
			if (count == 0)
			{
				goToXY(x, y++); cout << "There is no semester to delete.";
			}
			else {
				goToXY(x, y++); cout << "Please enter the name of semester you want to delete: ";
				string Semestername;
				getline(cin, Semestername, '\n');
				bool t = checkDuplicateSemester(academicYear, Semestername, pSemester);
				while (!t)
				{
					goToXY(x, y++); cout << "The name of semester has not existed.";
					goToXY(x, y++); cout << "Do you want to ";
					goToXY(x, y++); cout << "0. End deleting semester.";
					goToXY(x, y++); cout << "1. Enter another semester name.";
					int choice2;
					goToXY(x, y++); cout << "Your choice: ";
					string yourchoice;
					getline(cin, yourchoice);
					bool check = convertStringToInt(yourchoice, choice2);
					while (!check || (choice2 != 0 && choice2 != 1))
					{
						goToXY(x, y - 1); cout << "                                                                       ";
						goToXY(x, y - 1); cout << "Please enter your choice (0 or 1): ";
						getline(cin, yourchoice);
						check = convertStringToInt(yourchoice, choice2);
					}
					if (choice2 == 0)
						break;
					else
					{
						goToXY(x, y++); cout << "Please enter the semester name again: ";
						getline(cin, Semestername, '\n');
					}
					t = checkDuplicateSemester(academicYear, Semestername, pSemester);
				}
				if (t == false);
				else
				{
					count--;
					deleteSemester(academicYear, Semestername, numSemester, pSemester);
					textColor(2);
					goToXY(x, y++); cout << "The semester has successfully deleted!";
					textColor(14);
				}
			}
		}
	}
	rewriteSemester(numSemester, pSemester);
	goToXY(x, y);
	textColor(14);
	system("pause");
}
/*void deleteAcademicYear(int& numSemester, Semester*& pSemester)
{
	system("cls");
	int x = 10, y = 5;
	string academicYear;
	goToXY(x, y++); cout << "Delete academic year.";
	goToXY(x, y++); cout << "Please enter the academic year: ";
	int tmpx = x, tmpy = y - 1;
	getline(cin, academicYear, '\n');
	while (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		goToXY(tmpx, tmpy); cout << "                                                                                                         ";
		goToXY(tmpx, tmpy); cout << "The academic year is not available. Please enter another academic year: ";
		getline(cin, academicYear, '\n');
	}
	system("pause");
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "Delete academic year.";
	goToXY(x, y++); cout << "You choose academic year " << academicYear << endl;
	goToXY(x, y++); cout << "Do you want to delete this academic year? Enter 1 for yes, 0 for no: ";
	string yourchoice;
	getline(cin, yourchoice);
	int choice;
	bool check = convertStringToInt(yourchoice, choice);
	while (!check || (choice != 0 && choice != 1))
	{
		goToXY(x, y); cout << "                                                                                    ";
		goToXY(x, y); cout << "Please enter 0 or 1: ";
		getline(cin, yourchoice);
		check = convertStringToInt(yourchoice, choice);
	}
	y++;
	if (choice == 0);
	else
	{
		while (pSemester &&(checkDuplicateAcademicYear(academicYear,pSemester)))
		{
			Semester* cur = pSemester;
			while (cur && cur->academicYear != academicYear)
				cur = cur->pNext;
			deleteSemester(academicYear, cur->semester, numSemester, pSemester);
			goToXY(x, y++); cout << "The academic has been removed successfully.";
		}
	}
	rewriteSemester(numSemester, pSemester);
	system("pause");
}*/
void sortSemesterList(Semester*& pSemester)
{
	for (Semester* curI = pSemester; curI != nullptr; curI = curI->pNext)
		for (Semester* curJ = curI->pNext; curJ != nullptr; curJ = curJ->pNext)
			if (curI->academicYear > curJ->academicYear)
			{
				swap(curI->academicYear, curJ->academicYear);
				swap(curI->semester, curJ->semester);
			}
			else if (curI->academicYear == curJ->academicYear)
				if (curI->semester > curJ->semester)
				{
					swap(curI->semester, curJ->semester);
				}
}
void viewAcademicYear(int& x, int& y, string academicYear, int numSemester, Semester* pSemester)
{
	Semester* tempSemester = nullptr;
	Semester* temp = nullptr;
	int dem = 0;
	Semester* curSemester = pSemester;
	while (curSemester != nullptr)
	{
		if (curSemester->academicYear == academicYear)
		{
			dem++;
			if (tempSemester == nullptr)
			{
				tempSemester = new Semester;
				tempSemester->academicYear = curSemester->academicYear;
				tempSemester->semester = curSemester->semester;
				tempSemester->numSchedule = 0;
				tempSemester->pSchedule = nullptr;
				tempSemester->pNext = nullptr;
				temp = tempSemester;
			}
			else
			{
				temp->pNext = new Semester;
				temp = temp->pNext;
				temp->academicYear = curSemester->academicYear;
				temp->semester = curSemester->semester;
				temp->numSchedule = 0;
				temp->pSchedule = nullptr;
				temp->pNext = nullptr;
			}
		}
		curSemester = curSemester->pNext;
	}
	sortSemesterList(tempSemester);
	if (dem == 0)
	{
		goToXY(x, y++); cout << "The academic year has no semester.";
	}
	else {
		goToXY(x, y++); cout << "The academic year " << academicYear << " has " << dem << " semester(s) below: ";
		temp = tempSemester;
		x += 3; y++;
		while (temp)
		{
			goToXY(x, y++); cout << temp->semester;
			temp = temp->pNext;
		}
		x -= 3; y++;
	}
	deleteSemesterList(tempSemester);
}
void viewallSemester() {
	system("cls"); int x = 10, y = 5;
	int tmpnum = 0;
	Semester* tmppSemester = nullptr;
	loadSemester(tmpnum, tmppSemester);
	sortSemesterList(tmppSemester);
	Semester* cur = tmppSemester;
	goToXY(x, y++); cout << "All available semester(s): ";
	x += 3; y++;
	while (cur)
	{
		goToXY(x, y++); cout << cur->academicYear << " - " << cur->semester << endl;
		cur = cur->pNext;
	}
	x -= 3; y++;
	deleteSemesterList(tmppSemester);
	goToXY(x, y);
	textColor(14);
	system("pause");
}
bool checkExistingClass(string classname) {
	int numClass = 0;
	Class* pClass = nullptr;
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
bool checkExistingLecturer(string lecturerAccount)
{
	int numLecturer;
	Lecturer* pLecturer = nullptr;
	loadLecturer(numLecturer, pLecturer);
	Lecturer* cur = pLecturer;
	while (cur != nullptr)
	{
		if (cur->username == lecturerAccount)
		{
			deleteLecturerList(pLecturer);
			return true;
		}
		cur = cur->pNext;
	}
	deleteLecturerList(pLecturer);
	return false;
}
bool checkExistingClassInSemester(string classname, string academicYear, string Semestername, Semester* pSemester)
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
void createClassInSemester(string classname, string academicYear, string Semestername, Semester*& pSemester)//chua viet lai vao file
{
	if (!checkExistingClassInSemester(classname, academicYear, Semestername, pSemester))
	{
		//tao folder cho class
		string Foldername = "Semester\\" + academicYear + "-" + Semestername + "\\" + classname;
		char* Foldernamereal;
		int s = Foldername.size();
		Foldernamereal = new char[s + 1];
		for (int i = 0; i < s; ++i)
			Foldernamereal[i] = Foldername[i];
		Foldernamereal[s] = '\0';
		_mkdir(Foldernamereal);
		delete[]Foldernamereal;
		//tao file txt cho class
		Foldername = Foldername + "\\" + classname + ".txt";
		ofstream out;
		out.open(Foldername);
		out << 0 << endl;
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
	system("cls"); int x = 10, y = 5;
	goToXY(x, y++); cout << "Import a course from csv file.";
	goToXY(x, y++); cout << "Please enter the academic year you want to choose: ";
	string academicYear;
	getline(cin, academicYear, '\n');
	if (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		textColor(4);
		goToXY(x, y++); cout << "The academic year has not existed. ";
		goToXY(x, y); system("pause");
		textColor(14);
		return;
	}
	viewAcademicYear(x, y, academicYear, numSemester, pSemester);
	goToXY(x, y++); cout << "Please enter the semester you want to choose: ";
	string Semestername;
	getline(cin, Semestername, '\n');
	if (!checkDuplicateSemester(academicYear, Semestername, pSemester))
	{
		textColor(4);
		goToXY(x, y++); cout << "The semester has not existed!";
		goToXY(x, y); system("pause");
		textColor(14);
		return;
	}
	goToXY(x, y++); cout << "Please enter the class you want to import: ";
	string classname;
	getline(cin, classname, '\n');
	if (!checkExistingClass(classname))
	{
		textColor(4);
		goToXY(x, y++); cout << "This class is not available.";
		goToXY(x, y); system("pause");
		textColor(14);
		return;
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
	{
		curSchedule = curSchedule->pNext;
	}
	goToXY(x, y++); cout << "Please enter the link of csv file: ";
	string linkcsv;
	getline(cin, linkcsv, '\n');
	ifstream in;
	in.open(linkcsv);
	while (!in.is_open())
	{
		y++;
		textColor(4);
		goToXY(x, y++); cout << "Can not open csv file!";
		textColor(14);
		goToXY(x, y++); cout << "Do you want to: ";
		goToXY(x, y++); cout << "0. Exit.";
		goToXY(x, y++); cout << "1. Enter another link.";
		goToXY(x, y++); cout << "Your choice: ";
		int choice;
		string yourchoice;
		getline(cin, yourchoice);
		bool check = convertStringToInt(yourchoice, choice);
		while (!check || (choice != 0 && choice != 1))
		{
			goToXY(x, y - 1); cout << "                                                                    ";
			goToXY(x, y - 1); cout << "Please enter 0 or 1: ";
			getline(cin, yourchoice);
			check = convertStringToInt(yourchoice, choice);
		}
		if (choice == 0)
		{
			textColor(14);
			goToXY(x, y); system("pause");
			return;
		}
		else
		{
			goToXY(x, y++); cout << "Please enter csv link: ";
			getline(cin, linkcsv, '\n');
			in.open(linkcsv);
		}
	}
	in.ignore(1000, '\n');
	while (!in.eof())
	{
		in.ignore(100, ',');
		string courseID;
		getline(in, courseID, ',');
		if (in.eof()) break;
		Course* tmpCourse = curSchedule->pCourse;
		if (curSchedule->pCourse == nullptr)
		{
			curSchedule->numCourse++;
			curSchedule->pCourse = new Course;
			tmpCourse = curSchedule->pCourse;
			tmpCourse->pNext = nullptr;
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
				tmpCourse = curSchedule->pCourse;
				while (tmpCourse->pNext != nullptr)
					tmpCourse = tmpCourse->pNext;
				tmpCourse->pNext = new Course;
				tmpCourse = tmpCourse->pNext;
				curSchedule->numCourse++;
				tmpCourse->pNext = nullptr;
			}
		}
		tmpCourse->courseID = courseID;
		getline(in, tmpCourse->courseName, ',');
		string lecturerName;
		getline(in, lecturerName, ',');
		string lecturerDegree;
		getline(in, lecturerDegree, ',');
		string lecturerGender;
		getline(in, lecturerGender, ',');
		string lecturerAccount;
		getline(in, lecturerAccount, ',');
		in >> tmpCourse->dateStart.year;
		in.ignore();
		in >> tmpCourse->dateStart.month;
		in.ignore();
		in >> tmpCourse->dateStart.day;
		in.ignore();
		in >> tmpCourse->dateEnd.year;
		in.ignore();
		in >> tmpCourse->dateEnd.month;
		in.ignore();
		in >> tmpCourse->dateEnd.day;
		in.ignore();
		getline(in, tmpCourse->day, ',');
		in >> tmpCourse->timeStart.hour;
		in.ignore();
		in >> tmpCourse->timeStart.minute;
		in.ignore();
		in >> tmpCourse->timeEnd.hour;
		in.ignore();
		in >> tmpCourse->timeEnd.minute;
		in.ignore();
		getline(in, tmpCourse->room, '\n');
		if (!checkExistingLecturer(lecturerAccount))
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
		int numLecturer = 0;
		Lecturer* pLecturer = nullptr;
		loadLecturer(numLecturer, pLecturer);
		Lecturer* currentLecturer = pLecturer;
		while (currentLecturer != nullptr && currentLecturer->username != lecturerAccount)
			currentLecturer = currentLecturer->pNext;
		tmpCourse->lecturer.fullname = lecturerName;
		tmpCourse->lecturer.degree = lecturerDegree;
		if (lecturerGender == "Male")
			tmpCourse->lecturer.gender = 0;
		else
			tmpCourse->lecturer.gender = 1;
		tmpCourse->lecturer.password = currentLecturer->password;
		tmpCourse->lecturer.username = lecturerAccount;
		deleteLecturerList(pLecturer);
		tmpCourse->lecturer.pNext = nullptr;
		tmpCourse->cla = classname;
		tmpCourse->numStudent = 0;
		tmpCourse->pStudent = nullptr;
		loadStudent(tmpCourse->numStudent, tmpCourse->pStudent, classname);
		Student* temp = tmpCourse->pStudent;
		while (temp)
		{
			temp->grade.bonus = -1;
			temp->grade.final = -1;
			temp->grade.midterm = -1;
			temp->grade.total = -1;
			for (int i = 0; i < 10; i++)
				temp->attend[i] = -1;
			temp = temp->pNext;
		}
		string directory1 = "Semester\\" + academicYear + "-" + Semestername + "\\" + classname + "\\" + courseID + ".txt";
		rewriteCourse(tmpCourse, directory1);
	}
	//viet lai text file
	string directory = "Semester\\" + academicYear + "-" + Semestername + "\\" + academicYear + "-" + Semestername + ".txt";
	rewriteScheduleList(curSemester->numSchedule, curSemester->pSchedule, directory);
	directory = "Semester\\" + academicYear + "-" + Semestername + "\\" + classname + "\\" + classname + ".txt";
	rewriteCourseList(curSchedule->numCourse, curSchedule->pCourse, directory);
	in.close();
	y++;
	textColor(2);
	goToXY(x, y++); cout << "Import successfully!";
	goToXY(x, y++); system("pause");
	textColor(14);
}
void createdayOfWeek(int day, string& res)
{
	if (day == 2)
		res = "MON";
	if (day == 3)
		res = "TUE";
	if (day == 3)
		res = "WED";
	if (day == 5)
		res = "THU";
	if (day == 6)
		res = "FRI";
	if (day == 7)
		res = "SAT";
	else
		res = "SUN";
}
void inputdaycourse(Date& day, int& x, int& y)
{
	goToXY(x, y++); cout << "Day: ";
	string dobDay;
	getline(cin, dobDay);
	bool check = convertStringToInt(dobDay, day.day);
	while (!check && (day.day <= 0 || day.day > 31))
	{
		textColor(4);
		goToXY(x, y++); cout << "Please enter a positive integer: ";
		textColor(14);
		getline(cin, dobDay);
		check = convertStringToInt(dobDay, day.day);
	}
	goToXY(x, y++); cout << "Month: ";
	string dobMonth;
	getline(cin, dobMonth);
	check = convertStringToInt(dobMonth, day.month);
	while (!check && (day.month <= 0 || day.month > 12))
	{
		textColor(4);
		goToXY(x, y++); cout << "Please enter a positive integer: ";
		textColor(14);
		getline(cin, dobMonth);
		check = convertStringToInt(dobMonth, day.month);
	}
	goToXY(x, y++); cout << "Year: ";
	string dobYear;
	getline(cin, dobYear);
	check = convertStringToInt(dobYear, day.year);
	while (!check)
	{
		textColor(4);
		goToXY(x, y++); cout << "Please enter a positive integer: ";
		textColor(14);
		getline(cin, dobYear);
		check = convertStringToInt(dobYear, day.year);
	}
}
void manuallyAddCourse(int& numSemester, Semester*& pSemester)
{
	system("cls"); int x = 10, y = 5;
	goToXY(x, y++); cout << "Manually add a course.";
	goToXY(x, y++); cout << "Please enter the academic year you want to choose: ";
	string academicYear;
	getline(cin, academicYear, '\n');
	if (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		textColor(4);
		goToXY(x, y++); cout << "The academic year has not existed!";
		goToXY(x, y++); system("pause");
		textColor(14);
		return;
	}
	viewAcademicYear(x, y, academicYear, numSemester, pSemester);
	goToXY(x, y++); cout << "Please enter the semester you want to choose: ";
	string Semestername;
	getline(cin, Semestername, '\n');
	if (!checkDuplicateSemester(academicYear, Semestername, pSemester))
	{
		textColor(4);
		goToXY(x, y++); cout << "The semester has not existed!";
		goToXY(x, y++); system("pause");
		textColor(14);
		return;
	}
	goToXY(x, y++); cout << "We already have class(es) below: ";
	x += 3; y++;
	int numClass = 0;
	Class* pClass = nullptr;
	loadClass(numClass, pClass);
	Class* cur = pClass;
	while (cur != nullptr)
	{
		goToXY(x, y++); cout << cur->name;
		cur = cur->pNext;
	}
	deleteClassList(pClass);
	x -= 3; y++;
	goToXY(x, y++); cout << "Please enter the class you want to choose: ";
	string classname;
	getline(cin, classname, '\n');
	if (!checkExistingClass(classname))
	{
		textColor(4);
		goToXY(x, y++); cout << "The class has not existed!";
		goToXY(x, y++); system("pause");
		textColor(14);
		return;
	}
	if (!checkExistingClassInSemester(classname, academicYear, Semestername, pSemester))
	{
		createClassInSemester(classname, academicYear, Semestername, pSemester);
	}
	goToXY(x, y++);
	system("pause");
	system("cls");
	x = 10; y = 5;
	Semester* curSemester = pSemester;
	while (curSemester != nullptr && (curSemester->academicYear != academicYear || curSemester->semester != Semestername))
		curSemester = curSemester->pNext;
	Schedule* curSchedule = curSemester->pSchedule;
	while (curSchedule != nullptr && (curSchedule->cla != classname))
	{
		curSchedule = curSchedule->pNext;
	}
	goToXY(x, y++); cout << "Please enter course ID: ";
	string courseID;
	getline(cin, courseID, '\n');
	Course* tmpCourse = curSchedule->pCourse;
	if (curSchedule->pCourse == nullptr)
	{
		curSchedule->pCourse = new Course;
		tmpCourse = curSchedule->pCourse;
		curSchedule->numCourse++;
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
			tmpCourse = curSchedule->pCourse;
			while (tmpCourse->pNext != nullptr)
				tmpCourse = tmpCourse->pNext;
			tmpCourse->pNext = new Course;
			tmpCourse = tmpCourse->pNext;
			curSchedule->numCourse++;
		}
	}
	tmpCourse->pNext = nullptr;
	tmpCourse->courseID = courseID;
	goToXY(x, y++); cout << "Please enter course name: ";
	getline(cin, tmpCourse->courseName, '\n');
	goToXY(x, y++); cout << "Please enter lecturer username: ";
	string lecturerAccount;
	getline(cin, lecturerAccount, '\n');
	if (!checkExistingLecturer(lecturerAccount))
	{
		goToXY(x, y++); cout << "This is a new lecturer. We need to add more information.";
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
		curLecturer->username = lecturerAccount;
		goToXY(x, y++); cout << "Please enter lecturer name: ";
		string lecturerName;
		getline(cin, lecturerName, '\n');
		curLecturer->fullname = lecturerName;
		goToXY(x, y++); cout << "Please enter lecturer degree: ";
		string lecturerDegree;
		getline(cin, lecturerDegree, '\n');
		curLecturer->degree = lecturerDegree;
		goToXY(x, y++); cout << "Please enter lecturer gender (0 for male and 1 for female):";
		cin >> curLecturer->gender; cin.ignore();
		curLecturer->password = lecturerAccount;
		curLecturer->pNext = nullptr;
		numLecturer++;
		rewriteLecturer(numLecturer, pLecturer);
		deleteLecturerList(pLecturer);
	}
	goToXY(x, y++); cout << "Please enter date start: ";
	inputdaycourse(tmpCourse->dateStart, x, y);
	goToXY(x, y++); cout << "Please enter date end: ";
	inputdaycourse(tmpCourse->dateEnd, x, y);
	goToXY(x, y++); cout << "Please enter day of week(e.g: 2, 3, 4, 5, 6, 7, 8): ";
	int dayOfWeek;
	cin >> dayOfWeek;
	while (dayOfWeek <= 1 || dayOfWeek > 8)
	{
		goToXY(x, y++); cout << "Please enter from 2 to 8: ";
		cin >> dayOfWeek;
	}
	createdayOfWeek(dayOfWeek, tmpCourse->day);
	goToXY(x, y++); cout << "Please enter start hour: ";
	cin >> tmpCourse->timeStart.hour;
	goToXY(x, y++); cout << "Please enter start minute: ";
	cin >> tmpCourse->timeStart.minute;
	goToXY(x, y++); cout << "Please enter end hour: ";
	cin >> tmpCourse->timeEnd.hour;
	goToXY(x, y++); cout << "Please enter end minute: ";
	cin >> tmpCourse->timeEnd.minute;
	cin.ignore();
	goToXY(x, y++); cout << "Please enter room: ";
	getline(cin, tmpCourse->room, '\n');
	int numLecturer = 0;
	Lecturer* pLecturer = nullptr;
	loadLecturer(numLecturer, pLecturer);
	Lecturer* currentLecturer = pLecturer;
	while (currentLecturer != nullptr && currentLecturer->username != lecturerAccount)
		currentLecturer = currentLecturer->pNext;
	tmpCourse->lecturer.fullname = currentLecturer->fullname;
	tmpCourse->lecturer.degree = currentLecturer->degree;
	tmpCourse->lecturer.gender = currentLecturer->gender;
	tmpCourse->lecturer.password = currentLecturer->password;
	tmpCourse->lecturer.username = lecturerAccount;
	deleteLecturerList(pLecturer);
	tmpCourse->lecturer.pNext = nullptr;
	tmpCourse->cla = classname;
	tmpCourse->numStudent = 0;
	tmpCourse->pStudent = nullptr;
	loadStudent(tmpCourse->numStudent, tmpCourse->pStudent, classname);
	Student* temp = tmpCourse->pStudent;
	while (temp)
	{
		temp->grade.bonus = -1;
		temp->grade.final = -1;
		temp->grade.midterm = -1;
		temp->grade.total = -1;
		for (int i = 0; i < 10; i++)
			temp->attend[i] = -1;
		temp = temp->pNext;
	}
	string directory1 = "Semester\\" + academicYear + "-" + Semestername + "\\" + classname + "\\" + courseID + ".txt";
	rewriteCourse(tmpCourse, directory1);
	//viet lai text file
	string directory = "Semester\\" + academicYear + "-" + Semestername + "\\" + academicYear + "-" + Semestername + ".txt";
	rewriteScheduleList(curSemester->numSchedule, curSemester->pSchedule, directory);
	directory = "Semester\\" + academicYear + "-" + Semestername + "\\" + classname + "\\" + classname + ".txt";
	rewriteCourseList(curSchedule->numCourse, curSchedule->pCourse, directory);
	textColor(2);
	goToXY(x, y++); cout << "Import successfully!";
	goToXY(x, y++); system("pause");
	textColor(14);
	return;
}
bool checkExistingCourse(int numSemester, Semester* pSemester, string academicYear, string Semestername, string classname, string courseID)
{
	Semester* cur = pSemester;
	while (cur != nullptr && (cur->academicYear != academicYear || cur->semester != Semestername))
	{
		cur = cur->pNext;
	}
	Schedule* tmp = cur->pSchedule;
	while (tmp != nullptr && (tmp->cla != classname))
	{
		tmp = tmp->pNext;
	}
	Course* curCourse = tmp->pCourse;
	while (curCourse != nullptr)
	{
		if (curCourse->courseID == courseID)
			return true;
		curCourse = curCourse->pNext;
	}
	return false;
}
void importScoreboard(int& numSemester, Semester*& pSemester)//mac dinh course phai ton tai truoc moi nhap diem duoc
{
	system("cls"); int x = 10, y = 5;
	goToXY(x, y++); cout << "Import scoreboard from csv file."; y++;
	goToXY(x, y++); cout << "Please enter the academic year: ";
	string academicYear;
	getline(cin, academicYear, '\n');
	if (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		y++;
		textColor(4);
		goToXY(x, y++); cout << "The academic year has not existed!";
		goToXY(x, y++); system("pause");
		textColor(14);
		return;
	}
	viewAcademicYear(x, y, academicYear, numSemester, pSemester);
	goToXY(x, y++); cout << "Please enter the semester you want to choose: ";
	string Semestername;
	getline(cin, Semestername, '\n');
	if (!checkDuplicateSemester(academicYear, Semestername, pSemester))
	{
		y++;
		textColor(4);
		goToXY(x, y++); cout << "The semester has not existed!";
		goToXY(x, y++); system("pause");
		textColor(14);
		return;
	}
	goToXY(x, y++);  cout << "Please enter the class: ";
	string classname;
	getline(cin, classname, '\n');
	if (!checkExistingClassInSemester(classname, academicYear, Semestername, pSemester))
	{
		y++;
		textColor(4);
		goToXY(x, y++); cout << "The class has not existed in this semester.";
		goToXY(x, y++); system("pause");
		textColor(14);
		return;
	}
	Semester* curSemester = pSemester;
	while (curSemester != nullptr && (curSemester->academicYear != academicYear || curSemester->semester != Semestername))
		curSemester = curSemester->pNext;
	Schedule* curSchedule = curSemester->pSchedule;
	while (curSchedule != nullptr && (curSchedule->cla != classname))
	{
		curSchedule = curSchedule->pNext;
	}
	if (curSchedule->numCourse == 0)
	{
		textColor(4);
		goToXY(x, y++); cout << "The class has not had any course.";
		goToXY(x, y++); system("pause");
		textColor(14);
		return;
	}
	Course* pCourse = curSchedule->pCourse;
	goToXY(x, y++); cout << "Please enter course ID: ";
	string courseID;
	getline(cin, courseID, '\n');
	if (!checkExistingCourse(numSemester, pSemester, academicYear, Semestername, classname, courseID))
	{
		y++;
		textColor(4);
		goToXY(x, y++); cout << "The course is not available for this class!";
		goToXY(x, y++); system("pause");
		textColor(14);
		return;
	}
	Course* tmpCourse = pCourse;
	while (tmpCourse != nullptr && tmpCourse->courseID != courseID)
	{
		tmpCourse = tmpCourse->pNext;
	}
	goToXY(x, y++); cout << "Please enter the link of csv file: ";
	string linkcsv;
	getline(cin, linkcsv, '\n');
	ifstream in;
	in.open(linkcsv);
	while (!in.is_open())
	{
		y++;
		textColor(4);
		goToXY(x, y++); cout << "Can not open csv file!";
		textColor(14);
		goToXY(x, y++); cout << "Do you want to: ";
		goToXY(x, y++); cout << "0. Exit.";
		goToXY(x, y++); cout << "1. Enter another link.";
		goToXY(x, y++); cout << "Your choice: ";
		int choice;
		string yourchoice;
		getline(cin, yourchoice);
		bool check = convertStringToInt(yourchoice, choice);
		while (!check || (choice != 0 && choice != 1))
		{
			goToXY(x, y - 1); cout << "                                                                    ";
			goToXY(x, y - 1); cout << "Please enter your choice(0 or 1): ";
			getline(cin, yourchoice);
			check = convertStringToInt(yourchoice, choice);
		}
		if (choice == 0) {
			goToXY(x, y++);
			system("pause");
			return;
		}
		else
		{
			goToXY(x, y++); cout << "Please enter csv link: ";
			getline(cin, linkcsv, '\n');
			in.open(linkcsv);
		}
	}
	Student* pStudent = tmpCourse->pStudent;
	int dem = 0;
	int success = 0;
	in.ignore(100, '\n');
	while (!in.eof())
	{
		in.ignore(100, ',');
		int studentID;
		in >> studentID;
		if (in.eof()) break;
		in.ignore();
		string studentName;
		getline(in, studentName, ',');
		int midterm;
		in >> midterm;
		in.ignore();
		int final;
		in >> final;
		in.ignore();
		int bonus;
		in >> bonus;
		in.ignore();
		int total;
		in >> total;
		in.ignore(100, '\n');
		dem++;
		bool t = false;
		Student* curStudent = pStudent;
		while (curStudent)
		{
			if (curStudent->id == studentID)
			{
				t = true;
				break;
			}
			curStudent = curStudent->pNext;
		}
		if (t == true)
		{
			success++;
			curStudent->grade.midterm = midterm;
			curStudent->grade.final = final;
			curStudent->grade.bonus = bonus;
			curStudent->grade.total = total;
		}
	}
	in.close();
	string directory1 = "Semester\\" + academicYear + "-" + Semestername + "\\" + classname + "\\" + courseID + ".txt";
	rewriteCourse(tmpCourse, directory1);
	//viet lai text file
	string directory = "Semester\\" + academicYear + "-" + Semestername + "\\" + academicYear + "-" + Semestername + ".txt";
	rewriteScheduleList(curSemester->numSchedule, curSemester->pSchedule, directory);
	directory = "Semester\\" + academicYear + "-" + Semestername + "\\" + classname + "\\" + classname + ".txt";
	rewriteCourseList(curSchedule->numCourse, pCourse, directory);
	y++;
	textColor(2);
	goToXY(x, y++); cout << "We have import scoreboard successfully " << success << " student(s) in " << dem << " student(s)!";
	goToXY(x, y++);
	system("pause");
	textColor(14);
}
void exportAttendanceList(Semester* pSemester)
{
	int x, y;
	string dir;
	Course* curCourse;
	while (true)
	{
		system("cls");
		x = 10; y = 5;
		goToXY(x, y++); cout << "Choose the course you want to export the attendance list"; y++;
		bool check = inputCourse(x, y, pSemester, curCourse, dir);
		if (curCourse)	break;
		if (check)	exportAttendanceList(pSemester);
		return;
	}
	//
	string linkcsv;
	goToXY(x, y++); cout << "Please enter the link of csv file: "; getline(cin, linkcsv, '\n'); y++;

	ofstream outcsv;
	outcsv.open(linkcsv);
	if (!outcsv.is_open())
	{
		textColor(4);
		goToXY(x, y++); cout << "Can not open file csv!" << endl;
		goToXY(x, y++); system("pause");
		textColor(14);
		return;
	}
	outcsv << "No,Student ID,Student name,";
	//
	int numStudent;
	Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	int numDay = 10;
	Date date = curCourse->dateStart;
	for (int i = 0; i < 10; i++)
	{
		if (cmpDate(date, curCourse->dateEnd) == 1)
		{
			outcsv << endl;
			numDay = i;
			break;
		}
		outcsv << date.year << "-" << date.month << "-" << date.day;
		if (cmpDate(date, curCourse->dateEnd) != 0)
			outcsv << ",";
		nextWeek(date);
	}
	sortStudentList(curCourse->pStudent);
	Student* prevStudent = nullptr;
	Student* curStudent = curCourse->pStudent;
	int no = 0;
	while (curStudent)
	{
		Student* cur = pStudent;
		while (cur)
		{
			if (cur->id == curStudent->id)
				break;
			cur = cur->pNext;
		}
		if (cur)
		{
			no++;
			outcsv << no << ",";
			outcsv << cur->id << ",";
			outcsv << cur->fullname << ",";
			for (int i = 0; i < numDay; i++)
			{
				outcsv << curStudent->attend[i];
				if (i < (numDay - 1))
				{
					outcsv << ',';
				}
			}
			outcsv << endl;
			prevStudent = curStudent;
			curStudent = curStudent->pNext;
		}
		else
		{
			curCourse->numStudent--;
			deleteStudent(prevStudent, curStudent, curCourse->pStudent);
		}
	}
	deleteStudentList(pStudent);
	outcsv.close();

	textColor(2);
	goToXY(x, y++); cout << "Export successfully!";
	goToXY(x, y++); system("pause");
	textColor(14);
}
void exportScoreboard(Semester* pSemester)
{
	int x, y;
	string dir;
	Course* curCourse;
	while (true)
	{
		system("cls");
		x = 10; y = 5;
		goToXY(x, y++); cout << "Choose the course you want to export the scoreboard"; y++;
		bool check = inputCourse(x, y, pSemester, curCourse, dir);
		if (curCourse)	break;
		if (check)	exportScoreboard(pSemester);
		return;
	}
	//
	string linkcsv;
	goToXY(x, y++); cout << "Please enter the link of csv file: "; getline(cin, linkcsv, '\n'); y++;

	ofstream outcsv;
	outcsv.open(linkcsv);
	if (!outcsv.is_open())
	{
		textColor(4);
		goToXY(x, y++); cout << "Can not open file csv!" << endl;
		goToXY(x, y++); system("pause");
		textColor(14);
		return;
	}
	outcsv << "No,Student ID,Student name,Midterm,Final,Bonus,Total" << endl;
	//
	int numStudent;
	Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	sortStudentList(curCourse->pStudent);
	Student* prevStudent = nullptr;
	Student* curStudent = curCourse->pStudent;
	int no = 0;
	while (curStudent)
	{
		Student* cur = pStudent;
		while (cur)
		{
			if (cur->id == curStudent->id)
				break;
			cur = cur->pNext;
		}
		if (cur)
		{
			no++;
			outcsv << no << ",";
			outcsv << cur->id << ",";
			outcsv << cur->fullname << ",";
			outcsv << curStudent->grade.midterm << ",";
			outcsv << curStudent->grade.final << ",";
			outcsv << curStudent->grade.bonus << ",";
			outcsv << curStudent->grade.total;
			outcsv << endl;
			prevStudent = curStudent;
			curStudent = curStudent->pNext;
		}
		else
		{
			curCourse->numStudent--;
			deleteStudent(prevStudent, curStudent, curCourse->pStudent);
		}
	}
	deleteStudentList(pStudent);
	outcsv.close();

	textColor(2);
	goToXY(x, y++); cout << "Export successfully!";
	goToXY(x, y++); system("pause");
	textColor(14);
}