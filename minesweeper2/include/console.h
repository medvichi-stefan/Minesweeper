#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

void initializeConsole();
void gotoXY(const int &x, const int &y);
void clearConsole();
void getWindowSize(int &rows, int &columns);
void setWindowSize(const int &rows, const int &columns);
void setCursorSize(const unsigned short int &size);
void setCursorVisible(const bool &show);
void setFont(const unsigned short &x, const unsigned short &y);
void setTextColor(const int &color);

void readPlayerInput(char *playerInput, const int &inputSizeLimit);
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