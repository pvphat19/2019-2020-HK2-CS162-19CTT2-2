#include "function.h"
//little stuff for 3 main function
int y=5;
Student* checkCondition(int mark, int& Id, Student* pStudent) {
	Student* link = nullptr;
	goToXY(10, y);
	do {
	    link = pStudent;
		mark = 0;                                                                  
		goToXY(10, y); cout << "                                                                      ";
		goToXY(10, y);
		cout << "Enter ID of student that's available : "; cin >> Id;
		while (link != nullptr) {
			if (Id == link->id) {
				mark++;
				break;
			}
			else {
				link = link->pNext;
			}
		}
		if (link == nullptr && mark == 0) { goToXY(10, y+1);
		cout << "Invalid ID " << endl;
		}
	} while (mark == 0);
	goToXY(10, y++);
	return link;
}
void cloning(Student*& replica, Student* original) {
	replica->id = original->id;
	replica->password = original->password;
	replica->fullname = original->fullname;
	replica->dob = original->dob;
	replica->cla = original->cla;
	replica->status = original->status;
}
int removeFunction(Student*& pStudent, int d, int count, Student*& replica) {
	Student* p, * q;
	q = pStudent;
	p = pStudent->pNext;
	if (q->id == d) {
		pStudent = p;
		cloning(replica, q);
		delete q; 
		return count;
	}
	else {


		while (p->id != d) {
			p = p->pNext;
			q = q->pNext;
			count++;
		}
	}
	if (p->pNext == nullptr) {
		q->pNext = nullptr;
		cloning(replica, p);
		delete p; 
		count++; return count;
	}
	else {
		q->pNext = p->pNext;
		cloning(replica, p);
		delete p; 
		count++; return count;
	}

}
void insertBefore(Student*& pStudent, int d, Student* insert) {
	int count = 0;
	if (count == d) {
		insert->pNext = pStudent;
		pStudent = insert;
		return;
	}
	Student* link = pStudent;
	while (count != d - 1) {
		if (link->pNext != nullptr) link = link->pNext;
		count++;
	}
	Student* mob = link->pNext;
	link->pNext = insert;
	insert->pNext = mob;
}
Student* inputStudentsInfo(int i, Student* replica, Student* pStudent,int numStudent) {
	Student* start = new Student; char t[100], s[100], cl[100]; int d;
	Date dob; int st;
	if (i == 1) {    
		hass:goToXY(10, y+1); cout << "                                                      ";
		goToXY(10, y + 1); int count;
		cout << "Enter Student ID again: "; cin >> d; cout << endl;
		while (pStudent != nullptr) {
			count = 0;
			if (d == pStudent->id) {
				goToXY(10, y + 2); count++;
				cout << "Error, this ID is taken"; break;
			}
			else {
				pStudent = pStudent->pNext; 
			}
		}
		if (count != 0) { goto hass; }
		y += 2;
		start->id = d;
		start->password = replica->password;
		start->fullname = replica->fullname;
		start->dob = replica->dob;
		start->cla = replica->cla;
		start->status = replica->status;
	}

	if (i == 2) {
		goToXY(10, y++);
		cout << "Enter password again: "; cin.ignore(); cin.get(t, 100, '\n');
		start->id = replica->id;
		start->password = t;
		start->fullname = replica->fullname;
		start->dob = replica->dob;
		start->cla = replica->cla;
		start->status = replica->status;
	}
	if (i == 3) {
		goToXY(10, y++);
		cout << "Enter Student's name again:  "; cin.ignore(); cin.get(s, 100, '\n');
		start->id = replica->id;
		start->password = replica->password;
		start->fullname = s;
		start->dob = replica->dob;
		start->cla = replica->cla;
		start->status = replica->status;
	}
	if (i == 4) {
		goToXY(10, y++);
		cout << "Enter Student's day of birth again:  " << endl;
		goToXY(10, y++);
		do { cout << "Enter year: "; cin >> dob.year; cout << endl; } while (dob.year > 3000 || dob.year < 0);
		goToXY(10, y++);
		cout << "Enter month: "; cin >> dob.month; cout << endl;
		goToXY(10, y++);
		cout << "Enter day: "; cin >> dob.day; cout << endl;
		start->id = replica->id;
		start->password = replica->password;
		start->fullname = replica->fullname;
		start->dob = dob;
		start->cla = replica->cla;
		start->status = replica->status;
	}
	if (i == 5) {
		start->id = replica->id;
		start->password = replica->password;
		start->fullname = replica->fullname;
		start->dob = replica->dob;
		start->cla = replica->cla;
		start->status = replica->status;
	}
	if (i == 6) {
		goToXY(10, y++); int clr = y;
		do {
			goToXY(10, clr + 1);
			cout << "Enter Student's status again: ";
			cout << "0.inactive " << " " << "1.active" << endl;
			goToXY(10, clr + 2); cout << "                 ";
			goToXY(10, clr + 2);
			cout << "your choice: "; cin >> st;
		} while (st != 1 && st != 0);
		y += 3;
		start->id = replica->id;
		start->password = replica->password;
		start->fullname = replica->fullname;
		start->dob = replica->dob;
		start->cla = replica->cla;
		start->status = st;
	}
	delete replica;
	return start;
}
Student* inputStudentsInfoAuto(Student* replica, Student* pStudent,string s) {
	Student* start = new Student;
	start->id = replica->id;
	start->password = replica->password;
	start->fullname = replica->fullname;
	start->dob = replica->dob;
	start->cla = s;
	start->status = replica->status;
	return start;
}
Student* removeStudentsAuto(int numStudent, Student*& pStudent, int& count,int d,string x) {
	Student* replica = new Student;
	count = removeFunction(pStudent, d, 0, replica);
	numStudent--;
	rewriteStudent(numStudent, pStudent, x);
	return replica;
}
void ChangeInfoAuto(int numStudent, Student*& pStudent,string s,int d) {
	Student* re; int count = 0;
	re = removeStudentsAuto(numStudent, pStudent, count,d,"Student"); int i;
	deleteStudentList(pStudent);
	loadStudent(numStudent, pStudent, "Student");
    Student* insert = inputStudentsInfoAuto(re, pStudent,s);
	insertBefore(pStudent, count, insert);
	numStudent++;
	rewriteStudent(numStudent, pStudent, "Student");
}
void ChangeStudentsClassAuto(int numStudent, Student*& pStudent,Student*& sub) {
	int mark = 0, d = 0; char s[100]; int pos; bool k; int preserve = numStudent;
	goToXY(10, y++);
	cout << "This Students was in class " << sub->cla << endl;
	d = sub->id;
	Student* st2 = nullptr, * st3 = nullptr;
	Student* replica = new Student;
	loadStudent(numStudent, st2,sub->cla);
	if (st2 == nullptr) { 
		goToXY(10, y++);
		cout << "you have a problem with your input data ";
		return;
	}
	removeFunction(st2, d, 0, replica);
	numStudent--;
	rewriteStudent(numStudent, st2, sub->cla);
	deleteStudentList(st2);
	goToXY(10, y++); int clr = y;
	do {
		goToXY(10, clr + 1); cout << "                                   ";
		goToXY(10, clr + 1);
		cout << "Now change to class: "; cin.ignore(); cin.get(s, 100, '\n');
		k = true; loadStudent(numStudent, st3, s);
		if (k == true) {
			insertBefore(st3, 0, replica);
			numStudent++;
			st3->cla = s;
			rewriteStudent(numStudent, st3, s);
		}
		else {
			goToXY(10, clr +2);
			cout << "this class haven't ready yet, choose another class " << endl; }
	} while (k == false);
	y += 3;
	ChangeInfoAuto(preserve, pStudent, s,sub->id);
	delete sub; delete st3;
	goToXY(10, y++);
	cout << "Your data has been changed successfully." << endl;
}
void ViewInfo(Student* viewStudent)
{
	goToXY(10, y++);
	goToXY(10, y++);
	cout << "This is Student's Information: " << endl;
	goToXY(10, y++);
	cout << "ID: " << viewStudent->id << endl;
	goToXY(10, y++);
	cout << "Password: " << viewStudent->password << endl;
	goToXY(10, y++);
	cout << "Full name: " << viewStudent->fullname << endl;
	goToXY(10, y++);
	cout << "Date of birth: " << viewStudent->dob.year << " " << viewStudent->dob.day << " "
		<< viewStudent->dob.day << endl;
	goToXY(10, y++);
	if (viewStudent->status == 1)
		cout << "Status: " << "active";
	else cout << "Status: " << "inactive";
	goToXY(10, y++);
	cout << endl;
}
//Remove a Student 
void removeStudents() {
	system("cls");
	int numStudent = 0; Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	int mark = 0, Id = 0; int numStudent1; Student* st2=nullptr;
	Student*choose=checkCondition(mark, Id, pStudent); 
	ViewInfo(choose);
	goToXY(10, y++); 
	cout << "Are you sure to remove this student ? " << endl;
	goToXY(10, y++); int crr = y;
	cout << "1.Yes" << " " << "0.No" << endl;
	do {
		goToXY(10, crr + 1); cout << "                                        ";
		goToXY(10, crr + 1);
		cout << "Choose option correctly:  "; cin >> mark;
	} while (mark != 0 && mark != 1);
	if (mark == 0) return;
	string k = choose->cla;
	Student* replica = new Student;
	removeFunction(pStudent, Id, 0, replica);
	numStudent--;
	rewriteStudent(numStudent, pStudent, "Student");
	loadStudent(numStudent1, st2, k);
	removeFunction(st2, Id, 0, choose);
	numStudent1--;
	rewriteStudent(numStudent1, st2, k);
	deleteStudentList(st2);
	deleteStudentList(pStudent);
	goToXY(10, y++); goToXY(10, y++);
	cout << "Your data has been changed successfully." << endl;
}
//Edit an existing Student
void ChangeStudentsInfo() {
	system("cls");
	int numStudent = 0; Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	Student* re; int count = 0; int i;
	int mark = 0, d = 0; Student* st2 = nullptr;
	Student* choose = checkCondition(mark, d, pStudent); 
	Student* sub = new Student;
	cloning(sub, choose);
	string k = choose->cla; 
	int numStudent1;
	goToXY(10, y++);
	do {
		goToXY(10, y+1);
		cout << "Enter your choice: " << endl;
		goToXY(10, y+2);
		cout << "1.change student ID " << endl;
		goToXY(10, y+3);
		cout << "2.change student password " << endl;
		goToXY(10, y+4);
		cout << "3.change name" << endl;
		goToXY(10, y+5);
		cout << "4.change day of birth" << endl;
		goToXY(10, y+6);
		cout << "5.change class " << endl;
		goToXY(10, y+7);
		cout << "6.change status " << endl;
		goToXY(10, y+9);
		cout << "Choose the option to change student info: ";
		cin >> i; cout << endl;
	} while (i > 6 || i < 1);
	y = y + 10;
	re = removeStudentsAuto(numStudent, pStudent, count,d,"Student");
	deleteStudentList(pStudent);
	loadStudent(numStudent, pStudent, "Student");
	Student* insert = inputStudentsInfo(i, re, pStudent,numStudent);
	insertBefore(pStudent, count, insert);
	numStudent++;
	rewriteStudent(numStudent, pStudent, "Student");
	if (i == 5) {
		ChangeStudentsClassAuto(numStudent, pStudent,sub);
		return;
	}
	//
	loadStudent(numStudent1, st2, k);
	removeStudentsAuto(numStudent1,st2, count, d,k);
	deleteStudentList(st2);
	loadStudent(numStudent1, st2, k);
	insertBefore(st2, count, insert);
	numStudent1++;
	rewriteStudent(numStudent1, st2, k);
	deleteStudentList(pStudent);
	goToXY(10, y++);
	cout << "Your data has been changed successfully." << endl;
}
//Change student from Class A to B
void ChangeStudentsClass() {
	system("cls");
	int numStudent = 0; Student* pStudent = nullptr;
	loadStudent(numStudent, pStudent, "Student");
	int mark = 0, d = 0; char s[100]; int pos; bool k; int preserve = numStudent;
	Student* choose = checkCondition(mark, d, pStudent);
	goToXY(10, y++);
	cout << "This Students was in class " << choose->cla << endl;
	Student* st2 = nullptr, * st3 = nullptr;
	Student* replica = new Student;
	loadStudent(numStudent, st2, choose->cla);
	if (st2 == nullptr) {
		goToXY(10, y++);
		cout << "you have a problem with your input data ";
		return;
	}
	removeFunction(st2, d, 0, replica);
	numStudent--;
	rewriteStudent(numStudent, st2, choose->cla);
	deleteStudentList(st2);
	goToXY(10, y++);int clr = y;
	do {                                                     
		goToXY(10, clr + 1); cout << "                                   ";
		goToXY(10, clr + 1);
		cout << "Now change to class: "; cin.ignore(); cin.get(s, 100, '\n');
		k = true; loadStudent(numStudent, st3, s);
		if (k == true) {
			insertBefore(st3, 0, replica);
			numStudent++;
			st3->cla = s;
			rewriteStudent(numStudent, st3, s);
		}
		else {
			goToXY(10, clr+2);
			cout << "this class haven't ready yet, choose another class " << endl; }
	} while (k == false);
	y += 3;
	ChangeInfoAuto(preserve, pStudent, s, choose->id);
    delete st3;
	goToXY(10, y++);
	cout << "Your data has been changed successfully." << endl;
	deleteStudentList(pStudent);
}
