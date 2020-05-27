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
		if (AcademicYear == cur->academicYear && Semestername==cur->semester)
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
		string dir="Semester\\"+academicYear+"-"+Semestername+"\\"+pSchedule->cla+"\\"+pSchedule->pCourse->courseID+".txt";
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
	curSemester->pSchedule =curSemester-> pSchedule->pNext;
	delete tmp;
	curSemester->numSchedule--;
	dir = "Semester\\" + academicYear + "-" + Semestername + "\\" + academicYear + "-" + Semestername + ".txt";
	rewriteScheduleList(curSemester->numSchedule, curSemester->pSchedule, dir);
}
void deleteSemester(string AcademicYear, string Semestername, int& numSemester, Semester*& pSemester)
{
	//delete directory va nhung cai p trong no
	Semester* curSemester = pSemester;
	while (curSemester!=nullptr &&( curSemester->academicYear != AcademicYear || curSemester->semester != Semestername))
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
void createAcademicYear(int& numSemester, Semester*& pSemester)
{
	system("cls");
	int x = 10, y = 5;
	goToXY(x, y++); cout << "Create academic year.";
	goToXY(x, y); cout << "Please enter the academic year: ";
	int tmpx = x;
	int tmpy = y;
	y++;
	string AcademicYear;
	getline(cin, AcademicYear, '\n');
	while (checkDuplicateAcademicYear(AcademicYear, pSemester))
	{
		goToXY(tmpx, tmpy); cout << "                                                                                                 ";
		goToXY(tmpx,tmpy); cout << "The academic year has already existed. Please enter another academic year: ";
		getline(cin, AcademicYear, '\n');
	}
	goToXY(x, y++); cout << "Please enter the number of semester: ";
	tmpx = x; tmpy = y - 1;
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
		tmpx = x; tmpy = y;
		string Semestername;
		getline(cin, Semestername, '\n');
		while (checkDuplicateSemester(AcademicYear, Semestername, pSemester))
		{
			goToXY(tmpx, tmpy); cout << "                                                                                ";
			goToXY(tmpx,tmpy); cout << "The semester name havs already existed. Enter another name: ";
			getline(cin, Semestername, '\n');
		}
		createSemester(AcademicYear, Semestername, numSemester,pSemester);
	}
	rewriteSemester(numSemester, pSemester);
	goToXY(x, y++); cout << "The academic year has been created.";
	system("pause");
}

