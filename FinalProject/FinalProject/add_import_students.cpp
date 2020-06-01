#include "function.h"

void create_password(Date dob, string& s)
{
	s = "";
	while (dob.year > 0)
	{
		int k = dob.year % 10;
		char c = int('0') + k;
		s = c + s;
		dob.year = dob.year / 10;
	}
	char c = int('0') + dob.month / 10;
	s = s + c;
	c = int('0') + dob.month % 10;
	s = s + c;
	c = int('0') + dob.day / 10;
	s = s + c;
	c = int('0') + dob.day % 10;
	s = s + c;
}
bool check_id(int ID, Student* pStudent)
{
	if (pStudent == nullptr) return true;
	Student* tmp = pStudent;
	bool t = true;
	while (tmp != nullptr)
	{
		if (tmp->id == ID)
		{
			t = false;
			break;
		}
		tmp = tmp->pNext;
	}
	return t;
}
bool checkValidDate(Date day)
{
	if (day.month == 1 || day.month == 3 || day.month == 5 || day.month == 7 || day.month == 8 || day.month || 10 || day.month == 12)
	{
		if (day.day > 0 && day.day <= 31)
			return true;
		else return false;
	}
	else if (day.month == 4 || day.month == 6 || day.month == 9 || day.month == 11)
	{
		if (day.day > 0 && day.day <= 30)
			return true;
		else return false;
	}
	if (day.day > 0 && day.day <= 28) return true;
	else if (day.day == 29)
	{
		if (day.year % 4 != 0 || (day.year % 100 == 0 && day.year % 400 != 0))
			return false;
		return true;
	}
	return false;
}
void manually_add_student_to_class()//chua kt ngay thang nam
{
	int x;
	int y;
	system("cls");
	x = 10; y = 5;
	//input class
	int numClass = 0;
	Class* pClass = nullptr;
	loadClass(numClass, pClass);
	Class* cur = pClass;
	goToXY(x, y++); cout << "Manually add a student to a class.";
	goToXY(x, y++); cout << "Please choose the class you want to add in.";
	goToXY(x, y++); cout << " We have " << numClass << " class(es) below :";
	x += 3; y++;
	for (int i = 0; i < numClass; ++i)
	{
		goToXY(x, y++); cout << i + 1 << "." << cur->name << endl;
		cur = cur->pNext;
	}
	x -= 3; y++;
	goToXY(x, y++); cout << "Enter the order of class you want: ";
	string tmpchoice;
	int n = 0;
	getline(cin, tmpchoice);
	bool check = convertStringToInt(tmpchoice, n);
	while (!check || (n <= 0 || n > numClass))
	{
		goToXY(x, y++); cout << "Please enter a number from 1 to " << numClass << ": ";
		getline(cin, tmpchoice);
		check = convertStringToInt(tmpchoice, n);
	}
	cur = pClass;
	for (int i = 0; i < n - 1; ++i)
		cur = cur->pNext;
	system("cls"); x = 10; y = 5;
	goToXY(x, y++); cout << "Manually add a student to a class.";
	goToXY(x, y++); cout << "You choose class " << cur->name << "." << endl;
	//check id
	Student* pAllStudent = nullptr;
	int numAllStudent = 0;
	loadStudent(numAllStudent, pAllStudent, "Student");
	goToXY(x, y++); cout << "Please enter student ID: ";
	string tmpID;
	getline(cin, tmpID);
	int ID;
	check = convertStringToInt(tmpID, ID);
	if (!check || check_id(ID, pAllStudent) == false) y++;
	while (!check || check_id(ID, pAllStudent) == false) {
		goToXY(x, y - 1); cout << "                                                                                                 ";
		if (!check) {
			goToXY(x, y - 1); cout << "Please enter a number: ";
		}
		else
		{
			goToXY(x, y - 1); cout << "The ID has been used. Please enter another ID: ";
		}
		getline(cin, tmpID);
		check = convertStringToInt(tmpID, ID);
	}
	//cap nhat file cua lop
	Student* pStudent = nullptr;
	int numStudent = 0;
	loadStudent(numStudent, pStudent, cur->name);
	Student* tmp = pStudent;
	if (tmp == nullptr)
	{
		pStudent = new Student;
		tmp = pStudent;
	}
	else {
		for (int i = 0; i < numStudent - 1; ++i)
			tmp = tmp->pNext;
		tmp->pNext = new Student;
		tmp = tmp->pNext;
	}
	tmp->pNext = nullptr;
	tmp->id = ID;
	tmp->cla = cur->name;
	tmp->status = 1;
	goToXY(x, y++); cout << "Enter full name of the student: ";
	getline(cin, tmp->fullname);
	goToXY(x, y++); cout << "Enter date of birth: " << endl;
	goToXY(x, y++); cout << "Day: ";
	string dobDay;
	getline(cin, dobDay);
	check = convertStringToInt(dobDay, tmp->dob.day);
	while (!check && (tmp->dob.day <= 0 || tmp->dob.day > 31))
	{
		goToXY(x, y++); cout << "Please enter a positive integer: ";
		getline(cin, dobDay);
		check = convertStringToInt(dobDay, tmp->dob.day);
	}
	goToXY(x, y++); cout << "Month: ";
	string dobMonth;
	getline(cin, dobMonth);
	check = convertStringToInt(dobMonth, tmp->dob.month);
	while (!check && (tmp->dob.month <= 0 || tmp->dob.month > 12))
	{
		goToXY(x, y++); cout << "Please enter a positive integer: ";
		getline(cin, dobMonth);
		check = convertStringToInt(dobMonth, tmp->dob.month);
	}
	goToXY(x, y++); cout << "Year: ";
	string dobYear;
	getline(cin, dobYear);
	check = convertStringToInt(dobYear, tmp->dob.year);
	while (!check)
	{
		goToXY(x, y++); cout << "Please enter a positive integer: ";
		getline(cin, dobYear);
		check = convertStringToInt(dobYear, tmp->dob.year);
	}
	while (!checkValidDate(tmp->dob))
	{
		textColor(4);
		goToXY(x, y++); cout << "The date does not exist. Please enter another date: ";
		textColor(14);
		goToXY(x, y++); cout << "Day: ";
		string dobDay;
		getline(cin, dobDay);
		check = convertStringToInt(dobDay, tmp->dob.day);
		while (!check && (tmp->dob.day <= 0 || tmp->dob.day > 31))
		{
			goToXY(x, y++); cout << "Please enter a positive integer: ";
			getline(cin, dobDay);
			check = convertStringToInt(dobDay, tmp->dob.day);
		}
		goToXY(x, y++); cout << "Month: ";
		string dobMonth;
		getline(cin, dobMonth);
		check = convertStringToInt(dobMonth, tmp->dob.month);
		while (!check && (tmp->dob.month <= 0 || tmp->dob.month > 12))
		{
			goToXY(x, y++); cout << "Please enter a positive integer: ";
			getline(cin, dobMonth);
			check = convertStringToInt(dobMonth, tmp->dob.month);
		}
		goToXY(x, y++); cout << "Year: ";
		string dobYear;
		getline(cin, dobYear);
		check = convertStringToInt(dobYear, tmp->dob.year);
		while (!check && (tmp->dob.year <= 0))
		{
			goToXY(x, y++); cout << "Please enter a positive integer: ";
			getline(cin, dobYear);
			check = convertStringToInt(dobYear, tmp->dob.year);
		}
	}
	create_password(tmp->dob, tmp->password);
	tmp->grade.midterm = -1; tmp->grade.final = -1; tmp->grade.bonus = -1; tmp->grade.total = -1;
	for (int i = 0; i < 10; ++i)
		tmp->attend[i] = -1;
	numStudent++;
	//cap nhat student.txt
	Student* tmp1 = pAllStudent;
	if (tmp1 == nullptr)
	{
		pAllStudent = new Student;
		tmp1 = pAllStudent;
	}
	else {
		for (int i = 0; i < numAllStudent - 1; ++i)
			tmp1 = tmp1->pNext;
		tmp1->pNext = new Student;
		tmp1 = tmp1->pNext;
	}
	(*tmp1) = (*tmp);
	numAllStudent++;
	goToXY(x, y++); cout << "Do you want to add this student to class " << cur->name << "? 1 to confirm, 0 for exist: ";
	getline(cin, tmpchoice);
	int choice;
	check = convertStringToInt(tmpchoice, choice);
	while (!check || (choice != 0 && choice != 1))
	{
		goToXY(x, y++); cout << "Please enter 0 or 1: ";
		getline(cin, tmpchoice);
		check = convertStringToInt(tmpchoice, choice);
	}
	if (choice == 1) {
		rewriteStudent(numStudent, pStudent, cur->name);
		rewriteStudent(numAllStudent, pAllStudent, "Student");
		textColor(2);
		goToXY(x, y++); cout << "The student has been added to system!";
	}
	else
	{
		textColor(2);
		goToXY(x, y++); cout << "Cancel adding student!";
	}
	deleteStudentList(pStudent);
	deleteClassList(pClass);
	deleteStudentList(pAllStudent);
	goToXY(x, y++); system("pause");
	textColor(14);
}
void import_class()
{
	int x;
	int y;
	system("cls");
	x = 10; y = 5;
	goToXY(x, y++); cout << "Import a class from csv file.";
	goToXY(x, y++); cout << "Please enter the name of the class: ";
	//nhap ten class
	string classname;
	getline(cin, classname);
	bool t = true;
	int numClass = 0;
	Class* pClass = nullptr;
	loadClass(numClass, pClass);
	Class* tmpClass = pClass;
	while (tmpClass != nullptr)
	{
		if (tmpClass->name == classname)
			t = false;
		tmpClass = tmpClass->pNext;
	}
	deleteClassList(pClass);
	if (t == true)
	{
		goToXY(x, y++); cout << "This is a new class.";
	}
	goToXY(x, y++); cout << "You choose class " << classname << ".";
	goToXY(x, y++); cout << "Please enter the link of csv file: ";
	string csv;
	getline(cin, csv);
	ifstream in;
	in.open(csv);
	while (!in.is_open())
	{
		y++;
		textColor(4);
		goToXY(x, y++); cout << "Error when opening the csv file.";
		textColor(14);
		goToXY(x, y++); cout << "Do you want to:";
		goToXY(x, y++); cout << "0.Exit.";
		goToXY(x, y++); cout << "1. Enter another link.";
		goToXY(x, y++); cout << "Your choice: ";
		string yourChoice;
		int choice;
		getline(cin, yourChoice);
		bool check = convertStringToInt(yourChoice, choice);
		while (!check || (choice != 0 && choice != 1))
		{
			goToXY(x, y++); cout << "Please enter 0 or 1: ";
			getline(cin, yourChoice);
			check = convertStringToInt(yourChoice, choice);
		}
		if (choice == 0)
		{
			y++;
			goToXY(x, y++); system("pause");
			textColor(14);
			return;
		}
		goToXY(x, y++); cout << "Please enter csv link: ";
		getline(cin, csv);
		in.open(csv);
	}
	string filename = classname + ".txt";
	ofstream out;
	if (t == true) {
		out.open(filename);
		if (!out.is_open())
		{
			textColor(4);
			goToXY(x, y++);  cout << "Error in opening the class file.";
			goToXY(x, y++);  system("pause");
			textColor(14);
			return;
		}
		out << 0;
		out.close();
	}
	int success = 0;
	int dem = 0;
	Student* pStudent = nullptr;
	int numStudent = 0;
	loadStudent(numStudent, pStudent, classname);
	Student* cur = pStudent;
	if (cur != nullptr)
	{
		while (cur->pNext != nullptr)
		{
			cur = cur->pNext;
		}
	}
	int numStudent1 = 0;
	Student* pStudent1 = nullptr;
	loadStudent(numStudent1, pStudent1, "Student");
	Student* cur1 = pStudent1;
	if (cur1 != nullptr)
	{
		while (cur1->pNext != nullptr)
		{
			cur1 = cur1->pNext;
		}
	}
	in.ignore(1000, '\n');
	while (!in.eof())
	{
		in.ignore(100, ',');
		if (in.eof())
			break;
		int ID;
		in >> ID;
		if (!check_id(ID, pStudent1))
		{
			dem++;
			in.ignore();
			string lastname;
			getline(in, lastname, ',');
			string firstname;
			getline(in, firstname, ',');
			int year;
			in >> year;
			in.ignore();
			int month;
			in >> month;
			in.ignore();
			int day;
			in >> day;
			in.ignore();
		}
		else
		{
			if (pStudent == nullptr)
			{
				pStudent = new Student;
				pStudent->pNext = nullptr;
				cur = pStudent;
				success = 1;
				numStudent = 1;
				dem++;
				cur->id = ID;
			}
			else
			{
				cur->pNext = new Student;
				cur = cur->pNext;
				cur->pNext = nullptr;
				success++;
				dem++;
				numStudent++;
				cur->id = ID;
			}
			if (pStudent1 == nullptr)
			{
				pStudent1 = new Student;
				pStudent1->pNext = nullptr;
				cur1 = pStudent1;
				numStudent1 = 1;
				cur->id = ID;
			}
			else
			{
				cur1->pNext = new Student;
				cur1 = cur1->pNext;
				cur1->pNext = nullptr;
				numStudent1++;
				cur1->id = ID;
			}
			in.ignore(100, ',');
			string lastname;
			getline(in, lastname, ',');
			string firstname;
			getline(in, firstname, ',');
			cur->fullname = lastname + " " + firstname;
			cur1->fullname = cur->fullname;
			in >> cur->dob.year;
			cur1->dob.year = cur->dob.year;
			in.ignore();
			in >> cur->dob.month;
			cur1->dob.month = cur->dob.month;
			in.ignore();
			in >> cur->dob.day;
			cur1->dob.day = cur->dob.day;
			in.ignore();
			cur->status = 1;
			cur1->status = 1;
			cur->cla = classname;
			cur1->cla = cur->cla;
			create_password(cur->dob, cur->password);
			cur1->password = cur->password;
		}
	}
	in.close();
	rewriteStudent(numStudent, pStudent, classname);
	rewriteStudent(numStudent1, pStudent1, "Student");
	//update class.txt
	int numClass1 = 0;
	Class* pClass1 = nullptr;
	loadClass(numClass1, pClass1);
	if (t == true)
	{
		numClass1++;
		if (pClass1 == nullptr)
		{
			pClass1 = new Class;
			pClass1->name = classname;
			pClass1->pNext = nullptr;
			pClass1->pStudent = nullptr;
		}
		else
		{
			Class* temp1 = pClass1;
			while (temp1->pNext != nullptr)
				temp1 = temp1->pNext;
			temp1->pNext = new Class;
			temp1 = temp1->pNext;
			temp1->pNext = nullptr;
			temp1->name = classname;
			temp1->pStudent = nullptr;
		}
		rewriteClass(numClass1, pClass1);
	}
	//
	textColor(2);
	goToXY(x, y++); cout << "We have import " << success << " student(s) successfully in " << dem << " student(s)!";
	if (dem > success)
	{
		textColor(4);
		goToXY(x, y++); cout << dem - success << " students failed because of existing id!";
	}
	deleteClassList(pClass1);
	deleteStudentList(pStudent);
	deleteStudentList(pStudent1);
	goToXY(x, y++); system("pause");
	textColor(14);
}
void addStudentIntoCourse(Semester*& pSemester) {
	int x, y;
	string dir;
	Course* curCourse;
	while (true)
	{
		system("cls");
		x = 10; y = 5;
		goToXY(x, y++); cout << "Choose the course you want to add the students"; y++;
		bool check = inputCourse(x, y, pSemester, curCourse, dir);
		if (curCourse)	break;
		if (check)	addStudentIntoCourse(pSemester);
		return;
	}

	int numStudent;
	Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	y++; goToXY(x, y++); cout << "Enter student's ID to enroll: "; y++;
	int temp;
	string tmp;
	getline(cin, tmp);
	if (!convertStringToInt(tmp, temp))
		temp = -1;
	Student* prevStudent = nullptr;

	// check if the student has already in the course
	if (check_id(temp, curCourse->pStudent) == false)
	{
		textColor(4);
		goToXY(x, ++y); cout << "This student has already enrolled in this course.";
		goToXY(x, ++y); system("pause");
		textColor(14);
		return;
	}

	// check if the student is in the system
	Student* cur = pStudent;
	while (cur)
	{
		if (cur->id == temp)
			break;
		cur = cur->pNext;
	}

	// if yes
	if (cur)
	{
		goToXY(x, ++y); cout << "Student with ID " << cur->id << "'s information: ";
						cout << cur->fullname; cout << " in class "; cout << cur->cla << endl; y++;
		goToXY(x, ++y); cout << "Do you want to enroll this student into this course? YES (1) / NO (0)" << endl; 
		int choice;
		goToXY(x, ++y); cout << "Enter your choice: ";
		do {
			clearLine(x + 19, y);
			goToXY(x + 19, y); getline(cin, tmp);
		} while (!convertStringToInt(tmp, choice));
		y++;
		if (choice == 1) {
			Student* curStudent = curCourse->pStudent;
			if (curStudent == nullptr)
			{
				pStudent = new Student;
				curStudent = pStudent;
			}
			else {
				for (int i = 0; i < curCourse->numStudent - 1; ++i)
					curStudent = curStudent->pNext;
				curStudent->pNext = new Student;
				curStudent = curStudent->pNext;
			}
			curStudent->pNext = nullptr;
			curStudent->id = temp;
			curStudent->grade.bonus = 0, curStudent->grade.final = 0, curStudent->grade.midterm = 0;
			curStudent->grade.total = curStudent->grade.bonus * 0.3 + curStudent->grade.final * 0.4 + curStudent->grade.midterm * 0.3;
			for (int j = 0; j < 10; ++j) {
				curStudent->attend[j] = 0;
			}
			++curCourse->numStudent;
			textColor(2);
			goToXY(x, ++y); cout << "Student has been added to the course." << endl;
			goToXY(x, ++y); system("pause");
			textColor(14);
		}
		if (choice == 0)
		{
			goToXY(x, ++y); system("pause");
			return;
		}
	}

	// else, return
	else
	{
		textColor(4);
		goToXY(x, ++y); cout << "Student does not exist" << endl;
		goToXY(x, ++y); system("pause");
		textColor(14);
		return;
	}
	rewriteCourse(curCourse, dir + curCourse->courseID + ".txt");
	deleteStudentList(pStudent);
}