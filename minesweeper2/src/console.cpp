#include "../include/stdafx.h"

void initializeConsole()
{
	setCursorSize(80);
	setCursorVisible(false);
}

void gotoXY(int x, int y)
{
	COORD coord = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

void clearConsole()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0, 0 };
	DWORD count;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		// 32 = space
		FillConsoleOutputCharacter(hStdOut, (CHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		SetConsoleCursorPosition(hStdOut, coord);
	}
	return;
}

void printOnScreen(const short &gameState)
{
	switch (gameState)
	{
	case 1:
		writeMainMenu();
		break;
	case 2:
		writeSettingsMenu();
		break;
	case 3:
		writeLeaderboard();
		break;
	}
}

void getWindowSize(int &rows, int &columns)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void setWindowSize(const int &rows, const int &columns)
{
	COORD coord;
	coord.X = rows;
	coord.Y = columns;

	SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = columns - 1;
	Rect.Right = rows - 1;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(hStdOut, coord);
	SetConsoleWindowInfo(hStdOut, TRUE, &Rect);

}

void setCursorSize(const unsigned short int &size)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;

	cursor.dwSize = size;

	SetConsoleCursorInfo(hStdOut, &cursor);
}

void setCursorVisible(const bool &show)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hStdOut, &cursorInfo);
	cursorInfo.bVisible = show;
	SetConsoleCursorInfo(hStdOut, &cursorInfo);


}

void setFont(const unsigned short &x, const unsigned short &y)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX *lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = x;
	lpConsoleCurrentFontEx->dwFontSize.Y = y;
	SetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);
}

void setTextColor(const int &color)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, color);
}

void readPlayerInput(char *playerInput, const int &inputSizeLimit)
{
	cin.getline(playerInput, INPUT_SIZE);
	cin.clear();
	//cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

unsigned short getNumberFromString(const char *string)
{
	unsigned short number = 0;

	for (int i = 0; string[i]; ++i)
	{
		number = number * 10 + string[i] - '0';
	}
	return number;
}

void writeMainMenu()
{

}

void writeSettingsMenu()
{

}

void writeLeaderboard()
{

}