void updateAcademicYear(int& numSemester, Semester*& pSemester)//con xoa semester
{
	system("cls");
	int x = 10, y = 5;
	goToXY(x, y++); cout << "Update academic year.";
	string academicYear;
	goToXY(x, y++); cout << "Please enter the academic year: ";
	int tmpx = x, tmpy = y;
	getline(cin, academicYear, '\n');
	while (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		goToXY(tmpx, tmpy); cout << "                                                                                              ";
		goToXY(tmpx, tmpy); cout << "The academic year is not available. Please enter another academic year: ";
		getline(cin, academicYear, '\n');
	}
	system("pause");
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "You choose academic year " << academicYear << endl;
	goToXY(x, y++); cout << "The academic year has the semester(s) below: " << endl;
	Semester* cur = pSemester;
	int dem=0;
	while (cur != nullptr)
	{
		if (cur->academicYear == academicYear)
		{
			dem++;
			goToXY(x, y++); cout << dem << ". " << cur->semester << endl;
		}
		cur = cur->pNext;
	}
	if (dem == 0) { goToXY(x, y++); cout << "The academic year has no semester." << endl; }
	system("pause");
	while (true)
	{
		system("cls"); x = 10; y = 5;
		goToXY(x, y++); cout << "We have 3 options: " << endl;
		goToXY(x, y++); cout << "1. Add a new semester." << endl;
		goToXY(x, y++); cout << "2. Delete an existing semester." << endl;
		goToXY(x, y++); cout << "0. Exit." << endl;
		goToXY(x, y++); cout << "Your choice: ";
		tmpx = x; tmpy = y;
		string yourChoice;
		int choice;
		getline(cin, yourChoice);
		bool check = convertStringToInt(yourChoice, choice);
		while (!check || (choice < 0 || choice >2))
		{
			goToXY(tmpx, tmpy); cout << "                                                            ";
			goToXY(tmpx, tmpy); cout << "Please enter from 0 to 2: ";
			getline(cin, yourChoice);
			check = convertStringToInt(yourChoice, choice);
		}
		if (choice == 0)
			break;
		else if (choice == 1)
		{
			//tao folder semester va cap nhat pSemester
			system("cls"); x = 10; y = 5;
			goToXY(x, y++); cout << "Add a new semester.";
			goToXY(x, y++); cout << "Please enter the name of semester: ";
			tmpx = x; tmpy = y;
			string Semestername;
			getline(cin, Semestername, '\n');
			bool t = checkDuplicateSemester(academicYear, Semestername, pSemester);
			while (t)
			{
				goToXY(tmpx, tmpy); cout << "                                                    ";
				goToXY(tmpx, tmpy+1); cout << "                                                    ";
				goToXY(tmpx, tmpy+2); cout << "                                                    ";
				goToXY(tmpx, tmpy+3); cout << "                                                    ";
				goToXY(tmpx, tmpy+4); cout << "                                                    ";
				goToXY(tmpx, tmpy); cout << "The name of semester has existed." << endl;
				goToXY(tmpx, tmpy+1); cout << "Do you want to " << endl;
				goToXY(tmpx, tmpy+2); cout << "0. End adding semester." << endl;
				goToXY(tmpx, tmpy+3); cout << "1. Add another semester." << endl;
				int choice2;
				goToXY(tmpx, tmpy+4); cout << "Your choice: ";
				string yourchoice;
				getline(cin, yourchoice);
				bool check = convertStringToInt(yourchoice, choice2);
				while ( !check || (choice2 != 0 && choice2 != 1))
				{
					goToXY(tmpx, tmpy + 5); cout << "                                                          ";
					goToXY(tmpx, tmpy + 5); cout << "Please enter 0 or 1: ";
					getline(cin, yourchoice);
					check = convertStringToInt(yourchoice, choice2);
				}
				if (choice2 == 0)
					break;
				else
				{
					system("cls"); x = 10; y = 5;
					goToXY(x, y ++); cout << "Add a new semester.";
					goToXY(x, y ++); cout << "Please enter the semester name again: ";
					getline(cin, Semestername, '\n');
				}
				t = checkDuplicateSemester(academicYear, Semestername, pSemester);
			}
			if (t == true);
			else
			{
				dem++;
				createSemester(academicYear, Semestername, numSemester, pSemester);
				goToXY(x, y++); cout << "The semester has successfully added." << endl;
				system("pause");
			}
		}
		else
		{
			system("cls"); int x = 10; y = 5;
			goToXY(x, y++); cout << "Delete a semester.";
			// toi cho nay
			if (dem == 0)
			{
				goToXY(x, y++); cout << "There are no semester to delete." << endl;
			}
			else {
				goToXY(x, y++); cout << "Please enter the name of semester you want to delete: ";
				string deleteSemestername;
				getline(cin, deleteSemestername, '\n');
				tmpx = x; tmpy = y-1;
				while (!checkDuplicateSemester(academicYear, deleteSemestername, pSemester))
				{
					goToXY(tmpx, tmpy); cout << "                                                                                          ";
					goToXY(tmpx, tmpy); cout << "You have enter a wrong name. Please enter again: ";
					getline(cin, deleteSemestername, '\n');
				}
				dem--;
				deleteSemester(academicYear, deleteSemestername, numSemester, pSemester);
				goToXY(x, y++); cout << "The semester has been remove successfully." << endl;
				system("pause");
			}
		}
	}
	rewriteSemester(numSemester, pSemester);
	system("pause");
}
void deleteAcademicYear(int& numSemester, Semester*& pSemester)
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
}
void viewAcademicYear(string academicYear, int numSemester, Semester* pSemester)
{
	system("cls"); int x = 10, y = 5;
	int dem = 0;
	Semester* curSemester = pSemester;
	while (curSemester!=nullptr)
	{
		if (curSemester->academicYear == academicYear)
			dem++;
		curSemester = curSemester->pNext;
	}
	goToXY(x, y++); cout << "The academic " << academicYear << " has "<<dem<<" semester(s) below: ";
	curSemester = pSemester;
	while (curSemester)
	{
		if (curSemester->academicYear == academicYear)
		{
			goToXY(x, y++); cout << curSemester->semester;
		}
		curSemester = curSemester->pNext;
	}
	goToXY(x, y++);
	system("pause");
}
void sortSemesterList(Semester *&pSemester)
{
	for (Semester* curI = pSemester; curI != nullptr; curI = curI->pNext)
		for (Semester* curJ = curI->pNext; curJ != nullptr; curJ = curJ->pNext)
			if (curI->academicYear > curJ->academicYear)
			{
				swap(curI->academicYear, curJ->academicYear);
				swap(curI->semester, curJ->semester);
			}
			else if(curI->academicYear==curJ->academicYear)
				if (curI->semester > curJ->semester)
				{
					swap(curI->semester, curJ->semester);
				}
}
void viewallSemester() {
	system("cls"); int x = 10, y = 5;
	int tmpnum=0;
	Semester* tmppSemester=nullptr;
	loadSemester(tmpnum, tmppSemester);
	sortSemesterList(tmppSemester);
	Semester* cur = tmppSemester;
	goToXY(x, y++); cout << "All the semester we have: ";
	while (cur)
	{
		goToXY(x, y++); cout << cur->academicYear << " - " << cur->semester << endl;
		cur = cur->pNext;
	}
	goToXY(x, y++);
	deleteSemesterList(tmppSemester);
	system("pause");
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
	goToXY(x, y++); cout << "Import a course from csv file." << endl;
	system("pause");
	viewallSemester();
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "Import a course from csv file.";
	goToXY(x, y++); cout << "Please enter the academic year: ";
	string academicYear;
	getline(cin, academicYear, '\n');
	while (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		goToXY(x, y); cout << "                                                                                                   ";
		goToXY(x, y); cout << "The academic year is not existed. Please enter another academic year: ";
		getline(cin, academicYear, '\n');
	}
	y++;
	system("pause");
	viewAcademicYear(academicYear, numSemester, pSemester);
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "Import a course from csv file.";
	goToXY(x, y++); cout << "Please enter the semester: ";
	string Semestername;
	getline(cin, Semestername, '\n');
	while (!checkDuplicateSemester(academicYear, Semestername, pSemester))
	{
		goToXY(x, y); cout << "                                                                                                  ";
		goToXY(x, y); cout << "The semester is not existed. Please enter another semester: ";
		getline(cin, Semestername, '\n');
	}
	y++;
	goToXY(x, y++); cout << "We already have class(es) below: " << endl;
	int numClass=0;
	Class* pClass=nullptr;
	loadClass(numClass, pClass);
	Class* cur = pClass;
	while (cur != nullptr)
	{
		goToXY(x, y++); cout << cur->name << endl;
		cur = cur->pNext;
	}
	deleteClassList(pClass);
	goToXY(x, y++); cout << "Please enter the class: ";
	string classname;
	getline(cin, classname, '\n');
	while (!checkExistingClass(classname))
	{
		goToXY(x, y); cout << "                                                                                              ";
		goToXY(x, y); cout << "The class is not available. Please enter another class: ";
		getline(cin, classname, '\n');
	}
	y++;
	if (!checkExistingClassInSemester(classname,academicYear,Semestername, pSemester))
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
	Course* pCourse = curSchedule->pCourse;
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "Import a course from csv file.";
	goToXY(x, y++); cout << "Please enter the link of csv file: ";
	string linkcsv;
	getline(cin, linkcsv, '\n');
	ifstream in;
	in.open(linkcsv);
	while (!in.is_open())
	{
		system("cls"); x = 10; y = 5;
		int tmpx = x, tmpy = y;
		goToXY(tmpx, tmpy++); cout << "Can not open csv file.";
		goToXY(tmpx, tmpy++); cout << "Do you want to: ";
		goToXY(tmpx, tmpy++); cout << "1. Enter another link.";
		goToXY(tmpx, tmpy++); cout << "0. Exit.";
		goToXY(tmpx, tmpy); cout << "Your choice: ";
		int choice;
		string yourchoice;
		getline(cin, yourchoice);
		bool check = convertStringToInt(yourchoice, choice);
		while (!check || (choice != 0 && choice != 1))
		{
			goToXY(tmpx, tmpy); cout << "                                                                    ";
			goToXY(tmpx, tmpy); cout << "Please enter 0 or 1: ";
			getline(cin, yourchoice);
			check = convertStringToInt(yourchoice, choice);
		}
		if (choice == 0)
			return;
		else
		{
			tmpy++;
			goToXY(tmpx, tmpy++); cout << "Please enter csv link: ";
			getline(cin, linkcsv, '\n');
			in.open(linkcsv);
		}
	}
	y++;
	//toi cho nay thi check on, con 2 ham o tren chua viet thoi
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
				tmpCourse = pCourse;
				while (tmpCourse->pNext != nullptr)
					tmpCourse = tmpCourse->pNext;
				tmpCourse->pNext = new Course;
				tmpCourse = tmpCourse->pNext;
				curSchedule->numCourse++;
			}
		}
		tmpCourse->pNext = nullptr;
		tmpCourse->courseID = courseID;
		getline(in,tmpCourse->courseName,',');
		string lecturerName;
		getline(in, lecturerName,',');
		string lecturerDegree;
		getline(in, lecturerDegree, ',');
		string lecturerGender;
		getline(in, lecturerGender, ',');
		string lecturerAccount;
		getline(in, lecturerAccount,',');
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
		//neu lecturer trung username ma khac ten thi sao???
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
		loadStudent(tmpCourse->numStudent, tmpCourse->pStudent,classname);
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
	string directory="Semester\\"+academicYear+"-"+Semestername+"\\"+academicYear+"-"+Semestername+".txt";
	rewriteScheduleList(curSemester->numSchedule, curSemester->pSchedule, directory);
	directory = "Semester\\" + academicYear + "-" + Semestername + "\\" + classname + "\\" + classname + ".txt";
	rewriteCourseList(curSchedule->numCourse, pCourse, directory);
	in.close();
	system("cls"); x = 10; y = 6;
	goToXY(x, y++); cout << "Import successfully.";
	goToXY(x, y++);
	system("pause");
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

