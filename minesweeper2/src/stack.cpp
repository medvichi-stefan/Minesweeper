#pragma once
#include "../include/stack.h"

Stack::Stack()
{
	topNode = 0;
}

Stack::Stack(const Position &position)
{
	Node *newNode = new Node;
	newNode->info = position;
	newNode->next = 0;
	topNode = newNode;
}

Stack::~Stack()
{
	while (this->isEmpty() == false)
	{
		this->pop();
	}
}

Position Stack::top()
{
	return topNode->info;
}

void Stack::push(const Position &value)
{
	Node *newNode = new Node;
	newNode->info = value;
	newNode->next = 0;
	if (this->isEmpty())
	{
		topNode = newNode;
	}
	else
	{
		newNode->next = topNode;
		topNode = newNode;
	}
}

void Stack::pop()
{
	if (topNode != 0)
	{
		Node *nodeToDelete = topNode;
		topNode = topNode->next;
		delete nodeToDelete;
	}
}

bool Stack::isEmpty()
{
	if (topNode == 0) return true;
	else return false;
}