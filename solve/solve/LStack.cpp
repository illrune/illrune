#include "LStack.h"

cLStack::cLStack()
{
}
cLStack::~cLStack()
{
}

void cLStack::push(const int& i)
{
	slist.insert_back(i);
}
int cLStack::pop()
{
	if(!slist.empty())
	{
		int tmp = slist.getvalue_back();
		slist.remove_back();

		return tmp;
	}
	
	else
		std::cout << "stacklist empty." << std::endl;

	return 0;
}

void cLStack::print()
{
	slist.print_back();
}