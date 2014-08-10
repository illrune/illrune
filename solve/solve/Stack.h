#include <iostream>

class cStack
{
public :
	cStack();
	~cStack();
public :
	void push(const int& );
	int pop();
	void print();

private :
	int Data[5];
	int top;
};