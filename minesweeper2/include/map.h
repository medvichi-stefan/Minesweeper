#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "stack.h"
#include "board_cell.h"
#include "system.h"

#define NO_OF_NEIGHBOURS		8

#define MAX_INPUT_SIZE			16
#define INPUT_SIZE				5

#define MAP_POSITION_X			10
#define MAP_POSITION_Y			5
#define TEXT_INFO_POSITION_X	5

#define FLAG_LETTER				'F'
#define BIG_UNCOVER_LETTER		'M'
#define COVERED_SQUARE			'*'

struct Map
{
	unsigned short int rows, columns, noBombs;
	bool firstUncover, lost;
	char difficulty;
	struct BoardCell map[MAX_ROWS + 1][MAX_COLUMNS + 1]; // 1 -> MAX_ROW

	void initialize(const short &currentRows, const short &currentColumns, const short &currentBombs);
	void setDimensions(const unsigned short &newRows, const unsigned short &newColumns, const unsigned short &newNoBombs);
	void generateMines(const Position &safePosition);
	void gameLost();

	void printOnScreen();
	void print(const int &x, const int &y);
	void printInfo(const int &x, const int &y);
	void printLetterIdentifierOnRow(int x, int y, const int &textColor);
	void printNumberIdentifierOnColumn(int x, int y, const int &textColor);
	void printIdentifierSeparatorOnRow(int x, int y, const int &textColor);
	void printIdentifierSeparatorOnColumn(int x, int y, const int &textColor);
	void printCharacter(const char &character);
	void printGameLost();

	void processInput();

	Position getPositionFromInput(const char *playerInput);
	void updateSquare(const Position &currentPosition, const char *playerInput);
	void revealSquares(const Position &startPosition);
	void switchFlagState(const Position &currentPosition);
	char countFlaggedNeighbours(const Position &currentPosition);
	void incrementNeighbours(const Position &minedPosition);
	bool checkBorders(const Position &currentPosition);
	void revealAllSquares();
	inline bool isSquareCovered(const Position &currentPosition);
	inline bool isSquareFlagged(const Position &currentPosition);
};

#endif