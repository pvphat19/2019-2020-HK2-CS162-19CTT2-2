#include "function.h"

void replicateStaff(Staff* origin, Staff*& copy)
{
	if (origin == nullptr)
	{
		copy = nullptr;
		return;
	}
	copy = new Staff;
	copy->username = origin ->username;
	copy->password = origin->password;
	copy->fullname = origin->fullname;
	copy->gender = origin->gender;
}
bool isStaff(string username, string password, Staff*& curStaff)
{
	goToXY(1, 1);
	cout << username << endl;
	cout << password << endl;
	system("pause");

	int numStaff = 0;
	Staff* pStaff = nullptr;
	loadStaff(numStaff, pStaff);

	Staff* cur = pStaff;
	while (cur)
	{
		if ((username == cur->username) && (password == cur->password))
			break;
		cur = cur->pNext;
	}
	replicateStaff(cur, curStaff);
	deleteStaffList(pStaff);
	if (curStaff)
		return true;
	else
		return false;
}