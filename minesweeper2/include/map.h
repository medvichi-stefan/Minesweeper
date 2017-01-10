#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <ctime>

#define MAX_ROWS				24
#define MAX_COLUMNS				30
#define MAX_NO_BOMBS			668

#define MAX_INPUT_SIZE			16
#define INPUT_SIZE				5

#define MAP_POSITION_X			10
#define TEXT_INFO_POSITION_X	5

#define FLAG_LETTER				'F'
#define BIG_UNCOVER_LETTER		'M'
#define COVERED_SQUARE			'*'

struct Position
{
	unsigned short row, column;
};

struct Map
{
	unsigned short int rows, columns, noBombs;
	struct BoardCell map[MAX_ROWS + 1][MAX_COLUMNS + 1];
	bool firstUncover;

	void initialize();
	void setDimensions(const unsigned short &newRows, const unsigned short &newColumns, const unsigned short &newNoBombs);
	void generateMines(const Position &safePosition);

	void printOnScreen();
	void print(const int &x, const int &y);
	void printInfo(const int &x, const int &y);
	void printLetterIdentifierOnRow(int x, int y, const int &textColor);
	void printNumberIdentifierOnColumn(int x, int y, const int &textColor);
	void printIdentifierSeparatorOnRow(int x, int y, const int &textColor);
	void printIdentifierSeparatorOnColumn(int x, int y, const int &textColor);

	void processInput();

	Position getPositionFromInput(const char *playerInput);
	void updateSquare(const Position &currentPosition, const char *playerInput);
	void uncoverSquares(const Position &currentPosition);
	void switchFlagState(const Position &currentPosition);

	inline bool isSquareCovered(const Position &currentPosition);
	inline bool isSquareFlagged(const Position &currentPosition);
};

#endif