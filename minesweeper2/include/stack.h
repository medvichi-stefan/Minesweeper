#pragma once
#ifndef STACK_H
#define STACK_H

#include "position_struct.h"

struct Node
{
	Position info;
	Node *next;
};

struct Stack
{
	Node *topNode;

	Stack();
	Stack(const Position &position);
	~Stack();
	Position top();
	void push(const Position &value);
	void pop();
	bool isEmpty();
};

#endif