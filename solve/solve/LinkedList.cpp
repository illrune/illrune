#include "LinkedList.h"

Node::Node(const int& v, const pointer& p, const pointer& n)
: value(v), prev(p), next(n)
{
}
Node::Node(const pointer& p, const pointer& n)
: prev(p), next(n)
{
}

///////////////////////////////////////////

cLinkedList_int::cLinkedList_int()
: size(0)
{
	tail = new Node(NULL, NULL);
	head = new Node(NULL, tail);

	tail->prev = head;
}
cLinkedList_int::~cLinkedList_int()
{
	while(head)
	{
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}
}
void cLinkedList_int::insert_pos(const int& pos, const int& i)
{
	if(pos > abs(size))
		std::cout << "over pos." << std::endl;

	else
	{
		Node* current = head;

		for (int j = 0; j < pos; j++)
		{
			current = current->next;
		}

		Node* node = new Node(i, current, current->next);
		node->prev->next = node;
		node->next->prev = node;

		size++;
	}
}
void cLinkedList_int::remove_pos(const int& pos)
{
	if(pos >= abs(size))
		std::cout << "over pos." << std::endl;

	else
	{
		Node* current = head;

		for (int j = 0; j < pos; j++)
		{
			current = current->next;
		}

		if (current->next == tail)
			std::cout << "empty." << std::endl;
		else
		{
			current->prev->next = current->next;
			current->next->prev = current->prev;

			delete current;

			size--;
		}
	}
}

void cLinkedList_int::insert_front(const int& i)
{
	Node* node = new Node(i, head, head->next);
	node->prev->next = node;
	node->next->prev = node;
	size++;
}
void cLinkedList_int::remove_front()
{
	if(empty())
		std::cout << "underflow." << std::endl;

	else
	{
		Node* node = head->next;

		node->prev->next = node->next;
		node->next->prev = node->prev;

		delete node;

		size--;
	}

}

void cLinkedList_int::insert_back(const int& i)
{
	Node* node = new Node(i, tail->prev, tail);
	node->prev->next = node;
	node->next->prev = node;

	size++;
}
void cLinkedList_int::remove_back()
{
	if(empty())
		std::cout << "underflow." << std::endl;

	else
	{
		Node* node = tail->prev;

		node->prev->next = node->next;
		node->next->prev = node->prev;		

		delete node;

		size--;
	}
}

void cLinkedList_int::print_front()
{
	Node* current = head;

	if(empty())
		std::cout << "List empty.";

	while(current)
	{
		if (current == head || current == tail)
		{
			current = current->next;
			continue;
		}

		std::cout << current->value << ", ";

		current = current->next;
	}

	std::cout << std::endl;
}
void cLinkedList_int::print_back()
{
	Node* current = tail;

	if(empty())
		std::cout << "List empty.";

	while(current)
	{
		if (current == head || current == tail)
		{
			current = current->prev;
			continue;
		}

		std::cout << current->value << ", ";

		current = current->prev;
	}

	std::cout << std::endl;
}
int cLinkedList_int::getvalue_front()
{
	if(!empty())
		return head->next->value;
	else
		return 0;
}
int cLinkedList_int::getvalue_back()
{
	if(!empty())
		return tail->prev->value;
	else
		return 0;
}

bool cLinkedList_int::empty()
{
	return (head->next == tail);
}