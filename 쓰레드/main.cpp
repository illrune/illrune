#include <iostream>
#include <conio.h>
#include <string>
#include <list>

#include <windows.h>
#include <process.h>

using namespace std;

struct UserInfo
{
	std::string name;
	int time;

	friend std::ostream& operator << (std::ostream& os, const UserInfo& obj)
	{
		os << obj.name << endl;

		return os;
	}
	friend std::istream& operator >> (std::istream& is, UserInfo& obj)
	{
		is >> obj.name;
		is >> obj.time;

		return is;
	}
};
struct ThreadInfo
{
	HANDLE hThread;
	unsigned uId;
};

unsigned __stdcall foo(void* arg)
{
	DWORD tick = ::GetTickCount();

	UserInfo* Info = (UserInfo*)arg;

	cout << "foo called : " << Info->name << endl;

	while(::GetTickCount() - tick < unsigned(Info->time))
	{
	}

	cout << "end thread : " << Info->name << endl;

	return 0;
}

void bar()
{
	int count;

	cout << "¸î °³? :";
	cin >> count;

	list<UserInfo*> userlist;				

	for(int i = 0; i < count; i++)
	{
		UserInfo* info = new UserInfo;
		cin >> *info;
		userlist.push_back(info);
	}

	list<ThreadInfo*> threadlist;
	for(int i = 0; i < count; i++)
	{
		list<UserInfo*>::iterator it = userlist.begin();
		advance(it, i);

		ThreadInfo* info = new ThreadInfo;
		info->hThread = (HANDLE)::_beginthreadex(NULL,0,&foo,(void*)*it,0,&(info->uId));
		threadlist.push_back(info);
	}
	
	list<ThreadInfo*>::iterator tt;
	int i = 0;
	for(tt = threadlist.begin(); tt != threadlist.end(); tt++, i++)
	{
		cout << i << "/'s thread : " << (*tt)->hThread << endl;
	}

	int remain = count;

	while(remain)
	{
		HANDLE* hThread = new HANDLE[remain];
		list<ThreadInfo*>::iterator tt;
		int i = 0;
		for (tt = threadlist.begin(); tt != threadlist.end(); tt++, i++)
		{
			hThread[i] = (*tt)->hThread;
		}

		DWORD index = ::WaitForMultipleObjects(remain, hThread, FALSE, INFINITE);

		if (index == WAIT_FAILED)
		{
			cout << "error ..." << endl;
			continue;
		}

		// delete userlist element.
		list<UserInfo*>::iterator ut = userlist.begin();
		advance(ut, index);

		cout << "delete userinfo ..." << (*ut)->name << endl;
		delete *ut;
		userlist.erase(ut);

		// delete threadlist element.
		tt = threadlist.begin();
		advance(tt, index);

		cout << "delete threadinfo ..." << (*tt)->hThread << endl;
		delete *tt;
		threadlist.erase(tt);

		delete [] hThread;

		remain--;
	}

	cout << "end job." << endl;
}

int main(void)
{	
	bar();

	_getch();
	return 0;
}