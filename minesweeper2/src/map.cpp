#include "../include/stdafx.h"

void Map::initialize()
{
	int i, j;
	
	firstUncover = true;
	for (i = 1; i <= rows; ++i)
	{
		for (j = 1; j <= columns; ++j)
		{
			map[i][j] = '0';
			hasBomb[i][j] = false;
			isCovered[i][j] = true;
			isFlagged[i][j] = false;
		}
	}
}

void Map::setSize(const unsigned short &newRows, const unsigned short &newColumns, const unsigned short &newNoBombs)
{
	rows = newRows;
	columns = newColumns;
	noBombs = newNoBombs;
}

void Map::print(const int &x, const int &y)
{
	int i, j;
	char letterIdentifier;
	short int numberIdentifier;

	int currentRow, currentColumn;

	setTextColor(COLOR_YELLOW);

	currentRow = y; currentColumn = x - 2;
	for (i = 1, letterIdentifier = 'a'; i <= rows; ++i, currentRow +=2 )
	{
		gotoXY(currentColumn, currentRow);
		printf(" %c ", letterIdentifier++);
	}

	setTextColor(COLOR_WHITE);
	currentRow = y - 1; currentColumn = x;
	for (i = 1; i <= rows * 2; ++i, currentRow += 1)
	{
		gotoXY(currentColumn, currentRow);
		printf("|");
	}

	setTextColor(COLOR_YELLOW);
	currentRow = y - 3; currentColumn = x + 2;
	for (int i = 1, numberIdentifier = 1; i <= columns; ++i, currentColumn += 3)
	{
		gotoXY(currentColumn, currentRow);
		printf("%d  ", numberIdentifier++);
	}

	setTextColor(COLOR_WHITE);
	currentRow = y - 2; currentColumn = x;
	for (int i = 1; i <= columns * 3 + 1; ++i, currentColumn += 1)
	{
		gotoXY(currentColumn, currentRow);
		printf("_");
	}

	currentRow = y; currentColumn = x + 1;
	for (i = 1; i <= rows; ++i, currentRow+=2)
	{
		gotoXY(currentColumn, currentRow);
		for (j = 1; j <= columns; ++j)
		{
			if (isFlagged[i][j] && isCovered[i][j])
			{
				printf(" %c ", FLAG_LETTER);
			}
			else if (isCovered[i][j])
			{
				printf(" %c ", COVERED_SQUARE);
			}
			else
			{
				printf(" %c ", map[i][j]);
			}
		}
	}
}

void Map::printInfo(const int &x, const int &y)
{
	char lastLetter;
	short lastNumber;

	lastLetter = rows - 1 + 'a';
	lastNumber = columns;
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
	print(MAP_POSITION_X + MAX_ROWS - rows, 5);
	printInfo(TEXT_INFO_POSITION_X, rows * 2 + 5);
}

void Map::processInput()
{
	char playerInput[MAX_INPUT_SIZE];

	readPlayerInput(playerInput, INPUT_SIZE);

	Position positionRequested;
	positionRequested = getPositionFromInput(playerInput);
	
	updateSquare(positionRequested, playerInput);
}

Position Map::getPositionFromInput(const char *playerInput)
{
	char firstChar, maxLetter, currentRow;
	unsigned short maxNumber = columns;
	unsigned short currentNumber, currentColumn;
	Position currentPosition = { 0, 0 };

	maxLetter = getCharFromNumber(rows);
	firstChar = playerInput[0];

	if (isMarkingLetter(firstChar))
	{
		currentRow = tolower(playerInput[1]);
		currentColumn = getNumberFromString(playerInput + 2);
		if (isLetterInRange(currentRow, maxLetter))
		{
			currentPosition.row = getNumberFromChar(currentRow);
			if (isNumberInRange(currentColumn, maxNumber))
			{
				currentPosition.column = currentColumn;
			}
		}
	}
	else
	{
		firstChar = tolower(firstChar);
		currentRow = firstChar;
		currentColumn = getNumberFromString(playerInput + 1);
		if (isLetterInRange(firstChar, maxLetter))
		{
			currentPosition.row = getNumberFromChar(firstChar);
			if (isNumberInRange(currentColumn, maxNumber))
			{
				currentPosition.column = currentColumn;
			}
		}
	}
	return currentPosition;
}

void Map::updateSquare(const Position &currentPosition, const char *playerInput)
{
	char firstInputChar = playerInput[0];

	if (firstInputChar == FLAG_LETTER)
	{
		if (isSquareCovered(currentPosition) == true)
		{
			switchFlagState(currentPosition);
		}
	}
	else if (firstInputChar == BIG_UNCOVER_LETTER)
	{
		if (isSquareCovered(currentPosition) == true)
		{

		}
	}
	else
	{
		if (firstUncover)
		{
			firstUncover = false;
			generateMines(currentPosition);
		}
		if (isSquareCovered(currentPosition) == true)
		{
			if (isSquareFlagged(currentPosition) == false)
			{
				uncoverSquares(currentPosition);
			}
		}
	}
}

void Map::generateMines(const Position &safePosition)
{

}

void Map::uncoverSquares(const Position &currentPosition)
{
	isCovered[currentPosition.row][currentPosition.column] = false;
}

void Map::switchFlagState(const Position &currentPosition)
{
	isFlagged[currentPosition.row][currentPosition.column] = 1 ^ isFlagged[currentPosition.row][currentPosition.column];
}

inline bool Map::isSquareCovered(const Position &currentPosition)
{
	return isCovered[currentPosition.row][currentPosition.column];
}

inline bool Map::isSquareFlagged(const Position &currentPosition)
{
	return isFlagged[currentPosition.row][currentPosition.column];
}