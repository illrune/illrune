#pragma once

#include "LinkedList.h"

class cLStack
{
public :
	cLStack();
	~cLStack();
	
public :
	void push(const int& );
	int pop();

	void print();

private :
	cLinkedList_int slist;
};