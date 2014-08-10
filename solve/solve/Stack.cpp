#pragma once

#include "Stack.h"

cStack::cStack()
: top(-1)
{
	for(int i = 0; i < 5; i++)
	{
		Data[i] = NULL;
	}
}
cStack::~cStack()
{
}

void cStack::push(const int& i)
{
	if (i < 4)
	{
		top++;
		Data[top] = i;
	}
	else
	{
		std::cout << "overflow" << std::endl;
	}
}
int cStack::pop()
{
	if (top < 0)
	{
		std::cout << "underflow.";
	}
	else
	{
		int tmp = Data[top];
		Data[top] = NULL;
		top--;
		return tmp;
	}

	return NULL;
}
void cStack::print()
{
	if (top < 0)
	{
		std::cout << "empty stack.";
	}

	else
	{
		for(int i = top; i >= 0; i--)
		{
			std::cout << Data[i] << ", ";
		}
	}

	std::cout << std::endl;
}