void manuallyAddCourse(int& numSemester, Semester*& pSemester)
{
	cout << "We have the following semester: " << endl;
	viewallSemester();
	cout << "Please enter the academic year: ";
	string academicYear;
	getline(cin, academicYear, '\n');
	while (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		cout << "The academic year is not existed. Please enter another academic year: ";
		getline(cin, academicYear, '\n');
	}
	cout << "We already have the following semester." << endl;
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
	{
		curSchedule = curSchedule->pNext;
	}
	Course* pCourse = curSchedule->pCourse;
	cout << "Please enter course ID: ";
	string courseID;
	getline(cin, courseID, '\n');
	Course* tmpCourse = pCourse;
	if (pCourse == nullptr)
	{
		pCourse = new Course;
		tmpCourse = pCourse;
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
			tmpCourse = pCourse;
			while (tmpCourse->pNext != nullptr)
				tmpCourse = tmpCourse->pNext;
			tmpCourse->pNext = new Course;
			tmpCourse = tmpCourse->pNext;
			curSchedule->numCourse++;
		}
	}
	tmpCourse->pNext = nullptr;
	tmpCourse->courseID = courseID;
	cout << "Please enter course name: ";
	getline(cin, tmpCourse->courseName, '\n');
	cout << "Please enter lecturer username: ";
	string lecturerAccount;
	getline(cin, lecturerAccount, '\n');
	if (!checkExistingLecturer(lecturerAccount))
	{
		cout << "This is a new lecturer. We need to add more information." << endl;
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
		cout << "Please enter lecturer name: ";
		string lecturerName;
		getline(cin, lecturerName, '\n');
		curLecturer->fullname = lecturerName;
		cout << "Please enter lecturer degree: ";
		string lecturerDegree;
		getline(cin, lecturerDegree, '\n');
		curLecturer->degree = lecturerDegree;
		cout << "Please enter lecturer gender (0 for male and 1 for female):";
		cin >> curLecturer->gender;
		curLecturer->password = lecturerAccount;
		curLecturer->pNext = nullptr;
		numLecturer++;
		rewriteLecturer(numLecturer, pLecturer);
		deleteLecturerList(pLecturer);
	}
	cout << "Input date start. " << endl;
	inputDate(tmpCourse->dateStart.year, tmpCourse->dateStart.month, tmpCourse->dateStart.day);
	cout << "Input date end: " << endl;
	inputDate(tmpCourse->dateEnd.year, tmpCourse->dateEnd.month, tmpCourse->dateEnd.day);
	cout << "Day of week(e.g: 2, 3, 4, 5, 6, 7, 8): ";
	int dayOfWeek;
	cin >> dayOfWeek;
	while (dayOfWeek <= 1 || dayOfWeek > 8)
	{
		cout << "Please enter from 2 to 8: ";
		cin >> dayOfWeek;
	}
	createdayOfWeek(dayOfWeek, tmpCourse->day);
	cout << "Start hour: ";
	cin >> tmpCourse->timeStart.hour;
	cout << "Start minute: ";
	cin >> tmpCourse->timeStart.minute;
	cout << "End hour: ";
	cin >> tmpCourse->timeEnd.hour;
	cout << "End minute: ";
	cin >> tmpCourse->timeEnd.minute;
	cin.ignore();
	cout << "Room: ";
	getline(cin, tmpCourse->room, '\n');
	//neu lecturer trung username ma khac ten thi sao???
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
	rewriteCourseList(curSchedule->numCourse, pCourse, directory);
}

