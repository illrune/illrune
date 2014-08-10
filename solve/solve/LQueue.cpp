#include "LQueue.h"

cLQueue::cLQueue()
{
}
cLQueue::~cLQueue()
{
}

void cLQueue::enqueue(const int& i)
{
	qlist.insert_back(i);
}
int cLQueue::dequeue()
{
	if(qlist.empty())
		std::cout << "queuelist empty." << std::endl;
	else
	{
		int tmp = qlist.getvalue_front();
		qlist.remove_front();
		return tmp;
	}

	return 0;
}

void cLQueue::print()
{
	qlist.print_front();
}