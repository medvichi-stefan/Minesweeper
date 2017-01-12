#pragma once
#include "../include/board_cell.h"

void BoardCell::initialize()
{
	value = '0';
	covered = true;
	flagged = false;
	hasBomb = false;
}

void BoardCell::reveal()
{
	covered = false;
}

char BoardCell::getValue()
{
	return value;
}

void BoardCell::switchFlag()
{
	flagged = 1 ^ flagged;
}

void BoardCell::placeMine()
{
	value = 'M';
	hasBomb = true;
}

void BoardCell::incrementValue()
{
	value++;
}

bool BoardCell::isMine()
{
	return hasBomb;
}

bool BoardCell::isFlagged()
{
	return flagged;
}

bool BoardCell::isCovered()
{
	return covered;
}