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
#define MAP_POSITION_Y			7
#define TEXT_INFO_POSITION_X	5

#define FLAG_LETTER				'F'
#define BIG_UNCOVER_LETTER		'M'
#define COVERED_SQUARE			'*'
#define QUIT_LETTER				'Q'
#define BACK_TO_MENU_LETTER		'B'

#define WON						 0
#define LOST					 1

struct Map
{
	bool firstUncover, won, lost;
	char difficulty;
	unsigned short int rows, columns, noBombs, noRevealedSquares;
	clock_t startTime, endTime;
	struct BoardCell map[MAX_ROWS + 1][MAX_COLUMNS + 1]; // 1 -> MAX_ROW

	void initialize(const short &currentRows, const short &currentColumns, const short &currentBombs);
	void setDimensions(const unsigned short &newRows, const unsigned short &newColumns, const unsigned short &newNoBombs);
	void generateMines(const Position &safePosition);
	
	void endGame(const bool &end);
	void revealMap();
	bool checkWinCondition();

	void printOnScreen();
	void print(const int &x, const int &y);
	void printInfo(const int &x, const int &y);
	void printTimeElapsed();
	void printLetterIdentifierOnRow(int x, int y, const int &textColor);
	void printNumberIdentifierOnColumn(int x, int y, const int &textColor);
	void printIdentifierSeparatorOnRow(int x, int y, const int &textColor);
	void printIdentifierSeparatorOnColumn(int x, int y, const int &textColor);
	void printCharacter(const char &character);
	void printGameEndMessage(const bool &end);

	void processInput(char &gameState);

	Position getPositionFromInput(const char *playerInput);
	void updateSquare(const Position &currentPosition, const char *playerInput);
	void revealSquares(const Position &startPosition);
	void revealSurroundedSquares(const Position &currentPosition);
	void revealCurrentSquare(const Position &currentPosition);
	void revealAllSquares();
	void switchFlagState(const Position &currentPosition);
	char countFlaggedNeighbours(const Position &currentPosition);
	void incrementNeighbours(const Position &minedPosition);
	void incrementSquare(const Position &neighbour);
	void placeMine(const Position &currentPosition);
	bool checkBorders(const Position &currentPosition);

	char getSquareValue(const Position &currentPosition);

	inline bool isSquareCovered(const Position &currentPosition);
	inline bool isSquareFlagged(const Position &currentPosition);
	inline bool isSquareMine(const Position &currentPosition);
};

#endif