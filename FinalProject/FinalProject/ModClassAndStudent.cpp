#include "function.h"
Student* checkaStudent() {
	int num1, Id, mark = 0; Student*stu=nullptr; string stid; bool k;
	Student* link;
	loadStudent(num1, stu, "Student");
	do {
		link = stu;
		cout << "Enter Student's ID: "; cin >> stid;
		k = convertStringToInt(stid, Id);
		while (link != nullptr) {
			if (Id == link->id) {
				mark++;
				break;
			}
			else {
				link = link->pNext;
			}
		}
		if (link == nullptr && mark == 0 || k == false) {
			cout << "Invalid ID " << endl;
		}
	} while (mark == 0);
	return link;
	deleteStudentList(stu);
}
void cloning(Student*& replica, Student* original) {
	replica->id = original->id;
	replica->password = original->password;
	replica->fullname = original->fullname;
	replica->dob = original->dob;
	replica->cla = original->cla;
	replica->status = original->status;
	replica->pNext = nullptr;
}
Class* checkClass(Student* ch) {
	Class* clas = nullptr, * check; int num, mark = 0;
	loadClass(num, clas); string cl;
	cout << "This Student was in class: " << ch->cla << endl;
	do {
		check = clas;
		cout << "Now change to class: "; cin >> cl;
		while (check != nullptr) {
			if (check->name == cl) {
				mark++;
				return check;
			}
			check = check->pNext;
		}
		if (mark == 0) cout << "this class haven't ready yet, choose another class" << endl;
	} while (mark == 0);
}
void option1(Student* ch, int i, int i2) {
	string pss, ttt; char s[100]; bool kkk;
	Student* clas = NULL; int num1; int num2, num3, st;
	int yr, mo, dy;
	loadStudent(num1, clas, "Student");
	while (clas->id != ch->id) clas = clas->pNext;
	if (i == 1) { cout << "Enter password again: "; cin >> pss; }
	if (i == 2) { cout << "Enter Student's name again:  "; cin.ignore(); cin.get(s, 100, '\n'); }
	if (i == 3) {
		cout << "Enter Student's day of birth again:  " << endl;
		inputDate(yr, mo, dy);
	}
	if (i == 4) {
		do {
			cout << "Enter Student's status again: ";
			cout << "0.inactive " << " " << "1.active" << endl;
			cout << "your choice: "; cin >> ttt; kkk = convertStringToInt(ttt, st);
			if (st != 1 && st != 0 || kkk == false)cout << "Error input";
		} while (st != 1 && st != 0);
	}
	Student* test = clas;
	Student* test2 = nullptr, * test3 = nullptr;
	while (test != nullptr && test->id != ch->id) test = test->pNext;
	loadStudent(num2, test2, test->cla);
	loadStudent(num3, test3, "Student");
	if (i2 == 1) {
		if (test2->id == ch->id) {
			Student* tempt = test2;
			test2 = test2->pNext;
			delete tempt;
		}
		Student* test0 = test2;
		while (test0->pNext != nullptr) {
			if (test0->pNext->id == ch->id) {
				Student* tempt = test0->pNext;
				test0->pNext = test0->pNext->pNext;
				delete tempt;
			}
			else test0 = test0->pNext;
		}
		if (test3->id == ch->id) {
			Student* tempt = test3;
			test3 = test3->pNext;
			delete tempt;
		}
		else {
			Student* cur0 = test3;
			while (cur0->pNext != nullptr) {
				if (cur0->pNext->id == ch->id) {
					Student* tempt = cur0->pNext;
					cur0->pNext = cur0->pNext->pNext;
					delete tempt;
				}
				else cur0 = cur0->pNext;
			}
		}
		num2--; num3--;
	}
	Student* cur = test3;
	while (cur != nullptr && cur->id != ch->id) cur = cur->pNext;
	if (i == 1) {
		test->password = pss;
		cur->password = pss;
	}
	if (i == 2) {
		test->fullname = s;
		cur->fullname = s;
	}
	if (i == 3) {
		test->dob.year = yr;
		test->dob.month = mo;
		test->dob.day = dy;
		cur->dob.year = yr;
		cur->dob.month = mo;
		cur->dob.day = dy;

	}
	if (i == 4) {
		test->status = st;
		cur->status = st;
	}
	rewriteStudent(num2, test2, test->cla);
	rewriteStudent(num3, test3, "Student");
	deleteStudentList(clas);
	deleteStudentList(test2);
	deleteStudentList(test3);
}
void ViewInfo(Student* viewStudent)
{
	cout << "This is Student's Information: " << endl;
	cout << "ID: " << viewStudent->id << endl;
	cout << "Password: " << viewStudent->password << endl;
	cout << "Full name: " << viewStudent->fullname << endl;
	cout << "Date of birth: " << viewStudent->dob.year << " " << viewStudent->dob.day << " "
		<< viewStudent->dob.day << endl;
	if (viewStudent->status == 1)
		cout << "Status: " << "active";
	else cout << "Status: " << "inactive";
	cout << endl;
}
void editStudent() {
	Student* ch = checkaStudent(); string tk; int i; bool ed;
	do {
		cout << "Enter your choice: " << endl;
		cout << "1.change student password " << endl;
		cout << "2.change name" << endl;
		cout << "3.change day of birth" << endl;
		cout << "4.change status " << endl;
		cout << "Choose the option to change student info: ";
		cin >> tk; ed = convertStringToInt(tk, i); cout << endl;
		if (i > 4 || i < 1 || ed == false) cout << "Error Input ";
	} while (i > 4 || i < 1 || ed == false);
	option1(ch, i, 0);
	delete ch;
}
void removestudent() {
	Student* ch = checkaStudent();
	ViewInfo(ch); int mark;
	cout << "Are you sure to remove this student ? " << endl;
	cout << "1.Yes" << " " << "0.No" << endl;
	do {
		cout << "Choose option correctly:  "; cin >> mark;
	} while (mark != 0 && mark != 1);
	if (mark == 0) return;
	option1(ch, 0, 1);
	delete ch;

}
void changeStudentClass() {
	Student* ch = checkaStudent();
	Class* claa = checkClass(ch);
	Student* test2 = nullptr, * test3 = nullptr, * test4 = nullptr; int num2, num3, num4;
	loadStudent(num2, test2, ch->cla);
	loadStudent(num3, test3, claa->name);
	if (test2->id == ch->id) {
		Student* tempt = test2;
		test2 = test2->pNext;
		delete tempt;
	}
	else {
		Student* test0 = test2;
		while (test0->pNext != nullptr) {
			if (test0->pNext->id == ch->id) {
				Student* tempt = test0->pNext;
				test0->pNext = test0->pNext->pNext;
				delete tempt;
			}
			else test0 = test0->pNext;
		}
	}
	num2--;
	rewriteStudent(num2, test2, ch->cla);
	loadStudent(num4, test4, "Student");
	Student* cur0 = test4;
	while (cur0->id != ch->id)cur0 = cur0->pNext;
	cur0->cla = claa->name;
	ch->cla = claa->name;
	Student* cln = new Student;
	cloning(cln, ch);
	Student* cur = test3;
	if (test3 == nullptr) test3 = cln;
	else {
		while (cur->pNext != nullptr && cur != nullptr) cur = cur->pNext;
		cur->pNext = cln;
	}
	num3++;
	rewriteStudent(num4, test4, "Student");
	rewriteStudent(num3, test3, claa->name);
	deleteStudentList(test4);
	deleteStudentList(test2);
	deleteStudentList(test3);
	delete claa, cln;
	delete ch;
}

 