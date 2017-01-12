#pragma once
#ifndef BOARD_CELL_H
#define BOARD_CELL_H

#include "stdafx.h"

struct BoardCell
{
	char value; // number of mined neighbours
	bool covered;
	bool hasBomb;
	bool flagged;

	void initialize();
	void reveal();
	void switchFlag();
	void placeMine();
	void incrementValue();

	char getValue();

	bool isMine();
	bool isFlagged();
	bool isCovered();
};

#endif