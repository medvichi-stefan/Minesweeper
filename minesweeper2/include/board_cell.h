#pragma once
#ifndef FIELD_CELL_H
#define FIELD_CELL_H

struct BoardCell
{
	char value; // number of mined neighbours
	bool isCovered;
	bool hasBomb;
	bool isFlagged;

	void initialize();
	void uncover();
	void switchFlag();
};

#endif