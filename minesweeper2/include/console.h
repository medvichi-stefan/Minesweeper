#ifndef CONSOLE_H
#define CONSOLE_H

void initializeConsole();
void gotoXY(int x, int y);
void clearConsole();
void getWindowSize(int &rows, int &columns);
void setWindowSize(const int &rows, const int &columns);
void setCursorSize(const unsigned short int &size);
void setCursorVisible(const bool &show);
void setFont(const unsigned short &x, const unsigned short &y);
void setTextColor(const int &color);

void writeMainMenu();

#endif