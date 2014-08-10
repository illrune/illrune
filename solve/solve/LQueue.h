#pragma once

#include "LinkedList.h"

class cLQueue
{
public :
	cLQueue();
	~cLQueue();

public :
	void enqueue(const int& );
	int dequeue();

	void print();

private :
	cLinkedList_int qlist;
};