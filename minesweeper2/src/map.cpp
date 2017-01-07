#include "../include/stdafx.h"

void Map::initialize()
{
	int i, j;
	
	this->firstUncover = true;
	for (i = 1; i <= this->rows; ++i)
	{
		for (j = 1; j <= this->columns; ++j)
		{
			this->map[i][j] = '0';
			this->hasBomb[i][j] = false;
			this->isCovered[i][j] = true;
			this->isFlagged[i][j] = false;
		}
	}
}

void Map::setSize(const unsigned short &rows, const unsigned short &columns, const unsigned short &noBombs)
{
	this->rows = rows;
	this->columns = columns;
	this->noBombs = noBombs;
}

void Map::print(const int &x, const int &y)
{
	int i, j;
	char letterIdentifier;
	short int numberIdentifier;

	int currentRow, currentColumn;

	setTextColor(COLOR_YELLOW);

	currentRow = y; currentColumn = x - 2;
	for (i = 1, letterIdentifier = 'a'; i <= this->rows; ++i, currentRow +=2 )
	{
		gotoXY(currentColumn, currentRow);
		printf(" %c ", letterIdentifier++);
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
	for (int i = 1, numberIdentifier = 1; i <= this->columns; ++i, currentColumn += 3)
	{
		gotoXY(currentColumn, currentRow);
		printf("%d  ", numberIdentifier++);
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
			if (this->isFlagged[i][j] && this->isCovered[i][j])
			{
				printf(" M ");
			}
			else if (this->isCovered[i][j])
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

void Map::printInfo(const int &x, const int &y)
{
	char lastLetter;
	short lastNumber;

	lastLetter = this->rows - 1 + 'a';
	lastNumber = this->columns;
	gotoXY(x, y);
	printf("Legend: * - uncovered square, F - flagged, M - uncover more squares, 0-9 - number of neighbours with a mine");
	gotoXY(x, y + 2);
	printf("To choose a square, enter below the coordonates by following this pattern: [F/M][a-%c][1-%d]", lastLetter, lastNumber);
	gotoXY(x, y + 4);
	printf("Choose the square:");
	
}

void Map::printOnScreen()
{
	clearConsole();
	print(MAP_X + MAX_ROWS - this->rows, 5);
	printInfo(TEXT_INFO_X, this->rows * 2 + 5);
}

void Map::processInput()
{
	char playerInput[MAX_INPUT_SIZE];

	readPlayerInput(playerInput, INPUT_SIZE);

	Position positionRequested;
	positionRequested = this->getPositionFromInput(playerInput);
	
	this->updateSquare(positionRequested, playerInput);
}

Position Map::getPositionFromInput(const char *playerInput)
{

	char firstLetter = playerInput[0];
	char row;
	unsigned short column;
	Position currentPosition;

	if (firstLetter == 'F' || firstLetter == 'M')
	{
		row = tolower(playerInput[1]);
		column = getNumberFromString(playerInput + 2);
		currentPosition.row = row - 'a' + 1;
		currentPosition.column = column;
	}
	else
	{
		row = tolower(playerInput[0]);
		column = getNumberFromString(playerInput + 1);
		currentPosition.row = row - 'a' + 1;
		currentPosition.column = column;
	}
	return currentPosition;
}

void Map::updateSquare(const Position &currentPosition, const char *playerInput)
{
	char maxLetter = this->rows - 1 + 'a';
	unsigned short maxNumber = this->columns;
	unsigned short currentNumber;

	if (playerInput[0] == 'F')
	{
		if (isLetterInRange(playerInput[1], maxLetter))
		{
			currentNumber = getNumberFromString(playerInput + 2);
			if (isNumberInRange(currentNumber, maxNumber))
			{
				this->isFlagged[currentPosition.row][currentPosition.column] = 1 ^ isFlagged[currentPosition.row][currentPosition.column];
			}
		}
	}
	else if (playerInput[0] == 'M')
	{

	}
	else
	{
		if (isLetterInRange(playerInput[0], maxLetter))
		{
			currentNumber = getNumberFromString(playerInput + 1);
			if (isNumberInRange(currentNumber, maxNumber))
			{
				if (this->firstUncover)
				{
					this->firstUncover = false;
					this->generateMines();
				}
				if (this->isCovered[currentPosition.row][currentPosition.column] == true)
				{
					this->uncoverAllSquares(currentPosition);
				}
			}
		}
	}
}

void Map::generateMines()
{

}

void Map::uncoverAllSquares(const Position &currentPos)
{

}

inline bool isLetterInRange(const char &currentLetter, const char &maxLetter)
{
	if (currentLetter >= 'a' && currentLetter <= maxLetter) return true;
	else return false;
}

inline bool isNumberInRange(const unsigned short &currentNumber, const unsigned short &maxNumber)
{
	if (currentNumber >= 1 && currentNumber <= maxNumber) return true;
	else return false;
}