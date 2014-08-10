#pragma once

#include <iostream>

struct Node
{
	typedef Node* pointer;

	Node(const int& v, const pointer& p, const pointer& n);
	Node(const pointer& p, const pointer& n);

	int value;
	Node* prev;
	Node* next;
};

class cLinkedList_int
{
public :
	cLinkedList_int();
	~cLinkedList_int();

public :
	void insert_front(const int& );
	void remove_front();

	void insert_back(const int& );
	void remove_back();

	void print_front();
	void print_back();

	int getvalue_front();
	int getvalue_back();

	bool empty();

private :
	Node* head;
	Node* tail;
};