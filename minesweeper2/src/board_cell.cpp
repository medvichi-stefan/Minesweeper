#include "../include/board_cell.h"

void BoardCell::initialize()
{
	value = '0';
	isCovered = true;
	isFlagged = false;
	hasBomb = false;
}

void BoardCell::uncover()
{
	isCovered = false;
}

void BoardCell::switchFlag()
{
	isFlagged = 1 ^ isFlagged;
}