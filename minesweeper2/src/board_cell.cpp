#pragma once
#include "../include/board_cell.h"

void BoardCell::initialize()
{
	value = '0';
	isCovered = true;
	isFlagged = false;
	hasBomb = false;
}

void BoardCell::reveal()
{
	isCovered = false;
}

void BoardCell::switchFlag()
{
	isFlagged = 1 ^ isFlagged;
}

void BoardCell::placeMine()
{
	value = 'M';
	hasBomb = true;
}

bool BoardCell::isMine()
{
	return hasBomb;
}