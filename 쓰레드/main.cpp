#include <iostream>
#include <conio.h>

#include <windows.h>
#include <tchar.h>
#include <process.h>
#include <fstream>
#include <list>

using namespace std;

struct Division
{
	int s;
	int e;

	int pcount;

	friend std::istream& operator >> (std::istream& is, Division& obj)
	{
		is >> obj.s;
		is >> obj.e;

		return is;
	}
};
struct ThreadInfo
{
	HANDLE hThread;
	unsigned uId;
};

bool IsPrime(int n)
{
	if (n == 1)
		return false;

	for (int i = 2; i <= n/2; i++)
	{
		if (n%i == 0)
			return false;
	}

	return true;
}

int Prime(int s, int e)
{
	int primecount = 0;
	fstream file;
	DWORD tick = ::GetTickCount();

	list<int> primelist;

	for (int i = s; i <= e; i++)
	{
		if(IsPrime(i))
		{
			primecount++;
			primelist.push_back(i);
		}
	}

	file.open("prime.p", ios_base::out);

	list<int>::iterator it;
	int enter = 0;

	for (it = primelist.begin(); it != primelist.end(); it++)
	{
		file << *it << ' ';
		enter++;
		
		if(enter >= 10)
		{
			file << endl;
			enter = 0;
		}
	}

	file.close();

	cout << "[ " << "prime count : " << primecount << " ]" << endl;
	cout << "[ " << ::GetTickCount() - tick << " ms." << " ]" << endl;

	return primecount;
}

unsigned __stdcall PrimeThread(void* arg)
{
	Division* saen = (Division*)arg;
	saen->pcount = Prime(saen->s, saen->e);	

	return 0;
}

void Thread()
{
	int count;
	int total = 0;

	cout << "몇 개? :";
	cin >> count;

	list<Division*> divilist;

	for(int i = 0; i < count; i++)
	{
		Division* divi = new Division;
		cin >> *divi;
		divilist.push_back(divi);
	}

	list<ThreadInfo*> threadlist;
	for(int i = 0; i < count; i++)
	{
		list<Division*>::iterator it = divilist.begin();
		advance(it, i);

		ThreadInfo* info = new ThreadInfo;
		info->hThread = (HANDLE)::_beginthreadex(NULL,0,&PrimeThread,(void*)*it,0,&(info->uId));
		threadlist.push_back(info);
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
		list<Division*>::iterator ut = divilist.begin();
		advance(ut, index);

		cout << "delete userinfo ... " << (*ut)->s << '~' << (*ut)->e << endl;
		
		total += (*ut)->pcount;

		delete *ut;
		divilist.erase(ut);

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
	cout << "total count : " << total << endl;
}
int main(void)
{
	Thread();

	// 이야 내가 해냈다

	_getch();
	return 0;
}