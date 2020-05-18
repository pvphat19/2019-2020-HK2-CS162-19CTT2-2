#include "function.h"

void viewClass(Class*&pClass){
	if (pClass == nullptr) {
		cout << "There is no class in stored data" << endl;
	}

	else {
		Class* cur = pClass;
		int i = 1;
		cout << "Here is the list of class:" << endl;
		while (cur != nullptr) {
			cout << i << ". " << cur->name << endl;
			cur = cur->pNext;
			++i;
		}
	}
}

	Node* cur = pClass;

	// View Selection
	cout << "Choose the class you want to view students list: " << endl;
	int i = 0;
	while (cur != nullptr) {
		cout << i + 1 << ". " << cur->name << endl;
		cur = cur->pNext;
		++i;
	}

	cur = pClass;
	int count = 1;
	int choice;

	cout << "Choice: ";
	cin >> choice;

	while (cur != nullptr) {
		if (count == choice) {
			cout << cur->pStudent->fullname << " - " << cur->pStudent->id << endl;
			if (cur->pStudent == nullptr) break;
		}
		else {
			++count;
			cur = cur->pNext;
		}

		while (cur->pStudent != nullptr) {
			cout << cur->pStudent->fullname << " - " << cur->pStudent->id << endl;
			cur->pStudent = cur->pStudent->pNext;
		}
		break;
	}
	case 17:
	{
		string classname = "18CLC2";
		Class* cur = pClass;

		while (cur != nullptr) {
			if (cur->name == classname) {
				break;
			}
			cur = cur->pNext;
		}

		while (cur->pStudent != nullptr) {
			cout << cur->pStudent->fullname << " - " << cur->pStudent->id << endl;
			cur->pStudent = cur->pStudent->pNext;
		}
		break;
	}
	case 18:
	{
		string classname = "18CLC3";
		Class* cur = pClass;

		while (cur != nullptr) {
			if (cur->name == classname) {
				break;
			}
			cur = cur->pNext;
		}

		while (cur->pStudent != nullptr) {
			cout << cur->pStudent->fullname << " - " << cur->pStudent->id << endl;
			cur->pStudent = cur->pStudent->pNext;
		}
		break;
	}
	case 19:
	{
		string classname = "18CLC4";
		Class* cur = pClass;

		while (cur != nullptr) {
			if (cur->name == classname) {
				break;
			}
			cur = cur->pNext;
		}

		while (cur->pStudent != nullptr) {
			cout << cur->pStudent->fullname << " - " << cur->pStudent->id << endl;
			cur->pStudent = cur->pStudent->pNext;
		}
		break;
	}
	case 20:
	{
		string classname = "18CLC5";
		Class* cur = pClass;

		while (cur != nullptr) {
			if (cur->name == classname) {
				break;
			}
			cur = cur->pNext;
		}

		while (cur->pStudent != nullptr) {
			cout << cur->pStudent->fullname << " - " << cur->pStudent->id << endl;
			cur->pStudent = cur->pStudent->pNext;
		}
		break;
	}
	case 21:
	{
		string classname = "19CLC6";
		Class* cur = pClass;

		while (cur != nullptr) {
			if (cur->name == classname) {
				break;
			}
			cur = cur->pNext;
		}

		while (cur->pStudent != nullptr) {
			cout << cur->pStudent->fullname << " - " << cur->pStudent->id << endl;
			cur->pStudent = cur->pStudent->pNext;
		}
		break;
	}
	}
}