bool checkExistingCourse(int numSemester, Semester* pSemester, string academicYear, string Semestername, string classname, string courseID)
{
	Semester* cur = pSemester;
	while (cur != nullptr && (cur->academicYear != academicYear || cur->semester != Semestername))
	{
		cur = cur->pNext;
	}
	Schedule* tmp = cur->pSchedule;
	while (tmp != nullptr && (tmp->cla!=classname))
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
	goToXY(x, y++); cout << "Import scoreboard from csv file." << endl;
	system("pause");
	viewallSemester();
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "Import scoreboard from csv file." << endl;
	goToXY(x, y++); cout << "Please enter the academic year: ";
	string academicYear;
	getline(cin, academicYear, '\n');
	while (!checkDuplicateAcademicYear(academicYear, pSemester))
	{
		goToXY(x, y); cout << "                                                                                                 ";
		goToXY(x, y); cout << "The academic year is not existed. Please enter another academic year: ";
		getline(cin, academicYear, '\n');
	}
	system("pause");
	viewAcademicYear(academicYear, numSemester, pSemester);
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "Import scoreboard from csv file." << endl;
	goToXY(x, y++); cout << "Please enter the semester: ";
	string Semestername;
	getline(cin, Semestername, '\n');
	while (!checkDuplicateSemester(academicYear, Semestername, pSemester))
	{
		goToXY(x, y); cout << "                                                                                                   ";
		goToXY(x, y); cout << "The semester is not existed. Please enter another semester: ";
		getline(cin, Semestername, '\n');
	}
	system("pause");
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "Import scoreboard from csv file." << endl;
	goToXY(x, y++);  cout << "Please enter the class: ";
	string classname;
	getline(cin, classname, '\n');
	while (!checkExistingClass(classname))
	{
		goToXY(x, y); cout << "                                                                                               ";
		goToXY(x, y); cout << "The class is not available. Please enter another class: ";
		getline(cin, classname, '\n');
	}
	y++;
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
	if (curSchedule->numCourse == 0)
	{
		goToXY(x, y++); cout << "The class has not had any course." << endl;
	}
	system("pause");
	Course* pCourse = curSchedule->pCourse;
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "Import scoreboard from csv file." << endl;
	goToXY(x, y++); cout << "Please enter course ID: ";
	string courseID;
	getline(cin, courseID, '\n');
	while (!checkExistingCourse(numSemester, pSemester, academicYear, Semestername, classname, courseID))
	{
		goToXY(x, y); cout << "                                                                                         ";
		goToXY(x, y); cout << "The course is not existed. Please enter another course: ";
		getline(cin, courseID, '\n');
	}
	y++;
	Course* tmpCourse = pCourse;
	while (tmpCourse != nullptr && tmpCourse->courseID != courseID)
	{
		tmpCourse = tmpCourse->pNext;
	}
	system("pause");
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "Import scoreboard from csv file.";
	goToXY(x, y++); cout << "Please enter the link of csv file: ";
	string linkcsv;
	getline(cin, linkcsv, '\n');
	ifstream in;
	in.open(linkcsv);
	while (!in.is_open())
	{
		system("cls"); x = 10; y = 5;
		int tmpx = x, tmpy = y;
		goToXY(tmpx, tmpy++); cout << "Can not open csv file.";
		goToXY(tmpx, tmpy++); cout << "Do you want to: ";
		goToXY(tmpx, tmpy++); cout << "1. Enter another link.";
		goToXY(tmpx, tmpy++); cout << "0. Exit.";
		goToXY(tmpx, tmpy); cout << "Your choice: ";
		int choice;
		string yourchoice;
		getline(cin, yourchoice);
		bool check = convertStringToInt(yourchoice, choice);
		while (!check || (choice != 0 && choice != 1))
		{
			goToXY(tmpx, tmpy); cout << "                                                                    ";
			goToXY(tmpx, tmpy); cout << "Please enter 0 or 1: ";
			getline(cin, yourchoice);
			check = convertStringToInt(yourchoice, choice);
		}
		if (choice == 0)
			return;
		else
		{
			tmpy++;
			goToXY(tmpx, tmpy++); cout << "Please enter csv link: ";
			getline(cin, linkcsv, '\n');
			in.open(linkcsv);
		}
	}
	system("pause");
	Student *pStudent= tmpCourse->pStudent;
	int dem = 0;
	int success = 0;
	in.ignore(100, '\n');
	while (!in.eof())
	{
		in.ignore(100, ',');
		int studentID;
		in>>studentID;
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
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "We have import scoreboard successfully " << success << " student(s) in " << dem << " student(s).";
	goToXY(x, y++);
	system("pause");
}

void exportAttendanceList(Semester *pSemester)
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
		if (check)	viewCourseAttendance(pSemester);
		return;
	}
	//
	cout << "Please enter the link of csv file." << endl;
	string linkcsv;
	getline(cin, linkcsv, '\n');
	ofstream outcsv;
	outcsv.open(linkcsv);
	if (!outcsv.is_open())
	{
		cout << "Can not open file csv." << endl;
		return;
	}
	outcsv << "No,Student ID,Student name,";
	//
	int numStudent;
	Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	resizeConsole(1100, 700);
	y++; goToXY(x + 40, y++);
	int numDay = 10;
	Date date = curCourse->dateStart;
	for (int i = 0; i < 10; i++)
	{
		goToXY(x + 23 + i * 10, y);
		nextWeek(date, i);
		if (cmpDate(date, curCourse->dateEnd))
		{
			outcsv << endl;
			numDay = i;
			break;
		}
		outcsv << date.year << "-" << date.month << "-" << date.day;
		Date tmp = date;
		nextWeek(tmp, 1);
		if (!cmpDate(tmp, curCourse->dateEnd))
			outcsv << ",";
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
	y++;
	goToXY(x, y++); system("pause");
	deleteStudentList(pStudent);
	resizeConsole(1000, 700);
	outcsv.close();
}

void exportscoreboard(Semester* pSemester)
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
		if (check)	viewCourseAttendance(pSemester);
		return;
	}
	//
	cout << "Please enter the link of csv file." << endl;
	cout << "Notice that the order of csv file will be: No,Student ID,Student name,Midterm,Final,Bonus,Total" << endl;
	string linkcsv;
	getline(cin, linkcsv, '\n');
	ofstream outcsv;
	outcsv.open(linkcsv);
	if (!outcsv.is_open())
	{
		cout << "Can not open file csv." << endl;
		return;
	}
	outcsv << "No,Student ID,Student name,Midterm,Final,Bonus,Total"<<endl;
	//
	int numStudent;
	Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	resizeConsole(1100, 700);
	y++; goToXY(x + 40, y++);
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
	y++;
	goToXY(x, y++); system("pause");
	deleteStudentList(pStudent);
	resizeConsole(1000, 700);
	outcsv.close();
}