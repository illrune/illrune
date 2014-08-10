#pragma once

#include <iostream>

class cQueue
{
public :
	cQueue();
	~cQueue();

public :
	void enqueue(const int& );
	int dequeue();
	void print();

private :
	int Data[5];
	int first;
	int rear;
};