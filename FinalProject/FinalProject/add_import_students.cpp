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
	goToXY(x, y++); cout << "Please choose the class you want to add in. We have " << numClass << " class:";
	for (int i = 0; i < numClass; ++i)
	{
		goToXY(x, y++); cout << i + 1 << "." << cur->name << endl;
		cur = cur->pNext;
	}
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
	while (!check || check_id(ID, pAllStudent) == false) {
		if (!check) {
			goToXY(x, y++); cout << "Please enter a number: ";
		}
		else
		{
			goToXY(x, y++); cout << "The ID has been used. Please enter another ID: ";
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
	goToXY(x, y++); cout << "Please enter full name of the student: ";
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
	while (!check && (tmp->dob.month <= 0 || tmp->dob.month > 31))
	{
		goToXY(x, y++); cout << "Please enter a positive integer: ";
		getline(cin, dobMonth);
		check = convertStringToInt(dobMonth, tmp->dob.month);
	}
	goToXY(x, y++); cout << "Year: ";
	string dobYear;
	getline(cin, dobYear);
	check = convertStringToInt(dobYear, tmp->dob.year);
	while (!check && (tmp->dob.year <= 0 || tmp->dob.year > 31))
	{
		goToXY(x, y++); cout << "Please enter a positive integer: ";
		getline(cin, dobYear);
		check = convertStringToInt(dobYear, tmp->dob.year);
	}
	while (!checkValidDate(tmp->dob))
	{
		goToXY(x, y++); cout << "The date is not existed. Please enter another date: ";
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
		while (!check && (tmp->dob.month <= 0 || tmp->dob.month > 31))
		{
			goToXY(x, y++); cout << "Please enter a positive integer: ";
			getline(cin, dobMonth);
			check = convertStringToInt(dobMonth, tmp->dob.month);
		}
		goToXY(x, y++); cout << "Year: ";
		string dobYear;
		getline(cin, dobYear);
		check = convertStringToInt(dobYear, tmp->dob.year);
		while (!check && (tmp->dob.year <= 0 || tmp->dob.year > 31))
		{
			goToXY(x, y++); cout << "Please enter a positive integer: ";
			getline(cin, dobYear);
			check = convertStringToInt(dobYear, tmp->dob.year);
		}
	}
	create_password(tmp->dob, tmp->password);
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
	tmp1->pNext = nullptr;
	tmp1->id = tmp->id;
	tmp1->cla = tmp->cla;
	tmp1->dob = tmp->dob;
	tmp1->fullname = tmp->fullname;
	tmp1->password = tmp->password;
	tmp1->status = tmp->status;
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
		goToXY(x, y++); cout << "The student has been added to system." << endl;
	}
	else
	{
		goToXY(x, y++); cout << "The student has not been added to system" << endl;
	}
	deleteStudentList(pStudent);
	deleteClassList(pClass);
	deleteStudentList(pAllStudent);
}

void import_class()//can nang cap doan check class ban dau
{
	cout << "Please enter the name of the class: ";
	string classname;
	getline(cin, classname);
	//check the class is existed or not
	char* temp = new char[classname.size() + 1];
	for (int i = 0; i < classname.size(); ++i)
		temp[i] = classname[i];
	temp[classname.size()] = '\0';
	ifstream in;
	in.open("class.txt");
	int n;
	in >> n;
	in.ignore();
	char** cla;
	cla = new char* [n];
	bool t = true;
	for (int i = 0; i < n; ++i)
	{
		char tmp[100];
		in.get(tmp, 100, '\n');
		in.get();
		cla[i] = new char[strlen(tmp) + 1];
		strcpy(cla[i], tmp);
		if (strcmp(temp, cla[i]) == 0)
			t = false;
	}
	for (int i = 0; i < n; ++i)
		delete[]cla[i];
	delete[]cla;
	delete[] temp;
	in.close();
	if (t == false)
	{
		cout << "The class is existed." << endl;
		return;
	}
	else
	{
		//chua cap nhat Class.txt vi con dem so hoc sinh o sau
		cout << "This is a new class." << endl;
	}
	//end of checking
	//import
	cout << "Please enter the link of csv file:";
	string csv;
	getline(cin, csv);
	in.open(csv);
	if (!in)
	{
		cout << "Error when opening the csv file." << endl;
		return;
	}
	string filename = classname + ".txt";
	ofstream out;
	out.open(filename,std::ios::_Noreplace);
	if (!out)
	{
		cout << "Error in creating the file." << endl;
		return;
	}
		int success = 0;
		Student* pStudent = nullptr;
		Student* cur = pStudent;
		int dem = 0;
		int numstudent1 = 0;
		Student* pStudent1 = nullptr;
		loadStudent(numstudent1, pStudent1, "Student");
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
				int day;
				in >> day;
				in.ignore();
				int month;
				in >> month;
				in.ignore();
				int year;
				in >> year;
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
					dem ++;
					Student* tmp = pStudent1;
					if (pStudent1 == nullptr)
					{
						pStudent1 = pStudent;
					}
					else {
						while (tmp->pNext != nullptr)
							tmp = tmp->pNext;
						tmp->pNext = pStudent;
					}
					numstudent1++;
					cur->id = ID;
				}
				else
				{
					cur->pNext = new Student;
					cur = cur->pNext;
					cur->pNext = nullptr;
					success++;
					dem++;
					numstudent1++;
					cur->id = ID;
				}
				in.ignore(100, ',');
				string lastname;
				getline(in, lastname, ',');
				string firstname;
				getline(in, firstname, ',');
				cur->fullname = lastname + " " + firstname;
				in >> cur->dob.day;
				in.ignore(100, '/');
				in >> cur->dob.month;
				in.ignore(100, '/');
				in >> cur->dob.year;
				cur->status = 1;
				cur->cla = classname;
				create_password(cur->dob, cur->password);
			}
		}
		in.close();
		out.close();
		rewriteStudent(success, pStudent, classname);
		rewriteStudent(numstudent1, pStudent1, "Student");
		//update class.txt
		int numClass1 = 0;
		Class* pClass1 = nullptr;
		loadClass(numClass1, pClass1);
		Class* temp1 = pClass1;
		numClass1++;
		if (pClass1 == nullptr)
		{
			pClass1 = new Class;
			pClass1->name = classname;
			pClass1->pNext = nullptr;
		}
		else
		{
			Class* temp = pClass1;
			while (temp->pNext != nullptr)
				temp = temp->pNext;
			temp->pNext = new Class;
			temp = temp->pNext;
			temp->pNext = nullptr;
			temp->name = classname;
		}
		rewriteClass(numClass1, pClass1);
		//
		cout << "We have import " << success << " students successfully among " << dem << " students." << endl;
		if (dem > success)
		{
			cout << dem - success << " students failed because of existing id." << endl;
		}
		deleteClassList(pClass1);
		deleteStudentList(pStudent1);
}

