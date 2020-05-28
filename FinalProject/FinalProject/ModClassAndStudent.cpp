#include "function.h"
Student* checkaStudent(int x, int y) {
	int num1, Id, mark = 0; Student* stu = nullptr; string stid; bool k;
	Student* link;
	loadStudent(num1, stu, "Student");
	do {
		link = stu;
		goToXY(x, y); cout << "                                                             ";
		goToXY(x, y); cout << "Enter Student's ID: "; cin >> stid;
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
			{goToXY(x, y + 1);
			cout << "Invalid ID " << endl; }
		}
	} while (mark == 0);
	goToXY(x, y + 1); cout << "                                             ";
	return link;
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
Class* checkClass(Student* ch, int x, int y) {
	Class* clas = nullptr, * check; int num, mark = 0;
	loadClass(num, clas); string cl;
	goToXY(x, y);
	cout << "This Student was in class: " << ch->cla << endl;
	do {
		check = clas;
		goToXY(x, y + 1); cout << "                                                                            ";
		goToXY(x, y + 1); cout << "Now change to class: "; cin >> cl;
		while (check != nullptr) {
			if (check->name == cl) {
				mark++;
				return check;
			}
			check = check->pNext;
		}
		if (mark == 0) {
			goToXY(x, y + 2);
			cout << "this class haven't ready yet, choose another class" << endl;
		}
	} while (mark == 0);
	goToXY(x, y + 2); cout << "                                                  ";
}
void option1(Student* ch, int i, int i2, int x, int y) {
	string pss, ttt; char s[100]; bool kkk;
	Student* clas = NULL; int num1; int num2, num3, st;
	int yr, mo, dy;
	loadStudent(num1, clas, "Student");
	while (clas->id != ch->id) clas = clas->pNext;
	if (i == 1) {
		goToXY(x, y); cout << "                                                    ";
		goToXY(x, y); cout << "Enter password again: "; cin >> pss;
	}
	if (i == 2) { goToXY(x, y); cout << "Enter Student's name again:  "; cin.ignore(); cin.get(s, 100, '\n'); }
	if (i == 3) {
		goToXY(x, y);
		cout << "Enter Student's day of birth again:  " << endl;
		inputDate(yr, mo, dy, y + 1, x);
	}
	if (i == 4) {
		do {
			goToXY(x, y); cout << "Enter Student's status again: ";
			goToXY(x, y + 1); cout << "0.inactive " << " " << "1.active" << endl;
		aa:goToXY(x, y + 2); cout << "                                                       ";
			goToXY(x, y + 2); cout << "your choice: "; cin >> ttt; kkk = convertStringToInt(ttt, st);
			if (st != 1 && st != 0 || kkk == false) {
				goToXY(x, y + 3);
				cout << "Error input";
				goToXY(x, y + 4);
				system("pause");
				goToXY(x, y + 4); cout << "                                                                         ";
				goto aa;
			}
		} while (st != 1 && st != 0);
		goToXY(x, y + 3); cout << "                                  ";
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
		Student* test0 = test2; if (test0 == nullptr) goto b;
		while (test0->pNext != nullptr && test0 != nullptr) {
			if (test0->pNext->id == ch->id) {
				Student* tempt = test0->pNext;
				test0->pNext = test0->pNext->pNext;
				delete tempt;
			}
			else test0 = test0->pNext;
		}
	b:if (test3->id == ch->id) {
		Student* tempt = test3;
		test3 = test3->pNext;
		delete tempt;
	}
	else {
		Student* cur0 = test3; if (test3 == nullptr) goto c;
		while (cur0->pNext != nullptr) {
			if (cur0->pNext->id == ch->id) {
				Student* tempt = cur0->pNext;
				cur0->pNext = cur0->pNext->pNext;
				delete tempt;
			}
			else cur0 = cur0->pNext;
		}
	}
c:
	num2--; num3--;
	}
	Student* cur = test3; Student* tesk = test2;
	while (tesk != nullptr && tesk->id != ch->id) tesk = tesk->pNext;
	while (cur != nullptr && cur->id != ch->id) cur = cur->pNext;
	if (i == 1) {
		tesk->password = pss;
		cur->password = pss;
	}
	if (i == 2) {
		tesk->fullname = s;
		cur->fullname = s;
	}
	if (i == 3) {
		tesk->dob.year = yr;
		tesk->dob.month = mo;
		tesk->dob.day = dy;
		cur->dob.year = yr;
		cur->dob.month = mo;
		cur->dob.day = dy;

	}
	if (i == 4) {
		tesk->status = st;
		cur->status = st;
	}
	rewriteStudent(num2, test2, test->cla);
	rewriteStudent(num3, test3, "Student");
	deleteStudentList(clas);
	deleteStudentList(test2);
	deleteStudentList(test3);
}
void ViewInfo(Student* viewStudent, int x, int y)
{
	goToXY(x, y); cout << "This is Student's Information: " << endl;
	goToXY(x, y + 1); cout << "ID: " << viewStudent->id << endl;
	goToXY(x, y + 2); cout << "Password: " << viewStudent->password << endl;
	goToXY(x, y + 3); cout << "Full name: " << viewStudent->fullname << endl;
	goToXY(x, y + 4); cout << "Date of birth: " << viewStudent->dob.year << " " << viewStudent->dob.day << " "
		<< viewStudent->dob.day << endl;
	if (viewStudent->status == 1)
	{
		goToXY(x, y + 5); cout << "Status: " << "active";
	}
	else { goToXY(x, y + 5); cout << "Status: " << "inactive"; }
	cout << endl;
}
void editStudent() {
	int x = 10, y = 5;
	Student* ch = checkaStudent(x, y); string tk; int i; bool ed;
	do {
	pin:goToXY(x, y + 2); cout << "Enter your choice: " << endl;
		goToXY(x, y + 3); cout << "1.change student password " << endl;
		goToXY(x, y + 4); cout << "2.change name" << endl;
		goToXY(x, y + 5); cout << "3.change day of birth" << endl;
		goToXY(x, y + 6); cout << "4.change status " << endl;
		goToXY(x, y + 7); cout << "0.Exit";
		goToXY(x, y + 8); cout << "                                                                              ";
		goToXY(x, y + 8); cout << "Choose the option : ";
		cin >> tk; ed = convertStringToInt(tk, i); cout << endl;
		if ((i > 4 || i < 0) || ed == false) {
			goToXY(x, y + 9);
			cout << "Error Input ";
			goto pin;
		}
		goToXY(x, y + 9); cout << "                                                          ";
		if (i == 0) return;
		option1(ch, i, 0, x, y + 10);
		clrscrfromatob(y + 8, y + 15, x);
	} while (i != 0);
	delete ch;
}
void removestudent() {
	int y = 5, x = 10;
	Student* ch = checkaStudent(x, y);
	ViewInfo(ch, x, y + 2); int mark; string mark1; bool markk;
	goToXY(x, y + 7); cout << "Are you sure to remove this student ? " << endl;
	goToXY(x, y + 8); cout << "1.Yes" << " " << "0.No" << endl;
	do {
		goToXY(x, y + 9); cout << "                                                                   ";
		goToXY(x, y + 9); cout << "Choose option correctly:  "; cin >> mark1; markk = convertStringToInt(mark1, mark);
		if ((mark != 0 && mark != 1) || markk == false) {
			goToXY(x, y + 10);
			cout << "Invalid input!";
		}
	} while ((mark != 0 && mark != 1) || markk == false);
	goToXY(x, y + 10); cout << "                                                                            ";
	if (mark == 0) return;
	option1(ch, 0, 1, x, y + 11);
	delete ch;

}
void changeStudentClass() {
	int x = 10, y = 5;
	Student* ch = checkaStudent(x, y);
	Class* claa = checkClass(ch, x, y + 1);
	Student* test2 = nullptr, * test3 = nullptr, * test4 = nullptr; int num2, num3, num4;
	loadStudent(num2, test2, ch->cla);
	loadStudent(num3, test3, claa->name);
	if (test2->id == ch->id) {
		Student* tempt = test2;
		test2 = test2->pNext;
		delete tempt;
	}
	Student* test0 = test2; if (test2 == nullptr) goto bb;
	while (test0->pNext != nullptr) {
		if (test0->pNext->id == ch->id) {
			Student* tempt = test0->pNext;
			test0->pNext = test0->pNext->pNext;
			delete tempt;
		}
		else test0 = test0->pNext;
	}
	bb:
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

