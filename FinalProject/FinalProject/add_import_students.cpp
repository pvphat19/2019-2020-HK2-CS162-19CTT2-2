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

void manually_add_student_to_class()
{
	//input class
	int numClass=0;
	Class* pClass=nullptr;
	loadClass(numClass, pClass);
	Class* cur=pClass;
	cout << "Please choose the class you want to add in. We have " << numClass << " class:" << endl;
	for (int i = 0; i < numClass; ++i)
	{
		cout << i + 1 << "." << cur->name << endl;
		cur = cur->pNext;
	}
	cout << "Enter the class you want: ";
	int n;
	cin >> n;
	cur = pClass;
	for (int i = 0; i < n - 1; ++i)
		cur = cur->pNext;
	cout << "You choose class " << cur->name<<"." << endl;
	//check id
	Student* pStudent1=nullptr;
	int numStudent1=0;
	loadStudent(numStudent1, pStudent1, "Student");
	cout << "Please enter student ID: ";
	int ID;
	cin >> ID;
	while (check_id(ID,pStudent1) == false) {
		cout << "The ID has been used. Please enter new student ID: ";
		cin >> ID;
	}
	//add to the class file
	Student* pStudent=nullptr;
	int numStudent=0;
	loadStudent(numStudent, pStudent, cur->name);
	Student * tmp = pStudent;
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
	cout << "Please enter full name of the student: ";
	cin.ignore(100, '\n');
	getline(cin,tmp->fullname);
	cout << "Enter date of birth: " << endl;
	cout << "Day: ";
	cin >> tmp->dob.day;
	cout << "Month: ";
	cin >> tmp->dob.month;
	cout << "Year: ";
	cin >> tmp->dob.year;
	create_password(tmp->dob, tmp->password);
	numStudent++;
	rewriteStudent(numStudent, pStudent, cur->name);
	//add to student.txt
	Student *tmp1 = pStudent1;
	if (tmp1 == nullptr)
	{
		pStudent1 = new Student;
		tmp1 = pStudent1;
	}
	else {
		for (int i = 0; i < numStudent1 - 1; ++i)
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
	numStudent1++;
	rewriteStudent(numStudent1,pStudent1,"Student");
	deleteStudentList(pStudent);
	deleteClassList(pClass);
	deleteStudentList(pStudent1);
	cout << "The student has been add to symstem." << endl;
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