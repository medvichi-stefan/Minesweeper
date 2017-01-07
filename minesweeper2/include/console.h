#ifndef CONSOLE_H
#define CONSOLE_H

void initializeConsole();
void gotoXY(int x, int y);
void clearConsole();
void printOnScreen(const short &gameState);
void getWindowSize(int &rows, int &columns);
void setWindowSize(const int &rows, const int &columns);
void setCursorSize(const unsigned short int &size);
void setCursorVisible(const bool &show);
void setFont(const unsigned short &x, const unsigned short &y);
void setTextColor(const int &color);
void readPlayerInput(char *playerInput, const int &inputSizeLimit);
unsigned short getNumberFromString(const char *string);

void writeMainMenu();
void writeSettingsMenu();
void writeLeaderboard();

#endif