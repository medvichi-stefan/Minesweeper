#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

#include "stdafx.h"

#define MAX_ROWS				24
#define MAX_COLUMNS				30
#define MAX_NO_BOMBS			668
#define MIN_ROWS				5
#define MIN_COLUMNS				5
#define MIN_NO_BOMBS			2

#define EASY_NO_ROWS			9
#define EASY_NO_COLUMNS			9
#define EASY_NO_BOMBS			10

#define MEDIUM_NO_ROWS			16
#define MEDIUM_NO_COLUMNS		16
#define MEDIUM_NO_BOMBS			40

#define HARD_NO_ROWS			16
#define HARD_NO_COLUMNS			30
#define HARD_NO_BOMBS			99

#define MAX_INPUT_SIZE			16
#define INPUT_SIZE				5
#define INPUT_SIZE_DIMENSION	4
#define INPUT_SIZE_MAIN			2
#define INPUT_SIZE_SETTINGS		2

#define MENU_POSITION_X			5
#define MENU_POSITION_Y			5

void initializeSystem();
void quit();
void gotoXY(const int &x, const int &y);
void clearConsole();
void getWindowSize(int &rows, int &columns);
void setWindowSize(const int &rows, const int &columns);
void setCursorSize(const unsigned short int &size);
void setCursorVisible(const bool &show);
void setFont(const unsigned short &x, const unsigned short &y);
void setTextColor(const int &color);

void readPlayerInput(char *playerInput, const int &inputSizeLimit);
void processMainMenuInput(char &gameState);
void processSettingsInput(char &gameState, short &rows, short &columns, short &bombs);
void processLeaderboardInput();
void processCustomDimension(short &rows, short &columns, short &bombs);
void printFeedback(const int &posX, const int &posY, const char *feedbackText);


void printMainMenu();
void printSettingsMenu();
void printLeaderboard();

unsigned short getNumberFromString(const char *string);

inline unsigned short getNumberFromChar(const char &character)
{
	return character - 'a' + 1;
}

inline char getCharFromNumber(const unsigned short &number)
{
	return number -1 + 'a';
}

inline bool isMarkingLetter(const char &currentCharacter)
{
	if (currentCharacter == 'F' || currentCharacter == 'M') return true;
	else return false;
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

#endif