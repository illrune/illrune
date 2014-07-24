#include <iostream>
#include <conio.h>

using namespace std;

bool IsPrime(int n)
{
	for (int i = 2; i <= n/2; i++)
	{
		if (n%i == 0)
			return false;
	}

	return true;
}

void Prime()
{
	for (int i = 1; i < 100000; i++)
	{
		if(IsPrime(i))
			cout << i << endl;
	}
}

int main(void)
{
	Prime();

	// 쓰레드로 적절히 분배
	// 소수를 구하는데 걸린 시간
	// 소수의 갯수

	_getch();
	return 0;
}