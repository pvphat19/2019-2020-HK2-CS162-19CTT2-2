#include "function.h"
//little stuff for 3 main function
Student* checkCondition(int mark, int& d, Student* pStudent) {
	Student* link = nullptr;
	do {
	    link = pStudent;
		mark = 0;
		cout << "enter ID of student : "; cin >> d;
		while (link != nullptr) {
			if (d == link->id) {
				mark++;
				break;
			}
			else {
				link = link->pNext;
			}
		}
		if (link == nullptr && mark == 0)cout << " invalid ID " << endl;
	} while (mark == 0);
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
	if (pStudent == nullptr)cout << "yes";
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
		cout << "Enter Student ID again: "; cin >> d; cout << endl;
		while (pStudent != nullptr) {
			if (d == pStudent->id) {
				cout << "Error, this ID is taken,Enter Student ID again: "; cin >> d; cout << endl;
			}
			else {
				pStudent = pStudent->pNext; 
			}
		}
		start->id = d;
		start->password = replica->password;
		start->fullname = replica->fullname;
		start->dob = replica->dob;
		start->cla = replica->cla;
		start->status = replica->status;
	}

	if (i == 2) {
		cout << "Enter password again: "; cin.ignore(); cin.get(t, 100, '\n');
		start->id = replica->id;
		start->password = t;
		start->fullname = replica->fullname;
		start->dob = replica->dob;
		start->cla = replica->cla;
		start->status = replica->status;
	}
	if (i == 3) {
		cout << "Enter Student's name again:  "; cin.ignore(); cin.get(s, 100, '\n');
		start->id = replica->id;
		start->password = replica->password;
		start->fullname = s;
		start->dob = replica->dob;
		start->cla = replica->cla;
		start->status = replica->status;
	}
	if (i == 4) {
		cout << "Enter Student's day of birth again:  " << endl;
		cout << "Enter year: "; cin >> dob.year; cout << endl;
		cout << "Enter month: "; cin >> dob.month; cout << endl;
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
		do {
			cout << "Enter Student's status again: ";
			cout << "0.inactive " << " " << "1.active" << endl;
			cout << "your choice: "; cin >> st;
		} while (st > 1 && st < 0);
		start->id = replica->id;
		start->password = replica->password;
		start->fullname = replica->fullname;
		start->dob = replica->dob;
		start->cla = replica->cla;
		start->status = st;
	}
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
//Remove a Student (count=0 when you put it inparameter)
Student* removeStudents(int numStudent, Student*& pStudent, int& count) {
	int mark = 0, d = 0;
	checkCondition(mark, d, pStudent); 
	Student* replica = new Student;
	count = removeFunction(pStudent, d, 0, replica);
	numStudent--;
	rewriteStudent(numStudent, pStudent, "Student");
	return replica;
}
//Edit an existing Student
void ChangeStudentsInfo(int numStudent, Student*& pStudent) {
	Student* re; int count = 0; int i;
	int mark = 0, d = 0; Student* st2 = nullptr;
	Student* choose = checkCondition(mark, d, pStudent); 
	string k = choose->cla; 
	int numStudent1;
	do {
		cout << "Enter your choice: " << endl;
		cout << "1.change student ID " << endl;
		cout << "2.change student password " << endl;
		cout << "3.change name" << endl;
		cout << "4.change day of birth" << endl;
		cout << "5.change class " << endl;
		cout << "6.change status " << endl;
		cout << "choose the option to change student info: ";
		cin >> i; cout << endl;
	} while (i > 6 || i < 1);
	re = removeStudentsAuto(numStudent, pStudent, count,d,"Student");
	deleteStudentList(pStudent);
	loadStudent(numStudent, pStudent, "Student");

	Student* insert = inputStudentsInfo(i, re, pStudent,numStudent);
	insertBefore(pStudent, count, insert);
	numStudent++;
	rewriteStudent(numStudent, pStudent, "Student");
	if (i == 5) {
		ChangeStudentsClass(numStudent, pStudent);
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

}
//Change student from Class A to B
void ChangeStudentsClass(int numStudent, Student*& pStudent) {
	int mark = 0, d = 0; char s[100]; int pos; bool k; int preserve = numStudent;
	Student* choose = checkCondition(mark, d, pStudent); 
	cout << "This Students was in class " << choose->cla << endl;
	Student* st2 = nullptr, * st3 = nullptr;
	Student* replica = new Student;
	loadStudent(numStudent, st2, choose->cla);
	if (st2 == nullptr) { 
		cout << "you have a problem with your input data ";
		return;
	}
	removeFunction(st2, d, 0, replica);
	numStudent--;
	rewriteStudent(numStudent, st2, choose->cla);
	deleteStudentList(st2);
	do {
		cout << "Now change to class: "; cin.ignore(); cin.get(s, 100, '\n');
		k = loadStudent(numStudent, st3, s);
		if (k == true) {
			insertBefore(st3, 0, replica);
			numStudent++;
			st3->cla = s;
			rewriteStudent(numStudent, st3, s);
		}
		else cout << "this class haven't ready yet, choose another class " << endl;
	} while (k == false);
	ChangeInfoAuto(preserve, pStudent, s,choose->id);
}