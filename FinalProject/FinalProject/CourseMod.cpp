#include "function.h"

Semester* checkAcademicY(Semester*& sm, string& s) {
	int count = 0;
	do {
		cout << "Please enter Academic year (Example: 2012-2013): ";
		cin >> s;
		Semester* sms = sm;
		while (sms != nullptr) {
			if (sms->academicYear == s) {
				return sms;
				count++;
			}
			sms = sm->pNext;
		}
		if (count == 0) cout << "Invalid year!!!!" << endl;
	} while (count == 0);
}
Semester* checkSemester(Semester*& sm, string& s) {
	int count = 0;
	do {
		cout << "Please enter semester: ";
		cin >> s;
		Semester* sms = sm;
		while (sms != nullptr) {
			if (sms->semester == s) {
				return sms;
				count++;
			}
			sms = sms->pNext;
		}
		if (count == 0) cout << "Invalid semester!!!!" << endl;
	} while (count == 0);

}
Schedule* checkClassID(Semester*& sm, string& s) {
	int count = 0;
	do {
		cout << "Please enter class ID: ";
		cin >> s;
		Schedule* sche = sm->pSchedule;
		while (sche != nullptr) {
			if (sche->cla == s) {
				return sche;
				count++;
			}
			sche = sche->pNext;
		}
		if (count == 0)	cout << "Invalid class ID!!!!" << endl;
	} while (count == 0);

}
Course* checkCourse(Schedule*& sc, string& s) {
	int count = 0;
	do {
		cout << "Please enter course ID: ";
		cin >> s;
		Course* cour = sc->pCourse;
		while (cour != nullptr) {
			if (cour->courseID == s) {
				return cour;
				count++;
			}
			cour = cour->pNext;
		}
		if (count == 0) cout << "Invalid course ID!!!!" << endl;
	} while (count == 0);
}
Student* checkStudent(Course*& cour, string& s) {
	int count = 0; int Id;
	do {
		cout << "Please enter student ID:  ";
		cin >> s; convertStringToInt(s, Id); cout << endl;
		Student* st = cour->pStudent;
		while (st != nullptr) {
			if (st->id == Id) {
				return st;
				count++;
			}
			st = st->pNext;
		}
		if (count == 0) cout << "This student was not in this course yet!!!!" << endl;
	} while (count == 0);
}
void checkLecturer() {
	Lecturer* lectu = nullptr; int numlect; int count = 0; string lect;
	loadLecturer(numlect, lectu);
	do {
		cout << "Enter lecturer user name: "; cin >> lect;
		Lecturer* cur = lectu;
		while (cur->pNext != nullptr) {
			if (lect == cur->username) {
				count++;
			}
			cur = cur->pNext;
		}
		if (count == 0) cout << "Invalid lecturer username";
	} while (count == 0);
	deleteLecturerList(lectu);

}
bool correctDate(int month, int year, int day) {
	switch (month) {
	case 1: if (day > 0 && day < 32) return true;
		  else return false;
		break;
	case 2:
		if (year % 100 == 0) {
			if (year % 400 == 0) {
				if (day == 29) return true;
				else return false;
			}
			else {
				if (day == 28) return true;
				else return false;
			}
		}
		else if (year % 4 == 0) {
			if (day == 29) return true;
			else return false;
		}
		else {
			if (day == 28) return true;
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
void inputDate(int& result,int& result2,int& result3) {
	string yr;  bool compr;
	string mnth; bool compr2;
	string dy; bool compr3; bool ultcompr;
	cout << "Now change your date to  " << endl;
	do {
		cout << "year: "; cin >> yr;
		compr = convertStringToInt(yr, result);
		if (compr == false) cout << "Error Input " << endl;
	} while (compr == false);
	do {
		cout << "month: "; cin >> mnth;
		compr = convertStringToInt(mnth, result2);
		if (compr == false || (result2 < 1 && result2>12)) cout << "Error Input " << endl;
	} while (compr == false || (result2 < 1 && result2>12)); cout << endl;
	do {
		cout << "day: "; cin >> dy;
		compr = convertStringToInt(dy, result3);
		ultcompr = correctDate(result2, result, result3);
		if (compr == false || ultcompr == false) cout << "Error Input " << endl;
	} while (compr == false || ultcompr == false); cout << endl;
}
//cac ham chinh 
void editCourse(int numSemester, Semester* pSemester) {
	int x = 10; int y = 5; int choose;
	string acdmy, smstr2, classID, CourseID;
	Semester* smstr = pSemester;
	Semester* s1 = checkAcademicY(smstr, acdmy);
	Semester* s2 = checkSemester(s1, smstr2);
	Schedule* s3 = checkClassID(s2, classID);
	Course* s4 = checkCourse(s3, CourseID);
	do {
		cout << "Choose option below to change course information: " << endl;
		cout << "1. Change a new lecturer" << endl;
		cout << "2.Change course's date " << endl;
		cout << "3.Change course's room " << endl;
		cout << "4.Change start date " << endl;
		cout << "5.Change end date " << endl;
		cout << "6.Change start time " << endl;
		cout << "7.Change end time" << endl;
		cout << "0.exit " << endl;
		cout << "your option: " << endl;
		cin >> choose;
		if (choose > 7 && choose < 0) cout << "Enter again ";
		if (choose == 1) {
			checkLecturer();
			Lecturer* lectu = nullptr; int numlect; int count = 0; string lect;
			loadLecturer(numlect, lectu);
			do {
				cout << "Please enter lecturer username that you want to change: "; cin >> lect;
				Lecturer* cur = lectu;
				while (cur->pNext != nullptr) {
					if (lect == cur->username) {
						s4->lecturer.username = cur->username;
						s4->lecturer.fullname = cur->fullname;
						s4->lecturer.degree = cur->degree;
						rewriteCourse(s4, "Semester\\2018-2019-HK2\\" + classID + "\\" + CourseID + ".txt");
						count++;
					}
					cur = cur->pNext;
				}
				if (count == 0) cout << "Invalid lecturer username";
			} while (count == 0);
			deleteLecturerList(lectu);

		}
		if (choose == 2) {
			int pick;
			cout << "this course date is recurring in " << s4->day << endl;
			cout << "Now change to : " << endl;
			cout << "2.Monday" << endl;
			cout << "3.Tuesday" << endl;
			cout << "4.Wednesday" << endl;
			cout << "5.Thursday" << endl;
			cout << "6.Friday" << endl;
			cout << "7.Saturday" << endl;
			cout << "0.Sunday" << endl;
			cout << "your choice: "; cin >> pick; cout << endl;
			if (pick == 2) { s4->day = "MON"; }
			if (pick == 3) { s4->day = "TUE"; }
			if (pick == 4) { s4->day = "WED"; }
			if (pick == 5) { s4->day = "THU"; }
			if (pick == 6) { s4->day = "FRI"; }
			if (pick == 7) { s4->day = "SAT"; }
			if (pick == 8) { s4->day = "SUN"; }
			rewriteCourse(s4, "Semester\\2018-2019-HK2\\" + classID + "\\" + CourseID + ".txt");
		}
		if (choose == 3) {
			string roomID;
			cout << "the room ID for the course is: " << s4->room << endl;
			cout << "Now change to room : "; cin >> roomID;
			s4->room = roomID;
			rewriteCourse(s4, "Semester\\2018-2019-HK2\\" + classID + "\\" + CourseID + ".txt");
		}
		if (choose == 4) {
			cout << "current start date is " << s4->dateStart.year << " " << s4->dateStart.month << " " << s4->dateStart.day << endl;
			int yr, mnth, dy;
			inputDate(yr,mnth,dy);
			s4->dateStart.year = yr;
			s4->dateStart.month = mnth;
			s4->dateStart.day = dy;
			rewriteCourse(s4, "Semester\\2018-2019-HK2\\" + classID + "\\" + CourseID + ".txt");
		}
		if (choose == 5) {
			cout << "current end date is " << s4->dateEnd.year << " " << s4->dateEnd.month << " " << s4->dateEnd.day << endl;
			int yr, mnth, dy;
			inputDate(yr, mnth, dy);
			s4->dateEnd.year = yr;
			s4->dateEnd.month = mnth;
			s4->dateEnd.day = dy;
			rewriteCourse(s4, "Semester\\2018-2019-HK2\\" + classID + "\\" + CourseID + ".txt");
		}
		if (choose == 6) {
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
			rewriteCourse(s4, "Semester\\2018-2019-HK2\\" + classID + "\\" + CourseID + ".txt");
		}
		if (choose == 7) {
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
			rewriteCourse(s4, "Semester\\2018-2019-HK2\\" + classID + "\\" + CourseID + ".txt");
		}
	} while (choose != 0);
}
void removeCourse(int numSemester, Semester* pSemester) {
	int x = 10; int y = 5; int ch;
	cout << "To delete course, you have to input some information " << endl;
	string acdmy, smstr2, classID, CourseID;
	Semester* smstr = pSemester;
	Semester* s1 = checkAcademicY(smstr, acdmy);
	Semester* s2 = checkSemester(s1, smstr2);
	Schedule* s3 = checkClassID(s2, classID);
	Course* s4 = checkCourse(s3, CourseID);
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
		
		int n = sdel.length(); n++;
		char* del=new char[n];
		strcpy(del, sdel.c_str());
		remove(del);
	}
}
void removeStudentfromCourse(int numSemester, Semester* pSemester) {
	int x = 10; int y = 5; int ch;
	string acdmy, smstr2, classID, CourseID,student;
	Semester* smstr = pSemester;
	Semester* s1 = checkAcademicY(smstr, acdmy);
	Semester* s2 = checkSemester(s1, smstr2);
	Schedule* s3 = checkClassID(s2, classID);
	Course* s4 = checkCourse(s3, CourseID);
	cout << "Enter Student that you want to remove from the course: " << endl;
	Student*st=checkStudent(s4, student);
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