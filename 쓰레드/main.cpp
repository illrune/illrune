#include <iostream>
#include <conio.h>
#include <string>

#include <windows.h>
#include <process.h>

using namespace std;

struct UserInfo
{
	std::string name;
	int age;
	int time;

	friend std::ostream& operator << (std::ostream& os, const UserInfo& obj)
	{
		os << obj.name << ' ' << obj.age << endl;

		return os;
	}
	friend std::istream& operator >> (std::istream& is, UserInfo& obj)
	{
		is >> obj.name;
		is >> obj.age;
		is >> obj.time;

		return is;
	}
};

unsigned __stdcall foo(void* arg)
{
	DWORD tick = ::GetTickCount();

	cout << "foo called" << endl;

	UserInfo* Info = (UserInfo*)arg;

	while(::GetTickCount() - tick < unsigned(Info->time))
	{
		cout << "hello ";
		cout << *Info;
	}

	cout << "end thread : " << Info->name << endl;

	return 0;
}

void bar()
{
	int tcount = 0;

	UserInfo* info0 = new UserInfo;
	cin >> *info0;

	UserInfo* info1 = new UserInfo;
	cin >> *info1;

	UserInfo* info2 = new UserInfo;
	cin >> *info2;

	unsigned id[3];
	HANDLE hThread[3];

	hThread[0] = (HANDLE)::_beginthreadex(NULL,0,&foo,info0,0,&id[0]);
	hThread[1] = (HANDLE)::_beginthreadex(NULL,0,&foo,info1,0,&id[1]);
	hThread[2] = (HANDLE)::_beginthreadex(NULL,0,&foo,info2,0,&id[2]);

	do{
		if (::WaitForMultipleObjects(3-tcount, hThread, FALSE, INFINITE) == WAIT_OBJECT_0)
		{
			if (info0)
			{
				cout << "delete info 0" << endl;
				delete info0;
				info0 = NULL;
				tcount++;
			}
		}

		if (::WaitForMultipleObjects(3-tcount, hThread, FALSE, INFINITE) == WAIT_OBJECT_0 + 1)
		{
			if (info1)
			{
				cout << "delete info 1" << endl;
				delete info1;
				info1 = NULL;
				tcount++;
			}
		}

		if (::WaitForMultipleObjects(3-tcount, hThread, FALSE, INFINITE) == WAIT_OBJECT_0 + 2)
		{
			if (info2)
			{
				cout << "delete info 2" << endl;
				delete info2;
				info2 = NULL;
				tcount++;
			}
		}
	}while(tcount < 3);
}

int main(void)
{	
	bar();

	_getch();
	return 0;
}