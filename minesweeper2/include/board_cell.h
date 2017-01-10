#pragma once
#ifndef BOARD_CELL_H
#define BOARD_CELL_H

#include "stdafx.h"

struct BoardCell
{
	char value; // number of mined neighbours
	bool isCovered;
	bool hasBomb;
	bool isFlagged;

	void initialize();
	void reveal();
	void switchFlag();
	void placeMine();
	bool isMine();
};

#endif