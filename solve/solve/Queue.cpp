#include "Queue.h"

cQueue::cQueue()
: first(0),rear(0)
{
	for(int i = 0; i < 5; i++)
	{
		Data[i] = NULL;
	}
}
cQueue::~cQueue()
{
}

void cQueue::enqueue(const int& i)
{
	if(rear < 4)
	{
		Data[rear] = i;
		rear++;
	}

	else
		std::cout << "overflow." << std::endl;
}
int cQueue::dequeue()
{
	if (first >= rear)
	{
		std::cout << "underflow." << std::endl;
	}
	else
	{
		int tmp = Data[first];
		Data[first] = NULL;
		first++;

		return tmp;
	}
	
	return 0;
}
void cQueue::print()
{
	if (first == rear)
	{
		std::cout << "empty queue.";
	}

	else
	{
		for(int i = first; i < rear; i++)
		{
			std::cout << Data[i] << ", ";
		}
	}
	
	std::cout << std::endl;
}