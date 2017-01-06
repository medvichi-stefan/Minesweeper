#include "../include/stdafx.h"

void Map::initialize()
{
	int i, j;
	for (i = 1; i <= this->rows; ++i)
	{
		for (j = 1; j <= this->columns; ++j)
		{
			this->map[i][j] = '0';
			this->hasBomb[i][j] = false;
			this->isCovered[i][j] = true;
		}
	}
}

void Map::setSize(const unsigned short &rows, const unsigned short &columns)
{
	this->rows = rows;
	this->columns = columns;
}

void Map::print(const int &x, const int &y)
{
	int i, j;
	char litera;
	short int cifra;

	int currentRow, currentColumn;

	setTextColor(COLOR_YELLOW);

	currentRow = y; currentColumn = x - 2;
	for (i = 1, litera = 'a'; i <= this->rows; ++i, currentRow +=2 )
	{
		gotoXY(currentColumn, currentRow);
		printf(" %c ", litera++);
	}

	setTextColor(COLOR_WHITE);
	currentRow = y - 1; currentColumn = x;
	for (i = 1; i <= this->rows * 2; ++i, currentRow += 1)
	{
		gotoXY(currentColumn, currentRow);
		printf("|");
	}

	setTextColor(COLOR_YELLOW);
	currentRow = y - 3; currentColumn = x + 2;
	for (int i = 1, cifra = 1; i <= this->columns; ++i, currentColumn += 3)
	{
		gotoXY(currentColumn, currentRow);
		printf("%d  ", cifra++);
	}

	setTextColor(COLOR_WHITE);
	currentRow = y - 2; currentColumn = x;
	for (int i = 1; i <= this->columns * 3 + 1; ++i, currentColumn += 1)
	{
		gotoXY(currentColumn, currentRow);
		printf("_");
	}

	currentRow = y; currentColumn = x + 1;
	for (i = 1; i <= this->rows; ++i, currentRow+=2)
	{
		gotoXY(currentColumn, currentRow);
		for (j = 1; j <= this->columns; ++j)
		{
			if (this->isCovered[i][j])
			{
				printf(" * ");
			}
			else
			{
				printf(" %c ", this->map[i][j]);
			}
		}
	}
}