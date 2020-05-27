#include "function.h"

bool convertStringToInt(string str, int& x)
{
	int n = str.length();
	x = 0;
	for (int i = 0; i < n; i++)
		if (isdigit(str[i]))
			x = x * 10 + int(str[i]) - int('0');
		else
			return false;
	return true;
}
Semester* checkAcademicY(Semester*& sm, string& s,int&y,int&x) {
	int count = 0; 
	do {
		goToXY(x, y + 1); cout << "                                                                                                   ";
		goToXY(x, y + 1);
		cout << "Please enter Academic year (Example: 2012-2013): ";
		cin >> s;
		Semester* sms = sm;
		while (sms != nullptr) {
			if (sms->academicYear == s) {
				y += 1;
				return sms;
				count++;
			}
			sms = sm->pNext;
		}
		if (count == 0) {
			string choice; int out; bool cmp;
			do {
				goToXY(x, y + 2); cout << "                                                                       ";
				goToXY(x, y + 2); cout << "Invalid year! Do you want to try again(Yes(1) / No(0))?" << endl;
				goToXY(x, y + 3); cout << "                                                          ";
				goToXY(x, y + 3); cout << "Enter your choice: ";cin>> choice; cmp = convertStringToInt(choice, out);
				goToXY(x, y + 4);if (out != 0 && out != 1 || cmp == false) cout << "Error Input!";
				goToXY(x, y + 2); cout << "                                                                       ";
				goToXY(x, y + 3); cout << "                                                          ";
				goToXY(x, y + 4); cout << "                         ";
				if (out == 0&& cmp==true) return nullptr;
			} while (out != 0 && out != 1 || cmp == false);
		}
	} while (count == 0);
}
Semester* checkSemester(Semester*& sm, string& s,int&y,int&x) {
	int count = 0;
	do {
		goToXY(x, y + 1); cout << "                                                                                                   ";
		goToXY(x, y + 1);
		cout << "Please enter semester: ";
		cin >> s;
		Semester* sms = sm;
		while (sms != nullptr) {
			if (sms->semester == s) {
				y++;
				return sms;
				count++;
			}
			sms = sms->pNext;
		}
		if (count == 0) {
			string choice; int out; bool cmp;
			do {
				goToXY(x, y + 2); cout << "                                                                       ";
				goToXY(x, y + 2); cout << "Invalid semester! Do you want to try again(Yes(1) / No(0))?" << endl;
				goToXY(x, y + 3); cout << "                                                          ";
				goToXY(x, y + 3); cout << "Enter your choice: "; cin >> choice; cmp = convertStringToInt(choice, out);
				goToXY(x, y + 4); if (out != 0 && out != 1 || cmp == false) cout << "Error Input!";
				goToXY(x, y + 2); cout << "                                                                       ";
				goToXY(x, y + 3); cout << "                                                          ";
				goToXY(x, y + 4); cout << "                         ";
				if (out == 0 && cmp == true) return nullptr;
			} while (out != 0 && out != 1 || cmp == false);
		}
	} while (count == 0);
}
Schedule* checkClassID(Semester*& sm, string& s,int&y,int&x) {
	int count = 0;
	do {
		goToXY(x, y + 1); cout << "                                                                                                   ";
		goToXY(x, y + 1);
		cout << "Please enter class ID: ";
		cin >> s;
		Schedule* sche = sm->pSchedule;
		while (sche != nullptr) {
			if (sche->cla == s) {
				y++;
				return sche;
				count++;
			}
			sche = sche->pNext;
		}
		if (count == 0) {
			string choice; int out; bool cmp;
			do {
				goToXY(x, y + 2); cout << "                                                                       ";
				goToXY(x, y + 2); cout << "Invalid class! Do you want to try again(Yes(1) / No(0))?" << endl;
				goToXY(x, y + 3); cout << "                                                          ";
				goToXY(x, y + 3); cout << "Enter your choice: "; cin >> choice; cmp = convertStringToInt(choice, out);
				goToXY(x, y + 4); if (out != 0 && out != 1 || cmp == false) cout << "Error Input!";
				goToXY(x, y + 2); cout << "                                                                       ";
				goToXY(x, y + 3); cout << "                                                          ";
				goToXY(x, y + 4); cout << "                         ";
				if (out == 0 && cmp == true) return nullptr;
			} while (out != 0 && out != 1 || cmp == false);
		}
	} while (count == 0);
}
Course* checkCourse(Schedule*& sc, string& s,int&y,int&x) {
	int count = 0;
	do {
		goToXY(x, y + 1); cout << "                                                                                                   ";
		goToXY(x, y + 1);
		cout << "Please enter course ID: ";
		cin >> s;
		Course* cour = sc->pCourse;
		while (cour != nullptr) {
			if (cour->courseID == s) {
				y++;
				return cour;
				count++;
			}
			cour = cour->pNext;
		}
		if (count == 0) {
			string choice; int out; bool cmp;
			do {
				goToXY(x, y + 2); cout << "                                                                       ";
				goToXY(x, y + 2); cout << "Invalid Course! Do you want to try again(Yes(1) / No(0))?" << endl;
				goToXY(x, y + 3); cout << "                                                          ";
				goToXY(x, y + 3); cout << "Enter your choice: "; cin >> choice; cmp = convertStringToInt(choice, out);
				goToXY(x, y + 4); if (out != 0 && out != 1 || cmp == false) cout << "Error Input!";
				goToXY(x, y + 2); cout << "                                                                       ";
				goToXY(x, y + 3); cout << "                                                          ";
				goToXY(x, y + 4); cout << "                         ";
				if (out == 0 && cmp == true) return nullptr;
			} while (out != 0 && out != 1 || cmp == false);
		}
	} while (count == 0);
}
Student* checkStudent(Course*& cour, string& s,int&y,int&x) {
	int count = 0; int Id;
	do {
		goToXY(x, y + 1); cout << "                                                                                                   ";
		goToXY(x, y + 1);
		cout << "Please enter student ID:  ";
		cin >> s; convertStringToInt(s, Id); cout << endl;
		Student* st = cour->pStudent;
		while (st != nullptr) {
			if (st->id == Id) {
				y++;
				return st;
				count++;
			}
			st = st->pNext;
		}
		if (count == 0) { 
			string choice; int out; bool cmp;
			do {
				goToXY(x, y + 2); cout << "                                                                       ";
				goToXY(x, y + 2); cout << "Invalid student! Do you want to try again(Yes(1) / No(0))?" << endl;
				goToXY(x, y + 3); cout << "                                                          ";
				goToXY(x, y + 3); cout << "Enter your choice: "; cin >> choice; cmp = convertStringToInt(choice, out);
				goToXY(x, y + 4); if (out != 0 && out != 1 || cmp == false) cout << "Error Input!";
				goToXY(x, y + 2); cout << "                                                                       ";
				goToXY(x, y + 3); cout << "                                                          ";
				goToXY(x, y + 4); cout << "                         ";
				if (out == 0 && cmp == true) return nullptr;
			} while (out != 0 && out != 1 || cmp == false);
		}
	} while (count == 0);
}
bool correctDate(int month, int year, int day) {
	cout << "tttt";
	switch (month) {
	case 1: if (day > 0 && day < 32) return true;
		  else return false;
		break;
	case 2:
		if (year % 100 == 0) {
			if (year % 400 == 0) {
				if (day > 0 && day <30) return true;
				else return false;
			}
			else {
				if (day>0&&day<29) return true;
				else return false;
			}
		}
		else if (year % 4 == 0) {
			if (day > 0 && day < 30) return true;
			else return false;
		}
		else {
			if (day > 0 && day < 29) return true;
			else return false;
		}
		break;
	case 3:if (day > 0 && day < 32) return true;
		  else return false;
		break;
	case 4: 
		if (day > 0 && day < 31) return true;
		  else return false;
		break;
	case 5:if (day > 0 && day < 32) return true;
		  else return false;
		break;
	case 6:if (day > 0 && day < 31) return true;
		  else return false;
		break;
	case 7:if (day > 0 && day < 32) return true;
		  else return false;
		break;
	case 8:if (day > 0 && day < 32) return true;
		  else return false;
		break;
	case 9:if (day > 0 && day < 31) return true;
		  else return false;
		break;
	case 10:if (day > 0 && day < 32) return true;
		  else return false;
		break;
	case 11:if (day > 0 && day < 31) return true;
		  else return false;
		break;
	case 12:if (day > 0 && day < 32) return true;
		   else return false;
		break;
    }
}
bool correctMonth(int month) {
	if (month < 1 || month>12) return false;
	else return true;
}
void inputDate(int& result,int& result2,int& result3) {
	string yr;  bool compr;
	string mnth; bool compr2;
	string dy; bool compr3; bool ultcompr, monthcmpr;
	cout << "Now change your date to  " << endl;
	do {
		cout << "year: "; cin >> yr;
		compr = convertStringToInt(yr, result);
		if (compr == false) cout << "Error Input " << endl;
	} while (compr == false);
	do {
		cout << "month: "; cin >> mnth;
		compr = convertStringToInt(mnth, result2);
		monthcmpr = correctMonth(result2);
		if (compr == false ||monthcmpr==false) cout << "Error Input " << endl;
	} while (compr == false ||monthcmpr==false); cout << endl;
	do {
		cout << "day: "; cin >> dy;
		compr = convertStringToInt(dy, result3);
		ultcompr = correctDate(result2, result, result3);
		if (compr == false || ultcompr == false) cout << "Error Input " << endl;
	} while (compr == false || ultcompr == false); cout << endl;
}
//cac ham chinh 
void editCourse(int numSemester, Semester* pSemester) {
	int x = 10; int y = 5; string choose; int choice; bool formain;
	string acdmy, smstr2, classID, CourseID;
	Semester* smstr = pSemester;
	Semester* s1 = checkAcademicY(smstr, acdmy,y,x);
	if (s1 == nullptr) return;
	Semester* s2 = checkSemester(s1, smstr2,y,x);
	if (s2 == nullptr) return;
	Schedule* s3 = checkClassID(s2, classID,y,x);
	if (s3 == nullptr) return;
	Course* s4 = checkCourse(s3, CourseID, y, x); y++;
	if (s4 == nullptr) return;
	system("cls");
	do {
		goToXY(x, y - 4); cout << "academic year:  " << s1->academicYear;
		goToXY(x, y -3); cout << "Semester: " << s2->semester;
		goToXY(x, y - 2); cout << "Class: "<<s3->cla;
		goToXY(x, y-1); cout << "Course's ID: "<< s4->courseID;
		goToXY(x, y+1);	cout << "Choose option below to change course information: " << endl;
		goToXY(x, y+2); cout << "1. Change a new lecturer" << endl;
		goToXY(x, y+3); cout << "2.Change course's date " << endl;
		goToXY(x, y+4); cout << "3.Change course's room " << endl;
		goToXY(x, y+5); cout << "4.Change start date " << endl;
		goToXY(x, y+6); cout << "5.Change end date " << endl;
		goToXY(x, y+7); cout << "6.Change start time " << endl;
		goToXY(x, y+8); cout << "7.Change end time" << endl;
		goToXY(x, y+9); cout << "0.exit " << endl;
		goToXY(x, y + 10); cout << "                                           ";
		goToXY(x, y + 10); cout << "your option: ";
		cin >> choose; formain=convertStringToInt(choose, choice);
		if (choice > 7 && choice < 0||formain==false) { 
			goToXY(x, y + 11);
			cout << "Enter again!!!!! "; }
		if (choice == 1) {
			Lecturer* lectu = nullptr; int numlect; int count = 0; string lect;
			goToXY(x, y + 11); cout << "                                 ";
			loadLecturer(numlect, lectu);
			do {
				goToXY(x, y + 12); cout << "                                                                                                                                    ";
				goToXY(x, y + 12);
				cout << "Please enter lecturer username that you want to move into this class: "; cin >> lect;
				Lecturer* cur = lectu;
				while (cur->pNext != nullptr) {
					if (lect == cur->username) {
						s4->lecturer.username = cur->username;
						s4->lecturer.fullname = cur->fullname;
						s4->lecturer.degree = cur->degree;
						rewriteCourse(s4, "Semester\\" + s1->academicYear + "-" + s1->semester + "\\" + classID + "\\" + CourseID + ".txt");
						count++;
					}
					cur = cur->pNext;
				}
				if (count == 0) {
					goToXY(x, y + 13);
					cout << "Invalid lecturer username";
				}
				else { 
					goToXY(x, y + 13);
					cout << "your lecture has been changed succesfully "; 

					goToXY(x, y + 14);
					system("pause"); }
			} while (count == 0);
			deleteLecturerList(lectu);
			system("cls");

		}
		if (choice == 2) {
			int pick; string po; bool cm;
			do {
				goToXY(x, y + 10); cout << "                                 ";
				goToXY(x, y + 11); cout << "                                 ";
				goToXY(x, y + 11); cout << "this course date is recurring in " << s4->day << endl;
				goToXY(x, y + 12); cout << "Now change to : " << endl;
				goToXY(x, y + 13); cout << "2.Monday" << endl;
				goToXY(x, y + 14); cout << "3.Tuesday" << endl;
				goToXY(x, y + 15); cout << "4.Wednesday" << endl;
				goToXY(x, y + 16); cout << "5.Thursday" << endl;
				goToXY(x, y + 17); cout << "6.Friday" << endl;
				goToXY(x, y + 18); cout << "7.Saturday" << endl;
				goToXY(x, y + 19); cout << "8.Sunday" << endl;
				goToXY(x, y + 20); cout << "your choice: "; cin >> po; cm=convertStringToInt(po, pick); cout << endl;
				if (pick == 2) { s4->day = "MON"; }
				if (pick == 3) { s4->day = "TUE"; }
				if (pick == 4) { s4->day = "WED"; }
				if (pick == 5) { s4->day = "THU"; }
				if (pick == 6) { s4->day = "FRI"; }
				if (pick == 7) { s4->day = "SAT"; }
				if (pick == 8) { s4->day = "SUN"; }
			} while (x < 2 && x>8 || cm == false);
			rewriteCourse(s4, "Semester\\"+s1->academicYear+"-"+s1->semester+"\\" + classID + "\\" + CourseID + ".txt");
			system("cls");
		}
		if (choice == 3) {
			string roomID;
			cout << "the room ID for the course is: " << s4->room << endl;
			cout << "Now change to room : "; cin >> roomID;
			s4->room = roomID;
			rewriteCourse(s4, "Semester\\" + s1->academicYear + "-" + s1->semester + "\\" + classID + "\\" + CourseID + ".txt");
		}
		if (choice == 4) {
			cout << "current start date is " << s4->dateStart.year << " " << s4->dateStart.month << " " << s4->dateStart.day << endl;
			int yr, mnth, dy;
			inputDate(yr,mnth,dy);
			s4->dateStart.year = yr;
			s4->dateStart.month = mnth;
			s4->dateStart.day = dy;
			rewriteCourse(s4, "Semester\\" + s1->academicYear + "-" + s1->semester + "\\" + classID + "\\" + CourseID + ".txt");
		}
		if (choice == 5) {
			cout << "current end date is " << s4->dateEnd.year << " " << s4->dateEnd.month << " " << s4->dateEnd.day << endl;
			int yr, mnth, dy;
			inputDate(yr, mnth, dy);
			s4->dateEnd.year = yr;
			s4->dateEnd.month = mnth;
			s4->dateEnd.day = dy;
			rewriteCourse(s4, "Semester\\" + s1->academicYear + "-" + s1->semester + "\\" + classID + "\\" + CourseID + ".txt");
		}
		if (choice == 6) {
			cout << "current start time is " << s4->timeStart.hour << " " << s4->timeStart.minute << endl;
			cout << "Now change your start time to  " << endl;
			int hr; int min;
			do {
				cout << "hour : "; cin >> hr;
				if (hr < 0 || hr>24) cout << "Error Input ";
		    } while (hr < 0 || hr>24);
			do {
				cout << "minute : "; cin >> min;
				if (min < 0 || min>60) cout << "Error Input ";
			} while (min < 0 || min>60);
			s4->timeStart.hour = hr;
			s4->timeStart.minute = min;
			rewriteCourse(s4, "Semester\\" + s1->academicYear + "-" + s1->semester + "\\" + classID + "\\" + CourseID + ".txt");
		}
		if (choice == 7) {
			cout << "current end time is " << s4->timeEnd.hour << " " << s4->timeEnd.minute << endl;
			cout << "Now change your end time to  " << endl;
			int hr; int min;
			do {
				cout << "hour : "; cin >> hr;
				if (hr < 0 || hr>24) cout << "Error Input ";
			} while (hr < 0 || hr>24);
			do {
				cout << "minute : "; cin >> min;
				if (min < 0 || min>60) cout << "Error Input ";
			} while (min < 0 || min>60);
			s4->timeEnd.hour = hr;
			s4->timeEnd.minute = min;
			rewriteCourse(s4, "Semester\\" + s1->academicYear + "-" + s1->semester + "\\" + classID + "\\" + CourseID + ".txt");
		}
	} while (choice != 0 || formain == false);
}
void removeCourse(int numSemester, Semester* pSemester) {
	int x = 10; int y = 5; int ch;
	cout << "To delete course, you have to input some information " << endl;
	string acdmy, smstr2, classID, CourseID;
	Semester* smstr = pSemester;
	Semester* s1 = checkAcademicY(smstr, acdmy,y,x);
	if (s1 == nullptr) return;
	Semester* s2 = checkSemester(s1, smstr2,y,x);
	if (s2 == nullptr) return;
	Schedule* s3 = checkClassID(s2, classID,y,x);
	if (s3 == nullptr) return;
	Course* s4 = checkCourse(s3, CourseID,y,x);
	if (s4 == nullptr) return;
	cout << "Do you really want to delete this course ? " << endl;
	do {
		cout << "1.Yes->continue " << endl;
		cout << "0.No->exit" << endl;
		cout << "your choice: "; cin >> ch;
	} while (ch != 0 && ch != 1);
	if (ch == 0) return;
	if (ch == 1) {
		int j = 0; Course* s0=nullptr;
		loadCourseList(j, s0,"Semester\\2018-2019-HK2\\" + s3->cla + "\\", s3->cla);
		if (s0->courseID == s4->courseID) {
			Course* tempt = s0;
			s0 = s0->pNext; cout << s0->courseID;
			delete tempt;
		}
		Course* cur = s0;
		while (cur->pNext != nullptr) {
			if (cur->pNext->courseID == s4->courseID) {
				Course* tempt = cur->pNext;
				cur->pNext = cur->pNext->pNext;
				delete tempt;
			}
			else {
				cur = cur->pNext; }
		}
		rewriteCourseList(j-1,s0, "Semester\\2018-2019-HK2\\" + s3->cla + "\\" + s3->cla + ".txt");
		deleteCourseList(s0);
		
		string sdel= "Semester\\2018-2019-HK2\\" + s3->cla + "\\" + s4->courseID + ".txt";
		char* cstr=new char[sdel.size() + 1];
		sdel.copy(cstr, sdel.size() + 1);
		cstr[sdel.size()] = '\0';
		remove(cstr);
	}
}
void removeStudentfromCourse(int numSemester, Semester* pSemester) {
	int x = 10; int y = 5; int ch;
	string acdmy, smstr2, classID, CourseID,student;
	Semester* smstr = pSemester;
	Semester* s1 = checkAcademicY(smstr, acdmy,y,x);
	if (s1 == nullptr) return;
	Semester* s2 = checkSemester(s1, smstr2,y,x);
	if (s2 == nullptr) return;
	Schedule* s3 = checkClassID(s2, classID,y,x);
	if (s3 == nullptr) return;
	Course* s4 = checkCourse(s3, CourseID,y,x);
	if (s4 == nullptr) return;
	cout << "Enter Student that you want to remove from the course: " << endl;
	Student*st=checkStudent(s4, student,y,x);
	if (st == nullptr) return;
	cout << "Do you really want to remove this student from the course ? " << endl;
	do {
		cout << "1.Yes->continue " << endl;
		cout << "0.No->exit" << endl;
		cout << "your choice: "; cin >> ch;
	} while (ch != 0 && ch != 1);
	if (ch == 0) return;
	if (ch == 1) {
		if (st->id == s4->pStudent->id) {
			Student* tempt = s4->pStudent;
			s4->pStudent = s4->pStudent->pNext;
			delete tempt;
		}
		Student* curst = s4->pStudent;
		while (curst->pNext != nullptr) {
			if (st->id == curst->id) {
				Student* tempt = curst;
				curst->pNext = curst->pNext->pNext;
				delete tempt;
			}
			else curst = curst->pNext;
		}
		s4->numStudent--;
		rewriteCourse(s4, "Semester\\2018-2019-HK2\\" + classID + "\\" + CourseID + ".txt");
		
	}

}
void editAttendance(int numSemester, Semester* pSemester) {
	int x = 10; int y = 5; int ch,ngay,ap;
	string acdmy, smstr2, classID, CourseID, student;
	Semester* smstr = pSemester;
	Semester* s1 = checkAcademicY(smstr, acdmy, y, x);
	if (s1 == nullptr) return;
	Semester* s2 = checkSemester(s1, smstr2, y, x);
	if (s2 == nullptr) return;
	Schedule* s3 = checkClassID(s2, classID, y, x);
	if (s3 == nullptr) return;
	Course* s4 = checkCourse(s3, CourseID, y, x);
	if (s4 == nullptr) return;
	Student* curStudent = s4->pStudent;
	cout << "Enter Student that you want to edit attendance: " << endl;
	y++;
	Student* st = checkStudent(s4, student, y, x);
	if (st == nullptr) return;
	while (curStudent->id != st->id) curStudent = curStudent->pNext;
	for (int i = 0; i < 10; i++) {
		cout << curStudent->attend[i] << " ";
	}
	cout << "Edit Attendance information " << endl;
	cout << "Enter day: "; cin >> ngay; cout << endl;
	cout << "Absent or Present ?(Present(1) /Absent(0))"; cin >> ap; cout << endl;
	curStudent->attend[ngay] = ap;
	rewriteCourse(s4, "Semester\\" + s1->academicYear + "-" + s1->semester + "\\" + classID + "\\" + CourseID + ".txt");

}
void editScore(int numSemester, Semester* pSemester) {
	int x = 10; int y = 5; int ch, choices,diem;
	string acdmy, smstr2, classID, CourseID, student;
	Semester* smstr = pSemester;
	Semester* s1 = checkAcademicY(smstr, acdmy, y, x);
	if (s1 == nullptr) return;
	Semester* s2 = checkSemester(s1, smstr2, y, x);
	if (s2 == nullptr) return;
	Schedule* s3 = checkClassID(s2, classID, y, x);
	if (s3 == nullptr) return;
	Course* s4 = checkCourse(s3, CourseID, y, x);
	if (s4 == nullptr) return;
	Student* curStudent = s4->pStudent;
	cout << "Enter Student that you want to edit scorre: " << endl;
	y++;
	Student* st = checkStudent(s4, student, y, x);
	if (st == nullptr) return;
	while (curStudent->id != st->id) curStudent = curStudent->pNext;
	cout << "Choose type of score " << endl;
	cout << "1.bonus" << endl;
	cout << "2.midterm" << endl;
	cout << "3.final" << endl;
	cout << "4.total" << endl;
	cout << "Your choice: "; cin >> choices;
	cout << "Enter new score : "; cin >> diem;
	if (choices == 1) curStudent->grade.bonus = diem;
	if (choices == 2) curStudent->grade.bonus = diem;
	if (choices == 3) curStudent->grade.bonus = diem;
	if (choices == 4) curStudent->grade.bonus = diem;
	rewriteCourse(s4, "Semester\\" + s1->academicYear + "-" + s1->semester + "\\" + classID + "\\" + CourseID + ".txt");

}