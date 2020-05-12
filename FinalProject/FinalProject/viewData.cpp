#include "function.h"

void viewClass(Class*&pClass){
	if (pClass == nullptr) {
		cout << "There is no class in stored data" << endl;
	}

	else {
		Class* cur = pClass;
		cout << "Classes: " << endl;
		while (cur != nullptr) {
			cout << cur->name << endl;
			cur = cur->pNext;
		}
	}
}

void viewStudentsInClass(Student* pStudent, string name) {
	int option;

	cout << "Please choose the class you want to view information" << endl;
	cout << ">>>>> Menu <<<<<" << endl;
	cout << "1. 19APCS1" << endl;
	cout << "2. 19APCS2" << endl;
	cout << "3. 19CLC1" << endl;
	cout << "4. 19CLC2" << endl;
	cout << "5. 19CLC3" << endl;
	cout << "6. 19CLC4" << endl;
	cout << "7. 19CLC5" << endl;
	cout << "8. 19CLC6" << endl;
	cout << "9. 19CLC7" << endl;
	cout << "10. 19CLC8" << endl;
	cout << "11. 19CLC9" << endl;
	cout << "12. 19CLC10" << endl;
	cout << "13. 18APCS1" << endl;
	cout << "14. 18APCS2" << endl;
	cout << "15. 18APCS3" << endl;
	cout << "16. 18CLC1" << endl;
	cout << "17. 18CLC2" << endl;
	cout << "18. 18CLC3" << endl;
	cout << "19. 18CLC4" << endl;
	cout << "20. 18CLC5" << endl;
	cout << "21. 18CLC6" << endl;
	cin >> option;

	switch (option) {
	case 1:
	{
		string classname = "19APCS1";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 2:
	{
		string classname = "19APCS2";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 3:
	{
		string classname = "19CLC1";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 4:
	{
		string classname = "19CLC2";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 5:
	{
		string classname = "19CLC3";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 6:
	{
		string classname = "19CLC4";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 7:
	{
		string classname = "19CLC5";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 8:
	{
		string classname = "19CLC6";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 9:
	{
		string classname = "19CLC7";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 10:
	{
		string classname = "19CLC8";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 11:
	{
		string classname = "19CLC9";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 12:
	{
		string classname = "19CLC10";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 13:
	{
		string classname = "18APCS1";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 14:
	{
		string classname = "18APCS2";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 15:
	{
		string classname = "18APCS3";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 16:
	{
		string classname = "18CLC1";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 17:
	{
		string classname = "18CLC2";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 18:
	{
		string classname = "18CLC3";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 19:
	{
		string classname = "18CLC4";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 20:
	{
		string classname = "18CLC5";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	case 21:
	{
		string classname = "19CLC6";
		loadStudent(pStudent, classname);

		if (pStudent == nullptr) {
			cout << "There is no information about this class" << endl;
		}
		else
		{
			Student* cur = pStudent;
			while (cur != nullptr) {
				cout << cur->fullname << " - ";
				cout << cur->id;
				cur = cur->pNext;
			}
		}
	}
	}
}