#include <iostream>
#include <conio.h>
#include <cstring>

#include <windows.h>
#include <process.h>

using namespace std;

struct stru
{
	char a[20];
	int b;
};

unsigned __stdcall foo(void* arg)
{
	DWORD tick = ::GetTickCount();

	while(::GetTickCount() - tick < 1000)
	{
		cout << "hello ";
		//cout << *((char*)arg) << ' ';
		cout << *((int*)arg) << endl;
	}

	return 0;
}

int main(void)
{
	stru hi;

	cout << "이름입력 : ";
	cin >> hi.a;

	cout << "나이입력 : ";
	cin >> hi.b;

	unsigned id;
	HANDLE hThread = (HANDLE)::_beginthreadex(NULL,0,&foo,&hi,0,&id);

	_getch();
	return 0;
}